// Shared550/551 body and direct560, ending before the high-table selector.
    case 550: case 551:
        byte_17c = 10;
        if (frame_counter_144 == 0 && frame_timer_142 == 0
                && frame_index_140 == 0 && sequence_13e == 2)
            velocity_x_f4 = -2.0f;
        switch (sequence_13e) {
        case 0:
            resolve_stage_surface_landing_transition();
            if (state_180 == 3) {
                state_180 = 0;
                next_sequence_block();
                dispatch_character_wave_handle(18);
                return true;
            }
            break;
        case 1:
            if (frame_timer_142 % 3 == 0) {
                if (frame_timer_142 <= 9) {
                    float parameters[4];
                    parameters[1] = 0.0f;
                    parameters[2] = 4.0f;
                    parameters[3] = 0.0f;
                    for (float i = 0.0f; i < 8.0f; i += 1.0f) {
                        const unsigned int random = static_cast<unsigned int>(selector_random_roll(45));
                        parameters[0] = static_cast<float>(static_cast<double>(static_cast<float>(random)) + i * 45.0);
                        spawn_owned_object_via_manager(822,
                            static_cast<float>(lookup_orientation_cosine_quantized_abs(parameters[0])
                                * static_cast<float>(frame_timer_142 * 20) * facing_104 + x_ec),
                            static_cast<float>(lookup_orientation_sine_quantized_abs(parameters[0])
                                * static_cast<float>(frame_timer_142 * 20) + y_f0 + 100.0),
                            static_cast<unsigned char>(facing_104), 1, parameters, 4);
                    }
                }
                if (frame_timer_142 == 0) {
                    float parameters[4];
                    parameters[2] = 0.0f;
                    for (float sector = 0.0f; sector < 5.0f; sector += 1.0f) {
                        const double offset = sector * 72.0;
                        const float trajectory = static_cast<float>(offset - 90.0 + 162.0);
                        const float geometry = static_cast<float>(90.0 - offset);
                        for (float layer = 0.0f; layer < 5.0f; layer += 1.0f) {
                            parameters[0] = trajectory;
                            parameters[1] = static_cast<float>(layer * 18.0 + 8.0);
                            parameters[3] = static_cast<float>(layer + 30.0);
                            spawn_owned_object_via_manager(822,
                                static_cast<float>(lookup_orientation_cosine_quantized_abs(geometry)
                                    * 250.0 * facing_104 + x_ec),
                                static_cast<float>(lookup_orientation_sine_quantized_abs(geometry)
                                    * 250.0 + y_f0 + 100.0),
                                static_cast<unsigned char>(facing_104), 1, parameters, 4);
                        }
                    }
                }
            }
            break;
        case 2: case 3:
            velocity_y_f8 -= acceleration_y_100;
            if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
                set_action(10);
                y_f0 = reimu_stage_surface_height_at_x(this);
                zero_velocity_acceleration();
                byte_113 = 255;
                return true;
            }
            if (byte_113 < 245)
                byte_113 = static_cast<unsigned char>(byte_113 + 10);
            else
                byte_113 = 255;
            break;
        }
        if (advance_frame_and_dispatch())
            set_action(0);
        if (frame_counter_144 == 0 && frame_timer_142 == 0
                && frame_index_140 == 0 && sequence_13e == 1) {
            set_action(0);
            return true;
        }
        if (frame_counter_144 == 0 && frame_timer_142 == 0
                && frame_index_140 == 0 && sequence_13e == 2) {
            velocity_x_f4 = -200.0f;
            y_f0 = static_cast<float>(y_f0 + 100.0);
            velocity_y_f8 = 2.0f;
            byte_113 = 0;
            acceleration_y_100 = 0.5f;
        }
        if (sequence_13e == 0 && frame_timer_142 == 0 && frame_index_140 == 3) {
            adjust_counter_482(200, 120);
            add_scaled_counter(50);
        }
        return true;
    case 560:
        if (sequence_13e == 0 || sequence_13e == 3)
            resolve_stage_surface_landing_transition();
        byte_17c = 3;
        if (sequence_13e == 1 || sequence_13e == 2)
            velocity_y_f8 -= acceleration_y_100;
        if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())
                && sequence_13e < 3) {
            zero_velocity_acceleration();
            y_f0 = reimu_stage_surface_height_at_x(this);
            set_sequence(3);
            return true;
        }
        if (advance_frame_and_dispatch())
            set_action(0);
        if (frame_timer_142 == 0 && frame_index_140 == 3 && sequence_13e == 0) {
            const float parameters[3] = {0.0f, 12.0f, 0.0f};
            spawn_owned_object_via_manager(825, x_ec, y_f0,
                static_cast<unsigned char>(facing_104), 1, parameters, 3);
            dispatch_character_wave_handle(7);
        }
        if (frame_counter_144 == 0 && frame_timer_142 == 0
                && frame_index_140 == 0 && sequence_13e == 1) {
            adjust_counter_482(200, 120);
            add_scaled_counter(50);
            velocity_x_f4 = 4.5f;
            velocity_y_f8 = 14.0f;
            acceleration_y_100 = 0.75f;
        }
        return true;
