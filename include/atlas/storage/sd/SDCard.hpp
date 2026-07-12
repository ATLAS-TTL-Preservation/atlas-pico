#pragma once

#include <cstdint>

namespace atlas::storage::sd
{

class SDCard
{
public:
    SDCard();

    bool Initialize();

private:
    void Select();

    void Deselect();

    std::uint8_t Transfer(std::uint8_t data);
};

}