#include "RP2040_I2C.h"

#include "hardware/gpio.h"

namespace stdmicro::processor::RP2040
{

RP2040_I2C::RP2040_I2C(i2c_inst_t* i2c, stdmicro::I2CPins pins, uint baudrate):
    mI2c(i2c),
    mBaudRate(i2c_init(mI2c, baudrate))
{
    gpio_set_function(pins.sck, GPIO_FUNC_I2C);
    gpio_set_function(pins.sda, GPIO_FUNC_I2C);
}

RP2040_I2C::~RP2040_I2C(void)
{
    i2c_deinit(mI2c);
}

ssize_t RP2040_I2C::read(unsigned char address, void* destination, unsigned int bytes)
{
    return i2c_read_blocking(mI2c, address, (unsigned char*)destination, bytes, false);
}

ssize_t RP2040_I2C::write(unsigned char address, const void* source, unsigned int bytes)
{
    return i2c_write_blocking(mI2c, address, (const unsigned char*)source, bytes, false);
}

size_t RP2040_I2C::baudrate(void) const
{
    return mBaudRate;
}

size_t RP2040_I2C::baudrate(size_t baudRate)
{
    mBaudRate = i2c_set_baudrate(mI2c, baudRate);
    return mBaudRate;
}

} // stdmicro::rpocessor::RP2040
