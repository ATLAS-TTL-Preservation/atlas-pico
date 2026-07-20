#pragma once

#include <array>

#include <atlas/cores/kaos/usb/SkylandersPortalHid.hpp>

namespace atlas::cores::kaos::usb
{

class TrapTeamPortal final : public SkylandersPortalHid
{
public:
    TrapTeamPortal();
    ~TrapTeamPortal() override = default;

    const tusb_desc_device_t* GetDeviceDescriptor() const override;

    const uint8_t* GetConfigurationDescriptor(
        uint8_t configuration) const override;

    const uint8_t* GetReportDescriptor() const override;

    const char* const* GetStringDescriptors() const override;

private:
    tusb_desc_device_t m_deviceDescriptor;

    std::array<uint8_t, 29> m_reportDescriptor;

    std::array<uint8_t, 41> m_configurationDescriptor;

    std::array<char, 2> mLanguageDescriptor;

    std::array<const char*, 4> mStringDescriptors;
};

}