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

void blink(int count, uint delay = 250)
{
    while (count--) {
        gpio_put(LED_PIN, true);
        sleep_ms(delay);
        gpio_put(LED_PIN, false);
        sleep_ms(delay);
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
//      Name      GPIO // PIN
#define POWER          // 36 // 3.3v
#define GROUND         // 3  // GND

#define MISO_PIN  4    // 6  // ???   // Unused? (display won't write us back)
#define CS_PIN    5    // 7  // CS    // chip select (low active)
#define SCK_PIN   2    // 4  // SCK   // communications clock
#define MOSI_PIN  3    // 5  // DIN   // should be the data out (from us) pin

#define BUSY_PIN  6    // 9  // BUSY  // low for busy
#define RESET_PIN 7    // 10 // RESET // low for reset
#define DC_PIN    8    // 11 // DC    // Data (high), Command (low)

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
        spi_init(spiInstance, 20_MHz);

        // Initialize the SPI pins

        //gpio_set_function(mPins.spi.miso, GPIO_FUNC_SPI);
        gpio_set_function(mPins.spi.sck, GPIO_FUNC_SPI);
        gpio_set_function(mPins.spi.mosi, GPIO_FUNC_SPI);

        gpio_init(mPins.spi.cs);
        gpio_set_dir(mPins.spi.cs, GPIO_OUT); // output
        gpio_put(mPins.spi.cs, 1); // output

        // Initialize the dc, busy, and reset pins
        gpio_init(mPins.dc);
        gpio_set_dir(mPins.dc, GPIO_OUT); // output

        gpio_init(mPins.busy);
        gpio_set_dir(mPins.busy, GPIO_IN); // input

        gpio_init(mPins.reset);
        gpio_set_dir(mPins.reset, GPIO_OUT); // output

        spi_set_format(spiInstance, 8, SPI_CPOL_0, SPI_CPHA_0, SPI_MSB_FIRST);
    }

    ~Display(void)
    {
        spi_deinit(mSpiInstance);
    }

    void command(unsigned char byte)
    {
        gpio_put(mPins.dc, 0); // Set the pin low (command).

        write(&byte, 1);
    }

    void sendData(const unsigned char* data, size_t size)
    {
        gpio_put(mPins.dc, 1); // Set pin high (data)

        write(data, size);
    }

    void sendData(unsigned char data)
    {
        sendData(&data, 1);
    }

    void draw(const unsigned char* data, size_t size)
    {
        command(EINK_CMD_DISPLAY_START_TX_NEW);

        sendData(data, size);

        command(EINK_CMD_DISPLAY_REFRESH);
        sleep_ms(100);
        waitUntilIdle();
    }

    /**
     * Redraw a part of the screen, not the entire thing
     *
     * @param data The image data (with appropriate bit depth)
     * @param size The number of bytes in the data
     * @param x The starting horizontal pixel bank. NOTE: This goes in 8-pixel chunks.
     * @param y The starting vertical pizel bank. NOTE: This goes in 1-pixel chunks.
     * @param width The width of your image. NOTE: This value must be a multiple of 8, and will be converted internally to an end-bank value (must be at least x).
     * @param height The height of your image. NOTE: This gets converted to ending y-bank internally.
     */
    int drawPartial(const unsigned char* data, size_t size, size_t x, size_t y, size_t width, size_t height)
    {
        command(EINK_CMD_PARTIAL_WINDOW);

        width = (width / 8) + x - 1;
        height += y - 1;

        unsigned char windowData[9] = {
            (unsigned char)((x >> 5) & 0x03),
            (unsigned char)((x & 0x1f) << 3),
            (unsigned char)((width >> 5) & 0x03),
            (unsigned char)(0x07 | ((width & 0x1f) << 3)),

            (unsigned char)((y >> 8) & 0x03),
            (unsigned char)(y & 0x00ff),
            (unsigned char)((height >> 8) & 0x03),
            (unsigned char)(height & 0x00ff),

            (unsigned char)0x00 // 0x01 is the other option, which scans in and outside of the window (and only draws the inside), so we can to only scan the inside, hence 0.
        };
        sendData(windowData, 9);

        command(EINK_CMD_START_PARTIAL);

        draw(data, size);

        command(EINK_CMD_STOP_PARTIAL);
        return 0;
    }

    void reset(void)
    {
        gpio_put(mPins.reset, 1); // Pull to high
        sleep_ms(200);
        gpio_put(mPins.reset, 0); // Set low, resetting the display.
        sleep_ms(2);
        gpio_put(mPins.reset, 1); // Back to high, it is powered on.
        sleep_ms(200);
    }

    void powerOn()
    {
        command(EINK_CMD_POWER_ON);
        sleep_ms(100);
        waitUntilIdle();
    }

    void init(void)
    {
        reset();

        boosterSoftStart();
        powerSetting();
        powerOn();
        panelSetting();
        pllControl();
        resolution();
        dualSpi();
        tconSetting();
        vcomDcSetting();
        vcomSetting();
        lut();
    }

    void clear()
    {
        buffer[0] = 0x00;
        command(0x10);
        for (int i = 0; i < (mWidth / 8) * mHeight; ++i)
        {
            sendData(buffer, 1);
        }

        buffer[0] = 0xff;
        command(0x13);
        for (int i = 0; i < (mWidth / 8) * mHeight; ++i)
        {
            sendData(buffer, 1);
        }

        command(0x12);
        sleep_ms(100);
        waitUntilIdle();
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
        sleep_ms(500);

        buffer[0] = 0xa5; // Required value for deep sleep.
        command(EINK_CMD_DEEP_SLEEP);
        sendData(buffer, 1);
    }

private:
    size_t mWidth;
    size_t mHeight;
    spi_inst_t* mSpiInstance;
    DisplayPins mPins;

    unsigned char buffer[5];

    void write(const unsigned char* data, size_t len)
    {
        gpio_put(mPins.spi.cs, 0); // Active

        spi_write_blocking(mSpiInstance, data, len);

        gpio_put(mPins.spi.cs, 1); // Inactive
    }

    inline void panelSetting()
    {
        buffer[0] = 0x17; // 00 - reserved, 0 - load LUT from OPT, 1 - black and white mode, 0 - scan down (instead of up), 1 - shift right (instead of left), 1 - booster on (default), 1 - don't soft reset.
        command(EINK_CMD_PANEL_SETTING);
        sendData(buffer, 1);
    }

    inline void powerSetting()
    {
        buffer[0] = 0x07;
        buffer[1] = 0x17;
        buffer[2] = 0x3f;
        buffer[3] = 0x3f;
        buffer[4] = 0x03;
        command(EINK_CMD_POWER_SETTING);
        sendData(buffer, 5);
    }

    inline void boosterSoftStart()
    {
        buffer[0] = 0x17;
        buffer[1] = 0x17;
        buffer[2] = 0x27;
        buffer[3] = 0x17;
        command(EINK_CMD_BOOSTER_SOFT_START);
        sendData(buffer, 4);
    }

    inline void pllControl()
    {
        buffer[0] = 0x06;
        command(EINK_CMD_PLL_CONTROL);
        sendData(buffer, 1);
    }

    inline void lut()
    {
        buffer[0] = 0x02;
        buffer[1] = 0x80;
        buffer[2] = 0x00;
        command(EINK_CMD_KW_LUT);
        sendData(buffer, 3);
    }

    inline void resolution()
    {
        short width = (mWidth / 8) << 3;
        // horizontal resolution, 800
        buffer[0] = (width >> 8) & 0xff;
        buffer[1] = width & 0xff;

        // vertical resolution, 480
        buffer[2] = 0x01;
        buffer[3] = 0xe0;
        command(EINK_CMD_SET_RESOLUTION);
        sendData(buffer, 4);
    }

    inline void dualSpi()
    {
        // Disable MM input definition, and MISO SPI pin
        buffer[0] = 0x00;
        command(EINK_CMD_DUAL_SPI);
        sendData(buffer, 1);
    }

    inline void tconSetting()
    {
        buffer[0] = 0x22;
        command(EINK_CMD_TCON_SETTING);
        sendData(buffer, 1);
    }

    inline void vcomDcSetting()
    {
        buffer[0] = 0x26;
        command(EINK_CMD_VCOM_DC_SETTING);
        sendData(buffer, 1);
    }

    inline void vcomSetting()
    {
        buffer[0] = 0x10;
        buffer[1] = 0x07;
        command(EINK_CMD_VCOM_SETTING);
        sendData(buffer, 2);
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

    eink.init();
    blink(3);

    // Flood it to black.
    size_t bufSize = (800 * 480) / 8;
    unsigned char* buffer = new unsigned char[bufSize];
    for (int i = 0; i < bufSize; ++i)
    {
        // 1 = black, 0 = white
        buffer[i] = 0x01;
    }

    //blink(4);
    //eink.clear();

    blink(4);
    eink.draw(buffer, bufSize);

    blink(5);
    eink.off();
    blink(6);

    eink.reset();
    blink(7, 100);

    eink.powerOn();
    blink(7);

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
        (unsigned char)0x00,
        (unsigned char)0x01,
        (unsigned char)0x03,
        (unsigned char)0x07,
        (unsigned char)0x0f,
        (unsigned char)0x1f,
        (unsigned char)0x3f,
        (unsigned char)0x7f
    };
    eink.drawPartial(image, 8, 5, 5, 8, 8);
    blink(8);

    eink.off();

    // Finally, blink the LED to say we are done.
    blink(10, 100);
    sleep_ms(-1);
}
