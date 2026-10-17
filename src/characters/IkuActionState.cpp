#include "AnimationSequenceVirtuals.hpp"

namespace th105 {

int __cdecl selector_random_roll(int limit);
unsigned __cdecl mt19937_next_u32();
float __cdecl atan2_degrees(float y, float x);
// Both target lookup entries return a value loaded from the float table in
// ST0. The retained double declaration carries that value without rounding;
// it does not establish the original source return type.
double __cdecl lookup_orientation_sine_quantized_abs(float phase);
double __cdecl lookup_orientation_cosine_quantized_abs(float phase);
float __cdecl absolute_scalar_float(float value);
extern int g_match_identifier;

class IkuActionStateView;
float __fastcall stage_surface_height_at_x(IkuActionStateView *fighter);
int __fastcall is_y_at_or_below_stage_surface(IkuActionStateView *fighter);
struct IkuEventPairView { void *set_global_pair(float first, float second); };
struct IkuActionScratchView { void reset_fighter_action_scratch(); };

// Natural source recovery for all110 action IDs and the complete root
// prelude/default inside620920. The internal status methods express source
// sharing, not original callable boundaries. Compiler ownership and whole-root
// byte equality must be verified separately from this source hypothesis.
class IkuActionStateView : public AnimationSequenceObjectView {
public:
    unsigned char resolve_stage_surface_landing_transition();
    int has_crossed_stage_surface_while_descending();
    unsigned char advance_frame_and_dispatch();
    void zero_velocity_acceleration();
    void publish_texture_state(signed char index, short duration);
    void face_opponent_and_flip_horizontal_velocity();
    void finalize_sequence_entry(int outcome);
    void copy_action_word_176_to_174();
    void dispatch_indexed_event_member(unsigned index);
    void dispatch_indexed_sequence_window_45c8b0(signed char index, int outcome, int token);
    void advance_secondary_event_effect_cycle();
    signed char set_shared_first_target(signed char enabled, float value);
    signed char set_shared_second_target(signed char enabled, float value);
    signed char set_shared_third_target(signed char enabled, float value);
    void emit_fighter_effect_433cc0(int effect, float x, float y, int direction, int trailing);
    int spawn_owned_object_via_manager(
        int object_id, float x, float y, int direction, int variant,
        const void *payload, int count);

    void adjust_counter_482(short amount, int floor_value);
    int add_phase_scaled_counter_558(int amount);

    __forceinline bool try_dispatch_verified_object818_action();
    __forceinline bool try_dispatch_verified_spell_action();
    __forceinline bool try_dispatch_verified_late_action();
    __forceinline bool try_dispatch_verified_upper_remainder();
    __forceinline bool try_dispatch_verified_upper_action();
    __forceinline bool try_dispatch_verified_middle_action();
    __forceinline bool try_dispatch_verified_action();
    __forceinline bool try_dispatch_verified_opening_action();
    __forceinline bool try_dispatch_verified_glide_action();
    void dispatch_action_state_vslot28();
    void update_common_action_state();
    unsigned char try_dispatch_directional_action_208_210(int option);

private:
    __forceinline unsigned char &byte_at(unsigned offset) {
        return *(reinterpret_cast<unsigned char *>(this) + offset);
    }
    __forceinline short &short_at(unsigned offset) {
        return *reinterpret_cast<short *>(reinterpret_cast<unsigned char *>(this) + offset);
    }
    __forceinline float &float_at(unsigned offset) {
        return *reinterpret_cast<float *>(reinterpret_cast<unsigned char *>(this) + offset);
    }
    __forceinline int &int_at(unsigned offset) {
        return *reinterpret_cast<int *>(reinterpret_cast<unsigned char *>(this) + offset);
    }
    __forceinline int facing() { return static_cast<signed char>(byte_at(0x104)); }
    __forceinline unsigned char reverse_facing() { return static_cast<unsigned char>(-facing()); }
    __forceinline float peer_float(unsigned offset) {
        return *reinterpret_cast<float *>(static_cast<unsigned char *>(related_170) + offset);
    }
    __forceinline unsigned random_roll(int limit) { return static_cast<unsigned>(selector_random_roll(limit)); }
    __forceinline bool sequence_entry(short sequence) {
        return time_counter_144 == 0 && frame_timer_142 == 0
            && frame_index_140 == 0 && sequence_index_13e == sequence;
    }
    __forceinline void advance_or_action(short action) {
        if (advance_frame_and_dispatch())
            set_action_and_finalize(action);
    }
    __forceinline void begin_effect() {
        short_at(0x48a) = 40;
        dispatch_indexed_event_member(23);
    }
    __forceinline void finish_effect(int outcome) {
        dispatch_indexed_sequence_window_45c8b0(0, outcome, 60);
        advance_secondary_event_effect_cycle();
    }
    __forceinline void emit_860_triplet(bool reverse_first) {
        dispatch_character_wave_handle(14);
        float payload[3];
        payload[0] = static_cast<float>(random_roll(360));
        payload[1] = 12.0f;
        payload[2] = 0.0f;
        spawn_owned_object_via_manager(860, float_at(0xec),
            static_cast<float>(float_at(0xf0) + 275.0),
            reverse_first ? reverse_facing() : byte_at(0x104), 1, payload, 3);
        payload[2] = 5.0f;
        spawn_owned_object_via_manager(860, float_at(0xec),
            static_cast<float>(float_at(0xf0) + 275.0), reverse_facing(), 1, payload, 3);
        payload[2] = 6.0f;
        spawn_owned_object_via_manager(860, float_at(0xec),
            static_cast<float>(float_at(0xf0) + 275.0), reverse_facing(), 1, payload, 3);
    }
    __forceinline void emit_six_ring(float speed, bool ahead) {
        for (int angle = 0; angle < 360; angle += 60) {
            unsigned roll = random_roll(30);
            float payload[3];
            payload[0] = static_cast<float>(angle + 30.0 + static_cast<float>(roll));
            payload[1] = speed;
            payload[2] = 2.0f;
            int variant = payload[0] >= 0.0f && payload[0] <= 180.0f ? 1 : -1;
            float x = float_at(0xec);
            if (ahead)
                x = static_cast<float>(facing() * 55) + float_at(0xec);
            spawn_owned_object_via_manager(815, x, float_at(0xf0), byte_at(0x104), variant, payload, 3);
        }
    }
    __forceinline void emit_920_ring(float speed, double offset) {
        // Unlike the integer ring above, the target stores this loop carrier
        // as float and increments it with a floating addition.
        for (float ray = 0.0f; ray < 12.0f; ray += 1.0f) {
            float payload[3];
            payload[0] = static_cast<float>(ray * 30.0 + offset);
            payload[1] = speed;
            payload[2] = 7.0f;
            spawn_owned_object_via_manager(920, float_at(0xec),
                static_cast<float>(float_at(0xf0) + 100.0), byte_at(0x104), 1, payload, 3);
        }
    }
    __forceinline void clamp_x(float upper, float lower) {
        if (float_at(0xf4) > upper) float_at(0xf4) = upper;
        if (float_at(0xf4) < lower) float_at(0xf4) = lower;
    }
    __forceinline void clamp_y(float upper, float lower) {
        if (float_at(0xf8) > upper) float_at(0xf8) = upper;
        if (float_at(0xf8) < lower) float_at(0xf8) = lower;
    }
    __forceinline void steer(bool fixed_limit) {
        ++short_at(0x734);
        float x = static_cast<float>(facing()) * (peer_float(0xec) - float_at(0xec));
        float y = peer_float(0xf0) - float_at(0xf0);
        float_at(0x744) = -atan2_degrees(y, x);
        // Raw code uses FCHS twice, with no subtraction/decrement by one.
        float_at(0xf4) = static_cast<float>(
            lookup_orientation_cosine_quantized_abs(-float_at(0x744)) * 0.5 + float_at(0xf4));
        if (fixed_limit) clamp_x(5.0f, -5.0f);
        float_at(0xf8) = static_cast<float>(
            lookup_orientation_sine_quantized_abs(-float_at(0x744)) * 0.5 + float_at(0xf8));
        if (fixed_limit) {
            clamp_y(5.0f, -5.0f);
        } else {
            float upper, lower;
            if (g_match_identifier == 3) { upper = 6.0f; lower = -6.0f; }
            else if (g_match_identifier == 0) { upper = 4.0f; lower = -4.0f; }
            else { upper = 5.0f; lower = -5.0f; }
            clamp_x(upper, lower);
            clamp_y(upper, lower);
        }
        face_opponent_and_flip_horizontal_velocity();
    }
    __forceinline void restore_surface_motion() {
        float_at(0xf0) = stage_surface_height_at_x(this);
        zero_velocity_acceleration();
    }
    __forceinline void emit_object818(float *payload) {
        // The target rounds each coordinate to float before passing it. Keep
        // signed facing for the offset and its raw byte for the direction.
        spawn_owned_object_via_manager(
            818, static_cast<float>(static_cast<signed char>(byte_at(0x104)) * 99)
                     + float_at(0xec),
            static_cast<float>(float_at(0xf0) + 145.0),
            byte_at(0x104), 1, payload, 3);
    }

    __forceinline void emit_object818_phase(int count) {
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

    __forceinline void start_object818_emission(bool second_variant) {
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
    __forceinline void advance_spell_frame() {
        if (advance_frame_and_dispatch())
            set_action_and_finalize(0);
    }
    __forceinline void begin_spell_effect() {
        short_at(0x48a) = 40;
        dispatch_indexed_event_member(23);
    }
    __forceinline void finish_spell_effect(int outcome) {
        dispatch_indexed_sequence_window_45c8b0(0, outcome, 60);
        advance_secondary_event_effect_cycle();
    }
    __forceinline void emit_object860_triplet(bool reverse_first) {
        dispatch_character_wave_handle(14);
        float payload[3];
        payload[0] = static_cast<float>(random_roll(360));
        payload[1] = 12.0f;
        payload[2] = 0.0f;
        spawn_owned_object_via_manager(860, float_at(0xec),
            static_cast<float>(float_at(0xf0) + 275.0),
            reverse_first ? reverse_facing() : byte_at(0x104), 1, payload, 3);
        payload[2] = 5.0f;
        spawn_owned_object_via_manager(860, float_at(0xec),
            static_cast<float>(float_at(0xf0) + 275.0), reverse_facing(), 1, payload, 3);
        payload[2] = 6.0f;
        spawn_owned_object_via_manager(860, float_at(0xec),
            static_cast<float>(float_at(0xf0) + 275.0), reverse_facing(), 1, payload, 3);
    }
    __forceinline void emit_upper_object(int object, float *payload) {
        spawn_owned_object_via_manager(object,
            static_cast<float>(facing() * 99) + float_at(0xec),
            static_cast<float>(float_at(0xf0) + 145.0),
            byte_at(0x104), 1, payload, 3);
    }
    __forceinline void emit_813_aimed(int variant) {
        float x = static_cast<float>(facing()) * (peer_float(0xec) - float_at(0xec));
        float y = peer_float(0xf0) - float_at(0xf0);
        float_at(0x744) = -atan2_degrees(y, x);
        if (variant == 1) {
            if (float_at(0x744) < -60.0) float_at(0x744) = -60.0f;
            if (float_at(0x744) > -45.0f) float_at(0x744) = -45.0f;
        } else if (variant == 2) {
            if (float_at(0x744) < 45.0f) float_at(0x744) = 45.0f;
            if (float_at(0x744) > 60.0) float_at(0x744) = 60.0f;
        } else {
            if (float_at(0x744) < -10.0f) float_at(0x744) = -10.0f;
            if (float_at(0x744) > 10.0f) float_at(0x744) = 10.0f;
        }
        add_phase_scaled_counter_558(50);
        float payload[3] = {variant == 1 ? -45.0f : variant == 2 ? 45.0f : 0.0f, 17.5f, 0.0f};
        emit_upper_object(813, payload);
        int_at(0x180) = 1;
        dispatch_character_wave_handle(14);
        adjust_counter_482(200, 120);
    }
    __forceinline void emit_823(bool second, bool wave_first) {
        float payload[3] = {second ? -2.0f : 2.0f, 0.0f, 2.0f};
        emit_upper_object(823, payload);
        int_at(0x180) = 1;
        // Only airborne573 publishes the wave before the scaled counter.
        if (wave_first) dispatch_character_wave_handle(22);
        add_phase_scaled_counter_558(50);
        if (!wave_first) dispatch_character_wave_handle(22);
        adjust_counter_482(200, 120);
    }
    __forceinline bool middle_frame(short frame) {
        return frame_timer_142 == 0 && frame_index_140 == frame;
    }
    __forceinline void middle_decelerate(double amount) {
        float_at(0xf4) = static_cast<float>(float_at(0xf4) - amount);
        if (float_at(0xf4) < 0.0f) float_at(0xf4) = 0.0f;
    }
    __forceinline void middle_clear_input(unsigned offset) {
        if (int_at(offset) == 0) byte_at(0x750) = 0;
    }
    __forceinline void middle_cost(int floor, int scaled) {
        adjust_counter_482(200, floor);
        add_phase_scaled_counter_558(scaled);
    }
    __forceinline void spawn_middle(int object, int ahead, double height, float *payload) {
        spawn_owned_object_via_manager(object,
            ahead == 0 ? float_at(0xec) : static_cast<float>(facing() * ahead) + float_at(0xec),
            static_cast<float>(float_at(0xf0) + height), byte_at(0x104), 1, payload, 3);
    }
    __forceinline void middle_ring(int object, int ahead, float speed, bool on_surface) {
        for (int angle = 0; angle < 360; angle += 60) {
            unsigned roll = random_roll(30);
            float payload[3];
            payload[0] = static_cast<float>(angle + 30.0 + static_cast<float>(roll));
            payload[1] = speed;
            payload[2] = 2.0f;
            int variant = payload[0] >= 0.0f && payload[0] <= 180.0f ? 1 : -1;
            float y = on_surface ? stage_surface_height_at_x(this) : float_at(0xf0);
            spawn_owned_object_via_manager(object,
                ahead == 0 ? float_at(0xec) : static_cast<float>(facing() * ahead) + float_at(0xec), y,
                byte_at(0x104), variant, payload, 3);
        }
    }
    __forceinline void middle_fan800(int ahead, double height, double first, int step, int limit) {
        float payload[3] = {0.0f, 8.0f, 0.0f};
        for (int ray = 0; ray < limit; ray += step) {
            payload[0] = static_cast<float>(first - ray);
            spawn_middle(800, ahead, height, payload);
        }
    }
    __forceinline void middle_scatter801(bool second_sequence) {
        float payload[3] = {second_sequence ? 15.0f : 10.0f, 35.0f, 3.0f};
        spawn_middle(801, 70, 140.0, payload);
        payload[0] = second_sequence ? 0.0f : -10.0f;
        spawn_middle(801, 70, 140.0, payload);
        payload[0] = second_sequence ? -15.0f : 20.0f;
        spawn_middle(801, 70, 140.0, payload);
        payload[0] = second_sequence ? 35.0f : -20.0f;
        spawn_middle(801, 70, 140.0, payload);
        if (second_sequence) {
            payload[0] = -35.0f;
            spawn_middle(801, 70, 140.0, payload);
        }
    }
    __forceinline void middle_ground_air_fan(short action) {
        bool airborne = action == 404 || action == 406;
        bool low = action == 402;
        if (!airborne || sequence_index_13e == 2)
            resolve_stage_surface_landing_transition();
        middle_clear_input(0x6c0);
        if (airborne) {
            // These two arms subtract acceleration even in sequence2 and above.
            float_at(0xf8) -= float_at(0x100);
            if (sequence_index_13e < 2 && has_crossed_stage_surface_while_descending()) {
                select_sequence(2);
                restore_surface_motion();
                return;
            }
        }
        advance_or_action(low ? 2 : 0);
        if (sequence_entry(1) || (airborne && sequence_entry(2))) {
            set_action_and_finalize(airborne ? 9 : low ? 2 : 0);
            return;
        }
        int ahead = airborne ? 52 : low ? 55 : 60;
        double height = airborne ? 150.0 : low ? 85.0 : 132.0;
        bool wave_first = action == 400 || action == 406;
        if (sequence_index_13e == 0 && frame_timer_142 == 0) {
            if (frame_index_140 == 4 && byte_at(0x750)) {
                emit_fighter_effect_433cc0(62,
                    float_at(0xec) - static_cast<float>(facing() * 30),
                    static_cast<float>(float_at(0xf0) + (airborne ? 135.0 : low ? 70.0 : 112.0)),
                    byte_at(0x104), 1);
                next_sequence_block();
            }
            if (middle_frame(7)) {
                if (wave_first) dispatch_character_wave_handle(0);
                middle_cost(45, 30);
                int_at(0x180) = 1;
                if (!wave_first) dispatch_character_wave_handle(0);
                middle_fan800(ahead, height, low ? 12.0 : 40.0, low ? 12 : 20, low ? 36 : 100);
            }
            if (airborne && middle_frame(14)) float_at(0x100) = 0.5f;
        }
        if (sequence_index_13e == 1) {
            if (middle_frame(4)) {
                if (wave_first && airborne) dispatch_character_wave_handle(0);
                middle_cost(45, 50);
                int_at(0x180) = 1;
                if (!(wave_first && airborne)) dispatch_character_wave_handle(0);
                middle_fan800(ahead, height, low ? 10.0 : 60.0, low ? 10 : 15, low ? 50 : 135);
            }
            if (airborne && middle_frame(11)) float_at(0x100) = 0.5f;
        }
    }

    __forceinline short peer_short(unsigned offset) {
        return *reinterpret_cast<short *>(static_cast<unsigned char *>(related_170) + offset);
    }
    __forceinline void opening_brake(double amount, bool clear_motion) {
        if (float_at(0xf4) > 0.0f) {
            float_at(0xf4) = static_cast<float>(float_at(0xf4) - amount);
            if (float_at(0xf4) < 0.0f) {
                if (clear_motion) zero_velocity_acceleration();
                else float_at(0xf4) = 0.0f;
                if (clear_motion) byte_at(0x47e) = 0;
            }
        }
        // Keep this second independent test after the first possible store/call.
        if (float_at(0xf4) < 0.0f) {
            float_at(0xf4) = static_cast<float>(float_at(0xf4) + amount);
            if (float_at(0xf4) > 0.0f) {
                if (clear_motion) zero_velocity_acceleration();
                else float_at(0xf4) = 0.0f;
                if (clear_motion) byte_at(0x47e) = 0;
            }
        }
    }
    __forceinline void opening_periodic_effect(bool reverse) {
        double x = static_cast<double>(float_at(0xec)) + 50.0;
        int direction = reverse ? reverse_facing() : byte_at(0x104);
        unsigned y_roll = mt19937_next_u32() % 200U;
        float y = static_cast<float>(y_roll) + float_at(0xf0);
        unsigned x_roll = mt19937_next_u32() % 100U;
        emit_fighter_effect_433cc0(124,
            static_cast<float>(x - static_cast<float>(x_roll)), y, direction, 1);
    }
    __forceinline void opening_effect_pair(bool reverse, bool ahead, double height) {
        float x = ahead ? static_cast<float>(facing() * 80) + float_at(0xec) : float_at(0xec);
        emit_fighter_effect_433cc0(125, x, static_cast<float>(float_at(0xf0) + height),
            reverse ? reverse_facing() : byte_at(0x104), 1);
        emit_fighter_effect_433cc0(126, float_at(0xec), static_cast<float>(float_at(0xf0) + height),
            reverse ? reverse_facing() : byte_at(0x104), 1);
        dispatch_indexed_event_member(31);
    }
    __forceinline void opening_face_on_exit() {
        bool flip = byte_at(0x104) == 1
            ? peer_float(0xec) < float_at(0xec) : float_at(0xec) < peer_float(0xec);
        if (flip) {
            byte_at(0x104) = byte_at(0x104) == 1 ? 255 : reverse_facing();
            float_at(0xf4) = -float_at(0xf4);
        }
    }

};

__forceinline bool IkuActionStateView::try_dispatch_verified_object818_action()
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

__forceinline bool IkuActionStateView::try_dispatch_verified_spell_action()
{
    switch (action_id_13c) {
    case 600:
        // This action reverses the landing/texture call order of its peers.
        resolve_stage_surface_landing_transition();
        publish_texture_state(2, 2);
        advance_spell_frame();
        if (sequence_index_13e != 0 || frame_timer_142 != 0)
            return true;
        if (frame_index_140 == 4) {
            begin_spell_effect();
            emit_fighter_effect_433cc0(115, float_at(0xec),
                static_cast<float>(float_at(0xf0) + 155.0), byte_at(0x104), 1);
            finish_spell_effect(1);
        }
        if (frame_timer_142 == 0 && frame_index_140 == 6) {
            int_at(0x180) = 1;
            dispatch_character_wave_handle(50);
            float payload[3] = {0.0f, 25.0f, 0.0f};
            spawn_owned_object_via_manager(850, static_cast<float>(facing() * 130) + float_at(0xec),
                static_cast<float>(float_at(0xf0) + 140.0), byte_at(0x104), 1, payload, 3);
        }
        return true;

    case 601:
        publish_texture_state(2, 2);
        resolve_stage_surface_landing_transition();
        if (sequence_index_13e == 0 && frame_index_140 >= 7) {
            float adjusted = static_cast<float>(float_at(0xf4) - 0.75);
            float_at(0xf4) = adjusted;
            if (frame_index_140 < 12) {
                if (adjusted < 1.0f)
                    float_at(0xf4) = 1.0f;
            } else if (adjusted < 0.0f) {
                float_at(0xf4) = 0.0f;
            }
            if (int_at(0x180)) {
                ++short_at(0x730);
                if (static_cast<signed char>(byte_at(0x184)) > 0 && short_at(0x730) >= 3) {
                    short_at(0x730) = 0;
                    int_at(0x180) = 0;
                }
            }
        }
        advance_spell_frame();
        if (sequence_index_13e != 0 || frame_timer_142 != 0)
            return true;
        if (frame_index_140 == 4) {
            begin_spell_effect();
            emit_fighter_effect_433cc0(115, float_at(0xec) - static_cast<float>(facing() * 40),
                static_cast<float>(float_at(0xf0) + 190.0), byte_at(0x104), 1);
            finish_spell_effect(3);
        }
        if (frame_timer_142 == 0 && frame_index_140 == 8)
            spawn_owned_object_via_manager(851, static_cast<float>(facing() * 130) + float_at(0xec),
                static_cast<float>(float_at(0xf0) + 125.0), byte_at(0x104), 1, 0, 0);
        if (frame_timer_142 == 0 && frame_index_140 == 7) {
            float_at(0xf4) = 20.0f;
            dispatch_character_wave_handle(10);
            for (int angle = 0; angle < 360; angle += 45) {
                unsigned roll = random_roll(30);
                float payload[3];
                payload[0] = static_cast<float>(angle + 30.0 + static_cast<float>(roll));
                payload[1] = 20.0f;
                payload[2] = 2.0f;
                int variant = payload[0] >= 0.0f && payload[0] <= 180.0f ? 1 : -1;
                spawn_owned_object_via_manager(815, static_cast<float>(facing() * 55) + float_at(0xec),
                    float_at(0xf0), byte_at(0x104), variant, payload, 3);
            }
        }
        return true;

    case 602:
        publish_texture_state(2, 2);
        resolve_stage_surface_landing_transition();
        advance_spell_frame();
        if (sequence_entry(1))
            time_counter_144 = 0;
        if (sequence_index_13e == 0 && frame_timer_142 == 0) {
            if (frame_index_140 == 4) {
                begin_spell_effect();
                emit_fighter_effect_433cc0(115, static_cast<float>(facing() * 58) + float_at(0xec),
                    static_cast<float>(float_at(0xf0) + 85.0), byte_at(0x104), 1);
                finish_spell_effect(3);
            }
            if (frame_timer_142 == 0) {
                if (frame_index_140 == 8) {
                    float payload[3] = {0.0f, 0.0f, 1.0f};
                    spawn_owned_object_via_manager(852, float_at(0xec),
                        static_cast<float>(float_at(0xf0) + 320.0 + 1000.0),
                        byte_at(0x104), 1, payload, 3);
                }
                if (frame_timer_142 == 0 && frame_index_140 == 12) {
                    int_at(0x180) = 1;
                    float payload[3] = {0.0f, 0.0f, 2.0f};
                    spawn_owned_object_via_manager(852, float_at(0xec), float_at(0xf0),
                        byte_at(0x104), 1, payload, 3);
                    payload[2] = 3.0f;
                    spawn_owned_object_via_manager(852, float_at(0xec), float_at(0xf0),
                        reverse_facing(), 1, payload, 3);
                    dispatch_character_wave_handle(12);
                    float_at(0x73c) = static_cast<float>(random_roll(360));
                    for (int angle = 0; angle < 360; angle += 45) {
                        payload[0] = static_cast<float>(angle + 22.5 + float_at(0x73c));
                        payload[1] = 40.0f;
                        payload[2] = 4.0f;
                        int variant = payload[0] >= 0.0f && payload[0] <= 180.0f ? 1 : -1;
                        spawn_owned_object_via_manager(852, float_at(0xec), float_at(0xf0),
                            byte_at(0x104), variant, payload, 3);
                    }
                }
            }
        }
        if (sequence_index_13e != 1)
            return true;
        if (time_counter_144 % 6 == 0) {
            float payload[3] = {0.0f, 0.0f, 5.0f};
            // Target order: selector500 and rounded Y, then selector400.
            float y = static_cast<float>(random_roll(500)) + float_at(0xf0);
            unsigned offset = random_roll(400) - 200U;
            // Keep the unsigned conversion live until the X argument store.
            spawn_owned_object_via_manager(852, static_cast<float>(offset) + float_at(0xec),
                y, byte_at(0x104), 1, payload, 3);
        }
        if (time_counter_144 >= 60)
            next_sequence_block();
        return true;

    case 603:
        publish_texture_state(2, 2);
        resolve_stage_surface_landing_transition();
        if (sequence_index_13e == 1 && time_counter_144 >= 32) {
            next_sequence_block();
            return true;
        }
        advance_spell_frame();
        if (sequence_entry(1))
            time_counter_144 = 0;
        if (sequence_index_13e != 0 || frame_timer_142 != 0)
            return true;
        if (frame_index_140 == 4) {
            begin_spell_effect();
            emit_fighter_effect_433cc0(115, static_cast<float>(facing() * 60) + float_at(0xec),
                static_cast<float>(float_at(0xf0) + 85.0), byte_at(0x104), 1);
            finish_spell_effect(3);
        }
        if (frame_timer_142 == 0 && frame_index_140 == 12) {
            dispatch_character_wave_handle(23);
            float payload[3] = {0.0f, 0.0f, 0.0f};
            spawn_owned_object_via_manager(853, float_at(0xec),
                static_cast<float>(float_at(0xf0) + 360.0), byte_at(0x104), 1, payload, 3);
        }
        return true;

    case 606:
        publish_texture_state(2, 2);
        resolve_stage_surface_landing_transition();
        advance_spell_frame();
        if (sequence_entry(1)) {
            set_action_and_finalize(0);
            return true;
        }
        if (sequence_index_13e != 0 || frame_timer_142 != 0)
            return true;
        if (frame_index_140 == 4) {
            begin_spell_effect();
            emit_fighter_effect_433cc0(115, float_at(0xec),
                static_cast<float>(float_at(0xf0) + 155.0), byte_at(0x104), 1);
            finish_spell_effect(2);
        }
        if (frame_timer_142 == 0 && frame_index_140 == 7) {
            float payload[3] = {0.0f, 20.0f, 0.0f};
            spawn_owned_object_via_manager(856, static_cast<float>(facing() * 99) + float_at(0xec),
                static_cast<float>(float_at(0xf0) + 145.0), byte_at(0x104), 1, payload, 3);
            int_at(0x180) = 1;
            dispatch_character_wave_handle(13);
        }
        return true;

    case 607:
        publish_texture_state(2, 2);
        resolve_stage_surface_landing_transition();
        // These entry gates precede frame advancement in the target.
        if (sequence_index_13e == 0 && frame_timer_142 == 0) {
            if (frame_index_140 == 5) {
                begin_spell_effect();
                emit_fighter_effect_433cc0(115, static_cast<float>(facing() * 12) + float_at(0xec),
                    static_cast<float>(float_at(0xf0) + 138.0), byte_at(0x104), 1);
                finish_spell_effect(4);
            }
            if (frame_timer_142 == 0 && frame_index_140 == 11) {
                float payload[3] = {0.0f, 0.0f, 0.0f};
                spawn_owned_object_via_manager(857, float_at(0xec), float_at(0xf0),
                    byte_at(0x104), 1, payload, 3);
                short_at(0x7b0) = 900;
                dispatch_character_wave_handle(16);
            }
        }
        advance_spell_frame();
        return true;

    case 609:
        publish_texture_state(2, 2);
        resolve_stage_surface_landing_transition();
        if (sequence_index_13e == 1 && time_counter_144 >= 20) {
            next_sequence_block();
            return true;
        }
        advance_spell_frame();
        if (sequence_entry(1)) {
            float payload[3] = {0.0f, 0.0f, 1.0f};
            spawn_owned_object_via_manager(859, float_at(0xec),
                static_cast<float>(float_at(0xf0) + 100.0), byte_at(0x104), -1, payload, 3);
            payload[2] = 2.0f;
            spawn_owned_object_via_manager(859, float_at(0xec),
                static_cast<float>(float_at(0xf0) + 100.0), byte_at(0x104), -1, payload, 3);
            dispatch_character_wave_handle(13);
        }
        if (sequence_index_13e == 0 && frame_timer_142 == 0 && frame_index_140 == 3) {
            begin_spell_effect();
            emit_fighter_effect_433cc0(115, float_at(0xec) - static_cast<float>(facing() * 20),
                static_cast<float>(float_at(0xf0) + 180.0), byte_at(0x104), 1);
            finish_spell_effect(3);
        }
        return true;

    case 610:
        publish_texture_state(2, 2);
        resolve_stage_surface_landing_transition();
        if (sequence_index_13e == 1) {
            if (time_counter_144 % 20 == 0)
                emit_object860_triplet(false);
            if (time_counter_144 % 20 == 10)
                emit_object860_triplet(true);
            if (time_counter_144 >= 120) {
                next_sequence_block();
                return true;
            }
        }
        advance_spell_frame();
        if (sequence_index_13e != 0 || frame_timer_142 != 0)
            return true;
        if (frame_index_140 == 3) {
            begin_spell_effect();
            emit_fighter_effect_433cc0(115, float_at(0xec) - static_cast<float>(facing() * 20),
                static_cast<float>(float_at(0xf0) + 180.0), byte_at(0x104), 1);
            finish_spell_effect(5);
        }
        if (frame_timer_142 == 0 && frame_index_140 == 5) {
            float payload[3];
            payload[0] = static_cast<float>(random_roll(360));
            payload[1] = 0.0f;
            payload[2] = 4.0f;
            spawn_owned_object_via_manager(860, float_at(0xec),
                static_cast<float>(float_at(0xf0) + 275.0), byte_at(0x104), 1, payload, 3);
        }
        return true;
    }
    return false;
}

__forceinline bool IkuActionStateView::try_dispatch_verified_late_action()
{
    switch (action_id_13c) {
    case 650:
        if (sequence_index_13e == 1) {
            resolve_stage_surface_landing_transition();
        } else {
            float_at(0xf8) -= float_at(0x100);
            if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
                zero_velocity_acceleration();
                float_at(0xf0) = stage_surface_height_at_x(this);
                select_sequence(1);
                return true;
            }
        }
        publish_texture_state(2, 2);
        advance_or_action(0);
        if (sequence_entry(1)) { set_action_and_finalize(9); return true; }
        if (sequence_index_13e != 0 || frame_timer_142 != 0) return true;
        if (frame_index_140 == 4) {
            begin_effect();
            emit_fighter_effect_433cc0(115, float_at(0xec),
                static_cast<float>(float_at(0xf0) + 160.0), byte_at(0x104), 1);
            finish_effect(1);
        }
        if (frame_timer_142 == 0 && frame_index_140 == 6) {
            int_at(0x180) = 1;
            dispatch_character_wave_handle(50);
            float payload[3] = {0.0f, 25.0f, 0.0f};
            spawn_owned_object_via_manager(850, static_cast<float>(facing() * 130) + float_at(0xec),
                static_cast<float>(float_at(0xf0) + 145.0), byte_at(0x104), 1, payload, 3);
        }
        if (frame_timer_142 == 0 && frame_index_140 == 9) float_at(0x100) = 0.5f;
        return true;

    case 660:
        publish_texture_state(2, 2);
        if (sequence_index_13e == 1) {
            if (time_counter_144 % 20 == 0) emit_860_triplet(false);
            if (time_counter_144 % 20 == 10) emit_860_triplet(true);
            if (time_counter_144 >= 120) { next_sequence_block(); return true; }
        }
        if (advance_frame_and_dispatch()) {
            set_action_and_finalize(9);
            float_at(0x100) = 0.5f;
            return true;
        }
        if (sequence_index_13e != 0 || frame_timer_142 != 0) return true;
        if (frame_index_140 == 3) {
            begin_effect();
            emit_fighter_effect_433cc0(115, float_at(0xec) - static_cast<float>(facing() * 20),
                static_cast<float>(float_at(0xf0) + 180.0), byte_at(0x104), 1);
            finish_effect(5);
        }
        if (frame_timer_142 == 0 && frame_index_140 == 5) {
            float payload[3] = {static_cast<float>(random_roll(360)), 0.0f, 4.0f};
            spawn_owned_object_via_manager(860, float_at(0xec),
                static_cast<float>(float_at(0xf0) + 275.0), byte_at(0x104), 1, payload, 3);
        }
        return true;

    case 695:
        resolve_stage_surface_landing_transition();
        advance_or_action(0);
        if (sequence_index_13e == 0 && frame_timer_142 == 0 && frame_index_140 == 9) {
            dispatch_indexed_event_member(55);
            emit_fighter_effect_433cc0(140, float_at(0xec), static_cast<float>(float_at(0xf0) + 100.0), byte_at(0x104), 1);
            emit_fighter_effect_433cc0(140, float_at(0xec), static_cast<float>(float_at(0xf0) + 100.0), byte_at(0x104), 1);
            emit_fighter_effect_433cc0(140, float_at(0xec), static_cast<float>(float_at(0xf0) + 100.0), byte_at(0x104), 1);
            emit_fighter_effect_433cc0(141, float_at(0xec), static_cast<float>(float_at(0xf0) + 100.0), byte_at(0x104), -1);
            emit_fighter_effect_433cc0(142, float_at(0xec), float_at(0xf0), byte_at(0x104), -1);
        }
        return true;

    case 696:
        resolve_stage_surface_landing_transition();
        if (float_at(0xf4) > 0.0f) {
            float adjusted = static_cast<float>(float_at(0xf4) - static_cast<double>(0.85f));
            float_at(0xf4) = adjusted;
            if (adjusted < 0.0f) float_at(0xf4) = 0.0f;
        }
        advance_or_action(0);
        if (sequence_index_13e != 0 || frame_timer_142 != 0) return true;
        if (frame_index_140 == 3) float_at(0xf4) = 15.0f;
        if (frame_timer_142 == 0 && frame_index_140 == 4) dispatch_indexed_event_member(29);
        return true;

    case 710:
        if (advance_frame_and_dispatch()) {
            set_action_and_finalize(700);
            face_opponent_and_flip_horizontal_velocity();
        }
        if (sequence_index_13e == 0 && frame_timer_142 == 0 && frame_index_140 == 7) {
            float payload[3] = {0.0f, 0.0f, 5.0f};
            spawn_owned_object_via_manager(900, static_cast<float>(facing() * 99) + float_at(0xec),
                static_cast<float>(float_at(0xf0) + 145.0), byte_at(0x104), 1, payload, 3);
            dispatch_character_wave_handle(13);
        }
        return true;

    case 720:
        if (advance_frame_and_dispatch()) {
            set_action_and_finalize(700);
            face_opponent_and_flip_horizontal_velocity();
        }
        if (sequence_index_13e == 1 && time_counter_144 >= 120) { next_sequence_block(); return true; }
        if (sequence_entry(1)) {
            time_counter_144 = 0;
            float payload[3] = {0.0f, static_cast<float>(short_at(0x76c)), 0.0f};
            spawn_owned_object_via_manager(910, float_at(0xec), float_at(0xf0), byte_at(0x104), 1, payload, 3);
            emit_six_ring(25.0f, false);
        }
        return true;

    case 730:
        if (sequence_index_13e == 2 || sequence_index_13e == 3) float_at(0xf8) -= float_at(0x100);
        if (sequence_index_13e == 5 && time_counter_144 >= 60) { next_sequence_block(); return true; }
        if (sequence_index_13e == 7 || sequence_index_13e == 8) steer(false);
        if (sequence_index_13e == 9 || sequence_index_13e == 10) {
            steer(true);
            // The raw positive test excludes unordered; an inverted <= test
            // would incorrectly select sequence7 for a NaN velocity.
            if (float_at(0xf4) > 0.0f) { select_sequence(7); return true; }
        }
        if (short_at(0x734) >= 360 && sequence_index_13e <= 10) {
            set_action_and_finalize(704);
            float_at(0x100) = 0.2f;
            return true;
        }
        if (advance_frame_and_dispatch()) {
            set_action_and_finalize(700);
            face_opponent_and_flip_horizontal_velocity();
        }
        if (time_counter_144 != 0) return true;
        if (sequence_entry(1)) {
            float_at(0xf8) = 10.0f;
            float_at(0x100) = 0.5f;
            float_at(0xf4) = static_cast<float>(4.0 - static_cast<float>(random_roll(8)));
        }
        if (time_counter_144 != 0) return true;
        if (sequence_entry(4)) zero_velocity_acceleration();
        if (time_counter_144 != 0) return true;
        if (sequence_entry(5)) {
            time_counter_144 = 0;
            float payload[3] = {0.0f, 0.0f, 1.0f};
            spawn_owned_object_via_manager(920, float_at(0xec), static_cast<float>(float_at(0xf0) + 100.0), byte_at(0x104), -1, payload, 3);
            payload[2] = 2.0f;
            spawn_owned_object_via_manager(920, float_at(0xec), static_cast<float>(float_at(0xf0) + 100.0), byte_at(0x104), -1, payload, 3);
            if (g_match_identifier == 1) {
                emit_920_ring(6.0f, 0.0);
            } else if (g_match_identifier == 2) {
                emit_920_ring(6.0f, 0.0);
                emit_920_ring(4.0f, 10.0);
            } else if (g_match_identifier == 3) {
                emit_920_ring(6.0f, 0.0);
                emit_920_ring(4.0f, 10.0);
                emit_920_ring(2.0f, 20.0);
            }
            dispatch_character_wave_handle(13);
        }
        if (sequence_entry(7)) face_opponent_and_flip_horizontal_velocity();
        return true;

    case 740:
        if (sequence_index_13e >= 1 && sequence_index_13e <= 3) {
            ++short_at(0x730);
            if (short_at(0x730) >= 60) {
                select_sequence(4);
                byte_at(0x655) = 1;
                finalize_sequence_entry(-1);
                publish_texture_state(2, -1);
                copy_action_word_176_to_174();
                dispatch_indexed_event_member(23);
                zero_velocity_acceleration();
                short_at(0x4a8) = 60;
                short_at(0x4ac) = 60;
                return true;
            }
            short_at(0x4a8) = 2;
            short_at(0x4ac) = 2;
            float_at(0xf8) -= float_at(0x100);
        }
        advance_or_action(700);
        if (time_counter_144 == 0) {
            if (sequence_entry(1)) {
                byte_at(0x104) = float_at(0xec) >= 640.0f ? 0xff : 1;
                float distance = static_cast<float>(640.0 - float_at(0xec));
                float_at(0xf4) = static_cast<float>(absolute_scalar_float(distance) / 60.0);
                float_at(0xf8) = 10.0f;
                float_at(0x100) = 0.25f;
                short_at(0x730) = 0;
            }
            if (sequence_entry(5)) {
                short_at(0x730) = 0;
                short_at(0x734) = 0;
                time_counter_144 = 0;
                advance_frame_and_dispatch();
                return true;
            }
        }
        // This common tail ignores the return from the second advancement.
        advance_frame_and_dispatch();
        return true;

    case 770:
        advance_or_action(700);
        if (sequence_index_13e == 0 && frame_timer_142 == 0 && frame_index_140 == 10) {
            byte_at(0x655) = 1;
            finalize_sequence_entry(-1);
            publish_texture_state(2, -1);
            copy_action_word_176_to_174();
            short_at(0x76c) = 0;
            short_at(0x76a) = 1;
            short_at(0x766) = 0;
            short_at(0x768) = 0;
            short_at(0x764) = 0;
            dispatch_indexed_event_member(23);
        }
        return true;

    case 780:
        if (sequence_index_13e <= 3) {
            ++short_at(0x736);
            // The target multiplies by the double widening of 0.95f and
            // truncates before any float store: 20 becomes18, not19.
            short_at(0x738) = static_cast<short>(short_at(0x738) * static_cast<double>(0.95f));
            if (short_at(0x736) <= 180) {
                short_at(0x732) += 2;
                float_at(0xf0) = static_cast<float>(lookup_orientation_sine_quantized_abs(
                    static_cast<float>(short_at(0x732))) * 20.0 + (short_at(0x738) + 100));
            } else if (short_at(0x730) < 3) {
                short_at(0x732) += 2;
                float_at(0xf0) = static_cast<float>(lookup_orientation_sine_quantized_abs(
                    static_cast<float>(short_at(0x732))) * 20.0 + 100.0);
            } else {
                short_at(0x732) += 2;
                float adjusted = static_cast<float>(float_at(0xf0) - 1.0);
                float_at(0xf0) = adjusted;
                if (adjusted <= stage_surface_height_at_x(this)) {
                    zero_velocity_acceleration();
                    float_at(0xf0) = stage_surface_height_at_x(this);
                    set_action_and_finalize(700);
                    float_at(0xec) = 800.0f;
                }
            }
            float_at(0x73c) = static_cast<float>(float_at(0x73c) + 2.0);
            float_at(0xec) = static_cast<float>(lookup_orientation_cosine_quantized_abs(float_at(0x73c))
                * float_at(0x740) + 800.0);
            if (sequence_index_13e == 1
                && facing() * lookup_orientation_sine_quantized_abs(float_at(0x73c)) > 0.0) {
                next_sequence_block(); return true;
            }
            if (sequence_index_13e == 3
                && facing() * lookup_orientation_sine_quantized_abs(float_at(0x73c)) < 0.0) {
                select_sequence(0); return true;
            }
            if (short_at(0x730) > 0) {
                if (short_at(0x730) == 1) {
                    short_at(0x730) = 2;
                    float payload[3] = {0.0f, 0.0f, 0.0f};
                    spawn_owned_object_via_manager(898, 800.0f, -100.0f, byte_at(0x104), 1, payload, 3);
                    payload[2] = 1.0f;
                    spawn_owned_object_via_manager(898, 800.0f, -100.0f, byte_at(0x104), -1, payload, 3);
                    payload[2] = 2.0f;
                    spawn_owned_object_via_manager(898, 800.0f, -100.0f, byte_at(0x104), 1, payload, 3);
                    dispatch_character_wave_handle(23);
                }
                if (byte_at(0x112) < 240) {
                    byte_at(0x112) += 15;
                    byte_at(0x111) += 15;
                    byte_at(0x110) += 15;
                } else {
                    byte_at(0x112) = 255;
                    byte_at(0x111) = 255;
                    byte_at(0x110) = 255;
                }
                if (short_at(0x730) == 3) {
                    float adjusted = static_cast<float>(float_at(0x740) - 2.0);
                    float_at(0x740) = adjusted;
                    if (adjusted < 0.0f) float_at(0x740) = 0.0f;
                }
            }
        }
        advance_or_action(700);
        return true;

    case 781:
        ++short_at(0x7b2);
        if (short_at(0x7b2) > 255) short_at(0x7b2) = 255;
        if (sequence_index_13e == 0) {
            if (time_counter_144 % 15 == 0) {
                float payload[3] = {0.0f, 0.0f, static_cast<float>(static_cast<float>(random_roll(2)) + 1.0)};
                unsigned char direction = random_roll(100) < 50 ? 0xff : 1;
                float x = static_cast<float>(random_roll(640));
                spawn_owned_object_via_manager(995, x, -200.0f, direction, 1, payload, 3);
                advance_frame_and_dispatch();
                return true;
            }
        } else if (sequence_index_13e == 1) {
            short_at(0x78c) = 1;
            set_shared_first_target(1, 640.0f);
            set_shared_second_target(1, 0.0f);
            set_shared_third_target(1, 1.0f);
            if (short_at(0x732) == 0) {
                float_at(0x740) = float_at(0x73c) + float_at(0x740);
                float_at(0x73c) = static_cast<float>(float_at(0x73c) - 0.5);
                float_at(0x7b4) = float_at(0x740);
                if (float_at(0x740) <= 0.0f) {
                    float_at(0x740) = 0.0f;
                    short_at(0x732) = 1;
                    float_at(0x7b4) = 0.0f;
                }
            }
            reinterpret_cast<IkuEventPairView *>(reinterpret_cast<unsigned char *>(this) + 0x130)
                ->set_global_pair(0.0f, float_at(0x7b4));
            if (short_at(0x732) == 1) { set_action_and_finalize(700); return true; }
        }
        advance_frame_and_dispatch();
        return true;

    case 795:
        if (sequence_index_13e == 0) {
            float_at(0xf8) = static_cast<float>(float_at(0xf8) - static_cast<double>(0.3f));
            if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
                select_sequence(1);
                restore_surface_motion();
                return true;
            }
        }
        advance_or_action(700);
        return true;

    case 797:
    case 798:
        {
            bool alternate = action_id_13c == 798;
            if (sequence_index_13e == 0 || sequence_index_13e == 1) {
                if (float_at(0xf8) > 0.0f) {
                    select_sequence(2);
                    emit_six_ring(15.0f, true);
                    return true;
                }
                float_at(0xf8) -= float_at(0x100);
            }
            if (sequence_index_13e == 2 || sequence_index_13e == 3) {
                float adjusted = static_cast<float>(float_at(0xf4) * static_cast<double>(0.93f));
                float_at(0xf4) = adjusted;
                if (adjusted < 2.0f) {
                    ++short_at(0x730);
                    if (short_at(0x730) >= 20) { select_sequence(4); return true; }
                }
                float acceleration = static_cast<float>(float_at(0x100) * static_cast<double>(0.95f));
                float_at(0x100) = acceleration;
                float_at(0xf8) -= acceleration;
            }
            if (sequence_index_13e == 4 || sequence_index_13e == 5) {
                float_at(0xf8) = static_cast<float>(float_at(0xf8) - static_cast<double>(0.15f));
                float_at(0xf4) = static_cast<float>(float_at(0xf4) - static_cast<double>(0.1f));
                if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
                    set_action_and_finalize(alternate ? 709 : 10);
                    float_at(0xec) = alternate ? 800.0f : 480.0f;
                    restore_surface_motion();
                    return true;
                }
            }
            advance_frame_and_dispatch();
            return true;
        }
    }
    return false;
}

__forceinline bool IkuActionStateView::try_dispatch_verified_upper_remainder()
{
    bool airborne, second;
    switch (action_id_13c) {
    case 560: case 561: case 562: case 563:
        airborne = action_id_13c >= 562;
        second = action_id_13c == 561 || action_id_13c == 563;
        if (!airborne || sequence_index_13e == 2)
            resolve_stage_surface_landing_transition();
        byte_at(0x17c) = 3;
        if (int_at(second ? 0x6c4 : 0x6c0) == 0)
            byte_at(0x750) = 0;
        if (airborne && sequence_index_13e < 2) {
            float_at(0xf8) -= float_at(0x100);
            if (has_crossed_stage_surface_while_descending()) {
                zero_velocity_acceleration();
                float_at(0xf0) = stage_surface_height_at_x(this);
                select_sequence(2);
                return true;
            }
        }
        advance_or_action(0);
        if (sequence_entry(1) || (airborne && sequence_entry(2))) {
            set_action_and_finalize(airborne ? 9 : 0);
            return true;
        }
        if (sequence_index_13e == 0) {
            if (frame_timer_142 == 0 && frame_index_140 == 7)
                emit_813_aimed(second ? (airborne ? 2 : 1) : 0);
            if (frame_timer_142 == 0 && frame_index_140 == 8 && byte_at(0x750)) {
                next_sequence_block();
                return true;
            }
            if (airborne && frame_timer_142 == 0 && frame_index_140 == 9)
                float_at(0x100) = 0.5f;
        }
        if (airborne && sequence_index_13e == 1 && frame_timer_142 == 0 && frame_index_140 == 2)
            float_at(0x100) = 0.5f;
        return true;

    case 570: case 571: case 572: case 573:
        airborne = action_id_13c >= 572;
        second = action_id_13c == 571 || action_id_13c == 573;
        if (!airborne || sequence_index_13e == 1)
            resolve_stage_surface_landing_transition();
        byte_at(0x17c) = 11;
        if (airborne && sequence_index_13e < 1) {
            float_at(0xf8) -= float_at(0x100);
            if (has_crossed_stage_surface_while_descending()) {
                zero_velocity_acceleration();
                float_at(0xf0) = stage_surface_height_at_x(this);
                select_sequence(1);
                return true;
            }
        }
        advance_or_action(0);
        if (airborne && sequence_entry(1)) {
            set_action_and_finalize(9);
            return true;
        }
        if (sequence_index_13e == 0 && frame_timer_142 == 0) {
            if (frame_index_140 == 7)
                emit_823(second, airborne && second);
            if (airborne && frame_timer_142 == 0 && frame_index_140 == 9)
                float_at(0x100) = 0.5f;
        }
        return true;

    case 599:
        if (short_at(0x730) > 0 && frame_index_140 < 7 && short_at(0x730) < 12) {
            short_at(0x734) = static_cast<short>(mt19937_next_u32() % 35U);
            float payload[3];
            payload[0] = static_cast<float>(-20 - short_at(0x734));
            payload[1] = static_cast<float>(static_cast<short>(mt19937_next_u32() % 5U + 10U));
            payload[2] = 0.0f;
            spawn_owned_object_via_manager(807,
                static_cast<float>((short_at(0x730) + 1) * facing() * 20) + float_at(0xec),
                float_at(0xf0), byte_at(0x104), 1, payload, 3);
            payload[0] = static_cast<float>(mt19937_next_u32() % 360U);
            payload[1] = 0.0f;
            payload[2] = 1.0f;
            spawn_owned_object_via_manager(801,
                static_cast<float>((short_at(0x730) + 1) * facing() * 20) + float_at(0xec),
                float_at(0xf0), byte_at(0x104), 1, payload, 3);
            if (short_at(0x730) == 1) {
                dispatch_character_wave_handle(0);
                adjust_counter_482(200, 120);
            }
            ++short_at(0x730);
        }
        advance_or_action(0);
        if (frame_timer_142 == 0 && frame_index_140 == 5)
            short_at(0x730) = 1;
        return true;
    default:
        return false;
    }
}

__forceinline bool IkuActionStateView::try_dispatch_verified_upper_action()
{
    if (try_dispatch_verified_object818_action()) return true;
    if (try_dispatch_verified_spell_action()) return true;
    if (try_dispatch_verified_late_action()) return true;
    return try_dispatch_verified_upper_remainder();
}

__forceinline bool IkuActionStateView::try_dispatch_verified_middle_action()
{
    const short action = action_id_13c;
    switch (action) {
    case 300: case 301: case 302: case 303: case 304: case 305:
    case 320: case 321: case 322: {
        resolve_stage_surface_landing_transition();
        int option = action == 302 || action == 304 || action == 305 || action == 322 ? 1 : 0;
        if (try_dispatch_directional_action_208_210(option)) return true;
        if (action == 300 || action == 301 || action == 303) {
            bool braking = action == 303 ? static_cast<signed char>(byte_at(0x47e)) > 0 : byte_at(0x47e) != 0;
            if (braking) {
                float_at(0xf4) = static_cast<float>(float_at(0xf4) -
                    (action == 303 ? static_cast<double>(0.6f) : 0.5));
                if (float_at(0xf4) < 0.0f) {
                    float_at(0xf4) = 0.0f;
                    byte_at(0x47e) = 0;
                }
            }
            if (action == 301 && frame_index_140 > 4) middle_decelerate(1.5);
        }
        if (action == 302) {
            middle_clear_input(0x6bc);
            if (sequence_index_13e == 0 || sequence_index_13e == 1) {
                if (float_at(0xf4) > 0.0f)
                    float_at(0xf4) = static_cast<float>(float_at(0xf4) - (sequence_index_13e == 0 ? 0.5 : 1.0));
                if (float_at(0xf4) < 0.0f) float_at(0xf4) = 0.0f;
            }
        }
        if (action == 304) { middle_clear_input(0x6bc); middle_decelerate(0.5); }
        if ((action == 305 || action == 321) && frame_index_140 > 3) middle_decelerate(0.5);
        if (action == 320 && frame_index_140 > 1) middle_decelerate(2.0);
        if (action == 322 && frame_index_140 > 5) middle_decelerate(3.0);
        advance_or_action(action == 303 || action == 304 ? 2 : 0);
        if (action == 300 && middle_frame(4)) {
            float payload[3] = {0.0f, 0.0f, 6.0f};
            spawn_middle(899, 96, 129.0, payload);
            dispatch_indexed_event_member(27);
            byte_at(0x47e) = 0;
        }
        if (action == 301) {
            if (middle_frame(3)) float_at(0xf4) = 10.0f;
            if (middle_frame(4)) { middle_ring(815, 155, 25.0f, false); dispatch_indexed_event_member(28); byte_at(0x47e) = 0; }
        }
        if (action == 302) {
            if (sequence_entry(1)) { set_action_and_finalize(0); return true; }
            if (sequence_index_13e == 0) {
                if (middle_frame(5)) {
                    if (byte_at(0x750)) {
                        next_sequence_block();
                        emit_fighter_effect_433cc0(62, float_at(0xec), static_cast<float>(float_at(0xf0) + 150.0), byte_at(0x104), 1);
                        return true;
                    }
                    float_at(0xf4) = 11.0f;
                }
                if (middle_frame(6)) { dispatch_indexed_event_member(29); middle_ring(815, 125, 25.0f, false); }
            }
            if (sequence_index_13e == 1) {
                if (middle_frame(1)) float_at(0xf4) = 20.0f;
                if (middle_frame(2)) { dispatch_indexed_event_member(29); middle_ring(815, 125, 25.0f, false); }
            }
        }
        if (action == 303 && middle_frame(5)) dispatch_indexed_event_member(28);
        if (action == 304) {
            if (sequence_entry(1)) { set_action_and_finalize(2); return true; }
            if (sequence_index_13e == 0) {
                if (middle_frame(3) && byte_at(0x750) == 1) {
                    next_sequence_block();
                    emit_fighter_effect_433cc0(62, static_cast<float>(facing() * 11) + float_at(0xec),
                        static_cast<float>(float_at(0xf0) + 88.0), byte_at(0x104), 1);
                    return true;
                }
                if (middle_frame(4)) { float_at(0xf4) = 15.0f; dispatch_indexed_event_member(29); }
                if (middle_frame(5)) float_at(0xf4) = 7.5f;
            }
            if (sequence_index_13e == 1) {
                if (middle_frame(2)) { float_at(0xf4) = 25.0f; dispatch_indexed_event_member(29); }
                if (middle_frame(3)) { float_at(0xf4) = 10.0f; middle_ring(815, 155, 25.0f, false); }
            }
        }
        if (action == 305 && middle_frame(4)) dispatch_indexed_event_member(29);
        if ((action == 320 || action == 321) && middle_frame(5)) { dispatch_indexed_event_member(28); byte_at(0x47e) = 0; }
        if (action == 321 && middle_frame(10)) { dispatch_indexed_event_member(29); int_at(0x180) = 0; byte_at(0x184) = 1; }
        if (action == 322) {
            if (middle_frame(5)) { dispatch_indexed_event_member(29); float_at(0xf4) = 15.0f; byte_at(0x47e) = 0; }
            if (middle_frame(6)) { float payload[3] = {0.0f, 0.0f, 5.0f}; spawn_middle(899, 166, 137.0, payload); }
            if (middle_frame(7)) float_at(0xf4) = 0.0f;
        }
        return true;
    }
    case 306: case 307: case 308: case 309: case 409: {
        if (action == 307 || action == 308) middle_clear_input(0x6bc);
        float_at(0xf8) -= float_at(0x100);
        if (has_crossed_stage_surface_while_descending()) {
            set_action_and_finalize(10);
            if (action == 306) {
                float_at(0xf0) = stage_surface_height_at_x(this);
                float_at(0x100) = 0.0f;
                float_at(0xf8) = 0.0f;
            } else if (action == 409) {
                zero_velocity_acceleration();
                float_at(0xf0) = stage_surface_height_at_x(this);
            } else restore_surface_motion();
            return true;
        }
        if (action == 309 && sequence_index_13e == 1) {
            float_at(0xf4) = static_cast<float>(float_at(0x73c) * static_cast<double>(0.3f));
            float_at(0xf8) = float_at(0x73c);
            float_at(0x73c) = static_cast<float>(float_at(0x73c) - 1.0);
            if (float_at(0x73c) <= 4.0f) float_at(0x73c) = 4.0f;
            if (static_cast<signed char>(byte_at(0x184)) > 0 && int_at(0x180) != 0) {
                if (++short_at(0x730) > 3) { int_at(0x180) = 0; short_at(0x730) = 0; }
            }
            if (time_counter_144 > 14) { next_sequence_block(); float_at(0x100) = 0.6f; return true; }
        }
        advance_or_action(9);
        if (action == 306 && sequence_index_13e == 0 && middle_frame(4)) dispatch_indexed_event_member(28);
        if (action == 307 || action == 308) {
            if (sequence_entry(1)) { set_action_and_finalize(9); return true; }
            if (sequence_index_13e == 0) {
                if (action == 307 && middle_frame(2)) { float_at(0xf4) = 3.0f; float_at(0xf8) = 5.0f; float_at(0x100) = 0.3f; }
                if (middle_frame(4)) dispatch_indexed_event_member(29);
                if (middle_frame(7)) float_at(0x100) = 0.6f;
            }
        }
        if (action == 309 && sequence_entry(1)) {
            float_at(0x73c) = 15.0f; float_at(0x100) = 0.0f; dispatch_indexed_event_member(29);
        }
        return true;
    }
    case 310:
        if (int_at(0x180) != 0 && ++short_at(0x730) > 5) { int_at(0x180) = 0; short_at(0x730) = 0; }
        if (sequence_index_13e == 1) {
            if (time_counter_144 == 0) float_at(0xf4) = 15.0f;
            if (time_counter_144 % 8 == 0) dispatch_indexed_event_member(27);
            // The second increment in sequence1 is distinct and intentional.
            if (int_at(0x180) != 0 && ++short_at(0x730) > 5) { int_at(0x180) = 0; short_at(0x730) = 0; }
            if (time_counter_144 > 30) { next_sequence_block(); float_at(0xf8) = 6.0f; float_at(0xf4) = static_cast<float>(float_at(0xf4) * 0.5); }
        }
        if (sequence_index_13e == 2) {
            float_at(0xf8) -= float_at(0x100);
            double projected_y = static_cast<double>(float_at(0xf8)) + float_at(0xf0);
            float surface = stage_surface_height_at_x(this);
            if (projected_y <= surface && float_at(0xf8) < 0.0f) {
                float_at(0xf8) = 0.0f; float_at(0xf0) = stage_surface_height_at_x(this); set_action_and_finalize(9); return true;
            }
        }
        advance_or_action(9);
        return true;

    case 400: case 401: case 402: case 404: case 406:
        middle_ground_air_fan(action);
        return true;
    case 408:
        resolve_stage_surface_landing_transition();
        if (frame_index_140 > 6) float_at(0xf4) = static_cast<float>(float_at(0xf4) - 0.75);
        if (float_at(0xf4) < 0.0f) float_at(0xf4) = 0.0f;
        advance_or_action(0);
        if (middle_frame(6)) {
            float payload[3] = {0.0f, 0.0f, 4.0f}; spawn_middle(899, 166, 137.0, payload);
            dispatch_indexed_event_member(29); byte_at(0x47e) = 0;
        }
        return true;

    case 410: case 411: case 414: case 415: case 416: case 417: {
        bool airborne = action >= 414;
        if (!airborne || sequence_index_13e == 2) resolve_stage_surface_landing_transition();
        middle_clear_input(0x6c4);
        if (airborne && sequence_index_13e < 2) {
            float_at(0xf8) -= float_at(0x100);
            if (has_crossed_stage_surface_while_descending()) {
                select_sequence(2); restore_surface_motion(); return true;
            }
        }
        advance_or_action(0);
        if (sequence_entry(1) || (airborne && sequence_entry(2))) {
            set_action_and_finalize(airborne ? 9 : 0); return true;
        }
        if (sequence_index_13e == 0) {
            if (frame_timer_142 == 0) {
                if (frame_index_140 == (action >= 416 ? 3 : 5) && byte_at(0x750)) {
                    float x = action >= 416 ? float_at(0xec) - static_cast<float>(facing() * 47) : float_at(0xec);
                    emit_fighter_effect_433cc0(62, x,
                        static_cast<float>(float_at(0xf0) + (action >= 416 ? 132.0 : airborne ? 155.0 : 160.0)), byte_at(0x104), 1);
                    next_sequence_block();
                    if (action >= 416) return true;
                }
                if (middle_frame(action >= 416 ? 4 : 6)) {
                    bool publish_first = action == 410 || action == 411 || action == 415;
                    if (publish_first) int_at(0x180) = 1;
                    middle_cost(60, 50);
                    if (!publish_first) int_at(0x180) = 1;
                    dispatch_character_wave_handle(1);
                    if (action == 411 || action == 415) middle_scatter801(false);
                    else {
                        float payload[3] = {action == 416 ? 30.0f : action == 417 ? 50.0f : 0.0f, 15.0f, action >= 416 ? 5.0f : 0.0f};
                        spawn_middle(801, action == 416 ? 62 : action == 417 ? 46 : 130,
                            action == 416 ? 114.0 : action == 417 ? 106.0 : airborne ? 145.0 : 140.0, payload);
                    }
                }
            }
            if (airborne && middle_frame(action >= 416 ? 7 : 9)) float_at(0x100) = 0.5f;
        }
        if (sequence_index_13e == 1) {
            if (middle_frame(2)) {
                middle_cost(60, 50); int_at(0x180) = 1; dispatch_character_wave_handle(1);
                if (action == 411 || action == 415) middle_scatter801(true);
                else {
                    float payload[3] = {action == 416 ? 30.0f : action == 417 ? 50.0f : 0.0f, action >= 416 ? 15.0f : 22.5f, action >= 416 ? 5.0f : 0.0f};
                    spawn_middle(801, action == 416 ? 62 : action == 417 ? 46 : 130,
                        action == 416 ? 114.0 : action == 417 ? 106.0 : airborne ? 145.0 : 140.0, payload);
                    if (action >= 416) { payload[0] = action == 416 ? 50.0f : 70.0f; spawn_middle(801, action == 416 ? 62 : 46, action == 416 ? 114.0 : 106.0, payload); }
                }
            }
            if (airborne && middle_frame(action >= 416 ? 6 : 5)) float_at(0x100) = 0.5f;
        }
        return true;
    }
    case 412:
        if ((sequence_index_13e == 0 && frame_index_140 > 1) || sequence_index_13e == 1) {
            float_at(0xf8) -= float_at(0x100);
            float_at(0xf4) = static_cast<float>(float_at(0xf4) - static_cast<double>(0.1f));
            if (float_at(0xf4) < 1.0f) float_at(0xf4) = 1.0f;
            if (has_crossed_stage_surface_while_descending()) {
                zero_velocity_acceleration(); float_at(0xf0) = stage_surface_height_at_x(this); select_sequence(2); return true;
            }
        } else resolve_stage_surface_landing_transition();
        advance_or_action(0);
        if (sequence_index_13e == 0) {
            if (middle_frame(2)) { float_at(0xf4) = 6.0f; float_at(0xf8) = 6.0f; float_at(0x100) = 0.2f; }
            if (middle_frame(9)) {
                middle_cost(60, 50); int_at(0x180) = 1; dispatch_character_wave_handle(16);
                float payload[3] = {-20.0f, 13.0f, 0.0f}; spawn_middle(802, 75, 168.0, payload);
                middle_ring(802, 0, 15.0f, true);
            }
        }
        return true;
    case 418:
        if (sequence_index_13e == 2) resolve_stage_surface_landing_transition();
        if (is_y_at_or_below_stage_surface(this)) float_at(0xf4) = static_cast<float>(float_at(0xf4) - 0.5);
        if (float_at(0xf4) < 0.0f) float_at(0xf4) = 0.0f;
        if (sequence_index_13e < 2) float_at(0xf8) -= float_at(0x100);
        if (has_crossed_stage_surface_while_descending()) {
            zero_velocity_acceleration(); float_at(0xf0) = stage_surface_height_at_x(this); select_sequence(2); return true;
        }
        advance_or_action(0);
        if (sequence_index_13e == 0) {
            if (middle_frame(2)) { float_at(0xf4) = 7.5f; float_at(0xf8) = 5.0f; float_at(0x100) = 0.3f; }
            if (middle_frame(9)) dispatch_indexed_event_member(29);
        }
        return true;

    case 500: case 501:
        resolve_stage_surface_landing_transition(); byte_at(0x17c) = 0;
        if (sequence_index_13e == 0 && frame_index_140 > 6) {
            float_at(0xf4) = static_cast<float>(float_at(0xf4) - 0.75);
            float lower = frame_index_140 < 12 ? 1.0f : 0.0f;
            if (float_at(0xf4) < lower) float_at(0xf4) = lower;
            if (int_at(0x180) != 0) {
                ++short_at(0x730);
                if (static_cast<signed char>(byte_at(0x184)) > 0 && short_at(0x730) > 4) { short_at(0x730) = 0; int_at(0x180) = 0; }
            }
        }
        advance_or_action(0);
        if (sequence_index_13e == 0) {
            if (middle_frame(8)) spawn_owned_object_via_manager(810,
                static_cast<float>(facing() * 130) + float_at(0xec), static_cast<float>(float_at(0xf0) + 125.0), byte_at(0x104), 1, 0, 0);
            if (middle_frame(7)) { add_phase_scaled_counter_558(50); adjust_counter_482(200, 120); float_at(0xf4) = action == 500 ? 10.0f : 15.0f; dispatch_character_wave_handle(10); }
        }
        return true;
    case 505: case 506: {
        resolve_stage_surface_landing_transition(); byte_at(0x17c) = 4;
        middle_clear_input(action == 505 ? 0x6c0 : 0x6c4);
        advance_or_action(0);
        if (sequence_entry(1)) set_action_and_finalize(0);
        if (sequence_index_13e == 0 && frame_timer_142 == 0) {
            if (frame_index_140 == 7 && byte_at(0x750) == 1) {
                next_sequence_block();
                emit_fighter_effect_433cc0(62, float_at(0xec) - static_cast<float>(facing() * 41),
                    static_cast<float>(float_at(0xf0) + 192.0), byte_at(0x104), 1); return true;
            }
            if (frame_index_140 == 10) {
                float payload[3] = {0.0f, 0.0f, action == 505 ? 0.0f : 3.0f};
                spawn_middle(815, 150, action == 505 ? 120.0 : 195.0, payload);
                add_phase_scaled_counter_558(50); adjust_counter_482(200, 120);
                middle_ring(815, 55, 20.0f, false); dispatch_character_wave_handle(19);
            }
        }
        if (sequence_index_13e == 1 && middle_frame(4)) {
            float payload[3] = {0.0f, 0.0f, action == 505 ? 1.0f : 4.0f};
            spawn_middle(815, 150, action == 505 ? 120.0 : 195.0, payload);
            add_phase_scaled_counter_558(50); adjust_counter_482(200, 120);
            middle_ring(815, 55, 20.0f, false); dispatch_character_wave_handle(19);
        }
        return true;
    }
    case 520: case 521:
        resolve_stage_surface_landing_transition(); byte_at(0x17c) = 1;
        if (sequence_index_13e == 0) {
            if (middle_frame(3)) adjust_counter_482(200, 120);
            if (middle_frame(10)) {
                middle_ring(815, 55, 25.0f, false); add_phase_scaled_counter_558(50);
                float payload[3] = {0.0f, 0.0f, 1.0f};
                spawn_owned_object_via_manager(811, float_at(0xec), float_at(0xf0), byte_at(0x104), -1, payload, 3);
                dispatch_character_wave_handle(11);
            }
        }
        advance_or_action(0);
        return true;
    case 525: case 526:
        resolve_stage_surface_landing_transition(); byte_at(0x17c) = 5; advance_or_action(0);
        if (sequence_index_13e == 0 && middle_frame(9)) {
            float payload[3] = {0.0f, 10.0f, action == 525 ? 0.0f : 6.0f}; spawn_middle(816, 90, 105.0, payload);
            add_phase_scaled_counter_558(50); adjust_counter_482(200, 120); dispatch_character_wave_handle(16); int_at(0x180) = 1;
        }
        return true;
    case 540: case 541:
        resolve_stage_surface_landing_transition(); byte_at(0x17c) = 2;
        middle_clear_input(action == 540 ? 0x6c0 : 0x6c4); advance_or_action(0);
        if (sequence_entry(1)) { set_action_and_finalize(0); return true; }
        if (sequence_index_13e == 0) {
            if (frame_index_140 > 5 && frame_index_140 < 14 && static_cast<signed char>(byte_at(0x606)) > 3) short_at(0x4a8) = 2;
            if (middle_frame(8)) {
                add_phase_scaled_counter_558(50); adjust_counter_482(200, 120);
                float payload[3] = {0.0f, 0.0f, 1.0f};
                spawn_owned_object_via_manager(812, float_at(0xec), static_cast<float>((float_at(0xf0) + 320.0) + 1000.0),
                    byte_at(0x104), 1, payload, 3);
            }
            if (middle_frame(12)) {
                int_at(0x180) = 1; float payload[3] = {0.0f, 0.0f, 2.0f}; spawn_middle(812, 0, 320.0, payload);
                payload[2] = 3.0f;
                spawn_owned_object_via_manager(812, float_at(0xec), static_cast<float>(float_at(0xf0) + 320.0), reverse_facing(), 1, payload, 3);
                dispatch_character_wave_handle(13); float_at(0x73c) = static_cast<float>(random_roll(360));
                for (int angle = 0; angle < 360; angle += 45) {
                    payload[0] = static_cast<float>(angle + 22.5 + float_at(0x73c)); payload[1] = 30.0f; payload[2] = 4.0f;
                    int variant = payload[0] >= 0.0f && payload[0] <= 180.0f ? 1 : -1;
                    spawn_owned_object_via_manager(812, float_at(0xec), float_at(0xf0), byte_at(0x104), variant, payload, 3);
                }
            }
        }
        if (sequence_index_13e == 1 && frame_index_140 == 0 && !byte_at(0x750)) {
            select_sequence(0); frame_index_140 = 7;
        }
        return true;
    case 545: case 546:
        resolve_stage_surface_landing_transition(); byte_at(0x17c) = 6; advance_or_action(0);
        if (sequence_entry(1)) { set_action_and_finalize(0); return true; }
        if (sequence_index_13e == 0 && middle_frame(12)) {
            add_phase_scaled_counter_558(50); adjust_counter_482(200, 120); int_at(0x180) = 1;
            float payload[3] = {0.0f, action == 545 ? 0.0f : 1.0f, 0.0f}; spawn_middle(817, 0, 320.0, payload);
            payload[2] = 5.0f; spawn_middle(817, 0, 320.0, payload); dispatch_character_wave_handle(17);
        }
        return true;
    case 547:
        if (sequence_index_13e == 2) resolve_stage_surface_landing_transition();
        byte_at(0x17c) = 2;
        if (sequence_index_13e < 2) {
            float_at(0xf8) -= float_at(0x100);
            double projected_y = static_cast<double>(float_at(0xf8)) + float_at(0xf0);
            float surface = stage_surface_height_at_x(this);
            if (projected_y <= surface && float_at(0xf8) < 0.0f) {
                zero_velocity_acceleration(); select_sequence(2); float_at(0xf0) = stage_surface_height_at_x(this); return true;
            }
        }
        if (sequence_index_13e < 2) middle_clear_input(0x6c0);
        advance_or_action(9);
        if (sequence_entry(1)) { set_action_and_finalize(9); return true; }
        if (sequence_index_13e == 0 && frame_timer_142 == 0) {
            if (frame_index_140 == 8 && byte_at(0x750) == 1) { next_sequence_block(); return true; }
            if (frame_index_140 == 6) {
                int_at(0x180) = 1; dispatch_character_wave_handle(7); float_at(0xf4) = -4.0f; float_at(0xf8) = 8.0f; float_at(0x100) = 0.5f;
                spawn_owned_object_via_manager(816, static_cast<float>(facing() * 30) + float_at(0xec),
                    static_cast<float>(float_at(0xf0) + 62.0), byte_at(0x104), 1, 0, 0);
                adjust_counter_482(200, 120); add_phase_scaled_counter_558(50);
            }
        }
        return true;
    default:
        return false;
    }
}

__forceinline bool IkuActionStateView::try_dispatch_verified_action()
{
    if (try_dispatch_verified_middle_action()) return true;
    if (try_dispatch_verified_upper_action()) return true;
    return try_dispatch_verified_opening_action();
}

__forceinline bool IkuActionStateView::try_dispatch_verified_opening_action()
{
    const short action = action_id_13c;
    switch (action) {
    case 0: case 1: case 2: case 3:
        resolve_stage_surface_landing_transition();
        if (action == 0 && float_at(0xf4) == 0.0f) byte_at(0x47e) = 0;
        if (!byte_at(0x47e)) zero_velocity_acceleration();
        else opening_brake(0.5, true);
        if (advance_frame_and_dispatch() && frame_index_140 == 0) {
            if (action == 1) set_action_and_finalize(2);
            if (action == 3) set_action_and_finalize(0);
        }
        return true;
    case 4: case 5:
        resolve_stage_surface_landing_transition();
        float_at(0xf4) = action == 4 ? 2.5f : -3.0f;
        advance_frame_and_dispatch();
        return true;
    case 6: case 7: case 8:
        if (sequence_index_13e == 0) {
            resolve_stage_surface_landing_transition();
            if (sequence_index_13e == 0 && !byte_at(0x47e)) zero_velocity_acceleration();
        }
        if (sequence_index_13e > 0) {
            float_at(0xf8) -= float_at(0x100);
            if (has_crossed_stage_surface_while_descending()) {
                set_action_and_finalize(10); restore_surface_motion(); return true;
            }
        }
        advance_frame_and_dispatch();
        if (sequence_entry(1)) {
            float_at(0xf4) = action == 6 ? 0.0f : action == 7 ? 3.5f : -3.5f;
            float_at(0xf8) = action == 6 ? 12.0f : 11.0f;
            float_at(0x100) = 0.35f; byte_at(0x47e) = 0;
        }
        return true;
    case 9:
        if (float_at(0x100) == 0.0f) float_at(0x100) = 0.6f;
        float_at(0xf8) -= float_at(0x100);
        if (has_crossed_stage_surface_while_descending()) { set_action_and_finalize(10); restore_surface_motion(); }
        else advance_frame_and_dispatch();
        return true;
    case 10:
        resolve_stage_surface_landing_transition(); zero_velocity_acceleration();
        if (advance_frame_and_dispatch()) set_action_and_finalize(int_at(0x6b8) != 0 ? 2 : 0);
        return true;

    case 197: case 198: case 199:
        if (action == 199 || sequence_index_13e == 0 || sequence_index_13e == 2)
            resolve_stage_surface_landing_transition();
        if (action != 199 && sequence_index_13e == 1 && time_counter_144 > 39) {
            zero_velocity_acceleration(); select_sequence(2); return true;
        }
        if (advance_frame_and_dispatch()) {
            if (byte_at(0x72c) == 2) {
                set_action_and_finalize(700); short_at(0x4a8) = 3; short_at(0x4ac) = 3;
                return true;
            }
            set_action_and_finalize(0);
            if (int_at(0x6b8) > 0) set_action_and_finalize(1);
        }
        if ((action == 199 ? sequence_index_13e == 0 && middle_frame(5) : sequence_index_13e == 2 && middle_frame(3))) {
            if (peer_float(0xec) < float_at(0xec)) byte_at(0x104) = 255;
            if (float_at(0xec) < peer_float(0xec)) byte_at(0x104) = 1;
        }
        if (action != 199 && sequence_entry(1)) float_at(0xf4) = action == 197 ? 14.5f : -14.5f;
        return true;

    case 200: case 223:
        if (action == 200 && short_at(0x7b0) > 0) short_at(0x4a8) = 2;
        resolve_stage_surface_landing_transition(); byte_at(0x47e) = 1;
        if (action == 223 && short_at(0x7b0) > 0) short_at(0x4a8) = 2;
        advance_frame_and_dispatch();
        if (sequence_index_13e == 1) {
            if (time_counter_144 % 5 == 0) opening_periodic_effect(false);
            if (action == 200 && int_at(0x6b8) < 0) {
                set_action_and_finalize(facing() * int_at(0x6b4) < 1 ? 211 : 212); return true;
            }
            ++short_at(0x730);
            if ((facing() * int_at(0x6b4) < 1 && short_at(0x730) > (action == 200 ? 1 : 11)) || short_at(0x730) > 45) {
                set_action_and_finalize(204); return true;
            }
        }
        if (sequence_index_13e == 0 && middle_frame(2)) {
            float_at(0xf4) = action == 200 ? 8.5f : 4.25f;
            opening_effect_pair(false, true, 80.0);
        }
        return true;
    case 201: case 224:
        if (short_at(0x7b0) > 0 && sequence_index_13e < 3) short_at(0x4a8) = 2;
        if (sequence_index_13e == 0 || sequence_index_13e == 3) resolve_stage_surface_landing_transition();
        if (sequence_index_13e == 3) {
            float_at(0xf4) = static_cast<float>(float_at(0xf4) + 1.0);
            if (float_at(0xf4) > 0.0f) float_at(0xf4) = 0.0f;
        }
        if (!is_y_at_or_below_stage_surface(this) && time_counter_144 % 5 == 0) opening_periodic_effect(true);
        if (action == 201 ? sequence_index_13e < 3 : sequence_index_13e == 1 || sequence_index_13e == 2) {
            float_at(0xf8) = action == 201 ? float_at(0xf8) - float_at(0x100) : static_cast<float>(float_at(0xf8) - 0.5);
            if (has_crossed_stage_surface_while_descending()) {
                float_at(0xf8) = 0.0f; float_at(0xf0) = stage_surface_height_at_x(this); select_sequence(3); return true;
            }
        }
        if (advance_frame_and_dispatch()) { set_action_and_finalize(0); float_at(0xf4) = 0.0f; return true; }
        if (sequence_entry(1)) {
            ++short_at(0x730); float_at(0xf4) = -8.5f; float_at(0xf8) = 4.0f;
            if (action == 201) float_at(0x100) = 0.5f;
            opening_effect_pair(true, false, 80.0);
        }
        return true;
    case 202: case 203: case 225: case 226:
        float_at(0xf8) -= float_at(0x100);
        if (has_crossed_stage_surface_while_descending()) {
            zero_velocity_acceleration(); float_at(0xf0) = stage_surface_height_at_x(this); set_action_and_finalize(10); return true;
        }
        if (short_at(0x7b0) > 0) short_at(0x4a8) = 2;
        if ((action == 202 ? sequence_index_13e == 1 || sequence_index_13e == 2 :
             action == 203 ? sequence_index_13e < 3 : action == 225 ? frame_index_140 < 8 : sequence_index_13e == 2)
            && time_counter_144 % 5 == 0) opening_periodic_effect(action == 203 || action == 225);
        if (action == 202 || action == 203) advance_frame_and_dispatch();
        else if (advance_frame_and_dispatch()) { set_action_and_finalize(9); if (action == 226) return true; }
        if (action == 202 ? sequence_index_13e == 0 && middle_frame(2) : action == 226 ? sequence_entry(1) :
            action == 203 ? sequence_index_13e == 0 && middle_frame(2) : sequence_entry(1)) {
            if (action == 202 || action == 226) short_at(0x730) = 0;
            float_at(0xf4) = action == 202 || action == 226 ? 9.0f : action == 203 ? -9.0f : -7.5f;
            float_at(0xf8) = action == 225 ? 3.5f : 3.0f;
            float_at(0x100) = action == 225 ? 0.45f : 0.35f;
            opening_effect_pair(action == 203 || action == 225, action == 202 || action == 226,
                action == 202 || action == 226 ? 110.0 : 120.0);
        }
        if (action != 225 && sequence_entry(2)) face_opponent_and_flip_horizontal_velocity();
        return true;
    case 204:
        resolve_stage_surface_landing_transition();
        float_at(0xf4) = static_cast<float>(float_at(0xf4) - static_cast<double>(0.35f));
        if (float_at(0xf4) < 0.0f) { float_at(0xf4) = 0.0f; byte_at(0x47e) = 0; }
        if (advance_frame_and_dispatch()) { set_action_and_finalize(0); byte_at(0x47e) = 0; }
        return true;
    case 208: case 209: case 210: case 211: case 212: case 220: case 221: case 222:
        if (sequence_index_13e == 0) resolve_stage_surface_landing_transition();
        if (has_crossed_stage_surface_while_descending()) { set_action_and_finalize(10); restore_surface_motion(); return true; }
        if (is_y_at_or_below_stage_surface(this) || float_at(0xf8) > 0.0f) {
            if (short_at(0x7b0) > 0) short_at(0x4a8) = 2;
            short_at(0x4ae) = 2;
        }
        if (sequence_index_13e > 0) {
            float_at(0xf8) -= float_at(0x100);
            if (float_at(0xf8) < -20.0f) float_at(0xf8) = -20.0f;
        }
        if (sequence_index_13e == 1 && float_at(0xf8) < 4.0f) select_sequence(2);
        advance_frame_and_dispatch();
        if (sequence_entry(1)) {
            float_at(0xf4) = action == 208 || action == 220 ? 0.0f : action == 209 || action == 221 ? 7.0f :
                action == 210 || action == 222 ? -7.0f : action == 211 ? 2.0f : 8.0f;
            float_at(0xf8) = action == 208 || action == 220 ? 18.5f : action == 211 ? 17.5f : 15.0f;
            float_at(0x100) = 0.5f; byte_at(0x47e) = 0;
            emit_fighter_effect_433cc0(63, float_at(0xec), float_at(0xf0), byte_at(0x104), 1);
        }
        return true;
    case 214:
        return try_dispatch_verified_glide_action();
    case 215:
        resolve_stage_surface_landing_transition(); opening_brake(0.75, false); advance_or_action(0); return true;
    default:
        return false;
    }
}

__forceinline bool IkuActionStateView::try_dispatch_verified_glide_action()
{
    if (advance_frame_and_dispatch()) { set_action_and_finalize(9); return true; }
    if (sequence_entry(1)) {
        dispatch_indexed_event_member(31);
        if (float_at(0x740) >= 135.0f || float_at(0x740) <= -135.0f) { select_sequence(6); return true; }
        if (float_at(0x740) > 45.0f || float_at(0x740) < -45.0f) { select_sequence(4); return true; }
    }
    if (sequence_entry(9)) select_sequence(5);
    if (sequence_entry(10) || sequence_entry(11)) { set_action_and_finalize(9); return true; }
    int horizontal = facing() * int_at(0x6b4);
    if (int_at(0x6b8) > 0) short_at(0x732) = horizontal > 0 ? -45 : horizontal < 0 ? -135 : -90;
    else if (int_at(0x6b8) < 0) short_at(0x732) = horizontal > 0 ? 45 : horizontal < 0 ? 135 : 90;
    else if (horizontal > 0) short_at(0x732) = 0;
    else if (horizontal < 0) short_at(0x732) = 180;
    if (sequence_index_13e == 9 || sequence_index_13e == 10 || sequence_index_13e == 11)
        float_at(0xf8) -= float_at(0x100);
    else if (short_at(0x7b0) > 0) short_at(0x4a8) = 2;
    if (sequence_index_13e > 0 && sequence_index_13e < 9) {
        ++short_at(0x736);
        short_at(0x734) = static_cast<short>(short_at(0x732) - static_cast<short>(static_cast<int>(float_at(0x740))));
        if (short_at(0x734) > 180) short_at(0x734) -= 360;
        if (short_at(0x734) < -180) short_at(0x734) += 360;
        if (float_at(0x740) > 180.0f) float_at(0x740) = static_cast<float>(float_at(0x740) - 360.0);
        if (float_at(0x740) < -180.0f) float_at(0x740) = static_cast<float>(float_at(0x740) + 360.0);
        if (short_at(0x734) > 0) float_at(0x740) = static_cast<float>(float_at(0x740) + (int_at(0x4b8) == 0 ? 3.0 : 2.5));
        if (short_at(0x734) < 0) float_at(0x740) = static_cast<float>(float_at(0x740) - (int_at(0x4b8) == 0 ? 3.0 : 2.5));
        float_at(0xf4) = static_cast<float>(lookup_orientation_cosine_quantized_abs(float_at(0x740))) * float_at(0x73c);
        float_at(0xf8) = static_cast<float>(lookup_orientation_sine_quantized_abs(float_at(0x740))) * float_at(0x73c);
        if (float_at(0xf0) > 680.0f && float_at(0xf8) > 0.0f) float_at(0xf8) = 0.0f;
        adjust_counter_482(int_at(0x4b8) == 0 ? 4 : 8, 1);
        short sequence = sequence_index_13e;
        if ((sequence == 1 || sequence == 2) && (float_at(0x740) > 60.0 || float_at(0x740) < -60.0)) { select_sequence(3); return true; }
        if (sequence == 4 || sequence == 5) {
            if (float_at(0x740) <= 45.0f && float_at(0x740) >= -45.0f) { select_sequence(1); return true; }
            if (float_at(0x740) >= 135.0f || float_at(0x740) <= -135.0f) { select_sequence(6); return true; }
        }
        if ((sequence == 6 || sequence == 7) && float_at(0x740) < 120.0 && float_at(0x740) > -120.0) { select_sequence(8); return true; }
        if ((int_at(0x6c8) == 0 && short_at(0x736) > 10) || short_at(0x482) < 1) {
            if (sequence == 1 || sequence == 2) { opening_face_on_exit(); select_sequence(9); }
            if (sequence_index_13e == 3) {
                short_at(0x730) = frame_index_140; opening_face_on_exit();
                select_sequence(9); set_sequence_frame(short_at(0x730));
            }
            if (sequence_index_13e == 4 || sequence_index_13e == 5) { opening_face_on_exit(); select_sequence(10); }
            if (sequence_index_13e == 6 || sequence_index_13e == 7) { opening_face_on_exit(); select_sequence(11); }
            if (sequence_index_13e != 8) return true;
            short_at(0x730) = frame_index_140; opening_face_on_exit();
            select_sequence(11); set_sequence_frame(short_at(0x730)); return true;
        }
    }
    if (has_crossed_stage_surface_while_descending()) {
        float_at(0xf0) = stage_surface_height_at_x(this); float_at(0xf8) = 0.0f; float_at(0x100) = 0.0f;
        if (sequence_index_13e > 8) { set_action_and_finalize(10); zero_velocity_acceleration(); }
        else { reinterpret_cast<IkuActionScratchView *>(reinterpret_cast<unsigned char *>(this) + 4)->reset_fighter_action_scratch(); set_action_and_finalize(215); }
    }
    return true;
}

void IkuActionStateView::dispatch_action_state_vslot28()
{
    short_at(0x7a0) = 0;
    short_at(0x7a2) = 117;
    if (short_at(0x174) < 1 || peer_short(0x174) < 0) short_at(0x7b0) = 0;
    if (short_at(0x7b0) > 0) --short_at(0x7b0);
    if (action_id_13c > 149 && action_id_13c < 159 && byte_at(0x751) == 0) {
        byte_at(0x751) = 1;
        // Independent tests deliberately re-read action and coordinates after
        // each possible spawn, as the original prelude does.
        if (action_id_13c > 149 && action_id_13c < 154)
            spawn_owned_object_via_manager(998, static_cast<float>(facing() * 71) + float_at(0xec),
                static_cast<float>(float_at(0xf0) + 137.0), byte_at(0x104), 1, 0, 0);
        if (action_id_13c > 153 && action_id_13c < 158)
            spawn_owned_object_via_manager(998, static_cast<float>(facing() * 58) + float_at(0xec),
                static_cast<float>(float_at(0xf0) + 87.0), byte_at(0x104), 1, 0, 0);
        if (action_id_13c == 158)
            spawn_owned_object_via_manager(998, static_cast<float>(facing() * 43) + float_at(0xec),
                static_cast<float>(float_at(0xf0) + 136.0), byte_at(0x104), 1, 0, 0);
    }
    if (short_at(0x186) != 0 || peer_short(0x48c) != 0) return;
    if (try_dispatch_verified_action()) return;
    update_common_action_state();
}

} // namespace th105
