#pragma once

#include <deque>
#include <map>

#include "Menu.hpp"
#include "MenuCursor.hpp"
#include "GuideOverlay.hpp"
#include "Title.hpp"
#include "../battle/EffectSprite.hpp"
#include "../battle/SpellData.hpp"

namespace th105 {

typedef std::map<unsigned short, signed char> ProfileDeckCountMap;
typedef std::deque<unsigned short> ProfileDeckKeyDeque;
typedef std::deque<SpellTreeIterator> ProfileDeckIteratorDeque;

// Current CProfileDeckEdit ctor/dtor and the CSprite copy families establish
// five real 32-bit extension values after the 0x80-byte CSpriteBase prefix.
// Keep them typed as float data without assigning speculative field names.
struct ProfileDeckSprite94 : CSpriteBase {
    float extension_80[5];
};

// CTile copy construction at 0x004396A0 independently copies nine float
// values at +0x80..+0xA0 after the same CSpriteBase prefix.
struct ProfileDeckTileA4 : CSpriteBase {
    float extension_80[9];
};

// Only the first 0x20 bytes of the current resource-owner teardown at
// 0x00433A80 are touched by CProfileDeckEdit. They are the observed
// DwordDeque4 + SpellTree pair and end immediately before counts_3c0.
struct ProfileDeckResourceGroup20 {
    DwordDeque4 handles_00;
    SpellTree tree_14;

    ~ProfileDeckResourceGroup20();
    void clear_resources();
};

// CProfileDeckEdit::~CProfileDeckEdit creates one one-byte local receiver and
// uses the same address for the two calls below. The callees do not require
// payload fields from this receiver.
struct ProfileDeckRefreshFacade {
    void clear_common_resources();
    unsigned char reload_common_resources(
        unsigned char red, unsigned char green, unsigned char blue);
};

class CProfileDeckEdit : public Menu {
public:
    virtual ~CProfileDeckEdit();
    virtual bool update();
    virtual void render();

    void import_deck_counts(const ProfileDeckKeyDeque &source);
    void export_deck_counts(ProfileDeckKeyDeque *destination);
    int available_count_for_index_448df0(int index);

private:
    PlayerSlotRecord *player_04;
    int character_08;
    int mode_0c;
    TitleDesignResource design_10;
    UiDesignObject *objects_44[20];
    unsigned texture_94;
    ProfileDeckSprite94 sprite_98;
    unsigned field_12c;
    ProfileDeckSprite94 sprite_130;
    ProfileDeckSprite94 sprite_1c4;
    unsigned texture_258;
    ProfileDeckTileA4 tile_25c;
    unsigned texture_300;
    ProfileDeckSprite94 sprite_304;
    ProfileDeckResourceGroup20 resources_398;
    SpellTree *local_tree_3b8;
    SpellTree *common_tree_3bc;
    ProfileDeckCountMap counts_3c0;
    ProfileDeckIteratorDeque filtered_3cc;
    unsigned char color_3e0;
    unsigned char total_3e1;
    MenuCursorState cursor_3e4;
    MenuCursorState cursor_3f8;
    unsigned char flags_40c[4];
    GuideOverlay guides_410[4];
};

typedef char ProfileDeckSprite94_size_must_be_0x94[
    sizeof(ProfileDeckSprite94) == 0x94 ? 1 : -1];
typedef char ProfileDeckTileA4_size_must_be_0xa4[
    sizeof(ProfileDeckTileA4) == 0xA4 ? 1 : -1];
typedef char ProfileDeckResourceGroup20_size_must_be_0x20[
    sizeof(ProfileDeckResourceGroup20) == 0x20 ? 1 : -1];
typedef char CProfileDeckEdit_size_must_be_0x6b0[
    sizeof(CProfileDeckEdit) == 0x6B0 ? 1 : -1];

} // namespace th105
