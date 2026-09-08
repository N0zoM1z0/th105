#include "InfoEffectEmitter.hpp"

#include <stddef.h>

namespace th105 {

struct BattleInfoEffectPosition {
    unsigned char reserved_00[0x0c];
    float x_0c;
    float y_10;
};

struct BattleInfoRecordEffectRuntimeView {
    unsigned char side_00;
    unsigned char reserved_01[0x13];
    EffectEmitterSubobject *emitter_14;
    unsigned char reserved_18[0x48];
    BattleInfoEffectPosition *groups_60[1];

    void emit_group_effect_46f9f0(int effect_id, int group_index);
};

void BattleInfoRecordEffectRuntimeView::emit_group_effect_46f9f0(
    int effect_id,
    int group_index)
{
    signed char direction = side_00 ? -1 : 1;
    BattleInfoEffectPosition *position = groups_60[group_index];
    float x = position->x_0c;
    float y = position->y_10;
    emitter_14->emit(effect_id, x, y, direction, 1, 0);
}

typedef char BattleInfoRecordEmitterOffset[
    offsetof(BattleInfoRecordEffectRuntimeView, emitter_14) == 0x14 ? 1 : -1];
typedef char BattleInfoRecordGroupsOffset[
    offsetof(BattleInfoRecordEffectRuntimeView, groups_60) == 0x60 ? 1 : -1];

} // namespace th105
