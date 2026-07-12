#pragma once

#include <string>
#include <cstdint>

namespace atlas::storage
{

struct DirectoryEntry
{
    std::string Name;

    bool IsDirectory = false;

    std::uint32_t Size = 0;
};

}