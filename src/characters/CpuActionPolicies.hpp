#pragma once

#include <stddef.h>

namespace th105 {

// Source-facing layout for fighter vtable slot +0x58.  The gameplay labels of
// individual output fields remain intentionally neutral; IDA proves that the
// policy bodies write this contiguous control block from the current action,
// opponent position, sequence front, and randomized policy counters.
struct CpuActionPolicyView {
    unsigned char unknown_000[0xec];
    float x_ec;
    float y_f0;
    unsigned char unknown_0f4[0x10];
    signed char facing_104;
    unsigned char unknown_105[0x37];
    short action_13c;
    unsigned char unknown_13e[0x32];
    CpuActionPolicyView *other_fighter_170;
    unsigned char unknown_174[0x0c];
    unsigned policy_state_180;
    unsigned char unknown_184[0x3d6];
    signed char sequence_state_55a;
    signed char sequence_state_55b;
    unsigned char sequence_controller_55c[0x158];
    int control_6b4;
    int control_6b8;
    int control_6bc;
    int control_6c0;
    int control_6c4;
    int control_6c8;
    int control_6cc;
    int control_6d0;
    unsigned char unknown_6d4[0x50];
    int command_flags_724;
    int command_flags_728;
    signed char control_mode_72c;
    unsigned char unknown_72d[0x37];
    short policy_counter_764;
    short policy_counter_766;
    short policy_counter_768;
    short policy_counter_76a;
    short policy_counter_76c;
    short policy_random_76e;

    void update_default_cpu_action_policy();
};

struct ReimuCpuActionPolicyView : CpuActionPolicyView {
    void update_cpu_action_policy();
};

struct MarisaCpuActionPolicyView : CpuActionPolicyView {
    void update_cpu_action_policy();
};

struct AliceCpuActionPolicyView : CpuActionPolicyView {
    void update_cpu_action_policy();
};

struct AyaCpuActionPolicyView : CpuActionPolicyView {
    void update_cpu_action_policy();
};

typedef char CpuActionPolicyView_size_must_be_0x770[
    sizeof(CpuActionPolicyView) == 0x770 ? 1 : -1];
typedef char CpuActionPolicyView_control_offset_must_be_0x6b4[
    offsetof(CpuActionPolicyView, control_6b4) == 0x6b4 ? 1 : -1];
typedef char CpuActionPolicyView_counter_offset_must_be_0x764[
    offsetof(CpuActionPolicyView, policy_counter_764) == 0x764 ? 1 : -1];

} // namespace th105
