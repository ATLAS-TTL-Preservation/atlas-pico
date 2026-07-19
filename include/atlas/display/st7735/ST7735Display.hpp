#pragma once

#include <atlas/display/Display.hpp>
#include <atlas/display/st7735/Commands.hpp>
#include <atlas/display/st7735/Rotation.hpp>

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

    void DrawImage(
        std::uint16_t x,
        std::uint16_t y,
        const atlas::graphics::Image& image
    ) override;

    void DrawImageRegion(
        std::uint16_t dstX,
        std::uint16_t dstY,
        const atlas::graphics::Image& image,
        std::uint16_t srcX,
        std::uint16_t srcY,
        std::uint16_t width,
        std::uint16_t height) override;

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

    void DrawCharacter(
    std::uint16_t x,
    std::uint16_t y,
    char character);

    void SetAddressWindow(
    std::uint16_t x0,
    std::uint16_t y0,
    std::uint16_t x1,
    std::uint16_t y1);

    void InitializeController();
    
    void SetRotation(Rotation rotation);

    Rotation m_rotation = Rotation::Portrait;
    
    std::uint16_t m_width = 128;
    std::uint16_t m_height = 160;
};

} // namespace atlas::display::st7735