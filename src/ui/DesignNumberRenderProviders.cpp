// Actual integer-number and tile renderer bodies, using the shared caller layouts.
// Field names are mapped by their existing independently checked offsets.
namespace th105 {
void NumberRenderView::render(
    int value,
    float x,
    float y,
    int digits,
    char sign_mode)
{
    char suffix;
    if (value < 0) {
        value = -value;
        suffix = 2;
    } else {
        suffix = sign_mode != 0;
    }

    // Keeping this as a source local (rather than mutating x) lets VC8 reuse
    // the dead value-argument slot exactly as the shipped body does.
    float current_x = x - scale_0c * glyph_width_04;
    if (digits > 0) {
        do {
            int glyph = value % 10;
            tile_28.render(
                current_x, y, glyph % columns_14, glyph / columns_14);
            --digits;
            value /= 10;
            current_x -= (spacing_08 + glyph_width_04) * scale_0c;
        } while (digits > 0);
    } else {
        while (value >= 0) {
            int glyph = value % 10;
            tile_28.render(
                current_x, y, glyph % columns_14, glyph / columns_14);
            if (value < 10)
                value = -1;
            else
                value /= 10;
            current_x -= (spacing_08 + glyph_width_04) * scale_0c;
        }
    }

    if (suffix != 0) {
        int glyph = suffix + 9;
        tile_28.render(
            current_x, y, glyph % columns_14, glyph / columns_14);
    }
}


}

namespace th105 {
extern CHandleManager4 g_ui_tile_texture_manager;
extern D3DDevice9 *g_ui_tile_texture_device;
double __cdecl lookup_orientation_cosine_quantized_abs(float phase);
double __cdecl lookup_orientation_sine_quantized_abs(float phase);

// The target materializes shared geometry/UV values as float before reuse.
// Build this pending root with the documented strict-FP profile.
#pragma float_control(except, off, push)
void CNumberTileA4::render(float x, float y, int column, int row)
{
    float left = x - anchor_x_80 * scale_x_88 - 0.5f;
    vertices_08[0].x_00 = left;
    float top = y - anchor_y_84 * scale_y_8c - 0.5f;
    vertices_08[0].y_04 = top;
    float right = width_78 * scale_x_88 + left;
    vertices_08[1].x_00 = right;
    vertices_08[1].y_04 = top;
    vertices_08[2].x_00 = left;
    float bottom = height_7c * scale_y_8c + top;
    vertices_08[2].y_04 = bottom;
    vertices_08[3].y_04 = bottom;
    vertices_08[3].x_00 = right;

    float u_left = column * texture_width_u_9c + texture_u_94;
    vertices_08[0].u_14 = u_left;
    float v_top = row * texture_height_v_a0 + texture_v_98;
    vertices_08[0].v_18 = v_top;
    float u_right = (column + 1) * texture_width_u_9c + texture_u_94;
    vertices_08[1].u_14 = u_right;
    vertices_08[1].v_18 = v_top;
    vertices_08[2].u_14 = u_left;
    float v_bottom = (row + 1) * texture_height_v_a0 + texture_v_98;
    vertices_08[2].v_18 = v_bottom;
    vertices_08[3].v_18 = v_bottom;
    vertices_08[3].u_14 = u_right;

    if (rotation_90 != 0.0f) {
        float cosine = static_cast<float>(
            lookup_orientation_cosine_quantized_abs(rotation_90));
        float sine = static_cast<float>(
            lookup_orientation_sine_quantized_abs(rotation_90));
        float old_x = vertices_08[0].x_00;
        float old_y = vertices_08[0].y_04;
        vertices_08[0].x_00 = x + (old_x - x) * cosine - (old_y - y) * sine;
        vertices_08[0].y_04 = y + (old_x - x) * sine + (old_y - y) * cosine;

        old_x = vertices_08[1].x_00;
        old_y = vertices_08[1].y_04;
        vertices_08[1].x_00 = (old_x - x) * cosine + x - (old_y - y) * sine;
        vertices_08[1].y_04 = (old_x - x) * sine + y + (old_y - y) * cosine;

        old_x = vertices_08[2].x_00;
        old_y = vertices_08[2].y_04;
        vertices_08[2].x_00 = (old_x - x) * cosine + x - (old_y - y) * sine;
        vertices_08[2].y_04 = (old_x - x) * sine + y + (old_y - y) * cosine;

        old_x = vertices_08[3].x_00;
        old_y = vertices_08[3].y_04;
        vertices_08[3].x_00 = (old_x - x) * cosine + x - (old_y - y) * sine;
        vertices_08[3].y_04 = y + (old_x - x) * sine + cosine * (old_y - y);
    }

    unsigned handle = texture_handle_04;
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
        5, 2, vertices_08, sizeof(CNumberTileVertex));
}
#pragma float_control(pop)


}
