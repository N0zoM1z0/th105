#pragma once

#include "Menu.hpp"
#include "MenuCursor.hpp"
#include "GuideOverlay.hpp"
#include "Title.hpp"
#include "DesignBaseLifetime.hpp"
#include "Tile.hpp"
#include "UiPrimitives.hpp"

namespace th105 {

class CProfileCharacterSelect : public Menu {
public:
    explicit CProfileCharacterSelect(PlayerSlotRecord *player);
    virtual ~CProfileCharacterSelect();
    virtual bool update();
    virtual void render();

private:
    void refresh_character_preview();
    DesignTextureHandle texture_04;
    CSprite stand_08;
    PlayerSlotRecord *player_9c;
    int character_a0;
    unsigned field_a4;
    CSprite portrait_a8;
    CDesignBase design_13c;
    UiDesignObject *items_170[17];
    MenuCursorState column_1b4;
    MenuCursorState row_1c8;
    GuideOverlay guide_1dc;
    int item_count_284;
};

class CProfileKeyConfig : public Menu {
public:
    CProfileKeyConfig(PlayerSlotRecord *player, int input_slot);
    virtual ~CProfileKeyConfig();
    virtual bool update();
    virtual void render();

private:
    bool capture_key_input();
    PlayerSlotRecord *player_04;
    CDesignBase design_08;
    DesignTextureHandle texture_3c;
    CTile tile_40;
    DesignTextureHandle texture_e4;
    CTile tile_e8;
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
