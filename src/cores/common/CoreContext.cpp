#include <atlas/cores/common/CoreContext.hpp>

#include <atlas/cores/common/CoreManager.hpp>

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

}