#include <atlas/storage/sd/SPIBus.hpp>

#include <atlas/hardware/Pinout.hpp>

#include <hardware/gpio.h>
#include <hardware/spi.h>

namespace
{
    constexpr std::uint32_t InitBaudrate = 400000;
    constexpr std::uint32_t WorkBaudrate = 12500000;
}

namespace atlas::storage::sd
{

SPIBus::SPIBus() = default;

void SPIBus::Initialize()
{
    spi_init(spi0, InitBaudrate);

    spi_set_format(
        spi0,
        8,
        SPI_CPOL_0,
        SPI_CPHA_0,
        SPI_MSB_FIRST);

    gpio_set_function(
        atlas::hardware::Pinout::SD::Clock,
        GPIO_FUNC_SPI);

    gpio_set_function(
        atlas::hardware::Pinout::SD::Mosi,
        GPIO_FUNC_SPI);

    gpio_set_function(
        atlas::hardware::Pinout::SD::Miso,
        GPIO_FUNC_SPI);

    gpio_init(
        atlas::hardware::Pinout::SD::ChipSelect);

    gpio_set_dir(
        atlas::hardware::Pinout::SD::ChipSelect,
        GPIO_OUT);

    Deselect();

    for (int i = 0; i < 10; ++i)
    {
        Transfer(DummyByte);
    }
}

void SPIBus::SetLowSpeed()
{
    spi_set_baudrate(spi0, InitBaudrate);
}

void SPIBus::SetHighSpeed()
{
    spi_set_baudrate(spi0, WorkBaudrate);
}

void SPIBus::Select()
{
    gpio_put(
        atlas::hardware::Pinout::SD::ChipSelect,
        false);
}

void SPIBus::Deselect()
{
    gpio_put(
        atlas::hardware::Pinout::SD::ChipSelect,
        true);

    Transfer(DummyByte);
}

std::uint8_t SPIBus::Transfer(std::uint8_t data)
{
    std::uint8_t rx;

    spi_write_read_blocking(
        spi0,
        &data,
        &rx,
        1);

    return rx;
}

void SPIBus::Transfer(
    const std::uint8_t* tx,
    std::uint8_t* rx,
    std::size_t length)
{
    spi_write_read_blocking(
        spi0,
        tx,
        rx,
        length);
}

bool SPIBus::WaitReady()
{
    for (std::uint32_t i = 0; i < 500000; ++i)
    {
        if (Transfer(DummyByte) == DummyByte)
        {
            return true;
        }
    }

    return false;
}

}