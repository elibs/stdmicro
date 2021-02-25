#include "Display.h"
#include "Frequencies.h"

Display::Display(size_t width, size_t height, spi_inst_t* spiInstance, DisplayPins pinout):
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

Display::~Display(void)
{
    spi_deinit(mSpiInstance);
}

void Display::command(unsigned char byte)
{
    gpio_put(mPins.dc, 0); // Set the pin low (command).

    write(&byte, 1);
}

void Display::sendData(const unsigned char* data, size_t size)
{
    gpio_put(mPins.dc, 1); // Set pin high (data)

    write(data, size);
}

void Display::sendData(unsigned char data)
{
    sendData(&data, 1);
}

void Display::draw(const unsigned char* data, size_t size)
{
    command(EINK_CMD_DISPLAY_START_TX_NEW);

    sendData(data, size);

    command(EINK_CMD_DISPLAY_REFRESH);
    sleep_ms(100);
    waitUntilIdle();
}

int Display::drawPartial(const unsigned char* data, size_t size, size_t x, size_t y, size_t width, size_t height)
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

void Display::reset(void)
{
    gpio_put(mPins.reset, 1); // Pull to high
    sleep_ms(200);
    gpio_put(mPins.reset, 0); // Set low, resetting the display.
    sleep_ms(2);
    gpio_put(mPins.reset, 1); // Back to high, it is powered on.
    sleep_ms(200);
}

void Display::powerOn(void)
{
    command(EINK_CMD_POWER_ON);
    sleep_ms(100);
    waitUntilIdle();
}

void Display::restart(void)
{
    reset();

    powerOn();
    vcomDcSetting();
    vcomDataIntervalSetting();
}

void Display::init(void)
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
    vcomDataIntervalSetting();
    lut();
}

void Display::clear(void)
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

void Display::waitUntilIdle(void)
{
    while (gpio_get(mPins.busy) == 0) // if busy is being held low (by the display), then we wait.
    {
        sleep_ms(100);
    } 
}

void Display::powerOff(void)
{
    command(EINK_CMD_POWER_OFF);
    waitUntilIdle();
    sleep_ms(500);

    buffer[0] = 0xa5; // Required value for deep sleep.
    command(EINK_CMD_DEEP_SLEEP);
    sendData(buffer, 1);
}

void Display::write(const unsigned char* data, size_t len)
{
    gpio_put(mPins.spi.cs, 0); // Active

    spi_write_blocking(mSpiInstance, data, len);

    gpio_put(mPins.spi.cs, 1); // Inactive
}
