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
        m_current->OnPrevious();
    }

    if (input.Right && !m_lastRight)
    {
        m_current->OnNext();
    }

    if (input.Select && !m_lastSelect)
    {
        m_current->OnSelect();
    }

    if (input.ButtonA && !m_lastButtonA)
    {
        m_current->OnContext();
    }

    if (input.ButtonB && !m_lastButtonB)
    {
        m_current->OnBack();
    }

    m_current->Update();

    m_lastLeft = input.Left;
    m_lastRight = input.Right;

    m_lastSelect = input.Select;

    m_lastButtonA = input.ButtonA;
    m_lastButtonB = input.ButtonB;
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