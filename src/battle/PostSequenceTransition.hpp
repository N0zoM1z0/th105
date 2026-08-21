#pragma once

#include "InfoEffectEmitter.hpp"

namespace th105 {

// Narrow current-target view shared by battle transition code. Current callers
// pass a controller-owned object whose polymorphic emitter begins at +0x04.
struct PostSequenceTransitionView {
    unsigned int reserved_00;
    EffectEmitterSubobject emitter_04;

    int publish_transition_effect_46e040(int effect_id);
    void publish_transition_effect_at_46e130(float position);
};

} // namespace th105
