#pragma once

#include <vector>

#include "assets/ResourceHandleManager.hpp"
#include "engine/CriticalSectionWrapper.hpp"

namespace th105 {

// Native checked vectors place their begin/end pointers at +0x1c/+0x20
// and +0x2c/+0x30. Only the storage reached by 417800 is modeled here.
class CHandleManagerLookupView {
public:
    void **lookup_token_417800(unsigned int packed_token);

    unsigned char reserved_000[0x18];
    std::vector<void **> stable_resource_slots_018;
    std::vector<unsigned int> generations_028;
    unsigned char reserved_038[0x10];
    CriticalSectionWrapper lock_048;
};

typedef char CHandleManagerLookupView_lock_offset_must_be_0x48[
    offsetof(CHandleManagerLookupView, lock_048) == 0x48 ? 1 : -1];

} // namespace th105
