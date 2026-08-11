#pragma once

#include <stddef.h>

namespace th105 {

// Alice-specific extension of the shared CharacterObject layout. The target
// Alice pool allocates 0x38C bytes; this view covers the fields used here.
struct AliceObjectFlightState {
    unsigned char unknown_000[0xec];
    float x_ec;
    float y_f0;
    unsigned char unknown_0f4[0x10];
    signed char facing_104;
    unsigned char unknown_105[0x17];
    float distance_scale_11c;
    unsigned char unknown_120[0x0c];
    float heading_12c;
    unsigned char unknown_130[0x0e];
    short state_13e;
    unsigned char unknown_140[0x1f0];
    int lifetime_330;
    unsigned char unknown_334[0x14];
    AliceObjectFlightState *owner_348;
    AliceObjectFlightState *target_34c;
    unsigned char unknown_350[0x20];
    float x_delta_squared_370;
    float y_delta_squared_374;
    float target_distance_378;

    unsigned char update_from_owner_and_target(short expected_state);
};

typedef char CheckAliceObjectFlightOwnerOffset[
    offsetof(AliceObjectFlightState, owner_348) == 0x348 ? 1 : -1];
typedef char CheckAliceObjectFlightTargetOffset[
    offsetof(AliceObjectFlightState, target_34c) == 0x34c ? 1 : -1];
typedef char CheckAliceObjectFlightDistanceOffset[
    offsetof(AliceObjectFlightState, target_distance_378) == 0x378 ? 1 : -1];

} // namespace th105
