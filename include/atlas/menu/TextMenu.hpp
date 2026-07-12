#pragma once

#include <array>
#include <string_view>

#include <atlas/menu/Menu.hpp>

namespace atlas::menu
{

class TextMenu : public Menu
{
public:
    static constexpr std::size_t MaxEntries = 16;

    struct Entry
    {
        std::string_view Text;
    };

    void ClearEntries();

    void AddEntry(
        std::string_view text);

    void MoveUp();

    void MoveDown();

    std::size_t SelectedIndex() const;

    std::size_t EntryCount() const;

    void Draw(
        atlas::display::Display& display) override;

protected:
    virtual std::string_view Footer() const
    {
        return "";
    }

private:
    std::array<Entry, MaxEntries> m_entries;

    std::size_t m_entryCount = 0;

    std::size_t m_selectedIndex = 0;
};

}