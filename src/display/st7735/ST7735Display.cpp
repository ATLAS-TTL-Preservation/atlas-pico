#include <atlas/display/st7735/ST7735Display.hpp>

#include <atlas/display/st7735/Commands.hpp>

#include <atlas/graphics/fonts/IBMVGA.hpp>

#include <atlas/hardware/Pinout.hpp>

#include <hardware/gpio.h>
#include <hardware/spi.h>
#include <pico/stdlib.h>

#include <atlas/system/System.hpp>

using namespace std::chrono_literals;
using atlas::system::System;

namespace atlas::display::st7735
{

void ST7735Display::Init()
{
    InitializeSpi();
    InitializePins();

    Reset();

    InitializeController();
    SetRotation(Rotation::Landscape);

    Clear();
    WriteCommand(Command::DisplayOn);

    System::Delay(100ms);
}

void ST7735Display::InitializeSpi()
{
    spi_init(spi1, 40000000);

    gpio_set_function(
        atlas::hardware::Pinout::Display::Sck,
        GPIO_FUNC_SPI);

    gpio_set_function(
        atlas::hardware::Pinout::Display::Mosi,
        GPIO_FUNC_SPI);
}

void ST7735Display::InitializePins()
{
    gpio_init(atlas::hardware::Pinout::Display::Cs);
    gpio_set_dir(atlas::hardware::Pinout::Display::Cs, GPIO_OUT);
    gpio_put(atlas::hardware::Pinout::Display::Cs, true);

    gpio_init(atlas::hardware::Pinout::Display::Dc);
    gpio_set_dir(atlas::hardware::Pinout::Display::Dc, GPIO_OUT);
    gpio_put(atlas::hardware::Pinout::Display::Dc, true);

    gpio_init(atlas::hardware::Pinout::Display::Rst);
    gpio_set_dir(atlas::hardware::Pinout::Display::Rst, GPIO_OUT);
    gpio_put(atlas::hardware::Pinout::Display::Rst, true);
}

void ST7735Display::Reset()
{
    gpio_put(atlas::hardware::Pinout::Display::Rst, false);
    System::Delay(10ms);

    gpio_put(atlas::hardware::Pinout::Display::Rst, true);
    System::Delay(150ms);
}

void ST7735Display::InitializeController()
{
    // Software Reset
    WriteCommand(Command::SoftwareReset);
    System::Delay(150ms);

    // Sleep Out
    WriteCommand(Command::SleepOut);
    System::Delay(150ms);

    WriteCommand(Command::InterfacePixelFormat);
    WriteData(0x05);

    WriteCommand(Command::MemoryAccessControl);
    WriteData(0xC8);
}

void ST7735Display::SetRotation(Rotation rotation)
{
    m_rotation = rotation;

    WriteCommand(Command::MemoryAccessControl);

    switch (rotation)
    {
        case Rotation::Portrait:
            WriteData(0x00);
            m_width = 128;
            m_height = 160;
            break;

        case Rotation::Landscape:
            WriteData(0x60);
            m_width = 160;
            m_height = 128;
            break;

        case Rotation::PortraitFlipped:
            WriteData(0xC0);
            m_width = 128;
            m_height = 160;
            break;

        case Rotation::LandscapeFlipped:
            WriteData(0xA0);
            m_width = 160;
            m_height = 128;
            break;
    }
}

void ST7735Display::WriteCommand(Command command)
{
    gpio_put(atlas::hardware::Pinout::Display::Dc, false);
    gpio_put(atlas::hardware::Pinout::Display::Cs, false);

    const auto value = static_cast<std::uint8_t>(command);
    spi_write_blocking(spi1, &value, 1);

    gpio_put(atlas::hardware::Pinout::Display::Cs, true);
}

void ST7735Display::WriteData(std::uint8_t data)
{
    gpio_put(atlas::hardware::Pinout::Display::Dc, true);
    gpio_put(atlas::hardware::Pinout::Display::Cs, false);

    spi_write_blocking(spi1, &data, 1);

    gpio_put(atlas::hardware::Pinout::Display::Cs, true);
}

void ST7735Display::WriteData(const std::uint8_t* data, std::size_t length)
{
    gpio_put(atlas::hardware::Pinout::Display::Dc, true);
    gpio_put(atlas::hardware::Pinout::Display::Cs, false);

    spi_write_blocking(spi1, data, length);

    gpio_put(atlas::hardware::Pinout::Display::Cs, true);
}

void ST7735Display::DrawCharacter(
    std::uint16_t x,
    std::uint16_t y,
    char character)
{
    static atlas::graphics::fonts::IBMVGA font;

    const auto& glyph = font.GetGlyph(character);

    if (glyph.bitmap == nullptr)
    {
        return;
    }

    const std::uint8_t* bitmap = glyph.bitmap + glyph.offset;

    std::uint8_t bit = 0;
    std::uint8_t bits = 0;

    for (std::uint8_t yy = 0; yy < glyph.height; yy++)
    {
        for (std::uint8_t xx = 0; xx < glyph.width; xx++)
        {
            if ((bit++ & 7) == 0)
            {
                bits = *bitmap++;
            }

            if (bits & 0x80)
            {
                DrawPixel(
                    x + glyph.xOffset + xx,
                    y + glyph.yOffset + yy);
            }

            bits <<= 1;
        }
    }
}

void ST7735Display::SetAddressWindow(
    std::uint16_t x0,
    std::uint16_t y0,
    std::uint16_t x1,
    std::uint16_t y1)
{
    WriteCommand(Command::ColumnAddressSet);

    WriteData(static_cast<std::uint8_t>(x0 >> 8));
    WriteData(static_cast<std::uint8_t>(x0));

    WriteData(static_cast<std::uint8_t>(x1 >> 8));
    WriteData(static_cast<std::uint8_t>(x1));

    WriteCommand(Command::RowAddressSet);

    WriteData(static_cast<std::uint8_t>(y0 >> 8));
    WriteData(static_cast<std::uint8_t>(y0));

    WriteData(static_cast<std::uint8_t>(y1 >> 8));
    WriteData(static_cast<std::uint8_t>(y1));

    WriteCommand(Command::MemoryWrite);
}

void ST7735Display::Clear()
{
    SetAddressWindow(
        0,
        0,
        m_width - 1,
        m_height - 1);

    constexpr std::uint8_t pixel[] =
    {
        0x00,
        0x00
    };

    for (std::uint32_t i = 0; i < m_width * m_height; ++i)
    {
        WriteData(pixel, sizeof(pixel));
    }
}

void ST7735Display::DrawPixel(
    std::uint16_t x,
    std::uint16_t y)
{
    SetAddressWindow(x, y, x, y);

    constexpr std::uint8_t pixel[] =
    {
        0xFF,
        0xFF
    };

    WriteData(pixel, sizeof(pixel));
}

void ST7735Display::DrawHorizontalLine(
    std::uint16_t x,
    std::uint16_t y,
    std::uint16_t length)
{
    SetAddressWindow(
        x,
        y,
        x + length - 1,
        y);

    constexpr std::uint8_t pixel[] =
    {
        0xFF,
        0xFF
    };

    for (std::uint16_t i = 0; i < length; ++i)
    {
        WriteData(pixel, sizeof(pixel));
    }
}

void ST7735Display::DrawVerticalLine(
    std::uint16_t x,
    std::uint16_t y,
    std::uint16_t length)
{
    SetAddressWindow(
        x,
        y,
        x,
        y + length - 1);

    constexpr std::uint8_t pixel[] =
    {
        0xFF,
        0xFF
    };

    for (std::uint16_t i = 0; i < length; ++i)
    {
        WriteData(pixel, sizeof(pixel));
    }
}

void ST7735Display::DrawText(
    std::uint16_t x,
    std::uint16_t y,
    std::string_view text)
{
    static atlas::graphics::fonts::IBMVGA font;

    for (char c : text)
    {
        DrawCharacter(x, y, c);

        x += font.GetGlyph(c).advance;
    }
}

std::uint16_t ST7735Display::GetWidth() const
{
    return m_width;
}

std::uint16_t ST7735Display::GetHeight() const
{
    return m_height;
}

} // namespace atlas::display::st7735