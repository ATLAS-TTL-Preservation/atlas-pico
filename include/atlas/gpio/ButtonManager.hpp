#pragma once

#include <atlas/gpio/Button.hpp>
#include <atlas/hardware/Pinout.hpp>

namespace atlas::gpio
{

class ButtonManager
{
public:
    ButtonManager();

    void Init();

    [[nodiscard]]
    bool IsPressed(Button button) const;

private:
    static constexpr unsigned int Action1Pin = atlas::hardware::Pinout::Buttons::Action1;
    static constexpr unsigned int LeftPin    = atlas::hardware::Pinout::Buttons::Left;
    static constexpr unsigned int SelectPin  = atlas::hardware::Pinout::Buttons::Select;
    static constexpr unsigned int RightPin   = atlas::hardware::Pinout::Buttons::Right;
    static constexpr unsigned int Action2Pin = atlas::hardware::Pinout::Buttons::Action2;
};

} // namespace atlas::gpio