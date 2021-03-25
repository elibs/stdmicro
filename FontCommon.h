#ifndef __FONT_COMMON_H
#define __FONT_COMMON_H

#include "FontSize.h"

#define MAX_EM 2048.0

/**
 * An em is a unit equal to the font's point size.
 *
 * Points, are a size, measured in seventy-seconds of an inch (approximately
 * 0.353mm), and are used to determine the dimensions of the point square (or,
 * em square), in which each character being rendered fits. 
 */
typedef float em;
typedef float points;

constexpr FontSize operator "" _pt(unsigned long long value)
{
    return {(unsigned int)value};
}

#endif
