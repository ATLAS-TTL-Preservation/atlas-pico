#pragma once

#include <cstdint>
#include <cstddef>

#include <atlas/storage/sd/Command.hpp>
#include <atlas/storage/sd/Response.hpp>

namespace atlas::storage::sd
{

class SDCard
{
public:
    SDCard();

    bool Initialize();

private:

    bool SendCommand(
    Command command,
    std::uint32_t argument,
    std::uint8_t crc,
    std::uint8_t& response,
    std::uint8_t* data = nullptr,
    std::size_t length = 0);

    void Select();

    void Deselect();

    std::uint8_t Transfer(std::uint8_t data);
};

}