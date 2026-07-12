#pragma once

#include <atlas/menu/Menu.hpp>
#include <atlas/display/Display.hpp>

namespace atlas::menu
{

class MenuManager
{
public:

    void SetMenu(Menu* menu);

    void Update();

    virtual void Draw(atlas::display::Display& display);

private:

    Menu* m_current = nullptr;
};

}