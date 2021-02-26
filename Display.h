#ifndef __DISPLAY_H
#define __DISPLAY_H

#include "common.h"
#include "DisplayInterface.h"
#include "Pins.h"

#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/spi.h"

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

#define EINK_CMD_VCOM_DATA_INTERVAL_SETTING 0x50
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

// NOTE: We will be using DMA for our SPI controller, as it allows us to have
//       Direct Memory Access, and is a significantly faster transfer speed
//       than we can, ourselves, do.
class Display: public DisplayInterface
{
public:
    Display(size_t width, size_t height, spi_inst_t* spiInstance, DisplayPins pinout);

    ~Display(void);

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
    DisplayPins mPins;

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
        command(EINK_CMD_PANEL_SETTING);
        sendData(buffer, 1);
    }

    inline void powerSetting(void)
    {
        buffer[0] = 0x07;
        buffer[1] = 0x17;
        buffer[2] = 0x3f;
        buffer[3] = 0x3f;
        buffer[4] = 0x03;
        command(EINK_CMD_POWER_SETTING);
        sendData(buffer, 5);
    }

    inline void boosterSoftStart(void)
    {
        buffer[0] = 0x17;
        buffer[1] = 0x17;
        buffer[2] = 0x27;
        buffer[3] = 0x17;
        command(EINK_CMD_BOOSTER_SOFT_START);
        sendData(buffer, 4);
    }

    inline void pllControl(void)
    {
        buffer[0] = 0x06;
        command(EINK_CMD_PLL_CONTROL);
        sendData(buffer, 1);
    }

    inline void lut(void)
    {
        buffer[0] = 0x02;
        buffer[1] = 0x80;
        buffer[2] = 0x00;
        command(EINK_CMD_KW_LUT);
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
        command(EINK_CMD_SET_RESOLUTION);
        sendData(buffer, 4);
    }

    inline void dualSpi(void)
    {
        // Disable MM input definition, and MISO SPI pin
        buffer[0] = 0x00;
        command(EINK_CMD_DUAL_SPI);
        sendData(buffer, 1);
    }

    inline void tconSetting(void)
    {
        buffer[0] = 0x22;
        command(EINK_CMD_TCON_SETTING);
        sendData(buffer, 1);
    }

    inline void vcomDcSetting(void)
    {
        buffer[0] = 0x26;
        command(EINK_CMD_VCOM_DC_SETTING);
        sendData(buffer, 1);
    }

    inline void vcomDataIntervalSetting(void)
    {
        buffer[0] = 0x89;
        buffer[1] = 0x07;
        command(EINK_CMD_VCOM_DATA_INTERVAL_SETTING);
        sendData(buffer, 2);
    }
};

#endif
