#pragma once

#include <chrono>
#include <cstdint>

namespace atlas::system
{

class System
{
public:
    using Milliseconds = std::chrono::milliseconds;
    using Microseconds = std::chrono::microseconds;

public:
    static void Delay(Milliseconds duration);

    static void Delay(Microseconds duration);

    static void Yield();

    [[nodiscard]]
    static std::uint32_t Millis();

    [[nodiscard]]
    static std::uint64_t Micros();
};

}