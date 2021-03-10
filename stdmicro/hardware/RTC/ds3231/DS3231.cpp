#include "DS3231.h"

DS3231::DS3231(I2C* i2c):
    mI2c(i2c)
{
}

void DS3231::write(const tm& timespec)
{
    mBuffer[0] = 0x00;
    mBuffer[1] = bin2bcd(timespec.second);
    mBuffer[2] = bin2bcd(timespec.minute);
    mBuffer[3] = bin2bcd(timespec.hour);
    mBuffer[4] = timespec.dayOfWeek & 0x0f;
    mBuffer[5] = bin2bcd(timespec.dayOfMonth);
    mBuffer[6] = bin2bcd(timespec.month);
    mBuffer[7] = bin2bcd(timespec.year - 2000U);
    mI2c->write(address(), mBuffer, 8);

    mI2c->read(address(), mBuffer, 1);
    mBuffer[0] &= ~0x80;
    mI2c->write(address(), mBuffer, 1);
}

void DS3231::read(tm& timespec)
{
    mBuffer[0] = 0;
    mI2c->write(address(), mBuffer, 1);

    mI2c->read(address(), mBuffer, 7);
    timespec.second = bcd2bin(mBuffer[0] & 0x7f);
    timespec.minute = bcd2bin(mBuffer[1]);
    timespec.hour = bcd2bin(mBuffer[2]);
    timespec.dayOfWeek = mBuffer[3] & 0x07;
    timespec.dayOfMonth = bcd2bin(mBuffer[4]);
    timespec.month = bcd2bin(mBuffer[5]);
    timespec.year = bcd2bin(mBuffer[6]) + 2000U;
}
