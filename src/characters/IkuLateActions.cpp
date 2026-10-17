#include "AnimationSequenceVirtuals.hpp"

namespace th105 {

int __cdecl selector_random_roll(int limit);
float __cdecl atan2_degrees(float y, float x);
// Both target lookup entries return a value loaded from the float table in
// ST0. The retained double declaration carries that value without rounding;
// it does not establish the original source return type.
double __cdecl lookup_orientation_sine_quantized_abs(float phase);
double __cdecl lookup_orientation_cosine_quantized_abs(float phase);
float __cdecl absolute_scalar_float(float value);
extern int g_match_identifier;

class IkuLateActionView;
float __fastcall stage_surface_height_at_x(IkuLateActionView *fighter);
struct IkuEventPairView { void *set_global_pair(float first, float second); };

// Semantic staging for all fourteen high-switch actions after610 inside
// 620920. This is not a replacement for the whole root or an original helper
// boundary. No implemented/match ledger selects this partial source view.
class IkuLateActionView : public AnimationSequenceObjectView {
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

    bool try_dispatch_verified_late_action();

private:
    unsigned char &byte_at(unsigned offset) {
        return *(reinterpret_cast<unsigned char *>(this) + offset);
    }
    short &short_at(unsigned offset) {
        return *reinterpret_cast<short *>(reinterpret_cast<unsigned char *>(this) + offset);
    }
    float &float_at(unsigned offset) {
        return *reinterpret_cast<float *>(reinterpret_cast<unsigned char *>(this) + offset);
    }
    int &int_at(unsigned offset) {
        return *reinterpret_cast<int *>(reinterpret_cast<unsigned char *>(this) + offset);
    }
    int facing() { return static_cast<signed char>(byte_at(0x104)); }
    unsigned char reverse_facing() { return static_cast<unsigned char>(-facing()); }
    float peer_float(unsigned offset) {
        return *reinterpret_cast<float *>(static_cast<unsigned char *>(related_170) + offset);
    }
    unsigned random_roll(int limit) { return static_cast<unsigned>(selector_random_roll(limit)); }
    bool sequence_entry(short sequence) {
        return time_counter_144 == 0 && frame_timer_142 == 0
            && frame_index_140 == 0 && sequence_index_13e == sequence;
    }
    void advance_or_action(short action) {
        if (advance_frame_and_dispatch())
            set_action_and_finalize(action);
    }
    void begin_effect() {
        short_at(0x48a) = 40;
        dispatch_indexed_event_member(23);
    }
    void finish_effect(int outcome) {
        dispatch_indexed_sequence_window_45c8b0(0, outcome, 60);
        advance_secondary_event_effect_cycle();
    }
    void emit_860_triplet(bool reverse_first) {
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
    void emit_six_ring(float speed, bool ahead) {
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
    void emit_920_ring(float speed, double offset) {
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
    void clamp_x(float upper, float lower) {
        if (float_at(0xf4) > upper) float_at(0xf4) = upper;
        if (float_at(0xf4) < lower) float_at(0xf4) = lower;
    }
    void clamp_y(float upper, float lower) {
        if (float_at(0xf8) > upper) float_at(0xf8) = upper;
        if (float_at(0xf8) < lower) float_at(0xf8) = lower;
    }
    void steer(bool fixed_limit) {
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
    void restore_surface_motion() {
        float_at(0xf0) = stage_surface_height_at_x(this);
        zero_velocity_acceleration();
    }
};

bool IkuLateActionView::try_dispatch_verified_late_action()
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

} // namespace th105
