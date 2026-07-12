#pragma once

#include <atlas/display/Display.hpp>
#include <atlas/display/st7735/Commands.hpp>

#include <cstddef>
#include <cstdint>
#include <string_view>

namespace atlas::display::st7735
{

class ST7735Display final : public atlas::display::Display
{
public:
    ST7735Display() = default;
    ~ST7735Display() override = default;

    void Init() override;
    void Clear() override;

    void DrawPixel(
        std::uint16_t x,
        std::uint16_t y) override;

    void DrawVerticalLine(
        std::uint16_t x,
        std::uint16_t y,
        std::uint16_t length) override;

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
    void InitializeSpi();
    void InitializePins();

    void Reset();

    void WriteCommand(Command command);

    void WriteData(std::uint8_t data);

    void WriteData(const std::uint8_t* data, std::size_t length);

    void SetAddressWindow(
    std::uint16_t x0,
    std::uint16_t y0,
    std::uint16_t x1,
    std::uint16_t y1);

    void InitializeController();

private:
    // TODO: Width/Height will be updated when rotation support is implemented.
    static constexpr std::uint16_t Width = 128;
    static constexpr std::uint16_t Height = 160;
};

} // namespace atlas::display::st7735