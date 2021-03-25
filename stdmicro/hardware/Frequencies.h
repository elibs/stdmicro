#ifndef __STD_MICRO_FREQUENCIES_H
#define __STD_MICRO_FREQUENCIES_H

#include "types.h"

/**
 * Return a value in hertz
 */
constexpr size_t operator "" _Hz(unsigned long long value)
{
    return value;
}

/**
 * Return a value in KHz
 */
constexpr size_t operator "" _KHz(unsigned long long value)
{
    return 1000 * value;
}

/**
 * Return a value in MHz
 */
constexpr size_t operator "" _MHz(unsigned long long value)
{
    return 1000_KHz * value;
}

#endif
