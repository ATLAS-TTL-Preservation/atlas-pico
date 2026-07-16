#pragma once

#include <atlas/gpio/Led.hpp>
#include <atlas/gpio/ButtonManager.hpp>
#include <atlas/display/st7735/ST7735Display.hpp>
#include <atlas/storage/Storage.hpp>
#include <atlas/cores/atlas/menu/MainMenu.hpp>
#include <atlas/menu/MenuManager.hpp>
#include <atlas/input/InputManager.hpp>

namespace atlas::app
{

class Application
{
public:
    void Run();

private:
    void Initialize();
    void Loop();

private:
    atlas::gpio::Led m_led;
    atlas::gpio::ButtonManager m_buttons;
    atlas::display::st7735::ST7735Display m_display;
    atlas::storage::Storage m_storage;
    atlas::menu::MenuManager m_menuManager;

    atlas::menu::MainMenu m_mainMenu;
    atlas::input::InputManager m_input;
};

}