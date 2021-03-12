#ifndef __STD_MICRO_REAL_TIME_CLOCK_H
#define __STD_MICRO_REAL_TIME_CLOCK_H

struct tm
{
    unsigned char second;
    unsigned char minute;
    unsigned char hour;
    unsigned char dayOfMonth;
    unsigned char month;
    unsigned int year;
    unsigned char dayOfWeek;
    unsigned short dayOfYear;
    unsigned char isDaylightSavingsTime;
};

inline unsigned char bcd2bin(unsigned char val)
{
    return val - (6 * (val >> 4));
}

inline unsigned char bin2bcd(unsigned char val)
{
    return val + (6 * (val / 10));
}


class RTC
{
public:
    enum AlarmFrequency
    {
        EACH_SECOND = 1,
        EACH_MINUTE = 2,
        EACH_HOUR = 4,
        EACH_DAY = 8,
        EACH_WEEK = 16,
        EACH_MONTH = 32,
        EACH_YEAR = 64,
        SPECIFIC_DATE = 128
    };

    enum AlarmError
    {
        E_ALL_GOOD = 0,
        E_NOT_SUPPORTED,
        E_MUST_ENABLE_INTERRUPT,
        E_INDEX_OUT_OF_BOUNDS,

    };

    virtual void write(const tm& timespec) = 0;
    virtual void read(tm& timespec) = 0;

    virtual AlarmError setAlarm(unsigned int index, const tm& alarmTime, unsigned int frequencyFlags) = 0;
    virtual void disableAlarm(unsigned int index) = 0;
    virtual void clearAlarm(unsigned int index) = 0;

    virtual void enableInterrupt(void) = 0;
    virtual void disableInterrupt(void) = 0;
};

#endif
