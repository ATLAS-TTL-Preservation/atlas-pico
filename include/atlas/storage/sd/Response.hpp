#pragma once

#include <cstdint>

namespace atlas::storage::sd
{

enum class Response : std::uint8_t
{
    Idle = 0x01,

    Ready = 0x00
};

}