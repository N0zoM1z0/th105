// Middle shot/movement source, included directly in the staged root method.
    case 410: {
        const bool aerial = false;
        if (!aerial || sequence_13e == 3)
            resolve_stage_surface_landing_transition();
        if (aerial && ((sequence_13e == 0 && frame_index_140 >= 8)
                || (sequence_13e == 2 && frame_index_140 >= 4))) {
            acceleration_y_100 = 0.6f;
            velocity_y_f8 = static_cast<float>(velocity_y_f8 - static_cast<double>(0.6f));
            if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
                zero_velocity_acceleration();
                y_f0 = reimu_stage_surface_height_at_x(this);
                set_sequence(3);
                return true;
            }
        }
        if (field_6c4 == 0)
            byte_750 = 0;
        if (advance_frame_and_dispatch())
            set_action(0);
        if (frame_counter_144 == 0 && frame_timer_142 == 0 && frame_index_140 == 0
                && sequence_13e == 1) {
            set_action(aerial ? 9 : 0);
            return true;
        }
        if (aerial && frame_counter_144 == 0 && frame_timer_142 == 0
                && frame_index_140 == 0 && sequence_13e == 3) {
            set_action(9);
            return true;
        }
        if (sequence_13e == 0 && frame_timer_142 == 0) {
            if (frame_index_140 == (aerial ? 4 : 6) && byte_750 != 0) {
                emit_fighter_effect(62,
                    static_cast<float>(static_cast<float>(facing_104 * (aerial ? 62 : 67)) + x_ec),
                    static_cast<float>(y_f0 + (aerial ? 108.0 : 57.0)),
                    static_cast<unsigned char>(facing_104), 1);
                next_sequence_block();
                break;
            }
            if (frame_timer_142 == 0 && frame_index_140 == (aerial ? 5 : 8)) {
                if (aerial)
                    add_scaled_counter(50);
                const float delta_x = static_cast<float>(
                    (static_cast<double>(peer_170->x_ec) - x_ec) * facing_104);
                const short angle = static_cast<short>(static_cast<int>(atan2_degrees(
                    static_cast<float>(static_cast<double>(peer_170->y_f0) - y_f0), delta_x)));
                word_734 = static_cast<short>(-angle);
                if (word_734 < -10)
                    word_734 = -10;
                if (word_734 > 10)
                    word_734 = 10;
                dispatch_character_wave_handle(2);
                adjust_counter_482(200, 60);
                state_180 = 1;
                const float parameters[4] = {static_cast<float>(word_734), 10.0f, 1.0f, 0.0f};
                if (!aerial)
                    add_scaled_counter(50);
                spawn_owned_object_via_manager(801,
                    static_cast<float>(static_cast<float>(facing_104 * (aerial ? 62 : 48)) + x_ec),
                    static_cast<float>(y_f0 + (aerial ? 108.0 : 100.0)),
                    static_cast<unsigned char>(facing_104), 1, parameters, 4);
            }
        }
        if (sequence_13e == 1 && frame_counter_144 >= 25) {
            next_sequence_block();
            return true;
        }
        if (sequence_13e == 2 && frame_timer_142 == 0
                && frame_index_140 == (aerial ? 1 : 2)) {
            if (aerial)
                add_scaled_counter(50);
            const float delta_x = static_cast<float>(
                (static_cast<double>(peer_170->x_ec) - x_ec) * facing_104);
            const short angle = static_cast<short>(static_cast<int>(atan2_degrees(
                static_cast<float>(static_cast<double>(peer_170->y_f0) - y_f0), delta_x)));
            word_734 = static_cast<short>(-angle);
            if (word_734 < -10)
                word_734 = -10;
            if (word_734 > 10)
                word_734 = 10;
            dispatch_character_wave_handle(2);
            adjust_counter_482(200, 60);
            state_180 = 1;
            const float parameters[4] = {static_cast<float>(word_734), 10.0f, 1.0f, 1.0f};
            if (!aerial)
                add_scaled_counter(50);
            spawn_owned_object_via_manager(801,
                static_cast<float>(static_cast<float>(facing_104 * (aerial ? 62 : 48)) + x_ec),
                static_cast<float>(y_f0 + (aerial ? 108.0 : 100.0)),
                static_cast<unsigned char>(facing_104), 1, parameters, 4);
        }
        return true;
    }
    case 414: {
        const bool aerial = true;
        if (!aerial || sequence_13e == 3)
            resolve_stage_surface_landing_transition();
        if (aerial && ((sequence_13e == 0 && frame_index_140 >= 8)
                || (sequence_13e == 2 && frame_index_140 >= 4))) {
            acceleration_y_100 = 0.6f;
            velocity_y_f8 = static_cast<float>(velocity_y_f8 - static_cast<double>(0.6f));
            if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
                zero_velocity_acceleration();
                y_f0 = reimu_stage_surface_height_at_x(this);
                set_sequence(3);
                return true;
            }
        }
        if (field_6c4 == 0)
            byte_750 = 0;
        if (advance_frame_and_dispatch())
            set_action(0);
        if (frame_counter_144 == 0 && frame_timer_142 == 0 && frame_index_140 == 0
                && sequence_13e == 1) {
            goto reimu_action414_action9_exit;
        }
        if (aerial && frame_counter_144 == 0 && frame_timer_142 == 0
                && frame_index_140 == 0 && sequence_13e == 3) {
reimu_action414_action9_exit:
            set_action(9);
            return true;
        }
        if (sequence_13e == 0 && frame_timer_142 == 0) {
            if (frame_index_140 == (aerial ? 4 : 6) && byte_750 != 0) {
                emit_fighter_effect(62,
                    static_cast<float>(static_cast<float>(facing_104 * (aerial ? 62 : 67)) + x_ec),
                    static_cast<float>(y_f0 + (aerial ? 108.0 : 57.0)),
                    static_cast<unsigned char>(facing_104), 1);
                next_sequence_block();
                break;
            }
            if (frame_timer_142 == 0 && frame_index_140 == (aerial ? 5 : 8)) {
                if (aerial)
                    add_scaled_counter(50);
                const float delta_x = static_cast<float>(
                    (static_cast<double>(peer_170->x_ec) - x_ec) * facing_104);
                const short angle = static_cast<short>(static_cast<int>(atan2_degrees(
                    static_cast<float>(static_cast<double>(peer_170->y_f0) - y_f0), delta_x)));
                word_734 = static_cast<short>(-angle);
                if (word_734 < -10)
                    word_734 = -10;
                if (word_734 > 10)
                    word_734 = 10;
                dispatch_character_wave_handle(2);
                adjust_counter_482(200, 60);
                state_180 = 1;
                const float parameters[4] = {static_cast<float>(word_734), 10.0f, 1.0f, 0.0f};
                if (!aerial)
                    add_scaled_counter(50);
                spawn_owned_object_via_manager(801,
                    static_cast<float>(static_cast<float>(facing_104 * (aerial ? 62 : 48)) + x_ec),
                    static_cast<float>(y_f0 + (aerial ? 108.0 : 100.0)),
                    static_cast<unsigned char>(facing_104), 1, parameters, 4);
            }
        }
        if (sequence_13e == 1 && frame_counter_144 >= 25) {
            next_sequence_block();
            return true;
        }
        if (sequence_13e == 2 && frame_timer_142 == 0
                && frame_index_140 == (aerial ? 1 : 2)) {
            if (aerial)
                add_scaled_counter(50);
            const float delta_x = static_cast<float>(
                (static_cast<double>(peer_170->x_ec) - x_ec) * facing_104);
            const short angle = static_cast<short>(static_cast<int>(atan2_degrees(
                static_cast<float>(static_cast<double>(peer_170->y_f0) - y_f0), delta_x)));
            word_734 = static_cast<short>(-angle);
            if (word_734 < -10)
                word_734 = -10;
            if (word_734 > 10)
                word_734 = 10;
            dispatch_character_wave_handle(2);
            adjust_counter_482(200, 60);
            state_180 = 1;
            const float parameters[4] = {static_cast<float>(word_734), 10.0f, 1.0f, 1.0f};
            if (!aerial)
                add_scaled_counter(50);
            spawn_owned_object_via_manager(801,
                static_cast<float>(static_cast<float>(facing_104 * (aerial ? 62 : 48)) + x_ec),
                static_cast<float>(y_f0 + (aerial ? 108.0 : 100.0)),
                static_cast<unsigned char>(facing_104), 1, parameters, 4);
        }
        return true;
    }
    case 412:
        resolve_stage_surface_landing_transition();
        if (field_6c4 == 0)
            byte_750 = 0;
        if (advance_frame_and_dispatch())
            set_action(0);
        if (frame_counter_144 == 0 && frame_timer_142 == 0
                && frame_index_140 == 0 && sequence_13e == 3) {
            set_action(0);
            return true;
        }
        if (sequence_13e == 0 && frame_index_140 == 5 && frame_timer_142 == 0) {
            adjust_counter_482(200, 60);
            state_180 = 1;
            add_scaled_counter(50);
            dispatch_character_wave_handle(3);
            float parameters[3] = {0.0f, 0.0f, 0.0f};
            spawn_owned_object_via_manager(808, x_ec, y_f0,
                static_cast<unsigned char>(facing_104), -1, parameters, 3);
            parameters[2] = 1.0f;
            spawn_owned_object_via_manager(808, x_ec, y_f0,
                static_cast<unsigned char>(facing_104), -1, parameters, 3);
        }
        if (sequence_13e == 1 && frame_counter_144 > 20)
            next_sequence_block();
        return true;
    case 416:
        if (sequence_13e == 3)
            resolve_stage_surface_landing_transition();
        if ((sequence_13e == 0 && frame_index_140 >= 4)
                || (sequence_13e == 2 && frame_index_140 >= 1)) {
            acceleration_y_100 = 0.6f;
            velocity_y_f8 = static_cast<float>(velocity_y_f8 - static_cast<double>(0.6f));
            if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
                zero_velocity_acceleration();
                y_f0 = reimu_stage_surface_height_at_x(this);
                set_sequence(3);
                return true;
            }
        }
        if (field_6c4 == 0)
            byte_750 = 0;
        if (advance_frame_and_dispatch())
            set_action(0);
        if (frame_counter_144 == 0 && frame_timer_142 == 0 && frame_index_140 == 0
                && sequence_13e == 1) {
            set_action(9);
            return true;
        }
        if (frame_counter_144 == 0 && frame_timer_142 == 0 && frame_index_140 == 0
                && sequence_13e == 3) {
            set_action(9);
            return true;
        }
        if (sequence_13e == 0 && frame_timer_142 == 0) {
            if (frame_index_140 == 3 && byte_750 != 0) {
                emit_fighter_effect(62,
                    static_cast<float>(static_cast<float>(facing_104 * 14) + x_ec),
                    static_cast<float>(y_f0 + 197.0),
                    static_cast<unsigned char>(facing_104), 1);
                next_sequence_block();
                break;
            }
            if (frame_timer_142 == 0 && frame_index_140 == 4) {
                velocity_x_f4 = -5.0f;
                velocity_y_f8 = 6.5f;
                acceleration_y_100 = 0.6f;
                field_744 = 45.0f;
                dispatch_character_wave_handle(2);
                adjust_counter_482(200, 60);
                state_180 = 1;
                add_scaled_counter(50);
                const float parameters[4] = {field_744, 10.0f, 1.0f, 0.0f};
                spawn_owned_object_via_manager(801,
                    static_cast<float>(static_cast<float>(facing_104 * 55) + x_ec),
                    static_cast<float>(y_f0 + 80.0),
                    static_cast<unsigned char>(facing_104), 1, parameters, 4);
            }
        }
        if (sequence_13e == 1 && frame_counter_144 >= 25) {
            next_sequence_block();
            return true;
        }
        if (sequence_13e == 2 && frame_timer_142 == 0 && frame_index_140 == 1) {
            velocity_x_f4 = -5.0f;
            velocity_y_f8 = 6.5f;
            acceleration_y_100 = 0.6f;
            field_744 = 45.0f;
            dispatch_character_wave_handle(2);
            adjust_counter_482(200, 60);
            state_180 = 1;
            add_scaled_counter(50);
            const float parameters[4] = {field_744, 10.0f, 1.0f, 1.0f};
            spawn_owned_object_via_manager(801,
                static_cast<float>(static_cast<float>(facing_104 * 55) + x_ec),
                static_cast<float>(y_f0 + 80.0),
                static_cast<unsigned char>(facing_104), 1, parameters, 4);
        }
        return true;
    case 418:
        if ((sequence_13e == 0 && frame_index_140 <= 2) || sequence_13e == 2)
            resolve_stage_surface_landing_transition();
        velocity_y_f8 = static_cast<float>(velocity_y_f8 - acceleration_y_100);
        if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())
                && sequence_13e < 2) {
            y_f0 = reimu_stage_surface_height_at_x(this);
            acceleration_y_100 = 0.0f;
            velocity_y_f8 = 0.0f;
            set_sequence(2);
        }
        if (sequence_13e == 2) {
            velocity_x_f4 = static_cast<float>(velocity_x_f4 - 2.0);
            if (velocity_x_f4 < 0.0f)
                velocity_x_f4 = 0.0f;
        }
        if (advance_frame_and_dispatch())
            set_action(0);
        if (sequence_13e == 0 && frame_index_140 == 3 && frame_timer_142 == 0) {
            velocity_y_f8 = 10.0f;
            acceleration_y_100 = 0.85f;
            dispatch_indexed_event_member(29);
        }
        return true;
