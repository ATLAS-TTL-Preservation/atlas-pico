#include <atlas/gpio/Led.hpp>

#include <hardware/gpio.h>

#include <atlas/system/System.hpp>

using atlas::system::System;

namespace atlas::gpio
{

Led::Led() = default;

void Led::Init()
{
    gpio_init(LedPin);
    gpio_set_dir(LedPin, GPIO_OUT);

    Off();
}

void Led::On()
{
    gpio_put(LedPin, true);
    m_state = true;
}

void Led::Off()
{
    gpio_put(LedPin, false);
    m_state = false;
}

void Led::Toggle()
{
    gpio_xor_mask(1u << LedPin);
    m_state = !m_state;
}

void Led::SetPattern(atlas::hardware::LedPattern pattern)
{
    if (m_pattern == pattern)
    {
        return;
    }

    m_pattern = pattern;
    m_lastUpdate = System::Millis();
    m_step = 0;
}

void Led::Update()
{
    const auto now = System::Millis();

    switch (m_pattern)
    {
        case atlas::hardware::LedPattern::Off:
        {
            Off();
            break;
        }

        case atlas::hardware::LedPattern::On:
        {
            On();
            break;
        }

        case atlas::hardware::LedPattern::Busy:
        {
            if (now - m_lastUpdate >= 50)
            {
                Toggle();
                m_lastUpdate = now;
            }

            break;
        }

        case atlas::hardware::LedPattern::BlinkSlow:
        {
            if (now - m_lastUpdate >= 500)
            {
                Toggle();
                m_lastUpdate = now;
            }

            break;
        }

        case atlas::hardware::LedPattern::BlinkFast:
        {
            if (now - m_lastUpdate >= 125)
            {
                Toggle();
                m_lastUpdate = now;
            }

            break;
        }

        case atlas::hardware::LedPattern::Error:
        {
            static constexpr std::uint32_t Timings[] =
            {
                120, 120,
                120, 120,
                120, 600
            };

            if (now - m_lastUpdate >= Timings[m_step])
            {
                Toggle();

                m_lastUpdate = now;

                ++m_step;

                if (m_step >= 6)
                {
                    m_step = 0;
                }
            }

            break;
        }
    }
}

} // namespace atlas::gpio