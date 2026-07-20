#include <atlas/cores/kaos/usb/TrapTeamPortal.hpp>

namespace atlas::cores::kaos::usb
{

TrapTeamPortal::TrapTeamPortal()
{
    m_deviceDescriptor =
    {
        .bLength            = sizeof(tusb_desc_device_t),
        .bDescriptorType    = TUSB_DESC_DEVICE,
        .bcdUSB             = 0x0200,
        .bDeviceClass       = 0x00,
        .bDeviceSubClass    = 0x00,
        .bDeviceProtocol    = 0x00,
        .bMaxPacketSize0    = CFG_TUD_ENDPOINT0_SIZE,

        .idVendor           = 0x1430,
        .idProduct          = 0x0150,
        .bcdDevice          = 0x0100,

        .iManufacturer      = 0x01,
        .iProduct           = 0x02,
        .iSerialNumber      = 0x00,

        .bNumConfigurations = 0x01
    };

    m_reportDescriptor =
    {
        0x06, 0x00, 0xFF,
        0x09, 0x01,
        0xA1, 0x01,
        0x19, 0x01,
        0x29, 0x40,
        0x15, 0x00,
        0x26, 0xFF, 0x00,
        0x75, 0x08,
        0x95, 0x20,
        0x81, 0x00,
        0x19, 0x01,
        0x29, 0xFF,
        0x91, 0x00,
        0xC0
    };

    m_configurationDescriptor =
    {
        0x09,
        0x02,
        0x29, 0x00,
        0x01,
        0x01,
        0x00,
        0x80,
        0xFA,

        0x09,
        0x04,
        0x00,
        0x00,
        0x02,
        0x03,
        0x00,
        0x00,
        0x00,

        0x09,
        0x21,
        0x11, 0x01,
        0x00,
        0x01,
        0x22,
        0x1D, 0x00,

        0x07,
        0x05,
        0x81,
        0x03,
        0x40, 0x00,
        0x01,

        0x07,
        0x05,
        0x02,
        0x03,
        0x40, 0x00,
        0x01
    };

    mLanguageDescriptor =
    {
        0x09,
        0x04
    };

    mStringDescriptors =
    {
        mLanguageDescriptor.data(),
        "Activision",
        "Spyro Porta",
        "99B3f9C9E6"
    };
}

const tusb_desc_device_t* TrapTeamPortal::GetDeviceDescriptor() const
{
    return &m_deviceDescriptor;
}

const uint8_t* TrapTeamPortal::GetConfigurationDescriptor(
    uint8_t configuration) const
{
    (void)configuration;

    return m_configurationDescriptor.data();
}

const uint8_t* TrapTeamPortal::GetReportDescriptor() const
{
    return m_reportDescriptor.data();
}

const char* const* TrapTeamPortal::GetStringDescriptors() const
{
    return mStringDescriptors.data();
}

}