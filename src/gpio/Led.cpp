#include <atlas/gpio/Led.hpp>

#include <hardware/gpio.h>

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
}

void Led::Off()
{
    gpio_put(LedPin, false);
}

void Led::Toggle()
{
    gpio_xor_mask(1u << LedPin);
}

} // namespace atlas::gpio