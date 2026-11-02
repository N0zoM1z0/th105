// Complete native character-selection policy; cursor-base scheduling remains nonexact.
#include "input/InputManager.hpp"
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

struct SelectCharacterSetupView : MatchSetup {
    unsigned char random_character_4c[2];
};
struct SelectCharacterCursorPair {
    MenuCursorState horizontal;
    MenuCursorState vertical;
};
// Offset-constrained views only; never instantiated or allocated here.
struct SelectCharacterUpdateView {
    unsigned char unknown_000[8];
    int state_008;
    SelectCharacterSetupView *setup_00c;
    CInputManager *inputs_010[2];
    unsigned char unknown_018[0x93-0x18];
    bool locked_093;
    unsigned char unknown_094[0x100-0x94];
    SelectCharacterCursorPair cursors_100[2];
    unsigned char unknown_150[0x7f8-0x150];
    unsigned char confirmed_7f8[2];
    int update_characters_41fc90();
    void refresh_character_41fb80(int player, int character);
};
typedef char character_setup_random_offset[offsetof(SelectCharacterSetupView,random_character_4c)==0x4c?1:-1];
typedef char character_input_pointer_offset[offsetof(SelectCharacterUpdateView,inputs_010)==0x10?1:-1];
typedef char character_lock_offset[offsetof(SelectCharacterUpdateView,locked_093)==0x93?1:-1];
typedef char character_cursor_pair_size[sizeof(SelectCharacterCursorPair)==0x28?1:-1];
typedef char character_cursors_offset[offsetof(SelectCharacterUpdateView,cursors_100)==0x100?1:-1];
typedef char character_flags_offset[offsetof(SelectCharacterUpdateView,confirmed_7f8)==0x7f8?1:-1];

int SelectCharacterUpdateView::update_characters_41fc90()
{
    bool cancelled[2] = {false, false};
    for (int i = 0; i < 2; ++i) {
        if (inputs_010[i]) {
            if (confirmed_7f8[i] == 1) {
                if (inputs_010[i]->hold.buttons[1] == 1) {
                    dispatch_indexed_event(41);
                    confirmed_7f8[i] = 0;
                }
            } else {
                unsigned char moved = static_cast<unsigned char>(
                    cursors_100[i].horizontal.update() | (cursors_100[i].vertical.update() << 1));
                if (moved) {
                    if (locked_093) {
                        while ((cursors_100[i].horizontal.selection == 1 || cursors_100[i].horizontal.selection == 2) &&
                               cursors_100[i].vertical.selection == 3) {
                            cursors_100[i].horizontal.update();
                            cursors_100[i].vertical.update();
                        }
                    }
                    dispatch_indexed_event(39);
                    signed char selected = static_cast<signed char>(
                        cursors_100[i].horizontal.selection + 4 * cursors_100[i].vertical.selection);
                    if (selected >= 15)
                        setup_00c->sides_08[i].character_key_00 = 15;
                    else
                        setup_00c->sides_08[i].character_key_00 = select_character_ids_61c8[selected];
                    refresh_character_41fb80(i, setup_00c->sides_08[i].character_key_00);
                } else if (inputs_010[i]->hold.buttons[0] == 1) {
                    dispatch_indexed_event(40);
                    setup_00c->sides_08[i].fighter_option_05 =
                        static_cast<unsigned>(inputs_010[i]->hold.buttons[3]) > 0u;
                    confirmed_7f8[i] = 1;
                } else if (inputs_010[i]->hold.buttons[1] == 1) {
                    dispatch_indexed_event(41);
                    cancelled[i] = true;
                }
            }
        }
    }
    if (static_cast<int>(get_game_mode()) == 0) {
        if (confirmed_7f8[0] == 1) {
            prepare_scenario_match(0);
            fade_bgm(1000, 0);
            return 6;
        }
        if (cancelled[0])
            return 2;
    } else if (get_game_mode() == GAME_MODE_VS_COM) {
        if (confirmed_7f8[0] == 1) {
            if (setup_00c->sides_08[0].character_key_00 == 15) {
                if (locked_093)
                    setup_00c->sides_08[0].character_key_00 = selector_random_roll(13);
                else
                    setup_00c->sides_08[0].character_key_00 = selector_random_roll(15);
                setup_00c->random_character_4c[0] = 1;
            } else {
                setup_00c->random_character_4c[0] = 0;
            }
            prepare_select_match_43ac60(0);
            fade_bgm(1000, 0);
            return 6;
        }
        if (cancelled[0])
            return 2;
    } else {
        if (confirmed_7f8[0] == 1 && confirmed_7f8[1] == 1) {
            state_008 = 1;
            return 3;
        }
        if (cancelled[0] || (cancelled[1] && inputs_010[0] != inputs_010[1]))
            return 2;
    }
    return 3;
}
} // namespace th105
