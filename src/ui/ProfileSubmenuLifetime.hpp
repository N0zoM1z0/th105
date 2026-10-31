// Destructor-facing actual polymorphic members; runtime/constructor views remain unchanged.
#include "ui/CNumberLifetime.hpp"
#pragma once

#include "ui/Menu.hpp"
#include "ui/MenuCursor.hpp"
#include "ui/GuideOverlay.hpp"
#include "ui/Title.hpp"
#include "ui/UiPrimitives.hpp"

namespace th105 {



class CProfileCharacterSelectLifetime : public Menu {
public:
    explicit CProfileCharacterSelectLifetime(PlayerSlotRecord *player);
    virtual ~CProfileCharacterSelectLifetime();
    virtual bool update();
    virtual void render();

private:
    unsigned texture_04;
    UiSpriteLifetime94 stand_08;
    PlayerSlotRecord *player_9c;
    int character_a0;
    unsigned field_a4;
    UiSpriteLifetime94 portrait_a8;
    TitleDesignResource design_13c;
    UiDesignObject *items_170[17];
    MenuCursorState column_1b4;
    MenuCursorState row_1c8;
    GuideOverlay guide_1dc;
    int item_count_284;
};

class CProfileKeyConfigLifetime : public Menu {
public:
    CProfileKeyConfigLifetime(PlayerSlotRecord *player, int input_slot);
    virtual ~CProfileKeyConfigLifetime();
    virtual bool update();
    virtual void render();

private:
    PlayerSlotRecord *player_04;
    TitleDesignResource design_08;
    unsigned texture_3c;
    CNumberTileLifetime tile_40;
    unsigned texture_e4;
    CNumberTileLifetime tile_e8;
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

typedef char CProfileCharacterSelectLifetime_size_must_be_0x288[
    sizeof(CProfileCharacterSelectLifetime) == 0x288 ? 1 : -1];
typedef char CProfileKeyConfigLifetime_size_must_be_0x330[
    sizeof(CProfileKeyConfigLifetime) == 0x330 ? 1 : -1];

} // namespace th105
