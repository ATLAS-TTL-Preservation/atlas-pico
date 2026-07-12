#include <atlas/menu/MenuManager.hpp>

namespace atlas::menu
{

void MenuManager::SetMenu(Menu* menu)
{
    if (m_current != nullptr)
    {
        m_current->Exit();
    }

    m_current = menu;

    if (m_current != nullptr)
    {
        m_current->Enter();
    }
}

void MenuManager::Update()
{
    if (m_current != nullptr)
    {
        m_current->Update();
    }
}

void MenuManager::Draw(
    atlas::display::Display& display)
{
    if (m_current != nullptr)
    {
        m_current->Draw(display);
    }
}

} // namespace atlas::menu