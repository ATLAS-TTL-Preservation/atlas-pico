#include <atlas/usb/UsbManager.hpp>

#include <bsp/board_api.h>
#include <tusb.h>

namespace atlas::usb
{

void UsbManager::Initialize()
{
    board_init();
    tusb_init();
}

void UsbManager::Update()
{
    if (!tusb_inited())
    {
        return;
    }

    tud_task();
}

}