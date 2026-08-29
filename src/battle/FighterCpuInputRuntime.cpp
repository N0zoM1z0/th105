#include <stddef.h>
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
    signed char classify_fighter_x_boundary();
    void update_cpu_input_4633e0();
};
typedef char cpu_x[offsetof(FighterCpuInputRuntimeView,x_ec)==0xec?1:-1];
typedef char cpu_b4[offsetof(FighterCpuInputRuntimeView,field_6b4)==0x6b4?1:-1];
typedef char cpu_b8[offsetof(FighterCpuInputRuntimeView,field_6b8)==0x6b8?1:-1];
void FighterCpuInputRuntimeView::update_cpu_input_4633e0()
{
    switch (g_battle_input_gate_cpu_runtime->vertical_mode_18) {
    case 0: field_6b8 = 0; break;
    case 1: field_6b8 = 1; break;
    case 2: field_6b8 = -1; break;
    }

    switch (g_battle_input_gate_cpu_runtime->horizontal_mode_1c) {
    case 0:
        field_6b4 = classify_fighter_x_boundary() > 0 ? 0 : -1;
        break;
    case 1:
        if (x_ec < 630.0f)
            field_6b4 = 1;
        else if (x_ec > 650.0f)
            field_6b4 = -1;
        else
            field_6b4 = 0;
        break;
    case 2:
        field_6b4 = classify_fighter_x_boundary() >= 0 ? 1 : 0;
        break;
    case 3:
    case 4:
        field_6b4 = 0;
        break;
    }
}
}
