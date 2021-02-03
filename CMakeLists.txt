cmake_minimum_required(VERSION 3.12)

include(pico_sdk_import.cmake)

project(eink)

pico_sdk_init()

add_executable(eink e-ink.cpp)

# Pull in our pico_stdlib which pulls in commonly used features
target_link_libraries(eink pico_stdlib hardware_spi hardware_dma hardware_gpio)

pico_add_extra_outputs(eink)
