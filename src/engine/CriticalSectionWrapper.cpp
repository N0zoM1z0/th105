#include "CriticalSectionWrapper.hpp"

namespace th105 {


CriticalSectionWrapper::CriticalSectionWrapper()
{
    InitializeCriticalSection(&critical_section_04);
}

CriticalSectionWrapper::~CriticalSectionWrapper()
{
    DeleteCriticalSection(&critical_section_04);
}

void CriticalSectionWrapper::enter()
{
    EnterCriticalSection(&critical_section_04);
}

void CriticalSectionWrapper::leave()
{
    LeaveCriticalSection(&critical_section_04);
}

} // namespace th105
