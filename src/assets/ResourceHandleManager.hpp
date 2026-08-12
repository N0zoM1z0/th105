#pragma once

namespace th105 {

// Target ABI token: the 16-bit slot is valid only with its 16-bit generation.
struct ResourceHandleToken {
    unsigned short slot_00;
    unsigned short generation_02;
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
    ResourceHandleToken cached_tokens_64[8];

    // Verified normal-ECX entry point at 0x00417010.  Its returned cell is
    // still owned by the manager; callers clear it before recycling its token.
    void **lookup_token(unsigned int packed_token);
};

typedef char ResourceHandleToken_size_must_be_0x04[
    sizeof(ResourceHandleToken) == 0x04 ? 1 : -1];
typedef char CHandleManager4_size_must_be_0x84[
    sizeof(CHandleManager4) == 0x84 ? 1 : -1];

} // namespace th105
