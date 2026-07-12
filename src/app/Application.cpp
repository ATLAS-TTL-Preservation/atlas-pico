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
    if(m_storage.Init()){
        m_display.DrawText(0,0,"SD OK");
        if(m_storage.TestReadBlock()){
             m_display.DrawText(0,10,"READ OK");
        }else{
            m_display.DrawText(0,10,"READ FAIL");
        }
    }else{
        m_display.DrawText(0,0,"SD FAIL");
    }

}

void Application::Loop()
{
     m_led.Update(); 
}

}