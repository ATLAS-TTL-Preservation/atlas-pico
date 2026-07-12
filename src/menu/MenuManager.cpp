#include <atlas/menu/MenuManager.hpp>

namespace atlas::menu
{

void MenuManager::SetMenu(
    Menu* menu)
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

void MenuManager::Update(
    const atlas::input::Input& input)
{
    if (m_current == nullptr)
    {
        return;
    }

    if (input.Left && !m_lastLeft)
    {
        m_current->OnLeft();
    }

    if (input.Right && !m_lastRight)
    {
        m_current->OnRight();
    }

    if (input.Select && !m_lastSelect)
    {
        m_current->OnSelect();
    }

    if (input.Action1 && !m_lastAction1)
    {
        m_current->OnAction1();
    }

    if (input.Action2 && !m_lastAction2)
    {
        m_current->OnAction2();
    }

    m_current->Update();

    m_lastLeft = input.Left;
    m_lastRight = input.Right;
    m_lastSelect = input.Select;
    m_lastAction1 = input.Action1;
    m_lastAction2 = input.Action2;
}

void MenuManager::Draw(
    atlas::display::Display& display)
{
    if (m_current == nullptr)
    {
        return;
    }

    if (!m_current->NeedsRedraw())
    {
        return;
    }

    m_current->Draw(display);

    m_current->Validate();
}

}