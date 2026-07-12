cmake_minimum_required(VERSION 3.16)

set(PICO_BOARD pico2 CACHE STRING "Board type")

include(pico_sdk_import.cmake)

project(atlas_pico C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)

pico_sdk_init()

add_executable(atlas-pico
    src/main.cpp
    src/app/Application.cpp
)

target_include_directories(atlas-pico
    PRIVATE
        include
)

target_link_libraries(atlas-pico
    pico_stdlib
)

pico_add_extra_outputs(atlas-pico)