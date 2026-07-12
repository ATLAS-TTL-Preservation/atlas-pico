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
}

void Application::Loop()
{
    m_led.Toggle();

    sleep_ms(500);
}

}