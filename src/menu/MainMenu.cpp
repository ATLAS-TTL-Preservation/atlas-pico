#include <atlas/menu/MainMenu.hpp>

namespace atlas::menu
{

const char* MainMenu::Title() const
{
    return "ATLAS - Perserving TTL";
}

std::string_view MainMenu::Footer() const
{
    return "Middle BTN = Select";
}

void MainMenu::Enter()
{
    ClearEntries();

    AddEntry("Skylanders - KAOS");

    AddEntry("Settings");

    AddEntry("About");
}

}