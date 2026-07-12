#pragma once

#include <cstdint>

namespace atlas::display::st7735
{

enum class Rotation : std::uint8_t
{
    Portrait = 0,
    Landscape = 1,
    PortraitFlipped = 2,
    LandscapeFlipped = 3
};

} // namespace atlas::display::st7735