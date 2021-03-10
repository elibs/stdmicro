#ifndef __STD_MICRO_REAL_TIME_CLOCK_H
#define __STD_MICRO_REAL_TIME_CLOCK_H

struct tm
{
    int second;
    int minute;
    int hour;
    int dayOfMonth;
    int month;
    int year;
    int dayOfWeek;
    int dayOfYear;
    int isDaylightSavingsTime;
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
    virtual void write(const tm& timespec) = 0;
    virtual void read(tm& timespec) = 0;
};

#endif
