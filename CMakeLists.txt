cmake_minimum_required(VERSION 3.16)

include(pico_sdk_import.cmake)

project(atlas_pico C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)

pico_sdk_init()