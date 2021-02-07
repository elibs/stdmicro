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

struct DisplayPins
{
public:
    SPIPins spi;
    size_t dc;
    size_t busy;
    size_t reset;
};

#endif
