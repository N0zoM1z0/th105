#pragma once

#include <stddef.h>
#include <list>

namespace th105 {

// Bounded prefix for texture population, text traversal and native end cleanup.
// The complete font owner extends beyond this prefix (fallback color at168).
struct TextTextureFontView {
    void *dc_000;
    void *font_004;
    void *old_font_008;
    unsigned char unknown_00c[0x111];
    unsigned char render_via_intermediate_11d;
    unsigned char unknown_11e[0x22];
    void *surface_base_140;
    void *surface_cursor_144;
    unsigned surface_height_148;
    unsigned surface_width_14c;
    int surface_pitch_dwords_150;
    unsigned *active_color_154;
    unsigned *base_color_158;
    std::list<unsigned *> temporary_colors_15c;

    void render_text(const char *text, unsigned *width_out, unsigned *height_out);

    // Ordinary source members. The original privately lowers begin through ESI,
    // glyph/blend through EAX, and markup through EDX plus ECX height_out.
    void begin_text_render();
    void draw_text_glyph(unsigned character, unsigned *width_out, unsigned *height_out);
    int parse_text_markup(const char *cursor, unsigned *width_out, unsigned *height_out);
    unsigned char *blend_intermediate_text_surface(const unsigned *source, unsigned *destination);
};

typedef char TextFontSurfaceOffset[
    offsetof(TextTextureFontView, surface_base_140) == 0x140 ? 1 : -1];
typedef char TextFontPitchOffset[
    offsetof(TextTextureFontView, surface_pitch_dwords_150) == 0x150 ? 1 : -1];
typedef char TextFontColorListOffset[
    offsetof(TextTextureFontView, temporary_colors_15c) == 0x15c ? 1 : -1];

} // namespace th105
