// Twelve physical500-family bodies and their shared charge/landing exits.
    case 500: case 501: case 502: case 503:
    case 505: case 506: case 507: case 508:
    case 510: case 511: case 512: case 513: {
        const bool aerial = selected_action == 502 || selected_action == 503
            || selected_action == 507 || selected_action == 508
            || selected_action == 512 || selected_action == 513;
        const bool wide = selected_action >= 510;
        const bool alternate = selected_action >= 505;
        const bool second_input = selected_action == 501 || selected_action == 503
            || selected_action == 506 || selected_action == 508
            || selected_action == 511 || selected_action == 513;
        if (!aerial || sequence_13e == 5)
            resolve_stage_surface_landing_transition();
        byte_17c = wide ? 8 : alternate ? 4 : 0;
        if (sequence_13e <= 1 && (second_input ? field_6c4 : field_6c0) == 0)
            byte_750 = 0;
        if (aerial && sequence_13e < 5) {
            if (sequence_13e == 4) {
                acceleration_y_100 = 0.6f;
                velocity_y_f8 = static_cast<float>(velocity_y_f8 - static_cast<double>(0.6f));
            }
            if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
                zero_velocity_acceleration();
                y_f0 = reimu_stage_surface_height_at_x(this);
                set_sequence(5);
                return true;
            }
        }
        if (sequence_13e == 2 && frame_timer_142 == 0
                && frame_index_140 == (aerial ? 1 : 2)) {
            adjust_counter_482(200, 120);
            state_180 = 1;
            add_scaled_counter(50);
            dispatch_character_wave_handle(wide ? 20 : 4);
            const int x_offset = aerial ? 50 : 114;
            const double y_offset = aerial ? 108.0 : 96.0;
            if (wide) {
                if (word_736 == 0) {
                    float parameters[3] = {30.0f, 15.0f, 0.0f};
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = 0.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -30.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                }
                if (word_736 == 1) {
                    float parameters[3] = {45.0f, 15.0f, 0.0f};
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = 15.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -15.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -45.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                }
                if (word_736 == 2) {
                    float parameters[3] = {60.0f, 15.0f, 0.0f};
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = 30.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = 0.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -30.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -60.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                }
            } else if (!alternate) {
                if (word_736 == 0) {
                    float parameters[3] = {20.0f, 15.0f, 0.0f};
                    spawn_owned_object_via_manager(810,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -20.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(810,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                }
                if (word_736 == 1) {
                    for (int angle = 20; angle < 60; angle += 20) {
                        float parameters[3] = {static_cast<float>(angle), 15.0f, 0.0f};
                        spawn_owned_object_via_manager(810,
                            static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                            static_cast<float>(y_f0 + y_offset),
                            static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    }
                    for (int angle = -20; angle > -60; angle -= 20) {
                        float parameters[3] = {static_cast<float>(angle), 15.0f, 0.0f};
                        spawn_owned_object_via_manager(810,
                            static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                            static_cast<float>(y_f0 + y_offset),
                            static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    }
                }
                if (word_736 == 2) {
                    for (int angle = 20; angle < 80; angle += 20) {
                        float parameters[3] = {static_cast<float>(angle), 15.0f, 0.0f};
                        spawn_owned_object_via_manager(810,
                            static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                            static_cast<float>(y_f0 + y_offset),
                            static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    }
                    for (int angle = -20; angle > -80; angle -= 20) {
                        float parameters[3] = {static_cast<float>(angle), 15.0f, 0.0f};
                        spawn_owned_object_via_manager(810,
                            static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                            static_cast<float>(y_f0 + y_offset),
                            static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    }
                }
            } else {
                if (word_736 == 0) {
                    float parameters[3] = {10.0f, 23.0f, 0.0f};
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = 0.0f; parameters[1] = 25.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -10.0f; parameters[1] = 23.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                }
                if (word_736 == 1) {
                    float parameters[3] = {15.0f, 25.0f, 0.0f};
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = 5.0f; parameters[1] = 27.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -5.0f; parameters[1] = 27.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -15.0f; parameters[1] = 25.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                }
                if (word_736 == 2) {
                    float parameters[3] = {20.0f, 26.0f, 0.0f};
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = 10.0f; parameters[1] = 27.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = 0.0f; parameters[1] = 29.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -10.0f; parameters[1] = 27.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -20.0f; parameters[1] = 26.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                }
            }
        }
        if (advance_frame_and_dispatch())
            set_action(0);
        if (aerial && frame_counter_144 == 0 && frame_timer_142 == 0
                && frame_index_140 == 0 && sequence_13e == 5) {
            set_action(9);
            return true;
        }
        if (sequence_13e == 1) {
            if (frame_counter_144 > 20 && word_736 == 0) {
                word_736 = 1;
                emit_fighter_effect(62,
                    aerial ? static_cast<float>(x_ec - static_cast<float>(facing_104 * 35))
                           : static_cast<float>(static_cast<float>(facing_104 * 65) + x_ec),
                    static_cast<float>(y_f0 + (aerial ? 135.0 : 55.0)),
                    static_cast<unsigned char>(facing_104), 1);
            }
            if (frame_counter_144 > 60) {
                word_736 = 2;
                byte_750 = 0;
            }
            if (byte_750 == 0)
                next_sequence_block();
        }
        if (sequence_13e == 3 && frame_counter_144 > (word_736 + 1) * 10)
            next_sequence_block();
        return true;
    }
