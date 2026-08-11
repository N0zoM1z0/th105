#pragma once

#include <stddef.h>

namespace th105 {

// Observed VC8 deque prefix for four-byte elements.  The container owns its
// map and four-slot blocks, but not the pointers stored in those blocks.
struct PointerBlockDeque20 {
    unsigned opaque_00;
    void ***map_04;
    unsigned map_size_08;
    unsigned offset_0c;
    unsigned size_10;

    void **append_pointer_ref_4slot(void *const *value);
};

typedef char CheckPointerBlockDeque20Size[
    sizeof(PointerBlockDeque20) == 0x14 ? 1 : -1];
typedef char CheckPointerBlockDeque20MapOffset[
    offsetof(PointerBlockDeque20, map_04) == 0x04 ? 1 : -1];
typedef char CheckPointerBlockDeque20SizeOffset[
    offsetof(PointerBlockDeque20, size_10) == 0x10 ? 1 : -1];

} // namespace th105
