#pragma once

#include <atlas/display/Display.hpp>
#include <atlas/cores/common/CoreContext.hpp>

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

    void SetContext(
        atlas::core::CoreContext* context)
    {
        m_context = context;
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

protected:

    atlas::core::CoreContext* m_context = nullptr;

private:

    bool m_dirty = true;
};

}