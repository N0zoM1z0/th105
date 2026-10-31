#pragma once

#include "battle/PatResourceContracts.hpp"

namespace th105 {

// Native RTTI identifies this 32-byte group as PatternData.
struct EffectResourceGroup {
    EffectResourceGroup();
    virtual ~EffectResourceGroup();
    std::vector<FrameData> frames_04;
    unsigned char flag_14;
    EffectResourceGroup *previous_18;
    EffectResourceGroup *next_1c;
};
typedef char effect_group_size[sizeof(EffectResourceGroup) == 0x20 ? 1 : -1];

} // namespace th105
