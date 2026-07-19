#pragma once

#include <atlas/input/Input.hpp>

#include <atlas/menu/Menu.hpp>

namespace atlas::menu
{

class MenuManager
{
public:

    void SetMenu(
        Menu* menu);

    void Update(
        const atlas::input::Input& input);

    void Draw(
        atlas::display::Display& display);

private:

    Menu* m_current = nullptr;
};

}