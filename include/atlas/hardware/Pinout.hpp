#pragma once

namespace atlas::hardware
{

struct Pinout
{
    struct Led
    {
        static constexpr unsigned int Pin = 25;
    };

    struct Buttons
    {
        static constexpr unsigned int Action1 = 16;
        static constexpr unsigned int Left    = 17;
        static constexpr unsigned int Select  = 18;
        static constexpr unsigned int Right   = 19;
        static constexpr unsigned int Action2 = 20;
    };
};

} // namespace atlas::hardware