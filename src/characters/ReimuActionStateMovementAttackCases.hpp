// Shared source fragment; include only within the matching staging context.
    case 88:
        if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
            word_730 = static_cast<short>(static_cast<short>(static_cast<int>(velocity_x_f4)) * 100);
            word_732 = static_cast<short>(static_cast<short>(static_cast<int>(velocity_y_f8)) * 100);
            zero_velocity_acceleration();
            y_f0 = reimu_stage_surface_height_at_x(this);
            set_action(89);
            publish_battle_layout_scalar(5.0f);
            dispatch_indexed_event_member(22);
            return true;
        }
        advance_frame_and_dispatch();
        if (frame_counter_144 == 0 && frame_timer_142 == 0
                && frame_index_140 == 0 && sequence_13e == 1) {
            if (word_7a4 == 0) {
                word_7a4 = 1;
                spawn_owned_object_via_manager(951, x_ec, y_f0,
                    static_cast<unsigned char>(facing_104), 1, 0, 0);
            }
            if (velocity_y_f8) {
                if (!velocity_x_f4) {
                    set_sequence(3);
                    return true;
                }
                set_sequence(2);
                return true;
            }
        }
        word_730 = static_cast<short>(word_730 - 1);
        if (word_730 < 0)
            word_730 = 0;
        if (classify_fighter_x_boundary() && velocity_x_f4 < 0.0f) {
            velocity_x_f4 = static_cast<float>(velocity_x_f4 + 2.5);
            if (velocity_x_f4 > 0.0f)
                velocity_x_f4 = 0.0f;
            if (byte_490)
                field_6ac = static_cast<float>(word_730 * -2.0);
        }
        return true;
    case 89:
        if (sequence_13e > 0) {
            angle_12c = static_cast<float>(angle_12c - 40.0);
            velocity_y_f8 = static_cast<float>(velocity_y_f8 - acceleration_y_100);
            if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
                word_730 = static_cast<short>(static_cast<short>(static_cast<int>(velocity_x_f4)) * 100);
                word_732 = static_cast<short>(static_cast<short>(static_cast<int>(velocity_y_f8)) * 100);
                zero_velocity_acceleration();
                y_f0 = reimu_stage_surface_height_at_x(this);
                set_action(97);
                angle_12c = 0.0f;
                publish_battle_layout_scalar(2.0f);
                reinterpret_cast<ReimuRecoverySpriteView *>(
                    reinterpret_cast<unsigned char *>(this) + 4)->reset_fighter_action_scratch();
                dispatch_indexed_event_member(22);
                return true;
            }
        }
        advance_frame_and_dispatch();
        if (frame_counter_144 == 0 && frame_timer_142 == 0
                && frame_index_140 == 0 && sequence_13e == 1) {
            velocity_x_f4 = static_cast<float>(word_730 * static_cast<double>(0.0025f));
            velocity_y_f8 = static_cast<float>(-static_cast<int>(word_732) * static_cast<double>(0.0025f));
            acceleration_y_100 = 0.25f;
            word_7a0 = 0;
            word_7a2 = 85;
            field_108 = static_cast<float>(word_7a0);
            field_10c = static_cast<float>(word_7a2);
        }
        return true;
    case 145:
        if (frame_counter_144 == 0 && frame_timer_142 == 0
                && frame_index_140 == 0 && sequence_13e == 1 && word_7a4 == 0) {
            word_7a4 = 1;
            spawn_owned_object_via_manager(951, x_ec, y_f0,
                static_cast<unsigned char>(facing_104), 1, 0, 0);
        }
        if (sequence_13e == 1 && velocity_y_f8 < 2.0f) {
            next_sequence_block();
            return true;
        }
        velocity_y_f8 = static_cast<float>(velocity_y_f8 - acceleration_y_100);
        if (velocity_y_f8 > 0.0f)
            velocity_y_f8 = static_cast<float>(velocity_y_f8 - acceleration_y_100);
        if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
            word_730 = static_cast<short>(static_cast<short>(static_cast<int>(velocity_x_f4)) * 100);
            word_732 = static_cast<short>(static_cast<short>(static_cast<int>(velocity_y_f8)) * 100);
            zero_velocity_acceleration();
            y_f0 = reimu_stage_surface_height_at_x(this);
            set_action(97);
            publish_battle_layout_scalar(2.0f);
            dispatch_indexed_event_member(22);
            return true;
        }
        if (word_730 > 0)
            --word_730;
        if (classify_fighter_x_boundary() && velocity_x_f4 < 0.0f) {
            velocity_x_f4 = static_cast<float>(velocity_x_f4 + 1.0);
            if (velocity_x_f4 > 0.0f)
                velocity_x_f4 = 0.0f;
            if (byte_490)
                field_6ac = static_cast<float>(word_730 * -2.0);
        }
        advance_frame_and_dispatch();
        return true;
    case 197:
    case 198:
    case 199:
        if (selected_action == 199 || (sequence_13e == 0 && frame_index_140 <= 2)
                || sequence_13e == 2)
            resolve_stage_surface_landing_transition();
        if (selected_action != 199) {
            if (sequence_13e < 2)
                velocity_y_f8 = static_cast<float>(velocity_y_f8 - acceleration_y_100);
            if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
                y_f0 = reimu_stage_surface_height_at_x(this);
                zero_velocity_acceleration();
                set_sequence(2);
                return true;
            }
        }
        if (advance_frame_and_dispatch()) {
            if (byte_72c == 2) {
                set_action(700);
                word_4a8 = 3;
                word_4ac = 3;
                return true;
            }
            set_action(0);
            if (field_6b8 > 0)
                set_action(1);
        }
        if (sequence_13e == 2 && frame_index_140 == (selected_action == 199 ? 2 : 4)
                && frame_timer_142 == 0) {
            if (x_ec > peer_170->x_ec)
                facing_104 = -1;
            if (x_ec < peer_170->x_ec)
                facing_104 = 1;
        }
        if (selected_action != 199 && sequence_13e == 0
                && frame_index_140 == 3 && frame_timer_142 == 0) {
            velocity_y_f8 = 4.5f;
            velocity_x_f4 = selected_action == 197 ? 12.5f : -12.5f;
            acceleration_y_100 = 0.35f;
        }
        return true;
    case 200:
        resolve_stage_surface_landing_transition();
        byte_47e = 1;
        if (velocity_x_f4 > 8.0f) {
            velocity_x_f4 = static_cast<float>(velocity_x_f4 - 0.5);
            if (velocity_x_f4 < 8.0f)
                velocity_x_f4 = 8.0f;
        }
        advance_frame_and_dispatch();
        if (sequence_13e == 1) {
            if (frame_counter_144 % 5 == 0) {
                const double x_base = static_cast<double>(x_ec) + 50.0;
                const unsigned char direction = static_cast<unsigned char>(facing_104);
                emit_fighter_effect(124,
                    static_cast<float>(x_base - static_cast<float>(mt19937_next_u32() % 100)),
                    static_cast<float>(static_cast<float>(mt19937_next_u32() % 200) + y_f0),
                    direction, 1);
            }
            const int directed_input = static_cast<int>(static_cast<unsigned int>(facing_104)
                * static_cast<unsigned int>(field_6b4));
            if (field_6b8 < 0) {
                if (directed_input > 0) {
                    set_action(212);
                    return true;
                }
                set_action(211);
                return true;
            }
            word_730 = static_cast<short>(word_730 + 1);
            if ((directed_input <= 0 && word_730 > 5) || word_730 > 45) {
                set_action(204);
                return true;
            }
        }
        if (sequence_13e == 0 && frame_index_140 == 3 && frame_timer_142 == 0) {
            velocity_x_f4 = 15.5f;
            const float effect_y = static_cast<float>(y_f0 + 80.0);
            const float effect_x = static_cast<float>(facing_104 * 80 + x_ec);
            emit_fighter_effect(125, effect_x, effect_y, static_cast<unsigned char>(facing_104), 1);
            emit_fighter_effect(126, x_ec, static_cast<float>(y_f0 + 80.0),
                static_cast<unsigned char>(facing_104), 1);
            dispatch_indexed_event_member(31);
        }
        return true;
    case 201:
        if (sequence_13e == 0 || sequence_13e == 3)
            resolve_stage_surface_landing_transition();
        if (sequence_13e == 1 || sequence_13e == 2)
            velocity_y_f8 = static_cast<float>(velocity_y_f8 - 0.5);
        if (sequence_13e == 3) {
            velocity_x_f4 = static_cast<float>(velocity_x_f4 + 3.0);
            if (velocity_x_f4 > 0.0f)
                velocity_x_f4 = 0.0f;
        }
        if (!is_at_stage_surface() && frame_counter_144 % 5 == 0) {
            const double x_base = static_cast<double>(x_ec) + 50.0;
            const unsigned char direction = static_cast<unsigned char>(-facing_104);
            emit_fighter_effect(124,
                static_cast<float>(x_base - static_cast<float>(mt19937_next_u32() % 100)),
                static_cast<float>(static_cast<float>(mt19937_next_u32() % 200) + y_f0),
                direction, 1);
        }
        if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending()) && sequence_13e < 3) {
            velocity_y_f8 = 0.0f;
            acceleration_y_100 = 0.0f;
            y_f0 = reimu_stage_surface_height_at_x(this);
            set_sequence(3);
            return true;
        }
        if (advance_frame_and_dispatch()) {
            set_action(0);
            velocity_x_f4 = 0.0f;
            return true;
        }
        if (frame_counter_144 == 0 && frame_timer_142 == 0
                && frame_index_140 == 0 && sequence_13e == 1) {
            velocity_x_f4 = -14.0f;
            velocity_y_f8 = 4.0f;
            const float effect_y = static_cast<float>(y_f0 + 80.0);
            emit_fighter_effect(125, x_ec, effect_y, static_cast<unsigned char>(-facing_104), 1);
            emit_fighter_effect(126, x_ec, static_cast<float>(y_f0 + 80.0),
                static_cast<unsigned char>(-facing_104), 1);
            dispatch_indexed_event_member(31);
        }
        return true;
    case 202:
    case 203:
        if (selected_action == 203 && frame_counter_144 == 0 && frame_timer_142 == 0
                && frame_index_140 == 0 && sequence_13e == 0) {
            velocity_x_f4 = -10.0f;
            velocity_y_f8 = 4.0f;
            acceleration_y_100 = 0.45f;
            const float effect_y = static_cast<float>(y_f0 + 120.0);
            emit_fighter_effect(125, x_ec, effect_y, static_cast<unsigned char>(-facing_104), 1);
            emit_fighter_effect(126, x_ec, static_cast<float>(y_f0 + 120.0),
                static_cast<unsigned char>(-facing_104), 1);
            dispatch_indexed_event_member(31);
        }
        velocity_y_f8 = static_cast<float>(velocity_y_f8 - acceleration_y_100);
        if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
            zero_velocity_acceleration();
            y_f0 = reimu_stage_surface_height_at_x(this);
            set_action(10);
            return true;
        }
        if (sequence_13e == 1 && frame_counter_144 % 5 == 0) {
            const double x_base = static_cast<double>(x_ec) + 50.0;
            const unsigned char direction = static_cast<unsigned char>(
                selected_action == 202 ? facing_104 : -facing_104);
            emit_fighter_effect(124,
                static_cast<float>(x_base - static_cast<float>(mt19937_next_u32() % 100)),
                static_cast<float>(static_cast<float>(mt19937_next_u32() % 200) + y_f0),
                direction, 1);
        }
        advance_frame_and_dispatch();
        if (selected_action == 202 && sequence_13e == 0 && frame_index_140 == 3 && frame_timer_142 == 0) {
            word_730 = 0;
            velocity_x_f4 = 10.0f;
            velocity_y_f8 = 4.0f;
            acceleration_y_100 = 0.45f;
            const float effect_y = static_cast<float>(y_f0 + 110.0);
            const float effect_x = static_cast<float>(facing_104 * 80 + x_ec);
            emit_fighter_effect(125, effect_x, effect_y, static_cast<unsigned char>(facing_104), 1);
            emit_fighter_effect(126, x_ec, static_cast<float>(y_f0 + 110.0),
                static_cast<unsigned char>(facing_104), 1);
            dispatch_indexed_event_member(31);
        }
        if (frame_counter_144 == 0 && frame_timer_142 == 0
                && frame_index_140 == 0 && sequence_13e == 2)
            face_opponent_and_flip_horizontal_velocity();
        return true;
    case 204:
        resolve_stage_surface_landing_transition();
        velocity_x_f4 = static_cast<float>(velocity_x_f4 - 0.75);
        if (velocity_x_f4 < 0.0f) {
            velocity_x_f4 = 0.0f;
            byte_47e = 0;
        }
        if (advance_frame_and_dispatch()) {
            set_action(0);
            byte_47e = 0;
        }
        return true;
