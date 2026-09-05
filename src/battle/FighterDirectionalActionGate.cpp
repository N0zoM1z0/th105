#include <stddef.h>

namespace th105 {

struct FighterDirectionalActionGateView {
    virtual void slot_00();
    virtual void slot_04();
    virtual void set_action(int action);

    unsigned char unknown_004[0x100];
    signed char facing_104;
    unsigned char unknown_105[0x7b];
    int action_mode_180;
    unsigned char unknown_184[0x32e];
    unsigned short gate_4b2;
    unsigned char unknown_4b4[0x04];
    int state_4b8;
    unsigned char unknown_4bc[0x1f8];
    int horizontal_input_6b4;
    int vertical_input_6b8;

    unsigned char try_dispatch_directional_action_208_210(int option);
};

typedef char FighterDirectionalActionGate_facing_offset[
    offsetof(FighterDirectionalActionGateView, facing_104) == 0x104 ? 1 : -1];
typedef char FighterDirectionalActionGate_mode_offset[
    offsetof(FighterDirectionalActionGateView, action_mode_180) == 0x180 ? 1 : -1];
typedef char FighterDirectionalActionGate_gate_offset[
    offsetof(FighterDirectionalActionGateView, gate_4b2) == 0x4b2 ? 1 : -1];
typedef char FighterDirectionalActionGate_state_offset[
    offsetof(FighterDirectionalActionGateView, state_4b8) == 0x4b8 ? 1 : -1];
typedef char FighterDirectionalActionGate_horizontal_offset[
    offsetof(FighterDirectionalActionGateView, horizontal_input_6b4) == 0x6b4 ? 1 : -1];
typedef char FighterDirectionalActionGate_vertical_offset[
    offsetof(FighterDirectionalActionGateView, vertical_input_6b8) == 0x6b8 ? 1 : -1];

unsigned char FighterDirectionalActionGateView::try_dispatch_directional_action_208_210(
    int option)
{
    if (state_4b8 != 10 || gate_4b2 != 0)
        return 0;

    const int action_mode = action_mode_180;
    if ((!action_mode || option) &&
        ((action_mode != 1 && action_mode != 7 && action_mode != 9) || option != 1))
        return 0;

    if (vertical_input_6b8 < 0 &&
        static_cast<int>(facing_104) * horizontal_input_6b4 > 0) {
        set_action(209);
        return 1;
    }
    if (vertical_input_6b8 < 0 &&
        static_cast<int>(facing_104) * horizontal_input_6b4 < 0) {
        set_action(210);
        return 1;
    }
    if (vertical_input_6b8 < 0 && horizontal_input_6b4 == 0) {
        set_action(208);
        return 1;
    }
    return 0;
}

} // namespace th105
