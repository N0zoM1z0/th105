// Shared source fragment; include only within the matching staging context.
    case 0:
    case 1:
    case 2:
    case 3: {
        resolve_stage_surface_landing_transition();
        if (selected_action == 0 && !velocity_x_f4)
            byte_47e = 0;
        if (!byte_47e) {
            zero_velocity_acceleration();
        } else {
            if (velocity_x_f4 > 0.0f) {
                velocity_x_f4 = static_cast<float>(velocity_x_f4 - 0.5);
                if (velocity_x_f4 < 0.0f) {
                    zero_velocity_acceleration();
                    byte_47e = 0;
                }
            }
            if (velocity_x_f4 < 0.0f) {
                velocity_x_f4 = static_cast<float>(velocity_x_f4 + 0.5);
                if (velocity_x_f4 > 0.0f) {
                    zero_velocity_acceleration();
                    byte_47e = 0;
                }
            }
        }
        const unsigned char completed = advance_frame_and_dispatch();
        if ((selected_action == 1 || selected_action == 3)
                && completed && frame_index_140 == 0)
            set_action(selected_action == 1 ? 2 : 0);
        return true;
    }
    case 4:
    case 5:
        resolve_stage_surface_landing_transition();
        velocity_x_f4 = selected_action == 4 ? 4.5f : -4.5f;
        advance_frame_and_dispatch();
        return true;
    case 6:
    case 7:
    case 8:
        if (sequence_13e == 0)
            resolve_stage_surface_landing_transition();
        if (sequence_13e == 0 && !byte_47e)
            zero_velocity_acceleration();
        if (sequence_13e > 0) {
            velocity_y_f8 = static_cast<float>(velocity_y_f8 - acceleration_y_100);
            if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
                set_action(10);
                y_f0 = reimu_stage_surface_height_at_x(this);
                zero_velocity_acceleration();
                return true;
            }
        }
        advance_frame_and_dispatch();
        if (frame_counter_144 == 0 && frame_timer_142 == 0
                && frame_index_140 == 0 && sequence_13e == 1) {
            velocity_x_f4 = selected_action == 6 ? 0.0f : selected_action == 7 ? 4.0f : -4.0f;
            velocity_y_f8 = 15.0f;
            acceleration_y_100 = 0.55f;
            byte_47e = 0;
        }
        return true;
    case 9:
        if (!acceleration_y_100)
            acceleration_y_100 = 0.6f;
        velocity_y_f8 = static_cast<float>(velocity_y_f8 - acceleration_y_100);
        if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
            set_action(10);
            y_f0 = reimu_stage_surface_height_at_x(this);
            zero_velocity_acceleration();
            return true;
        }
        advance_frame_and_dispatch();
        return true;
    case 10:
        resolve_stage_surface_landing_transition();
        zero_velocity_acceleration();
        if (advance_frame_and_dispatch()) {
            if (field_6b8 == 0)
                set_action(0);
            else
                set_action(2);
        }
        return true;
