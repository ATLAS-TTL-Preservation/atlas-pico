#pragma once

#include <atlas/gpio/Led.hpp>
#include <atlas/gpio/ButtonManager.hpp>
#include <atlas/display/st7735/ST7735Display.hpp>
#include <atlas/storage/Storage.hpp>

#include <atlas/input/InputManager.hpp>

#include <atlas/cores/common/CoreManager.hpp>
#include <atlas/cores/common/CoreContext.hpp>

#include <atlas/cores/atlas/AtlasCore.hpp>

namespace atlas::app
{

class Application
{
public:
    Application();

    void Run();

private:
    void Initialize();
    void Loop();

private:
    atlas::gpio::Led m_led;
    atlas::gpio::ButtonManager m_buttons;
    atlas::display::st7735::ST7735Display m_display;
    atlas::storage::Storage m_storage;

    atlas::core::CoreManager m_coreManager;
    atlas::core::CoreContext m_coreContext;

    atlas::cores::AtlasCore m_atlasCore;

    atlas::input::InputManager m_input;
};

}