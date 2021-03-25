#ifndef __STD_MICRO_GD7965_H
#define __STD_MICRO_GD7965_H

#include "common.h"
#include "hardware/display/Display.h"
#include "hardware/SPI.h"
#include "hardware/GPIO.h"

// NOTE: We will be using DMA for our SPI controller, as it allows us to have
//       Direct Memory Access, and is a significantly faster transfer speed
//       than we can, ourselves, do.
class GD7965: public Display
{
public:
    enum Command
    {
        PANEL_SETTING = 0x00,
        POWER_SETTING = 0x01,
        POWER_OFF = 0x02,
        POWER_OFF_SEQ = 0x03,
        POWER_ON = 0x04,
        POWER_ON_MEASURE = 0x05,
        BOOSTER_SOFT_START = 0x06,
        DEEP_SLEEP = 0x07,

        DISPLAY_START_TX_OLD = 0x10,
        DATA_STOP = 0x11,
        DISPLAY_REFRESH = 0x12,
        DISPLAY_START_TX_NEW = 0x13,

        DUAL_SPI = 0x15,

        AUTO_SEQUENCE = 0x17,

        LUT_OPTION = 0x2A,
        KW_LUT = 0x2B,

        PLL_CONTROL = 0x30,

        TEMP_SENSOR_CALIBRATION = 0x40,
        TEMP_SENSOR_SELECT = 0x41,
        TEMP_SENSOR_WRITE = 0x42,
        TEMP_SENSOR_READ = 0x43,
        PANEL_BREAK_CHECK = 0x44,

        VCOM_DATA_INTERVAL_SETTING = 0x50,
        LOW_POWER_DETECT = 0x51,
        END_VOLTAGE_SETTING = 0x52,

        TCON_SETTING = 0x60,
        RESOLUTION_SETTING = 0x61,

        GATE_SOURCE_START_SETTING = 0x65,

        REVISION = 0x70,
        GET_STATUS = 0x71,

        AUTO_MEASUREMENT_VCOM = 0x80,
        READ_VCOM_VALUE = 0x81,
        VCOM_DC_SETTING = 0x82,

        PARTIAL_WINDOW = 0x90,
        START_PARTIAL = 0x91,
        STOP_PARTIAL = 0x92,

        PROGRAM_MODE = 0xA0,
        ACTIVE_PROGRAMMING = 0xA1,
        READ_OTP = 0xA2,

        CASCADE_SETTING = 0xE0,

        POWER_SAVING = 0xE3,
        LVD_VOLTAGE_SELECT = 0xE4,
        FORCE_TEMP = 0xE5,

        TEMP_BOUNDARY_PHASE_C2 = 0xE7
    };

    GD7965(SPI* spi, GPIO* dataCmd, GPIO* busy, GPIO* reset);

    ~GD7965(void);

    void draw(const unsigned char* data, size_t size) override;

    constexpr unsigned int dpi(void) const override
    {
        return 125;
    }

    constexpr unsigned int width(void) const override
    {
        return 800;
    }

    constexpr unsigned int height(void) const override
    {
        return 480;
    }

    /**
     * Redraw a part of the screen, not the entire thing
     *
     * @param data The image data (with appropriate bit depth)
     * @param size The number of bytes in the data
     * @param x The starting horizontal pixel bank. NOTE: This goes in 8-pixel chunks.
     * @param y The starting vertical pizel bank. NOTE: This goes in 1-pixel chunks.
     * @param w The width of your image. NOTE: This value must be a multiple of 8, and will be converted internally to an end-bank value (must be at least x).
     * @param h The height of your image. NOTE: This gets converted to ending y-bank internally.
     */
    int drawPartial(const unsigned char* data, size_t size, size_t x, size_t y, size_t w, size_t h) override;

    void powerOn(void) override;

    void restart(void) override;

    void init(void) override;

    void clear(void) override;

    void powerOff(void) override;

private:
    SPI* mSpi;
    GPIO* mDataCmd;
    GPIO* mBusy;
    GPIO* mReset;

    unsigned char buffer[5];

    void command(unsigned char byte);

    void sendData(const unsigned char* data, size_t size);

    void sendData(unsigned char data);

    void reset(void);

    void waitUntilIdle(void);

    inline void panelSetting()
    {
        buffer[0] = 0x1f; // 00 - reserved, 0 - load LUT from OPT, 1 - black and white mode, 0 - scan down (instead of up), 1 - shift right (instead of left), 1 - booster on (default), 1 - don't soft reset.
        command(PANEL_SETTING);
        sendData(buffer, 1);
    }

    inline void powerSetting(void)
    {
        buffer[0] = 0x07;
        buffer[1] = 0x17;
        buffer[2] = 0x3f;
        buffer[3] = 0x3f;
        buffer[4] = 0x03;
        command(POWER_SETTING);
        sendData(buffer, 5);
    }

    inline void boosterSoftStart(void)
    {
        buffer[0] = 0x17;
        buffer[1] = 0x17;
        buffer[2] = 0x27;
        buffer[3] = 0x17;
        command(BOOSTER_SOFT_START);
        sendData(buffer, 4);
    }

    inline void pllControl(void)
    {
        buffer[0] = 0x06;
        command(PLL_CONTROL);
        sendData(buffer, 1);
    }

    inline void lut(void)
    {
        buffer[0] = 0x02;
        buffer[1] = 0x80;
        buffer[2] = 0x00;
        command(KW_LUT);
        sendData(buffer, 3);
    }

    inline void resolution(void)
    {
        unsigned short w = (width() / 8) << 3;
        // horizontal resolution, 800
        buffer[0] = (w >> 8) & 0xff;
        buffer[1] = w & 0xff;

        // vertical resolution, 480
        buffer[2] = 0x01;
        buffer[3] = 0xe0;
        command(RESOLUTION_SETTING);
        sendData(buffer, 4);
    }

    inline void dualSpi(void)
    {
        // Disable MM input definition, and MISO SPI pin
        buffer[0] = 0x00;
        command(DUAL_SPI);
        sendData(buffer, 1);
    }

    inline void tconSetting(void)
    {
        buffer[0] = 0x22;
        command(TCON_SETTING);
        sendData(buffer, 1);
    }

    inline void vcomDcSetting(void)
    {
        buffer[0] = 0x26;
        command(VCOM_DC_SETTING);
        sendData(buffer, 1);
    }

    inline void vcomDataIntervalSetting(void)
    {
        buffer[0] = 0x89;
        buffer[1] = 0x07;
        command(VCOM_DATA_INTERVAL_SETTING);
        sendData(buffer, 2);
    }
};

#endif
