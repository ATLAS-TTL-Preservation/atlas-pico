#pragma once

#include <atlas/cores/common/Core.hpp>
#include <atlas/cores/common/CoreContext.hpp>

#include <atlas/menu/MenuManager.hpp>

#include <atlas/cores/kaos/menus/MainMenu.hpp>
#include <atlas/cores/kaos/usb/TrapTeamPortal.hpp>


namespace atlas::cores
{

class KaosCore final
    : public atlas::core::Core
{
public:

    explicit KaosCore(
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

    atlas::cores::kaos::menus::MainMenu m_mainMenu;

    atlas::cores::kaos::usb::TrapTeamPortal m_trapTeamPortal;
};

}