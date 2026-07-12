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
    struct Display
    {
        static constexpr unsigned int Sck  = 14;
        static constexpr unsigned int Mosi = 15;

        static constexpr unsigned int Cs   = 9;
        static constexpr unsigned int Dc   = 10;
        static constexpr unsigned int Rst  = 11;
    };
    struct SD
    {
        static constexpr unsigned int Clock = 6;
        static constexpr unsigned int Mosi  = 7;
        static constexpr unsigned int Miso  = 4;
        static constexpr unsigned int ChipSelect = 5;
    };
};

} // namespace atlas::hardware