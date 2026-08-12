#include "SpellTexturePool.hpp"

#include <string.h>

namespace th105 {

unsigned char *CompositeTextureUploadState::blend_intermediate_text_surface(
    const unsigned *source,
    unsigned *destination)
{
    const int width = static_cast<int>(surface_width_14c);
    const int height = static_cast<int>(surface_height_148);
    const int pitch = surface_pitch_dwords_150;
    const unsigned char *source_row =
        reinterpret_cast<const unsigned char *>(source + pitch);
    unsigned char *destination_row =
        reinterpret_cast<unsigned char *>(destination + pitch);

    for (int y = 1; y < height - 1; ++y) {
        const unsigned char *source_pixel = source_row + 4;
        unsigned char *destination_pixel = destination_row + 4;

        for (int x = 1; x < width - 1; ++x) {
            const unsigned alpha = source_pixel[3];
            if (alpha != 0) {
                unsigned opacity = alpha + 33;
                if (opacity >= 0x100)
                    opacity = 0x100;

                destination_pixel[0] =
                    static_cast<unsigned char>((opacity * source_pixel[0]) >> 8);
                destination_pixel[1] =
                    static_cast<unsigned char>((opacity * source_pixel[1]) >> 8);
                destination_pixel[2] =
                    static_cast<unsigned char>((opacity * source_pixel[2]) >> 8);
                destination_pixel[3] = 0xff;
            } else {
                unsigned char outline_alpha = source_pixel[-1];
                if (outline_alpha <= source_pixel[7])
                    outline_alpha = source_pixel[7];
                if (outline_alpha <= source_pixel[3 - 4 * pitch])
                    outline_alpha = source_pixel[3 - 4 * pitch];
                if (outline_alpha <= source_pixel[3 + 4 * pitch])
                    outline_alpha = source_pixel[3 + 4 * pitch];
                destination_pixel[3] = outline_alpha;
            }

            source_pixel += 4;
            destination_pixel += 4;
        }

        source_row += 4 * pitch;
        destination_row += 4 * pitch;
    }

    return destination_row;
}

void CompositeTextureUploadState::render_composite_text(const char *text)
{
    int length = static_cast<int>(strlen(text));
    unsigned *intermediate = 0;

    if (render_via_intermediate_11d != 0) {
        intermediate = new unsigned[
            surface_height_148 * surface_pitch_dwords_150];
        memset(
            intermediate,
            0,
            4 * surface_height_148 * surface_pitch_dwords_150);
        surface_base_140 = intermediate;
    }

    begin_text_render();

    int offset = 0;
    while (length > offset) {
        const unsigned char lead =
            static_cast<unsigned char>(text[offset]);
        unsigned character_code;
        int character_width;
        if (lead >= 0x81 && lead < 0xff) {
            character_code =
                (static_cast<unsigned>(lead) << 8)
                | static_cast<unsigned char>(text[offset + 1]);
            character_width = 2;
        } else {
            character_code = static_cast<unsigned>(
                static_cast<int>(static_cast<signed char>(lead)));
            character_width = 1;
        }

        offset += character_width;
        if (character_code == 0) {
            length = 0;
        } else if (character_code == '<') {
            offset += parse_text_markup(text + offset);
        } else if (length >= offset) {
            draw_text_glyph(character_code);
        }
    }

    end_text_render();

    if (render_via_intermediate_11d != 0) {
        blend_intermediate_text_surface(
            intermediate,
            static_cast<unsigned *>(surface_cursor_144));
        delete[] intermediate;
    }
}

} // namespace th105
