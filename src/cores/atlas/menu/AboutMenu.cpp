#include <atlas/cores/atlas/menu/AboutMenu.hpp>

namespace atlas::menu
{

const char* AboutMenu::Title() const
{
    return "About";
}

std::string_view AboutMenu::Footer() const
{
    return "Button B: Back";
}

void AboutMenu::Enter()
{
    ClearEntries();

    AddEntry("Version");

    AddEntry("Core");

    AddEntry("Build");

    AddEntry("Author");

    AddEntry("Back");
}

}