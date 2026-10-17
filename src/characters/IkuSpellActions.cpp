#include "AnimationSequenceVirtuals.hpp"

namespace th105 {

int __cdecl selector_random_roll(int limit);

// Complete semantic staging for actions600/601/602/603/606/607/609/610 in
// 620920. This helper is not the target root or an original compiler boundary;
// the remaining root actions must be recovered before source/unit selection.
class IkuSpellActionView : public AnimationSequenceObjectView {
public:
    unsigned char resolve_stage_surface_landing_transition();
    unsigned char advance_frame_and_dispatch();
    void publish_texture_state(signed char texture_index, short duration);
    void dispatch_indexed_event_member(unsigned event_code);
    void dispatch_indexed_sequence_window_45c8b0(signed char index, int outcome, int token);
    void advance_secondary_event_effect_cycle();
    void emit_fighter_effect_433cc0(int effect, float x, float y, int facing, int trailing);
    int spawn_owned_object_via_manager(
        int object_id, float x, float y, int facing, int variant,
        const void *payload, int payload_count);

    bool try_dispatch_verified_spell_action();

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
    int facing() {
        return static_cast<signed char>(byte_at(0x104));
    }
    unsigned char reverse_facing() {
        return static_cast<unsigned char>(-facing());
    }
    unsigned random_roll(int limit) {
        // Keep the accepted int-return interface and the caller's unsigned
        // interpretation. The selector can produce its inclusive endpoint.
        return static_cast<unsigned>(selector_random_roll(limit));
    }
    bool sequence_entry(short sequence) {
        return time_counter_144 == 0 && frame_timer_142 == 0
            && frame_index_140 == 0 && sequence_index_13e == sequence;
    }
    void advance_spell_frame() {
        if (advance_frame_and_dispatch())
            set_action_and_finalize(0);
    }
    void begin_spell_effect() {
        short_at(0x48a) = 40;
        dispatch_indexed_event_member(23);
    }
    void finish_spell_effect(int outcome) {
        dispatch_indexed_sequence_window_45c8b0(0, outcome, 60);
        advance_secondary_event_effect_cycle();
    }
    void emit_object860_triplet(bool reverse_first) {
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
};

bool IkuSpellActionView::try_dispatch_verified_spell_action()
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

} // namespace th105
