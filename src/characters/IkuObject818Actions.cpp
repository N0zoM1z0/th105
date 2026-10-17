#include "AnimationSequenceVirtuals.hpp"

namespace th105 {

// Semantic staging for the complete 565--568 family inside 620920, not a
// replacement for the 59,038-byte root or an original standalone function.
// No source-present/exact ledger entry selects this helper. The partial view
// names only access-backed state; the full Iku class layout remains unknown.
class IkuObject818ActionView;
float __fastcall stage_surface_height_at_x(IkuObject818ActionView *fighter);

class IkuObject818ActionView : public AnimationSequenceObjectView {
public:
    unsigned char resolve_stage_surface_landing_transition();
    int has_crossed_stage_surface_while_descending();
    unsigned char advance_frame_and_dispatch();
    void zero_velocity_acceleration();
    int spawn_owned_object_via_manager(
        int object_id, float x, float y, int direction, int arg5,
        const void *payload, int payload_count);
    void emit_fighter_effect_433cc0(
        int effect_id, float x, float y, int direction, int trailing_value);
    void adjust_counter_482(short amount, int floor_value);
    int add_phase_scaled_counter_558(int amount);

    bool try_dispatch_verified_object818_action();

private:
    unsigned char &byte_at(unsigned offset) {
        return *(reinterpret_cast<unsigned char *>(this) + offset);
    }
    short &short_at(unsigned offset) {
        return *reinterpret_cast<short *>(reinterpret_cast<unsigned char *>(this) + offset);
    }
    int &int_at(unsigned offset) {
        return *reinterpret_cast<int *>(reinterpret_cast<unsigned char *>(this) + offset);
    }
    float &float_at(unsigned offset) {
        return *reinterpret_cast<float *>(reinterpret_cast<unsigned char *>(this) + offset);
    }

    void emit_object818(float *payload) {
        // The target rounds each coordinate to float before passing it. Keep
        // signed facing for the offset and its raw byte for the direction.
        spawn_owned_object_via_manager(
            818, static_cast<float>(static_cast<signed char>(byte_at(0x104)) * 99)
                     + float_at(0xec),
            static_cast<float>(float_at(0xf0) + 145.0),
            byte_at(0x104), 1, payload, 3);
    }

    void emit_object818_phase(int count) {
        if (short_at(0x732) % 6 == 0 && short_at(0x734) < count) {
            float payload[3];
            payload[2] = 0.0f;
            // These are separate tests in the target. Re-read state and
            // coordinates after each call, rather than caching a pair.
            if (short_at(0x734) == 0) {
                payload[0] = -30.0f;
                payload[1] = 10.0f;
                emit_object818(payload);
                payload[0] = -15.0f;
                emit_object818(payload);
            }
            if (short_at(0x734) == 1) {
                payload[0] = -20.0f;
                payload[1] = 20.0f;
                emit_object818(payload);
                payload[0] = -10.0f;
                emit_object818(payload);
            }
            if (short_at(0x734) == 2) {
                payload[0] = -10.0f;
                payload[1] = 30.0f;
                emit_object818(payload);
                payload[0] = -5.0f;
                emit_object818(payload);
            }
            if (count == 4 && short_at(0x734) == 3) {
                payload[0] = -5.0f;
                payload[1] = 40.0f;
                emit_object818(payload);
                payload[0] = -2.5f;
                emit_object818(payload);
            }
            ++short_at(0x734);
        }
        ++short_at(0x732);
    }

    void start_object818_emission(bool second_variant) {
        short_at(0x730) = 1;
        adjust_counter_482(200, 120);
        // 566/568 publish +180 before the scaled-counter helper; 565/567
        // publish it afterwards. Preserve the observed call/store ordering.
        if (second_variant)
            int_at(0x180) = 1;
        add_phase_scaled_counter_558(50);
        if (!second_variant)
            int_at(0x180) = 1;
        dispatch_character_wave_handle(18);
    }
};

bool IkuObject818ActionView::try_dispatch_verified_object818_action()
{
    bool airborne;
    bool second_variant;
    switch (action_id_13c) {
    case 565: airborne = false; second_variant = false; break;
    case 566: airborne = false; second_variant = true;  break;
    case 567: airborne = true;  second_variant = false; break;
    case 568: airborne = true;  second_variant = true;  break;
    default: return false;
    }

    if (!airborne || sequence_index_13e == 2) {
        resolve_stage_surface_landing_transition();
    } else {
        float_at(0xf8) = float_at(0xf8) - float_at(0x100);
        if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
            zero_velocity_acceleration();
            float_at(0xf0) = stage_surface_height_at_x(this);
            select_sequence(2);
            return true;
        }
    }

    byte_at(0x17c) = 7;
    if (int_at(second_variant ? 0x6c4 : 0x6c0) == 0)
        byte_at(0x750) = 0;

    if (short_at(0x730) == 1) {
        if (sequence_index_13e == 0)
            emit_object818_phase(3);
        if (sequence_index_13e == 1)
            emit_object818_phase(4);
    }

    if (advance_frame_and_dispatch())
        set_action_and_finalize(0);

    if (time_counter_144 == 0 && frame_timer_142 == 0 && frame_index_140 == 0) {
        if (sequence_index_13e == 1 || (airborne && sequence_index_13e == 2)) {
            set_action_and_finalize(airborne ? 9 : 0);
            return true;
        }
    }

    if (sequence_index_13e == 0) {
        if (frame_timer_142 == 0) {
            if (frame_index_140 == 5 && byte_at(0x750)) {
                emit_fighter_effect_433cc0(
                    62, float_at(0xec), static_cast<float>(float_at(0xf0) + 150.0),
                    byte_at(0x104), 1);
                next_sequence_block();
                return true;
            }
            if (frame_index_140 == 6)
                start_object818_emission(second_variant);
        }
        if (airborne && frame_timer_142 == 0 && frame_index_140 == 10)
            float_at(0x100) = 0.6f;
    }

    if (sequence_index_13e == 1 && frame_timer_142 == 0) {
        if (frame_index_140 == 2)
            start_object818_emission(second_variant);
        // The shared 62AEDC tail rechecks the timer after the wave call.
        if (airborne && frame_timer_142 == 0 && frame_index_140 == 6)
            float_at(0x100) = 0.6f;
    }
    return true;
}

} // namespace th105
