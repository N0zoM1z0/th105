// JP1.06a native font rendering and actual file-local providers.
// Hex, blend and surface helpers are exact; other complete comparisons remain open.
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

static void __stdcall draw_font_glyph(TextFontOwner194 *font,
    unsigned character, unsigned *width_out, unsigned *height_out)
{
    GlyphMetrics metrics = {0};
    const unsigned long bytes = GetGlyphOutlineA(font->dc_000, character, 5,
        &metrics, 0, 0, &g_text_glyph_transform);
    if (bytes == 0xffffffffu)
        return;
    const unsigned stride = (bytes / metrics.gmBlackBoxY) & ~3u;
    const int width = static_cast<int>(metrics.gmBlackBoxX);
    const int height = static_cast<int>(metrics.gmBlackBoxY);
    const int bottom = font->font_ascent_13c - metrics.gmptGlyphOriginY + font->cursor_y_138 + height;
    const int right = font->cursor_x_134 + metrics.gmptGlyphOriginX + width;
    if (bottom >= static_cast<int>(font->surface_height_148))
        return;
    if (right > static_cast<int>(font->surface_width_14c)) {
        if (!font->config_00c.wrap_112)
            return;
        font->cursor_x_134 = font->config_00c.origin_x_118 + font->config_00c.outline_111;
        font->cursor_y_138 += font->config_00c.height_108 + font->config_00c.spacing_y_124;
    }
    if (bytes != 0) {
        unsigned char *glyph = new unsigned char[bytes];
        unsigned char *coverage = glyph;
        GetGlyphOutlineA(font->dc_000, character, 5, &metrics, bytes, coverage,
            &g_text_glyph_transform);
        unsigned *destination = static_cast<unsigned *>(font->surface_base_140) +
            (font->font_ascent_13c - metrics.gmptGlyphOriginY + font->cursor_y_138) * font->surface_pitch_dwords_150 +
            font->cursor_x_134 + metrics.gmptGlyphOriginX;
        unsigned *color = font->active_color_154;
        if (color) {
            color += font->font_ascent_13c - metrics.gmptGlyphOriginY;
            for (int y = 0; y < height; ++y) {
                for (int x = 0; x < width; ++x) {
                    *destination = ((0x0ff00000u * *coverage++) & 0xff000000u) | *color;
                    ++destination;
                }
                coverage += stride - width;
                destination += font->surface_pitch_dwords_150 - width;
                ++color;
            }
        } else {
            for (int y = 0; y < height; ++y) {
                for (int x = 0; x < width; ++x) {
                    *destination = ((0x0ff00000u * *coverage++) & 0xff000000u) | font->fallback_color_168;
                    ++destination;
                }
                coverage += stride - width;
                destination += font->surface_pitch_dwords_150 - width;
            }
        }
        delete[] glyph;
    }
    if (font->accent_16c)
        th105::draw_text_accent_dot(font, font->cursor_x_134 + metrics.gmCellIncX / 2,
            font->cursor_y_138 - font->config_00c.height_108);
    font->cursor_x_134 += metrics.gmCellIncX + font->config_00c.spacing_x_120;
    if (width_out) {
        const unsigned extent = static_cast<unsigned>(right);
        *width_out = *width_out > extent ? *width_out : extent;
    }
    if (height_out) {
        const unsigned extent = static_cast<unsigned>(bottom);
        *height_out = *height_out > extent ? *height_out : extent;
    }
}

void __stdcall set_markup_color(TextFontOwner194 *font,
    unsigned char red, unsigned char green, unsigned char blue)
{
    if (font->base_color_158) {
        font->temporary_colors_15c.push_front(new unsigned[font->config_00c.height_108]);
        const int last = font->config_00c.height_108 - 1;
        for (int y = 0; y <= last; ++y) {
            unsigned *color = font->temporary_colors_15c.front();
            color[y] =
                (((red - font->config_00c.colors_100[0]) * y / last +
                  font->config_00c.colors_100[0]) << 16) |
                (((green - font->config_00c.colors_100[2]) * y / last +
                  font->config_00c.colors_100[2]) << 8) |
                ((blue - font->config_00c.colors_100[4]) * y / last +
                  font->config_00c.colors_100[4]);
        }
        font->active_color_154 = font->temporary_colors_15c.front();
    } else {
        font->fallback_color_168 = (red << 16) | (green << 8) | blue;
    }
}

static void __stdcall reset_markup_color(TextFontOwner194 *font)
{
    while (!font->temporary_colors_15c.empty()) {
        delete[] font->temporary_colors_15c.front();
        font->temporary_colors_15c.pop_front();
    }
    if (font->base_color_158) {
        font->active_color_154 = font->base_color_158;
    } else {
        font->fallback_color_168 =
            (font->config_00c.colors_100[0] << 16) |
            (font->config_00c.colors_100[2] << 8) |
            font->config_00c.colors_100[4];
    }
}

struct TextSurfaceSize {
    unsigned width;
    unsigned height;
};
static void __stdcall set_font_surface(TextFontOwner194 *, void *, TextSurfaceSize, int);
static unsigned char __cdecl decode_markup_hex(unsigned char);
// Native checked-string operation at 0x412920. Original wrapper/template
// ownership remains unresolved; the operation is not authored progress credit.
static char &__cdecl checked_markup_character(std::string *text, unsigned index)
{
    return text->at(index);
}

// Real caller visibility and positive delimiter flow recover the native private
// EDX font / ECX height output / two-stack-word entry without an ABI facade.
static int __stdcall parse_text_markup(
    TextFontOwner194 *font, const char *cursor, unsigned *width_out, unsigned *height_out)
{
    std::deque<std::string> words;
    const char *close = strchr(cursor, '>');
    if (close) {
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
            font->cursor_y_138 += font->config_00c.height_108 + font->config_00c.spacing_y_124;
            font->cursor_x_134 = font->config_00c.origin_x_118 + font->config_00c.outline_111;
        } else if (words[0] == "ruby") {
            if (words.size() > 1) {
                font->saved_x_18c = font->cursor_x_134;
                font->saved_y_190 = font->cursor_y_138;
                font->text_170 = words[1];
                font->unknown_flag_16d = 1;
            }
        } else if (words[0] == "/ruby") {
            if (font->unknown_flag_16d) {
                TextFontOwner194 ruby;
                TextFontConfig128 config;
                const int ruby_height = font->config_00c.height_108 / 3;
                strcpy_s(config.face_000, 256, font->config_00c.face_000);
                config.height_108 = ruby_height;
                config.colors_100[0] = config.colors_100[1] = font->config_00c.colors_100[0];
                config.colors_100[2] = config.colors_100[3] = font->config_00c.colors_100[2];
                config.colors_100[4] = config.colors_100[5] = font->config_00c.colors_100[4];
                if (font->saved_y_190 >= ruby_height) {
                    TextSurfaceSize size = {font->surface_width_14c, font->surface_height_148};
                    set_font_surface(&ruby, static_cast<unsigned *>(font->surface_base_140) +
                        (font->saved_y_190 - ruby_height) * font->surface_pitch_dwords_150 + font->saved_x_18c,
                        size, font->surface_pitch_dwords_150);
                    const int span = font->cursor_x_134 - font->config_00c.spacing_x_120 - font->saved_x_18c;
                    if (span > 0) {
                        const char *text = font->text_170.c_str();
                        const int bytes = static_cast<int>(font->text_170.size());
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
                    ruby.render_text(font->text_170.c_str(), width_out, height_out);
                }
                font->unknown_flag_16d = 0;
            }
        } else if (words[0] == "accent") {
            font->accent_16c = 1;
        } else if (words[0] == "/accent") {
            font->accent_16c = 0;
        } else if (words[0] == "color") {
            if (words.size() > 1) {
                const unsigned char r = (decode_markup_hex(checked_markup_character(&words[1], 0)) << 4) | decode_markup_hex(checked_markup_character(&words[1], 1));
                const unsigned char g = (decode_markup_hex(checked_markup_character(&words[1], 2)) << 4) | decode_markup_hex(checked_markup_character(&words[1], 3));
                const unsigned char b = (decode_markup_hex(checked_markup_character(&words[1], 4)) << 4) | decode_markup_hex(checked_markup_character(&words[1], 5));
                set_markup_color(font, r, g, b);
            }
        } else if (words[0] == "/color") {
            reset_markup_color(font);
        }
        return length + 1;
    }
    return static_cast<int>(strlen(cursor));
}

static unsigned char *__stdcall blend_font_surface(TextFontOwner194 *, const unsigned *, unsigned *);
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
            offset += th105::parse_text_markup(this, text + offset, width_out, height_out);
        else if (offset <= length)
            draw_font_glyph(this, character, width_out, height_out);
    }

    finish_text_render(this);
    if (config_00c.outline_111 != 0) {
        blend_font_surface(this, intermediate, static_cast<unsigned *>(surface_cursor_144));
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

static void __stdcall set_font_surface(TextFontOwner194 *font,
    void *surface, TextSurfaceSize size, int pitch)
{
    font->surface_base_140 = font->surface_cursor_144 = surface;
    font->surface_width_14c = size.width;
    font->surface_height_148 = size.height;
    font->surface_pitch_dwords_150 = pitch;
}

static unsigned char *__stdcall blend_font_surface(TextFontOwner194 *font,
    const unsigned *source, unsigned *destination)
{
    const int height = static_cast<int>(font->surface_height_148);
    const int width = static_cast<int>(font->surface_width_14c);
    const int pitch = font->surface_pitch_dwords_150;
    const int byte_pitch = pitch * 4;
    const unsigned char *from = reinterpret_cast<const unsigned char *>(source) + byte_pitch;
    unsigned char *to = reinterpret_cast<unsigned char *>(destination) + byte_pitch;
    for (int y = 1; y < height - 1; ++y) {
        int x = 1;
        from += 4;
        to += 4;
        for (; x < width - 1; ++x) {
            if (from[3]) {
                unsigned scale = from[3] + 33;
                if (scale >= 256)
                    scale = 256;
                to[3] = 255;
                to[0] = static_cast<unsigned char>((from[0] * scale) >> 8);
                to[1] = static_cast<unsigned char>((from[1] * scale) >> 8);
                to[2] = static_cast<unsigned char>((from[2] * scale) >> 8);
            } else {
                to[3] = from[-1];
                to[3] = to[3] > from[7] ? to[3] : from[7];
                to[3] = to[3] > from[3 - byte_pitch] ? to[3] : from[3 - byte_pitch];
                to[3] = to[3] > from[3 + byte_pitch] ? to[3] : from[3 + byte_pitch];
            }
            from += 4;
            to += 4;
        }
        from += (pitch - x) * 4;
        to += (pitch - x) * 4;
    }
    return to;
}

} // namespace th105
