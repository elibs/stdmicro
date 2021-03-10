#ifndef __DS3231_H
#define __DS3231_H

#include "hardware/RTC/RTC.h"
#include "hardware/I2C.h"

class DS3231: public RTC
{
public:
    DS3231(I2C* i2c);

    constexpr unsigned char address(void) const
    {
        return 0x68;
    }

    void write(const tm& timespec) override;
    void read(tm& timespec) override;

private:
    I2C* mI2c;
    char mBuffer[8];
};

#endif
