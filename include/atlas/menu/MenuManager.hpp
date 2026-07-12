#pragma once

#include <atlas/input/Input.hpp>
#include <atlas/menu/Menu.hpp>

namespace atlas::menu
{

class MenuManager
{
public:

    void SetMenu(Menu* menu);

    void Update(
        const atlas::input::Input& input);

    void Draw(
        atlas::display::Display& display);

private:

    Menu* m_current = nullptr;

    bool m_lastLeft = false;
    bool m_lastRight = false;
    bool m_lastSelect = false;
    bool m_lastAction1 = false;
    bool m_lastAction2 = false;
};

}