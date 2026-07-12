#pragma once

#include <cstdint>

namespace atlas::graphics
{

struct Glyph
{
    const std::uint8_t* bitmap;

    std::uint16_t offset;

    std::uint8_t width;

    std::uint8_t height;

    std::uint8_t advance;

    std::int8_t xOffset;

    std::int8_t yOffset;
};

}