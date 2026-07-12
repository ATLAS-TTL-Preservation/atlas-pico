#include <atlas/app/Application.hpp>

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
    // Initialize application components.
}

void Application::Loop()
{
    // Main application loop.
}

}