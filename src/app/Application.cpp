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
    if (m_storage.Exists("/config.ptpe"))
    {
        m_display.DrawText(5, 15, "FILE EXISTS");
    }
    else{
        m_display.DrawText(5, 15, "DOESNT EXISTS");
    }
    if (m_storage.Exists("/config2.ptpe"))
    {
        m_display.DrawText(5, 25, "FILE EXISTS");
    }
    else{
        m_display.DrawText(5, 25, "DOESNT EXISTS");
    }
    

}

void Application::Loop()
{
     m_led.Update(); 
}

}