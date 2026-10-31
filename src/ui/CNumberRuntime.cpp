#include "CNumberTileTextureOptions.cpp"

namespace th105 {
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
