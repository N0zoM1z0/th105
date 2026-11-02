#pragma once

#include "SpellData.hpp"
#include "engine/Sprite.hpp"

namespace th105 {

struct PlayerIndexedCallbackView {
    SpellDataOwner *spell_data_00;
    unsigned char unknown_004[0x94];
    CSprite display_sprite_098;
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

struct FighterSequenceSlot {
    short record_id_00;
    unsigned short field_02;
    CSprite sprite_04;
};

typedef char FighterSequenceSlot_size_must_be_0x98[
    sizeof(FighterSequenceSlot) == 0x98 ? 1 : -1];

} // namespace th105
