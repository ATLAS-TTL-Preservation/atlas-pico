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

    virtual void OnPrevious()
    {
    }

    virtual void OnNext()
    {
    }

    virtual void OnSelect()
    {
    }

    virtual void OnContext()
    {
    }

    virtual void OnBack()
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