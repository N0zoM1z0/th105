#include "SpellTexturePool.hpp"

#include "engine/CriticalSectionWrapper.hpp"

#include <string.h>

namespace th105 {

struct TextureLockedRect {
    int pitch_00;
    void *bits_04;
};

struct Texture9;

typedef int (__stdcall *TextureLockRect)(
    Texture9 *texture,
    unsigned level,
    TextureLockedRect *locked,
    const void *rect,
    unsigned flags);
typedef int (__stdcall *TextureUnlockRect)(
    Texture9 *texture,
    unsigned level);

struct Texture9Vtable {
    void *unknown_00_48[19];
    TextureLockRect lock_rect_4c;
    TextureUnlockRect unlock_rect_50;
};

struct Texture9 {
    Texture9Vtable *vtable_00;
};

extern "C" __declspec(dllimport) int __stdcall D3DXCreateTexture(
    void *device,
    unsigned width,
    unsigned height,
    unsigned levels,
    unsigned usage,
    unsigned format,
    unsigned pool,
    Texture9 **texture);

extern unsigned char g_texture_creation_flags;
extern void *g_direct3d_device;
extern Win32CriticalSection24 g_texture_resource_lock;

int __cdecl populate_composite_texture_resource(
    ResourceSlotCell *resource_cell,
    const char *path_list,
    CompositeTextureUploadState *upload_state,
    unsigned width,
    unsigned height)
{
    unsigned texture_width = width;
    unsigned texture_height = height;
    if ((g_texture_creation_flags & 0x20) != 0) {
        if (texture_width < texture_height)
            texture_width = texture_height;
        else
            texture_height = texture_width;
    }

    EnterCriticalSection(&g_texture_resource_lock);
    int status = D3DXCreateTexture(
        g_direct3d_device,
        texture_width,
        texture_height,
        1,
        0,
        21,
        1,
        reinterpret_cast<Texture9 **>(&resource_cell->resource_00));
    LeaveCriticalSection(&g_texture_resource_lock);

    if (status >= 0) {
        EnterCriticalSection(&g_texture_resource_lock);
        Texture9 *const texture =
            static_cast<Texture9 *>(resource_cell->resource_00);
        TextureLockedRect locked;
        status = texture->vtable_00->lock_rect_4c(
            texture,
            0,
            &locked,
            0,
            0);
        if (status == 0) {
            memset(locked.bits_04, 0, 4 * texture_width * texture_height);
            upload_state->surface_base_140 = locked.bits_04;
            upload_state->surface_cursor_144 = locked.bits_04;
            upload_state->surface_pitch_dwords_150 = locked.pitch_00 / 4;
            upload_state->surface_width_14c = texture_width;
            upload_state->surface_height_148 = texture_height;
            upload_state->render_composite_text(path_list);
            texture->vtable_00->unlock_rect_50(texture, 0);
        }
        LeaveCriticalSection(&g_texture_resource_lock);
    }
    return status;
}

} // namespace th105
