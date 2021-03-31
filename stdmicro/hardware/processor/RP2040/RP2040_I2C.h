#ifndef __STD_MICRO_RP2040_I2C_H
#define __STD_MICRO_RP2040_I2C_H

#include "I2C.h"

#include "hardware/i2c.h"

namespace stdmicro::processor::RP2040
{

class RP2040_I2C: public stdmicro::I2C
{
public:
    RP2040_I2C(i2c_inst_t* i2c, stdmicro::I2CPins pins, uint baudrate);
    virtual ~RP2040_I2C(void);

    ssize_t read(unsigned char address, void* destination, unsigned int bytes);
    ssize_t write(unsigned char address, const void* source, unsigned int bytes);

    size_t baudrate(void) const override;
    size_t baudrate(size_t baudRate) override;
private:
    i2c_inst_t* mI2c;
    size_t mBaudRate;
};

} // stdmicro::processor::RP2040

#endif
