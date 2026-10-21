// Native JP1.06a font owner: canonical lifecycle/configuration source.
#include "TextFontOwner.hpp"

namespace th105 {
TextFontOwner194::TextFontOwner194()
{
    dc_000 = 0;
    font_004 = 0;
    old_font_008 = 0;
    surface_cursor_144 = 0;
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

}
