#include "BattleController.hpp"
#include "Collision.hpp"
#include <stddef.h>
namespace th105 {
extern BattleInputGate *g_battle_input_gate;
typedef char cpu_vertical_offset[offsetof(BattleInputGate,cpu_vertical_mode_18)==0x18?1:-1];
typedef char cpu_horizontal_offset[offsetof(BattleInputGate,cpu_horizontal_mode_1c)==0x1c?1:-1];
typedef char cpu_x[offsetof(Fighter,x_ec)==0xec?1:-1];
typedef char cpu_b4[offsetof(Fighter,field_6b4)==0x6b4?1:-1];
typedef char cpu_b8[offsetof(Fighter,field_6b8)==0x6b8?1:-1];
void Fighter::update_cpu_input_4633e0()
{
    switch (g_battle_input_gate->cpu_vertical_mode_18) {
    case 0: field_6b8 = 0; break;
    case 1: field_6b8 = 1; break;
    case 2: field_6b8 = -1; break;
    }

    switch (g_battle_input_gate->cpu_horizontal_mode_1c) {
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
