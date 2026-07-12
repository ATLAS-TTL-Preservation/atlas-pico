#include <atlas/storage/sd/SDCard.hpp>

namespace
{
    constexpr std::uint8_t DataToken = 0xFE;
}

namespace atlas::storage::sd
{

SDCard::SDCard() = default;

bool SDCard::Initialize()
{
    m_spi.Initialize();
    m_spi.SetLowSpeed();

    std::uint8_t response[4];

    // CMD0
    if (!SendCommand(
            Command::Cmd0,
            0,
            0x95,
            Response::Idle))
    {
        return false;
    }

    // CMD8
    if (!SendCommand(
            Command::Cmd8,
            0x000001AA,
            0x87,
            Response::Idle,
            response,
            4))
    {
        return false;
    }

    if (response[2] != 0x01 ||
        response[3] != 0xAA)
    {
        return false;
    }

    // ACMD41
    while (true)
    {
        if (!SendCommand(
                Command::Cmd55,
                0,
                0xFF,
                Response::Idle))
        {
            return false;
        }

        if (SendCommand(
                Command::Acmd41,
                0x40000000,
                0xFF,
                Response::Ready))
        {
            break;
        }
    }

    // CMD58
    if (!SendCommand(
            Command::Cmd58,
            0,
            0xFF,
            Response::Ready,
            response,
            4))
    {
        return false;
    }

    m_highCapacity = (response[0] & 0x40) != 0;

    m_spi.SetHighSpeed();

    return true;
}

bool SDCard::ReadBlock(
    std::uint32_t block,
    std::uint8_t* buffer)
{
    m_lastReadResult = ReadResult::Success;
    m_lastResponse = 0xFF;

    if (!m_highCapacity)
    {
        block <<= 9;
    }

    if (!m_spi.WaitReady())
    {
        m_lastReadResult = ReadResult::CommandTimeout;
        return false;
    }

    m_spi.Select();

    m_spi.Transfer(
        0x40 | static_cast<std::uint8_t>(Command::Cmd17));

    m_spi.Transfer(
        static_cast<std::uint8_t>(block >> 24));

    m_spi.Transfer(
        static_cast<std::uint8_t>(block >> 16));

    m_spi.Transfer(
        static_cast<std::uint8_t>(block >> 8));

    m_spi.Transfer(
        static_cast<std::uint8_t>(block));

    m_spi.Transfer(0xFF);

    std::uint8_t response;

    if (!WaitResponse(response))
    {
        m_lastReadResult = ReadResult::CommandTimeout;
        m_spi.Deselect();
        return false;
    }

    if (response != 0x00)
    {
        m_lastReadResult = ReadResult::InvalidResponse;
        m_lastResponse = response;
        m_spi.Deselect();
        return false;
    }

    std::uint8_t token;

    if (!WaitDataToken(token))
    {
        m_lastReadResult = ReadResult::TokenTimeout;
        m_spi.Deselect();
        return false;
    }

    if (token != 0xFE)
    {
        m_lastReadResult = ReadResult::InvalidDataToken;
        m_lastResponse = token;
        m_spi.Deselect();
        return false;
    }

    for (std::size_t i = 0; i < 512; ++i)
    {
        buffer[i] = m_spi.Transfer(0xFF);
    }

    // CRC
    m_spi.Transfer(0xFF);
    m_spi.Transfer(0xFF);

    m_spi.Deselect();

    return true;
}

bool SDCard::WriteBlock(
    std::uint32_t block,
    const std::uint8_t* buffer)
{
    if (!m_highCapacity)
    {
        block <<= 9;
    }

    if (!m_spi.WaitReady())
    {
        return false;
    }

    m_spi.Select();

    m_spi.Transfer(
        0x40 | static_cast<std::uint8_t>(Command::Cmd24));

    m_spi.Transfer(static_cast<std::uint8_t>(block >> 24));
    m_spi.Transfer(static_cast<std::uint8_t>(block >> 16));
    m_spi.Transfer(static_cast<std::uint8_t>(block >> 8));
    m_spi.Transfer(static_cast<std::uint8_t>(block));

    m_spi.Transfer(0xFF);

    std::uint8_t response;

    if (!WaitResponse(response))
    {
        m_spi.Deselect();
        return false;
    }

    if (response != 0x00)
    {
        m_spi.Deselect();
        return false;
    }

    m_spi.Transfer(DataToken);

    for (std::size_t i = 0; i < 512; ++i)
    {
        m_spi.Transfer(buffer[i]);
    }

    // Dummy CRC
    m_spi.Transfer(0xFF);
    m_spi.Transfer(0xFF);

    const std::uint8_t dataResponse =
        m_spi.Transfer(0xFF);

    if ((dataResponse & 0x1F) != 0x05)
    {
        m_spi.Deselect();
        return false;
    }

    if (!m_spi.WaitReady())
    {
        m_spi.Deselect();
        return false;
    }

    m_spi.Deselect();

    return true;
}

bool SDCard::SendCommand(
    Command command,
    std::uint32_t argument,
    std::uint8_t crc,
    Response expectedResponse,
    std::uint8_t* response,
    std::size_t responseLength)
{
    if (!m_spi.WaitReady())
    {
        return false;
    }

    m_spi.Select();

    m_spi.Transfer(
        0x40 | static_cast<std::uint8_t>(command));

    m_spi.Transfer(
        static_cast<std::uint8_t>(argument >> 24));

    m_spi.Transfer(
        static_cast<std::uint8_t>(argument >> 16));

    m_spi.Transfer(
        static_cast<std::uint8_t>(argument >> 8));

    m_spi.Transfer(
        static_cast<std::uint8_t>(argument));

    m_spi.Transfer(crc);

    std::uint8_t r1;

    if (!WaitResponse(r1))
    {
        m_spi.Deselect();
        return false;
    }

    if (response != nullptr)
    {
        for (std::size_t i = 0; i < responseLength; ++i)
        {
            response[i] = m_spi.Transfer(0xFF);
        }
    }

    if (r1 != static_cast<std::uint8_t>(expectedResponse))
    {
        m_spi.Deselect();
        return false;
    }

    m_spi.Deselect();

    return true;
}

bool SDCard::WaitResponse(
    std::uint8_t& response)
{
    for (std::uint32_t i = 0; i < 16; ++i)
    {
        response = m_spi.Transfer(0xFF);

        if ((response & 0x80) == 0)
        {
            m_lastResponse = response;
            return true;
        }
    }

    return false;
}

bool SDCard::WaitDataToken(std::uint8_t& token)
{
    for (std::uint32_t i = 0; i < 100000; ++i)
    {
        token = m_spi.Transfer(0xFF);

        if (token == 0xFF)
        {
            continue;
        }

        return true;
    }

    return false;
}

ReadResult SDCard::GetLastReadResult() const
{
    return m_lastReadResult;
}

std::uint8_t SDCard::GetLastResponse() const
{
    return m_lastResponse;
}

}