// Late high-table actions; continuation of the same dispatcher.
    case 650: case 651: {
        if (sequence_13e == 4)
            resolve_stage_surface_landing_transition();
        publish_texture_state(6, 2);
        if (sequence_13e == 1 && frame_counter_144 > (selected_action == 650 ? 30 : 60)) {
            next_sequence_block();
            return true;
        }
        if (selected_action == 650 && sequence_13e > 1 && sequence_13e < 4) {
            velocity_y_f8 -= acceleration_y_100;
            if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
                y_f0 = reimu_stage_surface_height_at_x(this);
                zero_velocity_acceleration();
                set_sequence(4);
                return true;
            }
        }
        if (sequence_13e == 1 && word_730 < (selected_action == 650 ? 5 : 10)
                && frame_counter_144 % 5 == 0) {
            dispatch_character_wave_handle(8);
            float parameters[3] = {
                selected_action == 650 ? static_cast<float>((word_730 - 2) * 30)
                    : static_cast<float>(word_730 * -45.0),
                0.0f, static_cast<float>(word_730 % 3)};
            spawn_owned_object_via_manager(selected_action == 650 ? 850 : 853,
                static_cast<float>(static_cast<float>(facing_104 * 18) + x_ec),
                static_cast<float>(y_f0 + 120.0),
                static_cast<unsigned char>(facing_104), 1, parameters, 3);
            if (selected_action == 651) {
                parameters[0] = 0.0f;
                parameters[1] = 0.0f;
                spawn_owned_object_via_manager(860,
                    static_cast<float>(static_cast<float>(facing_104 * 18) + x_ec),
                    static_cast<float>(y_f0 + 120.0),
                    static_cast<unsigned char>(facing_104), 1, parameters, 3);
            }
            word_730 = static_cast<short>(word_730 + 1);
        }
        if (selected_action == 651 && sequence_13e > 1 && sequence_13e < 4) {
            velocity_y_f8 -= acceleration_y_100;
            if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
                y_f0 = reimu_stage_surface_height_at_x(this);
                zero_velocity_acceleration();
                set_sequence(4);
                return true;
            }
        }
        if (advance_frame_and_dispatch())
            set_action(0);
        if (sequence_13e == 0 && frame_index_140 == 2 && frame_timer_142 == 0) {
            set_word_48a(40);
            dispatch_indexed_event_member(23);
            emit_fighter_effect(115, static_cast<float>(x_ec - facing_104 * 2),
                static_cast<float>(y_f0 + 120.0), static_cast<unsigned char>(facing_104), 1);
            dispatch_indexed_sequence_window_45c8b0(0, selected_action == 650 ? 2 : 5, 60);
            advance_secondary_event_effect_cycle();
        }
        return true;
    }
    case 658:
        if (sequence_13e == 3)
            resolve_stage_surface_landing_transition();
        publish_texture_state(6, 2);
        if (sequence_13e == 1 && frame_counter_144 > 20) {
            next_sequence_block();
            return true;
        }
        velocity_y_f8 -= acceleration_y_100;
        if (sequence_13e < 3) {
            if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
                y_f0 = reimu_stage_surface_height_at_x(this);
                zero_velocity_acceleration();
                set_sequence(3);
                return true;
            }
        }
        if (advance_frame_and_dispatch())
            set_action(0);
        if (sequence_13e == 0 && frame_timer_142 == 0) {
            if (frame_index_140 == 4) {
                dispatch_indexed_sequence_window_45c8b0(0, 1, 60);
                advance_secondary_event_effect_cycle();
                set_word_48a(40);
                dispatch_indexed_event_member(23);
                emit_fighter_effect(115, static_cast<float>(static_cast<float>(facing_104 * 24) + x_ec),
                    static_cast<float>(y_f0 + 144.0), static_cast<unsigned char>(facing_104), 1);
            }
            if (frame_timer_142 == 0 && frame_index_140 == 5) {
                velocity_x_f4 = -2.0f;
                velocity_y_f8 = 7.5f;
                acceleration_y_100 = 0.3f;
            }
            if (frame_timer_142 == 0 && frame_index_140 == 10)
                word_730 = 1;
        }
        if (frame_counter_144 == 0 && frame_timer_142 == 0 && frame_index_140 == 0 && sequence_13e == 3)
            set_action(9);
        if (word_730 > 0) {
            word_732 = static_cast<short>(word_732 - 1);
            if (word_732 <= 0 && word_734 < 3) {
                float parameters[3] = {static_cast<float>(word_734 * 10.0 - 80.0), 0.0f, 0.0f};
                spawn_owned_object_via_manager(858,
                    static_cast<float>(static_cast<float>(facing_104 * 78) + x_ec),
                    static_cast<float>(y_f0 + 120.0),
                    static_cast<unsigned char>(facing_104), 1, parameters, 3);
                parameters[0] = 0.0f;
                parameters[1] = 0.0f;
                parameters[2] = 2.0f;
                spawn_owned_object_via_manager(858,
                    static_cast<float>(static_cast<float>(facing_104 * 78) + x_ec),
                    static_cast<float>(y_f0 + 120.0),
                    static_cast<unsigned char>(facing_104), 1, parameters, 3);
                dispatch_character_wave_handle(11);
                word_732 = 6;
                word_734 = static_cast<short>(word_734 + 1);
            }
        }
        return true;
    case 669:
        publish_texture_state(6, 2);
        if (sequence_13e == 1) {
            if (frame_counter_144 >= 240) {
                next_sequence_block();
                acceleration_y_100 = 0.2f;
                return true;
            }
            if (frame_counter_144 <= 180) {
                if (frame_counter_144 % 2 == 0) {
                    float parameters[3];
                    for (float i = 0.0f; i < 3.0f; i += 1.0f) {
                        parameters[0] = static_cast<float>(i * 120.0 + field_73c);
                        parameters[1] = 30.0f;
                        parameters[2] = 3.0f;
                        spawn_owned_object_via_manager(869,
                            static_cast<float>(lookup_orientation_cosine_quantized_abs(-parameters[0])
                                * 80.0 * facing_104 + x_ec),
                            static_cast<float>(lookup_orientation_sine_quantized_abs(-parameters[0])
                                * 80.0 + (static_cast<double>(y_f0) + 100.0)),
                            static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    }
                    for (float i = 0.0f; i < 4.0f; i += 1.0f) {
                        parameters[0] = static_cast<float>(i * 90.0 - field_73c);
                        parameters[1] = 30.0f;
                        parameters[2] = 3.0f;
                        spawn_owned_object_via_manager(869,
                            static_cast<float>(lookup_orientation_cosine_quantized_abs(-parameters[0])
                                * 80.0 * facing_104 + x_ec),
                            static_cast<float>(lookup_orientation_sine_quantized_abs(-parameters[0])
                                * 80.0 + (static_cast<double>(y_f0) + 100.0)),
                            static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    }
                    field_73c = static_cast<float>(field_73c + 4.0);
                }
                if (frame_counter_144 % 8 == 0) {
                    const float parameters[3] = {0.0f, 0.0f, 4.0f};
                    spawn_owned_object_via_manager(869, x_ec, static_cast<float>(y_f0 + 100.0),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                }
                if (frame_counter_144 % 10 == 0) {
                    const float parameters[3] = {
                        static_cast<float>(static_cast<unsigned int>(selector_random_roll(360))), 0.0f, 5.0f};
                    spawn_owned_object_via_manager(869, x_ec, static_cast<float>(y_f0 + 100.0),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                }
            }
        }
        if (sequence_13e == 2 || sequence_13e == 3) {
            velocity_y_f8 -= acceleration_y_100;
            if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
                zero_velocity_acceleration();
                y_f0 = reimu_stage_surface_height_at_x(this);
                set_sequence(4);
                return true;
            }
        }
        if (advance_frame_and_dispatch()) {
            set_action(0);
            return true;
        }
        if (frame_counter_144 == 0 && frame_timer_142 == 0 && frame_index_140 == 0 && sequence_13e == 1) {
            dispatch_character_wave_handle(24);
            publish_battle_layout_scalar(8.0f);
        }
        if (sequence_13e == 0 && frame_timer_142 == 0 && frame_index_140 == 2) {
            advance_secondary_event_effect_cycle();
            set_word_48a(40);
            dispatch_indexed_event_member(23);
            emit_fighter_effect(115, x_ec, static_cast<float>(y_f0 + 120.0),
                static_cast<unsigned char>(facing_104), 1);
            timer_7c8 = 0;
            count_7ca = 0;
            latch_7cc = 0;
        }
        return true;
    case 695:
        resolve_stage_surface_landing_transition();
        if (advance_frame_and_dispatch())
            set_action(0);
        if (sequence_13e == 0 && frame_timer_142 == 0 && frame_index_140 == 6) {
            dispatch_indexed_event_member(55);
            emit_fighter_effect(140, x_ec, static_cast<float>(y_f0 + 100.0),
                static_cast<unsigned char>(facing_104), 1);
            emit_fighter_effect(140, x_ec, static_cast<float>(y_f0 + 100.0),
                static_cast<unsigned char>(facing_104), 1);
            emit_fighter_effect(140, x_ec, static_cast<float>(y_f0 + 100.0),
                static_cast<unsigned char>(facing_104), 1);
            emit_fighter_effect(141, x_ec, static_cast<float>(y_f0 + 100.0),
                static_cast<unsigned char>(facing_104), -1);
            emit_fighter_effect(142, x_ec, y_f0, static_cast<unsigned char>(facing_104), -1);
        }
        return true;
    case 696:
        resolve_stage_surface_landing_transition();
        if (velocity_x_f4 > 0.0f)
            velocity_x_f4 = static_cast<float>(velocity_x_f4 - 1.5);
        if (velocity_x_f4 < 0.0f)
            velocity_x_f4 = 0.0f;
        if (advance_frame_and_dispatch())
            set_action(0);
        if (sequence_13e == 0 && frame_timer_142 == 0) {
            if (frame_index_140 == 3)
                velocity_x_f4 = 20.0f;
            if (frame_timer_142 == 0 && frame_index_140 == 4)
                dispatch_indexed_event_member(28);
        }
        return true;
    case 710: case 711:
        if (sequence_13e == 6)
            resolve_stage_surface_landing_transition();
        if (sequence_13e >= 1 && sequence_13e <= 5) {
            velocity_y_f8 -= acceleration_y_100;
            if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
                y_f0 = reimu_stage_surface_height_at_x(this);
                zero_velocity_acceleration();
                set_sequence(6);
                dispatch_indexed_event_member(30);
                return true;
            }
        }
        if (advance_frame_and_dispatch())
            set_action(700);
        if (frame_counter_144 == 0 && frame_timer_142 == 0 && frame_index_140 == 0 && sequence_13e == 1) {
            velocity_x_f4 = field_780;
            velocity_y_f8 = field_784;
            acceleration_y_100 = field_788;
        }
        if (sequence_13e == 3 && frame_counter_144 >= 20) {
            next_sequence_block();
            velocity_x_f4 = static_cast<float>(velocity_x_f4 * 0.25);
            velocity_y_f8 = static_cast<float>(velocity_y_f8 * 0.25);
            acceleration_y_100 = selected_action == 710 ? 0.1f : 0.0f;
            return true;
        }
        if (sequence_13e == 4 && frame_timer_142 == 0) {
            if (frame_index_140 == 1) {
                dispatch_character_wave_handle(4);
                const unsigned int mode = static_cast<unsigned int>(g_match_identifier);
                float parameters[3];
                if (selected_action == 710) {
                    switch (mode) {
                    case 3:
                        for (float i = 0.0f; i < 8.0f; i += 1.0f) {
                            parameters[0] = static_cast<float>(
                                i * 45.0 + (-static_cast<double>(atan2_degrees(
                                    static_cast<float>(static_cast<double>(peer_170->y_f0) - y_f0),
                                    static_cast<float>((static_cast<double>(peer_170->x_ec) - x_ec) * facing_104)))));
                            parameters[1] = 4.0f;
                            parameters[2] = 0.0f;
                            spawn_owned_object_via_manager(900,
                                static_cast<float>(lookup_orientation_cosine_quantized_abs(-parameters[0])
                                    * 100.0 * facing_104 + x_ec),
                                static_cast<float>(lookup_orientation_sine_quantized_abs(-parameters[0])
                                    * 100.0 + y_f0 + 100.0),
                                static_cast<unsigned char>(facing_104), 1, parameters, 3);
                        }
                        break;
                    case 2:
                        for (float i = 0.0f; i < 6.0f; i += 1.0f) {
                            parameters[0] = static_cast<float>(
                                i * 60.0 + (-static_cast<double>(atan2_degrees(
                                    static_cast<float>(static_cast<double>(peer_170->y_f0) - y_f0),
                                    static_cast<float>((static_cast<double>(peer_170->x_ec) - x_ec) * facing_104)))));
                            parameters[1] = 4.0f;
                            parameters[2] = 0.0f;
                            spawn_owned_object_via_manager(900,
                                static_cast<float>(lookup_orientation_cosine_quantized_abs(-parameters[0])
                                    * 100.0 * facing_104 + x_ec),
                                static_cast<float>(lookup_orientation_sine_quantized_abs(-parameters[0])
                                    * 100.0 + y_f0 + 100.0),
                                static_cast<unsigned char>(facing_104), 1, parameters, 3);
                        }
                        break;
                    case 1:
                        for (float i = 0.0f; i < 4.0f; i += 1.0f) {
                            parameters[0] = static_cast<float>(
                                i * 90.0 + (-static_cast<double>(atan2_degrees(
                                    static_cast<float>(static_cast<double>(peer_170->y_f0) - y_f0),
                                    static_cast<float>((static_cast<double>(peer_170->x_ec) - x_ec) * facing_104)))));
                            parameters[1] = 4.0f;
                            parameters[2] = 0.0f;
                            spawn_owned_object_via_manager(900,
                                static_cast<float>(lookup_orientation_cosine_quantized_abs(-parameters[0])
                                    * 100.0 * facing_104 + x_ec),
                                static_cast<float>(lookup_orientation_sine_quantized_abs(-parameters[0])
                                    * 100.0 + y_f0 + 100.0),
                                static_cast<unsigned char>(facing_104), 1, parameters, 3);
                        }
                        break;
                    case 0:
                        for (float i = 0.0f; i < 3.0f; i += 1.0f) {
                            parameters[0] = static_cast<float>(
                                i * 120.0 + (-static_cast<double>(atan2_degrees(
                                    static_cast<float>(static_cast<double>(peer_170->y_f0) - y_f0),
                                    static_cast<float>((static_cast<double>(peer_170->x_ec) - x_ec) * facing_104)))));
                            parameters[1] = 4.0f;
                            parameters[2] = 0.0f;
                            spawn_owned_object_via_manager(900,
                                static_cast<float>(lookup_orientation_cosine_quantized_abs(-parameters[0])
                                    * 100.0 * facing_104 + x_ec),
                                static_cast<float>(lookup_orientation_sine_quantized_abs(-parameters[0])
                                    * 100.0 + y_f0 + 100.0),
                                static_cast<unsigned char>(facing_104), 1, parameters, 3);
                        }
                        break;
                    default:
                        break;
                    }
                } else {
                    switch (mode) {
                    case 3:
                        for (float i = 0.0f; i < 6.0f; i += 1.0f) {
                            parameters[0] = static_cast<float>(
                                i * 36.0 + (-static_cast<double>(atan2_degrees(
                                    static_cast<float>(static_cast<double>(peer_170->y_f0) - y_f0),
                                    static_cast<float>((static_cast<double>(peer_170->x_ec) - x_ec) * facing_104))) - 90.0));
                            parameters[1] = 4.0f;
                            parameters[2] = 0.0f;
                            spawn_owned_object_via_manager(900,
                                static_cast<float>(lookup_orientation_cosine_quantized_abs(-parameters[0])
                                    * 100.0 * facing_104 + x_ec),
                                static_cast<float>(lookup_orientation_sine_quantized_abs(-parameters[0])
                                    * 100.0 + y_f0 + 100.0),
                                static_cast<unsigned char>(facing_104), 1, parameters, 3);
                        }
                        break;
                    case 2:
                        for (float i = 0.0f; i < 5.0f; i += 1.0f) {
                            parameters[0] = static_cast<float>(
                                i * 45.0 + (-static_cast<double>(atan2_degrees(
                                    static_cast<float>(static_cast<double>(peer_170->y_f0) - y_f0),
                                    static_cast<float>((static_cast<double>(peer_170->x_ec) - x_ec) * facing_104))) - 90.0));
                            parameters[1] = 4.0f;
                            parameters[2] = 0.0f;
                            spawn_owned_object_via_manager(900,
                                static_cast<float>(lookup_orientation_cosine_quantized_abs(-parameters[0])
                                    * 100.0 * facing_104 + x_ec),
                                static_cast<float>(lookup_orientation_sine_quantized_abs(-parameters[0])
                                    * 100.0 + y_f0 + 100.0),
                                static_cast<unsigned char>(facing_104), 1, parameters, 3);
                        }
                        break;
                    case 1:
                        for (float i = 0.0f; i < 4.0f; i += 1.0f) {
                            parameters[0] = static_cast<float>(
                                i * 60.0 + (-static_cast<double>(atan2_degrees(
                                    static_cast<float>(static_cast<double>(peer_170->y_f0) - y_f0),
                                    static_cast<float>((static_cast<double>(peer_170->x_ec) - x_ec) * facing_104))) - 90.0));
                            parameters[1] = 4.0f;
                            parameters[2] = 0.0f;
                            spawn_owned_object_via_manager(900,
                                static_cast<float>(lookup_orientation_cosine_quantized_abs(-parameters[0])
                                    * 100.0 * facing_104 + x_ec),
                                static_cast<float>(lookup_orientation_sine_quantized_abs(-parameters[0])
                                    * 100.0 + y_f0 + 100.0),
                                static_cast<unsigned char>(facing_104), 1, parameters, 3);
                        }
                        break;
                    case 0:
                        for (float i = 0.0f; i < 3.0f; i += 1.0f) {
                            parameters[0] = static_cast<float>(
                                i * 60.0 + (-static_cast<double>(atan2_degrees(
                                    static_cast<float>(static_cast<double>(peer_170->y_f0) - y_f0),
                                    static_cast<float>((static_cast<double>(peer_170->x_ec) - x_ec) * facing_104))) - 60.0));
                            parameters[1] = 4.0f;
                            parameters[2] = 0.0f;
                            spawn_owned_object_via_manager(900,
                                static_cast<float>(lookup_orientation_cosine_quantized_abs(-parameters[0])
                                    * 100.0 * facing_104 + x_ec),
                                static_cast<float>(lookup_orientation_sine_quantized_abs(-parameters[0])
                                    * 100.0 + y_f0 + 100.0),
                                static_cast<unsigned char>(facing_104), 1, parameters, 3);
                        }
                        break;
                    default:
                        break;
                    }
                }
            }
            if (frame_timer_142 == 0 && frame_index_140 == 3)
                acceleration_y_100 = 0.1f;
        }
        return true;
