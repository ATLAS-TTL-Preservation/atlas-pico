#include <atlas/cores/atlas/menu/MainMenu.hpp>
#include <atlas/cores/kaos/KaosCore.hpp>
#include <atlas/cores/atlas/AtlasCore.hpp>

namespace atlas::menu
{

const char* MainMenu::Title() const
{
    return "ATLAS - Preserving TTL";
}

std::string_view MainMenu::Footer() const
{
    return "Select: Open";
}

void MainMenu::Enter()
{
    ClearEntries();

    AddEntry("Skylanders - KAOS");
    AddEntry("Settings");
    AddEntry("About");
}

void MainMenu::OnSelect()
{
    switch (SelectedIndex())
    {
    case 0:
       m_context
            ->GetCoreManager()
            .SetCore(
                &m_context->GetKaosCore());
        break;

    case 1:
        // Open Settings
        break;

    case 2:
        // Open About
        break;

    default:
        break;
    }
}

}