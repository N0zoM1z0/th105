#include "Tile.hpp"
#include "engine/RenderModeManager.hpp"
#include "assets/ResourceHandleManager.hpp"

#include <stddef.h>

namespace th105 {

extern CHandleManager4 g_ui_tile_texture_manager;
extern D3DDevice9 *g_ui_tile_texture_device;
double __cdecl lookup_orientation_cosine_quantized_abs(float phase);
double __cdecl lookup_orientation_sine_quantized_abs(float phase);

} // namespace th105
using namespace th105;

// The target materializes shared geometry/UV values as float before reuse.
// Build this pending root with the documented strict-FP profile.
#pragma float_control(except, off, push)
void CTile::render(float x, float y, int column, int row)
{
    float left = x - pivot_x_80 * scale_x_88 - 0.5f;
    vertices_08[0].x = left;
    float top = y - pivot_y_84 * scale_y_8c - 0.5f;
    vertices_08[0].y = top;
    float right = texture_width_78 * scale_x_88 + left;
    vertices_08[1].x = right;
    vertices_08[1].y = top;
    vertices_08[2].x = left;
    float bottom = texture_height_7c * scale_y_8c + top;
    vertices_08[2].y = bottom;
    vertices_08[3].y = bottom;
    vertices_08[3].x = right;

    float u_left = column * u_step_9c + u_origin_94;
    vertices_08[0].u = u_left;
    float v_top = row * v_step_a0 + v_origin_98;
    vertices_08[0].v = v_top;
    float u_right = (column + 1) * u_step_9c + u_origin_94;
    vertices_08[1].u = u_right;
    vertices_08[1].v = v_top;
    vertices_08[2].u = u_left;
    float v_bottom = (row + 1) * v_step_a0 + v_origin_98;
    vertices_08[2].v = v_bottom;
    vertices_08[3].v = v_bottom;
    vertices_08[3].u = u_right;

    if (angle_90 != 0.0f) {
        float cosine = static_cast<float>(
            lookup_orientation_cosine_quantized_abs(angle_90));
        float sine = static_cast<float>(
            lookup_orientation_sine_quantized_abs(angle_90));
        float old_x = vertices_08[0].x;
        float old_y = vertices_08[0].y;
        vertices_08[0].x = x + (old_x - x) * cosine - (old_y - y) * sine;
        vertices_08[0].y = y + (old_x - x) * sine + (old_y - y) * cosine;

        old_x = vertices_08[1].x;
        old_y = vertices_08[1].y;
        vertices_08[1].x = (old_x - x) * cosine + x - (old_y - y) * sine;
        vertices_08[1].y = (old_x - x) * sine + y + (old_y - y) * cosine;

        old_x = vertices_08[2].x;
        old_y = vertices_08[2].y;
        vertices_08[2].x = (old_x - x) * cosine + x - (old_y - y) * sine;
        vertices_08[2].y = (old_x - x) * sine + y + (old_y - y) * cosine;

        old_x = vertices_08[3].x;
        old_y = vertices_08[3].y;
        vertices_08[3].x = (old_x - x) * cosine + x - (old_y - y) * sine;
        vertices_08[3].y = y + (old_x - x) * sine + cosine * (old_y - y);
    }

    unsigned handle = value_04;
    if (handle == 0) {
        g_ui_tile_texture_device->SetTexture(0, 0);
        g_ui_tile_texture_manager.cached_handles_64[0] = handle;
    } else if (handle != g_ui_tile_texture_manager.cached_handles_64[0]) {
        void *texture = *g_ui_tile_texture_manager.lookup_token(handle);
        g_ui_tile_texture_device->SetTexture(0, texture);
        g_ui_tile_texture_manager.cached_handles_64[0] = handle;
    }
    g_render_mode_manager.device_04->SetFVF(0x144);
    g_render_mode_manager.device_04->DrawPrimitiveUP(
        5, 2, vertices_08, sizeof(SpriteVertex28));
}
#pragma float_control(pop)

typedef char SpriteVertex28Size[sizeof(SpriteVertex28) == 0x1c ? 1 : -1];
typedef char CTileSize[sizeof(CTile) == 0xa4 ? 1 : -1];
typedef char UiTileRenderVerticesOffset[
    offsetof(CTile, vertices_08) == 0x08 ? 1 : -1];
typedef char UiTileRenderPivotOffset[
    offsetof(CTile, pivot_x_80) == 0x80 ? 1 : -1];
typedef char UiTileRenderUvStepOffset[
    offsetof(CTile, u_step_9c) == 0x9c ? 1 : -1];
