#pragma once

#include <stddef.h>

namespace th105 {

// Shared observed prefix for animation/action objects used by roster-owned
// CharacterObject implementations. Concrete objects continue past +0x14D.
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

    void set_oriented_components_f0_f4(float angle, float magnitude);
    unsigned char advance_frame_and_dispatch();
};

typedef char CheckCharacterObjectComponentF0Offset[
    offsetof(CharacterObjectRuntime, component_f0) == 0xf0 ? 1 : -1];
typedef char CheckCharacterObjectComponentF4Offset[
    offsetof(CharacterObjectRuntime, component_f4) == 0xf4 ? 1 : -1];
typedef char CheckCharacterObjectFrameCounterOffset[
    offsetof(CharacterObjectRuntime, frame_counter_142) == 0x142 ? 1 : -1];
typedef char CheckCharacterObjectFrameLimitOffset[
    offsetof(CharacterObjectRuntime, frame_limit_14c) == 0x14c ? 1 : -1];

} // namespace th105
