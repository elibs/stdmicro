#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/spi.h"

typedef unsigned int size_t;

struct SPIPins
{
public:
    uint miso;
    uint cs;
    uint sck;
    uint mosi;
};

struct DisplayPins
{
    SPIPins spi;
    uint dc;
    uint busy;
    uint reset;
};

#define LED_PIN 25

void blink(int count)
{
    sleep_ms(1000);
    while (count--) {
        gpio_put(LED_PIN, true);
        sleep_ms(250);
        gpio_put(LED_PIN, false);
        sleep_ms(250);
    }
}

void hang(void)
{
    gpio_put(LED_PIN, true);
    while (1)
    {
        sleep_ms(1000);
    }
}

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

#define EINK_CMD_DISPLAY_START_TX_OLD 0x10
#define EINK_CMD_DATA_STOP          0x11
#define EINK_CMD_DISPLAY_REFRESH    0x12
#define EINK_CMD_DISPLAY_START_TX_NEW 0x13

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
        mPins(pinout)
    {
        // Set up SPI 0 with a baud rate of 7MHz
        spi_init(spiInstance, 1000 * 1000);

        // Initialize the SPI pins
        gpio_init(mPins.spi.cs);
        gpio_put(mPins.spi.cs, true); // drive cs high
        gpio_set_dir(mPins.spi.cs, true); // output

        gpio_set_function(mPins.spi.miso, GPIO_FUNC_SPI);
        gpio_set_function(mPins.spi.sck, GPIO_FUNC_SPI);
        gpio_set_function(mPins.spi.mosi, GPIO_FUNC_SPI);

        // Initialize the dc, busy, and reset pins
        gpio_init(mPins.dc);
        gpio_set_dir(mPins.dc, true); // output
        gpio_init(mPins.busy);
        gpio_put(mPins.busy, true); // high, not busy
        gpio_set_dir(mPins.busy, false); // input
        gpio_init(mPins.reset);
        gpio_set_dir(mPins.reset, true); // output

        spi_set_format(spiInstance, 8, SPI_CPOL_0, SPI_CPHA_0, SPI_MSB_FIRST);
    }

    ~Display(void)
    {
        spi_deinit(mSpiInstance);
    }

    void command(unsigned short byte)
    {
        gpio_put(mPins.dc, false); // Set the pin low (command).

        write(0x6000, &byte, 1);
    }

    void sendData(const unsigned short* data, size_t size)
    {
        gpio_put(mPins.dc, true); // Set pin high (data)

        write(0x0000, data, size);
    }

    void draw(const unsigned short* data, size_t size)
    {
        command(EINK_CMD_DISPLAY_START_TX_NEW);

        sendData(data, size);

        command(EINK_CMD_DISPLAY_REFRESH);
        sleep_ms(100);
        waitUntilIdle();
    }

    int drawPartial(const unsigned short* data, size_t size, size_t x, size_t y, size_t width, size_t height)
    {
        command(EINK_CMD_PARTIAL_WINDOW);

        width += x;
        height += y;
        if (x >= 0x80 || width >= 0x80 || x >= width)
        {
            // The X or width is out of range, as such, return bad.
            return -1;
        }
        if (y >= 1024 || height >= 1024 || y >= height)
        {
            // Y or height is out of range.
            return -2;
        }

        unsigned short windowData[9] = {
            (unsigned short)((x >> 5) & 0x03),
            (unsigned short)((x & 0x1f) << 3),
            (unsigned short)((width >> 5) & 0x03),
            (unsigned short)(0x07 | ((width & 0x1f) << 3)),

            (unsigned short)((y >> 8) & 0x03),
            (unsigned short)(y & 0x00ff),
            (unsigned short)((height >> 8) & 0x03),
            (unsigned short)(height & 0x00ff),

            (unsigned short)0x00 // 0x01 is the other option, which scans in and outside of the window (and only draws the inside), so we can to only scan the inside, hence 0.
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
        sleep_ms(200);
        gpio_put(mPins.reset, true); // Back to high, it is powered on.
        sleep_ms(200);
    }

    void panelSetting()
    {
        buffer[0] = 0x17; // 00 - reserved, 0 - load LUT from OPT, 1 - black and white mode, 0 - scan down (instead of up), 1 - shift right (instead of left), 1 - booster on (default), 1 - don't soft reset.
        command(EINK_CMD_PANEL_SETTING);
        sendData(buffer, 1);
        blink(7);
    }

    void powerSetting()
    {

        buffer[0] = 0x07;
        buffer[1] = 0x17;
        buffer[2] = 0x3f;
        buffer[3] = 0x3f;
        buffer[4] = 0x03;
        command(EINK_CMD_POWER_SETTING);
        sendData(buffer, 4);
        blink(4);
    }

    void boosterSoftStart()
    {
        buffer[0] = 0x17;
        buffer[1] = 0x17;
        buffer[2] = 0x27;
        buffer[3] = 0x17;
        command(EINK_CMD_BOOSTER_SOFT_START);
        sendData(buffer, 4);
        blink(3);
    }

    void powerOn()
    {
        command(EINK_CMD_POWER_ON);
        blink(5);
        sleep_ms(100);
        waitUntilIdle();
        blink(6);
    }

    void pllControl()
    {
        buffer[0] = 0x06;
        command(EINK_CMD_PLL_CONTROL);
        sendData(buffer, 1);
        blink(8);
    }

    void init(void)
    {
        reset();
        blink(3);

        powerSetting();
        panelSetting();
        boosterSoftStart();
        powerOn();
        pllControl();

        // horizontal resolution, 800
        buffer[0] = 0x03;
        buffer[1] = 0x20;

        // vertical resolution, 480
        buffer[2] = 0x01;
        buffer[3] = 0xe0;
        command(EINK_CMD_SET_RESOLUTION);
        sendData(buffer, 4);
        blink(8);

        // Disable MM input definition, and MISO SPI pin
        buffer[0] = 0x10;
        command(EINK_CMD_DUAL_SPI);
        sendData(buffer, 1);
        blink(9);

        buffer[0] = 0x10;
        buffer[1] = 0x07;
        command(EINK_CMD_VCOM_SETTING);
        sendData(buffer, 2);
        blink(10);

        buffer[0] = 0x22;
        command(EINK_CMD_TCON_SETTING);
        sendData(buffer, 1);
        blink(11);
    }

    void waitUntilIdle(void)
    {
        while (gpio_get(mPins.busy) == 0) // if busy is being held low (by the display), then we wait.
        {
            sleep_ms(100);
        } 
    }

    void off(void)
    {
        command(EINK_CMD_POWER_OFF);
        waitUntilIdle();
        unsigned short buffer = 0x00a5; // Required value for deep sleep.
        command(EINK_CMD_DEEP_SLEEP);
        sendData(&buffer, 1);
    }

private:
    size_t mWidth;
    size_t mHeight;
    spi_inst_t* mSpiInstance;
    DisplayPins mPins;

    unsigned short buffer[5];

    void write(unsigned short preamble, const unsigned short* buffer, size_t len)
    {
        waitUntilIdle();

        gpio_put(mPins.spi.cs, false); // Active

        spi_write16_blocking(mSpiInstance, &preamble, 1);

        waitUntilIdle();

        spi_write16_blocking(mSpiInstance, buffer, len);

        gpio_put(mPins.spi.cs, true); // Inactive
    }

    void read(unsigned short* buffer, size_t bytes)
    {
        gpio_put(mPins.dc, true); // Set pin high (data)
        gpio_put(mPins.spi.cs, false); // Active

        spi_read16_blocking(mSpiInstance, 0, buffer, bytes);

        gpio_put(mPins.spi.cs, true); // Inactive
    }
};

int main() {
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    blink(1);
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
    blink(2);

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
    unsigned short image[8] = {
        (unsigned short)0x0000,
        (unsigned short)0x0001,
        (unsigned short)0x0003,
        (unsigned short)0x0007,
        (unsigned short)0x000f,
        (unsigned short)0x001f,
        (unsigned short)0x003f,
        (unsigned short)0x007f
    };
    eink.init();
    blink(12);
    eink.drawPartial(image, 8, 5, 5, 8, 8);
    blink(13);
    eink.off();

    // Finally, blink the LED to say we are done.
    blink(-1);
}
