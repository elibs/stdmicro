#ifndef __STD_MICRO_FREQUENCIES_H
#define __STD_MICRO_FREQUENCIES_H

#include "types.h"

constexpr size_t operator "" _Hz(unsigned long long value)
{
    return value;
}

constexpr size_t operator "" _KHz(unsigned long long value)
{
    return 1000 * value;
}

constexpr size_t operator "" _MHz(unsigned long long value)
{
    return 1000_KHz * value;
}

#endif
