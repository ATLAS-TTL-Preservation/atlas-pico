#include <atlas/input/InputManager.hpp>

#include <atlas/system/System.hpp>

namespace atlas::input
{

void InputManager::Update(
    const atlas::gpio::ButtonManager& buttons)
{
    UpdateButton(
        m_left,
        buttons.IsPressed(atlas::gpio::Button::Left),
        m_input.Left);

    UpdateButton(
        m_right,
        buttons.IsPressed(atlas::gpio::Button::Right),
        m_input.Right);

    UpdateButton(
        m_select,
        buttons.IsPressed(atlas::gpio::Button::Select),
        m_input.Select);

    UpdateButton(
        m_buttonA,
        buttons.IsPressed(atlas::gpio::Button::Action1),
        m_input.ButtonA);

    UpdateButton(
        m_buttonB,
        buttons.IsPressed(atlas::gpio::Button::Action2),
        m_input.ButtonB);
}

const Input&
InputManager::GetInput() const
{
    return m_input;
}

void InputManager::UpdateButton(
    DebounceState& state,
    bool rawState,
    ButtonState& button)
{
    button.Pressed = false;
    button.Released = false;

    const std::uint32_t now =
        atlas::system::System::Millis();

    //
    // Raw input changed
    //
    if (rawState != state.Raw)
    {
        state.Raw = rawState;
        state.LastChange = now;
    }

    //
    // Debounce
    //
    if (state.Raw != state.Stable)
    {
        if ((now - state.LastChange) >= DebounceTimeMs)
        {
            state.Stable = state.Raw;

            button.Down = state.Stable;

            if (state.Stable)
            {
                button.Pressed = true;

                state.HoldStart = now;
                state.LastRepeat = now;
            }
            else
            {
                button.Released = true;
            }
        }

        return;
    }

    //
    // Keep current state
    //
    button.Down = state.Stable;

    //
    // Auto repeat
    //
    if (!state.Stable)
    {
        return;
    }

    if ((now - state.HoldStart) < RepeatDelayMs)
    {
        return;
    }

    if ((now - state.LastRepeat) < RepeatRateMs)
    {
        return;
    }

    state.LastRepeat = now;

    button.Pressed = true;
}

}