#ifndef __GD7965_H
#define __GD7965_H

#include "common.h"
#include "Display.h"
#include "Pins.h"

#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/spi.h"

struct GD7965Pins
{
public:
    SPIPins spi;
    size_t dc;
    size_t busy;
    size_t reset;
};

enum GD7965Command
{
    GD7965_PANEL_SETTING = 0x00,
    GD7965_POWER_SETTING = 0x01,
    GD7965_POWER_OFF = 0x02,
    GD7965_POWER_OFF_SEQ = 0x03,
    GD7965_POWER_ON = 0x04,
    GD7965_POWER_ON_MEASURE = 0x05,
    GD7965_BOOSTER_SOFT_START = 0x06,
    GD7965_DEEP_SLEEP = 0x07,

    GD7965_DISPLAY_START_TX_OLD = 0x10,
    GD7965_DATA_STOP = 0x11,
    GD7965_DISPLAY_REFRESH = 0x12,
    GD7965_DISPLAY_START_TX_NEW = 0x13,

    GD7965_DUAL_SPI = 0x15,

    GD7965_AUTO_SEQUENCE = 0x17,

    GD7965_LUT_OPTION = 0x2A,
    GD7965_KW_LUT = 0x2B,

    GD7965_PLL_CONTROL = 0x30,

    GD7965_TEMP_SENSOR_CALIBRATION = 0x40,
    GD7965_TEMP_SENSOR_SELECT = 0x41,
    GD7965_TEMP_SENSOR_WRITE = 0x42,
    GD7965_TEMP_SENSOR_READ = 0x43,
    GD7965_PANEL_BREAK_CHECK = 0x44,

    GD7965_VCOM_DATA_INTERVAL_SETTING = 0x50,
    GD7965_LOW_POWER_DETECT = 0x51,
    GD7965_END_VOLTAGE_SETTING = 0x52,

    GD7965_TCON_SETTING = 0x60,
    GD7965_RESOLUTION_SETTING = 0x61,

    GD7965_GATE_SOURCE_START_SETTING = 0x65,

    GD7965_REVISION = 0x70,
    GD7965_GET_STATUS = 0x71,

    GD7965_AUTO_MEASUREMENT_VCOM = 0x80,
    GD7965_READ_VCOM_VALUE = 0x81,
    GD7965_VCOM_DC_SETTING = 0x82,

    GD7965_PARTIAL_WINDOW = 0x90,
    GD7965_START_PARTIAL = 0x91,
    GD7965_STOP_PARTIAL = 0x92,

    GD7965_PROGRAM_MODE = 0xA0,
    GD7965_ACTIVE_PROGRAMMING = 0xA1,
    GD7965_READ_OTP = 0xA2,

    GD7965_CASCADE_SETTING = 0xE0,

    GD7965_POWER_SAVING = 0xE3,
    GD7965_LVD_VOLTAGE_SELECT = 0xE4,
    GD7965_FORCE_TEMP = 0xE5,

    GD7965_TEMP_BOUNDARY_PHASE_C2 = 0xE7
};

// NOTE: We will be using DMA for our SPI controller, as it allows us to have
//       Direct Memory Access, and is a significantly faster transfer speed
//       than we can, ourselves, do.
class GD7965: public Display
{
public:
    GD7965(size_t width, size_t height, spi_inst_t* spiInstance, GD7965Pins pinout);

    ~GD7965(void);

    void draw(const unsigned char* data, size_t size) override;

    constexpr unsigned int dpi(void) const override
    {
        return 125;
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
    int drawPartial(const unsigned char* data, size_t size, size_t x, size_t y, size_t width, size_t height) override;

    void powerOn(void) override;

    void restart(void) override;

    void init(void) override;

    void clear(void) override;

    void powerOff(void) override;

private:
    size_t mWidth;
    size_t mHeight;
    spi_inst_t* mSpiInstance;
    GD7965Pins mPins;

    unsigned char buffer[5];

    void command(unsigned char byte);

    void sendData(const unsigned char* data, size_t size);

    void sendData(unsigned char data);

    void reset(void);

    void waitUntilIdle(void);

    void write(const unsigned char* data, size_t len);

    inline void panelSetting()
    {
        buffer[0] = 0x1f; // 00 - reserved, 0 - load LUT from OPT, 1 - black and white mode, 0 - scan down (instead of up), 1 - shift right (instead of left), 1 - booster on (default), 1 - don't soft reset.
        command(GD7965_PANEL_SETTING);
        sendData(buffer, 1);
    }

    inline void powerSetting(void)
    {
        buffer[0] = 0x07;
        buffer[1] = 0x17;
        buffer[2] = 0x3f;
        buffer[3] = 0x3f;
        buffer[4] = 0x03;
        command(GD7965_POWER_SETTING);
        sendData(buffer, 5);
    }

    inline void boosterSoftStart(void)
    {
        buffer[0] = 0x17;
        buffer[1] = 0x17;
        buffer[2] = 0x27;
        buffer[3] = 0x17;
        command(GD7965_BOOSTER_SOFT_START);
        sendData(buffer, 4);
    }

    inline void pllControl(void)
    {
        buffer[0] = 0x06;
        command(GD7965_PLL_CONTROL);
        sendData(buffer, 1);
    }

    inline void lut(void)
    {
        buffer[0] = 0x02;
        buffer[1] = 0x80;
        buffer[2] = 0x00;
        command(GD7965_KW_LUT);
        sendData(buffer, 3);
    }

    inline void resolution(void)
    {
        unsigned short width = (mWidth / 8) << 3;
        // horizontal resolution, 800
        buffer[0] = (width >> 8) & 0xff;
        buffer[1] = width & 0xff;

        // vertical resolution, 480
        buffer[2] = 0x01;
        buffer[3] = 0xe0;
        command(GD7965_RESOLUTION_SETTING);
        sendData(buffer, 4);
    }

    inline void dualSpi(void)
    {
        // Disable MM input definition, and MISO SPI pin
        buffer[0] = 0x00;
        command(GD7965_DUAL_SPI);
        sendData(buffer, 1);
    }

    inline void tconSetting(void)
    {
        buffer[0] = 0x22;
        command(GD7965_TCON_SETTING);
        sendData(buffer, 1);
    }

    inline void vcomDcSetting(void)
    {
        buffer[0] = 0x26;
        command(GD7965_VCOM_DC_SETTING);
        sendData(buffer, 1);
    }

    inline void vcomDataIntervalSetting(void)
    {
        buffer[0] = 0x89;
        buffer[1] = 0x07;
        command(GD7965_VCOM_DATA_INTERVAL_SETTING);
        sendData(buffer, 2);
    }
};

#endif
