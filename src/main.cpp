#include <pico/stdlib.h>

#include <atlas/app/Application.hpp>

int main()
{
    stdio_init_all();

    atlas::app::Application app;
    app.Run();

    return 0;
}