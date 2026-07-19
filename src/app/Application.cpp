#include <atlas/app/Application.hpp>
#include <atlas/system/System.hpp>

#include <atlas/hardware/LedPattern.hpp>
#include <atlas/app/BootScreen.hpp>

using namespace std::chrono_literals;
using atlas::system::System;
using atlas::hardware::LedPattern;

namespace atlas::app
{

Application::Application()
    : m_coreContext(m_coreManager)
    , m_atlasCore(m_coreContext)
{
}

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

    BootScreen bootScreen(m_display);

    bootScreen.Show();

    const std::uint32_t bootStart = System::Millis();

    bootScreen.SetStatus("Initializing Storage...");

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

    bootScreen.SetStatus("         Ready         ");

    constexpr std::uint32_t MinimumBootScreenTimeMs = 1000;

    const std::uint32_t elapsed = System::Millis() - bootStart;

    if (elapsed < MinimumBootScreenTimeMs)
    {
        System::Delay(
            System::Milliseconds(
                MinimumBootScreenTimeMs - elapsed));
    }

    m_coreManager.SetCore(&m_atlasCore);
}

void Application::Loop()
{   
    m_input.Update(m_buttons);
    m_coreManager.Update(m_input.GetInput());

    m_coreManager.Draw(m_display);
    m_led.Update(); 
}

}