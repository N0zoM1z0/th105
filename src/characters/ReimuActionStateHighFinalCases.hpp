// Final high-table families; continuation of the same staged dispatcher.
    case 720:
        if ((sequence_13e == 0 && frame_index_140 <= 3) || sequence_13e == 6)
            resolve_stage_surface_landing_transition();
        if (sequence_13e == 0 && frame_index_140 > 3) {
            if (scale_11c > 0.0f) {
                scale_11c = static_cast<float>(scale_11c - static_cast<double>(0.1f));
                scale_120 = static_cast<float>(scale_120 + static_cast<double>(0.2f));
            }
            if (byte_113 > 25)
                byte_113 = static_cast<unsigned char>(byte_113 - 25);
        }
        if (sequence_13e == 1) {
            scale_11c = 1.0f;
            scale_120 = 1.0f;
            byte_113 = 0;
        }
        if (sequence_13e == 2)
            byte_113 = byte_113 <= 235 ? static_cast<unsigned char>(byte_113 + 20) : 255;
        if (sequence_13e == 3) {
            if (frame_counter_144 == 90) {
                word_730 = 1;
                dispatch_character_wave_handle(8);
            }
            if (frame_counter_144 == 120) {
                next_sequence_block();
                acceleration_y_100 = 0.25f;
                return true;
            }
        }
        if (sequence_13e == 4 || sequence_13e == 5) {
            velocity_y_f8 -= acceleration_y_100;
            if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
                zero_velocity_acceleration();
                y_f0 = reimu_stage_surface_height_at_x(this);
                set_sequence(6);
                return true;
            }
        }
        if (advance_frame_and_dispatch())
            set_action(700);
        if (frame_counter_144 == 0 && frame_timer_142 == 0 && frame_index_140 == 0) {
            if (sequence_13e == 2) {
                x_ec = static_cast<float>(static_cast<unsigned int>(selector_random_roll(800)) + 240.0);
                y_f0 = static_cast<float>(static_cast<unsigned int>(selector_random_roll(250)) + 100.0);
            }
            if (frame_counter_144 == 0 && frame_timer_142 == 0 && frame_index_140 == 0 && sequence_13e == 3) {
                dispatch_character_wave_handle(13);
                const unsigned int mode = static_cast<unsigned int>(g_match_identifier);
                float parameters[4];
                switch (mode) {
                case 3: {
                    const float base = static_cast<float>(static_cast<unsigned int>(selector_random_roll(360)));
                    for (float i = 0.0f; i < 8.0f; i += 1.0f) {
                        parameters[0] = static_cast<float>(i * 45.0 + base);
                        parameters[1] = 10.0f;
                        parameters[2] = 0.0f;
                        parameters[3] = 3.0f;
                        spawn_owned_object_via_manager(901, x_ec, static_cast<float>(y_f0 + 100.0),
                            static_cast<unsigned char>(facing_104), 1, parameters, 4);
                    }
                    break;
                }
                case 2: {
                    const float base = static_cast<float>(static_cast<unsigned int>(selector_random_roll(360)));
                    for (float i = 0.0f; i < 6.0f; i += 1.0f) {
                        parameters[0] = static_cast<float>(i * 60.0 + base);
                        parameters[1] = 10.0f;
                        parameters[2] = 0.0f;
                        parameters[3] = 2.0f;
                        spawn_owned_object_via_manager(901, x_ec, static_cast<float>(y_f0 + 100.0),
                            static_cast<unsigned char>(facing_104), 1, parameters, 4);
                    }
                    break;
                }
                case 1: {
                    const float base = static_cast<float>(static_cast<unsigned int>(selector_random_roll(360)));
                    for (float i = 0.0f; i < 4.0f; i += 1.0f) {
                        parameters[0] = static_cast<float>(i * 90.0 + base);
                        parameters[1] = 10.0f;
                        parameters[2] = 0.0f;
                        parameters[3] = 2.0f;
                        spawn_owned_object_via_manager(901, x_ec, static_cast<float>(y_f0 + 100.0),
                            static_cast<unsigned char>(facing_104), 1, parameters, 4);
                    }
                    break;
                }
                case 0: {
                    const float base = static_cast<float>(static_cast<unsigned int>(selector_random_roll(360)));
                    for (float i = 0.0f; i < 3.0f; i += 1.0f) {
                        parameters[0] = static_cast<float>(i * 120.0 + base);
                        parameters[1] = 10.0f;
                        parameters[2] = 0.0f;
                        parameters[3] = 1.0f;
                        spawn_owned_object_via_manager(901, x_ec, static_cast<float>(y_f0 + 100.0),
                            static_cast<unsigned char>(facing_104), 1, parameters, 4);
                    }
                    break;
                }
                }
            }
        }
        return true;
    case 730: case 760:
        if (advance_frame_and_dispatch())
            set_action(700);
        if (frame_counter_144 == 0 && frame_timer_142 == 0 && frame_index_140 == 0 && sequence_13e == 1) {
            velocity_x_f4 = static_cast<float>((640.0 - x_ec) / 60.0 * facing_104);
            velocity_y_f8 = 17.5f;
            acceleration_y_100 = 0.45f;
        }
        if (sequence_13e == 1 || sequence_13e == 2)
            velocity_y_f8 -= acceleration_y_100;
        if (frame_counter_144 == 0 && frame_timer_142 == 0 && frame_index_140 == 0 && sequence_13e == 3) {
            x_ec = 640.0f;
            dispatch_character_wave_handle(9);
            zero_velocity_acceleration();
            if (selected_action == 730) {
                float parameters[3] = {0.0f, 0.0f, 0.0f};
                spawn_owned_object_via_manager(902, x_ec, static_cast<float>(y_f0 + 100.0),
                    1, 1, parameters, 3);
                if (g_match_identifier == 2 || g_match_identifier == 3) {
                    parameters[0] = 0.0f;
                    parameters[1] = 0.0f;
                    parameters[2] = 1.0f;
                    spawn_owned_object_via_manager(902, x_ec, static_cast<float>(y_f0 + 100.0),
                        -1, 1, parameters, 3);
                }
            } else {
                float parameters[3] = {0.0f, 1.0f, 0.0f};
                spawn_owned_object_via_manager(905, x_ec, static_cast<float>(y_f0 + 100.0),
                    1, 1, parameters, 3);
                parameters[0] = 0.0f; parameters[1] = -1.5f; parameters[2] = 0.0f;
                spawn_owned_object_via_manager(906, x_ec, static_cast<float>(y_f0 + 100.0),
                    1, 1, parameters, 3);
                parameters[0] = 0.0f; parameters[1] = 2.0f; parameters[2] = 0.0f;
                spawn_owned_object_via_manager(907, x_ec, static_cast<float>(y_f0 + 100.0),
                    1, 1, parameters, 3);
                parameters[0] = 0.0f; parameters[1] = -2.5f; parameters[2] = 0.0f;
                spawn_owned_object_via_manager(908, x_ec, static_cast<float>(y_f0 + 100.0),
                    1, 1, parameters, 3);
            }
        }
        if (sequence_13e == 4 && frame_counter_144 >= 60) {
            if (selected_action == 760)
                word_736 = 0;
            next_sequence_block();
            return true;
        }
        if (selected_action == 730) {
            if (sequence_13e == 5) {
                const unsigned int mode = static_cast<unsigned int>(g_match_identifier);
                if (mode > 3)
                    return true;
                const int cadence = mode == 0 ? 8 : mode == 1 ? 6 : mode == 2 ? 5 : 4;
                if (frame_counter_144 % cadence == 0) {
                    float parameters[3];
                    if (mode == 3) {
                        const double angle = static_cast<double>(field_73c) + 7.0;
                        parameters[0] = static_cast<float>(angle - static_cast<unsigned int>(selector_random_roll(14)));
                    } else {
                        parameters[0] = field_73c;
                    }
                    parameters[1] = mode >= 2
                        ? static_cast<float>(4.0 - static_cast<unsigned int>(selector_random_roll(mode == 2 ? 5 : 10))
                            * static_cast<double>(0.1f)) : 4.0f;
                    parameters[2] = 2.0f;
                    const float y = static_cast<float>(lookup_orientation_sine_quantized_abs(-parameters[0])
                        * 100.0 + y_f0 + 100.0);
                    const float x = static_cast<float>(lookup_orientation_cosine_quantized_abs(-parameters[0])
                        * 100.0 * facing_104 + x_ec);
                    spawn_owned_object_via_manager(902, x, y,
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                }
                field_73c = static_cast<float>(field_73c + 2.0);
            }
        } else if (sequence_13e == 5) {
            if (word_736 > 0) {
                word_736 = static_cast<short>(word_736 - 1);
                word_4a8 = 3;
                word_4ac = 3;
            }
            if (word_738 == 0 && word_174 <= 7500) {
                word_738 = 1;
                word_736 = 120;
            }
            if (word_738 == 1 && word_174 <= 5000) {
                word_738 = 2;
                word_736 = 120;
            }
            if (word_738 == 2 && word_174 <= 2500) {
                word_738 = 3;
                word_736 = 120;
            }
        } else {
            word_736 = 3;
        }
        return true;
    case 740: {
        unsigned int mode = static_cast<unsigned int>(g_match_identifier);
        if (sequence_13e == 1) {
            // The out-of-range target arm reads uninitialized root-stack storage.
            // Leave that path pending instead of supplying a guessed value.
            if (mode > 3)
                return false;
            const int cadence = mode == 0 ? 10 : mode == 1 ? 8 : mode == 2 ? 6 : 5;
            const int limit = mode == 0 ? 6 : mode == 1 ? 8 : mode == 2 ? 11 : 14;
            if (frame_counter_144 % cadence == 0 && word_730 < limit) {
                dispatch_character_wave_handle(8);
                float parameters[3];
                parameters[0] = static_cast<float>(10.0 - static_cast<unsigned int>(selector_random_roll(200)));
                parameters[1] = static_cast<float>(static_cast<unsigned int>(selector_random_roll(30)) + 15.0);
                parameters[2] = static_cast<float>(word_730 % 3);
                spawn_owned_object_via_manager(903,
                    static_cast<float>(static_cast<float>(facing_104 * 18) + x_ec),
                    static_cast<float>(y_f0 + 120.0),
                    static_cast<unsigned char>(facing_104), 1, parameters, 3);
                word_730 = static_cast<short>(word_730 + 1);
                mode = static_cast<unsigned int>(g_match_identifier);
            }
            if (frame_counter_144 > 80) {
                next_sequence_block();
                return true;
            }
        }
        if (sequence_13e == 6) {
            if (mode > 3)
                return false;
            if (frame_counter_144 >= (mode <= 1 ? 60 : mode == 2 ? 50 : 30)) {
                next_sequence_block();
                return true;
            }
        }
        if (advance_frame_and_dispatch())
            set_action(700);
        if (frame_counter_144 == 0 && frame_timer_142 == 0 && frame_index_140 == 0 && sequence_13e == 6)
            dispatch_character_wave_handle(2);
        return true;
    }
    case 770:
        if (advance_frame_and_dispatch())
            set_action(700);
        if (sequence_13e == 0 && frame_timer_142 == 0 && frame_index_140 == 7) {
            byte_655 = 1;
            finalize_sequence_entry(-1);
            publish_texture_state(6, -1);
            copy_action_word_176_to_174();
            word_76c = 0;
            word_76a = 1;
            word_766 = 0;
            word_768 = 0;
            word_764 = 0;
            dispatch_indexed_event_member(23);
        }
        return true;
    case 795: case 797: case 798:
        if (sequence_13e == 0) {
            if (selected_action == 795)
                velocity_y_f8 = static_cast<float>(velocity_y_f8 - static_cast<double>(0.3f));
            else
                velocity_y_f8 -= acceleration_y_100;
            if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
                set_sequence(1);
                if (selected_action != 795) {
                    dispatch_indexed_event_member(30);
                    x_ec = selected_action == 797 ? 480.0f : 800.0f;
                }
                y_f0 = reimu_stage_surface_height_at_x(this);
                zero_velocity_acceleration();
                return true;
            }
        }
        if (advance_frame_and_dispatch())
            set_action(selected_action == 797 ? 0 : 700);
        return true;
