#include <atlas/system/System.hpp>

#include <hardware/timer.h>
#include <pico/stdlib.h>
#include <hardware/watchdog.h>

namespace atlas::system
{

void System::Delay(Milliseconds duration)
{
    sleep_ms(duration.count());
}

void System::Delay(Microseconds duration)
{
    sleep_us(duration.count());
}

std::uint32_t System::Millis()
{
    return to_ms_since_boot(get_absolute_time());
}

std::uint64_t System::Micros()
{
    return time_us_64();
}

void System::Yield()
{
    tight_loop_contents();
}

void System::Reboot(){
    watchdog_reboot(0, 0, 0);

    while (true)
    {
        Yield();
    }
}

}