#pragma once

namespace atlas::core
{

class CoreManager;

class CoreContext
{
public:
    explicit CoreContext(
        CoreManager& coreManager);

    [[nodiscard]]
    CoreManager& GetCoreManager();

private:
    CoreManager& m_coreManager;
};

}