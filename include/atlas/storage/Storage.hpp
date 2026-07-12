#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include <atlas/storage/DirectoryEntry.hpp>
#include <atlas/storage/FileMode.hpp>

#include <atlas/storage/sd/SDCard.hpp>

namespace atlas::storage
{

class Storage
{
public:
    Storage();

    bool Init();

    bool TestReadBlock();

    bool Exists(const std::string& path) const;

    bool CreateDirectory(const std::string& path);

    bool Delete(const std::string& path);

    bool ReadFile(
        const std::string& path,
        std::vector<std::uint8_t>& data);

    bool WriteFile(
        const std::string& path,
        const std::vector<std::uint8_t>& data);

    bool AppendFile(
        const std::string& path,
        const std::vector<std::uint8_t>& data);

    std::vector<DirectoryEntry>
    ListDirectory(const std::string& path);

    sd::SDCard& GetSDCard();

    const sd::SDCard& GetSDCard() const;

private:
    sd::SDCard m_sdCard;
};

}