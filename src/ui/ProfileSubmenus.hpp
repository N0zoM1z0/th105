#pragma once

#include "Menu.hpp"
#include "MenuCursor.hpp"
#include "GuideOverlay.hpp"
#include "Title.hpp"
#include "UiPrimitives.hpp"

namespace th105 {

class CProfileCharacterSelect : public Menu {
public:
    virtual ~CProfileCharacterSelect();
    virtual bool update();
    virtual void render();

private:
    unsigned texture_04;
    UiSprite94 stand_08;
    PlayerSlotRecord *player_9c;
    int character_a0;
    unsigned field_a4;
    UiSprite94 portrait_a8;
    TitleDesignResource design_13c;
    UiDesignObject *items_170[17];
    MenuCursorState column_1b4;
    MenuCursorState row_1c8;
    GuideOverlay guide_1dc;
    int item_count_284;
};

class CProfileKeyConfig : public Menu {
public:
    virtual ~CProfileKeyConfig();
    virtual bool update();
    virtual void render();

private:
    PlayerSlotRecord *player_04;
    TitleDesignResource design_08;
    unsigned texture_3c;
    UiTileA4 tile_40;
    unsigned texture_e4;
    UiTileA4 tile_e8;
    UiDesignObject *objects_18c[4];
    GuideOverlay guides_19c[2];
    signed char character_2ec;
    int keys_2f0[11];
    int field_31c;
    unsigned char alternate_320;
    int count_324;
    int state_328;
    int input_slot_32c;
};

typedef char CProfileCharacterSelect_size_must_be_0x288[
    sizeof(CProfileCharacterSelect) == 0x288 ? 1 : -1];
typedef char CProfileKeyConfig_size_must_be_0x330[
    sizeof(CProfileKeyConfig) == 0x330 ? 1 : -1];

} // namespace th105
