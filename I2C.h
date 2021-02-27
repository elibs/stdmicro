#ifndef __STD_MICRO_I2C_H
#define __STD_MICRO_I2C_H

class I2C
{
public:
    virtual int read(unsigned char address, void* destination, unsigned int bytes) = 0;
    virtual int write(unsigned char address, const void* source, unsigned int bytes) = 0;

    virtual unsigned int baudrate(void) const = 0;
    virtual void baudrate(unsigned int baudRate) = 0;
};

#endif
