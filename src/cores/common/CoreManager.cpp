#include <atlas/cores/common/CoreManager.hpp>

namespace atlas::core
{

void CoreManager::SetCore(
    Core* core)
{
    if (m_current != nullptr)
    {
        m_current->Exit();
    }

    m_current = core;

    if (m_current != nullptr)
    {
        m_current->Enter();
    }
}

void CoreManager::Update(
    const atlas::input::Input& input)
{
    if (m_current == nullptr)
    {
        return;
    }

    m_current->Update(input);
}

void CoreManager::Draw(
    atlas::display::Display& display)
{
    if (m_current == nullptr)
    {
        return;
    }

    m_current->Draw(display);
}

}