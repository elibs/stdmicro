cmake_minimum_required(VERSION 3.12)

include(pico_sdk_import.cmake)

project(eink)

pico_sdk_init()

add_definitions(
    -DMICROCONTROLLER=MICROCONTROLLER_RP2040
)

add_executable(eink
    BezierCurve.cpp
    Canvas.cpp
    DS3231.cpp
    DejaVuSans.cpp
    DejaVuSerif.cpp
    EmBox.cpp
    FontSize.cpp
    GD7965.cpp
    Led.cpp
    Path.cpp
    RP2040_GPIO.cpp
    RP2040_I2C.cpp
    RP2040_SPI.cpp
    e-ink.cpp
)

# Pull in our pico_stdlib which pulls in commonly used features
target_link_libraries(
    eink
    pico_stdlib
    hardware_spi
    hardware_gpio
    hardware_i2c
)

pico_add_extra_outputs(eink)
