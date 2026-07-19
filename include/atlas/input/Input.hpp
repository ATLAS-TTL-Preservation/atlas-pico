#pragma once

namespace atlas::input
{

struct ButtonState
{
    bool Down = false;

    bool Pressed = false;

    bool Released = false;
};

struct Input
{
    ButtonState Left;

    ButtonState Right;

    ButtonState Select;

    ButtonState ButtonA;

    ButtonState ButtonB;
};

}