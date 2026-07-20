#include <atlas/cores/kaos/KaosCore.hpp>
#include <atlas/system/System.hpp>

namespace atlas::cores
{

KaosCore::KaosCore(
    atlas::core::CoreContext& context)
    : m_context(context)
{
}

void KaosCore::Enter()
{
    m_context.GetUsbManager().SetProfile(&m_trapTeamPortal);

    if(m_context.GetUsbManager().Initialize()){
        m_mainMenu.SetContext(&m_context);

        m_menuManager.SetMenu(&m_mainMenu);
    }

}

void KaosCore::Exit()
{
    atlas::system::System::Reboot();
}

void KaosCore::Update(
    const atlas::input::Input& input)
{
    m_menuManager.Update(input);
}

void KaosCore::Draw(
    atlas::display::Display& display)
{
    m_menuManager.Draw(display);
}

}