#include "BattleInfoRecordEffectRuntime.hpp"

#include "ui/UiPrimitives.hpp"
#include <stddef.h>

namespace th105 {

void BattleInfoRecordEffectRuntimeView::emit_group_effect_46f9f0(
    int effect_id,
    int group_index)
{
    unsigned char direction = mode_00 ? 255 : 1;
    UiDesignObject *position = group_60[group_index];
    float x = position->x;
    float y = position->y;
    effect_manager_14->spawn_effect(effect_id, x, y, direction, 1, 0);
}

typedef char BattleInfoRecordEmitterOffset[
    offsetof(BattleInfoRecordEffectRuntimeView, effect_manager_14) == 0x14 ? 1 : -1];
typedef char BattleInfoRecordGroupsOffset[
    offsetof(BattleInfoRecordEffectRuntimeView, group_60) == 0x60 ? 1 : -1];

} // namespace th105
