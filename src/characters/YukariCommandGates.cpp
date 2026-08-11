#include "Yukari.hpp"

namespace th105 {

int __fastcall initialize_fighter_phase_631e0(Fighter *fighter);

namespace {

typedef void (__thiscall *SetFighterAction)(Fighter *, int);

__forceinline void call_fighter_vslot(Fighter *fighter, int slot, int value)
{
    void **const vtable = *reinterpret_cast<void ***>(fighter);
    reinterpret_cast<SetFighterAction>(vtable[slot])(fighter, value);
}

} // namespace

unsigned char Yukari::try_dispatch_mirrored_gate_actions_200_201(
    int window_value,
    int action_201_override)
{
    int const first_flags = field_724;
    if ((((first_flags & 1) != 0 && facing_104 == 1) ||
         ((first_flags & 2) != 0 && facing_104 == 0xff) ||
         (static_cast<unsigned>(field_6c8) > 0 && field_6b8 == 0 &&
          field_6b4 * static_cast<signed char>(facing_104) > 0)) &&
        state_13c != 204 &&
        window_value <= lookup_command_gate_value(200)) {
        short const state = state_13c;
        if ((state > 299 && result_180 != 0 && result_180 != 3) ||
            state < 300) {
            initialize_fighter_phase_631e0(this);
            call_fighter_vslot(this, 2, 200);
            return 1;
        }
    }

    int const second_flags = field_724;
    if ((((second_flags & 2) != 0 && facing_104 == 1) ||
         ((second_flags & 1) != 0 && facing_104 == 0xff) ||
         (static_cast<unsigned>(field_6c8) > 0 && field_6b8 == 0 &&
          field_6b4 * static_cast<signed char>(facing_104) < 0)) &&
        (window_value <= lookup_command_gate_value(201) ||
         action_201_override != 0)) {
        short const state = state_13c;
        if ((state > 299 && result_180 != 0 && result_180 != 3) ||
            state < 300) {
            initialize_fighter_phase_631e0(this);
            call_fighter_vslot(this, 2, 201);
            if (static_cast<unsigned char>(classify_fighter_x_boundary()) ==
                facing_104) {
                call_fighter_vslot(this, 3, 4);
            }
            return 1;
        }
    }
    return 0;
}

} // namespace th105
