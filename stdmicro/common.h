#ifndef __STD_MICRO_COMMON_H
#define __STD_MICRO_COMMON_H

#include "types.h"

#define PROCESSOR_MOCKED 0
#define PROCESSOR_RP2040 RP2040

#ifndef PROCESSOR
#define PROCESSOR PROCESSOR_MOCKED
#endif

#if (PROCESSOR == PROCESSOR_RP2040)
    #include "processor/RP2040/RP2040.h"
#endif

namespace stdmicro
{
    namespace mcu = ::stdmicro::processor::PROCESSOR;
} // stdmicro

#endif
