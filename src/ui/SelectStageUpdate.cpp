#include "ui/SelectConstructor.hpp"
#include "ui/MenuCursor.hpp"
#include "ui/UiPrimitives.hpp"
#include <vector>
#include <stddef.h>

namespace th105 {
void __cdecl dispatch_indexed_event(unsigned index);
int __cdecl selector_random_roll(int count);
// This caller pushes one ignored zero argument; the established cdecl body
// returns an unsigned value which this caller discards.
unsigned __cdecl prepare_select_match_43ac60(int unused);
void __cdecl fade_bgm(int duration, int target);

int CSelect::update_stage_420560()
{
    input_018.update_player_input_counters_from_raw();
    if (extras_0b8[stage_cursor_195c.selection] >= 0) {
        slots_2cb8[2]->enabled = true;
        if (variant_cursor_1970.update())
            dispatch_indexed_event(39);
    } else {
        slots_2cb8[2]->enabled = false;
    }
    if (stage_cursor_195c.update()) {
        dispatch_indexed_event(39);
        variant_cursor_1970.selection = 0;
        field_2d7c = 10;
        if (input_018.counters[1] > 0) {
            field_2d80 = static_cast<float>(field_2d80 + 1.0);
            field_2d84 = field_2d80;
        } else {
            field_2d80 = static_cast<float>(field_2d80 - 1.0);
            field_2d84 = field_2d80;
        }
        return 3;
    }
    if (input_018.counters[2] == 1) {
        if (stage_cursor_195c.selection)
            setup_00c->random_4c[2] = 0;
        else
            setup_00c->random_4c[2] = 1;
        for (int i = 0; i < 2; ++i) {
            if (setup_00c->sides_08[i].character_key_00 == 15) {
                if (locked_093)
                    setup_00c->sides_08[i].character_key_00 = selector_random_roll(13);
                else
                    setup_00c->sides_08[i].character_key_00 = selector_random_roll(15);
                setup_00c->random_4c[i] = 1;
            } else {
                setup_00c->random_4c[i] = 0;
            }
        }
        if (stage_cursor_195c.selection) {
            setup_00c->stage_04 = static_cast<signed char>(choices_098[stage_cursor_195c.selection]);
            if (variant_cursor_1970.selection)
                setup_00c->bgm_05 = static_cast<signed char>(extras_0b8[stage_cursor_195c.selection]);
            else
                setup_00c->bgm_05 = static_cast<signed char>(variants_0a8[stage_cursor_195c.selection]);
        } else {
            unsigned index = selector_random_roll(choice_count_094 - 1) + 1;
            setup_00c->stage_04 = static_cast<signed char>(choices_098[index]);
            setup_00c->bgm_05 = static_cast<signed char>(variants_0a8[index]);
            if (extras_0b8[index] >= 0 && selector_random_roll(2))
                setup_00c->bgm_05 = static_cast<signed char>(extras_0b8[index]);
        }
        if (setup_00c->sides_08[0].character_key_00 == 6 || setup_00c->sides_08[1].character_key_00 == 6) {
            if (setup_00c->stage_04 != 14 && setup_00c->stage_04 != 16) {
                if (selector_random_roll(2))
                    setup_00c->stage_04 = 14;
                else
                    setup_00c->stage_04 = 16;
            }
        }
        dispatch_indexed_event(40);
        prepare_select_match_43ac60(0);
        fade_bgm(1000, 0);
        return 6;
    }
    if (input_018.counters[3] == 1) {
        dispatch_indexed_event(41);
        state_008 = 0;
        fields_7f8[1] = 0;
        fields_7f8[0] = 0;
    }
    return 3;
}
} // namespace th105
