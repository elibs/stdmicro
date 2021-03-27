#ifndef __STD_MICRO_REAL_TIME_CLOCK_H
#define __STD_MICRO_REAL_TIME_CLOCK_H

namespace stdmicro
{

/**
 * A time structure, almost identical to what you would expect when dealing
 * with a Linux system, made smaller to deal with the fact that we are on a
 * microcontroller.
 *
 * NOTE: Technically, we could reduce this significantly further to a 64-bit
 *       value; however, many RTC devices appear to store and transfer their
 *       values as binary coded decimal (annoyingly), which means that doing so
 *       would result in incorrect values being returned or written.
 */
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

/**
 * Convert a binary-coded decimal value to binary.
 */
inline unsigned char bcd2bin(unsigned char val)
{
    return val - (6 * (val >> 4));
}

/**
 * Convert a binary value to a binary-coded decimal value.
 */
inline unsigned char bin2bcd(unsigned char val)
{
    return val + (6 * (val / 10));
}

/**
 * A real-time clock device.
 */
class RTC
{
public:
    /**
     * Used to set up alarms (from the RTC to the microcontroller/ other
     * device). Or these together to provide a bitmask of what you do, or do
     * not want to alarm on.
     * 
     * NOTE: This still needs some work, these don't exactly embody their
     *       purpose, but I haven't come up with a more accurate name as of
     *       yet.
     */
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

    /**
     * A return type for when setting alarms.
     */
    enum AlarmError
    {
        E_ALL_GOOD = 0,
        E_NOT_SUPPORTED,
        E_MUST_ENABLE_INTERRUPT,
        E_INDEX_OUT_OF_BOUNDS,

    };

    /**
     * Write a time and date to a RTC device.
     *
     * NOTE: It is not guaranteed that all fields will be stored.
     *
     * @param timespec The time and date to be written.
     */
    virtual void write(const tm& timespec) = 0;
    /**
     * Read back the current time and date from a RTC.
     *
     * NOTE: It is not guaranteed that all fields will be set.
     *
     * @param timespec The time and date to be written to.
     */
    virtual void read(tm& timespec) = 0;

    /**
     * Set an alarm on the RTC device.
     *
     * NOTE: This also enables the alarm.
     *
     * @param index The alarm index to set (0-based)
     * @param alarmTime The time for the alarm to fire at.
     * @param frequencyFlags A bitmask for the frequency you would like the
     *     alarm to fire at. See `AlarmFrequency` for fields to or together.
     * @returns AlarmError, a 0 (or `E_ALL_GOOD`) return value means that
     *     things went as expected, any other value means that something went
     *     wrong.
     */
    virtual AlarmError setAlarm(unsigned int index, const tm& alarmTime, unsigned int frequencyFlags) = 0;
    /**
     * Disable the alarm at specified index.
     */
    virtual void disableAlarm(unsigned int index) = 0;
    /**
     * Clear the alarm at specified index.
     */
    virtual void clearAlarm(unsigned int index) = 0;

    /**
     * Enable interrupt
     */
    virtual void enableInterrupt(void) = 0;
    /**
     * Disable interrupt
     */
    virtual void disableInterrupt(void) = 0;
};

} // stdmicro

#endif
