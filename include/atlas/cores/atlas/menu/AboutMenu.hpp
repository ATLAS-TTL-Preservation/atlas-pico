#pragma once

#include <atlas/menu/TextMenu.hpp>

namespace atlas::menu
{

class AboutMenu :
    public TextMenu
{
public:

    const char* Title() const override;

    void Enter() override;

protected:

    std::string_view Footer() const override;
};

}