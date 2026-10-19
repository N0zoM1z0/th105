// First high-table families; continuation of the same action dispatcher.
    case 561:
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
            velocity_y_f8 = 22.5f;
            acceleration_y_100 = 0.75f;
        }
        return true;
    case 565: case 566: {
        if ((sequence_13e == 0 && frame_index_140 <= 1) || sequence_13e == 1
                || sequence_13e == 2 || sequence_13e == 3 || sequence_13e == 6 || sequence_13e == 8)
            resolve_stage_surface_landing_transition();
        byte_17c = 7;
        if ((selected_action == 565 ? field_6c0 : field_6c4) == 0)
            byte_750 = 0;
        velocity_y_f8 -= acceleration_y_100;
        if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending()) && sequence_13e < 1) {
            y_f0 = reimu_stage_surface_height_at_x(this);
            acceleration_y_100 = 0.0f;
            velocity_y_f8 = 0.0f;
            set_sequence(1);
        }
        const double next_y = static_cast<double>(velocity_y_f8) + y_f0;
        if (reimu_stage_surface_height_at_x(this) >= next_y && velocity_y_f8 < 0.0f
                && (sequence_13e == 4 || sequence_13e == 5 || sequence_13e == 7)) {
            y_f0 = reimu_stage_surface_height_at_x(this);
            zero_velocity_acceleration();
            set_sequence(6);
        }
        if (sequence_13e == 1) {
            if (frame_counter_144 >= 10 && byte_750 != 0) {
                next_sequence_block();
                return true;
            }
            if (frame_counter_144 > 25) {
                set_sequence(8);
                return true;
            }
        }
        if (sequence_13e == 4 || sequence_13e == 5) {
            velocity_x_f4 = static_cast<float>(velocity_x_f4 - 0.25);
            if (velocity_x_f4 < 0.0f)
                velocity_x_f4 = 0.0f;
        }
        if (sequence_13e == 7) {
            velocity_x_f4 = static_cast<float>(velocity_x_f4 - static_cast<double>(0.1f));
            if (velocity_x_f4 < 0.0f)
                velocity_x_f4 = 0.0f;
        }
        if (sequence_13e == 8) {
            velocity_x_f4 = static_cast<float>(velocity_x_f4 - static_cast<double>(0.4f));
            if (velocity_x_f4 < 0.0f)
                velocity_x_f4 = 0.0f;
        }
        if (advance_frame_and_dispatch())
            set_action(0);
        if (frame_counter_144 == 0 && frame_timer_142 == 0
                && frame_index_140 == 0 && sequence_13e == 8) {
            set_sequence(5);
            return true;
        }
        if (sequence_13e == 0 && frame_timer_142 == 0 && frame_index_140 == 2) {
            velocity_x_f4 = 12.5f;
            velocity_y_f8 = 4.0f;
            acceleration_y_100 = 0.9f;
            adjust_counter_482(200, 120);
            add_scaled_counter(50);
        }
        if (sequence_13e == 4 && frame_timer_142 == 0 && frame_index_140 == 4
                && byte_750 != 0 && byte_60b >= 4) {
            set_sequence(7);
            state_180 = 0;
            byte_184 = 1;
            velocity_y_f8 = 10.0f;
            acceleration_y_100 = 0.5f;
            return true;
        }
        if (sequence_13e == 7 && frame_timer_142 == 0 && frame_index_140 == 1) {
            const float parameters[3] = {-75.0f, 12.0f, 1.0f};
            spawn_owned_object_via_manager(825,
                static_cast<float>(static_cast<float>(facing_104 * 85) + x_ec),
                static_cast<float>(y_f0 + 117.0),
                static_cast<unsigned char>(facing_104), 1, parameters, 3);
            dispatch_character_wave_handle(10);
        }
        if (frame_counter_144 == 0 && frame_timer_142 == 0 && frame_index_140 == 0 && sequence_13e == 4) {
            state_180 = 0;
            byte_184 = 1;
            velocity_y_f8 = 10.0f;
            acceleration_y_100 = 0.5f;
            const float parameters[3] = {0.0f, 12.0f, 0.0f};
            spawn_owned_object_via_manager(825, x_ec, y_f0,
                static_cast<unsigned char>(facing_104), 1, parameters, 3);
            dispatch_character_wave_handle(7);
        }
        if (frame_counter_144 == 0 && frame_timer_142 == 0 && frame_index_140 == 0 && sequence_13e == 7)
            set_action(0);
        return true;
    }
    case 600: case 601: case 602: {
        resolve_stage_surface_landing_transition();
        publish_texture_state(6, 2);
        const int limit = selected_action == 600 ? 30 : selected_action == 601 ? 60 : 45;
        if (sequence_13e == 1 && frame_counter_144 > limit) {
            next_sequence_block();
            return true;
        }
        const int count_limit = selected_action == 600 ? 5 : selected_action == 601 ? 10 : 14;
        if (selected_action == 602
                ? frame_counter_144 == 0 && frame_timer_142 == 0
                    && frame_index_140 == 0 && sequence_13e == 1 && word_730 < count_limit
                : sequence_13e == 1 && word_730 < count_limit && frame_counter_144 % 5 == 0) {
            dispatch_character_wave_handle(8);
            float angle;
            if (selected_action == 600)
                angle = static_cast<float>((word_730 - 2) * 45);
            else if (selected_action == 601)
                angle = static_cast<float>(word_730 * -36.0);
            else
                angle = static_cast<float>(static_cast<double>(static_cast<float>(mt19937_next_u32() % 70U)) - 35.0);
            float parameters[3] = {angle, 0.0f, static_cast<float>(word_730 % 3)};
            spawn_owned_object_via_manager(selected_action == 600 ? 850 : selected_action == 601 ? 853 : 854,
                static_cast<float>(static_cast<float>(facing_104 * 18) + x_ec),
                static_cast<float>(y_f0 + 120.0),
                static_cast<unsigned char>(facing_104), 1, parameters, 3);
            if (selected_action == 601) {
                parameters[0] = 0.0f;
                parameters[1] = 0.0f;
                spawn_owned_object_via_manager(860,
                    static_cast<float>(static_cast<float>(facing_104 * 18) + x_ec),
                    static_cast<float>(y_f0 + 120.0),
                    static_cast<unsigned char>(facing_104), 1, parameters, 3);
            }
            word_730 = static_cast<short>(word_730 + 1);
        }
        if (advance_frame_and_dispatch()) {
            set_action(0);
            if (selected_action != 602)
                publish_texture_state(6, static_cast<short>(selected_action == 600 ? 30 : 60));
        }
        if (sequence_13e == 0 && frame_index_140 == 2 && frame_timer_142 == 0) {
            set_word_48a(40);
            dispatch_indexed_event_member(23);
            const int direction_bits = static_cast<unsigned char>(facing_104);
            emit_fighter_effect(115,
                static_cast<float>(x_ec - static_cast<signed char>(direction_bits) * 2),
                static_cast<float>(y_f0 + 120.0), direction_bits, 1);
            dispatch_indexed_sequence_window_45c8b0(0, selected_action == 601 ? 5 : 2, 60);
            advance_secondary_event_effect_cycle();
        }
        return true;
    }
    case 604: case 605: case 606:
        resolve_stage_surface_landing_transition();
        publish_texture_state(6, 2);
        if ((sequence_13e == 1 && frame_counter_144 > (selected_action == 606 ? 90 : 30))
                || (sequence_13e == 2 && selected_action != 605
                    && frame_counter_144 > (selected_action == 606 ? 70 : 30))) {
            next_sequence_block();
            return true;
        }
        if (sequence_13e == 0 && frame_index_140 == 6 && frame_timer_142 == 0) {
            set_word_48a(40);
            dispatch_indexed_event_member(23);
            const int direction_bits = static_cast<unsigned char>(facing_104);
            emit_fighter_effect(115, static_cast<float>(static_cast<float>(static_cast<signed char>(direction_bits) * 7) + x_ec),
                static_cast<float>(y_f0 + 226.0), direction_bits, 1);
            dispatch_indexed_sequence_window_45c8b0(0, selected_action == 604 ? 2 : selected_action == 605 ? 3 : 4, 60);
            advance_secondary_event_effect_cycle();
        }
        if (advance_frame_and_dispatch())
            set_action(0);
        if (sequence_13e == 0 && frame_timer_142 == 0 && frame_index_140 == 8) {
            const float parameters[1] = {0.0f};
            if (selected_action == 605) {
                spawn_owned_object_via_manager(855,
                    static_cast<float>(static_cast<float>(facing_104 * 75) + x_ec), y_f0,
                    static_cast<unsigned char>(facing_104), 1, parameters, 1);
                spawn_owned_object_via_manager(855,
                    static_cast<float>(x_ec - static_cast<float>(facing_104 * 75)), y_f0,
                    static_cast<unsigned char>(-facing_104), 1, parameters, 1);
            } else {
                spawn_owned_object_via_manager(selected_action == 604 ? 851 : 856, x_ec, y_f0,
                    static_cast<unsigned char>(facing_104), 1, parameters, 1);
            }
            dispatch_character_wave_handle(9);
        }
        return true;
