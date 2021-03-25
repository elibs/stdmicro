#include "DS3231.h"

DS3231::DS3231(I2C* i2c):
    mI2c(i2c)
{
}

void DS3231::write(const tm& timespec)
{
    mBuffer[0] = DateTime;
    mBuffer[1] = bin2bcd(timespec.second);
    mBuffer[2] = bin2bcd(timespec.minute);
    mBuffer[3] = bin2bcd(timespec.hour);
    mBuffer[4] = timespec.dayOfWeek & 0x0f;
    mBuffer[5] = bin2bcd(timespec.dayOfMonth);
    mBuffer[6] = bin2bcd(timespec.month);
    mBuffer[7] = bin2bcd(timespec.year - 2000U);
    mI2c->write(address(), mBuffer, 8);

    // Ensure that the oscillator is enabled.
    mBuffer[0] = Control;
    mI2c->write(address(), mBuffer, 1);
    mI2c->read(address(), mBuffer + 1, 1);
    mBuffer[1] &= ~0x80;
    mI2c->write(address(), mBuffer, 2);

    // Clear the oscillator stopped flag.
    mBuffer[0] = Status;
    mI2c->write(address(), mBuffer, 1);
    mI2c->read(address(), mBuffer + 1, 1);
    mBuffer[1] &= ~0x80;
    mI2c->write(address(), mBuffer, 2);
}

void DS3231::read(tm& timespec)
{
    mBuffer[0] = DateTime;
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

static inline unsigned char flag(bool f)
{
    if (f)
    {
        return 1;
    }
    return 0;
}

RTC::AlarmError DS3231::setAlarm(unsigned int index, const tm& alarmTime, unsigned int frequencyFlags)
{
    if (index >= 2)
    {
        return RTC::E_INDEX_OUT_OF_BOUNDS;
    }

    mBuffer[0] = Control;
    mI2c->write(address(), mBuffer, 1);
    unsigned char control;
    mI2c->read(address(), &control, 1);
    if ((control & 0x04) == 0)
    {
        // the Interrupt bit hasn't been enabled, so alarms won't work as expected.
        return RTC::E_MUST_ENABLE_INTERRUPT;
    }

    mBuffer[0] = index == 0 ? Alarm1 : Alarm2;
    mBuffer[1] = bin2bcd(alarmTime.second) | (flag(frequencyFlags & RTC::EACH_SECOND) << 7);
    mBuffer[2] = bin2bcd(alarmTime.minute) | (flag(frequencyFlags & RTC::EACH_MINUTE) << 7);
    mBuffer[3] = bin2bcd(alarmTime.hour) | (flag(frequencyFlags & RTC::EACH_HOUR) << 7);

    unsigned char dowFlag = flag(frequencyFlags & RTC::EACH_WEEK) << 6;
    if (dowFlag)
    {
        mBuffer[4] = bin2bcd(alarmTime.dayOfWeek);
    }
    else
    {
        mBuffer[4] = bin2bcd(alarmTime.dayOfMonth);
    }

    mBuffer[4] |= (flag(frequencyFlags & EACH_DAY) << 7) | dowFlag;

    if (index == 1)
    {
        mBuffer[1] = mBuffer[0];
    }

    mI2c->write(address(), mBuffer + index, 5 - index);

    control |= (0x01 << index);
    mBuffer[0] = Control;
    mBuffer[1] = control;
    mI2c->write(address(), mBuffer, 2);

    return RTC::E_ALL_GOOD;
}

void DS3231::disableAlarm(unsigned int index)
{
    if (index >= 2)
    {
        return;
    }

    mBuffer[0] = Control;
    mI2c->write(address(), mBuffer, 1);
    mI2c->read(address(), mBuffer + 1, 1);

    mBuffer[1] &= ~(0x01 << index);
    mI2c->write(address(), mBuffer, 2);
}

void DS3231::clearAlarm(unsigned int index)
{
    mBuffer[0] = Status;
    mI2c->write(address(), mBuffer, 1);
    mI2c->read(address(), mBuffer + 1, 1);

    mBuffer[1] &= ~(0x01 << index);
    mI2c->write(address(), mBuffer, 2);
}

void DS3231::enableInterrupt(void)
{
    mBuffer[0] = Control;
    mI2c->write(address(), mBuffer, 1);
    mI2c->read(address(), mBuffer + 1, 1);

    // a = 10, b = 11, c = 12 = 1100
    // 0x1c = 00011100
    mBuffer[1] |= 0x04;
    mI2c->write(address(), mBuffer, 2);

    // Disable 32kHz square wave.
    mBuffer[0] = Status;
    mI2c->write(address(), mBuffer, 1);
    mI2c->read(address(), mBuffer + 1, 1);
    mBuffer[1] &= ~(0x01 << 3);
    mI2c->write(address(), mBuffer, 2);
}

void DS3231::disableInterrupt(void)
{
    mBuffer[0] = Control;
    mI2c->write(address(), mBuffer, 1);
    mI2c->read(address(), mBuffer + 1, 1);

    mBuffer[1] &= ~0x04;
    mI2c->write(address(), mBuffer, 2);
}

bool DS3231::isStopped(void)
{
    mBuffer[0] = Status;
    mI2c->write(address(), mBuffer, 1);
    mI2c->read(address(), mBuffer, 1);
    return mBuffer[1] & 0x80;
}
