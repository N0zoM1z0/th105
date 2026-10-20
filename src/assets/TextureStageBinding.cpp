// JP1.06a texture-stage binder404DF0; canonical equality remains pending.
// docs/TEXTURE_STAGE_BINDING_2026_10_21.md.
#include "engine/D3DBackend.hpp"
#include "ui/Title.hpp"

namespace th105 {
// Device is the +0x20 member of the exact-backed D3D backend aggregate.
void TitleResourceManager::bind_texture(unsigned int handle, int stage)
{
    if (handle == 0) {
        g_d3d_backend.device_020->SetTexture(stage, 0);
        cached_handles_64[stage] = 0;
    } else if (handle != cached_handles_64[stage]) {
        g_d3d_backend.device_020->SetTexture(
            stage, *lookup_token(handle));
        cached_handles_64[stage] = handle;
    }
}
typedef char TextureCacheOffset[
    offsetof(CHandleManager4, cached_handles_64) == 0x64 ? 1 : -1];
} // namespace th105
