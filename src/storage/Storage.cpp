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

bool Storage::Exists(const std::string& path) const
{
    FILINFO info;

    return f_stat(
        path.c_str(),
        &info) == FR_OK;
}

bool Storage::CreateDirectory(
    const std::string& path)
{
    return
        f_mkdir(path.c_str()) == FR_OK;
}

bool Storage::Delete(
    const std::string& path)
{
    return
        f_unlink(path.c_str()) == FR_OK;
}

bool Storage::ReadFile(
    const std::string& path,
    std::vector<std::uint8_t>& data)
{
    data.clear();

    FIL file;

    if (f_open(
            &file,
            path.c_str(),
            FA_READ) != FR_OK)
    {
        return false;
    }

    const FSIZE_t size = f_size(&file);

    data.resize(size);

    UINT bytesRead = 0;

    const FRESULT result =
        f_read(
            &file,
            data.data(),
            static_cast<UINT>(size),
            &bytesRead);

    f_close(&file);

    if (result != FR_OK)
    {
        data.clear();
        return false;
    }

    data.resize(bytesRead);

    return true;
}

bool Storage::WriteFile(
    const std::string& path,
    const std::vector<std::uint8_t>& data)
{
    FIL file;

    if (f_open(
            &file,
            path.c_str(),
            FA_CREATE_ALWAYS | FA_WRITE) != FR_OK)
    {
        return false;
    }

    UINT bytesWritten = 0;

    const FRESULT result =
        f_write(
            &file,
            data.data(),
            static_cast<UINT>(data.size()),
            &bytesWritten);

    f_close(&file);

    return
        result == FR_OK &&
        bytesWritten == data.size();
}

bool Storage::AppendFile(
    const std::string& path,
    const std::vector<std::uint8_t>& data)
{
    FIL file;

    if (f_open(
            &file,
            path.c_str(),
            FA_OPEN_APPEND | FA_WRITE) != FR_OK)
    {
        return false;
    }

    UINT bytesWritten = 0;

    const FRESULT result =
        f_write(
            &file,
            data.data(),
            static_cast<UINT>(data.size()),
            &bytesWritten);

    f_close(&file);

    return
        result == FR_OK &&
        bytesWritten == data.size();
}

std::vector<DirectoryEntry>
Storage::ListDirectory(const std::string& path)
{
    std::vector<DirectoryEntry> entries;

    DIR dir;

    if (f_opendir(&dir, path.c_str()) != FR_OK)
    {
        return entries;
    }

    while (true)
    {
        FILINFO info;

        if (f_readdir(&dir, &info) != FR_OK)
        {
            break;
        }

        if (info.fname[0] == '\0')
        {
            break;
        }

        DirectoryEntry entry;

        entry.Name = info.fname;
        entry.Size = info.fsize;
        entry.IsDirectory =
            (info.fattrib & AM_DIR) != 0;

        entries.push_back(entry);
    }

    f_closedir(&dir);

    return entries;
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