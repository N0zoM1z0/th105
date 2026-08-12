#include "SpellTexturePool.hpp"

namespace th105 {

// Source ABI for the single-use composite population backend at 0x00409300.
// In the shipped LTCG image its parameters are lowered to EAX=height,
// ESI=upload_state and three stack arguments.
extern int __cdecl populate_composite_texture_resource(
    ResourceSlotCell *resource_cell,
    const char *path_list,
    CompositeTextureUploadState *upload_state,
    unsigned width,
    unsigned height);

union PackedResourceHandle {
    ResourceHandleToken token;
    unsigned packed;
};

unsigned *SpellTexturePool::create_composite_texture(
    unsigned *result,
    const char *path_list,
    CompositeTextureUploadState *upload_state,
    int width,
    int height)
{
    PackedResourceHandle handle;
    handle.packed = 0;

    ResourceSlotCell *const resource_cell =
        acquire_4byte_slot(&handle.token);
    resource_cell->resource_00 = 0;

    if (populate_composite_texture_resource(
            resource_cell,
            path_list,
            upload_state,
            static_cast<unsigned>(width),
            static_cast<unsigned>(height)) < 0) {
        release_token(handle.token);
        *result = 0;
    } else {
        *result = handle.packed;
    }
    return result;
}

} // namespace th105
