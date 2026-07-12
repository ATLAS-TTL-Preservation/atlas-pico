#pragma once
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

private:
    static constexpr unsigned int LedPin = atlas::hardware::Pinout::Led::Pin;
};

} // namespace atlas::gpio