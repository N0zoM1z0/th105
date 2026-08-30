#include <vector>

#include "assets/ResourceHandleManager.hpp"
#include "engine/CriticalSectionWrapper.hpp"

namespace th105 {

// This view names only the storage reached by CHandleManager4::lookup_token.
// VC8's checked vector base contributes the leading dword in each 0x10-byte
// vector object, so the observed begin/end pointers are at +0x1c/+0x20 and
// +0x2c/+0x30 respectively.
class CHandleManagerLookupView {
public:
    void **lookup_token_417800(unsigned int packed_token);

    unsigned char reserved_000[0x18];
    std::vector<void **> stable_resource_slots_018;
    std::vector<unsigned int> generations_028;
    unsigned char reserved_038[0x10];
    CriticalSectionWrapper lock_048;
};

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

typedef char CHandleManagerLookupView_lock_offset_must_be_0x48[
    offsetof(CHandleManagerLookupView, lock_048) == 0x48 ? 1 : -1];

} // namespace th105
