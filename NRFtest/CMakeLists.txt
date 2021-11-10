cmake_minimum_required(VERSION 3.12)

include (pico_sdk_import.cmake)

set(CMAKE_CXX_STANDARD 17)

project(nrf)

pico_sdk_init()

add_executable(nrf
main.cpp
NRF24.cpp
)

target_link_libraries(nrf
pico_stdlib
hardware_spi
)

pico_add_extra_outputs(nrf)