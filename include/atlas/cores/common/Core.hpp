#pragma once

namespace atlas::display
{
class Display;
}

namespace atlas::input
{
struct Input;
}

namespace atlas::core
{

class Core
{
public:
    virtual ~Core() = default;

    virtual void Enter() = 0;

    virtual void Exit() = 0;

    virtual void Update(
        const atlas::input::Input& input) = 0;

    virtual void Draw(
        atlas::display::Display& display) = 0;
};

}