#include "GD7965.h"
#include "Frequencies.h"

GD7965::GD7965(SPI* spi, GPIO* dataCmd, GPIO* busy, GPIO* reset):
    mSpi(spi),
    mDataCmd(dataCmd),
    mBusy(busy),
    mReset(reset)
{
    mSpi->format(8, false, false, true);
}

GD7965::~GD7965(void)
{
    // NOTE: We don't actually own the pointers, so we don't free them either!
}

void GD7965::command(unsigned char byte)
{
    mDataCmd->put(false);

    mSpi->write(&byte, 1);
}

void GD7965::sendData(const unsigned char* data, size_t size)
{
    mDataCmd->put(true);

    mSpi->write(data, size);
}

void GD7965::sendData(unsigned char data)
{
    sendData(&data, 1);
}

void GD7965::draw(const unsigned char* data, size_t size)
{
    command(DISPLAY_START_TX_NEW);

    sendData(data, size);

    command(DISPLAY_REFRESH);
    sleep_ms(100);
    waitUntilIdle();
}

int GD7965::drawPartial(const unsigned char* data, size_t size, size_t x, size_t y, size_t w, size_t h)
{
    command(PARTIAL_WINDOW);

    w = (w / 8) + x - 1;
    h += y - 1;

    unsigned char windowData[9] = {
        (unsigned char)((x >> 5) & 0x03),
        (unsigned char)((x & 0x1f) << 3),
        (unsigned char)((w >> 5) & 0x03),
        (unsigned char)(0x07 | ((w & 0x1f) << 3)),

        (unsigned char)((y >> 8) & 0x03),
        (unsigned char)(y & 0x00ff),
        (unsigned char)((h >> 8) & 0x03),
        (unsigned char)(h & 0x00ff),

        (unsigned char)0x00 // 0x01 is the other option, which scans in and outside of the window (and only draws the inside), so we can to only scan the inside, hence 0.
    };
    sendData(windowData, 9);

    command(START_PARTIAL);

    draw(data, size);

    command(STOP_PARTIAL);
    return 0;
}

void GD7965::reset(void)
{
    mReset->put(true); // Pull to high
    sleep_ms(200);
    mReset->put(false); // Set low, resetting the display.
    sleep_ms(2);
    mReset->put(true); // Pull to high, powering back on
    sleep_ms(200);
}

void GD7965::powerOn(void)
{
    command(POWER_ON);
    sleep_ms(100);
    waitUntilIdle();
}

void GD7965::restart(void)
{
    reset();

    powerOn();
    vcomDcSetting();
    vcomDataIntervalSetting();
}

void GD7965::init(void)
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

void GD7965::clear(void)
{
    buffer[0] = 0x00;
    command(0x10);
    for (int i = 0; i < (width() / 8) * height(); ++i)
    {
        sendData(buffer, 1);
    }

    buffer[0] = 0xff;
    command(0x13);
    for (int i = 0; i < (width() / 8) * height(); ++i)
    {
        sendData(buffer, 1);
    }

    command(0x12);
    sleep_ms(100);
    waitUntilIdle();
}

void GD7965::waitUntilIdle(void)
{
    while (!*mBusy) // if busy is being held low (by the display), then we wait.
    {
        sleep_ms(100);
    } 
}

void GD7965::powerOff(void)
{
    command(POWER_OFF);
    waitUntilIdle();
    sleep_ms(500);

    buffer[0] = 0xa5; // Required value for deep sleep.
    command(DEEP_SLEEP);
    sendData(buffer, 1);
}
