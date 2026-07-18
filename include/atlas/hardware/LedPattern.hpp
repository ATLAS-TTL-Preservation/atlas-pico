#pragma once

namespace atlas::hardware
{

enum class LedPattern
{
    Off,
    On,

    BlinkSlow,
    BlinkFast,

    Busy,

    Fatal
};

} // namespace atlas::hardware