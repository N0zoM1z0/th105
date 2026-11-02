#include "engine/RenderModeManager.hpp"
#include "ui/TextureHandleRuntime.cpp"
#pragma float_control(precise, on)
#pragma fenv_access(on)
// JP1.06a CDesignNumber render callers and CNumber value dispatch.
// Complete source visibility is needed for the private EAX/ESI entries.
// Four complete exact bodies in the genuine linked provider context.
// See docs/DESIGN_NUMBER_FLOAT_EXACT_2026_10_31.md.
#include "DesignObjects.hpp"
#include <math.h>
#include <stddef.h>

#pragma float_control(except, off, push)

namespace th105 {
// Ordinary unexported definitions let VC8 choose the private calling protocol.
void __stdcall render_floating(CNumber *number, float value,
    float x, float y, int integer_digits, int fractional_digits, char sign_mode);
void __stdcall render_bound(CNumber *number, float x, float y);

} // namespace th105

void CDesignNumber::render()
{
    if (enabled_14)
        th105::render_bound(&number_18, x_0c + base_x_04, y_10 + base_y_08);
}
void CDesignNumber::render_offset(float x, float y)
{
    if (enabled_14)
        th105::render_bound(&number_18, x_0c + base_x_04 + x, y_10 + base_y_08 + y);
}

namespace th105 {

void __stdcall render_bound(CNumber *number, float x, float y)
{
    if (number->reserved_1c != 0)
        render_floating(number, number->number_value_24->get_floating(), x, y,
            number->reserved_18, number->reserved_1c,
            number->mode_20);
    else
        number->render(number->number_value_24->get_integer(), x, y,
            number->reserved_18, number->mode_20);
}

// The target retains EBP. Keeping a real frame here also keeps both digit
// counts on the stack, matching the independently observed caller ABI.
// The real linked provider/CRT context naturally supplies its 64-byte alignment.
#pragma optimize("y", off)
void __stdcall render_floating(CNumber *number, float value,
    float x, float y, int integer_digits, int fractional_digits, char sign_mode)
{
    char suffix;
    if (value < 0) {
        value = -value;
        suffix = 2;
    } else {
        suffix = sign_mode != 0;
    }
    int integer_part = static_cast<int>(value);
    float current_x = x - number->scale_0c * number->glyph_width_04;
    if (fractional_digits > 0) {
        int multiplier = 1;
        for (int i = 0; i < fractional_digits; ++i)
            multiplier *= 10;
        int fraction = static_cast<int>(fmod(static_cast<double>(value), 1.0) * multiplier);
        do {
            int glyph = fraction % 10;
            number->tile_28.render(current_x, y,
                glyph % number->columns_14, glyph / number->columns_14);
            fraction /= 10;
            --fractional_digits;
            current_x -= (number->glyph_width_04 + number->spacing_08) * number->scale_0c;
        } while (fractional_digits > 0);
        current_x += (1.0f - 0.33f) *
            ((number->glyph_width_04 + number->spacing_08) * number->scale_0c);
        number->tile_28.render(current_x, y,
            12 % number->columns_14, 12 / number->columns_14);
        current_x -= (number->glyph_width_04 + number->spacing_08) * number->scale_0c;
    }
    if (integer_digits > 0) {
        do {
            int glyph = integer_part % 10;
            number->tile_28.render(current_x, y,
                glyph % number->columns_14, glyph / number->columns_14);
            integer_part /= 10;
            --integer_digits;
            current_x -= (number->glyph_width_04 + number->spacing_08) * number->scale_0c;
        } while (integer_digits > 0);
    } else {
        while (integer_part >= 0) {
            int glyph = integer_part % 10;
            number->tile_28.render(current_x, y,
                glyph % number->columns_14, glyph / number->columns_14);
            if (integer_part < 10)
                integer_part = -1;
            else
                integer_part /= 10;
            current_x -= (number->glyph_width_04 + number->spacing_08) * number->scale_0c;
        }
    }
    if (suffix != 0) {
        int glyph = suffix + 9;
        number->tile_28.render(current_x, y,
            glyph % number->columns_14, glyph / number->columns_14);
    }
}

#pragma optimize("y", on)

typedef char NumberViewSize[sizeof(CNumber) == 0xcc ? 1 : -1];
typedef char NumberDesignBaseSize[sizeof(CDesignObjectBase) == 0x18 ? 1 : -1];
typedef char NumberDesignSize[sizeof(CDesignNumber) == 0xe4 ? 1 : -1];
typedef char NumberMemberOffset[offsetof(CDesignNumber, number_18) == 0x18 ? 1 : -1];
} // namespace th105

#pragma float_control(pop)

#include "DesignNumberRenderProviders.cpp"

#include "engine/AngleLookup.cpp"
