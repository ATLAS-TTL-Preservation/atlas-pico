#include <atlas/cores/common/CoreContext.hpp>

#include <atlas/cores/common/CoreManager.hpp>

#include <atlas/cores/atlas/AtlasCore.hpp>
#include <atlas/cores/kaos/KaosCore.hpp>

namespace atlas::core
{

CoreContext::CoreContext(
    CoreManager& coreManager)
    : m_coreManager(coreManager)
{
}

CoreManager& CoreContext::GetCoreManager()
{
    return m_coreManager;
}

atlas::cores::AtlasCore& CoreContext::GetAtlasCore()
{
    return *m_atlasCore;
}

atlas::cores::KaosCore& CoreContext::GetKaosCore()
{
    return *m_kaosCore;
}

void CoreContext::SetAtlasCore(
    atlas::cores::AtlasCore& atlasCore)
{
    m_atlasCore = &atlasCore;
}

void CoreContext::SetKaosCore(
    atlas::cores::KaosCore& kaosCore)
{
    m_kaosCore = &kaosCore;
}

}