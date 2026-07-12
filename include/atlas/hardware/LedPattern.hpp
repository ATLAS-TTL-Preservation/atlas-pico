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

    Error
};

} // namespace atlas::hardware