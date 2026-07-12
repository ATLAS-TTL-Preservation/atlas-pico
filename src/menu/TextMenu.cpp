#include <atlas/menu/TextMenu.hpp>

namespace atlas::menu
{

void TextMenu::ClearEntries()
{
    m_entryCount = 0;
    m_selectedIndex = 0;

    Invalidate();
}

void TextMenu::AddEntry(
    std::string_view text)
{
    if (m_entryCount >= MaxEntries)
    {
        return;
    }

    m_entries[m_entryCount++].Text = text;

    Invalidate();
}

void TextMenu::MoveUp()
{
    if (m_selectedIndex > 0)
    {
        --m_selectedIndex;

        Invalidate();
    }
}

void TextMenu::MoveDown()
{
    if (m_selectedIndex + 1 < m_entryCount)
    {
        ++m_selectedIndex;

        Invalidate();
    }
}

std::size_t TextMenu::SelectedIndex() const
{
    return m_selectedIndex;
}

std::size_t TextMenu::EntryCount() const
{
    return m_entryCount;
}

void TextMenu::Draw(
    atlas::display::Display& display)
{
    display.Clear();

    DrawStatic(display);

    DrawSelection(display);
}

void TextMenu::DrawStatic(
    atlas::display::Display& display)
{
    constexpr int HeaderY = 5;
    constexpr int Divider1Y = 18;

    constexpr int FirstEntryY = 28;
    constexpr int EntryHeight = 12;

    constexpr int FooterLineY = 115;
    constexpr int FooterY = 120;

    display.DrawText(
        5,
        HeaderY,
        Title());

    display.DrawHorizontalLine(
        0,
        Divider1Y,
        display.GetWidth());

    for (std::size_t i = 0; i < m_entryCount; ++i)
    {
        const int y =
            FirstEntryY +
            static_cast<int>(i) * EntryHeight;

        display.DrawText(
            5,
            y,
            m_entries[i].Text.data());
    }

    display.DrawHorizontalLine(
        0,
        FooterLineY,
        display.GetWidth());

    display.DrawText(
        5,
        FooterY,
        Footer().data());
}

void TextMenu::DrawSelection(
    atlas::display::Display& display)
{
    constexpr int FirstEntryY = 28;
    constexpr int EntryHeight = 12;

    const int y =
        FirstEntryY +
        static_cast<int>(m_selectedIndex) * EntryHeight;

    display.DrawText(
        display.GetWidth() - 12,
        y,
        "<");
}

void TextMenu::OnPrevious()
{
    MoveUp();
}

void TextMenu::OnNext()
{
    MoveDown();
}

void TextMenu::OnContext()
{
}

void TextMenu::OnBack()
{
}

}