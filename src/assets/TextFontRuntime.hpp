#pragma once

#include <stddef.h>
#include <list>

namespace th105 {

// Observed native prefix for texture population and font begin/end traversal.
// This is not a complete font-owner size or constructor contract.
struct TextTextureFontView {
    void *dc_000;
    void *font_004;
    void *old_font_008;
    char face_00c[0x100];
    unsigned char unknown_10c[8];
    int font_height_114;
    int font_weight_118;
    unsigned char font_italic_11c;
    unsigned char render_via_intermediate_11d;
    unsigned char unknown_11e[6];
    int origin_x_124;
    int origin_y_128;
    unsigned char unknown_12c[8];
    int cursor_x_134;
    int cursor_y_138;
    int font_ascent_13c;
    void *surface_base_140;
    void *surface_cursor_144;
    unsigned surface_height_148;
    unsigned surface_width_14c;
    int surface_pitch_dwords_150;
    unsigned *active_color_154;
    unsigned *base_color_158;
    std::list<unsigned *> temporary_colors_15c;
    unsigned fallback_color_168;
    unsigned char accent_16c;
    unsigned char unknown_flag_16d;

    void render_text(const char *text, unsigned *width_out, unsigned *height_out);

    // Ordinary source members. The original privately lowers begin through ESI,
    // glyph/blend through EAX, and markup through EDX plus ECX height_out.
    void draw_text_glyph(unsigned character, unsigned *width_out, unsigned *height_out);
    int parse_text_markup(const char *cursor, unsigned *width_out, unsigned *height_out);
    unsigned char *blend_intermediate_text_surface(const unsigned *source, unsigned *destination);
};

typedef char TextFontHeightOffset[
    offsetof(TextTextureFontView, font_height_114) == 0x114 ? 1 : -1];
typedef char TextFontAccentOffset[
    offsetof(TextTextureFontView, accent_16c) == 0x16c ? 1 : -1];
typedef char TextFontSurfaceOffset[
    offsetof(TextTextureFontView, surface_base_140) == 0x140 ? 1 : -1];
typedef char TextFontPitchOffset[
    offsetof(TextTextureFontView, surface_pitch_dwords_150) == 0x150 ? 1 : -1];
typedef char TextFontColorListOffset[
    offsetof(TextTextureFontView, temporary_colors_15c) == 0x15c ? 1 : -1];

} // namespace th105
