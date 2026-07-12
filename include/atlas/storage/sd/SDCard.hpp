#pragma once

#include <cstdint>
#include <cstddef>

#include <atlas/storage/sd/Command.hpp>
#include <atlas/storage/sd/Response.hpp>
#include <atlas/storage/sd/ReadResult.hpp>
#include <atlas/storage/sd/SPIBus.hpp>

namespace atlas::storage::sd
{

class SDCard
{
public:
    SDCard();

    bool Initialize();

    bool ReadBlock(
        std::uint32_t block,
        std::uint8_t* buffer);

    ReadResult GetLastReadResult() const;

    std::uint8_t GetLastResponse() const;

private:
    bool SendCommand(
        Command command,
        std::uint32_t argument,
        std::uint8_t crc,
        Response expectedResponse,
        std::uint8_t* response = nullptr,
        std::size_t responseLength = 0);

    bool WaitResponse(
        std::uint8_t& response);

    bool WaitDataToken(std::uint8_t& token);

private:
    SPIBus m_spi;

    ReadResult m_lastReadResult = ReadResult::Success;

    std::uint8_t m_lastResponse = 0xFF;

    bool m_highCapacity = false;
};

}