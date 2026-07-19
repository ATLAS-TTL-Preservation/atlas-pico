#include <atlas/app/BootScreen.hpp>

#include <atlas/assets/AtlasSplash.hpp>

namespace atlas::app
{

BootScreen::BootScreen(
    display::Display& display)
    : m_display(display)
{
}

void BootScreen::Show()
{
    m_display.Clear();

    m_display.DrawImage(
        0,
        0,
        atlas::assets::AtlasSplash);
}

void BootScreen::SetStatus(
    std::string_view status)
{
    constexpr std::uint16_t statusY =
        atlas::assets::AtlasSplash.GetHeight() -
        StatusAreaHeight;

    m_display.DrawImageRegion(
        0,
        statusY,
        atlas::assets::AtlasSplash,
        0,
        statusY,
        atlas::assets::AtlasSplash.GetWidth(),
        StatusAreaHeight);

    m_display.DrawText(
        2,
        statusY + 1,
        status);
}

}