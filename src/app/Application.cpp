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
    if (!m_storage.Init())
    {
        m_display.Clear();
        m_display.DrawText(5, 5, "Storage Error");
        m_display.DrawText(5, 20, "Failed to mount");
        m_display.DrawText(5, 35, "the SD card.");
        m_display.DrawText(5, 60, "Remove or replace");
        m_display.DrawText(5, 75, "the SD card and");
        m_display.DrawText(5, 90, "restart ATLAS.");
        m_led.SetPattern(LedPattern::Fatal);

        while (true)
        {
            m_led.Update();
            System::Yield();
        }
    }

    m_menuManager.SetMenu(&m_mainMenu);

}

void Application::Loop()
{   
    m_input.Update(m_buttons);
    m_menuManager.Update(m_input.GetInput());

    m_menuManager.Draw(m_display);
    m_led.Update(); 
}

}