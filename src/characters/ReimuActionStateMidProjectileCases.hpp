// Shared middle-table statements; not an original callable boundary.
    case 400: case 401: case 404: case 406: {
        const bool aerial = selected_action == 404 || selected_action == 406;
        if (!aerial || sequence_13e == 8)
            resolve_stage_surface_landing_transition();
        if (aerial) {
            velocity_y_f8 = static_cast<float>(velocity_y_f8 - acceleration_y_100);
            if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())
                    && sequence_13e < 8) {
                set_sequence(8);
                byte_47f = 0;
                y_f0 = reimu_stage_surface_height_at_x(this);
                zero_velocity_acceleration();
                word_730 = 0;
                return true;
            }
        }
        if (sequence_13e == 0 && field_6c0 == 0)
            byte_750 = 0;
        if (word_730 > 0) {
            word_730 = static_cast<short>(word_730 + 1);
            if (word_730 % 3 == 1 && word_732 < 5) {
                state_180 = 1;
                if (aerial)
                    add_scaled_counter(10);
                if (word_732 == 0)
                    adjust_counter_482(200, 45);
                if (selected_action == 401)
                    add_scaled_counter(10);
                float parameters[3] = {
                    static_cast<float>((word_732 - 2) * 5 + word_734), 15.0f, 0.0f};
                if (selected_action == 400)
                    add_scaled_counter(10);
                const int x_offset = selected_action == 400 ? 114
                    : selected_action == 401 ? 90 : selected_action == 404 ? 83 : 67;
                const double y_offset = selected_action == 400 ? 96.0
                    : selected_action == 401 ? 158.0 : selected_action == 404 ? 117.0 : 75.0;
                if (byte_750 == 0) {
                    spawn_owned_object_via_manager(800,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                } else {
                    for (int count = 0; count < 2; ++count) {
                        parameters[0] = static_cast<float>(selector_random_range(0, 30) + word_734 - 15);
                        parameters[1] = static_cast<float>(15 - selector_random_range(0, 5));
                        spawn_owned_object_via_manager(800,
                            static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                            static_cast<float>(y_f0 + y_offset),
                            static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    }
                }
                dispatch_character_wave_handle(0);
                word_732 = static_cast<short>(word_732 + 1);
            }
        }
        if (advance_frame_and_dispatch())
            set_action(0);
        if (frame_counter_144 == 0 && frame_timer_142 == 0
                && frame_index_140 == 0 && sequence_13e == 1 && byte_750 == 1) {
            if (selected_action != 406)
                set_sequence(4);
            emit_fighter_effect(62,
                aerial ? static_cast<float>(x_ec - static_cast<float>(facing_104 * 35))
                       : static_cast<float>(static_cast<float>(facing_104 * 65) + x_ec),
                static_cast<float>(y_f0 + (aerial ? 135.0 : 55.0)),
                static_cast<unsigned char>(facing_104), 1);
            if (selected_action == 406)
                set_sequence(4);
            return true;
        }
        if (frame_counter_144 == 0 && frame_timer_142 == 0
                && frame_index_140 == 0 && sequence_13e == 2) {
            const float delta_x = static_cast<float>(
                (static_cast<double>(peer_170->x_ec) - x_ec) * facing_104);
            const float delta_y = static_cast<float>(static_cast<double>(peer_170->y_f0) - y_f0);
            const short angle = static_cast<short>(static_cast<int>(atan2_degrees(delta_y, delta_x)));
            word_734 = static_cast<short>(-angle);
            const short lower = selected_action == 401 ? -60 : selected_action == 406 ? 40 : -30;
            const short upper = selected_action == 401 ? -40 : selected_action == 406 ? 60 : 30;
            if (word_734 < lower)
                word_734 = lower;
            if (word_734 > upper)
                word_734 = upper;
            word_730 = 1;
        }
        if (sequence_13e == 2 && frame_counter_144 > 20) {
            next_sequence_block();
            if (aerial)
                acceleration_y_100 = 0.35f;
        }
        if (frame_counter_144 == 0 && frame_timer_142 == 0
                && frame_index_140 == 0 && sequence_13e == 4)
            set_action(aerial ? 9 : 0);
        if (sequence_13e == 4 && frame_counter_144 > 15)
            next_sequence_block();
        if (frame_counter_144 == 0 && frame_timer_142 == 0
                && frame_index_140 == 0 && sequence_13e == 6) {
            const float delta_x = static_cast<float>(
                (static_cast<double>(peer_170->x_ec) - x_ec) * facing_104);
            const float delta_y = static_cast<float>(static_cast<double>(peer_170->y_f0) - y_f0);
            const short angle = static_cast<short>(static_cast<int>(atan2_degrees(delta_y, delta_x)));
            word_734 = static_cast<short>(-angle);
            const short lower = selected_action == 401 ? -60 : selected_action == 406 ? 40 : -30;
            const short upper = selected_action == 401 ? -40 : selected_action == 406 ? 60 : 30;
            if (word_734 < lower)
                word_734 = lower;
            if (word_734 > upper)
                word_734 = upper;
            word_730 = 1;
        }
        if (sequence_13e == 6 && frame_counter_144 > (aerial ? 28 : 20)) {
            next_sequence_block();
            if (aerial)
                acceleration_y_100 = 0.35f;
        }
        if (aerial && frame_counter_144 == 0 && frame_timer_142 == 0
                && frame_index_140 == 0 && sequence_13e == 8)
            set_action(9);
        return true;
    }
    case 402:
        resolve_stage_surface_landing_transition();
        if (word_730 > 0) {
            word_730 = static_cast<short>(word_730 + 1);
            if (word_738 != 0 && word_730 % 3 == 1 && word_732 < 5)
                word_732 = static_cast<short>(word_732 + 1);
        }
        if (sequence_13e == 2 && frame_counter_144 > 10) {
            next_sequence_block();
            return true;
        }
        if (advance_frame_and_dispatch())
            set_action(2);
        if (frame_counter_144 == 0 && frame_timer_142 == 0
                && frame_index_140 == 0 && sequence_13e == 2) {
            state_180 = 1;
            add_scaled_counter(30);
            float parameters[3] = {0.0f, 0.0f, 0.0f};
            spawn_owned_object_via_manager(807,
                static_cast<float>(static_cast<float>(facing_104 * 94) + x_ec),
                y_f0, static_cast<unsigned char>(facing_104), 1, parameters, 3);
            parameters[1] = 1.0f;
            spawn_owned_object_via_manager(807,
                static_cast<float>(static_cast<float>(facing_104 * 94) + x_ec),
                y_f0, static_cast<unsigned char>(facing_104), 1, parameters, 3);
            dispatch_character_wave_handle(1);
            adjust_counter_482(200, 45);
        }
        if (frame_counter_144 == 0 && frame_timer_142 == 0
                && frame_index_140 == 0 && sequence_13e == 4)
            set_action(2);
        return true;
    case 408:
        if (sequence_13e == 1 || sequence_13e == 2)
            resolve_stage_surface_landing_transition();
        if (sequence_13e == 0 && frame_index_140 == 2) {
            velocity_y_f8 = static_cast<float>(velocity_y_f8 - acceleration_y_100);
            if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
                y_f0 = reimu_stage_surface_height_at_x(this);
                acceleration_y_100 = 0.0f;
                velocity_y_f8 = 0.0f;
                next_sequence_block();
                dispatch_indexed_event_member(29);
            }
        }
        if (sequence_13e == 1 && frame_counter_144 > 10)
            next_sequence_block();
        if (sequence_13e == 2) {
            velocity_x_f4 = static_cast<float>(velocity_x_f4 - 1.0);
            if (velocity_x_f4 < 0.0f)
                velocity_x_f4 = 0.0f;
        }
        if (advance_frame_and_dispatch())
            set_action(0);
        if (sequence_13e == 0 && frame_index_140 == 2 && frame_timer_142 == 0) {
            velocity_y_f8 = 3.5f;
            acceleration_y_100 = 0.75f;
        }
        if (frame_counter_144 == 0 && frame_timer_142 == 0
                && frame_index_140 == 0 && sequence_13e == 1)
            dispatch_indexed_event_member(28);
        return true;
