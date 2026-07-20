#include <atlas/cores/kaos/usb/SkylandersPortalHid.hpp>
#include <array>

namespace atlas::cores::kaos::usb
{

uint16_t SkylandersPortalHid::OnGetReport(
    uint8_t instance,
    uint8_t reportId,
    hid_report_type_t reportType,
    uint8_t* buffer,
    uint16_t requestLength)
{
    (void)instance;
    (void)reportId;
    (void)reportType;
    (void)buffer;
    (void)requestLength;

    return 0;
}

void SkylandersPortalHid::OnSetReport(
    uint8_t instance,
    uint8_t reportId,
    hid_report_type_t reportType,
    const uint8_t* buffer,
    uint16_t bufferSize)
{
    (void)instance;
    (void)reportId;
    (void)bufferSize;

    if (reportType != HID_REPORT_TYPE_OUTPUT)
    {
        return;
    }

    std::array<uint8_t, 32> response{};

    switch (buffer[0])
    {
        case 'R':   // Reboot / Shutdown Portal
        {
            response[0] = 'R';
            response[1] = 0x02;
            response[2] = 0x1B;

            SendReport(response.data(), response.size());
            break;
        }

        case 'J':   // Speaker command
        {
            response[0] = 'J';

            SendReport(response.data(), response.size());
            break;
        }

        case 'M':   // Enable / Disable speaker
        {
            response[0] = 'M';

            SendReport(response.data(), response.size());
            break;
        }

        case 'A':   // Activate Portal
        {
            response[0] = 'A';
            response[1] = buffer[1];
            response[2] = 0xFF;
            response[3] = 0x77;

            SendReport(response.data(), response.size());
            break;
        }

        case 'S':   // Sense Portal
        {
            response[0] = 'S';
            response[1] = 0x00;              // TODO: Loaded Skylander bitmask
            response[5] = m_senseCounter++;
            response[6] = 0x01;

            SendReport(response.data(), response.size());
            break;
        }

        case 'Q':   // Read blocks
        {
            // TODO
            break;
        }

        case 'W':   // Write blocks
        {
            // TODO
            break;
        }

        case 'C':   // Portal LEDs
        {
            SendReport(buffer, bufferSize);
            break;
        }

        default:
            break;
    }
}

}