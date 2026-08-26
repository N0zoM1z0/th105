#include "InfoComboRuntime.hpp"
#include "Collision.hpp"
#include "../engine/RenderModeManager.hpp"

namespace th105 {

float __cdecl lookup_orientation_cosine(int angle);

void InfoShortRecord34Runtime::render_46a800()
{
    if (progress_18 == 0)
        return;

    float render_x = fighter_04->player_index_334 == 0
        ? 0.0f - x_08
        : x_08 + 520.0f;
    y_0c = 0.0f;

    unsigned char alpha = 0xff;
    if (progress_18 < 30)
        alpha = static_cast<unsigned char>(progress_18 * 255 / 30);

    g_render_mode_manager.set_blend_mode(1);
    combo_00->set_color_04(
        (static_cast<unsigned>(alpha) << 24) | 0x00ffffff);
    combo_00->render_combo_46a660(render_x, y_0c, fighter_04, &entries_20);
}

void InfoShortRecord34Runtime::update_46ac30()
{
    int current = fighter_04->value_498;
    if (current != previous_value_10) {
        previous_value_10 = current;
        if (current >= 2)
            progress_18 = 180;

        if (fighter_04->flag_491 > active_mask_1c) {
            for (int i = 0; i < 6; ++i) {
                if (((fighter_04->flag_491 - active_mask_1c) & (1 << i)) != 0) {
                    InfoComboEntry entry;
                    entry.value_00 = 0.0f;
                    entry.timer_04 = 10;
                    entry.item_index_08 = static_cast<unsigned char>(i);
                    entries_20.push_back(entry);
                }
            }
            active_mask_1c = fighter_04->flag_491;
        }
    }

    if (progress_18 == 0)
        return;

    --progress_18;
    if (timer_14 != 0) {
        x_08 =
            (1.0f - lookup_orientation_cosine(timer_14 * 9)) * 300.0f;
        --timer_14;
    } else {
        x_08 = 0.0f;
    }

    for (std::deque<InfoComboEntry>::iterator it = entries_20.begin();
         it != entries_20.end(); ++it) {
        if (it->timer_04 != 0) {
            --it->timer_04;
            if (fighter_04->player_index_334 == 0) {
                it->value_00 =
                    (1.0f - lookup_orientation_cosine(it->timer_04 * 9)) *
                    -300.0f;
            } else {
                it->value_00 =
                    (1.0f - lookup_orientation_cosine(it->timer_04 * 9)) *
                    300.0f;
            }
        }
    }
}

} // namespace th105
