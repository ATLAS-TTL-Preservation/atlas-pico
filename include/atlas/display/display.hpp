#pragma once

#include <cstdint>
#include <string_view>

#include <atlas/graphics/Image.hpp>

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

    /// Draws a Pixel
    virtual void DrawPixel(
        std::uint16_t x,
        std::uint16_t y) = 0;

    /// Draws a vertical line
    virtual void DrawVerticalLine(
        std::uint16_t x,
        std::uint16_t y,
        std::uint16_t length) = 0;

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

    /// Draws an image at the specified position.
    virtual void DrawImage(
        std::uint16_t x,
        std::uint16_t y,
        const atlas::graphics::Image& image
    ) = 0;

    virtual void DrawImageRegion(
        std::uint16_t dstX,
        std::uint16_t dstY,
        const atlas::graphics::Image& image,
        std::uint16_t srcX,
        std::uint16_t srcY,
        std::uint16_t width,
        std::uint16_t height) = 0;

    /// Returns the display width in pixels.
    [[nodiscard]]
    virtual std::uint16_t GetWidth() const = 0;

    /// Returns the display height in pixels.
    [[nodiscard]]
    virtual std::uint16_t GetHeight() const = 0;
};

} // namespace atlas::display