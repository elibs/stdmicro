#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/spi.h"
#include "hardware/dma.h"

typedef unsigned int size_t;

struct SPIPins
{
public:
    int miso;
    int cs;
    int sck;
    int mosi;
};

struct DisplayPins
{
    SPIPins spi;
    int dc;
    int busy;
    int reset;
};

size_t operator "" _Hz(unsigned long long value)
{
    return value;
}

size_t operator "" _KHz(unsigned long long value)
{
    return 1000 * value;
}

size_t operator "" _MHz(unsigned long long value)
{
    return 1000_KHz * value;
}

#define EINK_CMD_PANEL_SETTING      0x00
#define EINK_CMD_POWER_SETTING      0x01
#define EINK_CMD_POWER_OFF          0x02
#define EINK_CMD_POWER_OFF_SEQ      0x03
#define EINK_CMD_POWER_ON           0x04
#define EINK_CMD_POWER_ON_MEASURE   0x05
#define EINK_CMD_BOOSTER_SOFT_START 0x06
#define EINK_CMD_DEEP_SLEEP         0x07

#define EINK_CMD_DISPLAY_START_TX   0x10
#define EINK_CMD_DATA_STOP          0x11
#define EINK_CMD_DISPLAY_REFRESH    0x12
#define EINK_CMD_DISPLAY_START_TX_RED 0x13

#define EINK_CMD_DUAL_SPI           0x15

#define EINK_CMD_AUTO_SEQUENCE      0x17

#define EINK_CMD_KW_LUT             0x2B

#define EINK_CMD_PLL_CONTROL        0x30

#define EINK_CMD_TEMP_SENSOR_CALIBRATE 0x40
#define EINK_CMD_TEMP_SENSOR_SELECT 0x41
#define EINK_CMD_TEMP_SENSOR_WRITE  0x42
#define EINK_CMD_TEMP_SENSOR_READ   0x43
#define EINK_CMD_PANEL_BREAK_CHECK  0x44

#define EINK_CMD_VCOM_SETTING       0x50
#define EINK_CMD_LOW_POWER_DETECT   0x51
#define EINK_CMD_END_VOLT_SETTING   0x52

#define EINK_CMD_TCON_SETTING       0x60
#define EINK_CMD_SET_RESOLUTION     0x61

#define EINK_CMD_GATE_SOURCE_START_SETTING 0x65

#define EINK_CMD_REVISION           0x70
#define EINK_CMD_GET_STATUS         0x71

#define EINK_CMD_AUTO_MEASURE_VCOM  0x80
#define EINK_CMD_READ_VCOM_VALUE    0x81
#define EINK_CMD_VCOM_DC_SETTING    0x82

#define EINK_CMD_PARTIAL_WINDOW     0x90
#define EINK_CMD_START_PARTIAL      0x91
#define EINK_CMD_STOP_PARTIAL       0x92

#define EINK_CMD_PROGRAM_MODE       0xA0
#define EINK_CMD_ACTIVE_PROGRAMMING 0xA1
#define EINK_CMD_READ_OTP           0xA2

#define EINK_CMD_CASCADE_SETTING    0xE0

#define EINK_CMD_POWER_SAVING       0xE3
#define EINK_CMD_LVD_VOLT_SELECT    0xE4
#define EINK_CMD_FORCE_TEMP         0xE5
#define EINK_CMD_TEMP_BOUNDARY      0xE7

// Suggested that CPOL = 0 and CPHL = 0

// From spi_dma example //
// // Just for a note:
#define POWER     36 // 3.3v
#define GROUND    3  // GND

#define MISO_PIN  6  // ???   // Unused? (display won't write us back)
#define CS_PIN    7  // CS    // chip select (low active)
#define SCK_PIN   4  // SCK   // communications clock
#define MOSI_PIN  5  // DIN   // should be the data out (from us) pin

#define BUSY_PIN  9  // BUSY  // low for busy
#define RESET_PIN 10 // RESET // low for reset
#define DC_PIN    11 // DC    // Data (high), Command (low)

// NOTE: We will be using DMA for our SPI controller, as it allows us to have
//       Direct Memory Access, and is a significantly faster transfer speed
//       than we can, ourselves, do.
class Display
{
public:
    Display(size_t width, size_t height, spi_inst_t* spiInstance, DisplayPins pinout):
        mWidth(width),
        mHeight(height),
        mSpiInstance(spiInstance),
        mPins(pinout),
        mTx(dma_claim_unused_channel(true)),
        mRx(dma_claim_unused_channel(true))
    {
        // Set up SPI 0 with a baud rate of 1MHz
        spi_init(spiInstance, 1_MHz);

        // Initialize the SPI pins
        gpio_set_function(mPins.spi.miso, GPIO_FUNC_SPI);
        gpio_init(mPins.spi.cs);
        gpio_set_function(mPins.spi.sck, GPIO_FUNC_SPI);
        gpio_set_function(mPins.spi.mosi, GPIO_FUNC_SPI);

        // Initialize the dc, busy, and reset pins
        gpio_init(mPins.dc);
        gpio_init(mPins.busy);
        gpio_init(mPins.reset);

        spi_set_format(spiInstance, 8, SPI_CPOL_0, SPI_CPHA_0, SPI_MSB_FIRST)
    }

    ~Display(void)
    {
        dma_channel_unclaim(mTx);
        dma_channel_unclaim(mRx);
        spi_deinit(mSpiInstance);
    }

    void command(unsigned char byte)
    {
        gpio_put(mPins.dc, low); // Set the pin low (command).

        write(&byte, 1);
    }

    void sendData(const void* data, size_t size)
    {
        gpio_put(mPins.dc, true); // Set pin high (data)

        write(data, size);
    }

    void draw(const void* data, size_t size)
    {
        command(EINK_CMD_DISPLAY_START_TX);

        sendData(data, size);

        command(EINK_CMD_DISPLAY_REFRESH);
        sleep_ms(100);
        waitUntilIdle();
    }

    int drawPartial(const void* data, size_t size, size_t x, size_t y, size_t width, size_t height)
    {
        command(EINK_CMD_PARTIAL_WINDOW);

        if (x >= 0x80 || width >= 0x80 || x >= width)
        {
            // The X or width is out of range, as such, return bad.
            return -1;
        }
        if (y >= 1024 || heigh >= 1024 || y >= height)
        {
            // Y or height is out of range.
            return -2;
        }

        unsigned char windowData[9] = {
            ((x >> 5) & 0x03),
            ((x & 0x1f) << 3),
            ((width >> 5) & 0x03),
            0x07 | ((width & 0x1f) << 3),

            ((y >> 8) & 0x03),
            (y & 0x00ff),
            ((height >> 8) & 0x03),
            (height & 0x00ff),

            0x00 // 0x01 is the other option, which scans in and outside of the window (and only draws the inside), so we can to only scan the inside, hence 0.
        };
        sendData(windowData, 9);

        command(EINK_CMD_START_PARTIAL);

        draw(data, size);

        command(EINK_CMD_STOP_PARTIAL);
        return 0;
    }

    void reset(void)
    {
        gpio_put(mPins.reset, false); // Set low, resetting the display.
        sleep_ms(4);
        gpio_put(mPins.reset, true); // Back to high, it is powered on.
    }

    int init(void)
    {
        reset();

        unsigned char buffer[5] = {
            0x07,
            0x17,
            0x3a,
            0x3a,
            0x03
        };
        command(EINK_CMD_POWER_SETTING);
        sendData(buffer, 5);

        command(EINK_CMD_POWER_ON);
        sleep_ms(100);
        waitUntilIdle();

        buffer[0] = 0x17; // 00 - reserved, 0 - load LUT from OPT, 1 - black and white mode, 0 - scan down (instead of up), 1 - shift right (instead of left), 1 - booster on (defualt), 1 - don't soft reset.
        command(EINK_CMD_PANEL_SETTING);
        sendData(buffer, 1);

        // horizontal resolution, 800
        buffer[0] = 0x03;
        buffer[1] = 0x20;

        // vertical resolution, 480
        buffer[2] = 0x01;
        buffer[3] = 0xe0;
        command(EINK_CMD_SET_RESOLUTION);
        sendData(buffer, 4);

        // Disable MM input definition, and MISO SPI pin
        buffer[0] = 0x00;
        command(EINK_CMD_DUAL_SPI);
        sendData(buffer, 1);

        buffer[0] = 0x10;
        buffer[1] = 0x07;
        command(EINK_CMD_VCOM_SETTING);
        sendData(buffer, 2);


        buffer[0] = 0x22;
        command(EINK_CMD_TCON_SETTING);
        sendData(buffer, 1);
    }

    void waitUntilIdle(void)
    {
        while (!gpio_get(mPins.busy)) // if busy is being held low (by the display), then we wait.
        {
            sleep_ms(10);
        } 
    }

    void off(void)
    {
        command(EINK_CMD_POWER_OFF);
        waitUntilIdle();
        unsigned char buffer = 0xa5; // Required value for deep sleep.
        command(EINK_CMD_DEEP_SLEEP);
        sendData(&buffer, 1);
    }

private:
    size_t mWidth;
    size_t mHeight;
    spi_inst_t* mSpiInstance;
    DisplayPins mPins;

    size_t mTx;
    size_t mRx;

    void write(const void* buffer, size_t bytes)
    {
        gpio_put(mPins.spi.cs, false); // Active

        dma_channel_config channelConfig = dma_channel_get_default_config(mTx);
        channel_config_set_transfer_data_size(&channelConfig, DMA_SIZE_8);
        channel_config_set_dreq(&channelConfig, spi_get_index(mSpiInstance) ? DREQ_SPI1_TX : DREQ_SPI0_TX);
        dma_channel_configure(
            mTx,
            &channelConfig,
            &spi_get_hw(mSpiInstance)->dr, // write address
            buffer, // read address
            bytes, // element count (each element is of size transfer_data_size)
            true // start now
        );

        gpio_put(mPins.spi.cs, true); // Inactive
    }
};

int main() {

    Display eink(800, 480, spi0, {
        .spi = {
            .miso = MISO_PIN,
            .cs = CS_PIN,
            .sck = SCK_PIN,
            .mosi = MOSI_PIN
        },
        .dc = DC_PIN,
        .busy = BUSY_PIN,
        .reset = RESET_PIN
    });

    /**
     * Very basic image, will be 8x8 and should be a triangle like so (stars indicating black):
     * ********
     * *******
     * ******
     * *****
     * ****
     * ***
     * **
     * *
     */
    unsigned char image[8] = {
        ~0xff,
        ~0xfe,
        ~0xfc,
        ~0xf8,
        ~0xf0,
        ~0xe0,
        ~0xc0,
        ~0x80
    }
    eink.drawPartial(image, 8, 5, 5, 8, 8);
}
