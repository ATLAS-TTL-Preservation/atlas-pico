#pragma once

#include <atlas/cores/common/Core.hpp>

namespace atlas::core
{

class CoreManager
{
public:
    void SetCore(
        Core* core);

    void Update(
        const atlas::input::Input& input);

    void Draw(
        atlas::display::Display& display);

private:
    Core* m_current = nullptr;
};

}