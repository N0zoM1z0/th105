#include "engine/D3DTextureQuery.hpp"
#include "ui/Title.hpp"
#include "ResourceHandleLookupRuntime.hpp"

namespace th105 {

void TitleResourceManager::get_texture_size(
    unsigned int handle, unsigned int *width, unsigned int *height)
{
    if (handle == 0) {
        *width = 256;
        *height = 256;
        return;
    }

    EnterCriticalSection(&g_d3d_backend.critical_section_000.critical_section_04);
    D3DTexture9 *const texture = static_cast<D3DTexture9 *>(
        *reinterpret_cast<CHandleManagerLookupView *>(this)->lookup_token_417800(handle));
    D3DSurface9 *surface;
    texture->GetSurfaceLevel(0, &surface);
    D3DSurfaceDescription32 description;
    surface->GetDesc(&description);
    *width = description.width_18;
    *height = description.height_1c;
    surface->Release();
    LeaveCriticalSection(&g_d3d_backend.critical_section_000.critical_section_04);
}

} // namespace th105
