#include <atlas/cores/atlas/AtlasCore.hpp>

namespace atlas::cores
{

void AtlasCore::Enter()
{
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