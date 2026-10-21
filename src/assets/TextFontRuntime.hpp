#pragma once

#include <stddef.h>

namespace th105 {

// Bounded view of the prefix used by 4097A0/412670, not the complete font owner.
// In particular, the native color list at15C and color168 extend beyond it.
struct TextTextureFontView {
    unsigned char unknown_000[0x11d];
    unsigned char render_via_intermediate_11d;
    unsigned char unknown_11e[0x22];
    void *surface_base_140;
    void *surface_cursor_144;
    unsigned surface_height_148;
    unsigned surface_width_14c;
    int surface_pitch_dwords_150;

    void render_text(const char *text, unsigned *width_out, unsigned *height_out);

    // Ordinary source members. The original privately lowers begin/end through
    // ESI, glyph/blend through EAX, and markup through EDX plus ECX height_out.
    void begin_text_render();
    void end_text_render();
    void draw_text_glyph(unsigned character, unsigned *width_out, unsigned *height_out);
    int parse_text_markup(const char *cursor, unsigned *width_out, unsigned *height_out);
    unsigned char *blend_intermediate_text_surface(const unsigned *source, unsigned *destination);
};

typedef char TextFontSurfaceOffset[
    offsetof(TextTextureFontView, surface_base_140) == 0x140 ? 1 : -1];
typedef char TextFontPitchOffset[
    offsetof(TextTextureFontView, surface_pitch_dwords_150) == 0x150 ? 1 : -1];

} // namespace th105
