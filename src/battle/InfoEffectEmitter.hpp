#pragma once

#include "EffectManager.hpp"
#include <stddef.h>

namespace th105 {

// Pointer-only virtual view used by other effect receivers.
struct EffectEmitterSubobject {
    virtual void slot_00();
    virtual void slot_04();
    virtual void slot_08();
    virtual int emit(
        int effect_id,
        float x,
        float y,
        int flag_a,
        int flag_b,
        int trailing_zero);
    virtual void slot_10();
    virtual void slot_14();
    // Primary slot18 is the signed-byte render-layer callback (46F350).
    virtual void dispatch_state(signed char layer);
};

struct InfoEffectEmitterView {
    unsigned int reserved_00;
    CEffectManager<InfoEffectObject> emitter_04;

    InfoEffectObject *emit_effect(int effect_id, float x, float y, int flag_a, int flag_b);
};

typedef char InfoEffectEmitterManagerOffset[offsetof(InfoEffectEmitterView, emitter_04) == 4 ? 1 : -1];
typedef char InfoEffectEmitterViewSize[sizeof(InfoEffectEmitterView) == 0x98 ? 1 : -1];

extern InfoEffectEmitterView *g_info_effect_emitter;

} // namespace th105
