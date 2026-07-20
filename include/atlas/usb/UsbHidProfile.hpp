#pragma once

#include <cstdint>

#include <tusb.h>

namespace atlas::usb
{

class UsbHidProfile
{
public:
    virtual ~UsbHidProfile() = default;

    //-------------------------------------------------------------------------
    // USB Descriptors
    //-------------------------------------------------------------------------

    virtual const tusb_desc_device_t* GetDeviceDescriptor() const = 0;

    virtual const uint8_t* GetConfigurationDescriptor(
        uint8_t configuration) const = 0;

    virtual const uint8_t* GetReportDescriptor() const = 0;

    virtual const char* const* GetStringDescriptors() const = 0;

    //-------------------------------------------------------------------------
    // HID Callbacks
    //-------------------------------------------------------------------------

    virtual uint16_t OnGetReport(
        uint8_t instance,
        uint8_t reportId,
        hid_report_type_t reportType,
        uint8_t* buffer,
        uint16_t requestLength) = 0;

    virtual void OnSetReport(
        uint8_t instance,
        uint8_t reportId,
        hid_report_type_t reportType,
        const uint8_t* buffer,
        uint16_t bufferSize) = 0;

protected:
    void SendReport(const void* data, uint16_t length, uint8_t reportId = 0);
};

}