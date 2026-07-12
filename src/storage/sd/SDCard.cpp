#include <atlas/storage/sd/SDCard.hpp>

#include <atlas/hardware/Pinout.hpp>

#include <hardware/gpio.h>
#include <hardware/spi.h>

namespace
{
    constexpr std::uint32_t SpiBaudrate = 400'000;
    constexpr std::uint8_t DummyByte = 0xFF;
}

namespace atlas::storage::sd
{

SDCard::SDCard() = default;

void SDCard::Select()
{
    gpio_put(
        atlas::hardware::Pinout::SD::ChipSelect,
        false);
}
void SDCard::Deselect()
{
    gpio_put(
        atlas::hardware::Pinout::SD::ChipSelect,
        true);
}

bool SDCard::Initialize()
{
    spi_init(spi0, SpiBaudrate);

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

    return true;
}

std::uint8_t SDCard::Transfer(std::uint8_t data)
{
    std::uint8_t received;

    spi_write_read_blocking(
        spi0,
        &data,
        &received,
        1);

    return received;
}

}