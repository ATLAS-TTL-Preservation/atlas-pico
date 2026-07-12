#pragma once

#include <cstdint>
#include <cstddef>

namespace atlas::storage::sd
{

class SPIBus
{
public:
    SPIBus();

    void Initialize();

    void SetLowSpeed();

    void SetHighSpeed();

    void Select();

    void Deselect();

    std::uint8_t Transfer(std::uint8_t data);

    void Transfer(
        const std::uint8_t* tx,
        std::uint8_t* rx,
        std::size_t length);

    bool WaitReady();

private:
    static constexpr std::uint8_t DummyByte = 0xFF;
};

}