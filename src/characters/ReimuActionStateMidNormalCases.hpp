// Shared source fragment for the first middle-table group; no function boundary.
    case 301:
        resolve_stage_surface_landing_transition();
        if (try_dispatch_directional_action_208_210(0))
            return true;
        if (byte_47e != 0) {
            velocity_x_f4 = static_cast<float>(velocity_x_f4 - 0.5);
            if (velocity_x_f4 < 0.0f) {
                velocity_x_f4 = 0.0f;
                byte_47e = 0;
            }
        }
        if (frame_index_140 > 4) {
            velocity_x_f4 = static_cast<float>(velocity_x_f4 - 1.5);
            if (velocity_x_f4 < 0.0f)
                velocity_x_f4 = 0.0f;
        }
        if (advance_frame_and_dispatch())
            set_action(0);
        if (frame_timer_142 == 0 && frame_index_140 == 4) {
            dispatch_indexed_event_member(27);
            velocity_x_f4 = 5.0f;
            byte_47e = 0;
        }
        return true;
    case 302:
        resolve_stage_surface_landing_transition();
        if (try_dispatch_directional_action_208_210(1))
            return true;
        if (frame_index_140 < 4 && field_6bc == 0)
            byte_750 = 0;
        if (velocity_x_f4 > 0.0f)
            velocity_x_f4 = static_cast<float>(velocity_x_f4 - 1.5);
        if (velocity_x_f4 < 0.0f)
            velocity_x_f4 = 0.0f;
        if (advance_frame_and_dispatch())
            set_action(0);
        if (frame_counter_144 == 0 && frame_timer_142 == 0
                && frame_index_140 == 0 && sequence_13e == 1)
            set_action(0);
        if (sequence_13e == 0 && frame_timer_142 == 0) {
            if (frame_index_140 == 3) {
                if (byte_750 == 1) {
                    next_sequence_block();
                    emit_fighter_effect(62,
                        static_cast<float>(static_cast<float>(facing_104 * 40) + x_ec),
                        static_cast<float>(y_f0 + 70.0),
                        static_cast<unsigned char>(facing_104), 1);
                    return true;
                }
                velocity_x_f4 = 20.0f;
            }
            if (frame_timer_142 == 0 && frame_index_140 == 4) {
                dispatch_indexed_event_member(28);
                const float parameters[3] = {0.0f, 0.0f, 1.0f};
                spawn_owned_object_via_manager(848,
                    static_cast<float>(static_cast<float>(facing_104 * 130) + x_ec),
                    static_cast<float>(y_f0 + 80.0),
                    static_cast<unsigned char>(facing_104), 1, parameters, 3);
            }
        }
        if (sequence_13e == 1 && frame_timer_142 == 0) {
            if (frame_index_140 == 1)
                velocity_x_f4 = 20.0f;
            if (frame_timer_142 == 0 && frame_index_140 == 1) {
                dispatch_indexed_event_member(28);
                const float parameters[3] = {0.0f, 0.0f, 1.0f};
                spawn_owned_object_via_manager(848,
                    static_cast<float>(static_cast<float>(facing_104 * 130) + x_ec),
                    static_cast<float>(y_f0 + 80.0),
                    static_cast<unsigned char>(facing_104), 1, parameters, 3);
            }
        }
        return true;
    case 303:
        resolve_stage_surface_landing_transition();
        if (try_dispatch_directional_action_208_210(0))
            return true;
        if (static_cast<signed char>(byte_47e) > 0) {
            velocity_x_f4 = static_cast<float>(velocity_x_f4 - static_cast<double>(0.6f));
            if (velocity_x_f4 < 0.0f) {
                velocity_x_f4 = 0.0f;
                byte_47e = 0;
            }
        }
        if (advance_frame_and_dispatch())
            set_action(2);
        if (frame_timer_142 == 0 && frame_index_140 < 12)
            state_180 = 0;
        if (frame_timer_142 == 0 && frame_index_140 == 3)
            dispatch_indexed_event_member(27);
        if (frame_timer_142 == 0 && frame_index_140 == 5)
            dispatch_indexed_event_member(27);
        if (frame_timer_142 == 0 && frame_index_140 == 7)
            dispatch_indexed_event_member(27);
        if (frame_timer_142 == 0 && frame_index_140 == 9)
            dispatch_indexed_event_member(27);
        return true;
    case 304:
        if (sequence_13e == 0 || sequence_13e == 2
                || sequence_13e == 5 || sequence_13e == 6)
            resolve_stage_surface_landing_transition();
        if (field_6bc == 0)
            byte_750 = 0;
        if (sequence_13e == 1) {
            velocity_y_f8 = static_cast<float>(velocity_y_f8 - acceleration_y_100);
            if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
                velocity_y_f8 = 0.0f;
                acceleration_y_100 = 0.0f;
                y_f0 = reimu_stage_surface_height_at_x(this);
                set_sequence(2);
            }
        }
        if (sequence_13e == 2) {
            velocity_x_f4 = static_cast<float>(velocity_x_f4 - 1.5);
            if (velocity_x_f4 < 0.0f)
                velocity_x_f4 = 0.0f;
        }
        if (sequence_13e == 4) {
            velocity_y_f8 = static_cast<float>(velocity_y_f8 - acceleration_y_100);
            if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
                velocity_y_f8 = 0.0f;
                y_f0 = reimu_stage_surface_height_at_x(this);
                set_sequence(5);
                dispatch_indexed_event_member(29);
            }
        }
        if (sequence_13e == 5 && frame_counter_144 >= 12) {
            next_sequence_block();
            return true;
        }
        if (sequence_13e == 6) {
            velocity_x_f4 = static_cast<float>(velocity_x_f4 - 1.0);
            if (velocity_x_f4 < 0.0f) {
                velocity_x_f4 = 0.0f;
                byte_47e = 0;
            }
        }
        if (velocity_x_f4 > 14.0f)
            velocity_x_f4 = static_cast<float>(velocity_x_f4 - 0.5);
        if (advance_frame_and_dispatch())
            set_action(0);
        if (frame_counter_144 == 0 && frame_timer_142 == 0
                && frame_index_140 == 0 && sequence_13e == 1) {
            if (byte_750 == 1) {
                set_sequence(3);
                emit_fighter_effect(62, static_cast<float>(x_ec + 0.0),
                    static_cast<float>(y_f0 + 50.0),
                    static_cast<unsigned char>(facing_104), 1);
                return true;
            }
            byte_47e = 0;
            dispatch_indexed_event_member(28);
            velocity_x_f4 = 10.0f;
            velocity_y_f8 = 12.0f;
            acceleration_y_100 = 0.75f;
        }
        if (frame_counter_144 == 0 && frame_timer_142 == 0
                && frame_index_140 == 0 && sequence_13e == 3) {
            set_action(0);
            return true;
        }
        if (frame_counter_144 == 0 && frame_timer_142 == 0
                && frame_index_140 == 0 && sequence_13e == 4) {
            velocity_x_f4 = 18.0f;
            velocity_y_f8 = 5.0f;
            acceleration_y_100 = 1.0f;
        }
        return true;
    case 305:
        resolve_stage_surface_landing_transition();
        if (try_dispatch_directional_action_208_210(1))
            return true;
        if (frame_index_140 > 4 && velocity_x_f4 > 0.0f)
            velocity_x_f4 = static_cast<float>(velocity_x_f4 - 1.0);
        if (velocity_x_f4 < 0.0f)
            velocity_x_f4 = 0.0f;
        if (advance_frame_and_dispatch())
            set_action(0);
        if (frame_timer_142 == 0 && frame_index_140 == 3)
            velocity_x_f4 = 10.0f;
        if (frame_timer_142 == 0 && frame_index_140 == 4)
            dispatch_indexed_event_member(27);
        return true;
    case 306: case 307: case 308: case 309:
        velocity_y_f8 = static_cast<float>(velocity_y_f8 - acceleration_y_100);
        if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
            set_action(10);
            y_f0 = reimu_stage_surface_height_at_x(this);
            zero_velocity_acceleration();
            return true;
        }
        if (selected_action == 306 && sequence_13e == 1 && frame_counter_144 > 12)
            next_sequence_block();
        if (selected_action == 307 && frame_index_140 > 2) {
            velocity_x_f4 = static_cast<float>(velocity_x_f4 - 0.5);
            if (velocity_x_f4 < 6.0f)
                velocity_x_f4 = 6.0f;
        }
        if (advance_frame_and_dispatch())
            set_action(9);
        if (selected_action == 306 && sequence_13e == 0
                && frame_index_140 == 1 && frame_timer_142 == 0) {
            dispatch_indexed_event_member(27);
            const float parameters[3] = {0.0f, 0.0f, 3.0f};
            spawn_owned_object_via_manager(848,
                static_cast<float>(static_cast<float>(facing_104 * 150) + x_ec),
                static_cast<float>(y_f0 + 65.0),
                static_cast<unsigned char>(facing_104), 1, parameters, 3);
        }
        if (selected_action == 307 && frame_timer_142 == 0 && frame_index_140 == 2) {
            dispatch_indexed_event_member(29);
            velocity_x_f4 = 15.0f;
            velocity_y_f8 = 5.0f;
            acceleration_y_100 = 0.35f;
        }
        if (selected_action == 308) {
            if (frame_timer_142 == 0 && frame_index_140 == 4) {
                dispatch_indexed_event_member(29);
                const float parameters[3] = {0.0f, 0.0f, 5.0f};
                spawn_owned_object_via_manager(848, x_ec, y_f0,
                    static_cast<unsigned char>(facing_104), 1, parameters, 3);
            }
            if (sequence_13e == 1 && frame_counter_144 > 10)
                next_sequence_block();
        }
        if (selected_action == 309 && frame_timer_142 == 0 && frame_index_140 == 2) {
            dispatch_indexed_event_member(29);
            velocity_x_f4 = 5.0f;
            velocity_y_f8 = 15.0f;
            acceleration_y_100 = 0.9f;
        }
        return true;
    case 310:
        if (state_180 != 0) {
            word_730 = static_cast<short>(word_730 + 1);
            if (word_730 > 5) {
                state_180 = 0;
                word_730 = 0;
            }
        }
        if (sequence_13e == 1) {
            velocity_y_f8 = static_cast<float>(velocity_y_f8 - acceleration_y_100 * 0.5);
            angle_12c = static_cast<float>(angle_12c + 40.0);
            if (frame_counter_144 % 15 == 0)
                dispatch_indexed_event_member(27);
            if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
                velocity_y_f8 = 0.0f;
                y_f0 = reimu_stage_surface_height_at_x(this);
                next_sequence_block();
                angle_12c = 0.0f;
                return true;
            }
        }
        if (sequence_13e == 2) {
            velocity_x_f4 = static_cast<float>(velocity_x_f4 - 1.0);
            if (velocity_x_f4 < 0.0f)
                velocity_x_f4 = 0.0f;
        }
        if (advance_frame_and_dispatch())
            set_action(0);
        return true;
    case 320:
        resolve_stage_surface_landing_transition();
        if (try_dispatch_directional_action_208_210(0))
            return true;
        if (byte_47e != 0) {
            velocity_x_f4 = static_cast<float>(velocity_x_f4 - 0.5);
            if (velocity_x_f4 < 0.0f) {
                velocity_x_f4 = 0.0f;
                byte_47e = 0;
            }
        }
        if (advance_frame_and_dispatch())
            set_action(0);
        if (frame_timer_142 == 0 && frame_index_140 == 3) {
            dispatch_indexed_event_member(27);
            byte_47e = 0;
        }
        return true;
    case 321:
        resolve_stage_surface_landing_transition();
        if (try_dispatch_directional_action_208_210(0))
            return true;
        if (frame_index_140 > 1) {
            velocity_x_f4 = static_cast<float>(velocity_x_f4 - 2.0);
            if (velocity_x_f4 < 0.0f)
                velocity_x_f4 = 0.0f;
        }
        if (advance_frame_and_dispatch())
            set_action(0);
        if (frame_timer_142 == 0 && frame_index_140 == 2) {
            dispatch_indexed_event_member(28);
            byte_47e = 0;
        }
        return true;
    case 322:
        resolve_stage_surface_landing_transition();
        if (try_dispatch_directional_action_208_210(1))
            return true;
        if (velocity_x_f4 > 0.0f)
            velocity_x_f4 = static_cast<float>(velocity_x_f4 - 0.75);
        if (velocity_x_f4 < 0.0f)
            velocity_x_f4 = 0.0f;
        if (advance_frame_and_dispatch())
            set_action(0);
        if (frame_counter_144 == 0 && frame_timer_142 == 0
                && frame_index_140 == 0 && sequence_13e == 1)
            set_action(0);
        if (sequence_13e == 0 && frame_timer_142 == 0) {
            if (frame_index_140 == 3)
                velocity_x_f4 = 17.5f;
            if (frame_timer_142 == 0 && frame_index_140 == 5)
                dispatch_indexed_event_member(28);
        }
        return true;
