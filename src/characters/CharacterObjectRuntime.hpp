#pragma once

#include <stddef.h>

namespace th105 {

// Shared observed prefix for animation/action objects used by roster-owned
// CharacterObject implementations. Concrete objects continue past +0x387.
struct CharacterObjectRuntime {
    void **vtable_000;
    unsigned char unknown_004[0xec];
    float component_f0;
    float component_f4;
    unsigned char unknown_0f8[0x4a];
    short frame_counter_142;
    int time_counter_144;
    unsigned char unknown_148[0x04];
    short frame_limit_14c;
    unsigned char unknown_14e[0x32];
    int phase_state_180;
    unsigned char phase_index_184;
    unsigned char unknown_185[0x1ff];
    short state_six_counter_384;
    short phase_counter_386;

    void set_oriented_components_f0_f4(float angle, float magnitude);
    unsigned char advance_frame_and_dispatch();
    unsigned char advance_state_six_counter_conditional(int limit);
    unsigned char advance_phase_counter_conditional(int limit);
};

typedef char CheckCharacterObjectComponentF0Offset[
    offsetof(CharacterObjectRuntime, component_f0) == 0xf0 ? 1 : -1];
typedef char CheckCharacterObjectComponentF4Offset[
    offsetof(CharacterObjectRuntime, component_f4) == 0xf4 ? 1 : -1];
typedef char CheckCharacterObjectFrameCounterOffset[
    offsetof(CharacterObjectRuntime, frame_counter_142) == 0x142 ? 1 : -1];
typedef char CheckCharacterObjectFrameLimitOffset[
    offsetof(CharacterObjectRuntime, frame_limit_14c) == 0x14c ? 1 : -1];
typedef char CheckCharacterObjectPhaseStateOffset[
    offsetof(CharacterObjectRuntime, phase_state_180) == 0x180 ? 1 : -1];
typedef char CheckCharacterObjectPhaseIndexOffset[
    offsetof(CharacterObjectRuntime, phase_index_184) == 0x184 ? 1 : -1];
typedef char CheckCharacterObjectStateSixCounterOffset[
    offsetof(CharacterObjectRuntime, state_six_counter_384) == 0x384 ? 1 : -1];
typedef char CheckCharacterObjectPhaseCounterOffset[
    offsetof(CharacterObjectRuntime, phase_counter_386) == 0x386 ? 1 : -1];
typedef char CheckCharacterObjectRuntimeSize[
    sizeof(CharacterObjectRuntime) == 0x388 ? 1 : -1];

} // namespace th105
