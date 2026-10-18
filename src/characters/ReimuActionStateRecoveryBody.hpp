// Shared source fragment; include only within the matching staging context.
    if (selected_action == 71 || selected_action == 74) {
        if (frame_counter_144 == 0 && frame_timer_142 == 0
                && frame_index_140 == 0 && sequence_13e == 1 && word_7a4 == 0) {
            word_7a4 = 1;
            spawn_owned_object_via_manager(951, x_ec, y_f0,
                static_cast<unsigned char>(facing_104), 1, 0, 0);
        }
    }
    if ((selected_action == 71 || selected_action == 72 || selected_action == 74)
            && sequence_13e == 1 && velocity_y_f8 < 2.0f) {
        next_sequence_block();
        return true;
    }

    if (selected_action == 74) {
        if (classify_fighter_x_boundary() && velocity_x_f4 <= -25.0) {
            set_action(76);
            return true;
        }
        if (classify_fighter_x_boundary() && velocity_x_f4 <= -15.0) {
            set_action(78);
            return true;
        }
    }
    if ((selected_action == 76 && sequence_13e > 0) || selected_action == 77)
        angle_12c = static_cast<float>(angle_12c - 30.0);
    if (selected_action != 73 && selected_action != 75) {
        velocity_y_f8 = static_cast<float>(velocity_y_f8 - acceleration_y_100);
        if (selected_action == 71 && velocity_y_f8 > 0.0f)
            velocity_y_f8 = static_cast<float>(velocity_y_f8 - acceleration_y_100);
    }

    if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
        if (selected_action >= 76)
            dispatch_indexed_event_member(22);
        // The target truncates each velocity before its wrapping WORD product.
        word_730 = static_cast<short>(static_cast<short>(static_cast<int>(velocity_x_f4)) * 100);
        word_732 = static_cast<short>(static_cast<short>(static_cast<int>(velocity_y_f8)) * 100);
        zero_velocity_acceleration();
        y_f0 = reimu_stage_surface_height_at_x(this);
        set_action(97);
        if (selected_action == 76 || selected_action == 77)
            angle_12c = 0.0f;
        publish_battle_layout_scalar(selected_action == 73 || selected_action == 75
            ? 5.0f : selected_action == 76 ? 4.0f : 2.0f);
        if (selected_action == 76 || selected_action == 77)
            reinterpret_cast<ReimuRecoverySpriteView *>(
                reinterpret_cast<unsigned char *>(this) + 4)->reset_fighter_action_scratch();
        if (selected_action < 76)
            dispatch_indexed_event_member(22);
        return true;
    }

    if (selected_action == 75) {
        if (classify_fighter_x_boundary() && velocity_x_f4 <= -25.0) {
            set_action(76);
            return true;
        }
        if (classify_fighter_x_boundary() && velocity_x_f4 <= -15.0) {
            set_action(78);
            return true;
        }
    }
    if (selected_action == 73 || selected_action == 75) {
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
        if (selected_action == 75)
            return true;
        word_730 = static_cast<short>(word_730 - 1);
        if (word_730 < 0)
            word_730 = 0;
    } else if (selected_action == 71 && word_730 > 0) {
        --word_730;
    }
    if (selected_action == 71 || selected_action == 72 || selected_action == 73) {
        if (classify_fighter_x_boundary() && velocity_x_f4 < 0.0f) {
            velocity_x_f4 = static_cast<float>(velocity_x_f4 +
                (selected_action == 73 ? 2.5 : 1.0));
            if (velocity_x_f4 > 0.0f)
                velocity_x_f4 = 0.0f;
            if (byte_490)
                field_6ac = selected_action == 72 ? velocity_x_f4
                    : static_cast<float>(word_730 * -2.0);
        }
        if (selected_action == 73)
            return true;
    }

    if (selected_action == 76 || selected_action == 78) {
        advance_frame_and_dispatch();
        if (frame_counter_144 == 0 && frame_timer_142 == 0
                && frame_index_140 == 0 && sequence_13e == 1) {
            facing_104 = static_cast<signed char>(-facing_104);
            velocity_x_f4 = selected_action == 76 ? -3.0f : -5.0f;
            velocity_y_f8 = selected_action == 76 ? 10.0f : 3.0f;
            acceleration_y_100 = 0.5f;
            if (word_7a4 == 0) {
                word_7a4 = 1;
                spawn_owned_object_via_manager(951, x_ec, y_f0,
                    static_cast<unsigned char>(facing_104), 1, 0, 0);
            }
        }
        return true;
    }
    if (selected_action == 77 && frame_counter_144 == 0 && frame_timer_142 == 0
            && frame_index_140 == 0 && sequence_13e == 1 && word_7a4 == 0) {
        word_7a4 = 1;
        spawn_owned_object_via_manager(951, x_ec, y_f0,
            static_cast<unsigned char>(facing_104), 1, 0, 0);
    }
    advance_frame_and_dispatch();
    return true;
