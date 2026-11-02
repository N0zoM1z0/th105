// KeyConfig lifetime view; CharacterSelect uses the shared actual owner.
#include "ui/CNumberLifetime.hpp"
#pragma once

#include "ui/Menu.hpp"
#include "ui/ProfileSubmenus.hpp"
#include "ui/MenuCursor.hpp"
#include "ui/GuideOverlay.hpp"
#include "ui/Title.hpp"
#include "ui/UiPrimitives.hpp"

namespace th105 {

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

typedef char CProfileKeyConfigLifetime_size_must_be_0x330[
    sizeof(CProfileKeyConfigLifetime) == 0x330 ? 1 : -1];

} // namespace th105
