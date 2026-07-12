#pragma once

#include <cstdint>
#include <string_view>

namespace atlas::display
{

class Display
{
public:
    virtual ~Display() = default;

    /// Initializes the display.
    virtual void Init() = 0;

    /// Clears the entire display.
    virtual void Clear() = 0;

    /// Draws a horizontal line.
    virtual void DrawHorizontalLine(
        std::uint16_t x,
        std::uint16_t y,
        std::uint16_t length
    ) = 0;

    /// Draws text at the specified position.
    virtual void DrawText(
        std::uint16_t x,
        std::uint16_t y,
        std::string_view text
    ) = 0;

    /// Returns the display width in pixels.
    [[nodiscard]]
    virtual std::uint16_t GetWidth() const = 0;

    /// Returns the display height in pixels.
    [[nodiscard]]
    virtual std::uint16_t GetHeight() const = 0;
};

} // namespace atlas::display