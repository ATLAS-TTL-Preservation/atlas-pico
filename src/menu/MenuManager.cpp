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

    if (input.Left.Pressed)
    {
        m_current->OnPrevious();
    }

    if (input.Right.Pressed)
    {
        m_current->OnNext();
    }

    if (input.Select.Pressed)
    {
        m_current->OnSelect();
    }

    if (input.ButtonA.Pressed)
    {
        m_current->OnContext();
    }

    if (input.ButtonB.Pressed)
    {
        m_current->OnBack();
    }

    m_current->Update();
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