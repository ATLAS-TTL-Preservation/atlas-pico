#pragma once

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
    static constexpr unsigned int LedPin = 25;
};

} // namespace atlas::gpio