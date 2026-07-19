#pragma once

#include <atlas/cores/common/Core.hpp>
#include <atlas/cores/common/CoreContext.hpp>

#include <atlas/menu/MenuManager.hpp>

#include <atlas/cores/atlas/menu/MainMenu.hpp>
#include <atlas/cores/atlas/menu/AboutMenu.hpp>
#include <atlas/cores/atlas/menu/SettingsMenu.hpp>

namespace atlas::cores
{

class AtlasCore final
    : public atlas::core::Core
{
public:

    explicit AtlasCore(
        atlas::core::CoreContext& context);

    void Enter() override;

    void Exit() override;

    void Update(
        const atlas::input::Input& input) override;

    void Draw(
        atlas::display::Display& display) override;

private:

    atlas::core::CoreContext& m_context;

    atlas::menu::MenuManager m_menuManager;

    atlas::menu::MainMenu m_mainMenu;
    atlas::menu::AboutMenu m_aboutMenu;
    atlas::menu::SettingsMenu m_settingsMenu;
};

}