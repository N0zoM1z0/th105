#include "ui/SelectConstructor.hpp"
#include "ui/MenuCursor.hpp"
#include "engine/RenderModeManager.hpp"
#include <math.h>
namespace th105 {
extern "C" const int select_character_ids_61c8[];
void __cdecl draw_profile_overlay(unsigned char alpha);
struct SelectRenderEffectView {
    virtual void slot00(); virtual void slot04(); virtual void slot08();
    virtual void slot0c(); virtual void slot10(); virtual void slot14();
    virtual void render_side_18(int side);
};

bool CSelect::render()
{
    if (!g_render_mode_manager.begin_frame())
        return false;
    g_render_mode_manager.set_mode(2);
    background_2b8.render(0.0f, 0.0f);
    for (int i = 0; i < 16; ++i) {
        if (slots_5bc[i]->enabled) {
            g_render_mode_manager.draw_rect(slots_5bc[i]->x,
                static_cast<float>(slots_5bc[i]->y + 95.0),
                static_cast<float>(slots_5bc[i]->x + 47.0),
                static_cast<float>(slots_5bc[i]->y + 95.0 + 5.0), 0x60000000, 1);
        }
    }
    character_design_150.render_through(115);
    if (extra_textures_48c[0] && fields_090[0]) {
        extra_images_494[0].render(0.0f, 0.0f);
        reinterpret_cast<SelectRenderEffectView *>(selected_effects_1954[0])->render_side_18(0);
    }
    if (extra_textures_48c[1] && fields_090[1]) {
        extra_images_494[1].render(640.0f, 0.0f);
        reinterpret_cast<SelectRenderEffectView *>(selected_effects_1954[1])->render_side_18(1);
    }
    for (int player = 0; player < 2; ++player) {
        if (fields_090[player]) {
            MenuCursorState *cursor = character_cursors_100[player];
            int selected = cursor[0].selection + 4 * cursor[1].selection;
            cursor_images_18c[player].render(slots_5bc[selected]->x, slots_5bc[selected]->y);
            int character = select_character_ids_61c8[selected];
            if (character != 15)
                names_350.render(slots_5fc[player]->x, slots_5fc[player]->y, 0, character);
            else
                random_names_3f8.render(slots_5fc[player]->x, slots_5fc[player]->y);
        }
    }
    character_design_150.render_through(301);
    for (int player = 0; player < 2; ++player) {
        if (fields_090[player] && slots_604[player]->enabled)
            reinterpret_cast<UiDesignObject *>(slots_610[player])->render(
                static_cast<float>(slots_604[player]->x + 88.0),
                static_cast<float>(slots_604[player]->y + 10.0));
    }
    character_design_150.render();
    if (guide_mix_2d78) {
        draw_profile_overlay(guide_mix_2d78);
        g_render_mode_manager.draw_rect(0.0f,
            static_cast<float>(background_anchor_2cc4->y - 6.0),
            640.0f, static_cast<float>(background_anchor_2cc4->y + 80.0 - 6.0),
            (static_cast<unsigned>(guide_mix_2d78) << 23) | 0xFFFFFF, 1);
        background_design_1984.set_color(
            (static_cast<unsigned>(guide_mix_2d78) << 24) | 0xFFFFFF);
        for (int row = 0; row < 7; ++row) {
            float distance = static_cast<float>(row - 3 + static_cast<double>(field_2d80));
            distance = static_cast<float>(distance * 80.0);
            float picture_x = background_anchor_2cc4->x;
            float picture_y = background_anchor_2cc4->y + distance;
            float name_x = background_anchor_2cc8->x;
            float name_y = background_anchor_2cc8->y + distance;
            float music_x = music_anchor_2d74->x;
            float music_y = music_anchor_2d74->y + distance;
            int selected = (choice_count_094 + stage_cursor_195c.selection + row - 3) % choice_count_094;
            double alpha = (255.0 - static_cast<float>(fabs(distance))) *
                guide_mix_2d78 / 255.0;
            if (alpha < 0.0)
                alpha = 0.0;
            unsigned color = (static_cast<unsigned>(static_cast<unsigned char>(alpha)) << 24) | 0xFFFFFF;
            picture_images_1a38[selected].set_color(color);
            name_images_2378[selected].set_color(color);
            music_2cd0.set_color(color);
            picture_images_1a38[selected].render(picture_x, picture_y);
            name_images_2378[selected].render(name_x, name_y);
            int alternate = row == 3 && variant_cursor_1970.selection != 0 ? 1 : 0;
            music_2cd0.render(music_x, music_y, 0, selected + 15 * alternate);
        }
        double alpha = (1.0 - static_cast<float>(fabs(field_2d80))) * guide_mix_2d78;
        if (alpha < 0.0)
            alpha = 0.0;
        for (int i = 0; i < 3; ++i)
            slots_2cb8[i]->set_color((static_cast<unsigned>(static_cast<unsigned char>(alpha)) << 24) | 0xFFFFFF);
        background_design_1984.render();
    }
    g_render_mode_manager.set_mode(1);
    guides_2d88[0].render();
    guides_2d88[1].render();
    g_render_mode_manager.finish_frame();
    return true;
}
} // namespace th105
