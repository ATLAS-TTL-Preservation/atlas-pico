#include <atlas/cores/atlas/AtlasCore.hpp>

namespace atlas::cores
{

AtlasCore::AtlasCore(
    atlas::core::CoreContext& context)
    : m_context(context)
{
}

void AtlasCore::Enter()
{
    m_mainMenu.SetContext(&m_context);
    m_aboutMenu.SetContext(&m_context);
    m_settingsMenu.SetContext(&m_context);

    m_menuManager.SetMenu(&m_mainMenu);
}

void AtlasCore::Exit()
{
}

void AtlasCore::Update(
    const atlas::input::Input& input)
{
    m_menuManager.Update(input);
}

void AtlasCore::Draw(
    atlas::display::Display& display)
{
    m_menuManager.Draw(display);
}

}