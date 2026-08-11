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

} // namespace th105
