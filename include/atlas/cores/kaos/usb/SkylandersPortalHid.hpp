#pragma once

#include <atlas/usb/UsbHidProfile.hpp>

namespace atlas::cores::kaos::usb
{

class SkylandersPortalHid : public atlas::usb::UsbHidProfile
{
public:
    virtual ~SkylandersPortalHid() = default;

    uint16_t OnGetReport(
        uint8_t instance,
        uint8_t reportId,
        hid_report_type_t reportType,
        uint8_t* buffer,
        uint16_t requestLength) override;

    void OnSetReport(
        uint8_t instance,
        uint8_t reportId,
        hid_report_type_t reportType,
        const uint8_t* buffer,
        uint16_t bufferSize) override;

protected:
    uint8_t m_senseCounter = 0;
};

}