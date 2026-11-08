#pragma once

#include "battle/PatResourceContracts.hpp"

namespace th105 {

// Native RTTI identifies this 32-byte group as PatternData.
struct EffectResourceGroup {
    EffectResourceGroup();
    virtual ~EffectResourceGroup();
    std::vector<FrameData> frames_04;
    // Nonzero suppresses the frame-wrap signal used for automatic block advance.
    // Frames still wrap, and explicit block selection remains possible.
    unsigned char suppress_wrap_signal_14;
    EffectResourceGroup *previous_18;
    EffectResourceGroup *next_1c;
};
typedef char effect_group_size[sizeof(EffectResourceGroup) == 0x20 ? 1 : -1];

} // namespace th105
