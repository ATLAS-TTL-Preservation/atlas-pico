#pragma once

#include <atlas/usb/UsbHidProfile.hpp>

namespace atlas::usb
{

class UsbManager
{
public:
    UsbManager();

    static UsbManager* Get();
    bool Initialize();
    void Update();

    void SetProfile(UsbHidProfile* profile);

    UsbHidProfile* GetProfile() const;

private:
    static constexpr uint8_t RootHubPort = 0;
    UsbHidProfile* m_profile = nullptr;
    static UsbManager* s_instance;
};

}