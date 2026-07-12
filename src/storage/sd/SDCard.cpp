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
    std::uint8_t& response,
    std::uint8_t* data,
    std::size_t length)
{
    Select();

    Transfer(0x40 | static_cast<std::uint8_t>(command));

    Transfer(static_cast<std::uint8_t>(argument >> 24));
    Transfer(static_cast<std::uint8_t>(argument >> 16));
    Transfer(static_cast<std::uint8_t>(argument >> 8));
    Transfer(static_cast<std::uint8_t>(argument));

    Transfer(crc);

    for (std::uint8_t i = 0; i < 10; ++i)
    {
        response = Transfer(DummyByte);

        if ((response & 0x80) == 0)
        {
            for (std::size_t j = 0; j < length; ++j)
            {
                data[j] = Transfer(DummyByte);
            }

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

    std::uint8_t cmd8Response[4];

    if (!SendCommand(
            Command::Cmd8,
            0x000001AA,
            0x87,
            response,
            cmd8Response,
            4))
    {
        return false;
    }

    if (response != 0x01)
    {
        return false;
    }

    if (cmd8Response[2] != 0x01 || cmd8Response[3] != 0xAA)
    {
        return false;
    }

    while (true)
    {
        if (!SendCommand(
                Command::Cmd55,
                0x00000000,
                0x01,
                response))
        {
            return false;
        }

        if (!SendCommand(
                Command::Acmd41,
                0x40000000,
                0x01,
                response))
        {
            return false;
        }

        if (response == 0x00)
        {
            break;
        }
    }

    std::uint8_t ocr[4];

    if (!SendCommand(
            Command::Cmd58,
            0x00000000,
            0x01,
            response,
            ocr,
            4))
    {
        return false;
    }

    if (response != 0x00)
    {
        return false;
    }

    spi_set_baudrate(spi0, 25'000'000);

    return true;
}

}