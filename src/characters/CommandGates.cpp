#include "CommandGates.hpp"

#include "battle/Collision.hpp"
#include "battle/SpellRuntime.hpp"

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

__forceinline float &field_float(Fighter *fighter, unsigned offset)
{
    return *reinterpret_cast<float *>(
        reinterpret_cast<unsigned char *>(fighter) + offset);
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

unsigned char Fighter::try_dispatch_threshold_gated_actions_208_210(
    int window_value,
    int bypass_window_gate)
{
    if (((field_byte(this, 0x724) & 0x04) != 0 ||
         (static_cast<unsigned>(field_6c8) > 0 &&
          field_6b8 < 0 && field_6b4 == 0) ||
         (field_6b8 < 0 && field_6b4 == 0 && window_value >= 40)) &&
        (window_value <= lookup_command_gate_value(208) ||
         bypass_window_gate != 0)) {
        short const state = state_13c;
        if ((state > 299 && result_180 != 0 && result_180 != 3) ||
            state < 300) {
            initialize_fighter_phase_631e0(this);
            set_fighter_action(this, 208);
            return 1;
        }
    }

    if (((field_byte(this, 0x724) & 0x10) != 0 ||
         (static_cast<unsigned>(field_6c8) > 0 && field_6b8 < 0 &&
          field_6b4 * static_cast<signed char>(facing_104) > 0) ||
         (field_6b8 < 0 &&
          field_6b4 * static_cast<signed char>(facing_104) > 0 &&
          window_value >= 40)) &&
        (window_value <= lookup_command_gate_value(209) ||
         bypass_window_gate != 0)) {
        short const state = state_13c;
        if ((state > 299 && result_180 != 0 && result_180 != 3) ||
            state < 300) {
            initialize_fighter_phase_631e0(this);
            set_fighter_action(this, 209);
            return 1;
        }
    }

    if (((field_byte(this, 0x724) & 0x08) != 0 ||
         (static_cast<unsigned>(field_6c8) > 0 && field_6b8 < 0 &&
          field_6b4 * static_cast<signed char>(facing_104) < 0) ||
         (field_6b8 < 0 &&
          field_6b4 * static_cast<signed char>(facing_104) < 0 &&
          window_value >= 40)) &&
        (window_value <= lookup_command_gate_value(210) ||
         bypass_window_gate != 0)) {
        short const state = state_13c;
        if ((state > 299 && result_180 != 0 && result_180 != 3) ||
            state < 300) {
            initialize_fighter_phase_631e0(this);
            set_fighter_action(this, 210);
            return 1;
        }
    }
    return 0;
}

unsigned char Fighter::try_dispatch_mirrored_gate_actions_200_201(
    int window_value,
    int action_201_override)
{
    int const first_flags = field_int(this, 0x724);
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
            set_fighter_action(this, 200);
            return 1;
        }
    }

    int const second_flags = field_int(this, 0x724);
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
            set_fighter_action(this, 201);
            return 1;
        }
    }
    return 0;
}

unsigned char Fighter::try_dispatch_action_202(
    int window_value,
    int bypass_window_gate,
    int repeat_limit,
    int same_action_minimum)
{
    if (static_cast<signed char>(field_byte(this, 0x47f)) >= repeat_limit ||
        (state_13c == 202 &&
         *reinterpret_cast<short *>(
             reinterpret_cast<unsigned char *>(this) + 0x13e) <
             same_action_minimum)) {
        return 0;
    }

    int const flags = field_int(this, 0x724);
    if ((((flags & 1) == 0 || facing_104 != 1) &&
         ((flags & 2) == 0 || facing_104 != 0xff)) ||
        (window_value > lookup_command_gate_value(202) &&
         bypass_window_gate == 0) ||
        (!(y_component_f8 <= 0.0f) && !(y_f0 > 100.0))) {
        return 0;
    }

    short const state = state_13c;
    if ((state <= 299 || result_180 == 0 || result_180 == 3) &&
        state >= 300) {
        return 0;
    }

    initialize_fighter_phase_631e0(this);
    ++field_byte(this, 0x47f);
    set_fighter_action(this, 202);
    return 1;
}

unsigned char Fighter::try_dispatch_action_203(
    int window_value,
    int bypass_window_gate,
    int repeat_limit,
    int same_action_minimum)
{
    if (static_cast<signed char>(field_byte(this, 0x47f)) >= repeat_limit ||
        (state_13c == 203 &&
         *reinterpret_cast<short *>(
             reinterpret_cast<unsigned char *>(this) + 0x13e) <
             same_action_minimum)) {
        return 0;
    }

    int const flags = field_int(this, 0x724);
    if ((((flags & 2) == 0 || facing_104 != 1) &&
         ((flags & 1) == 0 || facing_104 != 0xff)) ||
        (window_value > lookup_command_gate_value(203) &&
         bypass_window_gate == 0) ||
        (!(y_component_f8 <= 0.0f) && !(y_f0 > 100.0))) {
        return 0;
    }

    short const state = state_13c;
    if ((state <= 299 || result_180 == 0 || result_180 == 3) &&
        state >= 300) {
        return 0;
    }

    initialize_fighter_phase_631e0(this);
    ++field_byte(this, 0x47f);
    set_fighter_action(this, 203);
    return 1;
}

unsigned char Fighter::try_dispatch_action_214_with_direction_angle(
    int window_value,
    int bypass_window_gate,
    int maximum_count)
{
    if (static_cast<signed char>(field_byte(this, 0x47f)) >= maximum_count ||
        static_cast<unsigned>(field_6c8) < 1 ||
        (field_6b4 == 0 && field_6b8 == 0) ||
        (!(y_component_f8 <= 0.0f) && !(y_f0 > 100.0)) ||
        (window_value > lookup_command_gate_value(214) &&
         bypass_window_gate == 0) ||
        ((state_13c <= 299 || result_180 == 0 || result_180 == 3) &&
         state_13c >= 300)) {
        return 0;
    }

    int const vertical = field_6b8;
    if (vertical > 0) {
        int const horizontal =
            field_6b4 * static_cast<signed char>(facing_104);
        if (horizontal > 0) {
            field_float(this, 0x740) = -45.0f;
        }
        if (horizontal < 0) {
            field_float(this, 0x740) = -135.0f;
        }
        if (horizontal == 0) {
            field_float(this, 0x740) = -90.0f;
        }
    }
    if (vertical < 0) {
        int const horizontal =
            field_6b4 * static_cast<signed char>(facing_104);
        if (horizontal > 0) {
            field_float(this, 0x740) = 45.0f;
        }
        if (horizontal < 0) {
            field_float(this, 0x740) = 135.0f;
        }
        if (horizontal == 0) {
            field_float(this, 0x740) = 90.0f;
        }
    }
    if (vertical == 0) {
        int const horizontal =
            field_6b4 * static_cast<signed char>(facing_104);
        if (horizontal > 0) {
            field_float(this, 0x740) = 0.0f;
        }
        if (horizontal < 0) {
            field_float(this, 0x740) = 180.0f;
        }
        if (horizontal == 0) {
            field_float(this, 0x740) = 0.0f;
        }
    }

    initialize_fighter_phase_631e0(this);
    SetFighterAction const action =
        reinterpret_cast<SetFighterAction>(
            (*reinterpret_cast<void ***>(this))[2]);
    ++field_byte(this, 0x47f);
    action(this, 214);
    return 1;
}

unsigned char Fighter::try_dispatch_front_word_actions_690_696(
    int window_value)
{
    int command_key = 690;
    CommandGateIterator found;
    CommandGateIterator *result = reinterpret_cast<CommandGateTree *>(
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

    int const saved_window = window_value;
    if (window_value <= result->node_04->value_10->value_10 &&
        sequence_controller_55c.entry_at_checked(0)->record_id_00 >= 100 &&
        sequence_controller_55c.entry_at_checked(0)->record_id_00 <= 199) {
        short const state = state_13c;
        if ((state > 299 && result_180 != 0 && result_180 != 3) ||
            state < 300) {
            initialize_fighter_phase_631e0(this);
            set_fighter_action(this, 690);
            return 1;
        }
    }

    window_value = 691;
    result = reinterpret_cast<CommandGateTree *>(
        *reinterpret_cast<void **>(
            reinterpret_cast<unsigned char *>(this) + 0x160))->lower_bound(
                &found,
                &window_value);
    if (result->owner_00 == 0) {
        _invalid_parameter_noinfo();
    }
    if (result->node_04 == result->owner_00->end_node_04) {
        _invalid_parameter_noinfo();
    }

    if (saved_window <= result->node_04->value_10->value_10 &&
        sequence_controller_55c.entry_at_checked(0)->record_id_00 == 0) {
        short const state = state_13c;
        if ((state > 299 && result_180 != 0 && result_180 != 3) ||
            state < 300) {
            initialize_fighter_phase_631e0(this);
            set_fighter_action(this, 691);
            return 1;
        }
    }

    window_value = 695;
    result = reinterpret_cast<CommandGateTree *>(
        *reinterpret_cast<void **>(
            reinterpret_cast<unsigned char *>(this) + 0x160))->lower_bound(
                &found,
                &window_value);
    if (result->owner_00 == 0) {
        _invalid_parameter_noinfo();
    }
    if (result->node_04 == result->owner_00->end_node_04) {
        _invalid_parameter_noinfo();
    }

    if (saved_window <= result->node_04->value_10->value_10 &&
        sequence_controller_55c.entry_at_checked(0)->record_id_00 == 1) {
        short const state = state_13c;
        if ((state > 299 && result_180 != 0 && result_180 != 3) ||
            state < 300) {
            initialize_fighter_phase_631e0(this);
            set_fighter_action(this, 695);
            return 1;
        }
    }

    if (saved_window <= lookup_command_gate_value(696) &&
        sequence_controller_55c.entry_at_checked(0)->record_id_00 == 2) {
        short const state = state_13c;
        if (state >= 150 && state <= 157) {
            if ((state > 299 && result_180 != 0 && result_180 != 3) ||
                state < 300) {
                initialize_fighter_phase_631e0(this);
                set_fighter_action(this, 696);
                return 1;
            }
        }
    }

    if (saved_window <= lookup_command_gate_value(692) &&
        sequence_controller_55c.entry_at_checked(0)->record_id_00 == 3) {
        short const state = state_13c;
        if ((state > 299 && result_180 != 0 && result_180 != 3) ||
            state < 300) {
            initialize_fighter_phase_631e0(this);
            set_fighter_action(this, 692);
            return 1;
        }
    }

    if (saved_window <= lookup_command_gate_value(693) &&
        sequence_controller_55c.entry_at_checked(0)->record_id_00 == 4) {
        short const state = state_13c;
        if ((state > 299 && result_180 != 0 && result_180 != 3) ||
            state < 300) {
            initialize_fighter_phase_631e0(this);
            set_fighter_action(this, 693);
            return 1;
        }
    }

    if (saved_window <= lookup_command_gate_value(694) &&
        sequence_controller_55c.entry_at_checked(0)->record_id_00 == 5) {
        short const state = state_13c;
        if ((state > 299 && result_180 != 0 && result_180 != 3) ||
            state < 300) {
            initialize_fighter_phase_631e0(this);
            set_fighter_action(this, 694);
            return 1;
        }
    }
    return 0;
}

} // namespace th105
