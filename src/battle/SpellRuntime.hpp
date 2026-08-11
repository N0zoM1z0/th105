#pragma once

#include "SpellData.hpp"

namespace th105 {

struct SpellDisplaySpriteView {
    virtual void unknown_00();
    virtual void unknown_04();
    virtual void unknown_08();
    virtual void unknown_0c();
    virtual void configure_record_display(
        void *batch_resource,
        int zero,
        int record_value,
        int width,
        int height,
        int vertical_offset,
        int mode);
};

struct PlayerIndexedCallbackView {
    SpellDataOwner *spell_data_00;
    unsigned char unknown_004[0x94];
    SpellDisplaySpriteView display_sprite_098;
    unsigned char unknown_09c[0x90];
    void *source_12c;
    unsigned char color_130;
    unsigned char intensity_131;
    unsigned char alternate_alignment_132;
    unsigned char unknown_133;
    float angle_start_134;
    float angle_end_138;
    float angle_step_13c;
    float width_scale_140;
    float height_scale_144;
    unsigned char unknown_148[4];
    unsigned char active_14c;
    unsigned char unknown_14d[3];
    int source_token_150;

    void invoke_indexed_record(int record_id, int source_token);
};

typedef char PlayerIndexedCallbackView_size_must_be_0x154[
    sizeof(PlayerIndexedCallbackView) == 0x154 ? 1 : -1];

struct SpellSpriteWork {
    void *vtable_00;
    unsigned char unknown_04[0x90];

    void load_optional_spell_resource(
        void *resource,
        int zero0,
        int zero1,
        void *global_a,
        void *global_b);
};

struct FighterSequenceSlot {
    short record_id_00;
    unsigned short field_02;
    SpellSpriteWork sprite_04;
};

typedef char FighterSequenceSlot_size_must_be_0x98[
    sizeof(FighterSequenceSlot) == 0x98 ? 1 : -1];

} // namespace th105
