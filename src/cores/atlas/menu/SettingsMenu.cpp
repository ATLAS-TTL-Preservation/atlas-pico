#include <atlas/cores/atlas/menu/SettingsMenu.hpp>

namespace atlas::menu
{

const char* SettingsMenu::Title() const
{
    return "Settings";
}

std::string_view SettingsMenu::Footer() const
{
    return "Select: Open";
}

void SettingsMenu::Enter()
{
    ClearEntries();

    AddEntry("Back");
}

}