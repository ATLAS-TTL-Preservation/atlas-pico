#include <atlas/storage/Storage.hpp>

namespace atlas::storage
{

Storage::Storage() = default;

bool Storage::Init()
{
    return m_sdCard.Initialize();
}

bool Storage::Exists(const std::string&) const
{
    return false;
}

bool Storage::CreateDirectory(const std::string&)
{
    return false;
}

bool Storage::Delete(const std::string&)
{
    return false;
}

bool Storage::ReadFile(
    const std::string&,
    std::vector<std::uint8_t>&)
{
    return false;
}

bool Storage::WriteFile(
    const std::string&,
    const std::vector<std::uint8_t>&)
{
    return false;
}

bool Storage::AppendFile(
    const std::string&,
    const std::vector<std::uint8_t>&)
{
    return false;
}

std::vector<DirectoryEntry>
Storage::ListDirectory(const std::string&)
{
    return {};
}

bool Storage::TestReadBlock(){
   std::uint8_t buffer[512];
   return m_sdCard.ReadBlock(0, buffer);
}

const sd::SDCard& Storage::GetSDCard() const
{
    return m_sdCard;
}

}