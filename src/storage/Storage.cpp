#include <atlas/storage/Storage.hpp>
#include <atlas/storage/fatfs/DiskIO.hpp>

namespace atlas::storage
{

Storage::Storage() = default;

bool Storage::Init()
{
    if (!m_sdCard.Initialize())
    {
        return false;
    }

    atlas::storage::fatfs::Initialize(m_sdCard);

    const FRESULT result =
        f_mount(
            &m_fileSystem,
            "",
            1);

    return result == FR_OK;
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

sd::SDCard& Storage::GetSDCard()
{
    return m_sdCard;
}

const sd::SDCard& Storage::GetSDCard() const
{
    return m_sdCard;
}

}