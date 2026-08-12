#include "SpellTexturePool.hpp"
#include "CompositeTextMarkup.hpp"
#include "String28.hpp"

#include <string.h>

namespace th105 {

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

extern "C" __declspec(dllimport) unsigned long __stdcall GetGlyphOutlineA(
    void *dc,
    unsigned character,
    unsigned format,
    GlyphMetrics *metrics,
    unsigned buffer_size,
    void *buffer,
    const GlyphTransform *transform);

extern GlyphTransform g_text_glyph_transform;

extern "C" void __cdecl _invalid_parameter_noinfo();

void *MarkupTokenRing::checked_at(int relative_index)
{
    const unsigned end = logical_begin_0c + size_10;
    if (logical_begin_0c > end)
        _invalid_parameter_noinfo();

    const unsigned absolute_index = logical_begin_0c + relative_index;
    if (absolute_index > end || absolute_index < logical_begin_0c)
        _invalid_parameter_noinfo();
    if (absolute_index >= end)
        _invalid_parameter_noinfo();

    if (capacity_08 > absolute_index)
        return storage_04[absolute_index];
    return storage_04[absolute_index - capacity_08];
}

void CompositeTextureUploadState::draw_text_accent_dot(
    int center_x,
    int top_y)
{
    GlyphMetrics metrics;
    memset(&metrics, 0, sizeof(metrics));

    const unsigned long glyph_size = GetGlyphOutlineA(
        *reinterpret_cast<void **>(this),
        '.',
        5,
        &metrics,
        0,
        0,
        &g_text_glyph_transform);
    if (glyph_size == 0xffffffffu)
        return;

    const int glyph_width = static_cast<int>(metrics.gmBlackBoxX);
    int glyph_height = static_cast<int>(metrics.gmBlackBoxY);
    const unsigned source_stride =
        (glyph_size / metrics.gmBlackBoxY) & ~3u;
    const int destination_y =
        top_y
        + *reinterpret_cast<int *>(
            reinterpret_cast<unsigned char *>(this) + 0x13c)
        - metrics.gmptGlyphOriginY;

    if (destination_y + glyph_height >=
            static_cast<int>(surface_height_148)
        || destination_y < 0
        || glyph_size == 0) {
        return;
    }

    unsigned char *glyph = new unsigned char[glyph_size];
    GetGlyphOutlineA(
        *reinterpret_cast<void **>(this),
        '.',
        5,
        &metrics,
        glyph_size,
        glyph,
        &g_text_glyph_transform);

    unsigned *destination =
        static_cast<unsigned *>(surface_base_140)
        + center_x
        + surface_pitch_dwords_150 * destination_y
        - (glyph_width >> 1);
    unsigned char *coverage = glyph;

    while (glyph_height-- > 0) {
        for (int x = 0; x < glyph_width; ++x) {
            const unsigned color = active_color_154 != 0
                ? *active_color_154
                : fallback_color_164;
            *destination++ =
                color | ((0x0ff00000u * *coverage++) & 0xff000000u);
        }
        coverage += source_stride - glyph_width;
        destination += surface_pitch_dwords_150 - glyph_width;
    }

    delete[] glyph;
}

unsigned char __cdecl decode_text_hex_nibble(unsigned char value)
{
    if (static_cast<unsigned char>(value - '0') <= 9)
        return static_cast<unsigned char>(value - '0');
    if (static_cast<unsigned char>(value - 'a') <= 5)
        return static_cast<unsigned char>(value - 'a' + 10);
    if (static_cast<unsigned char>(value - 'A') <= 5)
        return static_cast<unsigned char>(value - 'A' + 10);
    return 0;
}

bool __cdecl string28_equals_c_string(
    const String28 *value,
    const char *text)
{
    return value->compare(text) == 0;
}

} // namespace th105
