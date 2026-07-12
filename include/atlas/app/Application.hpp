#pragma once

#include <atlas/gpio/Led.hpp>

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
};

}