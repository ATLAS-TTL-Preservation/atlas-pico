#include <atlas/cores/kaos/menus/MainMenu.hpp>
#include <atlas/cores/kaos/KaosCore.hpp>
#include <atlas/cores/atlas/AtlasCore.hpp>

namespace atlas::cores::kaos::menus
{

const char* MainMenu::Title() const
{
    return "KAOS";
}

std::string_view MainMenu::Footer() const
{
    return "Select: Open";
}

void MainMenu::Enter()
{
    TextMenu::Enter();

    ClearEntries();

    AddEntry("Player 1");
    AddEntry("Exit");
}

void MainMenu::OnSelect()
{
    switch (SelectedIndex())
    {
    case 0:
        // Player 1
        break;

    case 1:
        m_context
            ->GetCoreManager()
            .SetCore(
                &m_context->GetAtlasCore());
        break;
    }
}

}