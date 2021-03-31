#ifndef __STD_MICRO_GD7965_H
#define __STD_MICRO_GD7965_H

#include "common.h"
#include "hardware/display/Display.h"
#include "hardware/SPI.h"
#include "hardware/GPIO.h"

namespace stdmicro
{

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
        /**
         * Bit fields:
         * 7-6: Reserved
         * 5: LUT Selection. 0 to load LUT from OTP (the default), or 1 to read
         *    the LUT from registers
         * 4: Black/ White/ Red. 0 means that the pixels are in Black/ White/
         *    Red mode (default), or 1 to be in Black and White mode. The
         *    GD7965 is a black-and-white display, so we want 0 here.
         * 3: Gate Scan Direction: 0 to scan down, 1 to scan up (default).
         * 2: Source Shift Direction. 0 to shift left, 1 to shift right (default)
         * 1: Booster Switch. 0 off, 1 on (default). When the booster is off the
         *    charge pump is diabled, which means that register and RAM values
         *    will be lost when voltage is turned off (for instance, on a power
         *    down). This also releases Source, Gate, Border, and VCOM to
         *    floating.
         * 0: Soft Reset. 0 Reset (booster off, register data is set to default,
         *    all drivers are reset and all functions are disabled. Source,
         *    Gate, Border, and VCOM are also released to floating. 1 means no
         *    effect (default).
         */
        buffer[0] = 0b00011111;
        command(PANEL_SETTING);
        sendData(buffer, 1);
    }

    inline void powerSetting(void)
    {
        /**
         * 7-5: reserved
         * 4: Border LDO enable. 0 to disable (default), 1 to enable
         * 3: reserved
         * 2: Source LV power selection. 0 external power, 1 internal DC/DC to
         *    generate voltage (default).
         * 1: Source power selection. 0 external power, 1 internal power
         *    (default).
         * 0: Gate power selection. 0 external, 1 internal (default)
         */
        buffer[0] = 0x07;
        /**
         * 7: OTP program power selection. 0 external, 1 internal (default).
         *    The voltage is determined by the internal VDHR power selection.
         * 6-5: reserved
         * 4: VCOM slew rate selection. 0 slow, 1 fast.
         * 3: reserved
         * 2-0: VGH/VGL voltage level selection. 111b is the default. See
         *    datasheet for specific voltages at each option.
         */
        buffer[1] = 0x17;
        /**
         * 7-6: reserved
         * 5-0: Internal VDH power selection (default 111010b). See datasheet
         *    for specific voltages at each option.
         */
        buffer[2] = 0x3f;
        /**
         * 7-6: reserved
         * 5-0: Internal VDL power selection (default 111010b). See datasheet
         *    for specific voltages at each option.
         */
        buffer[3] = 0x3f;
        /**
         * 7-6: reserved
         * 5-0: Internal VDHR power selection (default 111010b). See datasheet
         *    for specific voltages at each option.
         */
        buffer[4] = 0x03;
        command(POWER_SETTING);
        sendData(buffer, 5);
    }

    inline void boosterSoftStart(void)
    {
        /**
         * 7-6: Soft start period for phase A. 00b = 10mx, 01b: 20ms,
         *    10b: 30ms, 11b: 40ms
         * 5-3: Phase A driving strength. Strength = 1 + value (1-8). 8 is
         *    strongest
         * 2-0: Minimum off time setting for phase A. 000b: .27us, 001b: .34us,
         *    010b: .4us, 011b: .54us, 100b: .8us, 101b: 1.54us, 110b: 3.34us,
         *    111b: 6.58us
         * NOTE: The strengths, periods, and off times are the same for each of
         *       the other phases in this command.
         */
        buffer[0] = 0x17;
        /**
         * 7-6: Soft start period for phase B.
         * 5-3: Phase B driving strength
         * 2-0: Minimum off time for phase B.
         */
        buffer[1] = 0x17;
        /**
         * 7-6: reserved
         * 5-3: Phase C1 driving strength
         * 2-0: Minimum off time for phase C1.
         */
        buffer[2] = 0x27;
        /**
         * 7: Phase C2 enabled. 0 to disable, 1 to enable.
         * 6: reserved
         * 5-3: Phase C1 driving strength
         * 2-0: Minimum off time for phase C1.
         */
        buffer[3] = 0x17;
        command(BOOSTER_SOFT_START);
        sendData(buffer, 4);
    }

    inline void pllControl(void)
    {
        /**
         * 7-4: reserved
         * 3-0: PLL clock frequency. 0000b 5Hz, 0001b: 10Hz, 0010b: 15Hz,
         *    0011b: 20Hz, 0100b: 30Hz, 0101b: 40Hz, 0110b: 50Hz, 0111b: 60Hz,
         *    1000b: 70Hz, 1001b: 80Hz, 1010b: 90Hz, 1011b: 100Hz,
         *    1100b: 110Hz, 1101b: 130Hz, 1110b: 150Hz, 1111b: 200Hz
         */
        buffer[0] = 0x06;
        command(PLL_CONTROL);
        sendData(buffer, 1);
    }

    inline void lut(void)
    {
        /**
         * 7-2: reserved
         * 1: Black/White LUT
         * 0: Black/White/Red LUT
         *
         * 1-0: 00b Black/White/Red LUT alwasy, 01b Black/White LUT only,
         *    10b Auto detect by red data, 11b Black/White LUT only.
         */
        buffer[0] = 0x02;
        /**
         * 7-6: Black/White LUT control bits (bits 9 and 8)
         * 5-0: reserved
         */
        buffer[1] = 0x80;
        /**
         * 7-0: Black/White LUT control bits (bits 7 through 0).
         *    000000001b: Black/White LUT state 1,
         *    0000000011b state 1 and state 2, 0000001011b: state 1, 2, and 4.
         *
         * NOTE: The datasheet doesn't have a definition of _what_ these states
         *       actually mean. We use the suggested value from the datasheet's
         *       example flow diagram.
         */
        buffer[2] = 0x00;
        command(KW_LUT);
        sendData(buffer, 3);
    }

    inline void resolution(void)
    {
        unsigned short w = (width() / 8) << 3;
        // horizontal resolution, 800
        /**
         * 7-2: reserved
         * 1-0: Bits 9-8 of value
         */
        buffer[0] = (w >> 8) & 0xff;
        /**
         * 7-3: Bits 7-3 of value.
         * 2-0: Must be 0. Bits 2-0 of value
         *
         * This selects the horizontal resolution. It is worth noting that this
         * is defined to be in multiples of 8 (so 1 byte writes out 8 pixels,
         * and you can't easily write out a range that isn't a multiple of 8).
         *
         * The value winds up being value * 8 - 1
         *
         * Valid range is 0x01 - 0x64.
         */
        buffer[1] = w & 0xff;

        // vertical resolution, 480
        /**
         * 7-2: reserved
         * 1-0: Bits 9-8 of value
         */
        buffer[2] = 0x01;
        /**
         * 7-0: Bits 7-0 of value.
         *
         * The vertical resolution, valid range is 0x001 - 0x258.
         */
        buffer[3] = 0xe0;
        command(RESOLUTION_SETTING);
        sendData(buffer, 4);
    }

    inline void dualSpi(void)
    {
        /**
         * 7-6: reserved
         * 5: MM input definition enabled. 0 disable, 1 enable.
         * 4: Dual SPI mode enable. 0 disable (single SPI mode), 1 enable.
         * 3-0: reserved
         */
        buffer[0] = 0x00;
        command(DUAL_SPI);
        sendData(buffer, 1);
    }

    inline void tconSetting(void)
    {
        /**
         * 7-4: Source to Gate non-overlap period values start at
         *    0000b: 4 (period), with 0010b (default) being 12, and increase by
         *    4 for each bit, up to 1111b: 64. 1 period = 667ns.
         * 3-0: Gate to Source non-overlap period. The same as above.
         */
        buffer[0] = 0x22;
        command(TCON_SETTING);
        sendData(buffer, 1);
    }

    inline void vcomDcSetting(void)
    {
        /**
         * 7: reserved
         * 6-0: VCOM DC setting. This is determined by a table, see the
         *    datasheet for specifics.
         */
        buffer[0] = 0x26;
        command(VCOM_DC_SETTING);
        sendData(buffer, 1);
    }

    inline void vcomDataIntervalSetting(void)
    {
        /**
         * 7: Border Hi-Z control., 0 disable (default), 1 enable
         * 6: reserved
         * 5-4: Border LUT selection. This value depends on DDX as well, so
         *    look at the datasheet for specifics.
         * 3: Copy New data to Old data post-refresh enable.
         *    0 disable (default), 1 enable.
         * 2: reserved
         * 1-0: Data polality. Bit 1 is for Red data, bit 0 for Black/White
         *    data. The value of this field changes LUTs, see the datasheet for
         *    specifics.
         */
        buffer[0] = 0x89;
        /**
         * 7-4: reserved
         * 3-0: VCOM and data interval. 0111b: 10 (defualt). Lower values
         *    increase the number by 1, and higher values decrease it by 1.
         */
        buffer[1] = 0x07;
        command(VCOM_DATA_INTERVAL_SETTING);
        sendData(buffer, 2);
    }
};

} // stdmicro

#endif
