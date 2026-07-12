#include <atlas/app/Application.hpp>
#include <atlas/system/System.hpp>

using namespace std::chrono_literals;
using atlas::system::System;

namespace atlas::app
{

void Application::Run()
{
    Initialize();

    while (true)
    {
        Loop();
    }
}

void Application::Initialize()
{
    m_led.Init();
    m_buttons.Init();
    m_display.Init();
}

void Application::Loop()
{
    if (m_buttons.IsPressed(atlas::gpio::Button::Select))
    {
        m_led.Toggle();

        System::Delay(100ms);
    }
}

}