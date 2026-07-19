#pragma once

#include <string_view>

#include <atlas/display/Display.hpp>

namespace atlas::app
{

class BootScreen
{
public:
    explicit BootScreen(display::Display& display);

    void Show();

    void SetStatus(std::string_view status);

private:
    display::Display& m_display;

    static constexpr std::uint16_t StatusAreaHeight = 10;
};

}