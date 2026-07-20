#include <tusb.h>

#include <atlas/usb/UsbManager.hpp>

extern "C"
{

void tud_mount_cb()
{
}

void tud_umount_cb()
{
}

void tud_suspend_cb(bool remoteWakeupEnabled)
{
    (void)remoteWakeupEnabled;
}

void tud_resume_cb()
{
}

uint16_t tud_hid_get_report_cb(
    uint8_t instance,
    uint8_t reportId,
    hid_report_type_t reportType,
    uint8_t* buffer,
    uint16_t requestLength)
{
    auto* profile = atlas::usb::UsbManager::Get()->GetProfile();

    if (profile == nullptr)
    {
        return 0;
    }

    return profile->OnGetReport(
        instance,
        reportId,
        reportType,
        buffer,
        requestLength);
}

void tud_hid_set_report_cb(
    uint8_t instance,
    uint8_t reportId,
    hid_report_type_t reportType,
    uint8_t const* buffer,
    uint16_t bufferSize)
{
    auto* profile = atlas::usb::UsbManager::Get()->GetProfile();

    if (profile == nullptr)
    {
        return;
    }

    profile->OnSetReport(
        instance,
        reportId,
        reportType,
        buffer,
        bufferSize);
}

void tud_hid_report_complete_cb(
    uint8_t instance,
    uint8_t const* report,
    uint16_t length)
{
    (void)instance;
    (void)report;
    (void)length;
}

}