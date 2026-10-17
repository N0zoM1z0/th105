// Mid-table disappearance, movement and fan trajectories; no callable boundary.
    case 540: case 541: case 545: case 546: {
        const bool fan = selected_action == 545 || selected_action == 546;
        if ((selected_action == 540 && sequence_13e == 4)
                || (selected_action == 541 && sequence_13e >= 3 && sequence_13e <= 5)
                || (fan && sequence_13e == 6))
            resolve_stage_surface_landing_transition();
        byte_17c = fan ? 6 : 2;
        if (sequence_13e == 0) {
            if (frame_timer_142 == 0 && frame_index_140 == 4) {
                field_108 = 0.0f;
                field_10c = 100.0f;
                scale_11c = 1.0f;
                scale_120 = 1.0f;
                byte_113 = 255;
                byte_112 = 255;
                byte_111 = 255;
                byte_110 = 255;
                dispatch_character_wave_handle(6);
            }
            if (frame_index_140 > 3) {
                if (scale_11c > 0.0f) {
                    scale_11c = static_cast<float>(scale_11c - static_cast<double>(0.1f));
                    scale_120 = static_cast<float>(scale_120 + static_cast<double>(0.2f));
                }
                if (byte_113 > 25)
                    byte_113 = static_cast<unsigned char>(byte_113 - 25);
            }
        }
        if (sequence_13e == 2) {
            if (selected_action == 541)
                velocity_y_f8 = static_cast<float>(velocity_y_f8 - 1.0);
            if (selected_action == 541 || frame_index_140 < 5) {
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
            if (selected_action == 540 && frame_index_140 < 7)
                velocity_y_f8 = static_cast<float>(velocity_y_f8 - static_cast<double>(0.7f));
            if (selected_action == 541
                    && static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
                scale_11c = 1.0f;
                scale_120 = 1.0f;
                byte_113 = 255;
                y_f0 = reimu_stage_surface_height_at_x(this);
                velocity_y_f8 = 0.0f;
                set_sequence(3);
            }
        }
        if (selected_action == 540 && sequence_13e == 3
                && static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
            y_f0 = reimu_stage_surface_height_at_x(this);
            zero_velocity_acceleration();
            next_sequence_block();
            return true;
        }
        if (selected_action == 541) {
            if (sequence_13e == 3) {
                if (state_180 != 0) {
                    word_734 = static_cast<short>(word_734 + 1);
                    if (word_734 > 5) {
                        state_180 = 0;
                        word_734 = 0;
                    }
                }
                if (frame_counter_144 > 15) {
                    next_sequence_block();
                    byte_184 = 1;
                }
            }
            if (sequence_13e == 4 && state_180 != 0) {
                word_734 = static_cast<short>(word_734 + 1);
                if (word_734 > 5) {
                    state_180 = 0;
                    word_734 = 0;
                }
            }
            if (sequence_13e > 3) {
                velocity_x_f4 = static_cast<float>(velocity_x_f4 - static_cast<double>(0.8f));
                if (velocity_x_f4 < 0.0f)
                    velocity_x_f4 = 0.0f;
            }
        }
        if (fan) {
            if (sequence_13e >= 2 && sequence_13e <= 5) {
                velocity_y_f8 -= acceleration_y_100;
                if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
                    y_f0 = reimu_stage_surface_height_at_x(this);
                    zero_velocity_acceleration();
                    set_sequence(6);
                    return true;
                }
            }
            if (sequence_13e == 3 && frame_counter_144 >= 8) {
                next_sequence_block();
                return true;
            }
        }
        if (advance_frame_and_dispatch())
            set_action(0);
        if (selected_action == 540) {
            if (frame_counter_144 == 0 && frame_timer_142 == 0
                    && frame_index_140 == 0 && sequence_13e == 2) {
                adjust_counter_482(200, 120);
                x_ec = static_cast<float>(peer_170->x_ec - facing_104 * 180);
                y_f0 = 200.0f;
                velocity_x_f4 = 6.0f;
                velocity_y_f8 = 8.0f;
                dispatch_character_wave_handle(6);
            }
            if (sequence_13e == 2 && frame_index_140 == 7 && frame_timer_142 == 0) {
                velocity_x_f4 = 7.5f;
                velocity_y_f8 = -24.0f;
                add_scaled_counter(50);
            }
        } else if (selected_action == 541) {
            if (frame_counter_144 == 0 && frame_timer_142 == 0
                    && frame_index_140 == 0 && sequence_13e == 1) {
                adjust_counter_482(200, 120);
                x_ec = static_cast<float>(facing_104 * 100 + x_ec);
                y_f0 = 50.0f;
                velocity_x_f4 = 15.0f;
                velocity_y_f8 = 6.0f;
                dispatch_character_wave_handle(6);
                add_scaled_counter(50);
            }
        } else {
            if (frame_counter_144 == 0 && frame_timer_142 == 0
                    && frame_index_140 == 0 && sequence_13e == 2) {
                adjust_counter_482(200, 120);
                if (selected_action == 546)
                    x_ec = static_cast<float>(x_ec - facing_104 * 320);
                y_f0 = static_cast<float>(y_f0 + 100.0);
                if (y_f0 > 350.0f)
                    y_f0 = 350.0f;
                velocity_x_f4 = selected_action == 546 ? -5.0f : 5.0f;
                velocity_y_f8 = 15.0f;
                acceleration_y_100 = 0.5f;
                dispatch_character_wave_handle(6);
                const float parameters[3] = {0.0f, 0.0f, 3.0f};
                spawn_owned_object_via_manager(821, x_ec, static_cast<float>(y_f0 + 100.0),
                    static_cast<unsigned char>(facing_104), -1, parameters, 3);
            }
            if (frame_counter_144 == 0 && frame_timer_142 == 0
                    && frame_index_140 == 0 && sequence_13e == 3) {
                dispatch_character_wave_handle(14);
                add_scaled_counter(50);
                for (int i = 0; i <= 5; ++i) {
                    if (byte_60a >= 4 && i <= 4) {
                        float parameters[3] = {
                            static_cast<float>(selected_action == 546 ? 35.5 - i * 9.0 : i * 9.0 + 34.5),
                            22.0f, 0.0f};
                        const float y = static_cast<float>(lookup_orientation_sine_quantized_abs(-parameters[0])
                            * 50.0 + y_f0 + 100.0);
                        const float x = static_cast<float>(lookup_orientation_cosine_quantized_abs(-parameters[0])
                            * (facing_104 * 50) + x_ec);
                        spawn_owned_object_via_manager(821, x, y,
                            static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    }
                    float parameters[3] = {
                        static_cast<float>(selected_action == 546 ? 40.0 - i * 9.0 : i * 9.0 + 30.0),
                        25.0f, 0.0f};
                    const float y = static_cast<float>(lookup_orientation_sine_quantized_abs(-parameters[0])
                        * 50.0 + y_f0 + 100.0);
                    const float x = static_cast<float>(lookup_orientation_cosine_quantized_abs(-parameters[0])
                        * (facing_104 * 50) + x_ec);
                    spawn_owned_object_via_manager(821, x, y,
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                }
                const float parameters[3] = {0.0f, 0.0f, 4.0f};
                spawn_owned_object_via_manager(821, x_ec, static_cast<float>(y_f0 + 100.0),
                    static_cast<unsigned char>(facing_104), 1, parameters, 3);
                state_180 = 1;
            }
            if (frame_counter_144 == 0 && frame_timer_142 == 0
                    && frame_index_140 == 0 && sequence_13e == 5)
                set_action(9);
        }
        return true;
    }
