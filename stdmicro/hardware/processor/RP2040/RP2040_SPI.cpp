#include "RP2040_SPI.h"

#include "pico/stdlib.h"

namespace stdmicro::processor::RP2040
{

RP2040_SPI::RP2040_SPI(spi_inst_t* spi, stdmicro::SPIPins pins, size_t baudRate):
    mSpi(spi),
    mBaudRate(baudRate),
    mCs(pins.cs, stdmicro::GPIO::SIO, stdmicro::GPIO::Output),
    mSck(pins.sck, stdmicro::GPIO::SPI, stdmicro::GPIO::Output),
    mMiso(pins.miso, stdmicro::GPIO::SPI, stdmicro::GPIO::Input),
    mMosi(pins.mosi, stdmicro::GPIO::SPI, stdmicro::GPIO::Output)
{
    spi_init(mSpi, baudRate);
}

RP2040_SPI::~RP2040_SPI(void)
{
    spi_deinit(mSpi);
}

void RP2040_SPI::format(size_t bitsPerTransfer, bool cpol, bool cpha, bool msbFirst)
{
    spi_set_format(mSpi,
        bitsPerTransfer,
        cpol ? SPI_CPOL_1 : SPI_CPOL_0,
        cpha ? SPI_CPHA_1 : SPI_CPHA_0,
        msbFirst ? SPI_MSB_FIRST : SPI_LSB_FIRST
    );
}

ssize_t RP2040_SPI::write(const void* buffer, size_t len)
{
    mCs.put(false);
    ssize_t ret = spi_write_blocking(mSpi, (const uint8_t*)buffer, len);
    mCs.put(true);

    return ret;
}

ssize_t RP2040_SPI::read(unsigned char txByte, void* destination, size_t len) const
{
    return spi_read_blocking(mSpi, txByte, (uint8_t*)destination, len);
}

ssize_t RP2040_SPI::read_write(const void* output, void* input, size_t len)
{
    mCs.put(true);
    ssize_t ret = spi_write_read_blocking(mSpi, (const uint8_t*)output, (uint8_t*)input, len);
    mCs.put(false);

    return ret;
}

size_t RP2040_SPI::baudrate(void) const
{
    return mBaudRate;
}

size_t RP2040_SPI::baudrate(size_t baudRate)
{
    mBaudRate = spi_set_baudrate(mSpi, baudRate);
    return mBaudRate;
}

} // stdmicro::processor::RP2040
