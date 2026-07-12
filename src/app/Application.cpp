#include <atlas/app/Application.hpp>

#include <pico/stdlib.h>

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
    m_display.Clear();
}

void Application::Loop()
{
    if (m_buttons.IsPressed(atlas::gpio::Button::Select))
    {
        m_led.Toggle();

        sleep_ms(150);
    }
}

}