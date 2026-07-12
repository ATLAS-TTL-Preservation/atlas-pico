#pragma once

#include <atlas/graphics/Font.hpp>

namespace atlas::graphics::fonts
{

class IBMVGA final : public Font
{
public:
    [[nodiscard]]
    const Glyph& GetGlyph(char character) const override;

    [[nodiscard]]
    std::uint8_t GetHeight() const override;
};

}