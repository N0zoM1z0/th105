#include "ProfileSubmenus.hpp"
#include "GuideOverlay.hpp"
#include "Menu.hpp"
#include "MenuCursor.hpp"
#include "Title.hpp"
#include "DesignBaseLifetime.hpp"
#include "../input/InputManager.hpp"

#include <stddef.h>

extern "C" th105::CInputManager *g_active_menu_input;
extern "C" const char profile_character_select_design_path[];

namespace th105 {

struct PlayerSlotRecord;

struct ScoreDataCharacterSelectView {
    unsigned unknown_00;
    int extended_roster_04;
};

ScoreDataCharacterSelectView *__cdecl get_score_data_for_character_select();

CProfileCharacterSelect::CProfileCharacterSelect(
    PlayerSlotRecord *player)
    : texture_04(0),
      field_a4(0)
{
    typedef char CSprite_size[
        sizeof(CSprite) == 0x94 ? 1 : -1];
    typedef char CProfileCharacterSelect_size[
        sizeof(CProfileCharacterSelect) == 0x288 ? 1 : -1];
    typedef char CProfileCharacterSelect_stand[
        offsetof(CProfileCharacterSelect, stand_08) == 0x08 ? 1 : -1];
    typedef char CProfileCharacterSelect_portrait[
        offsetof(CProfileCharacterSelect, portrait_a8) == 0xa8 ? 1 : -1];
    typedef char CProfileCharacterSelect_design[
        offsetof(CProfileCharacterSelect, design_13c) == 0x13c ? 1 : -1];
    typedef char CProfileCharacterSelect_guide[
        offsetof(CProfileCharacterSelect, guide_1dc) == 0x1dc ? 1 : -1];
    typedef char CProfileCharacterSelect_column[
        offsetof(CProfileCharacterSelect, column_1b4) == 0x1b4 ? 1 : -1];
    typedef char CProfileCharacterSelect_row[
        offsetof(CProfileCharacterSelect, row_1c8) == 0x1c8 ? 1 : -1];

    player_9c = player;
    design_13c.load(profile_character_select_design_path);

    if (get_score_data_for_character_select()->extended_roster_04 != 0) {
        for (int i = 0; i < 16; ++i) {
            design_13c.bind_object_alt(&items_170[i], 100 + i);
            items_170[i]->enabled = true;
        }

        CInputManager *input = g_active_menu_input;
        if (input != 0)
            column_1b4.input_counter = &input->hold.horizontal;
        else
            column_1b4.input_counter = 0;
        column_1b4.selection = 0;
        column_1b4.window_start = 0;
        column_1b4.item_count = 2;
        column_1b4.page_size = 0;

        if (input != 0)
            row_1c8.input_counter = &input->hold.vertical;
        else
            row_1c8.input_counter = 0;
        row_1c8.selection = 0;
        row_1c8.window_start = 0;
        row_1c8.item_count = 9;
        row_1c8.page_size = 0;
        item_count_284 = 8;
    } else {
        for (int i = 0; i < 13; ++i) {
            design_13c.bind_object_alt(&items_170[i], 100 + i);
            items_170[i]->enabled = true;
        }
        design_13c.bind_object_alt(&items_170[13], 115);
        items_170[13]->enabled = true;

        CInputManager *input = g_active_menu_input;
        if (input != 0)
            column_1b4.input_counter = &input->hold.horizontal;
        else
            column_1b4.input_counter = 0;
        column_1b4.selection = 0;
        column_1b4.window_start = 0;
        column_1b4.item_count = 2;
        column_1b4.page_size = 0;

        if (input != 0)
            row_1c8.input_counter = &input->hold.vertical;
        else
            row_1c8.input_counter = 0;
        row_1c8.selection = 0;
        row_1c8.window_start = 0;
        row_1c8.item_count = 8;
        row_1c8.page_size = 0;
        item_count_284 = 7;
    }

    items_170[0]->enabled = true;
    guide_1dc.load(12);
    guide_1dc.visible = true;
    character_a0 = 0;
    refresh_character_preview();
}

} // namespace th105
