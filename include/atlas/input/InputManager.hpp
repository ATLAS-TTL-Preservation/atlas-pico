#pragma once

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

    Input m_input;
};

}