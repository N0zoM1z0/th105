// Complete native character-selection policy; cursor-base scheduling remains nonexact.
#include "ui/SelectConstructor.hpp"
#include "ui/MenuCursor.hpp"
#include "battle/GameMode.hpp"
#include <stddef.h>

namespace th105 {
void __cdecl dispatch_indexed_event(unsigned index);
int __cdecl selector_random_roll(int count);
unsigned __cdecl prepare_select_match_43ac60(int unused);
void __cdecl prepare_scenario_match(int player);
void __cdecl fade_bgm(int duration, int target);
extern "C" const int select_character_ids_61c8[];

int CSelect::update_characters_41fc90()
{
    bool cancelled[2] = {false, false};
    for (int i = 0; i < 2; ++i) {
        if (inputs_010[i]) {
            if (fields_7f8[i] == 1) {
                if (inputs_010[i]->hold_38[3] == 1) {
                    dispatch_indexed_event(41);
                    fields_7f8[i] = 0;
                }
            } else {
                unsigned char moved = static_cast<unsigned char>(
                    character_cursors_100[i][0].update() | (character_cursors_100[i][1].update() << 1));
                if (moved) {
                    if (locked_093) {
                        while ((character_cursors_100[i][0].selection == 1 || character_cursors_100[i][0].selection == 2) &&
                               character_cursors_100[i][1].selection == 3) {
                            character_cursors_100[i][0].update();
                            character_cursors_100[i][1].update();
                        }
                    }
                    dispatch_indexed_event(39);
                    signed char selected = static_cast<signed char>(
                        character_cursors_100[i][0].selection + 4 * character_cursors_100[i][1].selection);
                    if (selected >= 15)
                        setup_00c->sides_08[i].character_key_00 = 15;
                    else
                        setup_00c->sides_08[i].character_key_00 = select_character_ids_61c8[selected];
                    bind_character(i, setup_00c->sides_08[i].character_key_00);
                } else if (inputs_010[i]->hold_38[2] == 1) {
                    dispatch_indexed_event(40);
                    setup_00c->sides_08[i].fighter_option_05 =
                        static_cast<unsigned>(inputs_010[i]->hold_38[5]) > 0u;
                    fields_7f8[i] = 1;
                } else if (inputs_010[i]->hold_38[3] == 1) {
                    dispatch_indexed_event(41);
                    cancelled[i] = true;
                }
            }
        }
    }
    if (static_cast<int>(get_game_mode()) == 0) {
        if (fields_7f8[0] == 1) {
            prepare_scenario_match(0);
            fade_bgm(1000, 0);
            return 6;
        }
        if (cancelled[0])
            return 2;
    } else if (get_game_mode() == GAME_MODE_VS_COM) {
        if (fields_7f8[0] == 1) {
            if (setup_00c->sides_08[0].character_key_00 == 15) {
                if (locked_093)
                    setup_00c->sides_08[0].character_key_00 = selector_random_roll(13);
                else
                    setup_00c->sides_08[0].character_key_00 = selector_random_roll(15);
                setup_00c->random_4c[0] = 1;
            } else {
                setup_00c->random_4c[0] = 0;
            }
            prepare_select_match_43ac60(0);
            fade_bgm(1000, 0);
            return 6;
        }
        if (cancelled[0])
            return 2;
    } else {
        if (fields_7f8[0] == 1 && fields_7f8[1] == 1) {
            state_008 = 1;
            return 3;
        }
        if (cancelled[0] || (cancelled[1] && inputs_010[0] != inputs_010[1]))
            return 2;
    }
    return 3;
}
} // namespace th105
