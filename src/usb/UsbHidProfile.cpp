#include <atlas/usb/UsbHidProfile.hpp>

namespace atlas::usb
{

void UsbHidProfile::SendReport(const void* data, uint16_t length, uint8_t reportId)
{
    tud_hid_report(reportId, data, length);
}

}