#include <atlas/cores/common/CoreContext.hpp>

#include <atlas/cores/common/CoreManager.hpp>

#include <atlas/cores/atlas/AtlasCore.hpp>
#include <atlas/cores/kaos/KaosCore.hpp>


namespace atlas::core
{

CoreContext::CoreContext(
    CoreManager& coreManager, atlas::usb::UsbManager& usbManager)
    : m_coreManager(coreManager), m_usb(usbManager)
{
}

CoreManager& CoreContext::GetCoreManager()
{
    return m_coreManager;
}

atlas::usb::UsbManager& CoreContext::GetUsbManager()
{
    return m_usb;
}

atlas::cores::AtlasCore& CoreContext::GetAtlasCore()
{
    return *m_atlasCore;
}

atlas::cores::KaosCore& CoreContext::GetKaosCore()
{
    return *m_kaosCore;
}

void CoreContext::SetAtlasCore(
    atlas::cores::AtlasCore& atlasCore)
{
    m_atlasCore = &atlasCore;
}

void CoreContext::SetKaosCore(
    atlas::cores::KaosCore& kaosCore)
{
    m_kaosCore = &kaosCore;
}

}