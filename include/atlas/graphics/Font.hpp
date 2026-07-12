#pragma once

#include <atlas/graphics/Glyph.hpp>

#include <cstdint>

namespace atlas::graphics
{

class Font
{
public:
    virtual ~Font() = default;

    [[nodiscard]]
    virtual const Glyph& GetGlyph(char character) const = 0;

    [[nodiscard]]
    virtual std::uint8_t GetHeight() const = 0;
};

}