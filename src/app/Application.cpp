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
    
    std::vector<std::uint8_t> data =
    {
    'H',
    'e',
    'l',
    'l',
    'o',
    ' ',
    'A',
    'T',
    'L',
    'A',
    'S'
    };

    if (m_storage.WriteFile("/hello.txt", data))
    {
        m_display.DrawText(5,15,"WRITE OK");
    }
    else
    {
        m_display.DrawText(5,15,"WRITE FAIL");
    }
    
    std::vector<std::uint8_t> file;

    if (m_storage.ReadFile("/hello.txt", file))
    {
        file.push_back('\0');

        m_display.DrawText(5,25,reinterpret_cast<char*>(file.data()));
    }

}

void Application::Loop()
{
     m_led.Update(); 
}

}