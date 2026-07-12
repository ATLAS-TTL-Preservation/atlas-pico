#include <atlas/display/st7735/ST7735Display.hpp>

#include <atlas/display/st7735/Commands.hpp>

#include <atlas/hardware/Pinout.hpp>

#include <hardware/gpio.h>
#include <hardware/spi.h>
#include <pico/stdlib.h>

namespace atlas::display::st7735
{

void ST7735Display::Init()
{
    InitializeSpi();
    InitializePins();

    Reset();

    InitializeController();
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
    sleep_ms(10);

    gpio_put(atlas::hardware::Pinout::Display::Rst, true);
    sleep_ms(150);
}

void ST7735Display::InitializeController()
{
    // Software Reset
    WriteCommand(Command::SoftwareReset);
    sleep_ms(150);

    // Sleep Out
    WriteCommand(Command::SleepOut);
    sleep_ms(150);

    WriteCommand(Command::InterfacePixelFormat);
    WriteData(0x05);

    WriteCommand(Command::MemoryAccessControl);
    WriteData(0xC8);

    WriteCommand(Command::DisplayOn);

    sleep_ms(100);
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
        Width - 1,
        Height - 1);

    constexpr std::uint8_t pixel[] =
    {
        0x00,
        0x00
    };

    for (std::uint32_t i = 0; i < Width * Height; ++i)
    {
        WriteData(pixel, sizeof(pixel));
    }
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

} // namespace atlas::display::st7735