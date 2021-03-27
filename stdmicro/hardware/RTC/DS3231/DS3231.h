#ifndef __DS3231_H
#define __DS3231_H

#include "hardware/RTC/RTC.h"
#include "hardware/I2C.h"

namespace stdmicro
{

class DS3231: public RTC
{
public:
    enum Addresses
    {
        DateTime = 0x00,
        Alarm1 = 0x07,
        Alarm2 = 0x0B,
        Control = 0x0E,
        Status = 0x0F,
        AgingOffset = 0x10,
        Temperature = 0x11
    };

    DS3231(I2C* i2c);

    constexpr unsigned char address(void) const
    {
        return 0x68;
    }

    void write(const tm& timespec) override;
    void read(tm& timespec) override;

    AlarmError setAlarm(unsigned int index, const tm& alarmTime, unsigned int frequencyFlags) override;
    void disableAlarm(unsigned int index) override;
    void clearAlarm(unsigned int index) override;

    void enableInterrupt(void) override;
    void disableInterrupt(void) override;

    bool isStopped(void);

    inline unsigned char read(unsigned char reg)
    {
        mI2c->write(address(), &reg, 1);
        mI2c->read(address(), &reg, 1);
        return reg;
    }

private:
    I2C* mI2c;
    char mBuffer[8];
};

} // stdmicro

#endif
