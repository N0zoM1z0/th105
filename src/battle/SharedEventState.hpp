#pragma once

namespace th105 {

// Narrow current-target contract shared by the roster event bridges.  The
// represented fields are only those independently established by 1.06a code.
struct SharedEventState {
    float source_00;
    float source_04;
    float source_08;
    unsigned char reserved_0c[0x08];
    float mirrored_14;
    float mirrored_18;
    float mirrored_1c;
    float target_20;
    float target_24;
    float target_28;
    char enabled_2c;
    char enabled_2d;
    char enabled_2e;

    char set_target_20_enabled_2c(char enabled, float target);
    char set_target_24_enabled_2d(char enabled, float target);
    char set_target_28_enabled_2e(char enabled, float target);
    int synchronize_targets();
};

extern SharedEventState g_shared_event_state;

} // namespace th105
