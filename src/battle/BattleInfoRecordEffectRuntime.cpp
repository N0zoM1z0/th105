#include "BattleInfoRecordEffectRuntime.hpp"

#include <stddef.h>

namespace th105 {

void BattleInfoRecordEffectRuntimeView::emit_group_effect_46f9f0(
    int effect_id,
    int group_index)
{
    unsigned char direction = side_00 ? 255 : 1;
    BattleInfoEffectPosition *position = groups_60[group_index];
    float x = position->x_0c;
    float y = position->y_10;
    emitter_14->spawn_effect(effect_id, x, y, direction, 1, 0);
}

typedef char BattleInfoRecordEmitterOffset[
    offsetof(BattleInfoRecordEffectRuntimeView, emitter_14) == 0x14 ? 1 : -1];
typedef char BattleInfoRecordGroupsOffset[
    offsetof(BattleInfoRecordEffectRuntimeView, groups_60) == 0x60 ? 1 : -1];

} // namespace th105
