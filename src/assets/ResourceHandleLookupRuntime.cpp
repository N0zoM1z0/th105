#include "ResourceHandleLookupRuntime.hpp"

namespace th105 {

class ScopedHandleManagerLock {
public:
    explicit ScopedHandleManagerLock(CriticalSectionWrapper *lock)
        : lock_(lock)
    {
        EnterCriticalSection(&lock_->critical_section_04);
    }

    ~ScopedHandleManagerLock()
    {
        LeaveCriticalSection(&lock_->critical_section_04);
    }

private:
    CriticalSectionWrapper *lock_;
};

void **CHandleManagerLookupView::lookup_token_417800(
    unsigned int packed_token)
{
    ScopedHandleManagerLock scope(&lock_048);
    const ResourceHandleToken &token =
        *reinterpret_cast<const ResourceHandleToken *>(&packed_token);

    if (generations_028.size() <= token.slot_00
        || generations_028[token.slot_00] != token.generation_02)
        return 0;
    return stable_resource_slots_018.at(token.slot_00);
}

} // namespace th105
