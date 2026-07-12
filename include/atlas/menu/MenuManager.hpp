#pragma once

#include <atlas/menu/Menu.hpp>

namespace atlas::menu
{

class MenuManager
{
public:

    void SetMenu(Menu* menu);

    void Update();

    void Draw(
        atlas::display::Display& display);

private:

    Menu* m_current = nullptr;
};

}