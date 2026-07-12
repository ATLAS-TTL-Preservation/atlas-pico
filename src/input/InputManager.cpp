#include <atlas/input/InputManager.hpp>

namespace atlas::input
{

void InputManager::Update(
    const atlas::gpio::ButtonManager& buttons)
{
    m_input.Left =
        buttons.IsPressed(
            atlas::gpio::Button::Left);

    m_input.Right =
        buttons.IsPressed(
            atlas::gpio::Button::Right);

    m_input.Select =
        buttons.IsPressed(
            atlas::gpio::Button::Select);

    m_input.Action1 =
        buttons.IsPressed(
            atlas::gpio::Button::Action1);

    m_input.Action2 =
        buttons.IsPressed(
            atlas::gpio::Button::Action2);
}

const Input&
InputManager::GetInput() const
{
    return m_input;
}

}