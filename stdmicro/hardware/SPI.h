#ifndef __STD_MICRO_SPI_H
#define __STD_MICRO_SPI_H

#include "types.h"

struct SPIPins
{
public:
    size_t cs;
    size_t miso;
    size_t mosi;
    size_t sck;
};

class SPI
{
public:
    virtual void format(size_t bitsPerTransfer, bool cpol, bool cpha, bool msbFirst) = 0;

    virtual ssize_t write(const void* buffer, size_t len) = 0;
    virtual ssize_t read(unsigned char txByte, void* destination, size_t len) const = 0;
    virtual ssize_t read_write(const void* output, void* input, size_t len) = 0;
 
    virtual size_t baudrate(void) const = 0;
    virtual size_t baudrate(size_t baudRate) = 0;
};

#endif
