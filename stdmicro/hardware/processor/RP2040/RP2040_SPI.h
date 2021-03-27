#ifndef __STD_MICRO_RP2040_SPI_H
#define __STD_MICRO_RP2040_SPI_H

#include "types.h"
#include "SPI.h"
#include "RP2040_GPIO.h"

#include "hardware/spi.h"

namespace stdmicro::processor::RP2040
{

class RP2040_SPI: public SPI
{
public:
    RP2040_SPI(spi_inst_t* spi, stdmicro::SPIPins pins, size_t buadRate);
    virtual ~RP2040_SPI(void);

    void format(size_t bitsPerTransfer, bool cpol, bool cpha, bool msbFirst) override;

    ssize_t write(const void* buffer, size_t len) override;
    ssize_t read(unsigned char txByte, void* destination, size_t len) const override;
    ssize_t read_write(const void* output, void* input, size_t len) override;

    virtual size_t baudrate(void) const override;
    virtual size_t baudrate(size_t baudRate) override;

private:
    spi_inst_t* mSpi;
    size_t mBaudRate;
    RP2040_GPIO mCs;
    RP2040_GPIO mSck;
    RP2040_GPIO mMiso;
    RP2040_GPIO mMosi;
};

} // stdmicro::processor::RP2040

#endif
