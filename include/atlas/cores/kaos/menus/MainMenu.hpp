#pragma once

#include <atlas/menu/TextMenu.hpp>
#include <atlas/cores/common/CoreManager.hpp>


namespace atlas::cores::kaos::menus
{

class MainMenu final
    : public atlas::menu::TextMenu
{
public:

    const char* Title() const override;

    void Enter() override;

    void OnSelect() override;

protected:

    std::string_view Footer() const override;
};

}