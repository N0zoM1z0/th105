#include <stddef.h>

namespace th105 {
int __cdecl selector_random_roll(int limit);
unsigned __cdecl mt19937_next_u32();
float __cdecl atan2_degrees(float y, float x);
float __cdecl lookup_orientation_sine_quantized_abs(float phase);
float __cdecl lookup_orientation_cosine_quantized_abs(float phase);
float __cdecl absolute_scalar_float(float value);
extern int g_match_identifier;

class IkuActionStateView;
float __fastcall stage_surface_height_at_x(IkuActionStateView *fighter);
int __fastcall is_y_at_or_below_stage_surface(IkuActionStateView *fighter);
struct IkuEventPairView { void *set_global_pair(float first, float second); };
struct IkuActionScratchView { void reset_fighter_action_scratch(); };

struct IkuPeerView {
    unsigned char reserved_000[0xec];
    float x_ec;
    float y_f0;
    unsigned char reserved_0f4[0x80];
    short word_174;
    unsigned char reserved_176[0x316];
    short word_48c;
};

class IkuActionStateView {
public:
    virtual void scalar_delete_slot_00();
    virtual int set_action_sequence_and_finalize(short action, int sequence);
    virtual int set_action_and_finalize(short action);
    virtual int select_sequence(int sequence);
    virtual int reset_sequence();
    virtual unsigned char next_sequence_block();
    virtual int previous_sequence_block();
    virtual int set_sequence_frame(short frame);
    virtual unsigned char next_sequence_frame();
    virtual int previous_sequence_frame();
    virtual void pure_slot_28() = 0;

    void dispatch_character_wave_handle(unsigned index);

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
    void emit_fighter_effect_433cc0(int effect, float x, float y, unsigned char direction, int trailing);
    int spawn_owned_object_via_manager(
        int object_id, float x, float y, signed char direction, int variant,
        const void *payload, int count);

    void adjust_counter_482(short amount, int floor_value);
    int add_phase_scaled_counter_558(int amount);

    void dispatch_action_state_vslot28();
    void update_common_action_state();
    unsigned char try_dispatch_directional_action_208_210(int option);

    unsigned char reserved_004[0xe8];
    float x_ec;
    float y_f0;
    float velocity_x_f4;
    float velocity_y_f8;
    unsigned char reserved_0fc[4];
    float acceleration_y_100;
    signed char facing_104;
    unsigned char reserved_105[0x0b];
    unsigned char byte_110;
    unsigned char byte_111;
    unsigned char byte_112;
    unsigned char reserved_113[0x29];
    short action_id_13c;
    short sequence_index_13e;
    short frame_index_140;
    short frame_timer_142;
    int time_counter_144;
    unsigned char reserved_148[0x28];
    IkuPeerView *related_170;
    short word_174;
    unsigned char reserved_176[6];
    unsigned char byte_17c;
    unsigned char reserved_17d[3];
    int state_180;
    signed char byte_184;
    unsigned char reserved_185;
    short word_186;
    unsigned char reserved_188[0x2f6];
    unsigned char byte_47e;
    unsigned char reserved_47f[3];
    short word_482;
    unsigned char reserved_484[6];
    short word_48a;
    unsigned char reserved_48c[0x1c];
    short word_4a8;
    unsigned char reserved_4aa[2];
    short word_4ac;
    short word_4ae;
    unsigned char reserved_4b0[8];
    int field_4b8;
    unsigned char reserved_4bc[0x14a];
    signed char byte_606;
    unsigned char reserved_607[0x4e];
    unsigned char byte_655;
    unsigned char reserved_656[0x5e];
    int field_6b4;
    int field_6b8;
    int field_6bc;
    int field_6c0;
    int field_6c4;
    int field_6c8;
    unsigned char reserved_6cc[0x60];
    unsigned char byte_72c;
    unsigned char reserved_72d[3];
    short word_730;
    short word_732;
    short word_734;
    short word_736;
    short word_738;
    unsigned char reserved_73a[2];
    float field_73c;
    float field_740;
    float field_744;
    unsigned char reserved_748[8];
    unsigned char byte_750;
    unsigned char byte_751;
    unsigned char reserved_752[0x12];
    short word_764;
    short word_766;
    short word_768;
    short word_76a;
    short word_76c;
    unsigned char reserved_76e[0x1e];
    short word_78c;
    unsigned char reserved_78e[0x12];
    short word_7a0;
    short word_7a2;
    unsigned char reserved_7a4[0x0c];
    short word_7b0;
    short word_7b2;
    float field_7b4;

private:
    __forceinline int facing() { return facing_104; }
    __forceinline signed char reverse_facing() { return static_cast<signed char>(-facing_104); }
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
        word_48a = 40;
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
        spawn_owned_object_via_manager(860, x_ec,
            static_cast<float>(y_f0 + 275.0),
            reverse_first ? reverse_facing() : facing_104, 1, payload, 3);
        payload[2] = 5.0f;
        spawn_owned_object_via_manager(860, x_ec,
            static_cast<float>(y_f0 + 275.0), reverse_facing(), 1, payload, 3);
        payload[2] = 6.0f;
        spawn_owned_object_via_manager(860, x_ec,
            static_cast<float>(y_f0 + 275.0), reverse_facing(), 1, payload, 3);
    }
    __forceinline void emit_six_ring(float speed, bool ahead, float *payload) {
        for (int angle = 0; angle < 360; angle += 60) {
            unsigned roll = random_roll(30);
            payload[0] = static_cast<float>(angle + 30.0 + static_cast<float>(roll));
            payload[1] = speed;
            payload[2] = 2.0f;
            if (payload[0] >= 0.0f && payload[0] <= 180.0f) {
                spawn_owned_object_via_manager(815,
                    ahead ? static_cast<float>(facing() * 55) + x_ec : x_ec,
                    y_f0, facing_104, 1, payload, 3);
            } else {
                spawn_owned_object_via_manager(815,
                    ahead ? static_cast<float>(facing() * 55) + x_ec : x_ec,
                    y_f0, facing_104, -1, payload, 3);
            }
        }
    }
    __forceinline void emit_six_ring(float speed, bool ahead) {
        float payload[3];
        emit_six_ring(speed, ahead, payload);
    }
    __forceinline void emit_920_ring(float speed, double offset, float *payload) {
        // Unlike the integer ring above, the target stores this loop carrier
        // as float and increments it with a floating addition.
        for (float ray = 0.0f; ray < 12.0f; ray += 1.0f) {
            payload[0] = static_cast<float>(offset == 0.0 ? ray * 30.0 : ray * 30.0 + offset);
            payload[1] = speed;
            payload[2] = 7.0f;
            spawn_owned_object_via_manager(920, x_ec,
                static_cast<float>(y_f0 + 100.0), facing_104, 1, payload, 3);
        }
    }
    __forceinline void clamp_x(float upper, float lower) {
        if (velocity_x_f4 > upper) velocity_x_f4 = upper;
        if (velocity_x_f4 < lower) velocity_x_f4 = lower;
    }
    __forceinline void clamp_y(float upper, float lower) {
        if (velocity_y_f8 > upper) velocity_y_f8 = upper;
        if (velocity_y_f8 < lower) velocity_y_f8 = lower;
    }
    __forceinline void steer(bool fixed_limit) {
        ++word_734;
        float x = static_cast<float>(facing()) * (related_170->x_ec - x_ec);
        // Keep X's rounded argument ahead of Y evaluation. The peer Y field
        // is a reference, without an accessor-return temporary.
        const float &peer_y = related_170->y_f0;
        field_744 = -atan2_degrees(static_cast<float>(peer_y - y_f0), x);
        // Raw code uses FCHS twice, with no subtraction/decrement by one.
        velocity_x_f4 = static_cast<float>(
            lookup_orientation_cosine_quantized_abs(-field_744) * 0.5 + velocity_x_f4);
        if (fixed_limit) clamp_x(5.0f, -5.0f);
        velocity_y_f8 = static_cast<float>(
            lookup_orientation_sine_quantized_abs(-field_744) * 0.5 + velocity_y_f8);
        if (fixed_limit) {
            clamp_y(5.0f, -5.0f);
        } else {
            // Each target mode tests the X upper bound before joining the
            // remaining clamp operations; do not select a pair of limits first.
            if (g_match_identifier == 3) {
                clamp_x(6.0f, -6.0f);
                clamp_y(6.0f, -6.0f);
            } else if (g_match_identifier == 0) {
                clamp_x(4.0f, -4.0f);
                clamp_y(4.0f, -4.0f);
            } else {
                clamp_x(5.0f, -5.0f);
                clamp_y(5.0f, -5.0f);
            }
        }
        face_opponent_and_flip_horizontal_velocity();
    }
    __forceinline void restore_surface_motion() {
        y_f0 = stage_surface_height_at_x(this);
        zero_velocity_acceleration();
    }
    __forceinline void emit_object818(float *payload) {
        // The target rounds each coordinate to float before passing it. Keep
        // signed facing for the offset and its raw byte for the direction.
        spawn_owned_object_via_manager(
            818, static_cast<float>(static_cast<signed char>(facing_104) * 99)
                     + x_ec,
            static_cast<float>(y_f0 + 145.0),
            facing_104, 1, payload, 3);
    }

    __forceinline void emit_object818_phase(int count) {
        if (word_732 % 6 == 0 && word_734 < count) {
            float payload[3];
            payload[2] = 0.0f;
            // These are separate tests in the target. Re-read state and
            // coordinates after each call, rather than caching a pair.
            if (word_734 == 0) {
                payload[0] = -30.0f;
                payload[1] = 10.0f;
                emit_object818(payload);
                payload[0] = -15.0f;
                emit_object818(payload);
            }
            if (word_734 == 1) {
                payload[0] = -20.0f;
                payload[1] = 20.0f;
                emit_object818(payload);
                payload[0] = -10.0f;
                emit_object818(payload);
            }
            if (word_734 == 2) {
                payload[0] = -10.0f;
                payload[1] = 30.0f;
                emit_object818(payload);
                payload[0] = -5.0f;
                emit_object818(payload);
            }
            if (count == 4 && word_734 == 3) {
                payload[0] = -5.0f;
                payload[1] = 40.0f;
                emit_object818(payload);
                payload[0] = -2.5f;
                emit_object818(payload);
            }
            ++word_734;
        }
        ++word_732;
    }

    __forceinline void start_object818_emission(bool second_variant) {
        word_730 = 1;
        adjust_counter_482(200, 120);
        // 566/568 publish +180 before the scaled-counter helper; 565/567
        // publish it afterwards. Preserve the observed call/store ordering.
        if (second_variant)
            state_180 = 1;
        add_phase_scaled_counter_558(50);
        if (!second_variant)
            state_180 = 1;
        dispatch_character_wave_handle(18);
    }
    __forceinline void advance_spell_frame() {
        if (advance_frame_and_dispatch())
            set_action_and_finalize(0);
    }
    __forceinline void begin_spell_effect() {
        word_48a = 40;
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
        spawn_owned_object_via_manager(860, x_ec,
            static_cast<float>(y_f0 + 275.0),
            reverse_first ? reverse_facing() : facing_104, 1, payload, 3);
        payload[2] = 5.0f;
        spawn_owned_object_via_manager(860, x_ec,
            static_cast<float>(y_f0 + 275.0), reverse_facing(), 1, payload, 3);
        payload[2] = 6.0f;
        spawn_owned_object_via_manager(860, x_ec,
            static_cast<float>(y_f0 + 275.0), reverse_facing(), 1, payload, 3);
    }
    __forceinline void emit_upper_object(int object, float *payload) {
        spawn_owned_object_via_manager(object,
            static_cast<float>(facing() * 99) + x_ec,
            static_cast<float>(y_f0 + 145.0),
            facing_104, 1, payload, 3);
    }
    __forceinline void emit_813_aimed(int variant) {
        float x = static_cast<float>(facing()) * (related_170->x_ec - x_ec);
        const float &peer_y = related_170->y_f0;
        field_744 = -atan2_degrees(static_cast<float>(peer_y - y_f0), x);
        if (variant == 1) {
            if (field_744 < -60.0) field_744 = -60.0f;
            if (field_744 > -45.0f) field_744 = -45.0f;
        } else if (variant == 2) {
            if (field_744 < 45.0f) field_744 = 45.0f;
            if (field_744 > 60.0) field_744 = 60.0f;
        } else {
            if (field_744 < -10.0f) field_744 = -10.0f;
            if (field_744 > 10.0f) field_744 = 10.0f;
        }
        add_phase_scaled_counter_558(50);
        float payload[3] = {variant == 1 ? -45.0f : variant == 2 ? 45.0f : 0.0f, 17.5f, 0.0f};
        emit_upper_object(813, payload);
        state_180 = 1;
        dispatch_character_wave_handle(14);
        adjust_counter_482(200, 120);
    }
    __forceinline void emit_823(bool second, bool wave_first) {
        float payload[3] = {second ? -2.0f : 2.0f, 0.0f, 2.0f};
        emit_upper_object(823, payload);
        state_180 = 1;
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
        velocity_x_f4 = static_cast<float>(velocity_x_f4 - amount);
        if (velocity_x_f4 < 0.0f) velocity_x_f4 = 0.0f;
    }
    __forceinline void middle_cost(int floor, int scaled) {
        adjust_counter_482(200, floor);
        add_phase_scaled_counter_558(scaled);
    }
    __forceinline void spawn_middle(int object, int ahead, double height, float *payload) {
        spawn_owned_object_via_manager(object,
            ahead == 0 ? x_ec : static_cast<float>(facing() * ahead) + x_ec,
            static_cast<float>(y_f0 + height), facing_104, 1, payload, 3);
    }
    __forceinline void middle_ring(int object, int ahead, float speed, bool on_surface, float *payload) {
        for (int angle = 0; angle < 360; angle += 60) {
            unsigned roll = random_roll(30);
            payload[0] = static_cast<float>(angle + 30.0 + static_cast<float>(roll));
            payload[1] = speed;
            payload[2] = 2.0f;
            if (payload[0] >= 0.0f && payload[0] <= 180.0f) {
                spawn_owned_object_via_manager(object,
                    ahead == 0 ? x_ec : static_cast<float>(facing() * ahead) + x_ec,
                    on_surface ? stage_surface_height_at_x(this) : y_f0,
                    facing_104, 1, payload, 3);
            } else {
                spawn_owned_object_via_manager(object,
                    ahead == 0 ? x_ec : static_cast<float>(facing() * ahead) + x_ec,
                    on_surface ? stage_surface_height_at_x(this) : y_f0,
                    facing_104, -1, payload, 3);
            }
        }
    }
    __forceinline void middle_ring(int object, int ahead, float speed, bool on_surface) {
        float payload[3];
        middle_ring(object, ahead, speed, on_surface, payload);
    }
    __forceinline void middle_fan800(int ahead, double height, double first, int step, int limit) {
        float payload[3] = {0.0f, 8.0f, 0.0f};
        for (int ray = 0; ray < limit; ray += step) {
            payload[0] = static_cast<float>(first - ray);
            spawn_owned_object_via_manager(800,
                static_cast<float>(facing() * ahead) + x_ec,
                static_cast<float>(y_f0 + height),
                facing_104, 1, payload, 3);
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

    __forceinline void opening_brake(double amount, bool clear_motion) {
        if (velocity_x_f4 > 0.0f) {
            velocity_x_f4 = static_cast<float>(velocity_x_f4 - amount);
            if (velocity_x_f4 < 0.0f) {
                if (clear_motion) zero_velocity_acceleration();
                else velocity_x_f4 = 0.0f;
                if (clear_motion) byte_47e = 0;
            }
        }
        // Keep this second independent test after the first possible store/call.
        if (velocity_x_f4 < 0.0f) {
            velocity_x_f4 = static_cast<float>(velocity_x_f4 + amount);
            if (velocity_x_f4 > 0.0f) {
                if (clear_motion) zero_velocity_acceleration();
                else velocity_x_f4 = 0.0f;
                if (clear_motion) byte_47e = 0;
            }
        }
    }
    __forceinline void opening_periodic_effect(bool reverse) {
        emit_fighter_effect_433cc0(124,
            static_cast<float>((static_cast<double>(x_ec) + 50.0) - static_cast<float>(mt19937_next_u32() % 100U)),
            static_cast<float>(mt19937_next_u32() % 200U) + y_f0,
            reverse ? static_cast<unsigned char>(reverse_facing()) : static_cast<unsigned char>(facing_104),
            1);
    }
    __forceinline void opening_effect_pair(bool reverse, bool ahead, double height) {
        emit_fighter_effect_433cc0(125,
            ahead ? static_cast<float>(facing() * 80) + x_ec : x_ec,
            static_cast<float>(y_f0 + height),
            reverse ? static_cast<unsigned char>(reverse_facing()) : static_cast<unsigned char>(facing_104), 1);
        emit_fighter_effect_433cc0(126, x_ec, static_cast<float>(y_f0 + height),
            reverse ? static_cast<unsigned char>(reverse_facing()) : static_cast<unsigned char>(facing_104), 1);
        dispatch_indexed_event_member(31);
    }
    __forceinline void opening_face_and_select_exit(int sequence) {
        if (facing_104 == 1) {
            if (x_ec > related_170->x_ec) {
                facing_104 = -1;
                velocity_x_f4 = -velocity_x_f4;
                select_sequence(sequence);
            } else {
                select_sequence(sequence);
            }
        } else {
            if (x_ec < related_170->x_ec) {
                facing_104 = reverse_facing();
                velocity_x_f4 = -velocity_x_f4;
                select_sequence(sequence);
            } else {
                select_sequence(sequence);
            }
        }
    }
    __forceinline void opening_face_and_select_exit_frame(int sequence) {
        if (facing_104 == 1) {
            if (x_ec > related_170->x_ec) {
                facing_104 = -1;
                velocity_x_f4 = -velocity_x_f4;
                select_sequence(sequence);
                set_sequence_frame(word_730);
            } else {
                select_sequence(sequence);
                set_sequence_frame(word_730);
            }
        } else {
            if (x_ec < related_170->x_ec) {
                facing_104 = reverse_facing();
                velocity_x_f4 = -velocity_x_f4;
                select_sequence(sequence);
                set_sequence_frame(word_730);
            } else {
                select_sequence(sequence);
                set_sequence_frame(word_730);
            }
        }
    }
};

void IkuActionStateView::dispatch_action_state_vslot28()
{
    word_7a0 = 0;
    word_7a2 = 117;
    if (word_174 <= 0 || related_170->word_174 < 0) word_7b0 = 0;
    if (word_7b0 > 0) --word_7b0;
    if (action_id_13c > 149 && action_id_13c < 159 && byte_751 == 0) {
        byte_751 = 1;
        if (action_id_13c > 149 && action_id_13c < 154) {
            spawn_owned_object_via_manager(998, static_cast<float>(facing() * 71) + x_ec,
                static_cast<float>(y_f0 + 137.0), facing_104, 1, 0, 0);
        }
        if (action_id_13c > 153 && action_id_13c < 158) {
            spawn_owned_object_via_manager(998, static_cast<float>(facing() * 58) + x_ec,
                static_cast<float>(y_f0 + 87.0), facing_104, 1, 0, 0);
        }
        if (action_id_13c == 158) {
            spawn_owned_object_via_manager(998, static_cast<float>(facing() * 43) + x_ec,
                static_cast<float>(y_f0 + 136.0), facing_104, 1, 0, 0);
        }
    }
    if (word_186 != 0 || related_170->word_48c != 0) return;
    switch (action_id_13c) {
    case 0: {
        resolve_stage_surface_landing_transition();
        if (velocity_x_f4 == 0.0f) byte_47e = 0;
        if (!byte_47e) zero_velocity_acceleration();
        else opening_brake(0.5, true);
        break;
    }

    case 1: {
        resolve_stage_surface_landing_transition();

        if (!byte_47e) zero_velocity_acceleration();
        else opening_brake(0.5, true);
        if (advance_frame_and_dispatch() && frame_index_140 == 0) {
            set_action_and_finalize(2);
        }
        return;
    }

    case 2: {
        resolve_stage_surface_landing_transition();

        if (!byte_47e) zero_velocity_acceleration();
        else opening_brake(0.5, true);
        break;
    }

    case 3: {
        resolve_stage_surface_landing_transition();

        if (!byte_47e) zero_velocity_acceleration();
        else opening_brake(0.5, true);
        if (advance_frame_and_dispatch() && frame_index_140 == 0) {
            set_action_and_finalize(0);
        }
        return;
    }

    case 4: {
        resolve_stage_surface_landing_transition();
        velocity_x_f4 = 2.5f;
        break;
    }

    case 5: {
        resolve_stage_surface_landing_transition();
        velocity_x_f4 = -3.0f;
        break;
    }

    case 6: {
        if (sequence_index_13e == 0) {
            resolve_stage_surface_landing_transition();
            if (sequence_index_13e == 0 && !byte_47e) zero_velocity_acceleration();
        }
        if (sequence_index_13e > 0) {
            velocity_y_f8 -= acceleration_y_100;
            if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
                set_action_and_finalize(10); { restore_surface_motion(); return; }
            }
        }
        advance_frame_and_dispatch();
        if (sequence_entry(1)) {
            velocity_x_f4 = 0.0f;
            velocity_y_f8 = 12.0f;
            acceleration_y_100 = 0.35f; byte_47e = 0;
        }
        return;
    }

    case 7: {
        if (sequence_index_13e == 0) {
            resolve_stage_surface_landing_transition();
            if (sequence_index_13e == 0 && !byte_47e) zero_velocity_acceleration();
        }
        if (sequence_index_13e > 0) {
            velocity_y_f8 -= acceleration_y_100;
            if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
                set_action_and_finalize(10); { restore_surface_motion(); return; }
            }
        }
        advance_frame_and_dispatch();
        if (sequence_entry(1)) {
            velocity_x_f4 = 3.5f;
            velocity_y_f8 = 11.0f;
            acceleration_y_100 = 0.35f; byte_47e = 0;
        }
        return;
    }

    case 8: {
        if (sequence_index_13e == 0) {
            resolve_stage_surface_landing_transition();
            if (sequence_index_13e == 0 && !byte_47e) zero_velocity_acceleration();
        }
        if (sequence_index_13e > 0) {
            velocity_y_f8 -= acceleration_y_100;
            if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
                set_action_and_finalize(10); { restore_surface_motion(); return; }
            }
        }
        advance_frame_and_dispatch();
        if (sequence_entry(1)) {
            velocity_x_f4 = -3.5f;
            velocity_y_f8 = 11.0f;
            acceleration_y_100 = 0.35f; byte_47e = 0;
        }
        return;
    }

    case 9: {
        if (acceleration_y_100 == 0.0f) acceleration_y_100 = 0.6f;
        velocity_y_f8 -= acceleration_y_100;
        if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) { set_action_and_finalize(10); restore_surface_motion(); return; }
        break;
    }

    case 10: {
        resolve_stage_surface_landing_transition(); zero_velocity_acceleration();
        if (advance_frame_and_dispatch()) {
            if (field_6b8 == 0) { set_action_and_finalize(0); return; }
            set_action_and_finalize(2); return;
        }
        return;
    }

    case 197: {
        if ((sequence_index_13e == 0) || sequence_index_13e == 2)
            resolve_stage_surface_landing_transition();
        if ((sequence_index_13e == 1) && time_counter_144 >= 40) {
            zero_velocity_acceleration(); select_sequence(2); return;
        }
        if (advance_frame_and_dispatch()) {
            if (byte_72c == 2) {
                set_action_and_finalize(700); word_4a8 = 3; word_4ac = 3;
                return;
            }
            set_action_and_finalize(0);
            if (field_6b8 > 0) set_action_and_finalize(1);
        }
        if (sequence_index_13e == 2 && frame_index_140 == 3 && frame_timer_142 == 0) {
            if (x_ec > related_170->x_ec) facing_104 = -1;
            if (x_ec < related_170->x_ec) facing_104 = 1;
        }
        if (sequence_entry(1)) velocity_x_f4 = 14.5f;
        return;
    }

    case 198: {
        if ((sequence_index_13e == 0) || sequence_index_13e == 2)
            resolve_stage_surface_landing_transition();
        if ((sequence_index_13e == 1) && time_counter_144 >= 40) {
            zero_velocity_acceleration(); select_sequence(2); return;
        }
        if (advance_frame_and_dispatch()) {
            if (byte_72c == 2) {
                set_action_and_finalize(700); word_4a8 = 3; word_4ac = 3;
                return;
            }
            set_action_and_finalize(0);
            if (field_6b8 > 0) set_action_and_finalize(1);
        }
        if (sequence_index_13e == 2 && frame_index_140 == 3 && frame_timer_142 == 0) {
            if (x_ec > related_170->x_ec) facing_104 = -1;
            if (x_ec < related_170->x_ec) facing_104 = 1;
        }
        if (sequence_entry(1)) velocity_x_f4 = -14.5f;
        return;
    }

    case 199: {
        resolve_stage_surface_landing_transition();

        if (advance_frame_and_dispatch()) {
            if (byte_72c == 2) {
                set_action_and_finalize(700); word_4a8 = 3; word_4ac = 3;
                return;
            }
            set_action_and_finalize(0);
            if (field_6b8 > 0) set_action_and_finalize(1);
        }
        if (sequence_index_13e == 0 && frame_index_140 == 5 && frame_timer_142 == 0) {
            if (x_ec > related_170->x_ec) facing_104 = -1;
            if (x_ec < related_170->x_ec) facing_104 = 1;
        }

        return;
    }

    case 200: {
        if (word_7b0 > 0) word_4a8 = 2;
        resolve_stage_surface_landing_transition(); byte_47e = 1;

        advance_frame_and_dispatch();
        if (sequence_index_13e == 1) {
            if (time_counter_144 % 5 == 0) opening_periodic_effect(false);
            if (field_6b8 < 0) {
                if (facing() * field_6b4 > 0) { set_action_and_finalize(212); return; }
                set_action_and_finalize(211); return;
            }
            ++word_730;
            if ((facing() * field_6b4 <= 0 && word_730 > (1)) || word_730 > 45) {
                set_action_and_finalize(204); return;
            }
        }
        if (sequence_index_13e == 0 && frame_index_140 == 2 && frame_timer_142 == 0) {
            velocity_x_f4 = 8.5f;
            opening_effect_pair(false, true, 80.0);
        }
        return;
    }

    case 201: {
        if (word_7b0 > 0 && sequence_index_13e < 3) word_4a8 = 2;
        if (sequence_index_13e == 0 || sequence_index_13e == 3) resolve_stage_surface_landing_transition();
        if (sequence_index_13e == 3) {
            velocity_x_f4 = static_cast<float>(velocity_x_f4 + 1.0);
            if (velocity_x_f4 > 0.0f) velocity_x_f4 = 0.0f;
        }
        if (!static_cast<unsigned char>(is_y_at_or_below_stage_surface(this)) && time_counter_144 % 5 == 0) opening_periodic_effect(true);
        if (sequence_index_13e < 3) {
            velocity_y_f8 = (velocity_y_f8 - acceleration_y_100);
            if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
                velocity_y_f8 = 0.0f; y_f0 = stage_surface_height_at_x(this); select_sequence(3); return;
            }
        }
        if (advance_frame_and_dispatch()) { set_action_and_finalize(0); velocity_x_f4 = 0.0f; return; }
        if (sequence_entry(1)) {
            ++word_730; velocity_x_f4 = -8.5f; velocity_y_f8 = 4.0f;
            acceleration_y_100 = 0.5f;
            opening_effect_pair(true, false, 80.0);
        }
        return;
    }

    case 202: {
        velocity_y_f8 -= acceleration_y_100;
        if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
            zero_velocity_acceleration(); y_f0 = stage_surface_height_at_x(this); set_action_and_finalize(10); return;
        }
        if (word_7b0 > 0) word_4a8 = 2;
        if ((sequence_index_13e == 1 || sequence_index_13e == 2)
            && time_counter_144 % 5 == 0) opening_periodic_effect(false);
        advance_frame_and_dispatch();
        if (sequence_index_13e == 0 && middle_frame(2)) {
            word_730 = 0;
            velocity_x_f4 = 9.0f;
            velocity_y_f8 = 3.0f;
            acceleration_y_100 = 0.35f;
            opening_effect_pair(false, true,
                110.0);
        }
        if (sequence_entry(2)) face_opponent_and_flip_horizontal_velocity();
        return;
    }

    case 203: {
        velocity_y_f8 -= acceleration_y_100;
        if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
            zero_velocity_acceleration(); y_f0 = stage_surface_height_at_x(this); set_action_and_finalize(10); return;
        }
        if (word_7b0 > 0) word_4a8 = 2;
        if (((sequence_index_13e < 3))
            && time_counter_144 % 5 == 0) opening_periodic_effect(true);
        advance_frame_and_dispatch();
        if (sequence_index_13e == 0 && middle_frame(2)) {
            velocity_x_f4 = -9.0f;
            velocity_y_f8 = 3.0f;
            acceleration_y_100 = 0.35f;
            opening_effect_pair(true, false,
                120.0);
        }
        if (sequence_entry(2)) face_opponent_and_flip_horizontal_velocity();
        return;
    }

    case 204: {
        resolve_stage_surface_landing_transition();
        velocity_x_f4 = static_cast<float>(velocity_x_f4 - static_cast<double>(0.35f));
        if (velocity_x_f4 < 0.0f) { velocity_x_f4 = 0.0f; byte_47e = 0; }
        if (advance_frame_and_dispatch()) { set_action_and_finalize(0); byte_47e = 0; }
        return;
    }

    case 208: {
        if (sequence_index_13e == 0) resolve_stage_surface_landing_transition();
        if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) { set_action_and_finalize(10); restore_surface_motion(); return; }
        if (static_cast<unsigned char>(is_y_at_or_below_stage_surface(this)) || velocity_y_f8 > 0.0f) {
            if (word_7b0 > 0) word_4a8 = 2;
            word_4ae = 2;
        }
        if (sequence_index_13e > 0) {
            velocity_y_f8 -= acceleration_y_100;
            if (velocity_y_f8 < -20.0f) velocity_y_f8 = -20.0f;
        }
        if (sequence_index_13e == 1 && velocity_y_f8 < 4.0f) select_sequence(2);
        advance_frame_and_dispatch();
        if (sequence_entry(1)) {
            velocity_x_f4 = 0.0f;
            velocity_y_f8 = 18.5f;
            acceleration_y_100 = 0.5f; byte_47e = 0;
            emit_fighter_effect_433cc0(63, x_ec, y_f0, facing_104, 1);
        }
        return;
    }

    case 209: {
        if (sequence_index_13e == 0) resolve_stage_surface_landing_transition();
        if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) { set_action_and_finalize(10); restore_surface_motion(); return; }
        if (static_cast<unsigned char>(is_y_at_or_below_stage_surface(this)) || velocity_y_f8 > 0.0f) {
            if (word_7b0 > 0) word_4a8 = 2;
            word_4ae = 2;
        }
        if (sequence_index_13e > 0) {
            velocity_y_f8 -= acceleration_y_100;
            if (velocity_y_f8 < -20.0f) velocity_y_f8 = -20.0f;
        }
        if (sequence_index_13e == 1 && velocity_y_f8 < 4.0f) select_sequence(2);
        advance_frame_and_dispatch();
        if (sequence_entry(1)) {
            velocity_x_f4 = 7.0f;
            velocity_y_f8 = 15.0f;
            acceleration_y_100 = 0.5f; byte_47e = 0;
            emit_fighter_effect_433cc0(63, x_ec, y_f0, facing_104, 1);
        }
        return;
    }

    case 210: {
        if (sequence_index_13e == 0) resolve_stage_surface_landing_transition();
        if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) { set_action_and_finalize(10); restore_surface_motion(); return; }
        if (static_cast<unsigned char>(is_y_at_or_below_stage_surface(this)) || velocity_y_f8 > 0.0f) {
            if (word_7b0 > 0) word_4a8 = 2;
            word_4ae = 2;
        }
        if (sequence_index_13e > 0) {
            velocity_y_f8 -= acceleration_y_100;
            if (velocity_y_f8 < -20.0f) velocity_y_f8 = -20.0f;
        }
        if (sequence_index_13e == 1 && velocity_y_f8 < 4.0f) select_sequence(2);
        advance_frame_and_dispatch();
        if (sequence_entry(1)) {
            velocity_x_f4 = ((-7.0f));
            velocity_y_f8 = 15.0f;
            acceleration_y_100 = 0.5f; byte_47e = 0;
            emit_fighter_effect_433cc0(63, x_ec, y_f0, facing_104, 1);
        }
        return;
    }

    case 211: {
        if (sequence_index_13e == 0) resolve_stage_surface_landing_transition();
        if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) { set_action_and_finalize(10); restore_surface_motion(); return; }
        if (static_cast<unsigned char>(is_y_at_or_below_stage_surface(this)) || velocity_y_f8 > 0.0f) {
            if (word_7b0 > 0) word_4a8 = 2;
            word_4ae = 2;
        }
        if (sequence_index_13e > 0) {
            velocity_y_f8 -= acceleration_y_100;
            if (velocity_y_f8 < -20.0f) velocity_y_f8 = -20.0f;
        }
        if (sequence_index_13e == 1 && velocity_y_f8 < 4.0f) select_sequence(2);
        advance_frame_and_dispatch();
        if (sequence_entry(1)) {
            velocity_x_f4 = (((2.0f)));
            velocity_y_f8 = 17.5f;
            acceleration_y_100 = 0.5f; byte_47e = 0;
            emit_fighter_effect_433cc0(63, x_ec, y_f0, facing_104, 1);
        }
        return;
    }

    case 212: {
        if (sequence_index_13e == 0) resolve_stage_surface_landing_transition();
        if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) { set_action_and_finalize(10); restore_surface_motion(); return; }
        if (static_cast<unsigned char>(is_y_at_or_below_stage_surface(this)) || velocity_y_f8 > 0.0f) {
            if (word_7b0 > 0) word_4a8 = 2;
            word_4ae = 2;
        }
        if (sequence_index_13e > 0) {
            velocity_y_f8 -= acceleration_y_100;
            if (velocity_y_f8 < -20.0f) velocity_y_f8 = -20.0f;
        }
        if (sequence_index_13e == 1 && velocity_y_f8 < 4.0f) select_sequence(2);
        advance_frame_and_dispatch();
        if (sequence_entry(1)) {
            velocity_x_f4 = (((8.0f)));
            velocity_y_f8 = 15.0f;
            acceleration_y_100 = 0.5f; byte_47e = 0;
            emit_fighter_effect_433cc0(63, x_ec, y_f0, facing_104, 1);
        }
        return;
    }

    case 214: {
        if (advance_frame_and_dispatch()) { set_action_and_finalize(9); return; }
        if (sequence_entry(1)) {
            dispatch_indexed_event_member(31);
            if (field_740 >= 135.0f || field_740 <= -135.0f) { select_sequence(6); return; }
            if (field_740 > 45.0f || field_740 < -45.0f) { select_sequence(4); return; }
        }
        if (sequence_entry(9)) select_sequence(5);
        if (sequence_entry(10)) { set_action_and_finalize(9); return; }
        if (sequence_entry(11)) { set_action_and_finalize(9); return; }
        if (field_6b8 > 0) {
            if (facing() * field_6b4 > 0) word_732 = -45;
            else if (facing() * field_6b4 < 0) word_732 = -135;
            else word_732 = -90;
        } else if (field_6b8 < 0) {
            if (facing() * field_6b4 > 0) word_732 = 45;
            else if (facing() * field_6b4 < 0) word_732 = 135;
            else word_732 = 90;
        } else {
            if (facing() * field_6b4 > 0) word_732 = 0;
            else if (facing() * field_6b4 < 0) word_732 = 180;
        }
        if (sequence_index_13e == 9 || sequence_index_13e == 10 || sequence_index_13e == 11)
            velocity_y_f8 -= acceleration_y_100;
        else if (word_7b0 > 0) word_4a8 = 2;
        if (sequence_index_13e > 0 && sequence_index_13e < 9) {
            ++word_736;
            word_734 = static_cast<short>(word_732 - static_cast<short>(static_cast<int>(field_740)));
            if (word_734 > 180) word_734 -= 360;
            if (word_734 < -180) word_734 += 360;
            if (field_740 > 180.0f) field_740 = static_cast<float>(field_740 - 360.0);
            if (field_740 < -180.0f) field_740 = static_cast<float>(field_740 + 360.0);
            if (word_734 > 0) {
                if (field_4b8 == 0) field_740 = static_cast<float>(field_740 + 3.0);
                else field_740 = static_cast<float>(field_740 + 2.5);
            }
            if (word_734 < 0) {
                if (field_4b8 == 0) field_740 = static_cast<float>(field_740 - 3.0);
                else field_740 = static_cast<float>(field_740 - 2.5);
            }
            velocity_x_f4 = static_cast<float>(lookup_orientation_cosine_quantized_abs(field_740) * field_73c);
            velocity_y_f8 = static_cast<float>(lookup_orientation_sine_quantized_abs(field_740) * field_73c);
            if (y_f0 > 680.0f && velocity_y_f8 > 0.0f) velocity_y_f8 = 0.0f;
            if (field_4b8 == 0) adjust_counter_482(4, 1);
            else adjust_counter_482(8, 1);
            if ((sequence_index_13e == 1 || sequence_index_13e == 2) && (field_740 > 60.0 || field_740 < -60.0)) { select_sequence(3); return; }
            if (sequence_index_13e == 4 || sequence_index_13e == 5) {
                if (field_740 <= 45.0f && field_740 >= -45.0f) { select_sequence(1); return; }
                if (field_740 >= 135.0f || field_740 <= -135.0f) { select_sequence(6); return; }
            }
            if ((sequence_index_13e == 6 || sequence_index_13e == 7) && field_740 < 120.0 && field_740 > -120.0) { select_sequence(8); return; }
            if ((field_6c8 == 0 && word_736 > 10) || word_482 <= 0) {
                if ((field_6c8 == 0 && word_736 > 10) || word_482 <= 0) {
                    if (sequence_index_13e == 1 || sequence_index_13e == 2) { opening_face_and_select_exit(9); }
                    if (sequence_index_13e == 3) {
                        word_730 = frame_index_140;
                        opening_face_and_select_exit_frame(9);
                    }
                    if (sequence_index_13e == 4 || sequence_index_13e == 5) { opening_face_and_select_exit(10); }
                    if (sequence_index_13e == 6 || sequence_index_13e == 7) { opening_face_and_select_exit(11); }
                    if (sequence_index_13e == 8) {
                        word_730 = frame_index_140;
                        if (facing_104 == 1) {
                            if (x_ec > related_170->x_ec) {
                                facing_104 = -1;
                                velocity_x_f4 = -velocity_x_f4;
                                select_sequence(11); set_sequence_frame(word_730); return;
                            } else {
                                select_sequence(11); set_sequence_frame(word_730); return;
                            }
                        } else {
                            if (x_ec < related_170->x_ec) {
                                facing_104 = reverse_facing();
                                velocity_x_f4 = -velocity_x_f4;
                                select_sequence(11); set_sequence_frame(word_730); return;
                            } else {
                                select_sequence(11); set_sequence_frame(word_730); return;
                            }
                        }
                    }
                    return;
                }
            }
        }
        if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
            y_f0 = stage_surface_height_at_x(this); velocity_y_f8 = 0.0f; acceleration_y_100 = 0.0f;
            if (sequence_index_13e < 9) {
                reinterpret_cast<IkuActionScratchView *>(reinterpret_cast<unsigned char *>(this) + 4)->reset_fighter_action_scratch();
                set_action_and_finalize(215);
            } else {
                set_action_and_finalize(10); zero_velocity_acceleration();
            }
        }
        return;
    }

    case 215: {
        resolve_stage_surface_landing_transition(); opening_brake(0.75, false); advance_or_action(0); return;
    }

    case 220: {
        if (sequence_index_13e == 0) resolve_stage_surface_landing_transition();
        if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) { set_action_and_finalize(10); { restore_surface_motion(); return; } }
        if (static_cast<unsigned char>(is_y_at_or_below_stage_surface(this)) || velocity_y_f8 > 0.0f) {
            if (word_7b0 > 0) word_4a8 = 2;
            word_4ae = 2;
        }
        if (sequence_index_13e > 0) {
            velocity_y_f8 -= acceleration_y_100;
            if (velocity_y_f8 < -20.0f) velocity_y_f8 = -20.0f;
        }
        if (sequence_index_13e == 1 && velocity_y_f8 < 4.0f) select_sequence(2);
        advance_frame_and_dispatch();
        if (sequence_entry(1)) {
            velocity_x_f4 = 0.0f;
            velocity_y_f8 = 18.5f;
            acceleration_y_100 = 0.5f; byte_47e = 0;
            emit_fighter_effect_433cc0(63, x_ec, y_f0, facing_104, 1);
        }
        return;
    }

    case 221: {
        if (sequence_index_13e == 0) resolve_stage_surface_landing_transition();
        if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) { set_action_and_finalize(10); restore_surface_motion(); return; }
        if (static_cast<unsigned char>(is_y_at_or_below_stage_surface(this)) || velocity_y_f8 > 0.0f) {
            if (word_7b0 > 0) word_4a8 = 2;
            word_4ae = 2;
        }
        if (sequence_index_13e > 0) {
            velocity_y_f8 -= acceleration_y_100;
            if (velocity_y_f8 < -20.0f) velocity_y_f8 = -20.0f;
        }
        if (sequence_index_13e == 1 && velocity_y_f8 < 4.0f) select_sequence(2);
        advance_frame_and_dispatch();
        if (sequence_entry(1)) {
            velocity_x_f4 = 7.0f;
            velocity_y_f8 = 15.0f;
            acceleration_y_100 = 0.5f; byte_47e = 0;
            emit_fighter_effect_433cc0(63, x_ec, y_f0, facing_104, 1);
        }
        return;
    }

    case 222: {
        if (sequence_index_13e == 0) resolve_stage_surface_landing_transition();
        if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) { set_action_and_finalize(10); restore_surface_motion(); return; }
        if (static_cast<unsigned char>(is_y_at_or_below_stage_surface(this)) || velocity_y_f8 > 0.0f) {
            if (word_7b0 > 0) word_4a8 = 2;
            word_4ae = 2;
        }
        if (sequence_index_13e > 0) {
            velocity_y_f8 -= acceleration_y_100;
            if (velocity_y_f8 < -20.0f) velocity_y_f8 = -20.0f;
        }
        if (sequence_index_13e == 1 && velocity_y_f8 < 4.0f) select_sequence(2);
        advance_frame_and_dispatch();
        if (sequence_entry(1)) {
            velocity_x_f4 = ((-7.0f));
            velocity_y_f8 = 15.0f;
            acceleration_y_100 = 0.5f; byte_47e = 0;
            emit_fighter_effect_433cc0(63, x_ec, y_f0, facing_104, 1);
        }
        return;
    }

    case 223: {
        resolve_stage_surface_landing_transition(); byte_47e = 1;
        if (word_7b0 > 0) word_4a8 = 2;
        advance_frame_and_dispatch();
        if (sequence_index_13e == 1) {
            if (time_counter_144 % 5 == 0) opening_periodic_effect(false);

            ++word_730;
            if ((facing() * field_6b4 <= 0 && word_730 > (11)) || word_730 > 45) {
                set_action_and_finalize(204); return;
            }
        }
        if (sequence_index_13e == 0 && frame_index_140 == 2 && frame_timer_142 == 0) {
            velocity_x_f4 = 4.25f;
            opening_effect_pair(false, true, 80.0);
        }
        return;
    }

    case 224: {
        if (word_7b0 > 0 && sequence_index_13e < 3) word_4a8 = 2;
        if (sequence_index_13e == 0 || sequence_index_13e == 3) resolve_stage_surface_landing_transition();
        if (sequence_index_13e == 3) {
            velocity_x_f4 = static_cast<float>(velocity_x_f4 + 1.0);
            if (velocity_x_f4 > 0.0f) velocity_x_f4 = 0.0f;
        }
        if (!static_cast<unsigned char>(is_y_at_or_below_stage_surface(this)) && time_counter_144 % 5 == 0) opening_periodic_effect(true);
        if (sequence_index_13e == 1 || sequence_index_13e == 2) {
            velocity_y_f8 -= 0.5;
            if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
                velocity_y_f8 = 0.0f; y_f0 = stage_surface_height_at_x(this); select_sequence(3); return;
            }
        }
        if (advance_frame_and_dispatch()) { set_action_and_finalize(0); velocity_x_f4 = 0.0f; return; }
        if (sequence_entry(1)) {
            ++word_730; velocity_x_f4 = -8.5f; velocity_y_f8 = 4.0f;

            opening_effect_pair(true, false, 80.0);
        }
        return;
    }

    case 225: {
        velocity_y_f8 -= acceleration_y_100;
        if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
            zero_velocity_acceleration(); y_f0 = stage_surface_height_at_x(this); set_action_and_finalize(10); return;
        }
        if (word_7b0 > 0) word_4a8 = 2;
        if ((((frame_index_140 <= 7)))
            && time_counter_144 % 5 == 0) opening_periodic_effect(true);
        if (advance_frame_and_dispatch()) { set_action_and_finalize(9);  }
        if (sequence_entry(1)) {
            velocity_x_f4 = -7.5f;
            velocity_y_f8 = 3.5f;
            acceleration_y_100 = 0.45f;
            opening_effect_pair(true, false,
                120.0);
        }

        return;
    }

    case 226: {
        velocity_y_f8 -= acceleration_y_100;
        if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
            zero_velocity_acceleration(); y_f0 = stage_surface_height_at_x(this); set_action_and_finalize(10); return;
        }
        if (word_7b0 > 0) word_4a8 = 2;
        if ((((sequence_index_13e == 2)))
            && time_counter_144 % 5 == 0) opening_periodic_effect(false);
        if (advance_frame_and_dispatch()) { set_action_and_finalize(9); return; }
        if (sequence_entry(1)) {
            word_730 = 0;
            velocity_x_f4 = 9.0f;
            velocity_y_f8 = 3.0f;
            acceleration_y_100 = 0.35f;
            opening_effect_pair(false, true,
                110.0);
        }
        if (sequence_entry(2)) face_opponent_and_flip_horizontal_velocity();
        return;
    }

    case 300: {
        {
            resolve_stage_surface_landing_transition();

            if (try_dispatch_directional_action_208_210(0)) return;
            {
                bool braking = (byte_47e != 0);
                if (braking) {
                    velocity_x_f4 = static_cast<float>(velocity_x_f4 -
                        (0.5));
                    if (velocity_x_f4 < 0.0f) {
                        velocity_x_f4 = 0.0f;
                        byte_47e = 0;
                    }
                }
            }

            advance_or_action(0);
            if (middle_frame(4)) {
                float payload[3] = {0.0f, 0.0f, 6.0f};
                spawn_middle(899, 96, 129.0, payload);
                dispatch_indexed_event_member(27);
                byte_47e = 0;
            }

            return;
        }
    }

    case 301: {
        {
            resolve_stage_surface_landing_transition();

            if (try_dispatch_directional_action_208_210(0)) return;
            {
                bool braking = (byte_47e != 0);
                if (braking) {
                    velocity_x_f4 = static_cast<float>(velocity_x_f4 -
                        (0.5));
                    if (velocity_x_f4 < 0.0f) {
                        velocity_x_f4 = 0.0f;
                        byte_47e = 0;
                    }
                }
                if (frame_index_140 > 4) middle_decelerate(1.5);
            }

            advance_or_action(0);

            {
                if (middle_frame(3)) velocity_x_f4 = 10.0f;
                if (middle_frame(4)) { middle_ring(815, 155, 25.0f, false); dispatch_indexed_event_member(28); byte_47e = 0; }
            }

            return;
        }
    }

    case 302: {
        {
            resolve_stage_surface_landing_transition();

            if (try_dispatch_directional_action_208_210(1)) return;

            {
                if (field_6bc == 0) byte_750 = 0;
                if (sequence_index_13e == 0) {
                    if (velocity_x_f4 > 0.0f) velocity_x_f4 -= 0.5;
                    if (velocity_x_f4 < 0.0f) velocity_x_f4 = 0.0f;
                }
                if (sequence_index_13e == 1) {
                    if (velocity_x_f4 > 0.0f) velocity_x_f4 -= 1.0;
                    if (velocity_x_f4 < 0.0f) velocity_x_f4 = 0.0f;
                }
            }

            advance_or_action(0);

            {
                if (sequence_entry(1)) { set_action_and_finalize(0); return; }
                if (sequence_index_13e == 0) {
                    if (middle_frame(5)) {
                        if (byte_750) {
                            next_sequence_block();
                            emit_fighter_effect_433cc0(62, x_ec, static_cast<float>(y_f0 + 150.0), facing_104, 1);
                            return;
                        }
                        velocity_x_f4 = 11.0f;
                    }
                    if (middle_frame(6)) { dispatch_indexed_event_member(29); middle_ring(815, 125, 25.0f, false); }
                }
                if (sequence_index_13e == 1) {
                    if (middle_frame(1)) velocity_x_f4 = 20.0f;
                    if (middle_frame(2)) { dispatch_indexed_event_member(29); middle_ring(815, 125, 25.0f, false); }
                }
            }

            return;
        }
    }

    case 303: {
        {
            resolve_stage_surface_landing_transition();

            if (try_dispatch_directional_action_208_210(0)) return;
            {
                bool braking = (static_cast<signed char>(byte_47e) > 0);
                if (braking) {
                    velocity_x_f4 = static_cast<float>(velocity_x_f4 -
                        (static_cast<double>(0.6f)));
                    if (velocity_x_f4 < 0.0f) {
                        velocity_x_f4 = 0.0f;
                        byte_47e = 0;
                    }
                }
            }

            advance_or_action(2);

            if (middle_frame(5)) dispatch_indexed_event_member(28);

            return;
        }
    }

    case 304: {
        {
            resolve_stage_surface_landing_transition();

            if (try_dispatch_directional_action_208_210(1)) return;

            { if (field_6bc == 0) byte_750 = 0; middle_decelerate(0.5); }

            advance_or_action(2);

            {
                if (sequence_entry(1)) { set_action_and_finalize(2); return; }
                if (sequence_index_13e == 0) {
                    if (middle_frame(3) && byte_750 == 1) {
                        next_sequence_block();
                        emit_fighter_effect_433cc0(62, static_cast<float>(facing() * 11) + x_ec,
                            static_cast<float>(y_f0 + 88.0), facing_104, 1);
                        return;
                    }
                    if (middle_frame(4)) { velocity_x_f4 = 15.0f; dispatch_indexed_event_member(29); }
                    if (middle_frame(5)) velocity_x_f4 = 7.5f;
                }
                if (sequence_index_13e == 1) {
                    if (middle_frame(2)) { velocity_x_f4 = 25.0f; dispatch_indexed_event_member(29); }
                    if (middle_frame(3)) { velocity_x_f4 = 10.0f; middle_ring(815, 155, 25.0f, false); }
                }
            }

            return;
        }
    }

    case 305: {
        {
            resolve_stage_surface_landing_transition();

            if (try_dispatch_directional_action_208_210(1)) return;

            if (frame_index_140 >= 4) middle_decelerate(0.5);

            advance_or_action(0);

            if (middle_frame(4)) dispatch_indexed_event_member(29);

            return;
        }
    }

    case 306: {
        {
            velocity_y_f8 -= acceleration_y_100;
            if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
                set_action_and_finalize(10);
                {
                    y_f0 = stage_surface_height_at_x(this);
                    acceleration_y_100 = 0.0f;
                    velocity_y_f8 = 0.0f;
                }
                return;
            }

            advance_or_action(9);
            if ((sequence_index_13e == 0) && frame_index_140 == 4 && frame_timer_142 == 0) dispatch_indexed_event_member(28);

            return;
        }
    }

    case 307: {
        {
            if (field_6bc == 0) byte_750 = 0;
            velocity_y_f8 -= acceleration_y_100;
            if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
                set_action_and_finalize(10);
                { restore_surface_motion(); return; }
            }

            advance_or_action(9);

            {
                if (sequence_entry(1)) { set_action_and_finalize(9); return; }
                if (sequence_index_13e == 0) {
                    if (middle_frame(2)) { velocity_x_f4 = 3.0f; velocity_y_f8 = 5.0f; acceleration_y_100 = 0.3f; }
                    if (middle_frame(4)) dispatch_indexed_event_member(29);
                    if (middle_frame(7)) acceleration_y_100 = 0.6f;
                }
            }

            return;
        }
    }

    case 308: {
        {
            if (field_6bc == 0) byte_750 = 0;
            velocity_y_f8 -= acceleration_y_100;
            if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
                set_action_and_finalize(10);
                { restore_surface_motion(); return; }
            }

            advance_or_action(9);

            {
                if (sequence_entry(1)) { set_action_and_finalize(9); return; }
                if (sequence_index_13e == 0) {
                    if (middle_frame(4)) dispatch_indexed_event_member(29);
                    if (middle_frame(7)) acceleration_y_100 = 0.6f;
                }
            }

            return;
        }
    }

    case 309: {
        {
            velocity_y_f8 -= acceleration_y_100;
            if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
                set_action_and_finalize(10);
                { restore_surface_motion(); return; }
            }
            if (sequence_index_13e == 1) {
                velocity_x_f4 = static_cast<float>(field_73c * static_cast<double>(0.3f));
                velocity_y_f8 = field_73c;
                field_73c = static_cast<float>(field_73c - 1.0);
                if (field_73c <= 4.0f) field_73c = 4.0f;
                if (static_cast<signed char>(byte_184) > 0 && state_180 != 0) {
                    if (++word_730 >= 4) { state_180 = 0; word_730 = 0; }
                }
                if (time_counter_144 >= 15) { next_sequence_block(); acceleration_y_100 = 0.6f; return; }
            }
            advance_or_action(9);

            if (sequence_entry(1)) {
                field_73c = 15.0f; acceleration_y_100 = 0.0f; dispatch_indexed_event_member(29);
            }
            return;
        }
    }

    case 310: {
        if (state_180 != 0 && ++word_730 > 5) { state_180 = 0; word_730 = 0; }
        if (sequence_index_13e == 1) {
            if (time_counter_144 == 0) velocity_x_f4 = 15.0f;
            if (time_counter_144 % 8 == 0) dispatch_indexed_event_member(27);
            // The second increment in sequence1 is distinct and intentional.
            if (state_180 != 0 && ++word_730 > 5) { state_180 = 0; word_730 = 0; }
            if (time_counter_144 > 30) { next_sequence_block(); velocity_y_f8 = 6.0f; velocity_x_f4 = static_cast<float>(velocity_x_f4 * 0.5); }
        }
        if (sequence_index_13e == 2) {
            velocity_y_f8 -= acceleration_y_100;
            double projected_y = static_cast<double>(velocity_y_f8) + y_f0;
            float surface = stage_surface_height_at_x(this);
            if (projected_y <= surface && velocity_y_f8 < 0.0f) {
                velocity_y_f8 = 0.0f; y_f0 = stage_surface_height_at_x(this); set_action_and_finalize(9); return;
            }
        }
        advance_or_action(9);
        return;
    }

    case 320: {
        {
            resolve_stage_surface_landing_transition();

            if (try_dispatch_directional_action_208_210(0)) return;

            if (frame_index_140 > 1) middle_decelerate(2.0);

            advance_or_action(0);

            if (middle_frame(5)) { dispatch_indexed_event_member(28); byte_47e = 0; }

            return;
        }
    }

    case 321: {
        {
            resolve_stage_surface_landing_transition();

            if (try_dispatch_directional_action_208_210(0)) return;

            if (frame_index_140 > 3) middle_decelerate(0.5);

            advance_or_action(0);

            if (middle_frame(5)) { dispatch_indexed_event_member(28); byte_47e = 0; }
            if (middle_frame(10)) { dispatch_indexed_event_member(29); state_180 = 0; byte_184 = 1; }

            return;
        }
    }

    case 322: {
        {
            resolve_stage_surface_landing_transition();

            if (try_dispatch_directional_action_208_210(1)) return;

            if (frame_index_140 > 5) middle_decelerate(3.0);
            advance_or_action(0);

            {
                if (middle_frame(5)) { dispatch_indexed_event_member(29); velocity_x_f4 = 15.0f; byte_47e = 0; }
                if (middle_frame(6)) { float payload[3] = {0.0f, 0.0f, 5.0f}; spawn_middle(899, 166, 137.0, payload); }
                if (middle_frame(7)) velocity_x_f4 = 0.0f;
            }
            return;
        }
    }

    case 400: {
        resolve_stage_surface_landing_transition();
        if (field_6c0 == 0) byte_750 = 0;
        advance_or_action(0);
        if (sequence_entry(1)) { set_action_and_finalize(0); return; }
        if (sequence_index_13e == 0) {
            if (frame_timer_142 == 0 && frame_index_140 == 4 && byte_750) {
                emit_fighter_effect_433cc0(62, x_ec - static_cast<float>(facing() * 30), static_cast<float>(y_f0 + 112.0), facing_104, 1);
                next_sequence_block();
            }
            if (middle_frame(7)) {
                dispatch_character_wave_handle(0);
                middle_cost(45, 30);
                state_180 = 1;
                middle_fan800(60, 132.0, 40.0, 20, 100);
            }
        }
        if (sequence_index_13e == 1) {
            if (middle_frame(4)) {
                middle_cost(45, 50);
                state_180 = 1;
                dispatch_character_wave_handle(0);
                middle_fan800(60, 132.0, 60.0, 15, 135);
            }
        }
        return;
    }

    case 401: {
        resolve_stage_surface_landing_transition();
        if (field_6c0 == 0) byte_750 = 0;
        advance_or_action(0);
        if (sequence_entry(1)) { set_action_and_finalize(0); return; }
        if (sequence_index_13e == 0) {
            if (frame_timer_142 == 0 && frame_index_140 == 4 && byte_750) {
                emit_fighter_effect_433cc0(62, x_ec - static_cast<float>(facing() * 30), static_cast<float>(y_f0 + 112.0), facing_104, 1);
                next_sequence_block();
            }
            if (middle_frame(7)) {
                middle_cost(45, 30);
                state_180 = 1;
                dispatch_character_wave_handle(0);
                middle_fan800(60, 132.0, 40.0, 20, 100);
            }
        }
        if (sequence_index_13e == 1) {
            if (middle_frame(4)) {
                middle_cost(45, 50);
                state_180 = 1;
                dispatch_character_wave_handle(0);
                middle_fan800(60, 132.0, 60.0, 15, 135);
            }
        }
        return;
    }

    case 402: {
        resolve_stage_surface_landing_transition();
        if (field_6c0 == 0) byte_750 = 0;
        advance_or_action(2);
        if (sequence_entry(1)) { set_action_and_finalize(2); return; }
        if (sequence_index_13e == 0) {
            if (frame_timer_142 == 0 && frame_index_140 == 4 && byte_750) {
                emit_fighter_effect_433cc0(62, x_ec - static_cast<float>(facing() * 30), static_cast<float>(y_f0 + 70.0), facing_104, 1);
                next_sequence_block();
            }
            if (middle_frame(7)) {
                middle_cost(45, 30);
                state_180 = 1;
                dispatch_character_wave_handle(0);
                middle_fan800(55, 85.0, 12.0, 12, 36);
            }
        }
        if (sequence_index_13e == 1) {
            if (middle_frame(4)) {
                middle_cost(45, 50);
                state_180 = 1;
                dispatch_character_wave_handle(0);
                middle_fan800(55, 85.0, 10.0, 10, 50);
            }
        }
        return;
    }

    case 404: {
        if (sequence_index_13e == 2) resolve_stage_surface_landing_transition();
        if (field_6c0 == 0) byte_750 = 0;
        velocity_y_f8 -= acceleration_y_100;
        if (sequence_index_13e < 2 && static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
            select_sequence(2);
            restore_surface_motion();
            return;
        }
        advance_or_action(0);
        if (sequence_entry(1)) { set_action_and_finalize(9); return; }
        if (sequence_entry(2)) { set_action_and_finalize(9); return; }
        if (sequence_index_13e == 0) {
            if (frame_timer_142 == 0 && frame_index_140 == 4 && byte_750) {
                emit_fighter_effect_433cc0(62, x_ec - static_cast<float>(facing() * 30), static_cast<float>(y_f0 + 135.0), facing_104, 1);
                next_sequence_block();
            }
            if (middle_frame(7)) {
                middle_cost(45, 30);
                state_180 = 1;
                dispatch_character_wave_handle(0);
                middle_fan800(52, 150.0, 40.0, 20, 100);
            }
            if (frame_timer_142 == 0) { if (frame_index_140 == 14) acceleration_y_100 = 0.5f; }
        }
        if (sequence_index_13e == 1) {
            if (middle_frame(4)) {
                middle_cost(45, 50);
                state_180 = 1;
                dispatch_character_wave_handle(0);
                middle_fan800(52, 150.0, 60.0, 15, 135);
            }
            if (middle_frame(11)) acceleration_y_100 = 0.5f;
        }
        return;
    }

    case 406: {
        if (sequence_index_13e == 2) resolve_stage_surface_landing_transition();
        if (field_6c0 == 0) byte_750 = 0;
        velocity_y_f8 -= acceleration_y_100;
        if (sequence_index_13e < 2 && static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
            select_sequence(2);
            restore_surface_motion();
            return;
        }
        advance_or_action(0);
        if (sequence_entry(1)) { set_action_and_finalize(9); return; }
        if (sequence_entry(2)) { set_action_and_finalize(9); return; }
        if (sequence_index_13e == 0) {
            if (frame_timer_142 == 0 && frame_index_140 == 4 && byte_750) {
                emit_fighter_effect_433cc0(62, x_ec - static_cast<float>(facing() * 30), static_cast<float>(y_f0 + 135.0), facing_104, 1);
                next_sequence_block();
            }
            if (middle_frame(7)) {
                dispatch_character_wave_handle(0);
                middle_cost(45, 30);
                state_180 = 1;
                middle_fan800(52, 150.0, 40.0, 20, 100);
            }
            if (frame_timer_142 == 0) { if (frame_index_140 == 14) acceleration_y_100 = 0.5f; }
        }
        if (sequence_index_13e == 1) {
            if (middle_frame(4)) {
                dispatch_character_wave_handle(0);
                middle_cost(45, 50);
                state_180 = 1;
                middle_fan800(52, 150.0, 60.0, 15, 135);
            }
            if (middle_frame(11)) acceleration_y_100 = 0.5f;
        }
        return;
    }

    case 408: {
        resolve_stage_surface_landing_transition();
        if (frame_index_140 >= 7) velocity_x_f4 = static_cast<float>(velocity_x_f4 - 0.75);
        if (velocity_x_f4 < 0.0f) velocity_x_f4 = 0.0f;
        advance_or_action(0);
        if (middle_frame(6)) {
            float payload[3] = {0.0f, 0.0f, 4.0f}; spawn_middle(899, 166, 137.0, payload);
            dispatch_indexed_event_member(29); byte_47e = 0;
        }
        return;
    }

    case 409: {
        {
            velocity_y_f8 -= acceleration_y_100;
            if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
                set_action_and_finalize(10);
                {
                    zero_velocity_acceleration();
                    y_f0 = stage_surface_height_at_x(this);
                }
                return;
            }

            advance_or_action(9);

            return;
        }
    }

    case 410: {
        {
            resolve_stage_surface_landing_transition();
            if (field_6c4 == 0) byte_750 = 0;

            advance_or_action(0);
            if (sequence_entry(1)) {
                set_action_and_finalize(0); return;
            }
            if (sequence_index_13e == 0) {
                if (frame_timer_142 == 0) {
                    if (frame_index_140 == (5) && byte_750) {
                        float x = (x_ec);
                        emit_fighter_effect_433cc0(62, x,
                            static_cast<float>(y_f0 + ((160.0))), facing_104, 1);
                        next_sequence_block();
                    }
                    if (middle_frame(6)) {
                        state_180 = 1;
                        middle_cost(60, 50);

                        dispatch_character_wave_handle(1);
                        {
                            float payload[3] = {(0.0f), 15.0f, 0.0f};
                            spawn_middle(801, (130),
                                ((140.0)), payload);
                        }
                    }
                }
            }
            if (sequence_index_13e == 1) {
                if (middle_frame(2)) {
                    middle_cost(60, 50); state_180 = 1; dispatch_character_wave_handle(1);
                    {
                        float payload[3] = {(0.0f), 22.5f, 0.0f};
                        spawn_middle(801, (130),
                            ((140.0)), payload);
                    }
                }
            }
            return;
        }
    }

    case 411: {
        {
            resolve_stage_surface_landing_transition();
            if (field_6c4 == 0) byte_750 = 0;

            advance_or_action(0);
            if (sequence_entry(1)) {
                set_action_and_finalize(0); return;
            }
            if (sequence_index_13e == 0) {
                if (frame_timer_142 == 0) {
                    if (frame_index_140 == (5) && byte_750) {
                        float x = (x_ec);
                        emit_fighter_effect_433cc0(62, x,
                            static_cast<float>(y_f0 + ((160.0))), facing_104, 1);
                        next_sequence_block();
                    }
                    if (middle_frame(6)) {
                        state_180 = 1;
                        middle_cost(60, 50);

                        dispatch_character_wave_handle(1);
                        middle_scatter801(false);
                    }
                }
            }
            if (sequence_index_13e == 1) {
                if (middle_frame(2)) {
                    middle_cost(60, 50); state_180 = 1; dispatch_character_wave_handle(1);
                    middle_scatter801(true);
                }
            }
            return;
        }
    }

    case 412: {
        if ((sequence_index_13e == 0 && frame_index_140 >= 2) || sequence_index_13e == 1) {
            velocity_y_f8 -= acceleration_y_100;
            velocity_x_f4 = static_cast<float>(velocity_x_f4 - static_cast<double>(0.1f));
            if (velocity_x_f4 < 1.0f) velocity_x_f4 = 1.0f;
            if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
                { zero_velocity_acceleration(); y_f0 = stage_surface_height_at_x(this); select_sequence(2); return; }
            }
        } else resolve_stage_surface_landing_transition();
        advance_or_action(0);
        if (sequence_index_13e == 0) {
            if (middle_frame(2)) { velocity_x_f4 = 6.0f; velocity_y_f8 = 6.0f; acceleration_y_100 = 0.2f; }
            if (middle_frame(9)) {
                middle_cost(60, 50); state_180 = 1; dispatch_character_wave_handle(16);
                float payload[3] = {-20.0f, 13.0f, 0.0f}; spawn_middle(802, 75, 168.0, payload);
                middle_ring(802, 0, 15.0f, true, payload);
            }
        }
        return;
    }

    case 414: {
        {
            if (sequence_index_13e == 2) resolve_stage_surface_landing_transition();
            if (field_6c4 == 0) byte_750 = 0;
            if (sequence_index_13e < 2) {
                velocity_y_f8 -= acceleration_y_100;
                if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
                    select_sequence(2); { restore_surface_motion(); return; }
                }
            }
            advance_or_action(0);
            if (sequence_entry(1)) {
                set_action_and_finalize(9); return;
            }
            if (sequence_entry(2)) {
                set_action_and_finalize(9); return;
            }
            if (sequence_index_13e == 0) {
                if (frame_timer_142 == 0 && frame_index_140 == 5 && byte_750) {
                    emit_fighter_effect_433cc0(62, x_ec,
                        static_cast<float>(y_f0 + 155.0), facing_104, 1);
                    next_sequence_block();
                }
                if (middle_frame(6)) {
                        middle_cost(60, 50);
                        state_180 = 1;
                        dispatch_character_wave_handle(1);
                        {
                            float payload[3] = {0.0f, 15.0f, 0.0f};
                            spawn_middle(801, 130, 145.0, payload);
                        }
                }
                if (middle_frame(9)) acceleration_y_100 = 0.5f;
            }
            if (sequence_index_13e == 1) {
                if (middle_frame(2)) {
                    middle_cost(60, 50); state_180 = 1; dispatch_character_wave_handle(1);
                    {
                        float payload[3] = {(0.0f), 22.5f, 0.0f};
                        spawn_middle(801, (130),
                            ((145.0)), payload);
                    }
                }
                if (middle_frame(5)) acceleration_y_100 = 0.5f;
            }
            return;
        }
    }

    case 415: {
        {
            if (sequence_index_13e == 2) resolve_stage_surface_landing_transition();
            if (field_6c4 == 0) byte_750 = 0;
            if (sequence_index_13e < 2) {
                velocity_y_f8 -= acceleration_y_100;
                if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
                    select_sequence(2); { restore_surface_motion(); return; }
                }
            }
            advance_or_action(0);
            if (sequence_entry(1)) {
                set_action_and_finalize(9); return;
            }
            if (sequence_entry(2)) {
                set_action_and_finalize(9); return;
            }
            if (sequence_index_13e == 0) {
                if (frame_timer_142 == 0 && frame_index_140 == 5 && byte_750) {
                    emit_fighter_effect_433cc0(62, x_ec,
                        static_cast<float>(y_f0 + 155.0), facing_104, 1);
                    next_sequence_block();
                }
                if (middle_frame(6)) {
                        state_180 = 1;
                        middle_cost(60, 50);

                        dispatch_character_wave_handle(1);
                        middle_scatter801(false);
                }
                if (middle_frame(9)) acceleration_y_100 = 0.5f;
            }
            if (sequence_index_13e == 1) {
                if (middle_frame(2)) {
                    middle_cost(60, 50); state_180 = 1; dispatch_character_wave_handle(1);
                    middle_scatter801(true);
                }
                if (middle_frame(5)) acceleration_y_100 = 0.5f;
            }
            return;
        }
    }

    case 416: {
        {
            if (sequence_index_13e == 2) resolve_stage_surface_landing_transition();
            if (field_6c4 == 0) byte_750 = 0;
            if (sequence_index_13e < 2) {
                velocity_y_f8 -= acceleration_y_100;
                if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
                    select_sequence(2); { restore_surface_motion(); return; }
                }
            }
            advance_or_action(0);
            if (sequence_entry(1)) {
                set_action_and_finalize(9); return;
            }
            if (sequence_entry(2)) {
                set_action_and_finalize(9); return;
            }
            if (sequence_index_13e == 0) {
                if (frame_timer_142 == 0 && frame_index_140 == 3 && byte_750) {
                    emit_fighter_effect_433cc0(62, x_ec - static_cast<float>(facing() * 47), static_cast<float>(y_f0 + 132.0), facing_104, 1); next_sequence_block(); return;
                }
                if (middle_frame(4)) {
                        middle_cost(60, 50);
                        state_180 = 1;
                        dispatch_character_wave_handle(1);
                        {
                            float payload[3] = {30.0f, 15.0f, 5.0f};
                            spawn_middle(801, 62, 114.0, payload);
                        }
                }
                if (middle_frame(7)) acceleration_y_100 = 0.5f;
            }
            if (sequence_index_13e == 1) {
                if (middle_frame(2)) {
                    middle_cost(60, 50); state_180 = 1; dispatch_character_wave_handle(1);
                    {
                        float payload[3] = {30.0f, 15.0f, 5.0f};
                        spawn_middle(801, 62, 114.0, payload);
                        payload[0] = 50.0f; payload[1] = 15.0f; payload[2] = 5.0f;
                        spawn_middle(801, 62, 114.0, payload);
                    }
                }
                if (middle_frame(6)) acceleration_y_100 = 0.5f;
            }
            return;
        }
    }

    case 417: {
        {
            if (sequence_index_13e == 2) resolve_stage_surface_landing_transition();
            if (field_6c4 == 0) byte_750 = 0;
            if (sequence_index_13e < 2) {
                velocity_y_f8 -= acceleration_y_100;
                if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
                    select_sequence(2); { restore_surface_motion(); return; }
                }
            }
            advance_or_action(0);
            if (sequence_entry(1)) {
                set_action_and_finalize(9); return;
            }
            if (sequence_entry(2)) {
                set_action_and_finalize(9); return;
            }
            if (sequence_index_13e == 0) {
                if (frame_timer_142 == 0 && frame_index_140 == 3 && byte_750) {
                    emit_fighter_effect_433cc0(62, x_ec - static_cast<float>(facing() * 47), static_cast<float>(y_f0 + 132.0), facing_104, 1); next_sequence_block(); return;
                }
                if (middle_frame(4)) {
                        middle_cost(60, 50);
                        state_180 = 1;
                        dispatch_character_wave_handle(1);
                        {
                            float payload[3] = {50.0f, 15.0f, 5.0f};
                            spawn_middle(801, 46, 106.0, payload);
                        }
                }
                if (middle_frame(7)) acceleration_y_100 = 0.5f;
            }
            if (sequence_index_13e == 1) {
                if (middle_frame(2)) {
                    middle_cost(60, 50); state_180 = 1; dispatch_character_wave_handle(1);
                    {
                        float payload[3] = {50.0f, 15.0f, 5.0f};
                        spawn_middle(801, 46, 106.0, payload);
                        payload[0] = 70.0f; payload[1] = 15.0f; payload[2] = 5.0f;
                        spawn_middle(801, 46, 106.0, payload);
                    }
                }
                if (middle_frame(6)) acceleration_y_100 = 0.5f;
            }
            return;
        }
    }

    case 418: {
        if (sequence_index_13e == 2) resolve_stage_surface_landing_transition();
        if (static_cast<unsigned char>(is_y_at_or_below_stage_surface(this))) velocity_x_f4 = static_cast<float>(velocity_x_f4 - 0.5);
        if (velocity_x_f4 < 0.0f) velocity_x_f4 = 0.0f;
        if (sequence_index_13e < 2) velocity_y_f8 -= acceleration_y_100;
        if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
            { zero_velocity_acceleration(); y_f0 = stage_surface_height_at_x(this); select_sequence(2); return; }
        }
        advance_or_action(0);
        if (sequence_index_13e == 0) {
            if (middle_frame(2)) { velocity_x_f4 = 7.5f; velocity_y_f8 = 5.0f; acceleration_y_100 = 0.3f; }
            if (middle_frame(9)) dispatch_indexed_event_member(29);
        }
        return;
    }

    case 500: {
        resolve_stage_surface_landing_transition(); byte_17c = 0;
        if (sequence_index_13e == 0 && frame_index_140 >= 7) {
            velocity_x_f4 = static_cast<float>(velocity_x_f4 - 0.75);
            if (frame_index_140 <= 11) {
                if (velocity_x_f4 < 1.0f) velocity_x_f4 = 1.0f;
            } else {
                if (velocity_x_f4 < 0.0f) velocity_x_f4 = 0.0f;
            }
            if (state_180 != 0) {
                ++word_730;
                if (byte_184 > 0 && word_730 >= 5) { word_730 = 0; state_180 = 0; }
            }
        }
        advance_or_action(0);
        if (sequence_index_13e == 0) {
            if (middle_frame(8)) spawn_owned_object_via_manager(810,
                static_cast<float>(facing() * 130) + x_ec, static_cast<float>(y_f0 + 125.0), facing_104, 1, 0, 0);
            if (middle_frame(7)) { add_phase_scaled_counter_558(50); adjust_counter_482(200, 120); velocity_x_f4 = 10.0f; dispatch_character_wave_handle(10); }
        }
        return;
    }

    case 501: {
        resolve_stage_surface_landing_transition(); byte_17c = 0;
        if (sequence_index_13e == 0 && frame_index_140 >= 7) {
            velocity_x_f4 = static_cast<float>(velocity_x_f4 - 0.75);
            if (frame_index_140 <= 11) {
                if (velocity_x_f4 < 1.0f) velocity_x_f4 = 1.0f;
            } else {
                if (velocity_x_f4 < 0.0f) velocity_x_f4 = 0.0f;
            }
            if (state_180 != 0) {
                ++word_730;
                if (byte_184 > 0 && word_730 >= 5) { word_730 = 0; state_180 = 0; }
            }
        }
        advance_or_action(0);
        if (sequence_index_13e == 0) {
            if (middle_frame(8)) spawn_owned_object_via_manager(810,
                static_cast<float>(facing() * 130) + x_ec, static_cast<float>(y_f0 + 125.0), facing_104, 1, 0, 0);
            if (middle_frame(7)) { add_phase_scaled_counter_558(50); adjust_counter_482(200, 120); velocity_x_f4 = 15.0f; dispatch_character_wave_handle(10); }
        }
        return;
    }

    case 505: {
        {
            resolve_stage_surface_landing_transition(); byte_17c = 4;
            if (field_6c0 == 0) byte_750 = 0;
            advance_or_action(0);
            if (sequence_entry(1)) set_action_and_finalize(0);
            if (sequence_index_13e == 0) {
                if (frame_timer_142 == 0 && frame_index_140 == 7 && byte_750 == 1) {
                    next_sequence_block();
                    emit_fighter_effect_433cc0(62, x_ec - static_cast<float>(facing() * 41),
                        static_cast<float>(y_f0 + 192.0), facing_104, 1); return;
                }
                if (frame_timer_142 == 0 && frame_index_140 == 10) {
                    float payload[3] = {0.0f, 0.0f, 0.0f};
                    spawn_middle(815, 150, 120.0, payload);
                    add_phase_scaled_counter_558(50); adjust_counter_482(200, 120);
                    middle_ring(815, 55, 20.0f, false, payload); dispatch_character_wave_handle(19);
                }
            }
            if (sequence_index_13e == 1 && middle_frame(4)) {
                float payload[3] = {0.0f, 0.0f, 1.0f};
                spawn_middle(815, 150, 120.0, payload);
                add_phase_scaled_counter_558(50); adjust_counter_482(200, 120);
                middle_ring(815, 55, 20.0f, false, payload); dispatch_character_wave_handle(19);
            }
            return;
        }
    }

    case 506: {
        {
            resolve_stage_surface_landing_transition(); byte_17c = 4;
            if (field_6c4 == 0) byte_750 = 0;
            advance_or_action(0);
            if (sequence_entry(1)) set_action_and_finalize(0);
            if (sequence_index_13e == 0) {
                if (frame_timer_142 == 0 && frame_index_140 == 7 && byte_750 == 1) {
                    next_sequence_block();
                    emit_fighter_effect_433cc0(62, x_ec - static_cast<float>(facing() * 41),
                        static_cast<float>(y_f0 + 192.0), facing_104, 1); return;
                }
                if (frame_timer_142 == 0 && frame_index_140 == 10) {
                    float payload[3] = {0.0f, 0.0f, 3.0f};
                    spawn_middle(815, 150, 195.0, payload);
                    add_phase_scaled_counter_558(50); adjust_counter_482(200, 120);
                    middle_ring(815, 55, 20.0f, false, payload); dispatch_character_wave_handle(19);
                }
            }
            if (sequence_index_13e == 1 && middle_frame(4)) {
                float payload[3] = {0.0f, 0.0f, 4.0f};
                spawn_middle(815, 150, 195.0, payload);
                add_phase_scaled_counter_558(50); adjust_counter_482(200, 120);
                middle_ring(815, 55, 20.0f, false, payload); dispatch_character_wave_handle(19);
            }
            return;
        }
    }

    case 520: {
        resolve_stage_surface_landing_transition(); byte_17c = 1;
        if (sequence_index_13e == 0) {
            if (middle_frame(3)) adjust_counter_482(200, 120);
            if (middle_frame(10)) {
                float payload[3];
                middle_ring(815, 55, 25.0f, false, payload);
                payload[0] = 0.0f; payload[1] = 0.0f; payload[2] = 1.0f;
                add_phase_scaled_counter_558(50);
                spawn_owned_object_via_manager(811, x_ec, y_f0, facing_104, -1, payload, 3);
                dispatch_character_wave_handle(11);
            }
        }
        advance_or_action(0);
        return;
    }

    case 521: {
        resolve_stage_surface_landing_transition(); byte_17c = 1;
        if (sequence_index_13e == 0) {
            if (middle_frame(3)) adjust_counter_482(200, 120);
            if (middle_frame(10)) {
                float payload[3];
                middle_ring(815, 55, 25.0f, false, payload); add_phase_scaled_counter_558(50);
                payload[0] = 0.0f; payload[1] = 0.0f; payload[2] = 1.0f;
                spawn_owned_object_via_manager(811, x_ec, y_f0, facing_104, -1, payload, 3);
                dispatch_character_wave_handle(11);
            }
        }
        advance_or_action(0);
        return;
    }

    case 525: {
        resolve_stage_surface_landing_transition(); byte_17c = 5; advance_or_action(0);
        if (sequence_index_13e == 0 && middle_frame(9)) {
            float payload[3] = {0.0f, 10.0f, 0.0f}; spawn_middle(816, 90, 105.0, payload);
            add_phase_scaled_counter_558(50); adjust_counter_482(200, 120); dispatch_character_wave_handle(16); state_180 = 1;
        }
        return;
    }

    case 526: {
        resolve_stage_surface_landing_transition(); byte_17c = 5; advance_or_action(0);
        if (sequence_index_13e == 0 && middle_frame(9)) {
            float payload[3] = {0.0f, 10.0f, 6.0f}; spawn_middle(816, 90, 105.0, payload);
            add_phase_scaled_counter_558(50); adjust_counter_482(200, 120); dispatch_character_wave_handle(16); state_180 = 1;
        }
        return;
    }

    case 540: {
        resolve_stage_surface_landing_transition(); byte_17c = 2;
        if (field_6c0 == 0) byte_750 = 0; advance_or_action(0);
        if (sequence_entry(1)) { set_action_and_finalize(0); return; }
        if (sequence_index_13e == 0) {
            if (frame_index_140 >= 6 && frame_index_140 <= 13 && byte_606 >= 4) word_4a8 = 2;
            if (middle_frame(8)) {
                add_phase_scaled_counter_558(50); adjust_counter_482(200, 120);
                float payload[3] = {0.0f, 0.0f, 1.0f};
                spawn_owned_object_via_manager(812, x_ec, static_cast<float>((y_f0 + 320.0) + 1000.0),
                    facing_104, 1, payload, 3);
            }
            if (middle_frame(12)) {
                state_180 = 1; float payload[3] = {0.0f, 0.0f, 2.0f}; spawn_middle(812, 0, 320.0, payload);
                payload[2] = 3.0f;
                spawn_owned_object_via_manager(812, x_ec, static_cast<float>(y_f0 + 320.0), reverse_facing(), 1, payload, 3);
                dispatch_character_wave_handle(13); field_73c = static_cast<float>(random_roll(360));
                for (int angle = 0; angle < 360; angle += 45) {
                    payload[0] = static_cast<float>(angle + 22.5 + field_73c); payload[1] = 30.0f; payload[2] = 4.0f;
                    if (payload[0] >= 0.0f && payload[0] <= 180.0f)
                        spawn_owned_object_via_manager(812, x_ec, y_f0, facing_104, 1, payload, 3);
                    else
                        spawn_owned_object_via_manager(812, x_ec, y_f0, facing_104, -1, payload, 3);
                }
            }
        }
        if (sequence_index_13e == 1 && frame_index_140 == 0 && !byte_750) {
            select_sequence(0); frame_index_140 = 7;
        }
        return;
    }

    case 541: {
        resolve_stage_surface_landing_transition(); byte_17c = 2;
        if (field_6c4 == 0) byte_750 = 0; advance_or_action(0);
        if (sequence_entry(1)) { set_action_and_finalize(0); return; }
        if (sequence_index_13e == 0) {
            if (frame_index_140 >= 6 && frame_index_140 <= 13 && byte_606 >= 4) word_4a8 = 2;
            if (middle_frame(8)) {
                add_phase_scaled_counter_558(50); adjust_counter_482(200, 120);
                float payload[3] = {0.0f, 0.0f, 1.0f};
                spawn_owned_object_via_manager(812, x_ec, static_cast<float>((y_f0 + 320.0) + 1000.0),
                    facing_104, 1, payload, 3);
            }
            if (middle_frame(12)) {
                state_180 = 1; float payload[3] = {0.0f, 0.0f, 2.0f}; spawn_middle(812, 0, 320.0, payload);
                payload[2] = 3.0f;
                spawn_owned_object_via_manager(812, x_ec, static_cast<float>(y_f0 + 320.0), reverse_facing(), 1, payload, 3);
                dispatch_character_wave_handle(13); field_73c = static_cast<float>(random_roll(360));
                for (int angle = 0; angle < 360; angle += 45) {
                    payload[0] = static_cast<float>(angle + 22.5 + field_73c); payload[1] = 30.0f; payload[2] = 4.0f;
                    if (payload[0] >= 0.0f && payload[0] <= 180.0f)
                        spawn_owned_object_via_manager(812, x_ec, y_f0, facing_104, 1, payload, 3);
                    else
                        spawn_owned_object_via_manager(812, x_ec, y_f0, facing_104, -1, payload, 3);
                }
            }
        }
        if (sequence_index_13e == 1 && frame_index_140 == 0 && !byte_750) {
            select_sequence(0); frame_index_140 = 7;
        }
        return;
    }

    case 545: {
        resolve_stage_surface_landing_transition(); byte_17c = 6; advance_or_action(0);
        if (sequence_entry(1)) { set_action_and_finalize(0); return; }
        if (sequence_index_13e == 0 && middle_frame(12)) {
            add_phase_scaled_counter_558(50); adjust_counter_482(200, 120); state_180 = 1;
            float payload[3] = {0.0f, 0.0f, 0.0f}; spawn_middle(817, 0, 320.0, payload);
            payload[2] = 5.0f; spawn_middle(817, 0, 320.0, payload); dispatch_character_wave_handle(17);
        }
        return;
    }

    case 546: {
        resolve_stage_surface_landing_transition(); byte_17c = 6; advance_or_action(0);
        if (sequence_entry(1)) { set_action_and_finalize(0); return; }
        if (sequence_index_13e == 0 && middle_frame(12)) {
            add_phase_scaled_counter_558(50); adjust_counter_482(200, 120); state_180 = 1;
            float payload[3] = {0.0f, 1.0f, 0.0f}; spawn_middle(817, 0, 320.0, payload);
            payload[2] = 5.0f; spawn_middle(817, 0, 320.0, payload); dispatch_character_wave_handle(17);
        }
        return;
    }

    case 547: {
        if (sequence_index_13e == 2) resolve_stage_surface_landing_transition();
        byte_17c = 2;
        if (sequence_index_13e < 2) {
            velocity_y_f8 -= acceleration_y_100;
            double projected_y = static_cast<double>(velocity_y_f8) + y_f0;
            float surface = stage_surface_height_at_x(this);
            if (projected_y <= surface && velocity_y_f8 < 0.0f) {
                zero_velocity_acceleration(); select_sequence(2); y_f0 = stage_surface_height_at_x(this); return;
            }
        }
        if (sequence_index_13e <= 1) if (field_6c0 == 0) byte_750 = 0;
        advance_or_action(9);
        if (sequence_entry(1)) { set_action_and_finalize(9); return; }
        if (sequence_index_13e == 0) {
            if (frame_timer_142 == 0 && frame_index_140 == 8 && byte_750 == 1) { next_sequence_block(); return; }
            if (frame_timer_142 == 0 && frame_index_140 == 6) {
                state_180 = 1; dispatch_character_wave_handle(7); velocity_x_f4 = -4.0f; velocity_y_f8 = 8.0f; acceleration_y_100 = 0.5f;
                spawn_owned_object_via_manager(816, static_cast<float>(facing() * 30) + x_ec,
                    static_cast<float>(y_f0 + 62.0), facing_104, 1, 0, 0);
                adjust_counter_482(200, 120); add_phase_scaled_counter_558(50);
            }
        }
        return;
    }

    case 560: {
        resolve_stage_surface_landing_transition();
        byte_17c = 3;
        if (field_6c0 == 0)
            byte_750 = 0;

        advance_or_action(0);
        if (sequence_entry(1)) {
            set_action_and_finalize(0);
            return;
        }
        if (sequence_index_13e == 0) {
            if (frame_timer_142 == 0 && frame_index_140 == 7)
                emit_813_aimed(0);
            if (frame_timer_142 == 0 && frame_index_140 == 8 && byte_750) {
                next_sequence_block();
                return;
            }
        }

        return;
    }

    case 561: {
        resolve_stage_surface_landing_transition();
        byte_17c = 3;
        if (field_6c4 == 0)
            byte_750 = 0;

        advance_or_action(0);
        if (sequence_entry(1)) {
            set_action_and_finalize(0);
            return;
        }
        if (sequence_index_13e == 0) {
            if (frame_timer_142 == 0 && frame_index_140 == 7)
                emit_813_aimed(((1)));
            if (frame_timer_142 == 0 && frame_index_140 == 8 && byte_750) {
                next_sequence_block();
                return;
            }
        }

        return;
    }

    case 562: {
        if (sequence_index_13e == 2)
            resolve_stage_surface_landing_transition();
        byte_17c = 3;
        if (field_6c0 == 0)
            byte_750 = 0;
        if (sequence_index_13e < 2) {
            velocity_y_f8 -= acceleration_y_100;
            if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
                zero_velocity_acceleration();
                y_f0 = stage_surface_height_at_x(this);
                select_sequence(2);
                return;
            }
        }
        advance_or_action(0);
        if (sequence_entry(1)) {
            set_action_and_finalize(9);
            return;
        }
        if (sequence_entry(2)) {
            set_action_and_finalize(9);
            return;
        }
        if (sequence_index_13e == 0) {
            if (frame_timer_142 == 0 && frame_index_140 == 7)
                emit_813_aimed(0);
            if (frame_timer_142 == 0 && frame_index_140 == 8 && byte_750) {
                next_sequence_block();
                return;
            }
            if ((frame_timer_142 == 0) && frame_index_140 == 9)
                acceleration_y_100 = 0.5f;
        }
        if ((sequence_index_13e == 1) && frame_timer_142 == 0 && frame_index_140 == 2)
            acceleration_y_100 = 0.5f;
        return;
    }

    case 563: {
        if (sequence_index_13e == 2)
            resolve_stage_surface_landing_transition();
        byte_17c = 3;
        if (field_6c4 == 0)
            byte_750 = 0;
        if (sequence_index_13e < 2) {
            velocity_y_f8 -= acceleration_y_100;
            if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
                zero_velocity_acceleration();
                y_f0 = stage_surface_height_at_x(this);
                select_sequence(2);
                return;
            }
        }
        advance_or_action(0);
        if (sequence_entry(1)) {
            set_action_and_finalize(9);
            return;
        }
        if (sequence_entry(2)) {
            set_action_and_finalize(9);
            return;
        }
        if (sequence_index_13e == 0) {
            if (frame_timer_142 == 0 && frame_index_140 == 7)
                emit_813_aimed(((2)));
            if (frame_timer_142 == 0 && frame_index_140 == 8 && byte_750) {
                next_sequence_block();
                return;
            }
            if ((frame_timer_142 == 0) && frame_index_140 == 9)
                acceleration_y_100 = 0.5f;
        }
        if ((sequence_index_13e == 1) && frame_timer_142 == 0 && frame_index_140 == 2)
            acceleration_y_100 = 0.5f;
        return;
    }

    case 565: {
        {
            resolve_stage_surface_landing_transition();
        }

        byte_17c = 7;
        if (field_6c0 == 0)
            byte_750 = 0;

        if (word_730 == 1) {
            if (sequence_index_13e == 0)
                emit_object818_phase(3);
            if (sequence_index_13e == 1)
                emit_object818_phase(4);
        }

        if (advance_frame_and_dispatch())
            set_action_and_finalize(0);

        if (time_counter_144 == 0 && frame_timer_142 == 0 && frame_index_140 == 0) {
            if (sequence_index_13e == 1) {
                set_action_and_finalize(0);
                return;
            }
        }

        if (sequence_index_13e == 0) {
            if (frame_timer_142 == 0 && frame_index_140 == 5 && byte_750) {
                emit_fighter_effect_433cc0(62, x_ec, static_cast<float>(y_f0 + 150.0), facing_104, 1); next_sequence_block(); return;
            }
            if (frame_timer_142 == 0 && frame_index_140 == 6)
                start_object818_emission(false);
        }

        if (sequence_index_13e == 1) {
            if (frame_timer_142 == 0 && frame_index_140 == 2)
                start_object818_emission(false);
            // The shared 62AEDC tail rechecks the timer after the wave call.
        }
        return;
    }

    case 566: {
        {
            resolve_stage_surface_landing_transition();
        }

        byte_17c = 7;
        if (field_6c4 == 0)
            byte_750 = 0;

        if (word_730 == 1) {
            if (sequence_index_13e == 0)
                emit_object818_phase(3);
            if (sequence_index_13e == 1)
                emit_object818_phase(4);
        }

        if (advance_frame_and_dispatch())
            set_action_and_finalize(0);

        if (time_counter_144 == 0 && frame_timer_142 == 0 && frame_index_140 == 0) {
            if (sequence_index_13e == 1) {
                set_action_and_finalize(0);
                return;
            }
        }

        if (sequence_index_13e == 0) {
            if (frame_timer_142 == 0 && frame_index_140 == 5 && byte_750) {
                emit_fighter_effect_433cc0(62, x_ec, static_cast<float>(y_f0 + 150.0), facing_104, 1); next_sequence_block(); return;
            }
            if (frame_timer_142 == 0 && frame_index_140 == 6)
                start_object818_emission(true);
        }

        if (sequence_index_13e == 1) {
            if (frame_timer_142 == 0 && frame_index_140 == 2)
                start_object818_emission(true);
            // The shared 62AEDC tail rechecks the timer after the wave call.
        }
        return;
    }

    case 567: {
        if (sequence_index_13e == 2) {
            resolve_stage_surface_landing_transition();
        } else {
            velocity_y_f8 = velocity_y_f8 - acceleration_y_100;
            if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
                zero_velocity_acceleration();
                y_f0 = stage_surface_height_at_x(this);
                select_sequence(2);
                return;
            }
        }

        byte_17c = 7;
        if (field_6c0 == 0)
            byte_750 = 0;

        if (word_730 == 1) {
            if (sequence_index_13e == 0)
                emit_object818_phase(3);
            if (sequence_index_13e == 1)
                emit_object818_phase(4);
        }

        if (advance_frame_and_dispatch())
            set_action_and_finalize(0);

        if (sequence_entry(1)) {
            set_action_and_finalize(9);
            return;
        }
        if (sequence_entry(2)) {
            set_action_and_finalize(9);
            return;
        }

        if (sequence_index_13e == 0) {
            if (frame_timer_142 == 0 && frame_index_140 == 5 && byte_750) {
                emit_fighter_effect_433cc0(62, x_ec, static_cast<float>(y_f0 + 150.0), facing_104, 1); next_sequence_block(); return;
            }
            if (frame_timer_142 == 0 && frame_index_140 == 6)
                start_object818_emission(false);
            if ((frame_timer_142 == 0) && frame_index_140 == 10)
                acceleration_y_100 = 0.6f;
        }

        if (sequence_index_13e == 1) {
            if (frame_timer_142 == 0 && frame_index_140 == 2)
                start_object818_emission(false);
            // The shared 62AEDC tail rechecks the timer after the wave call.
            if ((frame_timer_142 == 0) && frame_index_140 == 6)
                acceleration_y_100 = 0.6f;
        }
        return;
    }

    case 568: {
        if (sequence_index_13e == 2) {
            resolve_stage_surface_landing_transition();
        } else {
            velocity_y_f8 = velocity_y_f8 - acceleration_y_100;
            if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
                zero_velocity_acceleration();
                y_f0 = stage_surface_height_at_x(this);
                select_sequence(2);
                return;
            }
        }

        byte_17c = 7;
        if (field_6c4 == 0)
            byte_750 = 0;

        if (word_730 == 1) {
            if (sequence_index_13e == 0)
                emit_object818_phase(3);
            if (sequence_index_13e == 1)
                emit_object818_phase(4);
        }

        if (advance_frame_and_dispatch())
            set_action_and_finalize(0);

        if (sequence_entry(1)) {
            set_action_and_finalize(9);
            return;
        }
        if (sequence_entry(2)) {
            set_action_and_finalize(9);
            return;
        }

        if (sequence_index_13e == 0) {
            if (frame_timer_142 == 0 && frame_index_140 == 5 && byte_750) {
                emit_fighter_effect_433cc0(62, x_ec, static_cast<float>(y_f0 + 150.0), facing_104, 1); next_sequence_block(); return;
            }
            if (frame_timer_142 == 0 && frame_index_140 == 6)
                start_object818_emission(true);
            if ((frame_timer_142 == 0) && frame_index_140 == 10)
                acceleration_y_100 = 0.6f;
        }

        if (sequence_index_13e == 1) {
            if (frame_timer_142 == 0 && frame_index_140 == 2)
                start_object818_emission(true);
            // The shared 62AEDC tail rechecks the timer after the wave call.
            if ((frame_timer_142 == 0) && frame_index_140 == 6)
                acceleration_y_100 = 0.6f;
        }
        return;
    }

    case 570: {
        resolve_stage_surface_landing_transition();
        byte_17c = 11;

        advance_or_action(0);

        if (sequence_index_13e == 0 && frame_timer_142 == 0) {
            if (frame_index_140 == 7)
                emit_823(false, false);
        }
        return;
    }

    case 571: {
        resolve_stage_surface_landing_transition();
        byte_17c = 11;

        advance_or_action(0);

        if (sequence_index_13e == 0 && frame_timer_142 == 0) {
            if (frame_index_140 == 7)
                emit_823(true, false);
        }
        return;
    }

    case 572: {
        if (sequence_index_13e == 1)
            resolve_stage_surface_landing_transition();
        byte_17c = 11;
        if (sequence_index_13e < 1) {
            velocity_y_f8 -= acceleration_y_100;
            if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
                zero_velocity_acceleration();
                y_f0 = stage_surface_height_at_x(this);
                select_sequence(1);
                return;
            }
        }
        advance_or_action(0);
        if (sequence_entry(1)) {
            set_action_and_finalize(9);
            return;
        }
        if (sequence_index_13e == 0 && frame_timer_142 == 0) {
            if (frame_index_140 == 7)
                emit_823(false, false);
            if ((frame_timer_142 == 0) && frame_index_140 == 9)
                acceleration_y_100 = 0.5f;
        }
        return;
    }

    case 573: {
        if (sequence_index_13e == 1)
            resolve_stage_surface_landing_transition();
        byte_17c = 11;
        if (sequence_index_13e < 1) {
            velocity_y_f8 -= acceleration_y_100;
            if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
                zero_velocity_acceleration();
                y_f0 = stage_surface_height_at_x(this);
                select_sequence(1);
                return;
            }
        }
        advance_or_action(0);
        if (sequence_entry(1)) {
            set_action_and_finalize(9);
            return;
        }
        if (sequence_index_13e == 0 && frame_timer_142 == 0) {
            if (frame_index_140 == 7)
                emit_823(true, true);
            if ((frame_timer_142 == 0) && frame_index_140 == 9)
                acceleration_y_100 = 0.5f;
        }
        return;
    }

    case 599: {
        if (word_730 > 0 && frame_index_140 < 7 && word_730 < 12) {
            word_734 = static_cast<short>(mt19937_next_u32() % 35U);
            float payload[3];
            payload[0] = static_cast<float>(-20 - word_734);
            payload[1] = static_cast<float>(static_cast<short>(mt19937_next_u32() % 5U + 10U));
            payload[2] = 0.0f;
            spawn_owned_object_via_manager(807,
                static_cast<float>((word_730 + 1) * facing() * 20) + x_ec,
                y_f0, facing_104, 1, payload, 3);
            payload[0] = static_cast<float>(mt19937_next_u32() % 360U);
            payload[1] = 0.0f;
            payload[2] = 1.0f;
            spawn_owned_object_via_manager(801,
                static_cast<float>((word_730 + 1) * facing() * 20) + x_ec,
                y_f0, facing_104, 1, payload, 3);
            if (word_730 == 1) {
                dispatch_character_wave_handle(0);
                adjust_counter_482(200, 120);
            }
            ++word_730;
        }
        advance_or_action(0);
        if (frame_timer_142 == 0 && frame_index_140 == 5)
            word_730 = 1;
        return;
    }

    case 600: {
        // This 600 reverses the landing/texture call order of its peers.
        resolve_stage_surface_landing_transition();
        publish_texture_state(2, 2);
        advance_spell_frame();
        if (sequence_index_13e != 0 || frame_timer_142 != 0)
            return;
        if (frame_index_140 == 4) {
            begin_spell_effect();
            emit_fighter_effect_433cc0(115, x_ec,
                static_cast<float>(y_f0 + 155.0), facing_104, 1);
            finish_spell_effect(1);
        }
        if (frame_timer_142 == 0 && frame_index_140 == 6) {
            state_180 = 1;
            dispatch_character_wave_handle(50);
            float payload[3] = {0.0f, 25.0f, 0.0f};
            spawn_owned_object_via_manager(850, static_cast<float>(facing() * 130) + x_ec,
                static_cast<float>(y_f0 + 140.0), facing_104, 1, payload, 3);
        }
        return;
    }

    case 601: {
        publish_texture_state(2, 2);
        resolve_stage_surface_landing_transition();
        if (sequence_index_13e == 0 && frame_index_140 >= 7) {
            float adjusted = static_cast<float>(velocity_x_f4 - 0.75);
            velocity_x_f4 = adjusted;
            if (frame_index_140 <= 11) {
                if (adjusted < 1.0f)
                    velocity_x_f4 = 1.0f;
            } else if (adjusted < 0.0f) {
                velocity_x_f4 = 0.0f;
            }
            if (state_180) {
                ++word_730;
                if (static_cast<signed char>(byte_184) > 0 && word_730 >= 3) {
                    word_730 = 0;
                    state_180 = 0;
                }
            }
        }
        advance_spell_frame();
        if (sequence_index_13e != 0 || frame_timer_142 != 0)
            return;
        if (frame_index_140 == 4) {
            begin_spell_effect();
            emit_fighter_effect_433cc0(115, x_ec - static_cast<float>(facing() * 40),
                static_cast<float>(y_f0 + 190.0), facing_104, 1);
            finish_spell_effect(3);
        }
        if (frame_timer_142 == 0 && frame_index_140 == 8)
            spawn_owned_object_via_manager(851, static_cast<float>(facing() * 130) + x_ec,
            static_cast<float>(y_f0 + 125.0), facing_104, 1, 0, 0);
        if (frame_timer_142 == 0 && frame_index_140 == 7) {
            velocity_x_f4 = 20.0f;
            dispatch_character_wave_handle(10);
            for (int angle = 0; angle < 360; angle += 45) {
                unsigned roll = random_roll(30);
                float payload[3];
                payload[0] = static_cast<float>(angle + 30.0 + static_cast<float>(roll));
                payload[1] = 20.0f;
                payload[2] = 2.0f;
                if (payload[0] >= 0.0f && payload[0] <= 180.0f)
                    spawn_owned_object_via_manager(815, static_cast<float>(facing() * 55) + x_ec,
                        y_f0, facing_104, 1, payload, 3);
                else
                    spawn_owned_object_via_manager(815, static_cast<float>(facing() * 55) + x_ec,
                        y_f0, facing_104, -1, payload, 3);
            }
        }
        return;
    }

    case 602: {
        publish_texture_state(2, 2);
        resolve_stage_surface_landing_transition();
        advance_spell_frame();
        if (sequence_entry(1))
            time_counter_144 = 0;
        if (sequence_index_13e == 0 && frame_timer_142 == 0) {
            if (frame_index_140 == 4) {
                begin_spell_effect();
                emit_fighter_effect_433cc0(115, static_cast<float>(facing() * 58) + x_ec,
                    static_cast<float>(y_f0 + 85.0), facing_104, 1);
                finish_spell_effect(3);
            }
            if (frame_timer_142 == 0) {
                if (frame_index_140 == 8) {
                    float payload[3] = {0.0f, 0.0f, 1.0f};
                    spawn_owned_object_via_manager(852, x_ec,
                        static_cast<float>(y_f0 + 320.0 + 1000.0),
                        facing_104, 1, payload, 3);
                }
                if (frame_timer_142 == 0 && frame_index_140 == 12) {
                    state_180 = 1;
                    float payload[3] = {0.0f, 0.0f, 2.0f};
                    spawn_owned_object_via_manager(852, x_ec, y_f0,
                        facing_104, 1, payload, 3);
                    payload[2] = 3.0f;
                    spawn_owned_object_via_manager(852, x_ec, y_f0,
                        reverse_facing(), 1, payload, 3);
                    dispatch_character_wave_handle(12);
                    field_73c = static_cast<float>(random_roll(360));
                    for (int angle = 0; angle < 360; angle += 45) {
                        payload[0] = static_cast<float>(angle + 22.5 + field_73c);
                        payload[1] = 40.0f;
                        payload[2] = 4.0f;
                        if (payload[0] >= 0.0f && payload[0] <= 180.0f)
                            spawn_owned_object_via_manager(852, x_ec, y_f0,
                                facing_104, 1, payload, 3);
                        else
                            spawn_owned_object_via_manager(852, x_ec, y_f0,
                                facing_104, -1, payload, 3);
                    }
                }
            }
        }
        if (sequence_index_13e != 1)
            return;
        if (time_counter_144 % 6 == 0) {
            float payload[3] = {0.0f, 0.0f, 5.0f};
            spawn_owned_object_via_manager(852,
                static_cast<float>(static_cast<unsigned>(selector_random_roll(400)) - 200U) + x_ec,
                static_cast<float>(static_cast<unsigned>(selector_random_roll(500))) + y_f0,
                facing_104, 1, payload, 3);
        }
        if (time_counter_144 >= 60)
            next_sequence_block();
        return;
    }

    case 603: {
        publish_texture_state(2, 2);
        resolve_stage_surface_landing_transition();
        if (sequence_index_13e == 1 && time_counter_144 >= 32) {
            next_sequence_block();
            return;
        }
        advance_spell_frame();
        if (sequence_entry(1))
            time_counter_144 = 0;
        if (sequence_index_13e != 0 || frame_timer_142 != 0)
            return;
        if (frame_index_140 == 4) {
            begin_spell_effect();
            emit_fighter_effect_433cc0(115, static_cast<float>(facing() * 60) + x_ec,
                static_cast<float>(y_f0 + 85.0), facing_104, 1);
            finish_spell_effect(3);
        }
        if (frame_timer_142 == 0 && frame_index_140 == 12) {
            dispatch_character_wave_handle(23);
            float payload[3] = {0.0f, 0.0f, 0.0f};
            spawn_owned_object_via_manager(853, x_ec,
                static_cast<float>(y_f0 + 360.0), facing_104, 1, payload, 3);
        }
        return;
    }

    case 606: {
        publish_texture_state(2, 2);
        resolve_stage_surface_landing_transition();
        advance_spell_frame();
        if (sequence_entry(1)) {
            set_action_and_finalize(0);
            return;
        }
        if (sequence_index_13e != 0 || frame_timer_142 != 0)
            return;
        if (frame_index_140 == 4) {
            begin_spell_effect();
            emit_fighter_effect_433cc0(115, x_ec,
                static_cast<float>(y_f0 + 155.0), facing_104, 1);
            finish_spell_effect(2);
        }
        if (frame_timer_142 == 0 && frame_index_140 == 7) {
            float payload[3] = {0.0f, 20.0f, 0.0f};
            spawn_owned_object_via_manager(856, static_cast<float>(facing() * 99) + x_ec,
                static_cast<float>(y_f0 + 145.0), facing_104, 1, payload, 3);
            state_180 = 1;
            dispatch_character_wave_handle(13);
        }
        return;
    }

    case 607: {
        publish_texture_state(2, 2);
        resolve_stage_surface_landing_transition();
        // These entry gates precede frame advancement in the target.
        if (sequence_index_13e == 0 && frame_timer_142 == 0) {
            if (frame_index_140 == 5) {
                begin_spell_effect();
                emit_fighter_effect_433cc0(115, static_cast<float>(facing() * 12) + x_ec,
                    static_cast<float>(y_f0 + 138.0), facing_104, 1);
                finish_spell_effect(4);
            }
            if (frame_timer_142 == 0 && frame_index_140 == 11) {
                float payload[3] = {0.0f, 0.0f, 0.0f};
                spawn_owned_object_via_manager(857, x_ec, y_f0,
                    facing_104, 1, payload, 3);
                word_7b0 = 900;
                dispatch_character_wave_handle(16);
            }
        }
        advance_spell_frame();
        return;
    }

    case 609: {
        publish_texture_state(2, 2);
        resolve_stage_surface_landing_transition();
        if (sequence_index_13e == 1 && time_counter_144 >= 20) {
            next_sequence_block();
            return;
        }
        advance_spell_frame();
        if (sequence_entry(1)) {
            float payload[3] = {0.0f, 0.0f, 1.0f};
            spawn_owned_object_via_manager(859, x_ec,
                static_cast<float>(y_f0 + 100.0), facing_104, -1, payload, 3);
            payload[2] = 2.0f;
            spawn_owned_object_via_manager(859, x_ec,
                static_cast<float>(y_f0 + 100.0), facing_104, -1, payload, 3);
            dispatch_character_wave_handle(13);
        }
        if (sequence_index_13e == 0 && frame_timer_142 == 0 && frame_index_140 == 3) {
            begin_spell_effect();
            emit_fighter_effect_433cc0(115, x_ec - static_cast<float>(facing() * 20),
                static_cast<float>(y_f0 + 180.0), facing_104, 1);
            finish_spell_effect(3);
        }
        return;
    }

    case 610: {
        publish_texture_state(2, 2);
        resolve_stage_surface_landing_transition();
        if (sequence_index_13e == 1) {
            if (time_counter_144 % 20 == 0)
                emit_object860_triplet(false);
            if (time_counter_144 % 20 == 10)
                emit_object860_triplet(true);
            if (time_counter_144 >= 120) {
                next_sequence_block();
                return;
            }
        }
        advance_spell_frame();
        if (sequence_index_13e == 0) {
            if (frame_timer_142 == 0 && frame_index_140 == 3) {
                begin_spell_effect();
                emit_fighter_effect_433cc0(115, x_ec - static_cast<float>(facing() * 20),
                    static_cast<float>(y_f0 + 180.0), facing_104, 1);
                finish_spell_effect(5);
            }
            if (frame_timer_142 == 0 && frame_index_140 == 5) {
                float payload[3];
                payload[0] = static_cast<float>(random_roll(360));
                payload[1] = 0.0f;
                payload[2] = 4.0f;
                spawn_owned_object_via_manager(860, x_ec,
                    static_cast<float>(y_f0 + 275.0), facing_104, 1, payload, 3);
            }
        }
        return;
    }

    case 650: {
        if (sequence_index_13e == 1) {
            resolve_stage_surface_landing_transition();
        } else {
            velocity_y_f8 -= acceleration_y_100;
            if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
                zero_velocity_acceleration();
                y_f0 = stage_surface_height_at_x(this);
                select_sequence(1);
                return;
            }
        }
        publish_texture_state(2, 2);
        advance_or_action(0);
        if (sequence_entry(1)) { set_action_and_finalize(9); return; }
        if (sequence_index_13e != 0 || frame_timer_142 != 0) return;
        if (frame_index_140 == 4) {
            begin_effect();
            emit_fighter_effect_433cc0(115, x_ec,
                static_cast<float>(y_f0 + 160.0), facing_104, 1);
            finish_effect(1);
        }
        if (frame_timer_142 == 0 && frame_index_140 == 6) {
            state_180 = 1;
            dispatch_character_wave_handle(50);
            float payload[3] = {0.0f, 25.0f, 0.0f};
            spawn_owned_object_via_manager(850, static_cast<float>(facing() * 130) + x_ec,
                static_cast<float>(y_f0 + 145.0), facing_104, 1, payload, 3);
        }
        if (frame_timer_142 == 0 && frame_index_140 == 9) acceleration_y_100 = 0.5f;
        return;
    }

    case 660: {
        publish_texture_state(2, 2);
        if (sequence_index_13e == 1) {
            if (time_counter_144 % 20 == 0) emit_860_triplet(false);
            if (time_counter_144 % 20 == 10) emit_860_triplet(true);
            if (time_counter_144 >= 120) { next_sequence_block(); return; }
        }
        if (advance_frame_and_dispatch()) {
            set_action_and_finalize(9);
            acceleration_y_100 = 0.5f;
            return;
        }
        if (sequence_index_13e == 0) {
            if (frame_timer_142 == 0 && frame_index_140 == 3) {
                begin_effect();
                emit_fighter_effect_433cc0(115, x_ec - static_cast<float>(facing() * 20),
                    static_cast<float>(y_f0 + 180.0), facing_104, 1);
                finish_effect(5);
            }
            if (frame_timer_142 == 0 && frame_index_140 == 5) {
                float payload[3] = {static_cast<float>(random_roll(360)), 0.0f, 4.0f};
                spawn_owned_object_via_manager(860, x_ec,
                    static_cast<float>(y_f0 + 275.0), facing_104, 1, payload, 3);
            }
        }
        return;
    }

    case 695: {
        resolve_stage_surface_landing_transition();
        advance_or_action(0);
        if (sequence_index_13e == 0 && frame_timer_142 == 0 && frame_index_140 == 9) {
            dispatch_indexed_event_member(55);
            emit_fighter_effect_433cc0(140, x_ec, static_cast<float>(y_f0 + 100.0), facing_104, 1);
            emit_fighter_effect_433cc0(140, x_ec, static_cast<float>(y_f0 + 100.0), facing_104, 1);
            emit_fighter_effect_433cc0(140, x_ec, static_cast<float>(y_f0 + 100.0), facing_104, 1);
            emit_fighter_effect_433cc0(141, x_ec, static_cast<float>(y_f0 + 100.0), facing_104, -1);
            emit_fighter_effect_433cc0(142, x_ec, y_f0, facing_104, -1);
        }
        return;
    }

    case 696: {
        resolve_stage_surface_landing_transition();
        if (velocity_x_f4 > 0.0f) {
            float adjusted = static_cast<float>(velocity_x_f4 - static_cast<double>(0.85f));
            velocity_x_f4 = adjusted;
            if (adjusted < 0.0f) velocity_x_f4 = 0.0f;
        }
        advance_or_action(0);
        if (sequence_index_13e != 0 || frame_timer_142 != 0) return;
        if (frame_index_140 == 3) velocity_x_f4 = 15.0f;
        if (frame_timer_142 == 0 && frame_index_140 == 4) dispatch_indexed_event_member(29);
        return;
    }

    case 710: {
        if (advance_frame_and_dispatch()) {
            set_action_and_finalize(700);
            face_opponent_and_flip_horizontal_velocity();
        }
        if (sequence_index_13e == 0 && frame_timer_142 == 0 && frame_index_140 == 7) {
            float payload[3] = {0.0f, 0.0f, 5.0f};
            spawn_owned_object_via_manager(900, static_cast<float>(facing() * 99) + x_ec,
                static_cast<float>(y_f0 + 145.0), facing_104, 1, payload, 3);
            dispatch_character_wave_handle(13);
        }
        return;
    }

    case 720: {
        if (advance_frame_and_dispatch()) {
            set_action_and_finalize(700);
            face_opponent_and_flip_horizontal_velocity();
        }
        if (sequence_index_13e == 1 && time_counter_144 >= 120) { next_sequence_block(); return; }
        if (sequence_entry(1)) {
            time_counter_144 = 0;
            float payload[3] = {0.0f, static_cast<float>(word_76c), 0.0f};
            spawn_owned_object_via_manager(910, x_ec, y_f0, facing_104, 1, payload, 3);
            emit_six_ring(25.0f, false, payload);
        }
        return;
    }

    case 730: {
        if (sequence_index_13e == 2 || sequence_index_13e == 3) velocity_y_f8 -= acceleration_y_100;
        if (sequence_index_13e == 5 && time_counter_144 >= 60) { next_sequence_block(); return; }
        if (sequence_index_13e == 7 || sequence_index_13e == 8) steer(false);
        if (sequence_index_13e == 9 || sequence_index_13e == 10) {
            steer(true);
            // The raw positive test excludes unordered; an inverted <= test
            // would incorrectly select sequence7 for a NaN velocity.
            if (velocity_x_f4 > 0.0f) { select_sequence(7); return; }
        }
        if (word_734 >= 360 && sequence_index_13e <= 10) {
            set_action_and_finalize(704);
            acceleration_y_100 = 0.2f;
            return;
        }
        if (advance_frame_and_dispatch()) {
            set_action_and_finalize(700);
            face_opponent_and_flip_horizontal_velocity();
        }
        if (time_counter_144 != 0) return;
        if (sequence_entry(1)) {
            velocity_y_f8 = 10.0f;
            acceleration_y_100 = 0.5f;
            velocity_x_f4 = static_cast<float>(4.0 - static_cast<float>(random_roll(8)));
        }
        if (time_counter_144 != 0) return;
        if (sequence_entry(4)) zero_velocity_acceleration();
        if (time_counter_144 != 0) return;
        if (sequence_entry(5)) {
            time_counter_144 = 0;
            float payload[3] = {0.0f, 0.0f, 1.0f};
            spawn_owned_object_via_manager(920, x_ec, static_cast<float>(y_f0 + 100.0), facing_104, -1, payload, 3);
            payload[2] = 2.0f;
            spawn_owned_object_via_manager(920, x_ec, static_cast<float>(y_f0 + 100.0), facing_104, -1, payload, 3);
            switch (g_match_identifier) {
            case 1:
                emit_920_ring(6.0f, 0.0, payload);
                break;
            case 2:
                emit_920_ring(6.0f, 0.0, payload);
                emit_920_ring(4.0f, 10.0, payload);
                break;
            case 3:
                emit_920_ring(6.0f, 0.0, payload);
                emit_920_ring(4.0f, 10.0, payload);
                emit_920_ring(2.0f, 20.0, payload);
                break;
            }
            dispatch_character_wave_handle(13);
        }
        if (sequence_entry(7)) face_opponent_and_flip_horizontal_velocity();
        return;
    }

    case 740: {
        switch (sequence_index_13e) { case 1: case 2: case 3: {
            ++word_730;
            if (word_730 >= 60) {
                select_sequence(4);
                byte_655 = 1;
                finalize_sequence_entry(-1);
                publish_texture_state(2, -1);
                copy_action_word_176_to_174();
                dispatch_indexed_event_member(23);
                zero_velocity_acceleration();
                word_4a8 = 60;
                word_4ac = 60;
                return;
            }
            word_4a8 = 2;
            word_4ac = 2;
            velocity_y_f8 -= acceleration_y_100;
        } break; }
        advance_or_action(700);
        if (time_counter_144 == 0) {
            if (sequence_entry(1)) {
                if (x_ec >= 640.0f) facing_104 = -1; else facing_104 = 1;
                float distance = static_cast<float>(640.0 - x_ec);
                velocity_x_f4 = static_cast<float>(absolute_scalar_float(distance) / 60.0);
                velocity_y_f8 = 10.0f;
                acceleration_y_100 = 0.25f;
                word_730 = 0;
            }
            if (sequence_entry(5)) {
                word_730 = 0;
                word_734 = 0;
                time_counter_144 = 0;
                break;
            }
        }
        break;
    }

    case 770: {
        advance_or_action(700);
        if (sequence_index_13e == 0 && frame_timer_142 == 0 && frame_index_140 == 10) {
            byte_655 = 1;
            finalize_sequence_entry(-1);
            publish_texture_state(2, -1);
            copy_action_word_176_to_174();
            word_76c = 0;
            word_76a = 1;
            word_766 = 0;
            word_768 = 0;
            word_764 = 0;
            dispatch_indexed_event_member(23);
        }
        return;
    }

    case 780: {
        if (sequence_index_13e <= 3) {
            ++word_736;
            // The target multiplies by the double widening of 0.95f and
            // truncates before any float store: 20 becomes18, not19.
            word_738 = static_cast<short>(word_738 * static_cast<double>(0.95f));
            if (word_736 <= 180) {
                word_732 += 2;
                y_f0 = static_cast<float>(lookup_orientation_sine_quantized_abs(
                    static_cast<float>(word_732)) * 20.0 + static_cast<float>(word_738 + 100));
            } else if (word_730 < 3) {
                word_732 += 2;
                y_f0 = static_cast<float>(lookup_orientation_sine_quantized_abs(
                    static_cast<float>(word_732)) * 20.0 + 100.0);
            } else {
                word_732 += 2;
                float adjusted = static_cast<float>(y_f0 - 1.0);
                y_f0 = adjusted;
                if (adjusted <= stage_surface_height_at_x(this)) {
                    zero_velocity_acceleration();
                    y_f0 = stage_surface_height_at_x(this);
                    set_action_and_finalize(700);
                    x_ec = 800.0f;
                }
            }
            field_73c = static_cast<float>(field_73c + 2.0);
            x_ec = static_cast<float>(lookup_orientation_cosine_quantized_abs(field_73c)
                * field_740 + 800.0);
            if (sequence_index_13e == 1) {
                double sine = lookup_orientation_sine_quantized_abs(field_73c);
                int direction = facing();
                if (direction * sine > 0.0) { next_sequence_block(); return; }
            }
            if (sequence_index_13e == 3) {
                double sine = lookup_orientation_sine_quantized_abs(field_73c);
                int direction = facing();
                if (direction * sine < 0.0) { select_sequence(0); return; }
            }
            if (word_730 > 0) {
                if (word_730 == 1) {
                    word_730 = 2;
                    float payload[3] = {0.0f, 0.0f, 0.0f};
                    spawn_owned_object_via_manager(898, 800.0f, -100.0f, facing_104, 1, payload, 3);
                    payload[2] = 1.0f;
                    spawn_owned_object_via_manager(898, 800.0f, -100.0f, facing_104, -1, payload, 3);
                    payload[2] = 2.0f;
                    spawn_owned_object_via_manager(898, 800.0f, -100.0f, facing_104, 1, payload, 3);
                    dispatch_character_wave_handle(23);
                }
                if (byte_112 < 240) {
                    byte_112 += 15;
                    byte_111 += 15;
                    byte_110 += 15;
                } else {
                    byte_112 = 255;
                    byte_111 = 255;
                    byte_110 = 255;
                }
                if (word_730 == 3) {
                    float adjusted = static_cast<float>(field_740 - 2.0);
                    field_740 = adjusted;
                    if (adjusted < 0.0f) field_740 = 0.0f;
                }
            }
        }
        advance_or_action(700);
        return;
    }

    case 781: {
        ++word_7b2;
        if (word_7b2 > 255) word_7b2 = 255;
        switch (sequence_index_13e) { case 0: {
            if (time_counter_144 % 15 == 0) {
                float payload[3] = {0.0f, 0.0f, static_cast<float>(static_cast<float>(static_cast<unsigned>(selector_random_roll(2))) + 1.0)};
                spawn_owned_object_via_manager(995,
                    static_cast<float>(static_cast<unsigned>(selector_random_roll(640))),
                    -200.0f,
                    static_cast<signed char>(1 - 2 * (static_cast<unsigned>(selector_random_roll(100)) < 50)),
                    1, payload, 3);
                advance_frame_and_dispatch();
                return;
            }
        } break; case 1: {
            word_78c = 1;
            set_shared_first_target(1, 640.0f);
            set_shared_second_target(1, 0.0f);
            set_shared_third_target(1, 1.0f);
            if (word_732 == 0) {
                double step_y = field_73c; field_740 = static_cast<float>(step_y + field_740);
                field_73c = static_cast<float>(field_73c - 0.5);
                field_7b4 = field_740;
                if (field_740 <= 0.0f) {
                    field_740 = 0.0f;
                    word_732 = 1;
                    field_7b4 = 0.0f;
                }
            }
            reinterpret_cast<IkuEventPairView *>(reinterpret_cast<unsigned char *>(this) + 0x130)
            ->set_global_pair(0.0f, field_7b4);
            if (word_732 == 1) { set_action_and_finalize(700); return; }
        } break; }
        break;
    }

    case 795: {
        if (sequence_index_13e == 0) {
            velocity_y_f8 = static_cast<float>(velocity_y_f8 - static_cast<double>(0.3f));
            if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
                select_sequence(1);
                { restore_surface_motion(); return; }
            }
        }
        advance_or_action(700);
        return;
    }

    case 797: {
        {
            if (sequence_index_13e == 0 || sequence_index_13e == 1) {
                if (velocity_y_f8 > 0.0f) {
                    select_sequence(2);
                    emit_six_ring(15.0f, true);
                    return;
                }
                velocity_y_f8 -= acceleration_y_100;
            }
            if (sequence_index_13e == 2 || sequence_index_13e == 3) {
                velocity_x_f4 = static_cast<float>(velocity_x_f4 * static_cast<double>(0.93f));
                if (velocity_x_f4 < 2.0f) {
                    ++word_730;
                    if (word_730 >= 20) { select_sequence(4); return; }
                }
                acceleration_y_100 = static_cast<float>(acceleration_y_100 * static_cast<double>(0.95f));
                velocity_y_f8 -= acceleration_y_100;
            }
            if (sequence_index_13e == 4 || sequence_index_13e == 5) {
                velocity_y_f8 = static_cast<float>(velocity_y_f8 - static_cast<double>(0.15f));
                velocity_x_f4 = static_cast<float>(velocity_x_f4 - static_cast<double>(0.1f));
                if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
                    set_action_and_finalize(10);
                    x_ec = 480.0f;
                    { restore_surface_motion(); return; }
                }
            }
            advance_frame_and_dispatch();
            return;
        }
    }

    case 798: {
        {
            if (sequence_index_13e == 0 || sequence_index_13e == 1) {
                if (velocity_y_f8 > 0.0f) {
                    select_sequence(2);
                    emit_six_ring(15.0f, true);
                    return;
                }
                velocity_y_f8 -= acceleration_y_100;
            }
            if (sequence_index_13e == 2 || sequence_index_13e == 3) {
                velocity_x_f4 = static_cast<float>(velocity_x_f4 * static_cast<double>(0.93f));
                if (velocity_x_f4 < 2.0f) {
                    ++word_730;
                    if (word_730 >= 20) { select_sequence(4); return; }
                }
                acceleration_y_100 = static_cast<float>(acceleration_y_100 * static_cast<double>(0.95f));
                velocity_y_f8 -= acceleration_y_100;
            }
            if (sequence_index_13e == 4 || sequence_index_13e == 5) {
                velocity_y_f8 = static_cast<float>(velocity_y_f8 - static_cast<double>(0.15f));
                velocity_x_f4 = static_cast<float>(velocity_x_f4 - static_cast<double>(0.1f));
                if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
                    set_action_and_finalize(709);
                    x_ec = 800.0f;
                    { restore_surface_motion(); return; }
                }
            }
            advance_frame_and_dispatch();
            return;
        }
    }

    default:
        update_common_action_state();
        return;
    }
    advance_frame_and_dispatch();
}

typedef char Iku_off_ec[(offsetof(IkuActionStateView, x_ec) == 0xec) ? 1 : -1];
typedef char Iku_off_104[(offsetof(IkuActionStateView, facing_104) == 0x104) ? 1 : -1];
typedef char Iku_off_110[(offsetof(IkuActionStateView, byte_110) == 0x110) ? 1 : -1];
typedef char Iku_off_13c[(offsetof(IkuActionStateView, action_id_13c) == 0x13c) ? 1 : -1];
typedef char Iku_off_170[(offsetof(IkuActionStateView, related_170) == 0x170) ? 1 : -1];
typedef char Iku_off_186[(offsetof(IkuActionStateView, word_186) == 0x186) ? 1 : -1];
typedef char Iku_off_47e[(offsetof(IkuActionStateView, byte_47e) == 0x47e) ? 1 : -1];
typedef char Iku_off_482[(offsetof(IkuActionStateView, word_482) == 0x482) ? 1 : -1];
typedef char Iku_off_48a[(offsetof(IkuActionStateView, word_48a) == 0x48a) ? 1 : -1];
typedef char Iku_off_4a8[(offsetof(IkuActionStateView, word_4a8) == 0x4a8) ? 1 : -1];
typedef char Iku_off_4b8[(offsetof(IkuActionStateView, field_4b8) == 0x4b8) ? 1 : -1];
typedef char Iku_off_606[(offsetof(IkuActionStateView, byte_606) == 0x606) ? 1 : -1];
typedef char Iku_off_655[(offsetof(IkuActionStateView, byte_655) == 0x655) ? 1 : -1];
typedef char Iku_off_6b4[(offsetof(IkuActionStateView, field_6b4) == 0x6b4) ? 1 : -1];
typedef char Iku_off_72c[(offsetof(IkuActionStateView, byte_72c) == 0x72c) ? 1 : -1];
typedef char Iku_off_730[(offsetof(IkuActionStateView, word_730) == 0x730) ? 1 : -1];
typedef char Iku_off_73c[(offsetof(IkuActionStateView, field_73c) == 0x73c) ? 1 : -1];
typedef char Iku_off_750[(offsetof(IkuActionStateView, byte_750) == 0x750) ? 1 : -1];
typedef char Iku_off_764[(offsetof(IkuActionStateView, word_764) == 0x764) ? 1 : -1];
typedef char Iku_off_78c[(offsetof(IkuActionStateView, word_78c) == 0x78c) ? 1 : -1];
typedef char Iku_off_7a0[(offsetof(IkuActionStateView, word_7a0) == 0x7a0) ? 1 : -1];
typedef char Iku_off_7b0[(offsetof(IkuActionStateView, word_7b0) == 0x7b0) ? 1 : -1];
typedef char Iku_off_7b4[(offsetof(IkuActionStateView, field_7b4) == 0x7b4) ? 1 : -1];
typedef char IkuPeer_off[(offsetof(IkuPeerView, word_174) == 0x174 && offsetof(IkuPeerView, word_48c) == 0x48c) ? 1 : -1];

} // namespace th105
