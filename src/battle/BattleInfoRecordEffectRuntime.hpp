#pragma once

#include "InfoManagerResources.hpp"

namespace th105 {

// Declaration-only callable view over the actual initialized record state.
struct BattleInfoRecordEffectRuntimeView : BattleInfoRecordF8 {
    void emit_group_effect_46f9f0(int effect_id, int group_index);
};

} // namespace th105
