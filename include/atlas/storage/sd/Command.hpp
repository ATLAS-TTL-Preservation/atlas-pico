#pragma once

#include <cstdint>

namespace atlas::storage::sd
{

enum class Command : std::uint8_t
{
    Cmd0  = 0,
    Cmd8  = 8,
    Cmd9  = 9,
    Cmd10 = 10,
    Cmd12 = 12,
    Cmd13 = 13,
    Cmd16 = 16,
    Cmd17 = 17,
    Cmd24 = 24,
    Cmd55 = 55,
    Cmd58 = 58,

    Acmd41 = 41
};

}