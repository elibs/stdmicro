#ifndef __STD_MICRO_RP2040_I2C_H
#define __STD_MICRO_RP2040_I2C_H

#include "I2C.h"

#include "hardware/i2c.h"

struct RP2040_I2C_Pins
{
    unsigned int sck;
    unsigned int sda;
};

class RP2040_I2C: public I2C
{
public:
    RP2040_I2C(i2c_inst_t* i2c, RP2040_I2C_Pins pins, uint baudrate);
    virtual ~RP2040_I2C(void);

    int read(unsigned char address, void* destination, unsigned int bytes);
    int write(unsigned char address, const void* source, unsigned int bytes);

    size_t baudrate(void) const override;
    size_t baudrate(size_t baudRate) override;
private:
    i2c_inst_t* mI2c;
    RP2040_I2C_Pins mPins;
    unsigned int mBaudRate;
};

#endif
