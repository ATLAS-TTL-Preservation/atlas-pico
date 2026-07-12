#include <atlas/storage/fatfs/DiskIO.hpp>

#include <diskio.h>
#include <ff.h>

namespace
{
    atlas::storage::sd::SDCard* g_sd = nullptr;
}

namespace atlas::storage::fatfs
{

void Initialize(atlas::storage::sd::SDCard& card)
{
    g_sd = &card;
}

}

extern "C"
{

DSTATUS disk_status(BYTE)
{
    if (g_sd == nullptr)
    {
        return STA_NOINIT;
    }

    return 0;
}

DSTATUS disk_initialize(BYTE)
{
    if (g_sd == nullptr)
    {
        return STA_NOINIT;
    }

    return 0;
}

DRESULT disk_read(
    BYTE,
    BYTE* buffer,
    LBA_t sector,
    UINT count)
{
    if (g_sd == nullptr)
    {
        return RES_NOTRDY;
    }

    for (UINT i = 0; i < count; ++i)
    {
        if (!g_sd->ReadBlock(
                sector + i,
                buffer + (i * 512)))
        {
            return RES_ERROR;
        }
    }

    return RES_OK;
}

DRESULT disk_write(
    BYTE,
    const BYTE*,
    LBA_t,
    UINT)
{
    return RES_WRPRT;
}

DRESULT disk_ioctl(
    BYTE,
    BYTE cmd,
    void* buffer)
{
    switch (cmd)
    {
        case CTRL_SYNC:
            return RES_OK;

        case GET_SECTOR_SIZE:
            *static_cast<WORD*>(buffer) = 512;
            return RES_OK;

        case GET_BLOCK_SIZE:
            *static_cast<DWORD*>(buffer) = 1;
            return RES_OK;

        default:
            return RES_PARERR;
    }
}

}