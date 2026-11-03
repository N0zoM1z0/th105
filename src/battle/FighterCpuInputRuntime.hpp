#pragma once

namespace th105 {

struct FighterCpuInputPolicyView {
    unsigned char unknown_00[0x18];
    int vertical_mode_18;
    int horizontal_mode_1c;
};
extern FighterCpuInputPolicyView *g_battle_input_gate_cpu_runtime;
struct FighterCpuInputRuntimeView {
    unsigned char unknown_000[0xec];
    float x_ec;
    unsigned char unknown_f0[0x5c4];
    int field_6b4;
    int field_6b8;
    void update_cpu_input_4633e0();
};
} // namespace th105
