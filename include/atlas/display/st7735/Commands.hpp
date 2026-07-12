#pragma once

#include <cstdint>

namespace atlas::display::st7735
{

enum class Command : std::uint8_t
{
    Nop = 0x00,
    SoftwareReset = 0x01,

    SleepIn = 0x10,
    SleepOut = 0x11,

    PartialMode = 0x12,
    NormalDisplay = 0x13,

    DisplayInvertOff = 0x20,
    DisplayInvertOn = 0x21,

    DisplayOff = 0x28,
    DisplayOn = 0x29,

    ColumnAddressSet = 0x2A,
    RowAddressSet = 0x2B,
    MemoryWrite = 0x2C,
    MemoryRead = 0x2E,

    VerticalScrollDefinition = 0x33,

    MemoryAccessControl = 0x36,
    VerticalScrollStart = 0x37,

    InterfacePixelFormat = 0x3A,

    FrameRateControlNormal = 0xB1,
    FrameRateControlIdle = 0xB2,
    FrameRateControlPartial = 0xB3,

    DisplayInversionControl = 0xB4,
    DisplayFunctionControl = 0xB6,

    PowerControl1 = 0xC0,
    PowerControl2 = 0xC1,
    PowerControl3 = 0xC2,
    PowerControl4 = 0xC3,
    PowerControl5 = 0xC4,

    VcomControl1 = 0xC5,

    PowerControl6 = 0xFC,

    PositiveGammaCorrection = 0xE0,
    NegativeGammaCorrection = 0xE1
};

} // namespace atlas::display::st7735