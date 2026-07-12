#include <atlas/menu/MainMenu.hpp>

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
        // Open Skylanders Menu
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