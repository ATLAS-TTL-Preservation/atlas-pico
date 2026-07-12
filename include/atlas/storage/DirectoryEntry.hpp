#pragma once

#include <string>

namespace atlas::storage
{

struct DirectoryEntry
{
    std::string Name;

    bool IsDirectory = false;
};

}