#pragma once

#include <cstdint>

#include <atlas/gpio/ButtonManager.hpp>

#include <atlas/input/Input.hpp>

namespace atlas::input
{

class InputManager
{
public:

    void Update(
        const atlas::gpio::ButtonManager& buttons);

    const Input& GetInput() const;

private:

    struct DebounceState
    {
        bool Raw = false;

        bool Stable = false;

        std::uint32_t LastChange = 0;

        std::uint32_t HoldStart = 0;

        std::uint32_t LastRepeat = 0;
    };

    static constexpr std::uint32_t DebounceTimeMs = 20;

    static constexpr std::uint32_t RepeatDelayMs = 500;

    static constexpr std::uint32_t RepeatRateMs = 100;

    DebounceState m_left;

    DebounceState m_right;

    DebounceState m_select;

    DebounceState m_buttonA;

    DebounceState m_buttonB;

    Input m_input;

    void UpdateButton(
        DebounceState& state,
        bool rawState,
        ButtonState& button);
};

}