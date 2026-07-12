#include <atlas/display/ST7735Display.hpp>

namespace atlas::display
{

void ST7735Display::Init()
{
}

void ST7735Display::Clear()
{
}

void ST7735Display::DrawHorizontalLine(
    std::uint16_t,
    std::uint16_t,
    std::uint16_t)
{
}

void ST7735Display::DrawText(
    std::uint16_t,
    std::uint16_t,
    std::string_view)
{
}

std::uint16_t ST7735Display::GetWidth() const
{
    return Width;
}

std::uint16_t ST7735Display::GetHeight() const
{
    return Height;
}

} // namespace atlas::display