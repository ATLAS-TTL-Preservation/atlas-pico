#pragma once

#include <atlas/gpio/Led.hpp>
#include <atlas/gpio/ButtonManager.hpp>
#include <atlas/display/st7735/ST7735Display.hpp>

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
};

}