#pragma once

namespace th105 {

struct FighterCutinSpriteWork {
    virtual void slot_00();
    virtual void slot_04();
    virtual void slot_08();
    virtual void slot_0c();
    virtual void slot_10();
    virtual void configure_texture(
        unsigned handle,
        int zero0,
        int zero1,
        unsigned first_extent,
        unsigned second_extent);

    unsigned char unknown_04[0x84];
    float field_88;
    float field_8c;
    unsigned char unknown_90[0x04];
};

struct FighterCutinResource {
    unsigned handle_00;
    FighterCutinSpriteWork sprite_04;
    int selector_98;
    int state_9c;

    void load_for_character(int character_key, int selector);
};

struct FighterFaceResource {
    unsigned handle_00;
    FighterCutinSpriteWork sprite_04;
};

typedef char CheckFighterCutinResourceSize[
    sizeof(FighterCutinResource) == 0xa0 ? 1 : -1];
typedef char CheckFighterCutinSpriteWorkSize[
    sizeof(FighterCutinSpriteWork) == 0x94 ? 1 : -1];
typedef char CheckFighterFaceResourceSize[
    sizeof(FighterFaceResource) == 0x98 ? 1 : -1];

} // namespace th105
