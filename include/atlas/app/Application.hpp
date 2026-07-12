#pragma once

#include <atlas/gpio/Led.hpp>
#include <atlas/gpio/ButtonManager.hpp>

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
};

}