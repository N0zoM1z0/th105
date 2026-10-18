// Mid-table trajectories and opponent-relative objects; no callable boundary.
    case 520: case 521: case 522: case 523: {
        const bool aerial = selected_action == 522 || selected_action == 523;
        const bool fast = selected_action == 521 || selected_action == 523;
        if (!aerial || sequence_13e == 5)
            resolve_stage_surface_landing_transition();
        byte_17c = 1;
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
        if (sequence_13e == 3 && frame_counter_144 == 0) {
            adjust_counter_482(200, 120);
            state_180 = 1;
            add_scaled_counter(50);
            const int x_offset = aerial ? 43 : 114;
            const double y_offset = aerial ? 107.0 : 96.0;
            float parameters[3] = {0.0f, fast ? 25.0f : 12.0f, 0.0f};
            spawn_owned_object_via_manager(815,
                static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                static_cast<float>(y_f0 + y_offset),
                static_cast<unsigned char>(facing_104), 1, parameters, 3);
            parameters[0] = atan2_degrees(135.0f, fast ? 330.0f : 135.0f);
            float shot_speed = static_cast<float>(sqrt_float_value(fast ? 128500.0f : 37825.0f) / 15.0);
            parameters[1] = shot_speed;
            parameters[2] = 2.0f;
            spawn_owned_object_via_manager(815,
                static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                static_cast<float>(y_f0 + y_offset),
                static_cast<unsigned char>(facing_104), 1, parameters, 3);
            parameters[0] = atan2_degrees(-135.0f, fast ? 330.0f : 135.0f);
            parameters[1] = shot_speed;
            spawn_owned_object_via_manager(815,
                static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                static_cast<float>(y_f0 + y_offset),
                static_cast<unsigned char>(facing_104), 1, parameters, 3);
            parameters[0] = atan2_degrees(-115.0f, fast ? 420.0f : 225.0f);
            shot_speed = static_cast<float>(sqrt_float_value(fast ? 190800.0f : 65025.0f) / 15.0);
            parameters[1] = shot_speed;
            spawn_owned_object_via_manager(815,
                static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                static_cast<float>(y_f0 + y_offset),
                static_cast<unsigned char>(facing_104), 1, parameters, 3);
            parameters[0] = atan2_degrees(115.0f, fast ? 420.0f : 225.0f);
            parameters[1] = shot_speed;
            spawn_owned_object_via_manager(815,
                static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                static_cast<float>(y_f0 + y_offset),
                static_cast<unsigned char>(facing_104), 1, parameters, 3);
            dispatch_character_wave_handle(21);
        }
        if (advance_frame_and_dispatch())
            set_action(0);
        if (aerial && frame_counter_144 == 0 && frame_timer_142 == 0
                && frame_index_140 == 0 && sequence_13e == 5) {
            set_action(9);
            return true;
        }
        if (sequence_13e == 1 && frame_counter_144 > 0)
            next_sequence_block();
        return true;
    }
    case 525: case 526:
        resolve_stage_surface_landing_transition();
        byte_17c = 5;
        if ((sequence_13e == 1 && frame_counter_144 > 10)
                || (sequence_13e == 2 && frame_counter_144 > 50)) {
            next_sequence_block();
            return true;
        }
        if (advance_frame_and_dispatch())
            set_action(0);
        if (sequence_13e == 0 && frame_timer_142 == 0 && frame_index_140 == 7) {
            adjust_counter_482(200, 120);
            add_scaled_counter(50);
            state_180 = 1;
            float parameters[3];
            if (selected_action == 525) {
                parameters[0] = 0.0f;
                parameters[1] = 0.0f;
                parameters[2] = 0.0f;
                spawn_owned_object_via_manager(816,
                    static_cast<float>(peer_170->x_ec - static_cast<float>(facing_104 * 50)),
                    static_cast<float>(peer_170->y_f0 + 125.0),
                    static_cast<unsigned char>(facing_104), 1, parameters, 3);
                spawn_owned_object_via_manager(816,
                    static_cast<float>(static_cast<float>(facing_104 * 50) + peer_170->x_ec),
                    static_cast<float>(peer_170->y_f0 + 125.0),
                    static_cast<unsigned char>(-facing_104), 1, parameters, 3);
            }
            if (selected_action == 526 || byte_609 >= 4) {
                parameters[0] = 90.0f;
                parameters[1] = 30.0f;
                parameters[2] = 4.0f;
                spawn_owned_object_via_manager(816, peer_170->x_ec,
                    static_cast<float>(peer_170->y_f0 + 50.0),
                    static_cast<unsigned char>(facing_104), 1, parameters, 3);
                parameters[0] = -90.0f;
                spawn_owned_object_via_manager(816, peer_170->x_ec,
                    static_cast<float>(peer_170->y_f0 + 150.0),
                    static_cast<unsigned char>(facing_104), 1, parameters, 3);
            }
            if (selected_action == 526 && byte_609 >= 4) {
                parameters[0] = 0.0f;
                parameters[1] = 0.0f;
                parameters[2] = 0.0f;
                spawn_owned_object_via_manager(816,
                    static_cast<float>(peer_170->x_ec - static_cast<float>(facing_104 * 50)),
                    static_cast<float>(peer_170->y_f0 + 125.0),
                    static_cast<unsigned char>(facing_104), 1, parameters, 3);
                spawn_owned_object_via_manager(816,
                    static_cast<float>(static_cast<float>(facing_104 * 50) + peer_170->x_ec),
                    static_cast<float>(peer_170->y_f0 + 125.0),
                    static_cast<unsigned char>(-facing_104), 1, parameters, 3);
            }
            dispatch_character_wave_handle(5);
        }
        return true;
    case 530: case 531:
        resolve_stage_surface_landing_transition();
        byte_17c = 9;
        if (sequence_13e == 1 && frame_counter_144 >= 18) {
            next_sequence_block();
            return true;
        }
        if (advance_frame_and_dispatch())
            set_action(selected_action == 530 ? 0 : 2);
        if (frame_counter_144 == 0 && frame_timer_142 == 0
                && frame_index_140 == 0 && sequence_13e == 1) {
            adjust_counter_482(200, 120);
            add_scaled_counter(50);
            state_180 = 1;
            const float parameters[3] = {0.0f, selected_action == 530 ? 0.0f : 20.0f,
                selected_action == 530 ? 0.0f : 9.0f};
            spawn_owned_object_via_manager(817,
                static_cast<float>(static_cast<float>(facing_104 * (selected_action == 530 ? 10 : 50)) + x_ec),
                static_cast<float>(y_f0 - 10.0),
                static_cast<unsigned char>(facing_104), -1, parameters, 3);
            dispatch_character_wave_handle(15);
        }
        return true;
