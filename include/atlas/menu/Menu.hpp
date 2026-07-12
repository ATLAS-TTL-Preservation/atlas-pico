#pragma once

#include <atlas/display/Display.hpp>

namespace atlas::menu
{

class Menu
{
public:
    virtual ~Menu() = default;

    virtual const char* Title() const
    {
        return "";
    }

    virtual void Enter()
    {
    }

    virtual void Exit()
    {
    }

    virtual void Update()
    {
    }

    virtual void Draw(
        atlas::display::Display& display) = 0;
};

} // namespace atlas::menu