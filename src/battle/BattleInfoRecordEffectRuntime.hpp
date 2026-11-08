#pragma once

#include "EffectManager.hpp"

namespace th105 {

struct BattleInfoEffectPosition {
    unsigned char reserved_00[0x0c];
    float x_0c;
    float y_10;
};

struct BattleInfoRecordEffectRuntimeView {
    unsigned char side_00;
    unsigned char reserved_01[0x13];
    CEffectManager<InfoEffectObject> *emitter_14;
    unsigned char reserved_18[0x48];
    BattleInfoEffectPosition *groups_60[5];

    void emit_group_effect_46f9f0(int effect_id, int group_index);
};

} // namespace th105
