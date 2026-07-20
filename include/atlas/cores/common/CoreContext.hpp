#pragma once

#include <atlas/usb/UsbManager.hpp>

namespace atlas::core
{

class CoreManager;

}

namespace atlas::cores
{

class AtlasCore;
class KaosCore;

}

namespace atlas::core
{

class CoreContext
{
public:

    explicit CoreContext(
        CoreManager& coreManager, atlas::usb::UsbManager& usbManager);

    CoreManager& GetCoreManager();

    atlas::cores::AtlasCore& GetAtlasCore();

    atlas::cores::KaosCore& GetKaosCore();

    atlas::usb::UsbManager& GetUsbManager();

    void SetAtlasCore(
        atlas::cores::AtlasCore& atlasCore);

    void SetKaosCore(
        atlas::cores::KaosCore& kaosCore);

private:

    CoreManager& m_coreManager;
    atlas::usb::UsbManager& m_usb;

    atlas::cores::AtlasCore* m_atlasCore = nullptr;
    atlas::cores::KaosCore* m_kaosCore = nullptr;
   
};

}