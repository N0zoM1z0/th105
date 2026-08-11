#include "CriticalSectionWrapper.hpp"

namespace th105 {

void CriticalSectionWrapper::enter()
{
    EnterCriticalSection(&critical_section_04);
}

void CriticalSectionWrapper::leave()
{
    LeaveCriticalSection(&critical_section_04);
}

} // namespace th105
