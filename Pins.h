#ifndef __PINS_H
#define __PINS_H

#include "common.h"

struct SPIPins
{
public:
    size_t miso;
    size_t cs;
    size_t sck;
    size_t mosi;
};

#endif
