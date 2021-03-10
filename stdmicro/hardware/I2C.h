#ifndef __STD_MICRO_I2C_H
#define __STD_MICRO_I2C_H

#include "types.h"

class I2C
{
public:
    virtual int read(unsigned char address, void* destination, unsigned int bytes) = 0;
    virtual int write(unsigned char address, const void* source, unsigned int bytes) = 0;

    virtual size_t baudrate(void) const = 0;
    virtual size_t baudrate(size_t baudRate) = 0;
};

#endif
