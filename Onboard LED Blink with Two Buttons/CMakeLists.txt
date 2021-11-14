# Set minimum required version of CMake
cmake_minimum_required(VERSION 3.12)

# Include build functions from Pico C/C++ SDK
include(pico_sdk_import.cmake)

# Set name of project and programming languages to use (C, C++, ASM)
project(OnboardLEDBlinkTwoButtons C CXX ASM)

# Set standard version to use for C/C++
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Creates a pico-sdk subdirectory in our project for the libraries
pico_sdk_init()

# Tell CMake where to find the executable source file
add_executable(OnboardLEDBlinkTwoButtons main.cpp)

# Create map/bin/hex/uf2 files
pico_add_extra_outputs(OnboardLEDBlinkTwoButtons)

# Link to pico_stdlib (gpio, time, etc. functions)
target_link_libraries(OnboardLEDBlinkTwoButtons pico_stdlib)
