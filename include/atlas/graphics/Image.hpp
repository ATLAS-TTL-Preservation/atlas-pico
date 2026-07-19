#pragma once

#include <cstdint>

namespace atlas::graphics
{

class Image
{
public:
    constexpr Image(
        const std::uint16_t* data,
        std::uint16_t width,
        std::uint16_t height)
        : m_data(data),
          m_width(width),
          m_height(height)
    {
    }

    constexpr const std::uint16_t* GetData() const
    {
        return m_data;
    }

    constexpr std::uint16_t GetWidth() const
    {
        return m_width;
    }

    constexpr std::uint16_t GetHeight() const
    {
        return m_height;
    }

private:
    const std::uint16_t* m_data;

    std::uint16_t m_width;

    std::uint16_t m_height;
};
} // namespace atlas::graphics