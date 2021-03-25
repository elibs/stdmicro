#ifndef __STD_MICRO_I2C_H
#define __STD_MICRO_I2C_H

#include "types.h"

struct I2CPins
{
    unsigned int sck;
    unsigned int sda;
};


class I2C
{
public:
    /**
     * Read bytes off of the I2C interface.
     *
     * @param address The I2C address to read from
     * @param destination Where to store the bytes read
     * @param bytes How many bytes to read
     * @returns ssize_t The number of bytes actually read, or a negative value on error
     */
    virtual ssize_t read(unsigned char address, void* destination, unsigned int bytes) = 0;

    /**
     * Write bytes to the I2C interface.
     *
     * @param address The I2C address to write to
     * @param source The data to write
     * @param bytes How many bytes to write
     * @returns ssize_t The number of bytes actually written, or a negative value on error
     */
    virtual ssize_t write(unsigned char address, const void* source, unsigned int bytes) = 0;

    /**
     * @returns The baudrate the I2C interface is running at.
     */
    virtual size_t baudrate(void) const = 0;

    /**
     * Set the baudrate for the I2C interface
     *
     * @param baudRate The baud rate
     * @returns The actual baudrate achieved, which may not be what was requested.
     */
    virtual size_t baudrate(size_t baudRate) = 0;
};

#endif
