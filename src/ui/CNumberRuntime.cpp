#include "CNumberRuntime.hpp"

namespace th105 {

struct TitleTextureSizeView {
    void get_texture_size(
        unsigned int handle,
        unsigned int *width,
        unsigned int *height);
};

extern TitleTextureSizeView g_title_texture_size_view;

void CNumberTileA4::set_texture_options(
    unsigned int handle,
    int x,
    int y,
    int width,
    int height,
    int anchor_x,
    int anchor_y)
{
    width_78 = static_cast<float>(width);
    height_7c = static_cast<float>(height);
    anchor_x_80 = static_cast<float>(anchor_x);
    anchor_y_84 = static_cast<float>(anchor_y);
    texture_handle_04 = handle;

    g_title_texture_size_view.get_texture_size(
        handle,
        &handle,
        reinterpret_cast<unsigned int *>(&width));

    vertices_08[0].color_10 =
        vertices_08[1].color_10 =
        vertices_08[2].color_10 =
        vertices_08[3].color_10 = ~0u;

    texture_u_94 = static_cast<float>(x) / handle;
    texture_v_98 = static_cast<float>(y) /
        static_cast<unsigned int>(width);
    texture_width_u_9c = width_78 / handle;
    texture_height_v_a0 = height_7c / static_cast<unsigned int>(width);

    vertices_08[0].z_08 = 0.5f;
    vertices_08[0].rhw_0c = 1.0f;
    vertices_08[1].rhw_0c = 1.0f;
    vertices_08[2].rhw_0c = 1.0f;
    vertices_08[3].rhw_0c = 1.0f;
    scale_y_8c = 1.0f;
    scale_x_88 = 1.0f;
    vertices_08[1].z_08 = 0.5f;
    vertices_08[2].z_08 = 0.5f;
    vertices_08[3].z_08 = 0.5f;
    rotation_90 = 0.0f;
}

void CNumber::initialize(
    unsigned int texture,
    int left,
    int top,
    int right,
    int bottom,
    int columns,
    float spacing,
    int reserved_a,
    int reserved_b,
    int mode)
{
    columns_14 = columns;
    reserved_18 = reserved_a;
    reserved_1c = reserved_b;
    int const glyph_width = right - left;
    glyph_width_04 = static_cast<float>(glyph_width);
    mode_20 = static_cast<unsigned char>(mode);
    spacing_08 = spacing;
    scale_0c = secondary_scale_10 = 1.0f;

    tile_28.set_texture_options(
        texture,
        left,
        top,
        glyph_width,
        bottom - top,
        0,
        0);
}

void CNumber::render(
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

} // namespace th105
