#ifndef __DS3231_H
#define __DS3231_H

#include "hardware/RTC/RTC.h"
#include "hardware/I2C.h"

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

private:
    I2C* mI2c;
    char mBuffer[8];
};

#endif
