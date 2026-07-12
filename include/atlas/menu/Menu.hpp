#pragma once

#include <atlas/display/Display.hpp>

namespace atlas::input
{
struct Input;
}

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
        Invalidate();
    }

    virtual void Exit()
    {
    }

    virtual void Update()
    {
    }

    virtual void Draw(
        atlas::display::Display& display) = 0;

    virtual void OnLeft()
    {
    }

    virtual void OnRight()
    {
    }

    virtual void OnSelect()
    {
    }

    virtual void OnAction1()
    {
    }

    virtual void OnAction2()
    {
    }

    bool NeedsRedraw() const
    {
        return m_dirty;
    }

    void Validate()
    {
        m_dirty = false;
    }

protected:

    void Invalidate()
    {
        m_dirty = true;
    }

private:

    bool m_dirty = true;
};

}