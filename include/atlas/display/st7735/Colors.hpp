#pragma once

#include <cstdint>

namespace atlas::display::st7735
{

enum class Color : std::uint16_t
{
    Black   = 0x0000,
    Blue    = 0x001F,
    Red     = 0xF800,
    Green   = 0x07E0,
    Cyan    = 0x07FF,
    Magenta = 0xF81F,
    Yellow  = 0xFFE0,
    White   = 0xFFFF
};

} // namespace atlas::display::st7735