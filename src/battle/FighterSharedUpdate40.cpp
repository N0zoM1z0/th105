#include <math.h>
#include <stddef.h>

namespace th105 {

int __cdecl selector_random_roll(int limit);
extern int g_fighter_state_4b8_default;
extern short g_info_mode_value_6fa88c;

struct FighterSharedUpdate40View;
bool __fastcall is_state_13c_in_32_95(FighterSharedUpdate40View *fighter);
float __fastcall stage_surface_height_at_x(FighterSharedUpdate40View *fighter);

struct FighterSharedUpdate40View {
    void finalize_sequence_entry_45bb10(int sequence);
    void publish_texture_state(signed char texture_index, short duration);
    void emit_fighter_effect_433cc0(
        int effect_id, float x, float y, int direction, int arg5);
    int spawn_owned_object_via_manager(
        int object_id, float x, float y, int direction,
        unsigned char arg5, int arg6, int arg7);
    void update_shared_state_40();

    unsigned char unknown_000[0xec];
    float x_ec;
    float y_f0;
    unsigned char unknown_0f4[0x10];
    unsigned char facing_104;
    unsigned char unknown_105[0x37];
    short state_13c;
    unsigned char unknown_13e[0x32];
    FighterSharedUpdate40View *other_fighter_170;
    short value_174;
    short maximum_176;
    unsigned char unknown_178[4];
    signed char state_17c;
    unsigned char unknown_17d[0x1b7];
    signed char player_index_334;
    unsigned char unknown_335[0x157];
    short gate_48c;
    short blocker_48e;
    unsigned char unknown_490[0x12];
    short value_4a2;
    short field_4a4;
    unsigned char unknown_4a6[0x0a];
    short gate_4b0;
    short gate_4b2;
    short gate_4b4;
    signed char trigger_4b6;
    unsigned char unknown_4b7;
    int state_4b8;
    float source_factor_4bc;
    float target_factor_4c0;
    float threshold_scale_4c4;
    float source_modifier_4c8;
    float source_modifier_4cc;
    float factor_4d0;
    float factor_4d4;
    float scale_4d8;
    unsigned char unknown_4dc[8];
    signed char gate_4e4;
    signed char unknown_4e5;
    signed char gate_4e6;
    signed char unknown_4e7;
    unsigned char unknown_4e8[0x1c4];
    float peer_component_6ac;
    unsigned char unknown_6b0[0x7c];
    signed char state_72c;
    unsigned char unknown_72d[0x26];
    signed char effect_gate_753;
    signed char state_flags_754[5];
    signed char active_759;
    signed char peer_action_600_689_75a;
    unsigned char unknown_75b;
    int spawn_period_75c;
    int active_duration_760;
};

#define OFFCHECK(name, off) typedef char offcheck_##name[offsetof(FighterSharedUpdate40View, name)==off?1:-1]
OFFCHECK(x_ec,0xec); OFFCHECK(y_f0,0xf0); OFFCHECK(facing_104,0x104);
OFFCHECK(state_13c,0x13c); OFFCHECK(other_fighter_170,0x170);
OFFCHECK(value_174,0x174); OFFCHECK(state_17c,0x17c); OFFCHECK(player_index_334,0x334);
OFFCHECK(gate_48c,0x48c); OFFCHECK(value_4a2,0x4a2); OFFCHECK(field_4a4,0x4a4);
OFFCHECK(gate_4b0,0x4b0); OFFCHECK(gate_4b2,0x4b2); OFFCHECK(gate_4b4,0x4b4);
OFFCHECK(trigger_4b6,0x4b6); OFFCHECK(state_4b8,0x4b8); OFFCHECK(source_factor_4bc,0x4bc);
OFFCHECK(peer_component_6ac,0x6ac); OFFCHECK(state_72c,0x72c);
OFFCHECK(effect_gate_753,0x753); OFFCHECK(active_759,0x759); OFFCHECK(spawn_period_75c,0x75c);
OFFCHECK(active_duration_760,0x760);
#undef OFFCHECK

void FighterSharedUpdate40View::update_shared_state_40()
{
    if (gate_4b2 > 0 && gate_48c == 0) {
        active_759 = 1;
    } else if (active_duration_760 <= 0) {
        active_759 = 0;
    }

    FighterSharedUpdate40View *const peer = other_fighter_170;
    if (peer->state_13c >= 600 && peer->state_13c <= 689)
        peer_action_600_689_75a = 1;
    else
        peer_action_600_689_75a = 0;

    const short value = value_174;
    if (value <= 0) {
        gate_4b0 = 0;
        gate_4b2 = 0;
        gate_4b4 = 0;
    }
    if (peer->value_174 <= 0) {
        gate_4b0 = 0;
        gate_4b2 = 0;
    }

    if (value <= 0 && state_72c == 2 &&
        state_13c >= 50 && state_13c <= 149) {
        finalize_sequence_entry_45bb10(0);
        publish_texture_state(0, 0);
    }

    if (gate_4b4 > 0) {
        if (is_state_13c_in_32_95(this))
            gate_4b4 = 0;

        value_174 += 4;
        if (value_174 >= maximum_176)
            value_174 = maximum_176;

        if (gate_4b4 % 15 == 0) {
            emit_fighter_effect_433cc0(
                151, x_ec, y_f0, facing_104, 1);
        }
        if (gate_4b4 % 10 == 0) {
            const double y = y_f0;
            if (stage_surface_height_at_x(this) >= y) {
                emit_fighter_effect_433cc0(
                    150, x_ec, y_f0, facing_104, -1);
            }
        }
        --gate_4b4;
    }

    if (trigger_4b6 == 1) {
        if (g_fighter_state_4b8_default != 16) {
            if (g_info_mode_value_6fa88c >= 3) {
                g_info_mode_value_6fa88c -= 3;
            } else {
                g_info_mode_value_6fa88c = 0;
                trigger_4b6 = 0;
            }
        } else {
            trigger_4b6 = 0;
        }
    }

    if (value_4a2 >= 100 && effect_gate_753 == 0) {
        const float effect_y_112 = static_cast<float>(y_f0 + 100.0);
        emit_fighter_effect_433cc0(
            112, x_ec, effect_y_112, facing_104, -1);
        const float effect_y_137 = static_cast<float>(y_f0 + 100.0);
        emit_fighter_effect_433cc0(
            137, x_ec, effect_y_137, facing_104, -1);
        effect_gate_753 = 1;
    }

    if ((state_13c < 50 || state_13c > 149) && field_4a4 <= 0)
        effect_gate_753 = 0;

    float zero = 0.0f;
    if (active_759) {
        if (active_duration_760 > 0)
            --active_duration_760;
        else
            active_759 = 0;

        if (spawn_period_75c <= 0) {
            spawn_period_75c = selector_random_roll(60) + 60;

            float parameters[3];
            parameters[0] = static_cast<float>(
                static_cast<unsigned int>(selector_random_roll(360)));
            parameters[1] = static_cast<float>(
                static_cast<double>(static_cast<float>(
                    static_cast<unsigned int>(selector_random_roll(60)))) +
                90.0);
            parameters[2] = 0.0f;

            const float vertical_offset = static_cast<float>(
                25.0 - static_cast<double>(static_cast<float>(
                    static_cast<unsigned int>(selector_random_roll(50)))));
            spawn_owned_object_via_manager(
                980,
                static_cast<float>(
                    static_cast<double>(static_cast<float>(
                        static_cast<unsigned int>(selector_random_roll(100))) + x_ec) -
                    50.0),
                vertical_offset + y_f0,
                static_cast<unsigned char>(facing_104),
                static_cast<unsigned char>(
                    1 - 2 * (vertical_offset >= 0.0f)),
                reinterpret_cast<int>(parameters),
                3);
            zero = 0.0f;
                } else {
            --spawn_period_75c;
                }
    }

    const int mode = state_4b8;
    state_17c = -1;

    if (mode != 3 || gate_4b2 > 0) {
        state_flags_754[0] = 1;
        state_flags_754[1] = 1;
        state_flags_754[2] = 1;
        state_flags_754[3] = 1;
        state_flags_754[4] = 1;
    }

    factor_4d0 = 1.0f;
    gate_4e4 = 0;
    source_factor_4bc = 1.0f;
    unknown_4e5 = 0;
    target_factor_4c0 = 1.0f;
    gate_4e6 = 0;
    source_modifier_4cc = 1.0f;
    unknown_4e7 = 0;
    source_modifier_4c8 = 1.0f;
    blocker_48e = 0;
    threshold_scale_4c4 = 1.0f;
    factor_4d4 = zero;
    scale_4d8 = zero;

    if (gate_4b2 != 0)
        return;

    switch (mode) {
    case 1:
        source_modifier_4c8 = 1.25f;
        return;

    case 2:
        factor_4d0 = 2.0f;
        return;

    case 3:
        if (state_13c <= 499 || state_13c >= 600) {
            state_flags_754[0] = 0;
            state_flags_754[1] = 0;
            state_flags_754[2] = 0;
            state_flags_754[3] = 0;
            state_flags_754[4] = 0;
        }
        return;

    case 4:
        source_modifier_4cc = 1.25f;
        return;

    case 6:
        factor_4d4 = 0.5f;
        return;

    case 7:
        scale_4d8 = 0.5f;
        return;

    case 8:
        gate_4e4 = 1;
        return;

    case 9:
        unknown_4e5 = 1;
        return;

    case 17:
        gate_4e6 = 1;
        return;

    case 11:
        unknown_4e7 = 1;
        return;

    case 12:
        if (state_13c <= 599 &&
            (state_13c <= 99 || state_13c >= 112)) {
            FighterSharedUpdate40View *const peer = other_fighter_170;
            const float delta_x = peer->x_ec - x_ec;
            const float absolute_delta_x = static_cast<float>(fabs(delta_x));
            float adjustment = static_cast<float>(
                (absolute_delta_x - 480.0) * 0.009999999776482582);
            if (adjustment > 3.0f)
                adjustment = 3.0f;
            else if (adjustment < -3.0f)
                adjustment = -3.0f;

            peer->peer_component_6ac =
                ((peer->x_ec < x_ec && facing_104 == 1) ||
                 (peer->x_ec > x_ec && facing_104 == 0xff))
                    ? peer->peer_component_6ac - adjustment
                    : adjustment;
        }
        return;

    case 13:
        threshold_scale_4c4 = zero;
        blocker_48e = 1;
        return;

    default:
        return;
    }
}

} // namespace th105
