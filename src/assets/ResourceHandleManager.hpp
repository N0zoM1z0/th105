#pragma once

namespace th105 {

// Target ABI token: the 16-bit slot is valid only with its 16-bit generation.
struct ResourceHandleToken {
    unsigned short slot_00;
    unsigned short generation_02;
};

// The value stored in the stable slot table is an owning external-resource
// pointer.  0x00402680 publishes a zeroed cell before the bitmap/wave loader
// populates it; 0x00404FA0 releases and clears that same cell.
struct ResourceSlotCell {
    void *resource_00;
};

// Observed CHandleManager<IDirect3DTexture9 *> storage.  The container regions
// remain raw until their individual VC8 specialization boundaries are matched.
struct CHandleManager4 {
    void *vptr_00;
    unsigned char resource_deque_04[0x10];
    unsigned int resource_slot_count_14;
    unsigned char stable_resource_slot_vector_18[0x10];
    unsigned char generation_vector_28[0x10];
    unsigned char free_slot_list_38[0x0c];
    unsigned int next_generation_44;
    unsigned char lock_48[0x1c];
    unsigned int cached_handles_64[8];

    // Raw target layout contracts used by the shared acquire/recycle pair:
    // +0x14 is the next fresh slot, +0x2c is the generation dword array,
    // +0x38 is the intrusive free-slot list, +0x44 is the generation counter,
    // and +0x4c is the CRITICAL_SECTION object (inside lock_48).
    //
    // 0x00402680 receives this object in EDI, a private optimized ABI.  Keep
    // it a ledger/source contract until an original-TU or linked-island path
    // can express that ABI without a fabricated normal C++ member wrapper.

    // Verified normal-ECX entry point at 0x00417010.  Its returned cell is
    // still owned by the manager; callers clear it before recycling its token.
    void **lookup_token(unsigned int packed_token);
};

typedef char ResourceHandleToken_size_must_be_0x04[
    sizeof(ResourceHandleToken) == 0x04 ? 1 : -1];
typedef char ResourceSlotCell_size_must_be_0x04[
    sizeof(ResourceSlotCell) == 0x04 ? 1 : -1];
typedef char CHandleManager4_size_must_be_0x84[
    sizeof(CHandleManager4) == 0x84 ? 1 : -1];

} // namespace th105
