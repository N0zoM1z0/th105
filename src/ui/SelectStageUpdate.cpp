#include "input/InputManager.hpp"
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

struct SelectStagePlayerView {
    int character;
    unsigned char unknown_04[0x1c];
};
// Read/write partial views, never constructed or allocated here.
struct SelectStageSetupView {
    int mode_00;
    signed char stage_04, bgm_05;
    unsigned char unknown_06[2];
    SelectStagePlayerView players_08[2];
    unsigned char unknown_48[4];
    unsigned char random_character_4c[2];
    unsigned char random_stage_4e;
};
struct SelectStageUpdateView {
    unsigned char unknown_000[8];
    int state_008;
    SelectStageSetupView *setup_00c;
    unsigned char unknown_010[8];
    CInputManager input_018;
    unsigned char unknown_078[0x1b];
    bool locked_093;
    int choice_count_094;
    std::vector<int> choices_098, variants_0a8, extras_0b8;
    unsigned char unknown_0c8[0x7f8-0xc8];
    unsigned char selection_flags_7f8[2];
    unsigned char unknown_7fa[0x195c-0x7fa];
    MenuCursorState stage_cursor_195c;
    MenuCursorState variant_cursor_1970;
    unsigned char unknown_1984[0x2cc0-0x1984];
    UiDesignObject *variant_label_2cc0;
    unsigned char unknown_2cc4[0x2d7c-0x2cc4];
    int transition_ticks_2d7c;
    float transition_2d80, transition_origin_2d84;
    int update_stage_420560();
};
typedef char stage_cursor_offset[offsetof(SelectStageUpdateView,stage_cursor_195c)==0x195c?1:-1];
typedef char stage_label_offset[offsetof(SelectStageUpdateView,variant_label_2cc0)==0x2cc0?1:-1];
typedef char stage_transition_offset[offsetof(SelectStageUpdateView,transition_2d80)==0x2d80?1:-1];

int SelectStageUpdateView::update_stage_420560()
{
    input_018.update_player_input_counters_from_raw();
    if (extras_0b8[stage_cursor_195c.selection] >= 0) {
        variant_label_2cc0->enabled = true;
        if (variant_cursor_1970.update())
            dispatch_indexed_event(39);
    } else {
        variant_label_2cc0->enabled = false;
    }
    if (stage_cursor_195c.update()) {
        dispatch_indexed_event(39);
        variant_cursor_1970.selection = 0;
        transition_ticks_2d7c = 10;
        if (input_018.hold.vertical > 0) {
            transition_2d80 = static_cast<float>(transition_2d80 + 1.0);
            transition_origin_2d84 = transition_2d80;
        } else {
            transition_2d80 = static_cast<float>(transition_2d80 - 1.0);
            transition_origin_2d84 = transition_2d80;
        }
        return 3;
    }
    if (input_018.hold.buttons[0] == 1) {
        if (stage_cursor_195c.selection)
            setup_00c->random_stage_4e = 0;
        else
            setup_00c->random_stage_4e = 1;
        for (int i = 0; i < 2; ++i) {
            if (setup_00c->players_08[i].character == 15) {
                if (locked_093)
                    setup_00c->players_08[i].character = selector_random_roll(13);
                else
                    setup_00c->players_08[i].character = selector_random_roll(15);
                setup_00c->random_character_4c[i] = 1;
            } else {
                setup_00c->random_character_4c[i] = 0;
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
        if (setup_00c->players_08[0].character == 6 || setup_00c->players_08[1].character == 6) {
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
    if (input_018.hold.buttons[1] == 1) {
        dispatch_indexed_event(41);
        state_008 = 0;
        selection_flags_7f8[1] = 0;
        selection_flags_7f8[0] = 0;
    }
    return 3;
}
} // namespace th105
