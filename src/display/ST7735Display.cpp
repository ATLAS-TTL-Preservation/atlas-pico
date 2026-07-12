#include <atlas/display/ST7735Display.hpp>

#include <atlas/hardware/Pinout.hpp>

#include <pico/stdlib.h>

#include <hardware/gpio.h>
#include <hardware/spi.h>

namespace atlas::display
{

void ST7735Display::Init()
{
    InitializeSpi();
    InitializePins();

    Reset();
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

void ST7735Display::WriteCommand(std::uint8_t command)
{
    gpio_put(atlas::hardware::Pinout::Display::Dc, false);
    gpio_put(atlas::hardware::Pinout::Display::Cs, false);

    spi_write_blocking(spi1, &command, 1);

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