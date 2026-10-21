// JP1.06a font entry412670. Ordinary COFF remains nonexact; provider/TU closure
// is still required to reproduce its aligned frame and private call entries.
#include "TextFontRuntime.hpp"

#include <new>
#include <string.h>

struct HWND__;

namespace th105 {

extern HWND__ *g_main_window;
extern "C" __declspec(dllimport) void *__stdcall SelectObject(void *, void *);
extern "C" __declspec(dllimport) int __stdcall DeleteObject(void *);
extern "C" __declspec(dllimport) int __stdcall ReleaseDC(HWND__ *, void *);

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
    begin_text_render();

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
