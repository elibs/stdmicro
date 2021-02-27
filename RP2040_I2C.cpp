#include "RP2040_I2C.h"

#include "hardware/gpio.h"

RP2040_I2C::RP2040_I2C(i2c_inst_t* i2c, RP2040_I2C_Pins pins, uint baudrate):
    mI2c(i2c),
    mPins(pins),
    mBaudRate(i2c_init(mI2c, baudrate))
{
    gpio_set_function(mPins.sck, GPIO_FUNC_I2C);
    gpio_set_function(mPins.sda, GPIO_FUNC_I2C);
}

RP2040_I2C::~RP2040_I2C(void)
{
    i2c_deinit(mI2c);
}

int RP2040_I2C::read(unsigned char address, void* destination, unsigned int bytes)
{
    return i2c_read_blocking(mI2c, address, (unsigned char*)destination, bytes, false);
}

int RP2040_I2C::write(unsigned char address, const void* source, unsigned int bytes)
{
    return i2c_write_blocking(mI2c, address, (const unsigned char*)source, bytes, false);
}

unsigned int RP2040_I2C::baudrate(void) const
{
    return mBaudRate;
}

void RP2040_I2C::baudrate(unsigned int baudRate)
{
    mBaudRate = i2c_set_baudrate(mI2c, baudRate);
}
