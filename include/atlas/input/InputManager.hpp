#pragma once

#include <atlas/input/Input.hpp>
#include <atlas/gpio/ButtonManager.hpp>

namespace atlas::input
{

class InputManager
{
public:

    InputManager() = default;

    void Update(
        const atlas::gpio::ButtonManager& buttons);

    const Input& GetInput() const;

private:

    Input m_input;
};

}