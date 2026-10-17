// Middle high-table families; no separate callable boundary.
    case 608:
        if ((sequence_13e == 0 && frame_index_140 <= 3) || sequence_13e == 3)
            resolve_stage_surface_landing_transition();
        publish_texture_state(6, 2);
        if (sequence_13e == 1 && frame_counter_144 > 20) {
            next_sequence_block();
            return true;
        }
        if (sequence_13e < 3) {
            velocity_y_f8 -= acceleration_y_100;
            if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
                y_f0 = reimu_stage_surface_height_at_x(this);
                zero_velocity_acceleration();
                set_sequence(3);
                return true;
            }
        }
        if (advance_frame_and_dispatch()) {
            set_action(0);
            publish_texture_state(6, 60);
        }
        if (sequence_13e == 0 && frame_timer_142 == 0) {
            if (frame_index_140 == 4) {
                dispatch_indexed_sequence_window_45c8b0(0, 1, 60);
                advance_secondary_event_effect_cycle();
                set_word_48a(40);
                dispatch_indexed_event_member(23);
                emit_fighter_effect(115, static_cast<float>(static_cast<float>(facing_104 * 24) + x_ec),
                    static_cast<float>(y_f0 + 144.0), static_cast<unsigned char>(facing_104), 1);
            }
            if (frame_timer_142 == 0 && frame_index_140 == 5) {
                velocity_x_f4 = -2.0f;
                velocity_y_f8 = 7.5f;
                acceleration_y_100 = 0.3f;
            }
            if (frame_timer_142 == 0 && frame_index_140 == 10)
                word_730 = 1;
        }
        if (frame_counter_144 == 0 && frame_timer_142 == 0 && frame_index_140 == 0 && sequence_13e == 3)
            set_action(9);
        if (word_730 > 0) {
            word_732 = static_cast<short>(word_732 - 1);
            if (word_732 <= 0 && word_734 < 3) {
                float parameters[3] = {static_cast<float>(word_734 * 10.0 - 80.0), 0.0f, 0.0f};
                spawn_owned_object_via_manager(858,
                    static_cast<float>(static_cast<float>(facing_104 * 78) + x_ec),
                    static_cast<float>(y_f0 + 120.0),
                    static_cast<unsigned char>(facing_104), 1, parameters, 3);
                parameters[0] = 0.0f;
                parameters[1] = 0.0f;
                parameters[2] = 2.0f;
                spawn_owned_object_via_manager(858,
                    static_cast<float>(static_cast<float>(facing_104 * 78) + x_ec),
                    static_cast<float>(y_f0 + 120.0),
                    static_cast<unsigned char>(facing_104), 1, parameters, 3);
                dispatch_character_wave_handle(11);
                word_732 = 6;
                word_734 = static_cast<short>(word_734 + 1);
            }
        }
        return true;
    case 609:
        resolve_stage_surface_landing_transition();
        publish_texture_state(6, 2);
        if ((sequence_13e == 1 && (frame_counter_144 > 40 || word_738 == 1))
                || (sequence_13e == 2 && frame_counter_144 > 24)) {
            next_sequence_block();
            return true;
        }
        if (advance_frame_and_dispatch())
            set_action(0);
        if (sequence_13e == 0 && frame_timer_142 == 0 && frame_index_140 == 5) {
            const float parameters[3] = {0.0f, 0.0f, 0.0f};
            spawn_owned_object_via_manager(852,
                static_cast<float>(static_cast<float>(facing_104 * 228) + x_ec),
                static_cast<float>(y_f0 + 93.0),
                static_cast<unsigned char>(facing_104), 1, parameters, 3);
            dispatch_character_wave_handle(12);
        }
        return true;
    case 610:
        resolve_stage_surface_landing_transition();
        publish_texture_state(6, 2);
        if (sequence_13e == 1 && frame_counter_144 > 60) {
            next_sequence_block();
            return true;
        }
        if (advance_frame_and_dispatch()) {
            set_action(0);
            publish_texture_state(6, 120);
        }
        if (sequence_13e == 0 && frame_timer_142 == 0 && frame_index_140 == 7) {
            spawn_owned_object_via_manager(859,
                static_cast<float>(static_cast<float>(facing_104 * 280) + x_ec),
                static_cast<float>(y_f0 + 93.0),
                static_cast<unsigned char>(facing_104), 1, 0, 0);
            dispatch_character_wave_handle(13);
        }
        return true;
    case 612: {
        if (sequence_13e == 0) {
            if (frame_timer_142 == 0 && frame_index_140 == 1) {
                field_108 = 0.0f;
                field_10c = 50.0f;
                scale_11c = 1.0f;
                scale_120 = 1.0f;
                byte_113 = 255;
                byte_112 = 255;
                byte_111 = 255;
                byte_110 = 255;
                dispatch_character_wave_handle(2);
            }
            if (frame_index_140 > 0) {
                if (scale_11c > 0.0f) {
                    scale_11c = static_cast<float>(scale_11c - static_cast<double>(0.1f));
                    scale_120 = static_cast<float>(scale_120 + static_cast<double>(0.2f));
                }
                byte_113 = byte_113 > 25 ? static_cast<unsigned char>(byte_113 - 25) : 0;
            }
        }
        if (sequence_13e == 2) {
            if (frame_index_140 == 0) {
                if (scale_11c < 1.0f) {
                    scale_11c = static_cast<float>(scale_11c + static_cast<double>(0.1f));
                    scale_120 = static_cast<float>(scale_120 - static_cast<double>(0.2f));
                    byte_113 = static_cast<unsigned char>(byte_113 + 25);
                } else {
                    scale_11c = 1.0f;
                    scale_120 = 1.0f;
                    byte_113 = 255;
                }
            }
            if (frame_index_140 < 3)
                velocity_y_f8 = static_cast<float>(velocity_y_f8 - static_cast<double>(0.7f));
        }
        if (sequence_13e == 3) {
            if (state_180 != 0 && static_cast<signed char>(byte_184) > 0)
                state_180 = 0;
            const double next_y = static_cast<double>(velocity_y_f8) + y_f0;
            if (reimu_stage_surface_height_at_x(this) >= next_y && velocity_y_f8 < 0.0f) {
                y_f0 = reimu_stage_surface_height_at_x(this);
                zero_velocity_acceleration();
                next_sequence_block();
                return true;
            }
        }
        if (advance_frame_and_dispatch())
            set_action(0);
        if (sequence_13e == 0 && frame_timer_142 == 0 && frame_index_140 == 3) {
            dispatch_indexed_sequence_window_45c8b0(0, 2, 60);
            advance_secondary_event_effect_cycle();
            set_word_48a(40);
            dispatch_indexed_event_member(23);
        }
        if (frame_counter_144 == 0 && frame_timer_142 == 0 && frame_index_140 == 0 && sequence_13e == 2) {
            x_ec = static_cast<float>(peer_170->x_ec - facing_104 * 180);
            y_f0 = 150.0f;
            velocity_x_f4 = 6.0f;
            velocity_y_f8 = 8.0f;
            dispatch_character_wave_handle(6);
        }
        if (sequence_13e == 2 && frame_index_140 == 3 && frame_timer_142 == 0) {
            velocity_x_f4 = 7.5f;
            velocity_y_f8 = -24.0f;
        }
        return true;
    }
    case 614:
        if (sequence_13e == 0 || sequence_13e == 3 || sequence_13e == 4 || sequence_13e == 7)
            resolve_stage_surface_landing_transition();
        publish_texture_state(6, 2);
        velocity_y_f8 -= acceleration_y_100;
        if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
            if (sequence_13e < 3) {
                zero_velocity_acceleration();
                y_f0 = reimu_stage_surface_height_at_x(this);
                set_sequence(3);
                return true;
            }
            if (sequence_13e > 3 && sequence_13e < 7) {
                zero_velocity_acceleration();
                y_f0 = reimu_stage_surface_height_at_x(this);
                set_sequence(7);
                return true;
            }
        }
        if (advance_frame_and_dispatch())
            set_action(0);
        if (sequence_13e == 0 && frame_timer_142 == 0) {
            if (frame_index_140 == 1) {
                dispatch_indexed_sequence_window_45c8b0(0, 3, 60);
                advance_secondary_event_effect_cycle();
                set_word_48a(40);
                dispatch_indexed_event_member(23);
                emit_fighter_effect(115, static_cast<float>(static_cast<float>(facing_104 * 24) + x_ec),
                    static_cast<float>(y_f0 + 144.0), static_cast<unsigned char>(facing_104), 1);
            }
            if (frame_timer_142 == 0 && frame_index_140 == 3) {
                const float parameters[3] = {0.0f, 12.0f, 0.0f};
                spawn_owned_object_via_manager(825, x_ec, y_f0,
                    static_cast<unsigned char>(facing_104), 1, parameters, 3);
                dispatch_character_wave_handle(7);
            }
        }
        if (frame_counter_144 == 0 && frame_timer_142 == 0 && frame_index_140 == 0 && sequence_13e == 1) {
            state_180 = 0;
            byte_184 = 1;
            velocity_x_f4 = 6.0f;
            velocity_y_f8 = 10.0f;
            acceleration_y_100 = 1.25f;
        }
        if (frame_counter_144 == 0 && frame_timer_142 == 0 && frame_index_140 == 0
                && sequence_13e == 4 && word_730 < 2) {
            word_730 = static_cast<short>(word_730 + 1);
            set_sequence(0);
            frame_timer_142 = 0;
            frame_index_140 = 3;
            const float parameters[3] = {0.0f, 12.0f, 0.0f};
            spawn_owned_object_via_manager(825, x_ec, y_f0,
                static_cast<unsigned char>(facing_104), 1, parameters, 3);
            dispatch_character_wave_handle(7);
        }
        if (sequence_13e == 4 && frame_timer_142 == 0 && frame_index_140 == 2) {
            const float parameters[3] = {0.0f, 12.0f, 0.0f};
            spawn_owned_object_via_manager(825, x_ec, y_f0,
                static_cast<unsigned char>(facing_104), 1, parameters, 3);
            dispatch_character_wave_handle(7);
        }
        if (frame_counter_144 == 0 && frame_timer_142 == 0 && frame_index_140 == 0 && sequence_13e == 5) {
            state_180 = 0;
            byte_184 = 1;
            velocity_x_f4 = 6.0f;
            velocity_y_f8 = 16.0f;
            acceleration_y_100 = 0.5f;
        }
        if (sequence_13e == 5 && frame_timer_142 == 0) {
            if (frame_index_140 == 5) {
                byte_184 = 1;
                state_180 = 0;
                const float parameters[3] = {-75.0f, 12.0f, 1.0f};
                spawn_owned_object_via_manager(825,
                    static_cast<float>(static_cast<float>(facing_104 * 85) + x_ec),
                    static_cast<float>(y_f0 + 117.0),
                    static_cast<unsigned char>(facing_104), 1, parameters, 3);
                dispatch_character_wave_handle(10);
            }
            if (frame_timer_142 == 0 && frame_index_140 == 6) {
                acceleration_y_100 = 0.1f;
                velocity_x_f4 = static_cast<float>(velocity_x_f4 * 0.5);
                velocity_y_f8 = static_cast<float>(velocity_y_f8 * 0.5);
            }
            if (frame_timer_142 == 0 && frame_index_140 == 8)
                acceleration_y_100 = 0.5f;
        }
        return true;
    case 616:
        if (sequence_13e == 8)
            resolve_stage_surface_landing_transition();
        publish_texture_state(6, 2);
        switch (sequence_13e) {
        case 1: case 2: {
            velocity_y_f8 -= acceleration_y_100;
            const double next_y = static_cast<double>(velocity_y_f8) + y_f0;
            if (reimu_stage_surface_height_at_x(this) + 300.0 >= next_y && velocity_y_f8 < 0.0f) {
                zero_velocity_acceleration();
                set_sequence(3);
                y_f0 = static_cast<float>(reimu_stage_surface_height_at_x(this) + 280.0);
                float parameters[3];
                parameters[2] = 2.0f;
                for (float i = 0.0f; i < 8.0f; i += 1.0f) {
                    parameters[0] = static_cast<float>(i * 45.0);
                    parameters[1] = 30.0f;
                    spawn_owned_object_via_manager(866, x_ec, reimu_stage_surface_height_at_x(this),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                }
                return true;
            }
            break;
        }
        case 3:
            y_f0 = static_cast<float>(reimu_stage_surface_height_at_x(this) + 280.0 + field_73c);
            field_73c = static_cast<float>(field_73c + 2.0);
            if (field_73c > 20.0f)
                field_73c = 20.0f;
            break;
        case 4: case 5:
            velocity_x_f4 = static_cast<float>(velocity_x_f4 + static_cast<double>(0.2f));
            if (velocity_x_f4 > 8.0f)
                velocity_x_f4 = 8.0f;
            if (reimu_stage_surface_height_at_x(this) + 300.0 < y_f0) {
                velocity_y_f8 = static_cast<float>(velocity_y_f8 - static_cast<double>(0.2f));
                const double next_y = static_cast<double>(velocity_y_f8) + y_f0;
                if (reimu_stage_surface_height_at_x(this) + 300.0 >= next_y) {
                    y_f0 = static_cast<float>(reimu_stage_surface_height_at_x(this) + 300.0);
                    velocity_y_f8 = 0.0f;
                }
            }
            if (sequence_13e == 5 && frame_counter_144 >= 120) {
                next_sequence_block();
                velocity_y_f8 = 4.5f;
                velocity_x_f4 = -4.0f;
                acceleration_y_100 = 0.5f;
            }
            break;
        case 6: case 7:
            velocity_y_f8 -= acceleration_y_100;
            if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
                zero_velocity_acceleration();
                y_f0 = reimu_stage_surface_height_at_x(this);
                set_sequence(8);
            }
            break;
        }
        if (advance_frame_and_dispatch()) {
            set_action(0);
            return true;
        }
        if (frame_counter_144 == 0 && frame_timer_142 == 0 && frame_index_140 == 0 && sequence_13e == 1) {
            velocity_x_f4 = 0.0f;
            velocity_y_f8 = 25.0f;
            acceleration_y_100 = 0.7f;
            const float parameters[3] = {0.0f, 0.0f, 0.0f};
            spawn_owned_object_via_manager(866, x_ec,
                static_cast<float>(reimu_stage_surface_height_at_x(this) + 150.0),
                static_cast<unsigned char>(facing_104), -1, parameters, 3);
            dispatch_indexed_sequence_window_45c8b0(0, 3, 60);
            advance_secondary_event_effect_cycle();
            set_word_48a(120);
            dispatch_indexed_event_member(23);
            emit_fighter_effect(115, static_cast<float>(static_cast<float>(facing_104 * 24) + x_ec),
                static_cast<float>(y_f0 + 144.0), static_cast<unsigned char>(facing_104), 1);
        }
        if (sequence_13e == 3 && frame_timer_142 == 0 && frame_index_140 == 5)
            set_word_48a(1);
        return true;
    case 619:
        resolve_stage_surface_landing_transition();
        publish_texture_state(6, 2);
        if (sequence_13e == 1 && frame_counter_144 >= 20) {
            next_sequence_block();
            return true;
        }
        if (advance_frame_and_dispatch()) {
            set_action(0);
            return true;
        }
        if (sequence_13e == 0 && frame_timer_142 == 0) {
            if (frame_index_140 == 3) {
                dispatch_indexed_sequence_window_45c8b0(0, 5, 60);
                advance_secondary_event_effect_cycle();
                set_word_48a(40);
                dispatch_indexed_event_member(23);
                emit_fighter_effect(115, x_ec, static_cast<float>(y_f0 + 120.0),
                    static_cast<unsigned char>(facing_104), 1);
            }
            if (frame_timer_142 == 0 && frame_index_140 == 5) {
                dispatch_character_wave_handle(22);
                for (float i = 0.0f; i < 7.0f; i += 1.0f) {
                    const float parameters[4] = {
                        static_cast<float>(static_cast<double>(51.4f) * i), 0.0f, 0.0f, i};
                    const int arg5 = lookup_orientation_sine_quantized_abs(parameters[0]) > 0.0f ? -1 : 1;
                    spawn_owned_object_via_manager(869, x_ec,
                        static_cast<float>(reimu_stage_surface_height_at_x(this) + 150.0),
                        static_cast<unsigned char>(facing_104), arg5, parameters, 4);
                }
                timer_7c8 = 900;
                count_7ca = 0;
                latch_7cc = 0;
            }
        }
        return true;
