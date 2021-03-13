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
    /**
     * Set the format of the SPI interface
     *
     * @param bitsPerTransfer The number of bits to transfer in a single shot.
     * @param cpol True for high clock polarity, false for low
     * @param cpha True for high clock phase, false for low
     * @param msbFirst True for most-significant bit being transferred first,
     *     false for it to be least-significant first.
     */
    virtual void format(size_t bitsPerTransfer, bool cpol, bool cpha, bool msbFirst) = 0;

    /**
     * Write a buffer to the SPI interface
     *
     * @param buffer The buffer to write
     * @param len The number of bytes in the buffer
     * @returns ssize_t The number of bytes actually written. If things went well, this is a positive value.
     */
    virtual ssize_t write(const void* buffer, size_t len) = 0;
    /**
     * Read a buffer to the SPI interface
     *
     * @param txByte The value to send repeatedly on the MOSI line while
     *     reading.
     * @param buffer The buffer to read into
     * @param len The number of bytes to read
     * @returns ssize_t The number of bytes actually read. If things went well,
     *     this is a positive value.
     */
    virtual ssize_t read(unsigned char txByte, void* destination, size_t len) const = 0;
    /**
     * Read and write a buffer to the SPI interface at the same time
     *
     * @param output The buffer to write from
     * @param input The buffer to read into
     * @param len The number of bytes in _each_ buffer
     * @returns ssize_t The number of bytes actually read. If things went well,
     *     this is a positive value.
     */
    virtual ssize_t read_write(const void* output, void* input, size_t len) = 0;
 
    /**
     * Retrieve the baud rate of the interface.
     */
    virtual size_t baudrate(void) const = 0;
    /**
     * Set the baud rate of the interface
     *
     * @returns The baud rate that was actually set, this may differ from the
     *     requested baud rate.
     */
    virtual size_t baudrate(size_t baudRate) = 0;
};

#endif
