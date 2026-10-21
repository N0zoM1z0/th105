// Native font owner411430 hypothesis from complete JP1.06a target evidence.
// Original nominal class/TU spelling remains unknown.
#include <list>
#include <string>
#include <stddef.h>

namespace th105 {
struct TextFontConfig128 {
    char face_000[256];
    unsigned char colors_100[6];
    int height_108;
    int weight_10c;
    unsigned char italic_110;
    unsigned char outline_111;
    unsigned char wrap_112;
    int unknown_114;
    int origin_x_118;
    int origin_y_11c;
    int spacing_x_120;
    int spacing_y_124;

    TextFontConfig128()
    {
        weight_10c = 400;
        italic_110 = 0;
        outline_111 = 0;
        wrap_112 = 0;
        spacing_x_120 = 0;
        spacing_y_124 = 0;
        origin_x_118 = 0;
        origin_y_11c = 0;
        unknown_114 = 100000;
    }
};
struct TextFontOwner194 {
    void *dc_000;
    void *font_004;
    void *old_font_008;
    TextFontConfig128 config_00c;
    int cursor_x_134;
    int cursor_y_138;
    int ascent_13c;
    void *surface_base_140;
    void *surface_destination_144;
    unsigned height_148;
    unsigned width_14c;
    int pitch_150;
    unsigned *active_color_154;
    unsigned *base_color_158;
    std::list<unsigned *> temporary_colors_15c;
    unsigned fallback_color_168;
    unsigned char accent_16c;
    unsigned char unknown_flag_16d;
    std::string text_170;
    int saved_x_18c;
    int saved_y_190;

    TextFontOwner194();
    ~TextFontOwner194();
    void configure(const TextFontConfig128 *config);
};
TextFontOwner194::TextFontOwner194()
{
    dc_000 = 0;
    font_004 = 0;
    old_font_008 = 0;
    surface_destination_144 = 0;
    active_color_154 = 0;
    base_color_158 = 0;
}
TextFontOwner194::~TextFontOwner194()
{
    while (!temporary_colors_15c.empty()) {
        delete[] temporary_colors_15c.front();
        temporary_colors_15c.pop_front();
    }
    if (base_color_158) {
        delete[] base_color_158;
        base_color_158 = 0;
    }
}
void TextFontOwner194::configure(const TextFontConfig128 *config)
{
    config_00c = *config;
    if (config_00c.colors_100[0] == config_00c.colors_100[1] &&
        config_00c.colors_100[2] == config_00c.colors_100[3] &&
        config_00c.colors_100[4] == config_00c.colors_100[5]) {
        fallback_color_168 = (config_00c.colors_100[0] << 16) |
            (config_00c.colors_100[2] << 8) | config_00c.colors_100[4];
    } else {
        if (base_color_158)
            delete[] base_color_158;
        base_color_158 = new unsigned[config_00c.height_108];
        int last = config_00c.height_108 - 1;
        for (int y = 0; y <= last; ++y) {
            base_color_158[y] =
                (((config_00c.colors_100[1] - config_00c.colors_100[0]) * y / last +
                  config_00c.colors_100[0]) << 16) |
                (((config_00c.colors_100[3] - config_00c.colors_100[2]) * y / last +
                  config_00c.colors_100[2]) << 8) |
                ((config_00c.colors_100[5] - config_00c.colors_100[4]) * y / last +
                  config_00c.colors_100[4]);
        }
        active_color_154 = base_color_158;
    }
    while (!temporary_colors_15c.empty()) {
        delete[] temporary_colors_15c.front();
        temporary_colors_15c.pop_front();
    }
}

typedef char ConfigSize[sizeof(TextFontConfig128) == 0x128 ? 1 : -1];
typedef char OwnerSize[sizeof(TextFontOwner194) == 0x194 ? 1 : -1];
typedef char ConfigOffset[offsetof(TextFontOwner194, config_00c) == 0x00c ? 1 : -1];
typedef char ListOffset[offsetof(TextFontOwner194, temporary_colors_15c) == 0x15c ? 1 : -1];
typedef char TextOffset[offsetof(TextFontOwner194, text_170) == 0x170 ? 1 : -1];
}
