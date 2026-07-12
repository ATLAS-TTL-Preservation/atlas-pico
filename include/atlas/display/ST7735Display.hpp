#pragma once

#include <atlas/display/Display.hpp>

namespace atlas::display
{

class ST7735Display final : public Display
{
public:
    ST7735Display() = default;
    ~ST7735Display() override = default;

    void Init() override;
    void Clear() override;

    void DrawHorizontalLine(
        std::uint16_t x,
        std::uint16_t y,
        std::uint16_t length
    ) override;

    void DrawText(
        std::uint16_t x,
        std::uint16_t y,
        std::string_view text
    ) override;

    [[nodiscard]]
    std::uint16_t GetWidth() const override;

    [[nodiscard]]
    std::uint16_t GetHeight() const override;

private:
    static constexpr std::uint16_t Width = 160;
    static constexpr std::uint16_t Height = 128;
};

} // namespace atlas::display