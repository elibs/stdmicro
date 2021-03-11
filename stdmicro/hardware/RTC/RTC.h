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
    virtual void write(const tm& timespec) = 0;
    virtual void read(tm& timespec) = 0;
};

#endif
