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
    m_display.DrawText(
        0,
        0,
        "Hello World!");
    m_display.DrawText(
        0,
        9,
        "ATLAS Custom Driver");
    m_display.DrawText(
        0,
        18,
        "for the ST7735 Display");
    // Basic Smiley for testing
    // eyes
    m_display.DrawPixel(45, 45);
    m_display.DrawPixel(75, 45);
    // Mouth
    m_display.DrawHorizontalLine(50, 65, 20);

    m_display.DrawPixel(49, 64);
    m_display.DrawPixel(70, 64);

    m_display.DrawPixel(48, 63);
    m_display.DrawPixel(71, 63);
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