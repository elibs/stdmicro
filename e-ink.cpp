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
    sleep_ms(1000);
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
        spi_init(spiInstance, 7_MHz);

        // Initialize the SPI pins
        gpio_init(mPins.spi.cs);
        gpio_pull_up(mPins.spi.cs); // drive cs high
        gpio_set_dir(mPins.spi.cs, true); // output

        gpio_set_function(mPins.spi.miso, GPIO_FUNC_SPI);
        gpio_set_function(mPins.spi.sck, GPIO_FUNC_SPI);
        gpio_set_function(mPins.spi.mosi, GPIO_FUNC_SPI);

        // Initialize the dc, busy, and reset pins
        gpio_init(mPins.dc);
        gpio_set_dir(mPins.dc, true); // output

        gpio_init(mPins.busy);
        gpio_set_dir(mPins.busy, false); // input

        gpio_init(mPins.reset);
        gpio_set_dir(mPins.reset, true); // output

        spi_set_format(spiInstance, 8, SPI_CPOL_0, SPI_CPHA_0, SPI_MSB_FIRST);
    }

    ~Display(void)
    {
        spi_deinit(mSpiInstance);
    }

    void command(unsigned char byte)
    {
        gpio_pull_down(mPins.dc); // Set the pin low (command).

        write(true, &byte, 1);
    }

    void sendData(const unsigned char* data, size_t size)
    {
        gpio_pull_up(mPins.dc); // Set pin high (data)

        write(false, data, size);
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

    void drawPart(const unsigned char* pbuffer, size_t xStart, size_t yStart, size_t Picture_Width, size_t Picture_Height)
    {
        command(0x13);
        int * padd;
        for (unsigned long j = 0; j < mHeight; j++)
        {
            for (unsigned long i = 0; i < mWidth/8; i++)
            {
                if( (j>=yStart) && (j<yStart+Picture_Height) && (i*8>=xStart) && (i*8<xStart+Picture_Width))
                {
                    sendData(
                            ~(
                                pbuffer[i-xStart/8 + (
                                    Picture_Width
                                    )/8*(
                                        j-yStart
                                        )
                                ]
                            )
                        );
                    // SendData(0xff);
                }
                else
                {
                    sendData(0x00);
                }
            }
        }

        command(0x12);
        sleep_ms(100);
        waitUntilIdle();
    }

    int drawPartial(const unsigned char* data, size_t size, size_t x, size_t y, size_t width, size_t height)
    {
        command(EINK_CMD_PARTIAL_WINDOW);

        width += x;
        height += y;

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
        gpio_pull_up(mPins.reset); // Pull to high
        sleep_ms(200);
        gpio_pull_down(mPins.reset); // Set low, resetting the display.
        sleep_ms(2);
        gpio_pull_up(mPins.reset); // Back to high, it is powered on.
        sleep_ms(200);
    }

    void panelSetting()
    {
        buffer[0] = 0x1f; // 00 - reserved, 0 - load LUT from OPT, 1 - black and white mode, 0 - scan down (instead of up), 1 - shift right (instead of left), 1 - booster on (default), 1 - don't soft reset.
        command(EINK_CMD_PANEL_SETTING);
        sendData(buffer, 1);
    }

    void powerSetting()
    {
        buffer[0] = 0x07;
        buffer[1] = 0x07;
        buffer[2] = 0x3f;
        buffer[3] = 0x3f;
        command(EINK_CMD_POWER_SETTING);
        sendData(buffer, 4);
    }

    void boosterSoftStart()
    {
        buffer[0] = 0x17;
        buffer[1] = 0x17;
        buffer[2] = 0x27;
        buffer[3] = 0x17;
        command(EINK_CMD_BOOSTER_SOFT_START);
        sendData(buffer, 4);
    }

    void powerOn()
    {
        command(EINK_CMD_POWER_ON);
        sleep_ms(100);
        waitUntilIdle();
    }

    void pllControl()
    {
        buffer[0] = 0x06;
        command(EINK_CMD_PLL_CONTROL);
        sendData(buffer, 1);
    }

    void lut()
    {
        buffer[0] = 0x02;
        buffer[1] = 0x80;
        buffer[2] = 0x00;
        command(EINK_CMD_KW_LUT);
        sendData(buffer, 3);
    }

    void setResolution()
    {
        // horizontal resolution, 800
        buffer[0] = 0x03;
        buffer[1] = 0x20;

        // vertical resolution, 480
        buffer[2] = 0x01;
        buffer[3] = 0xe0;
        command(EINK_CMD_SET_RESOLUTION);
        sendData(buffer, 4);
    }

    void dualSpi(void)
    {
        // Disable MM input definition, and MISO SPI pin
        buffer[0] = 0x00;
        command(EINK_CMD_DUAL_SPI);
        sendData(buffer, 1);
    }

    void tconSetting(void)
    {
        buffer[0] = 0x22;
        command(EINK_CMD_TCON_SETTING);
        sendData(buffer, 1);
    }

    void vconDataInterval(void)
    {
        buffer[0] = 0x10;
        buffer[1] = 0x07;
        command(EINK_CMD_VCOM_SETTING);
        sendData(buffer, 2);
    }

    void init(void)
    {
        int iters = 1;
        reset();
        blink(iters++, 100); // 1

        //boosterSoftStart();
        //blink(iters++, 100); // 2
        powerSetting();
        blink(iters++, 100); // 3
        powerOn();
        blink(iters++, 100); // 4
        panelSetting();
        blink(iters++, 100); // 5
        //pllControl();
        setResolution();
        blink(iters++, 100); // 6
        dualSpi();
        blink(iters++, 100); // 7
        vconDataInterval();
        blink(iters++, 100); // 9
        tconSetting();
        blink(iters++, 100); // 8

        //buffer[0] = 0x26;
        //command(EINK_CMD_VCOM_DC_SETTING);
        //sendData(buffer, 1);

        //lut();
    }

    void clear()
    {
        command(0x10);
        buffer[0] = 0x00;
        for (int i = 0; i < mWidth * mHeight; ++i)
        {
            sendData(buffer, 1);
        }

        command(0x13);
        for (int i = 0; i < mWidth * mHeight; ++i)
        {
            sendData(buffer, 1);
        }

        command(0x12);
        sleep_ms(100);
        waitUntilIdle();
    }

    void waitUntilIdle(void)
    {
        while (gpio_is_pulled_down(mPins.busy)) // if busy is being held low (by the display), then we wait.
        {
            command(0x71);
            sleep_ms(100);
        } 
    }

    void off(void)
    {
        command(EINK_CMD_POWER_OFF);
        waitUntilIdle();
        sleep_ms(500);

        unsigned char buffer = 0xa5; // Required value for deep sleep.
        command(EINK_CMD_DEEP_SLEEP);
        sendData(&buffer, 1);
    }

private:
    size_t mWidth;
    size_t mHeight;
    spi_inst_t* mSpiInstance;
    DisplayPins mPins;

    unsigned char buffer[5];

    void write(unsigned char preamble, const unsigned char* buffer, size_t len)
    {
            gpio_pull_down(mPins.spi.cs); // Active

            spi_write_blocking(mSpiInstance, buffer, len);

            gpio_pull_up(mPins.spi.cs); // Inactive
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

    eink.clear();
    blink(4);

const unsigned char IMAGE_DATA[3096] = { //0X00,0X01,0XF0,0X00,0X67,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0XFF,0XC0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X01,0XFF,0XC0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,
0XFF,0XC0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,0XFF,0XC0,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,0XFF,0XC0,0X00,0X00,
0X00,0X00,0X01,0XF8,0X78,0X0F,0X00,0X0F,0XFF,0XFF,0XFF,0XC0,0X00,0X01,0XF0,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,0XFF,0XC0,0X00,0X00,0X00,0X00,
0X01,0XF8,0X78,0X0F,0X00,0X0F,0XFF,0XFF,0XFF,0XC0,0X00,0X01,0XF0,0X00,0X00,0X1F,
0XFF,0XFF,0XF0,0X00,0X00,0X00,0X00,0X01,0XF8,0X3F,0XFF,0XFF,0XFF,0XFC,0X03,0XF0,
0X78,0X0F,0X00,0X0F,0XFF,0XFF,0XFF,0XC0,0X00,0X01,0XF0,0X00,0X00,0X3F,0XFF,0XFF,
0XF8,0X00,0X00,0X00,0X00,0X01,0XF8,0X3F,0XFF,0XFF,0XFF,0XFC,0X07,0XEF,0X7B,0XCF,
0X00,0X0F,0XFF,0XFF,0XFF,0XC0,0X00,0X01,0XF0,0X00,0X00,0X3F,0XFF,0XFF,0XFC,0X00,
0X00,0X00,0X00,0X01,0XF8,0X3F,0XFF,0XFF,0XFF,0XFC,0X0F,0XEF,0X7B,0XCF,0X00,0X00,
0X00,0X7C,0X00,0X00,0X00,0X03,0XF0,0X00,0X00,0X3F,0XFF,0XFF,0XFE,0X00,0X00,0X00,
0X00,0X01,0XF8,0X3F,0XFF,0XFF,0XFF,0XFC,0X1F,0XCF,0X7B,0XDF,0X00,0X3F,0XFF,0XFF,
0XFF,0XF0,0X1F,0XFF,0XFF,0XFF,0X00,0X3F,0XFF,0XFF,0XFC,0X00,0X00,0X00,0X00,0X01,
0XF8,0X3F,0XFF,0XFF,0XFF,0XFC,0X3F,0X8F,0X7B,0XDF,0X00,0X3F,0XFF,0XFF,0XFF,0XF0,
0X1F,0XFF,0XFF,0XFF,0X00,0X1F,0XFF,0XFF,0XF8,0X00,0X00,0X00,0X00,0X00,0XFF,0XFF,
0XFF,0XFE,0XFF,0XFC,0X3F,0X0F,0X7B,0XDF,0XFE,0X3F,0XFF,0XFF,0XFF,0XF0,0X1F,0XFF,
0XFF,0XFF,0X00,0X00,0X00,0X1F,0XF0,0X00,0X00,0X00,0X00,0X00,0X0F,0XFF,0XFF,0XFC,
0XFF,0XFC,0X1E,0XFF,0XFF,0XFF,0XFE,0X3F,0XFF,0XFF,0XFF,0XF0,0X1F,0XFF,0XFF,0XFF,
0X00,0X00,0X00,0X7F,0XC0,0X00,0X00,0X00,0X00,0X00,0X0F,0XFF,0XFF,0XF8,0XFF,0XFC,
0X1D,0XFF,0XFF,0XFF,0XFE,0X3C,0X00,0X7C,0X01,0XF0,0X1F,0XFF,0XFF,0XFF,0X00,0X00,
0X00,0XFF,0X80,0X00,0X00,0X00,0X00,0X00,0X0F,0XFF,0XFF,0XF0,0XFF,0XFC,0X09,0XFF,
0XFF,0XFF,0XFE,0X3D,0XFE,0X7F,0XFF,0XF0,0X1F,0X01,0XF0,0X1F,0X00,0X00,0X03,0XFF,
0X00,0X00,0X00,0X00,0X00,0X00,0X0F,0XFF,0XFF,0XE0,0XFF,0XFC,0X03,0XFF,0XFF,0XFE,
0XF8,0X3D,0XFE,0X7F,0XFF,0XF0,0X1F,0X01,0XF0,0X1F,0X00,0X00,0X03,0XFE,0X00,0X00,
0X00,0X00,0X00,0X00,0X0F,0XFF,0XFF,0XE0,0XFF,0XFC,0X03,0XF0,0X00,0X7E,0XF8,0X3D,
0XFE,0X7F,0XFF,0XF0,0X1F,0X01,0XF0,0X1F,0X00,0X00,0X03,0XF0,0X00,0X00,0X00,0X00,
0X00,0X00,0X0F,0XFF,0XFF,0XE0,0XFF,0XFC,0X07,0XE0,0X00,0XFE,0XF8,0X3C,0X00,0X7C,
0X01,0XF0,0X1F,0XFF,0XFF,0XFF,0X00,0X00,0X03,0XE0,0X00,0X00,0X00,0X00,0X00,0X00,
0X0E,0X0F,0X0F,0XC1,0XF1,0XFC,0X0F,0XEF,0XFF,0XFE,0XF8,0X3D,0XFE,0X7F,0XFF,0XF0,
0X1F,0XFF,0XFF,0XFF,0X00,0X00,0X03,0XE0,0X00,0X00,0X00,0X00,0X00,0X00,0X0E,0X0F,
0X07,0XC3,0XE0,0XFC,0X1F,0XEF,0XFF,0XFE,0XF8,0X3D,0XFE,0X7F,0XFE,0XF0,0X1F,0XFF,
0XFF,0XFF,0X00,0X00,0X03,0XE0,0X00,0X00,0X00,0X00,0X00,0X00,0X0E,0X0F,0X07,0X83,
0XE0,0XFC,0X3F,0XEF,0XFF,0XFE,0XF8,0X01,0XFE,0X7F,0XFE,0X00,0X1F,0XFF,0XFF,0XFF,
0X03,0XFF,0XFF,0XFF,0XFF,0XC0,0X00,0X00,0X00,0X00,0X0F,0X07,0X07,0X83,0XC0,0X7C,
0X3F,0XEF,0XFF,0XFF,0XF8,0X00,0X00,0X7C,0X00,0X00,0X1F,0X03,0XF0,0X1F,0X03,0XFF,
0XFF,0XFF,0XFF,0XC0,0X00,0X00,0X00,0X00,0X0F,0X07,0X03,0X87,0XC0,0X7C,0X3F,0XE0,
0X00,0X3F,0XF8,0X00,0X00,0X00,0X00,0X00,0X1F,0X01,0XF0,0X1F,0X03,0XFF,0XFF,0XFF,
0XFF,0XC0,0X00,0X00,0X00,0X00,0X0F,0X06,0X03,0X07,0X80,0X3C,0X3F,0XE3,0XFF,0X0F,
0XF0,0X00,0X00,0X00,0X00,0X00,0X1F,0X01,0XF0,0X1F,0X03,0XFF,0XFF,0XFF,0XFF,0XC0,
0X00,0X00,0X00,0X00,0X0F,0X00,0X01,0X0F,0X80,0X3C,0X1F,0XE3,0XFF,0X0F,0XF0,0X07,
0XFF,0XFF,0XFF,0X80,0X1F,0XFF,0XFF,0XFF,0X00,0X00,0X07,0XE0,0X00,0X00,0X00,0X00,
0X00,0X00,0X0F,0X80,0X00,0X0F,0X80,0X3C,0X19,0XE3,0XFF,0X0F,0XF0,0X07,0XFF,0XFF,
0XFF,0X80,0X1F,0XFF,0XFF,0XFF,0X00,0X00,0X03,0XE0,0X00,0X00,0X00,0X00,0X00,0X00,
0X0F,0X80,0X60,0X0F,0X04,0X1C,0X01,0XE3,0XFF,0X0F,0XE0,0X07,0XFF,0XFF,0XFF,0X80,
0X1F,0XFF,0XFF,0XFF,0X00,0X00,0X03,0XE0,0X00,0X00,0X00,0X00,0X00,0X00,0X0F,0X80,
0X60,0X1E,0X04,0X1C,0X01,0XE3,0XCF,0X0F,0XE0,0X03,0XFF,0XFF,0XFF,0X80,0X1F,0XFF,
0XFF,0XFF,0X00,0X00,0X03,0XE0,0X00,0X00,0X00,0X00,0X00,0X00,0X0F,0XC0,0X70,0X1E,
0X0E,0X0C,0X01,0XE3,0XCF,0XF7,0XE0,0X00,0X00,0X00,0X0F,0X80,0X1F,0XFF,0XFF,0XFF,
0X00,0X00,0X03,0XE0,0X00,0X00,0X00,0X00,0X00,0X00,0X0F,0XC0,0XF0,0X3C,0X1F,0X04,
0X01,0XE3,0XCF,0XF7,0XC0,0X03,0XFF,0XFF,0XFF,0X80,0X1F,0X01,0XF0,0X01,0XC0,0X00,
0X03,0XE0,0X00,0X00,0X00,0X00,0X00,0X00,0X0F,0XE0,0XF0,0X78,0X1F,0X0C,0X01,0XE7,
0XCF,0XFF,0XE0,0X03,0XFF,0XFF,0XFF,0X80,0X1F,0X01,0XF0,0X03,0XF0,0X00,0X03,0XE0,
0X00,0X00,0X00,0X00,0X00,0X00,0X0F,0XE0,0XF0,0X78,0X3E,0X0C,0X01,0XE7,0XCF,0XFF,
0XF0,0X03,0XFF,0XFF,0XFF,0X80,0X1F,0X01,0XF0,0X03,0XF0,0X00,0X03,0XE0,0X00,0X00,
0X00,0X00,0X00,0X00,0X0F,0XE0,0XF8,0X78,0X3E,0X1C,0X01,0XE7,0XCF,0XFF,0XF0,0X01,
0XFF,0XFF,0XFF,0X80,0X00,0X01,0XF0,0X03,0XF0,0X00,0X03,0XE0,0X00,0X00,0X00,0X00,
0X00,0X00,0X0F,0XF1,0XF8,0X78,0X3C,0X1C,0X01,0XEF,0X8F,0XBF,0XF8,0X00,0X00,0X00,
0X0F,0X80,0X00,0X01,0XF0,0X03,0XE0,0X00,0X03,0XE0,0X00,0X00,0X00,0X00,0X00,0X00,
0X0F,0XFF,0XFF,0XFF,0XFC,0X3C,0X01,0XEF,0X8F,0XFF,0XFC,0X07,0XFF,0XFF,0XFF,0X80,
0X00,0X01,0XFF,0XFF,0XE0,0X03,0XFF,0XE0,0X00,0X00,0X00,0X00,0X00,0X00,0X0F,0XFF,
0XFF,0XFF,0XF0,0X3C,0X01,0XFF,0X8F,0XFE,0XFF,0X07,0XFF,0XFF,0XFF,0X80,0X00,0X01,
0XFF,0XFF,0XE0,0X01,0XFF,0XE0,0X00,0X00,0X00,0X00,0X00,0X00,0X0F,0XFF,0XFF,0XFF,
0XF0,0X7C,0X01,0XFF,0X01,0XFC,0X7E,0X07,0XFF,0XFF,0XFF,0X80,0X00,0X01,0XFF,0XFF,
0XC0,0X01,0XFF,0XE0,0X00,0X00,0X00,0X00,0X00,0X00,0X0F,0XFF,0XFF,0XFF,0XF0,0X7C,
0X01,0XE7,0X00,0XF8,0X3C,0X07,0XFF,0XFF,0XFF,0X80,0X00,0X00,0XFF,0XFF,0XC0,0X01,
0XFF,0XC0,0X00,0X00,0X00,0X00,0X00,0X00,0X0F,0XFF,0XFF,0XFF,0XF0,0X7C,0X01,0XE6,
0X00,0XF0,0X18,0X00,0X00,0X00,0X0F,0X80,0X00,0X00,0X7F,0XFF,0X80,0X01,0XFF,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X0F,0XFF,0XFF,0XFF,0XF0,0XFC,0X01,0XE0,0X00,0X60,
0X00,0X00,0X00,0X00,0X0F,0X80,0X00,0X00,0X00,0X00,0X00,0X00,0XF0,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X0F,0XFF,0XFF,0XFF,0XF1,0XFC,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X0F,0XFF,0XFF,0XFF,0XF3,0X83,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFE,0X00,0X00,0X00,0X00,
0X0F,0XFF,0XFF,0XFF,0XF7,0X83,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFE,0X00,0X00,0X00,0X00,0X0F,0XFF,
0XFF,0XFF,0XFF,0X83,0XFF,0XFF,0XFF,0XFF,0XFF,0XF8,0XFF,0XFF,0XFF,0XFF,0XFF,0X3F,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFE,0X00,0X00,0X00,0X00,0X0F,0XFF,0XFF,0XFF,
0XFF,0X83,0XCE,0X71,0XFF,0XFF,0XFF,0XF8,0XFF,0XFF,0XFF,0XFF,0X03,0X3F,0XFF,0XFF,
0XFF,0XFF,0XFE,0X3F,0XFF,0XFE,0X00,0X00,0X00,0X00,0X0F,0XFF,0XFF,0XFF,0XFF,0X83,
0XC6,0X33,0XFF,0XFF,0XFF,0XF8,0XFF,0XFF,0XFF,0XFF,0X3F,0X3F,0XFF,0XF3,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFE,0X00,0X00,0X00,0X00,0X0F,0XFF,0XFF,0XFF,0XFF,0XFF,0XC6,0X23,
0X8E,0X79,0X8F,0X80,0X1F,0X1E,0X1E,0X3F,0X3F,0X3C,0X7C,0X20,0X83,0X8E,0X4F,0X3C,
0X30,0XFE,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0XFF,0XC4,0X23,0X07,0X33,
0X07,0X08,0X0E,0X0C,0X18,0X1F,0X3F,0X30,0X38,0X20,0X82,0X06,0X06,0X30,0X30,0XFE,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0XFF,0XE4,0X03,0X33,0X32,0X32,0X78,
0XC6,0X44,0X39,0X9F,0X07,0X31,0XB1,0XF3,0X8E,0X66,0X22,0X31,0XE7,0XFE,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0XFF,0XE0,0X07,0XC3,0X02,0X03,0X18,0XC7,0X84,
0X70,0X1F,0X3F,0X30,0X13,0XF3,0X9C,0X62,0X62,0X33,0XE1,0XFE,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0XFF,0XE1,0X87,0X03,0X06,0X03,0X88,0XC6,0X04,0X70,0X1F,
0X3F,0X30,0X13,0XF3,0X9C,0X62,0X62,0X33,0XF0,0XFE,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0XFF,0XE1,0X86,0X33,0X06,0X7F,0XC0,0XC4,0X44,0X71,0XFF,0X3F,0X33,
0XF3,0XF3,0X9C,0X62,0X62,0X33,0XFC,0XFE,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0XFF,0XE1,0X8E,0X23,0X8F,0X3F,0XC8,0XC4,0X44,0X78,0XFF,0X3F,0X31,0XF9,0XF1,
0X9E,0X06,0X62,0X31,0XFC,0XFE,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0XFF,
0XF1,0X8F,0X03,0X8F,0X86,0X18,0XC6,0X04,0X7C,0X1F,0X03,0X3C,0X3C,0X30,0X9F,0X0E,
0X62,0X3C,0X61,0XFE,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFE,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFE,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFE,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,};

    eink.drawPart(IMAGE_DATA, 250, 200, 240, 103);
    blink(5);

    eink.off();

    ///**
    // * Very basic image, will be 8x8 and should be a triangle like so (stars indicating black):
    // * ********
    // * *******
    // * ******
    // * *****
    // * ****
    // * ***
    // * **
    // * *
    // */
    //unsigned char image[8] = {
    //    (unsigned char)0x00,
    //    (unsigned char)0x01,
    //    (unsigned char)0x03,
    //    (unsigned char)0x07,
    //    (unsigned char)0x0f,
    //    (unsigned char)0x1f,
    //    (unsigned char)0x3f,
    //    (unsigned char)0x7f
    //};
    //eink.init();
    //blink(12);
    //eink.drawPartial(image, 8, 5, 5, 8, 8);
    //blink(13);
    //eink.off();

    // Finally, blink the LED to say we are done.
    blink(10, 100);
    sleep_ms(-1);
}
