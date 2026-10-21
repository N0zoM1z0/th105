// JP1.06a font entry and native begin/end/glyph/accent/markup providers.
// Complete canonical comparisons remain nonexact;
// remaining provider/TU context is needed for the frame and private entries.
#include "TextFontRuntime.hpp"

#include <new>
#include <deque>
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
    font->font_004 = CreateFontA(font->config_00c.height_108, 0, 0, 0,
        font->config_00c.weight_10c, font->config_00c.italic_110, 0, 0, 0x80, 4, 0, 2, 0x31,
        font->config_00c.face_000);
    font->dc_000 = GetDC(g_main_window);
    font->old_font_008 = SelectObject(font->dc_000, font->font_004);
    TextMetricsA metrics;
    GetTextMetricsA(font->dc_000, &metrics);
    font->font_ascent_13c = metrics.ascent;
    font->cursor_x_134 = font->config_00c.origin_x_118 + font->config_00c.outline_111;
    font->cursor_y_138 = font->config_00c.origin_y_11c + font->config_00c.outline_111;
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
        if (!config_00c.wrap_112)
            return;
        cursor_x_134 = config_00c.origin_x_118 + config_00c.outline_111;
        cursor_y_138 += config_00c.height_108 + config_00c.spacing_y_124;
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
            cursor_y_138 - config_00c.height_108);
    cursor_x_134 += metrics.gmCellIncX + config_00c.spacing_x_120;
    if (width_out) {
        const unsigned extent = static_cast<unsigned>(right);
        *width_out = *width_out > extent ? *width_out : extent;
    }
    if (height_out) {
        const unsigned extent = static_cast<unsigned>(bottom);
        *height_out = *height_out > extent ? *height_out : extent;
    }
}

void __stdcall set_markup_color(TextFontOwner194 *, unsigned char, unsigned char, unsigned char);
void reset_markup_color(TextFontOwner194 *);
static unsigned char __cdecl decode_markup_hex(unsigned char);
int TextTextureFontView::parse_text_markup(
    const char *cursor, unsigned *width_out, unsigned *height_out)
{
    std::deque<std::string> words;
    const char *close = strchr(cursor, '>');
    if (!close)
        return static_cast<int>(strlen(cursor));
    const int length = static_cast<int>(close - cursor);
    char *buffer = new char[length + 1];
    strncpy_s(buffer, length + 1, cursor, length);
    buffer[length] = 0;
    char delimiters[] = " =\t\n";
    char *context;
    char *token = strtok_s(buffer, delimiters, &context);
    while (token) {
        words.push_back(std::string(token));
        token = strtok_s(0, delimiters, &context);
    }
    delete[] buffer;
    if (words[0] == "br") {
        cursor_y_138 += config_00c.height_108 + config_00c.spacing_y_124;
        cursor_x_134 = config_00c.origin_x_118 + config_00c.outline_111;
    } else if (words[0] == "ruby") {
        if (words.size() > 1) {
            saved_x_18c = cursor_x_134;
            saved_y_190 = cursor_y_138;
            text_170 = words[1];
            unknown_flag_16d = 1;
        }
    } else if (words[0] == "/ruby") {
        if (unknown_flag_16d) {
            TextFontOwner194 ruby;
            TextFontConfig128 config;
            const int ruby_height = config_00c.height_108 / 3;
            strcpy_s(config.face_000, 256, config_00c.face_000);
            config.height_108 = ruby_height;
            config.colors_100[0] = config.colors_100[1] = config_00c.colors_100[0];
            config.colors_100[2] = config.colors_100[3] = config_00c.colors_100[2];
            config.colors_100[4] = config.colors_100[5] = config_00c.colors_100[4];
            if (saved_y_190 >= ruby_height) {
                ruby.set_surface(static_cast<unsigned *>(surface_base_140) +
                    (saved_y_190 - ruby_height) * surface_pitch_dwords_150 + saved_x_18c,
                    surface_width_14c, surface_height_148, surface_pitch_dwords_150);
                const int span = cursor_x_134 - config_00c.spacing_x_120 - saved_x_18c;
                if (span > 0) {
                    const char *text = text_170.c_str();
                    const int bytes = static_cast<int>(text_170.size());
                    int offset = 0;
                    int characters = 0;
                    while (offset < bytes) {
                        const unsigned char lead = static_cast<unsigned char>(text[offset]);
                        if ((lead >= 0x81 && lead < 0xa0) || (lead >= 0xe0 && lead < 0xff))
                            offset += 2;
                        else
                            ++offset;
                        ++characters;
                    }
                    const int gap = (span - bytes * ruby_height / 2) / (characters + 1);
                    config.origin_x_118 = gap;
                    config.origin_y_11c = 0;
                    config.spacing_x_120 = gap;
                    config.spacing_y_124 = 0;
                }
                ruby.configure(&config);
                ruby.render_text(text_170.c_str(), width_out, height_out);
            }
            unknown_flag_16d = 0;
        }
    } else if (words[0] == "accent") {
        accent_16c = 1;
    } else if (words[0] == "/accent") {
        accent_16c = 0;
    } else if (words[0] == "color") {
        if (words.size() > 1) {
            const unsigned char r = (decode_markup_hex(words[1].at(0)) << 4) | decode_markup_hex(words[1].at(1));
            const unsigned char g = (decode_markup_hex(words[1].at(2)) << 4) | decode_markup_hex(words[1].at(3));
            const unsigned char b = (decode_markup_hex(words[1].at(4)) << 4) | decode_markup_hex(words[1].at(5));
            set_markup_color(this, r, g, b);
        }
    } else if (words[0] == "/color") {
        reset_markup_color(this);
    }
    return length + 1;
}

void TextTextureFontView::render_text(const char *text, unsigned *width_out, unsigned *height_out)
{
    int length = static_cast<int>(strlen(text));
    unsigned *intermediate = 0;
    if (config_00c.outline_111 != 0) {
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
    if (config_00c.outline_111 != 0) {
        blend_intermediate_text_surface(intermediate, static_cast<unsigned *>(surface_cursor_144));
        delete[] intermediate;
    }
}

static unsigned char __cdecl decode_markup_hex(unsigned char value)
{
    if (static_cast<unsigned char>(value - '0') <= 9)
        return static_cast<unsigned char>(value - '0');
    if (static_cast<unsigned char>(value - 'a') <= 5)
        return static_cast<unsigned char>(value - 'a' + 10);
    if (static_cast<unsigned char>(value - 'A') <= 5)
        return static_cast<unsigned char>(value - 'A' + 10);
    return 0;
}

} // namespace th105
