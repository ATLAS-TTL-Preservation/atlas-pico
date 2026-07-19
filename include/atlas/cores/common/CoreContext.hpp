#pragma once

namespace atlas::core
{

class CoreManager;

}

namespace atlas::cores
{

class AtlasCore;
class KaosCore;

}

namespace atlas::core
{

class CoreContext
{
public:

    explicit CoreContext(
        CoreManager& coreManager);

    CoreManager& GetCoreManager();

    atlas::cores::AtlasCore& GetAtlasCore();

    atlas::cores::KaosCore& GetKaosCore();

    void SetAtlasCore(
        atlas::cores::AtlasCore& atlasCore);

    void SetKaosCore(
        atlas::cores::KaosCore& kaosCore);

private:

    CoreManager& m_coreManager;

    atlas::cores::AtlasCore* m_atlasCore = nullptr;
    atlas::cores::KaosCore* m_kaosCore = nullptr;
};

}