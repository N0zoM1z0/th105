// JP1.06a font entry412670 and native begin/end/glyph providers. COFF is nonexact;
// remaining provider/TU context is needed for the frame and private entries.
#include "TextFontRuntime.hpp"

#include <new>
#include <string.h>

struct HWND__;

namespace th105 {

extern HWND__ *g_main_window;
extern "C" __declspec(dllimport) void *__stdcall SelectObject(void *, void *);
extern "C" __declspec(dllimport) int __stdcall DeleteObject(void *);
extern "C" __declspec(dllimport) int __stdcall ReleaseDC(HWND__ *, void *);


// ANSI Win32 TEXTMETRICA layout, 56 bytes in the pinned x86 SDK.
struct TextMetricsA {
    long height, ascent, descent, internal_leading, external_leading;
    long average_width, maximum_width, weight, overhang;
    long digitized_aspect_x, digitized_aspect_y;
    unsigned char first_char, last_char, default_char, break_char;
    unsigned char italic, underlined, struck_out, pitch_and_family, char_set;
};
typedef char TextMetricsSize[sizeof(TextMetricsA) == 56 ? 1 : -1];
extern "C" __declspec(dllimport) void *__stdcall CreateFontA(
    int, int, int, int, int, unsigned, unsigned, unsigned,
    unsigned, unsigned, unsigned, unsigned, unsigned, const char *);
extern "C" __declspec(dllimport) void *__stdcall GetDC(HWND__ *);
extern "C" __declspec(dllimport) int __stdcall GetTextMetricsA(void *, TextMetricsA *);

static void __stdcall start_text_render(TextTextureFontView *font)
{
    font->font_004 = CreateFontA(font->font_height_114, 0, 0, 0,
        font->font_weight_118, font->font_italic_11c, 0, 0, 0x80, 4, 0, 2, 0x31,
        font->face_00c);
    font->dc_000 = GetDC(g_main_window);
    font->old_font_008 = SelectObject(font->dc_000, font->font_004);
    TextMetricsA metrics;
    GetTextMetricsA(font->dc_000, &metrics);
    font->font_ascent_13c = metrics.ascent;
    font->cursor_x_134 = font->origin_x_124 + font->render_via_intermediate_11d;
    font->cursor_y_138 = font->origin_y_128 + font->render_via_intermediate_11d;
    font->accent_16c = 0;
    font->unknown_flag_16d = 0;
    font->active_color_154 = font->base_color_158;
    while (!font->temporary_colors_15c.empty()) {
        delete[] font->temporary_colors_15c.front();
        font->temporary_colors_15c.pop_front();
    }
}

// Real end cleanup in its actual text-render caller TU. VC8 naturally passes
// font in ESI; conditional EDI saving still differs from the target function.
static void __stdcall finish_text_render(TextTextureFontView *font)
{
    while (!font->temporary_colors_15c.empty()) {
        delete[] font->temporary_colors_15c.front();
        font->temporary_colors_15c.pop_front();
    }
    DeleteObject(SelectObject(font->dc_000, font->old_font_008));
    ReleaseDC(g_main_window, font->dc_000);
    font->dc_000 = font->old_font_008 = font->font_004 = 0;
}

// Native x86 Win32 FIXED/MAT2 and GLYPHMETRICS layouts.
struct Fixed16_16 {
    unsigned short fractional;
    short value;
};

struct GlyphTransform {
    Fixed16_16 eM11;
    Fixed16_16 eM12;
    Fixed16_16 eM21;
    Fixed16_16 eM22;
};

struct GlyphMetrics {
    unsigned gmBlackBoxX;
    unsigned gmBlackBoxY;
    int gmptGlyphOriginX;
    int gmptGlyphOriginY;
    short gmCellIncX;
    short gmCellIncY;
};

typedef char GlyphMetricsSize[sizeof(GlyphMetrics) == 20 ? 1 : -1];
typedef char GlyphTransformSize[sizeof(GlyphTransform) == 16 ? 1 : -1];
extern GlyphTransform g_text_glyph_transform;
extern GlyphTransform g_text_accent_transform;
extern "C" __declspec(dllimport) unsigned long __stdcall GetGlyphOutlineA(
    void *, unsigned, unsigned, GlyphMetrics *, unsigned, void *, const GlyphTransform *);

static void __stdcall draw_text_accent_dot(TextTextureFontView *font, int center_x, int top_y)
{
    GlyphMetrics metrics = {0};
    const unsigned long bytes = GetGlyphOutlineA(font->dc_000, '.', 5,
        &metrics, 0, 0, &g_text_accent_transform);
    if (bytes == 0xffffffffu)
        return;
    const int width = static_cast<int>(metrics.gmBlackBoxX);
    const int height = static_cast<int>(metrics.gmBlackBoxY);
    const unsigned stride = (bytes / metrics.gmBlackBoxY) & ~3u;
    const int top = font->font_ascent_13c - metrics.gmptGlyphOriginY + top_y;
    if (top + height >= static_cast<int>(font->surface_height_148) || top < 0 || bytes == 0)
        return;
    unsigned char *glyph = new unsigned char[bytes];
    GetGlyphOutlineA(font->dc_000, '.', 5, &metrics, bytes, glyph,
        &g_text_accent_transform);
    unsigned *destination = static_cast<unsigned *>(font->surface_base_140) +
        (top_y - metrics.gmptGlyphOriginY + font->font_ascent_13c) * font->surface_pitch_dwords_150 -
        static_cast<int>(metrics.gmBlackBoxX >> 1) + center_x;
    unsigned char *coverage = glyph;
    if (font->active_color_154) {
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x)
                *destination++ = ((0x0ff00000u * *coverage++) & 0xff000000u) | *font->active_color_154;
            coverage += stride - width;
            destination += font->surface_pitch_dwords_150 - width;
        }
    } else {
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x)
                *destination++ = ((0x0ff00000u * *coverage++) & 0xff000000u) | font->fallback_color_168;
            coverage += stride - width;
            destination += font->surface_pitch_dwords_150 - width;
        }
    }
    delete[] glyph;
}

void TextTextureFontView::draw_text_glyph(
    unsigned character, unsigned *width_out, unsigned *height_out)
{
    GlyphMetrics metrics = {0};
    const unsigned long bytes = GetGlyphOutlineA(dc_000, character, 5,
        &metrics, 0, 0, &g_text_glyph_transform);
    if (bytes == 0xffffffffu)
        return;
    const unsigned stride = (bytes / metrics.gmBlackBoxY) & ~3u;
    const int width = static_cast<int>(metrics.gmBlackBoxX);
    const int height = static_cast<int>(metrics.gmBlackBoxY);
    const int bottom = font_ascent_13c - metrics.gmptGlyphOriginY + cursor_y_138 + height;
    const int right = cursor_x_134 + metrics.gmptGlyphOriginX + width;
    if (bottom >= static_cast<int>(surface_height_148))
        return;
    if (right > static_cast<int>(surface_width_14c)) {
        if (!wrap_11e)
            return;
        cursor_x_134 = origin_x_124 + render_via_intermediate_11d;
        cursor_y_138 += font_height_114 + spacing_y_130;
    }
    if (bytes != 0) {
        unsigned char *glyph = new unsigned char[bytes];
        GetGlyphOutlineA(dc_000, character, 5, &metrics, bytes, glyph,
            &g_text_glyph_transform);
        unsigned *destination = static_cast<unsigned *>(surface_base_140) +
            (font_ascent_13c - metrics.gmptGlyphOriginY + cursor_y_138) * surface_pitch_dwords_150 +
            cursor_x_134 + metrics.gmptGlyphOriginX;
        unsigned char *coverage = glyph;
        unsigned *color = active_color_154;
        if (color) {
            color += font_ascent_13c - metrics.gmptGlyphOriginY;
            for (int y = 0; y < height; ++y) {
                for (int x = 0; x < width; ++x)
                    *destination++ = ((0x0ff00000u * *coverage++) & 0xff000000u) | *color;
                coverage += stride - width;
                destination += surface_pitch_dwords_150 - width;
                ++color;
            }
        } else {
            for (int y = 0; y < height; ++y) {
                for (int x = 0; x < width; ++x)
                    *destination++ = ((0x0ff00000u * *coverage++) & 0xff000000u) | fallback_color_168;
                coverage += stride - width;
                destination += surface_pitch_dwords_150 - width;
            }
        }
        delete[] glyph;
    }
    if (accent_16c)
        th105::draw_text_accent_dot(this, cursor_x_134 + metrics.gmCellIncX / 2,
            cursor_y_138 - font_height_114);
    cursor_x_134 += metrics.gmCellIncX + spacing_x_12c;
    if (width_out) {
        const unsigned extent = static_cast<unsigned>(right);
        *width_out = *width_out > extent ? *width_out : extent;
    }
    if (height_out) {
        const unsigned extent = static_cast<unsigned>(bottom);
        *height_out = *height_out > extent ? *height_out : extent;
    }
}

void TextTextureFontView::render_text(const char *text, unsigned *width_out, unsigned *height_out)
{
    int length = static_cast<int>(strlen(text));
    unsigned *intermediate = 0;
    if (render_via_intermediate_11d != 0) {
        intermediate = new unsigned[surface_height_148 * surface_pitch_dwords_150];
        memset(intermediate, 0, 4 * surface_height_148 * surface_pitch_dwords_150);
        surface_base_140 = intermediate;
    }
    if (width_out)
        *width_out = 0;
    if (height_out)
        *height_out = 0;
    start_text_render(this);

    int offset = 0;
    while (offset < length) {
        const unsigned char lead = static_cast<unsigned char>(text[offset]);
        unsigned character;
        unsigned char consumed;
        if ((lead >= 0x81 && lead < 0xa0) || (lead >= 0xe0 && lead < 0xff)) {
            character = (static_cast<unsigned>(lead) << 8)
                | static_cast<unsigned char>(text[offset + 1]);
            consumed = 2;
        } else {
            character = static_cast<unsigned>(static_cast<int>(static_cast<signed char>(lead)));
            consumed = 1;
        }
        offset += consumed;
        if (character == 0)
            length = 0;
        else if (character == '<')
            offset += parse_text_markup(text + offset, width_out, height_out);
        else if (offset <= length)
            draw_text_glyph(character, width_out, height_out);
    }

    finish_text_render(this);
    if (render_via_intermediate_11d != 0) {
        blend_intermediate_text_surface(intermediate, static_cast<unsigned *>(surface_cursor_144));
        delete[] intermediate;
    }
}

} // namespace th105
