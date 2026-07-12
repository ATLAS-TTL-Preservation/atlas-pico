#include <atlas/gpio/ButtonManager.hpp>

#include <hardware/gpio.h>

namespace atlas::gpio
{

ButtonManager::ButtonManager() = default;

void ButtonManager::Init()
{
    constexpr unsigned int pins[] =
    {
        Action1Pin,
        LeftPin,
        SelectPin,
        RightPin,
        Action2Pin
    };

    for (unsigned int pin : pins)
    {
        gpio_init(pin);
        gpio_set_dir(pin, GPIO_IN);
        gpio_pull_up(pin);
    }
}

bool ButtonManager::IsPressed(Button button) const
{
    unsigned int pin = 0;

    switch (button)
    {
        case Button::Action1:
            pin = Action1Pin;
            break;

        case Button::Left:
            pin = LeftPin;
            break;

        case Button::Select:
            pin = SelectPin;
            break;

        case Button::Right:
            pin = RightPin;
            break;

        case Button::Action2:
            pin = Action2Pin;
            break;
    }

    // Pull-Up => LOW = gedrückt
    return !gpio_get(pin);
}

} // namespace atlas::gpio