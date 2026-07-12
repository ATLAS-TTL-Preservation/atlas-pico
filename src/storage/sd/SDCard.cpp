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

bool SDCard::SendCommand(
    Command command,
    std::uint32_t argument,
    std::uint8_t crc,
    std::uint8_t& response)
{
    Select();

    Transfer(0x40 | static_cast<std::uint8_t>(command));

    Transfer(argument >> 24);
    Transfer(argument >> 16);
    Transfer(argument >> 8);
    Transfer(argument);

    Transfer(crc);

    for (std::uint8_t i = 0; i < 10; ++i)
    {
        response = Transfer(DummyByte);

        if ((response & 0x80) == 0)
        {
            Deselect();
            return true;
        }
    }

    Deselect();

    return false;
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

    // SD specification requires at least 74 clock cycles
    // with CS high before the first command.
    for (int i = 0; i < 10; ++i)
    {
        Transfer(DummyByte);
    }

    std::uint8_t response = 0xFF;

    if (!SendCommand(
            Command::Cmd0,
            0x00000000,
            0x95,
            response))
    {
        return false;
    }

    if (response != 0x01)
    {
        return false;
    }

    return true;
}

}