#include <atlas/app/Application.hpp>
#include <atlas/system/System.hpp>

#include <atlas/hardware/LedPattern.hpp>

using namespace std::chrono_literals;
using atlas::system::System;
using atlas::hardware::LedPattern;

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
    if (m_storage.Init())
    {
        m_display.DrawText(5,5,"MOUNT OK");
    }
    else
    {
        m_display.DrawText(5,5,"MOUNT FAIL");
    }

}

void Application::Loop()
{
     m_led.Update(); 
}

}