#include "CommandGates.hpp"

#include "battle/Collision.hpp"

extern "C" void __cdecl _invalid_parameter_noinfo(void);

namespace th105 {

int __fastcall initialize_fighter_phase_631e0(Fighter *fighter);

namespace {

typedef void (__thiscall *SetFighterAction)(Fighter *, int);

__forceinline void set_fighter_action(Fighter *fighter, int action)
{
    void **const vtable = *reinterpret_cast<void ***>(fighter);
    reinterpret_cast<SetFighterAction>(vtable[2])(fighter, action);
}

__forceinline int &field_int(Fighter *fighter, unsigned offset)
{
    return *reinterpret_cast<int *>(
        reinterpret_cast<unsigned char *>(fighter) + offset);
}

__forceinline unsigned char &field_byte(Fighter *fighter, unsigned offset)
{
    return *(reinterpret_cast<unsigned char *>(fighter) + offset);
}

} // namespace

unsigned char Fighter::try_dispatch_signed_gate_actions_208_210()
{
    if (field_6b8 < 0) {
        int const product =
            field_6b4 * static_cast<signed char>(facing_104);
        if (product > 0) {
            initialize_fighter_phase_631e0(this);
            set_fighter_action(this, 209);
            return 1;
        }
        if (product < 0) {
            initialize_fighter_phase_631e0(this);
            set_fighter_action(this, 210);
            return 1;
        }
        if (field_6b4 == 0) {
            initialize_fighter_phase_631e0(this);
            set_fighter_action(this, 208);
            return 1;
        }
    }
    return 0;
}

unsigned char Fighter::try_dispatch_flagged_gate_actions_220_224()
{
    if ((field_int(this, 0x724) & 0x20) == 0 ||
        field_byte(this, 0x75a) != 0 ||
        state_13c < 150 || state_13c > 157 ||
        (unknown_484 < 200 && state_4b8 != 0)) {
        return 0;
    }

    if (field_6b8 > 0) {
        int const command_value = field_6b4;
        int const product =
            static_cast<signed char>(facing_104) * command_value;
        if (product <= 0) {
            if (product < 0) {
                initialize_fighter_phase_631e0(this);
                set_fighter_action(this, 222);
                if (state_4b8 != 0) {
                    consume_counter_484_steps(1);
                }
                return 1;
            }
            if (command_value != 0) {
                return 0;
            }
        }
        initialize_fighter_phase_631e0(this);
        set_fighter_action(this, 220);
    } else {
        if (static_cast<signed char>(facing_104) * field_6b4 > 0) {
            initialize_fighter_phase_631e0(this);
            set_fighter_action(this, 223);
        } else {
            initialize_fighter_phase_631e0(this);
            set_fighter_action(this, 224);
        }
    }

    if (state_4b8 != 0) {
        consume_counter_484_steps(1);
    }
    return 1;
}

unsigned char Fighter::try_dispatch_flagged_gate_actions_225_226()
{
    if ((field_int(this, 0x724) & 0x20) != 0 &&
        field_byte(this, 0x75a) == 0 &&
        state_13c == 158 &&
        (unknown_484 >= 200 || state_4b8 == 0)) {
        int const product =
            static_cast<signed char>(facing_104) * field_6b4;
        if (product > 0) {
            initialize_fighter_phase_631e0(this);
            set_fighter_action(this, 226);
            if (state_4b8 != 0) {
                consume_counter_484_steps(1);
            }
            return 1;
        }

        initialize_fighter_phase_631e0(this);
        set_fighter_action(this, 225);
        if (state_4b8 != 0) {
            consume_counter_484_steps(1);
        }
        return 1;
    }
    return 0;
}

int Fighter::set_action_and_finalize_command(
    int action_id,
    int window_value)
{
    if (window_value >= 10) {
        flag_491 |= 0x10;
    }
    set_fighter_action(this, action_id);
    int const result = initialize_fighter_phase_631e0(this);
    *reinterpret_cast<float *>(
        reinterpret_cast<unsigned char *>(this) + 0x12c) = 0.0f;
    return result;
}

short Fighter::lookup_command_gate_value(int command_key)
{
    CommandGateIterator found;
    command_key = static_cast<short>(command_key);
    CommandGateIterator *const result = reinterpret_cast<CommandGateTree *>(
        *reinterpret_cast<void **>(
            reinterpret_cast<unsigned char *>(this) + 0x160))->lower_bound(
                &found,
                &command_key);
    if (result->owner_00 == 0) {
        _invalid_parameter_noinfo();
    }
    if (result->node_04 == result->owner_00->end_node_04) {
        _invalid_parameter_noinfo();
    }
    return result->node_04->value_10->value_10;
}

} // namespace th105
