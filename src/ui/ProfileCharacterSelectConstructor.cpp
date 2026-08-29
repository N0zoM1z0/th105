#include "GuideOverlay.hpp"
#include "Menu.hpp"
#include "MenuCursor.hpp"
#include "Title.hpp"
#include "../input/InputManager.hpp"

#include <stddef.h>

extern "C" th105::CInputManager *g_active_menu_input;
extern "C" const char profile_character_select_design_path[];

namespace th105 {

struct PlayerSlotRecord;

struct ProfileCharacterSpriteColorBase {
    unsigned reserved_04;
    ProfileCharacterSpriteColorBase() : reserved_04(0) {}
};

class ProfileCharacterSprite94 : public ProfileCharacterSpriteColorBase {
public:
    ProfileCharacterSprite94() {}
    virtual ~ProfileCharacterSprite94();

private:
    unsigned char reserved_08[0x8c];
};

class ProfileCharacterDesignResource {
public:
    ProfileCharacterDesignResource();
    ~ProfileCharacterDesignResource();
    virtual void slot_00();
    virtual void slot_04();
    virtual void slot_08();
    virtual void slot_0c();
    virtual void load(const char *path);
    void bind_object_alt(UiDesignObject **result, int object_id);
private:
    unsigned char reserved_04[0x30];
};

typedef char ProfileCharacterDesignResource_size[
    sizeof(ProfileCharacterDesignResource) == 0x34 ? 1 : -1];

struct ScoreDataCharacterSelectView {
    unsigned unknown_00;
    int extended_roster_04;
};

ScoreDataCharacterSelectView *__cdecl get_score_data_for_character_select();

class CProfileCharacterSelectConstructorView : public Menu {
public:
    explicit CProfileCharacterSelectConstructorView(PlayerSlotRecord *player);
    virtual ~CProfileCharacterSelectConstructorView();
    virtual bool update();
    virtual void render();

    void refresh_character_preview_4484f0();

    unsigned texture_04;
    ProfileCharacterSprite94 stand_08;
    PlayerSlotRecord *player_9c;
    int character_a0;
    unsigned field_a4;
    ProfileCharacterSprite94 portrait_a8;
    ProfileCharacterDesignResource design_13c;
    UiDesignObject *items_170[17];
    MenuCursorState column_1b4;
    MenuCursorState row_1c8;
    GuideOverlay guide_1dc;
    int item_count_284;
};

CProfileCharacterSelectConstructorView::CProfileCharacterSelectConstructorView(
    PlayerSlotRecord *player)
    : texture_04(0),
      field_a4(0)
{
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
    refresh_character_preview_4484f0();
}

typedef char ProfileCharacterSprite94_size[
    sizeof(ProfileCharacterSprite94) == 0x94 ? 1 : -1];
typedef char CProfileCharacterSelectConstructorView_size[
    sizeof(CProfileCharacterSelectConstructorView) == 0x288 ? 1 : -1];
typedef char CProfileCharacterSelectConstructorView_stand[
    offsetof(CProfileCharacterSelectConstructorView, stand_08) == 0x08 ? 1 : -1];
typedef char CProfileCharacterSelectConstructorView_portrait[
    offsetof(CProfileCharacterSelectConstructorView, portrait_a8) == 0xa8 ? 1 : -1];
typedef char CProfileCharacterSelectConstructorView_design[
    offsetof(CProfileCharacterSelectConstructorView, design_13c) == 0x13c ? 1 : -1];
typedef char CProfileCharacterSelectConstructorView_guide[
    offsetof(CProfileCharacterSelectConstructorView, guide_1dc) == 0x1dc ? 1 : -1];

} // namespace th105
