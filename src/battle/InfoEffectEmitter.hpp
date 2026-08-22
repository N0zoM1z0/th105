#pragma once

namespace th105 {

// Narrow current-target view of the polymorphic emitter embedded at
// InfoEffectEmitterView +0x04. The exact 0x0046E9D0 facade calls vslot +0x0C.
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
    virtual int dispatch_state(int state);
};

struct InfoEffectEmitterView {
    unsigned int reserved_00;
    EffectEmitterSubobject emitter_04;

    int emit_effect(int effect_id, float x, float y, int flag_a, int flag_b);
};

extern InfoEffectEmitterView *g_info_effect_emitter;

} // namespace th105
