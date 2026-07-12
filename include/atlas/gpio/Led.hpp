#pragma once

#include <cstdint>

#include <atlas/hardware/LedPattern.hpp>
#include <atlas/hardware/Pinout.hpp>

namespace atlas::gpio
{

class Led
{
public:
    Led();

    void Init();

    void On();

    void Off();

    void Toggle();

    void SetPattern(atlas::hardware::LedPattern pattern);

    void Update();

private:
    static constexpr unsigned int LedPin = atlas::hardware::Pinout::Led::Pin;

private:
    atlas::hardware::LedPattern m_pattern = atlas::hardware::LedPattern::Off;

    bool m_state = false;

    std::uint32_t m_lastUpdate = 0;

    std::uint8_t m_step = 0;
};

} // namespace atlas::gpio