cmake_minimum_required(VERSION 3.12)

include(pico_sdk_import.cmake)

project(eink)

pico_sdk_init()

add_definitions(
    -DPROCESSOR=PROCESSOR_RP2040
)

add_compile_options(
    -Wall
    -Werror
    # -Wextra   ### NOTE: These can't be enabled due to pico's sdk having errors at that point. They will eventually be
    # -pedantic ###       added back in, once pico-sdk is part of stdmicro.
)

add_executable(eink
    BezierCurve.cpp
    Canvas.cpp
    DejaVuSans.cpp
    DejaVuSerif.cpp
    EmBox.cpp
    FontSize.cpp
    Led.cpp
    Path.cpp
    stdmicro/hardware/RTC/ds3231/DS3231.cpp
    stdmicro/hardware/display/eink/gd7965/GD7965.cpp
    stdmicro/hardware/processor/rp2040/RP2040_GPIO.cpp
    stdmicro/hardware/processor/rp2040/RP2040_I2C.cpp
    stdmicro/hardware/processor/rp2040/RP2040_SPI.cpp
    e-ink.cpp
)

include_directories(
    stdmicro
    stdmicro/hardware
    stdmicro/hardware/display/eink
    stdmicro/hardware/processor
)

# Pull in our pico_stdlib which pulls in commonly used features
target_link_libraries(eink
    pico_stdlib
    hardware_spi
    hardware_gpio
    hardware_i2c
)

pico_add_extra_outputs(eink)
