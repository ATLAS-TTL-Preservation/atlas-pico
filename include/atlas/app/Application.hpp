#pragma once

namespace atlas::app
{

class Application
{
public:
    void Run();

private:
    void Initialize();
    void Loop();
};

} // namespace atlas::app