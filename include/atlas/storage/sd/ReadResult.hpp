#pragma once

#include <cstdint>

namespace atlas::storage::sd
{

enum class ReadResult : std::uint8_t
{
    Success,

    CommandTimeout,

    InvalidResponse,

    TokenTimeout,

    InvalidDataToken
};

}