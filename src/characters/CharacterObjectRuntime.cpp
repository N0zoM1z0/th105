#include "CharacterObjectRuntime.hpp"

namespace th105 {

float __cdecl lookup_orientation_sine_quantized_abs(float angle);
float __cdecl lookup_orientation_cosine_quantized_abs(float angle);

namespace {

typedef unsigned char (__thiscall *ObjectPhase)(CharacterObjectRuntime *);

__forceinline unsigned char call_object_phase(
    CharacterObjectRuntime *object,
    int slot)
{
    return reinterpret_cast<ObjectPhase>(object->vtable_000[slot])(object);
}

} // namespace

void CharacterObjectRuntime::set_oriented_components_f0_f4(
    float angle,
    float magnitude)
{
    component_f0 = lookup_orientation_cosine_quantized_abs(angle) * magnitude;
    component_f4 = -lookup_orientation_sine_quantized_abs(angle) * magnitude;
}

unsigned char CharacterObjectRuntime::advance_frame_and_dispatch()
{
    ++time_counter_144;
    ++frame_counter_142;
    if (frame_counter_142 >= frame_limit_14c &&
        call_object_phase(this, 8)) {
        return call_object_phase(this, 5);
    }
    return 0;
}

unsigned char CharacterObjectRuntime::advance_state_six_counter_conditional(
    int limit)
{
    if (phase_state_180 != 6) {
        goto return_zero;
    }
    ++state_six_counter_384;
    if (limit <= 0 || state_six_counter_384 < limit) {
        ++phase_index_184;
        phase_state_180 = 0;
        goto return_zero;
    }
    return 1;

return_zero:
    return 0;
}

unsigned char CharacterObjectRuntime::advance_phase_counter_conditional(int limit)
{
    if (phase_state_180 == 4 || phase_state_180 == 8) {
        ++phase_counter_386;
        if (limit > 0 && phase_counter_386 >= limit) {
            return 1;
        }
        ++phase_index_184;
        phase_state_180 = 0;
    }
    return 0;
}

} // namespace th105
