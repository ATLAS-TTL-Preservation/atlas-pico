#include <atlas/usb/UsbManager.hpp>

#include <bsp/board_api.h>
#include <tusb.h>

namespace atlas::usb
{

UsbManager* UsbManager::s_instance = nullptr;

UsbManager* UsbManager::Get()
{
    return s_instance;
}

UsbManager::UsbManager()
{
    s_instance = this;
}


bool UsbManager::Initialize()
{
    board_init();
    return tusb_rhport_init(RootHubPort, nullptr);
}

void UsbManager::Update()
{
    if (!tusb_inited())
    {
        return;
    }

    tud_task();
}

void UsbManager::SetProfile(UsbHidProfile* profile)
{
    m_profile = profile;
}

UsbHidProfile* UsbManager::GetProfile() const
{
    return m_profile;
}

}