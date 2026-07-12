#pragma once

#include <cstdint>

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
        std::uint8_t& response);

    void Select();

    void Deselect();

    std::uint8_t Transfer(std::uint8_t data);
};

}