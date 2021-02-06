#ifndef __FREQUENCIES_H
#define __FREQUENCIES_H

#include "common.h"

size_t operator "" _Hz(unsigned long long value);

size_t operator "" _KHz(unsigned long long value);

size_t operator "" _MHz(unsigned long long value);

#endif
