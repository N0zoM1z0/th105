#include "CNumberRuntime.hpp"

namespace th105 {

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
