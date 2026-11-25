#include "ReimuActionStateStaging.hpp"


namespace th105 {

// Natural C++ reconstruction of the Reimu Fighter +0x28 action-state root.
// Action 740 remains semantically provisional; exact whole-root replay is pending.
void ReimuActionStatePreludeView::run_action_dispatch_root()
{
// Shared source fragment; include only within the matching staging context.
    register short reimu_frame_85;
    word_7a0 = 0;
    reimu_frame_85 = 85;
    word_7a2 = static_cast<short>(reimu_frame_85);
    if (action_13c > 149 && action_13c < 159 && !byte_751) {
        byte_751 = 1;
        // Each call can change owner state. Preserve the three later action
        // reads and the unsigned direction argument independently of signed X.
        if (action_13c > 149 && action_13c < 154) {
            const int direction = static_cast<unsigned char>(facing_104);
            spawn_owned_object_via_manager(998,
                static_cast<float>(static_cast<signed char>(direction) * 57) + x_ec,
                static_cast<float>(y_f0 + 94.0), direction, 1, 0, 0);
        }
        if (action_13c > 153 && action_13c < 158) {
            const int direction = static_cast<unsigned char>(facing_104);
            spawn_owned_object_via_manager(998,
                static_cast<float>(static_cast<signed char>(direction) * 57) + x_ec,
                static_cast<float>(y_f0 + 60.0), direction, 1, 0, 0);
        }
        if (action_13c == 158) {
            const int direction = static_cast<unsigned char>(facing_104);
            spawn_owned_object_via_manager(998,
                static_cast<float>(static_cast<signed char>(direction) * 57) + x_ec,
                static_cast<float>(y_f0 + 100.0), direction, 1, 0, 0);
        }
    }
    if (timer_7c8 > 0) {
        if (word_174 <= 0 || peer_170->word_174 <= 0)
            timer_7c8 = 0;
        if (latch_7cc == 0 && (state_180 == 1 || state_180 == 7)) {
            count_7ca = static_cast<short>(count_7ca + 1);
            latch_7cc = 1;
        }
        if (count_7ca >= 7 && action_13c <= 10) {
            set_action(669);
            return;
        }
        // Clearing the timer above does not bypass this decrement or the
        // action-669 test: the cleared timer can finish this phase at -1.
        timer_7c8 = static_cast<short>(timer_7c8 - 1);
    }
    if (word_186 != 0 || peer_170->word_48c != 0)
        return;

    register int frame_threshold;
    register short frame_one;
    register int landing_sequence;
    unsigned char reimu_directional_result;
    const int selected_action = action_13c;
    goto reimu_action_dispatch_switch;
reimu_action_dispatch_switch:
    switch (selected_action) {
    case 0: {
        resolve_stage_surface_landing_transition();
        if (0 == 0 && !velocity_x_f4)
            byte_47e = 0;
        if (!byte_47e) {
            zero_velocity_acceleration();
            advance_frame_and_dispatch();
            return;
        }
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
                advance_frame_and_dispatch();
                return;
            }
            goto reimu_action9_advance;
        }
        goto reimu_action9_fpu_cleanup;
    }
        case 1: {
        resolve_stage_surface_landing_transition();
        if (1 == 0 && !velocity_x_f4)
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
#ifdef TH105_REIMU_SHARED_LOW_ADVANCE
        if (1 == 0 || 1 == 2)
            goto reimu_advance_frame_and_return;
#endif
        const unsigned char completed = advance_frame_and_dispatch();
        if ((1 == 1 || 1 == 3)
                && completed && frame_index_140 == 0)
            set_action(1 == 1 ? 2 : 0);
        return;
    }
    case 2: {
        resolve_stage_surface_landing_transition();
        if (2 == 0 && !velocity_x_f4)
            byte_47e = 0;
        if (!byte_47e) {
            zero_velocity_acceleration();
            advance_frame_and_dispatch();
            return;
        }
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
                advance_frame_and_dispatch();
                return;
            }
            goto reimu_action9_advance;
        }
        goto reimu_action9_fpu_cleanup;
    }
        case 3: {
        resolve_stage_surface_landing_transition();
        if (3 == 0 && !velocity_x_f4)
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
#ifdef TH105_REIMU_SHARED_LOW_ADVANCE
        if (3 == 0 || 3 == 2)
            goto reimu_advance_frame_and_return;
#endif
        const unsigned char completed = advance_frame_and_dispatch();
        if ((3 == 1 || 3 == 3)
                && completed && frame_index_140 == 0)
            set_action(3 == 1 ? 2 : 0);
        return;
    }
        case 4:
        resolve_stage_surface_landing_transition();
        velocity_x_f4 = 4 == 4 ? 4.5f : -4.5f;
        advance_frame_and_dispatch();
        return;
        case 5:
        resolve_stage_surface_landing_transition();
        velocity_x_f4 = 5 == 4 ? 4.5f : -4.5f;
        advance_frame_and_dispatch();
        return;
        case 6:
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
                return;
            }
        }
        advance_frame_and_dispatch();
        if (frame_counter_144 == 0 && frame_timer_142 == 0
                && frame_index_140 == 0 && sequence_13e == 1) {
            velocity_x_f4 = 6 == 6 ? 0.0f : 6 == 7 ? 4.0f : -4.0f;
            velocity_y_f8 = 15.0f;
            acceleration_y_100 = 0.55f;
            byte_47e = 0;
        }
        return;
        case 7:
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
                return;
            }
        }
        advance_frame_and_dispatch();
        if (frame_counter_144 == 0 && frame_timer_142 == 0
                && frame_index_140 == 0 && sequence_13e == 1) {
            velocity_x_f4 = 7 == 6 ? 0.0f : 7 == 7 ? 4.0f : -4.0f;
            velocity_y_f8 = 15.0f;
            acceleration_y_100 = 0.55f;
            byte_47e = 0;
        }
        return;
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
                return;
            }
        }
        advance_frame_and_dispatch();
        if (frame_counter_144 == 0 && frame_timer_142 == 0
                && frame_index_140 == 0 && sequence_13e == 1) {
            velocity_x_f4 = 8 == 6 ? 0.0f : 8 == 7 ? 4.0f : -4.0f;
            velocity_y_f8 = 15.0f;
            acceleration_y_100 = 0.55f;
            byte_47e = 0;
        }
        return;
        case 9:
        if (!acceleration_y_100)
            acceleration_y_100 = 0.6f;
        velocity_y_f8 = static_cast<float>(velocity_y_f8 - acceleration_y_100);
        if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending()))
            goto reimu_action9_landing_tail;
        goto reimu_action9_advance;
reimu_action9_landing_tail:
        set_action(10);
        y_f0 = reimu_stage_surface_height_at_x(this);
        zero_velocity_acceleration();
        return;
reimu_action9_fpu_cleanup:
reimu_action9_advance:
        reinterpret_cast<CharacterObjectRuntime *>(this)->advance_frame_and_dispatch();
        return;
        case 10:
        resolve_stage_surface_landing_transition();
        zero_velocity_acceleration();
        if (advance_frame_and_dispatch()) {
            if (field_6b8 == 0)
                set_action(0);
            else
                set_action(2);
        }
        return;

        case 71: {
// Shared source fragment; include only within the matching staging context.
    if (71 == 71 || 71 == 74) {
        if (frame_counter_144 == 0 && frame_timer_142 == 0
                && frame_index_140 == 0 && sequence_13e == 1 && word_7a4 == 0) {
            word_7a4 = 1;
            spawn_owned_object_via_manager(951, x_ec, y_f0,
                static_cast<unsigned char>(facing_104), 1, 0, 0);
        }
    }
    if ((71 == 71 || 71 == 72 || 71 == 74)
            && sequence_13e == 1 && velocity_y_f8 < 2.0f) {
        next_sequence_block();
        return;
    }

    if (71 == 74) {
        if (classify_fighter_x_boundary() && velocity_x_f4 <= -25.0) {
            set_action(76);
            return;
        }
        if (classify_fighter_x_boundary() && velocity_x_f4 <= -15.0) {
            set_action(78);
            return;
        }
    }
    if ((71 == 76 && sequence_13e > 0) || 71 == 77)
        angle_12c = static_cast<float>(angle_12c - 30.0);
    if (71 != 73 && 71 != 75) {
        velocity_y_f8 = static_cast<float>(velocity_y_f8 - acceleration_y_100);
        if (71 == 71 && velocity_y_f8 > 0.0f)
            velocity_y_f8 = static_cast<float>(velocity_y_f8 - acceleration_y_100);
    }

    if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
        if (71 >= 76)
            dispatch_indexed_event_member(22);
        // The target truncates each velocity before its wrapping WORD product.
        word_730 = static_cast<short>(static_cast<short>(static_cast<int>(velocity_x_f4)) * 100);
        word_732 = static_cast<short>(static_cast<short>(static_cast<int>(velocity_y_f8)) * 100);
        zero_velocity_acceleration();
        y_f0 = reimu_stage_surface_height_at_x(this);
        set_action(97);
        if (71 == 76 || 71 == 77)
            angle_12c = 0.0f;
        publish_battle_layout_scalar(71 == 73 || 71 == 75
            ? 5.0f : 71 == 76 ? 4.0f : 2.0f);
        if (71 == 76 || 71 == 77)
            reinterpret_cast<ReimuRecoverySpriteView *>(
                reinterpret_cast<unsigned char *>(this) + 4)->reset_fighter_action_scratch();
        if (71 < 76)
            dispatch_indexed_event_member(22);
        return;
    }

    if (71 == 75) {
        if (classify_fighter_x_boundary() && velocity_x_f4 <= -25.0) {
            set_action(76);
            return;
        }
        if (classify_fighter_x_boundary() && velocity_x_f4 <= -15.0) {
            set_action(78);
            return;
        }
    }
    if (71 == 73 || 71 == 75) {
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
                    return;
                }
                set_sequence(2);
                return;
            }
        }
        if (71 == 75)
            return;
        word_730 = static_cast<short>(word_730 - 1);
        if (word_730 < 0)
            word_730 = 0;
    } else if (71 == 71 && word_730 > 0) {
        --word_730;
    }
    if (71 == 71 || 71 == 72 || 71 == 73) {
        if (classify_fighter_x_boundary() && velocity_x_f4 < 0.0f) {
            velocity_x_f4 = static_cast<float>(velocity_x_f4 +
                (71 == 73 ? 2.5 : 1.0));
            if (velocity_x_f4 > 0.0f)
                velocity_x_f4 = 0.0f;
            if (byte_490)
                field_6ac = 71 == 72 ? velocity_x_f4
                    : static_cast<float>(word_730 * -2.0);
        }
        if (71 == 73)
            return;
    }

    if (71 == 76 || 71 == 78) {
        advance_frame_and_dispatch();
        if (frame_counter_144 == 0 && frame_timer_142 == 0
                && frame_index_140 == 0 && sequence_13e == 1) {
            facing_104 = static_cast<signed char>(-facing_104);
            velocity_x_f4 = 71 == 76 ? -3.0f : -5.0f;
            velocity_y_f8 = 71 == 76 ? 10.0f : 3.0f;
            acceleration_y_100 = 0.5f;
            if (word_7a4 == 0) {
                word_7a4 = 1;
                spawn_owned_object_via_manager(951, x_ec, y_f0,
                    static_cast<unsigned char>(facing_104), 1, 0, 0);
            }
        }
        return;
    }
    if (71 == 77 && frame_counter_144 == 0 && frame_timer_142 == 0
            && frame_index_140 == 0 && sequence_13e == 1 && word_7a4 == 0) {
        word_7a4 = 1;
        spawn_owned_object_via_manager(951, x_ec, y_f0,
            static_cast<unsigned char>(facing_104), 1, 0, 0);
    }
#ifdef TH105_REIMU_SHARED_LOW_ADVANCE
    if (71 == 71 || 71 == 72 || 71 == 74)
        goto reimu_advance_frame_and_return;
#endif
    advance_frame_and_dispatch();
    return;

    }
// Shared source fragment; include only within the matching staging context.
        case 72: {
// Shared source fragment; include only within the matching staging context.
    if (72 == 71 || 72 == 74) {
        if (frame_counter_144 == 0 && frame_timer_142 == 0
                && frame_index_140 == 0 && sequence_13e == 1 && word_7a4 == 0) {
            word_7a4 = 1;
            spawn_owned_object_via_manager(951, x_ec, y_f0,
                static_cast<unsigned char>(facing_104), 1, 0, 0);
        }
    }
    if ((72 == 71 || 72 == 72 || 72 == 74)
            && sequence_13e == 1 && velocity_y_f8 < 2.0f) {
        next_sequence_block();
        return;
    }

    if (72 == 74) {
        if (classify_fighter_x_boundary() && velocity_x_f4 <= -25.0) {
            set_action(76);
            return;
        }
        if (classify_fighter_x_boundary() && velocity_x_f4 <= -15.0) {
            set_action(78);
            return;
        }
    }
    if ((72 == 76 && sequence_13e > 0) || 72 == 77)
        angle_12c = static_cast<float>(angle_12c - 30.0);
    if (72 != 73 && 72 != 75) {
        velocity_y_f8 = static_cast<float>(velocity_y_f8 - acceleration_y_100);
        if (72 == 71 && velocity_y_f8 > 0.0f)
            velocity_y_f8 = static_cast<float>(velocity_y_f8 - acceleration_y_100);
    }

    if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
        if (72 >= 76)
            dispatch_indexed_event_member(22);
        // The target truncates each velocity before its wrapping WORD product.
        word_730 = static_cast<short>(static_cast<short>(static_cast<int>(velocity_x_f4)) * 100);
        word_732 = static_cast<short>(static_cast<short>(static_cast<int>(velocity_y_f8)) * 100);
        zero_velocity_acceleration();
        y_f0 = reimu_stage_surface_height_at_x(this);
        set_action(97);
        if (72 == 76 || 72 == 77)
            angle_12c = 0.0f;
        publish_battle_layout_scalar(72 == 73 || 72 == 75
            ? 5.0f : 72 == 76 ? 4.0f : 2.0f);
        if (72 == 76 || 72 == 77)
            reinterpret_cast<ReimuRecoverySpriteView *>(
                reinterpret_cast<unsigned char *>(this) + 4)->reset_fighter_action_scratch();
        if (72 < 76)
            dispatch_indexed_event_member(22);
        return;
    }

    if (72 == 75) {
        if (classify_fighter_x_boundary() && velocity_x_f4 <= -25.0) {
            set_action(76);
            return;
        }
        if (classify_fighter_x_boundary() && velocity_x_f4 <= -15.0) {
            set_action(78);
            return;
        }
    }
    if (72 == 73 || 72 == 75) {
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
                    return;
                }
                set_sequence(2);
                return;
            }
        }
        if (72 == 75)
            return;
        word_730 = static_cast<short>(word_730 - 1);
        if (word_730 < 0)
            word_730 = 0;
    } else if (72 == 71 && word_730 > 0) {
        --word_730;
    }
    if (72 == 71 || 72 == 72 || 72 == 73) {
        if (classify_fighter_x_boundary() && velocity_x_f4 < 0.0f) {
            velocity_x_f4 = static_cast<float>(velocity_x_f4 +
                (72 == 73 ? 2.5 : 1.0));
            if (velocity_x_f4 > 0.0f)
                velocity_x_f4 = 0.0f;
            if (byte_490)
                field_6ac = 72 == 72 ? velocity_x_f4
                    : static_cast<float>(word_730 * -2.0);
        }
        if (72 == 73)
            return;
    }

    if (72 == 76 || 72 == 78) {
        advance_frame_and_dispatch();
        if (frame_counter_144 == 0 && frame_timer_142 == 0
                && frame_index_140 == 0 && sequence_13e == 1) {
            facing_104 = static_cast<signed char>(-facing_104);
            velocity_x_f4 = 72 == 76 ? -3.0f : -5.0f;
            velocity_y_f8 = 72 == 76 ? 10.0f : 3.0f;
            acceleration_y_100 = 0.5f;
            if (word_7a4 == 0) {
                word_7a4 = 1;
                spawn_owned_object_via_manager(951, x_ec, y_f0,
                    static_cast<unsigned char>(facing_104), 1, 0, 0);
            }
        }
        return;
    }
    if (72 == 77 && frame_counter_144 == 0 && frame_timer_142 == 0
            && frame_index_140 == 0 && sequence_13e == 1 && word_7a4 == 0) {
        word_7a4 = 1;
        spawn_owned_object_via_manager(951, x_ec, y_f0,
            static_cast<unsigned char>(facing_104), 1, 0, 0);
    }
#ifdef TH105_REIMU_SHARED_LOW_ADVANCE
    if (72 == 71 || 72 == 72 || 72 == 74)
        goto reimu_advance_frame_and_return;
#endif
    advance_frame_and_dispatch();
    return;

    }
// Shared source fragment; include only within the matching staging context.
        case 73: {
// Shared source fragment; include only within the matching staging context.
    if (73 == 71 || 73 == 74) {
        if (frame_counter_144 == 0 && frame_timer_142 == 0
                && frame_index_140 == 0 && sequence_13e == 1 && word_7a4 == 0) {
            word_7a4 = 1;
            spawn_owned_object_via_manager(951, x_ec, y_f0,
                static_cast<unsigned char>(facing_104), 1, 0, 0);
        }
    }
    if ((73 == 71 || 73 == 72 || 73 == 74)
            && sequence_13e == 1 && velocity_y_f8 < 2.0f) {
        next_sequence_block();
        return;
    }

    if (73 == 74) {
        if (classify_fighter_x_boundary() && velocity_x_f4 <= -25.0) {
            set_action(76);
            return;
        }
        if (classify_fighter_x_boundary() && velocity_x_f4 <= -15.0) {
            set_action(78);
            return;
        }
    }
    if ((73 == 76 && sequence_13e > 0) || 73 == 77)
        angle_12c = static_cast<float>(angle_12c - 30.0);
    if (73 != 73 && 73 != 75) {
        velocity_y_f8 = static_cast<float>(velocity_y_f8 - acceleration_y_100);
        if (73 == 71 && velocity_y_f8 > 0.0f)
            velocity_y_f8 = static_cast<float>(velocity_y_f8 - acceleration_y_100);
    }

    if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
        if (73 >= 76)
            dispatch_indexed_event_member(22);
        // The target truncates each velocity before its wrapping WORD product.
        word_730 = static_cast<short>(static_cast<short>(static_cast<int>(velocity_x_f4)) * 100);
        word_732 = static_cast<short>(static_cast<short>(static_cast<int>(velocity_y_f8)) * 100);
        zero_velocity_acceleration();
        y_f0 = reimu_stage_surface_height_at_x(this);
        set_action(97);
        if (73 == 76 || 73 == 77)
            angle_12c = 0.0f;
        publish_battle_layout_scalar(73 == 73 || 73 == 75
            ? 5.0f : 73 == 76 ? 4.0f : 2.0f);
        if (73 == 76 || 73 == 77)
            reinterpret_cast<ReimuRecoverySpriteView *>(
                reinterpret_cast<unsigned char *>(this) + 4)->reset_fighter_action_scratch();
        if (73 < 76)
            dispatch_indexed_event_member(22);
        return;
    }

    if (73 == 75) {
        if (classify_fighter_x_boundary() && velocity_x_f4 <= -25.0) {
            set_action(76);
            return;
        }
        if (classify_fighter_x_boundary() && velocity_x_f4 <= -15.0) {
            set_action(78);
            return;
        }
    }
    if (73 == 73 || 73 == 75) {
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
                    return;
                }
                set_sequence(2);
                return;
            }
        }
        if (73 == 75)
            return;
        word_730 = static_cast<short>(word_730 - 1);
        if (word_730 < 0)
            word_730 = 0;
    } else if (73 == 71 && word_730 > 0) {
        --word_730;
    }
    if (73 == 71 || 73 == 72 || 73 == 73) {
        if (classify_fighter_x_boundary() && velocity_x_f4 < 0.0f) {
            velocity_x_f4 = static_cast<float>(velocity_x_f4 +
                (73 == 73 ? 2.5 : 1.0));
            if (velocity_x_f4 > 0.0f)
                velocity_x_f4 = 0.0f;
            if (byte_490)
                field_6ac = 73 == 72 ? velocity_x_f4
                    : static_cast<float>(word_730 * -2.0);
        }
        if (73 == 73)
            return;
    }

    if (73 == 76 || 73 == 78) {
        advance_frame_and_dispatch();
        if (frame_counter_144 == 0 && frame_timer_142 == 0
                && frame_index_140 == 0 && sequence_13e == 1) {
            facing_104 = static_cast<signed char>(-facing_104);
            velocity_x_f4 = 73 == 76 ? -3.0f : -5.0f;
            velocity_y_f8 = 73 == 76 ? 10.0f : 3.0f;
            acceleration_y_100 = 0.5f;
            if (word_7a4 == 0) {
                word_7a4 = 1;
                spawn_owned_object_via_manager(951, x_ec, y_f0,
                    static_cast<unsigned char>(facing_104), 1, 0, 0);
            }
        }
        return;
    }
    if (73 == 77 && frame_counter_144 == 0 && frame_timer_142 == 0
            && frame_index_140 == 0 && sequence_13e == 1 && word_7a4 == 0) {
        word_7a4 = 1;
        spawn_owned_object_via_manager(951, x_ec, y_f0,
            static_cast<unsigned char>(facing_104), 1, 0, 0);
    }
#ifdef TH105_REIMU_SHARED_LOW_ADVANCE
    if (73 == 71 || 73 == 72 || 73 == 74)
        goto reimu_advance_frame_and_return;
#endif
    advance_frame_and_dispatch();
    return;

    }
// Shared source fragment; include only within the matching staging context.
        case 74: {
// Shared source fragment; include only within the matching staging context.
    if (74 == 71 || 74 == 74) {
        if (frame_counter_144 == 0 && frame_timer_142 == 0
                && frame_index_140 == 0 && sequence_13e == 1 && word_7a4 == 0) {
            word_7a4 = 1;
            spawn_owned_object_via_manager(951, x_ec, y_f0,
                static_cast<unsigned char>(facing_104), 1, 0, 0);
        }
    }
    if ((74 == 71 || 74 == 72 || 74 == 74)
            && sequence_13e == 1 && velocity_y_f8 < 2.0f) {
        next_sequence_block();
        return;
    }

    if (74 == 74) {
        if (classify_fighter_x_boundary() && velocity_x_f4 <= -25.0) {
            set_action(76);
            return;
        }
        if (classify_fighter_x_boundary() && velocity_x_f4 <= -15.0) {
            set_action(78);
            return;
        }
    }
    if ((74 == 76 && sequence_13e > 0) || 74 == 77)
        angle_12c = static_cast<float>(angle_12c - 30.0);
    if (74 != 73 && 74 != 75) {
        velocity_y_f8 = static_cast<float>(velocity_y_f8 - acceleration_y_100);
        if (74 == 71 && velocity_y_f8 > 0.0f)
            velocity_y_f8 = static_cast<float>(velocity_y_f8 - acceleration_y_100);
    }

    if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
        if (74 >= 76)
            dispatch_indexed_event_member(22);
        // The target truncates each velocity before its wrapping WORD product.
        word_730 = static_cast<short>(static_cast<short>(static_cast<int>(velocity_x_f4)) * 100);
        word_732 = static_cast<short>(static_cast<short>(static_cast<int>(velocity_y_f8)) * 100);
        zero_velocity_acceleration();
        y_f0 = reimu_stage_surface_height_at_x(this);
        set_action(97);
        if (74 == 76 || 74 == 77)
            angle_12c = 0.0f;
        publish_battle_layout_scalar(74 == 73 || 74 == 75
            ? 5.0f : 74 == 76 ? 4.0f : 2.0f);
        if (74 == 76 || 74 == 77)
            reinterpret_cast<ReimuRecoverySpriteView *>(
                reinterpret_cast<unsigned char *>(this) + 4)->reset_fighter_action_scratch();
        if (74 < 76)
            dispatch_indexed_event_member(22);
        return;
    }

    if (74 == 75) {
        if (classify_fighter_x_boundary() && velocity_x_f4 <= -25.0) {
            set_action(76);
            return;
        }
        if (classify_fighter_x_boundary() && velocity_x_f4 <= -15.0) {
            set_action(78);
            return;
        }
    }
    if (74 == 73 || 74 == 75) {
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
                    return;
                }
                set_sequence(2);
                return;
            }
        }
        if (74 == 75)
            return;
        word_730 = static_cast<short>(word_730 - 1);
        if (word_730 < 0)
            word_730 = 0;
    } else if (74 == 71 && word_730 > 0) {
        --word_730;
    }
    if (74 == 71 || 74 == 72 || 74 == 73) {
        if (classify_fighter_x_boundary() && velocity_x_f4 < 0.0f) {
            velocity_x_f4 = static_cast<float>(velocity_x_f4 +
                (74 == 73 ? 2.5 : 1.0));
            if (velocity_x_f4 > 0.0f)
                velocity_x_f4 = 0.0f;
            if (byte_490)
                field_6ac = 74 == 72 ? velocity_x_f4
                    : static_cast<float>(word_730 * -2.0);
        }
        if (74 == 73)
            return;
    }

    if (74 == 76 || 74 == 78) {
        advance_frame_and_dispatch();
        if (frame_counter_144 == 0 && frame_timer_142 == 0
                && frame_index_140 == 0 && sequence_13e == 1) {
            facing_104 = static_cast<signed char>(-facing_104);
            velocity_x_f4 = 74 == 76 ? -3.0f : -5.0f;
            velocity_y_f8 = 74 == 76 ? 10.0f : 3.0f;
            acceleration_y_100 = 0.5f;
            if (word_7a4 == 0) {
                word_7a4 = 1;
                spawn_owned_object_via_manager(951, x_ec, y_f0,
                    static_cast<unsigned char>(facing_104), 1, 0, 0);
            }
        }
        return;
    }
    if (74 == 77 && frame_counter_144 == 0 && frame_timer_142 == 0
            && frame_index_140 == 0 && sequence_13e == 1 && word_7a4 == 0) {
        word_7a4 = 1;
        spawn_owned_object_via_manager(951, x_ec, y_f0,
            static_cast<unsigned char>(facing_104), 1, 0, 0);
    }
#ifdef TH105_REIMU_SHARED_LOW_ADVANCE
    if (74 == 71 || 74 == 72 || 74 == 74)
        goto reimu_advance_frame_and_return;
#endif
    advance_frame_and_dispatch();
    return;

    }
// Shared source fragment; include only within the matching staging context.
        case 75: {
// Shared source fragment; include only within the matching staging context.
    if (75 == 71 || 75 == 74) {
        if (frame_counter_144 == 0 && frame_timer_142 == 0
                && frame_index_140 == 0 && sequence_13e == 1 && word_7a4 == 0) {
            word_7a4 = 1;
            spawn_owned_object_via_manager(951, x_ec, y_f0,
                static_cast<unsigned char>(facing_104), 1, 0, 0);
        }
    }
    if ((75 == 71 || 75 == 72 || 75 == 74)
            && sequence_13e == 1 && velocity_y_f8 < 2.0f) {
        next_sequence_block();
        return;
    }

    if (75 == 74) {
        if (classify_fighter_x_boundary() && velocity_x_f4 <= -25.0) {
            set_action(76);
            return;
        }
        if (classify_fighter_x_boundary() && velocity_x_f4 <= -15.0) {
            set_action(78);
            return;
        }
    }
    if ((75 == 76 && sequence_13e > 0) || 75 == 77)
        angle_12c = static_cast<float>(angle_12c - 30.0);
    if (75 != 73 && 75 != 75) {
        velocity_y_f8 = static_cast<float>(velocity_y_f8 - acceleration_y_100);
        if (75 == 71 && velocity_y_f8 > 0.0f)
            velocity_y_f8 = static_cast<float>(velocity_y_f8 - acceleration_y_100);
    }

    if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
        if (75 >= 76)
            dispatch_indexed_event_member(22);
        // The target truncates each velocity before its wrapping WORD product.
        word_730 = static_cast<short>(static_cast<short>(static_cast<int>(velocity_x_f4)) * 100);
        word_732 = static_cast<short>(static_cast<short>(static_cast<int>(velocity_y_f8)) * 100);
        zero_velocity_acceleration();
        y_f0 = reimu_stage_surface_height_at_x(this);
        set_action(97);
        if (75 == 76 || 75 == 77)
            angle_12c = 0.0f;
        publish_battle_layout_scalar(75 == 73 || 75 == 75
            ? 5.0f : 75 == 76 ? 4.0f : 2.0f);
        if (75 == 76 || 75 == 77)
            reinterpret_cast<ReimuRecoverySpriteView *>(
                reinterpret_cast<unsigned char *>(this) + 4)->reset_fighter_action_scratch();
        if (75 < 76)
            dispatch_indexed_event_member(22);
        return;
    }

    if (75 == 75) {
        if (classify_fighter_x_boundary() && velocity_x_f4 <= -25.0) {
            set_action(76);
            return;
        }
        if (classify_fighter_x_boundary() && velocity_x_f4 <= -15.0) {
            set_action(78);
            return;
        }
    }
    if (75 == 73 || 75 == 75) {
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
                    return;
                }
                set_sequence(2);
                return;
            }
        }
        if (75 == 75)
            return;
        word_730 = static_cast<short>(word_730 - 1);
        if (word_730 < 0)
            word_730 = 0;
    } else if (75 == 71 && word_730 > 0) {
        --word_730;
    }
    if (75 == 71 || 75 == 72 || 75 == 73) {
        if (classify_fighter_x_boundary() && velocity_x_f4 < 0.0f) {
            velocity_x_f4 = static_cast<float>(velocity_x_f4 +
                (75 == 73 ? 2.5 : 1.0));
            if (velocity_x_f4 > 0.0f)
                velocity_x_f4 = 0.0f;
            if (byte_490)
                field_6ac = 75 == 72 ? velocity_x_f4
                    : static_cast<float>(word_730 * -2.0);
        }
        if (75 == 73)
            return;
    }

    if (75 == 76 || 75 == 78) {
        advance_frame_and_dispatch();
        if (frame_counter_144 == 0 && frame_timer_142 == 0
                && frame_index_140 == 0 && sequence_13e == 1) {
            facing_104 = static_cast<signed char>(-facing_104);
            velocity_x_f4 = 75 == 76 ? -3.0f : -5.0f;
            velocity_y_f8 = 75 == 76 ? 10.0f : 3.0f;
            acceleration_y_100 = 0.5f;
            if (word_7a4 == 0) {
                word_7a4 = 1;
                spawn_owned_object_via_manager(951, x_ec, y_f0,
                    static_cast<unsigned char>(facing_104), 1, 0, 0);
            }
        }
        return;
    }
    if (75 == 77 && frame_counter_144 == 0 && frame_timer_142 == 0
            && frame_index_140 == 0 && sequence_13e == 1 && word_7a4 == 0) {
        word_7a4 = 1;
        spawn_owned_object_via_manager(951, x_ec, y_f0,
            static_cast<unsigned char>(facing_104), 1, 0, 0);
    }
#ifdef TH105_REIMU_SHARED_LOW_ADVANCE
    if (75 == 71 || 75 == 72 || 75 == 74)
        goto reimu_advance_frame_and_return;
#endif
    advance_frame_and_dispatch();
    return;

    }
// Shared source fragment; include only within the matching staging context.
        case 76: {
// Shared source fragment; include only within the matching staging context.
    if (76 == 71 || 76 == 74) {
        if (frame_counter_144 == 0 && frame_timer_142 == 0
                && frame_index_140 == 0 && sequence_13e == 1 && word_7a4 == 0) {
            word_7a4 = 1;
            spawn_owned_object_via_manager(951, x_ec, y_f0,
                static_cast<unsigned char>(facing_104), 1, 0, 0);
        }
    }
    if ((76 == 71 || 76 == 72 || 76 == 74)
            && sequence_13e == 1 && velocity_y_f8 < 2.0f) {
        next_sequence_block();
        return;
    }

    if (76 == 74) {
        if (classify_fighter_x_boundary() && velocity_x_f4 <= -25.0) {
            set_action(76);
            return;
        }
        if (classify_fighter_x_boundary() && velocity_x_f4 <= -15.0) {
            set_action(78);
            return;
        }
    }
    if ((76 == 76 && sequence_13e > 0) || 76 == 77)
        angle_12c = static_cast<float>(angle_12c - 30.0);
    if (76 != 73 && 76 != 75) {
        velocity_y_f8 = static_cast<float>(velocity_y_f8 - acceleration_y_100);
        if (76 == 71 && velocity_y_f8 > 0.0f)
            velocity_y_f8 = static_cast<float>(velocity_y_f8 - acceleration_y_100);
    }

    if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
        if (76 >= 76)
            dispatch_indexed_event_member(22);
        // The target truncates each velocity before its wrapping WORD product.
        word_730 = static_cast<short>(static_cast<short>(static_cast<int>(velocity_x_f4)) * 100);
        word_732 = static_cast<short>(static_cast<short>(static_cast<int>(velocity_y_f8)) * 100);
        zero_velocity_acceleration();
        y_f0 = reimu_stage_surface_height_at_x(this);
        set_action(97);
        if (76 == 76 || 76 == 77)
            angle_12c = 0.0f;
        publish_battle_layout_scalar(76 == 73 || 76 == 75
            ? 5.0f : 76 == 76 ? 4.0f : 2.0f);
        if (76 == 76 || 76 == 77)
            reinterpret_cast<ReimuRecoverySpriteView *>(
                reinterpret_cast<unsigned char *>(this) + 4)->reset_fighter_action_scratch();
        if (76 < 76)
            dispatch_indexed_event_member(22);
        return;
    }

    if (76 == 75) {
        if (classify_fighter_x_boundary() && velocity_x_f4 <= -25.0) {
            set_action(76);
            return;
        }
        if (classify_fighter_x_boundary() && velocity_x_f4 <= -15.0) {
            set_action(78);
            return;
        }
    }
    if (76 == 73 || 76 == 75) {
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
                    return;
                }
                set_sequence(2);
                return;
            }
        }
        if (76 == 75)
            return;
        word_730 = static_cast<short>(word_730 - 1);
        if (word_730 < 0)
            word_730 = 0;
    } else if (76 == 71 && word_730 > 0) {
        --word_730;
    }
    if (76 == 71 || 76 == 72 || 76 == 73) {
        if (classify_fighter_x_boundary() && velocity_x_f4 < 0.0f) {
            velocity_x_f4 = static_cast<float>(velocity_x_f4 +
                (76 == 73 ? 2.5 : 1.0));
            if (velocity_x_f4 > 0.0f)
                velocity_x_f4 = 0.0f;
            if (byte_490)
                field_6ac = 76 == 72 ? velocity_x_f4
                    : static_cast<float>(word_730 * -2.0);
        }
        if (76 == 73)
            return;
    }

    if (76 == 76 || 76 == 78) {
        advance_frame_and_dispatch();
        if (frame_counter_144 == 0 && frame_timer_142 == 0
                && frame_index_140 == 0 && sequence_13e == 1) {
            facing_104 = static_cast<signed char>(-facing_104);
            velocity_x_f4 = 76 == 76 ? -3.0f : -5.0f;
            velocity_y_f8 = 76 == 76 ? 10.0f : 3.0f;
            acceleration_y_100 = 0.5f;
            if (word_7a4 == 0) {
                word_7a4 = 1;
                spawn_owned_object_via_manager(951, x_ec, y_f0,
                    static_cast<unsigned char>(facing_104), 1, 0, 0);
            }
        }
        return;
    }
    if (76 == 77 && frame_counter_144 == 0 && frame_timer_142 == 0
            && frame_index_140 == 0 && sequence_13e == 1 && word_7a4 == 0) {
        word_7a4 = 1;
        spawn_owned_object_via_manager(951, x_ec, y_f0,
            static_cast<unsigned char>(facing_104), 1, 0, 0);
    }
#ifdef TH105_REIMU_SHARED_LOW_ADVANCE
    if (76 == 71 || 76 == 72 || 76 == 74)
        goto reimu_advance_frame_and_return;
#endif
    advance_frame_and_dispatch();
    return;

    }
// Shared source fragment; include only within the matching staging context.
        case 77: {
// Shared source fragment; include only within the matching staging context.
    if (77 == 71 || 77 == 74) {
        if (frame_counter_144 == 0 && frame_timer_142 == 0
                && frame_index_140 == 0 && sequence_13e == 1 && word_7a4 == 0) {
            word_7a4 = 1;
            spawn_owned_object_via_manager(951, x_ec, y_f0,
                static_cast<unsigned char>(facing_104), 1, 0, 0);
        }
    }
    if ((77 == 71 || 77 == 72 || 77 == 74)
            && sequence_13e == 1 && velocity_y_f8 < 2.0f) {
        next_sequence_block();
        return;
    }

    if (77 == 74) {
        if (classify_fighter_x_boundary() && velocity_x_f4 <= -25.0) {
            set_action(76);
            return;
        }
        if (classify_fighter_x_boundary() && velocity_x_f4 <= -15.0) {
            set_action(78);
            return;
        }
    }
    if ((77 == 76 && sequence_13e > 0) || 77 == 77)
        angle_12c = static_cast<float>(angle_12c - 30.0);
    if (77 != 73 && 77 != 75) {
        velocity_y_f8 = static_cast<float>(velocity_y_f8 - acceleration_y_100);
        if (77 == 71 && velocity_y_f8 > 0.0f)
            velocity_y_f8 = static_cast<float>(velocity_y_f8 - acceleration_y_100);
    }

    if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
        if (77 >= 76)
            dispatch_indexed_event_member(22);
        // The target truncates each velocity before its wrapping WORD product.
        word_730 = static_cast<short>(static_cast<short>(static_cast<int>(velocity_x_f4)) * 100);
        word_732 = static_cast<short>(static_cast<short>(static_cast<int>(velocity_y_f8)) * 100);
        zero_velocity_acceleration();
        y_f0 = reimu_stage_surface_height_at_x(this);
        set_action(97);
        if (77 == 76 || 77 == 77)
            angle_12c = 0.0f;
        publish_battle_layout_scalar(77 == 73 || 77 == 75
            ? 5.0f : 77 == 76 ? 4.0f : 2.0f);
        if (77 == 76 || 77 == 77)
            reinterpret_cast<ReimuRecoverySpriteView *>(
                reinterpret_cast<unsigned char *>(this) + 4)->reset_fighter_action_scratch();
        if (77 < 76)
            dispatch_indexed_event_member(22);
        return;
    }

    if (77 == 75) {
        if (classify_fighter_x_boundary() && velocity_x_f4 <= -25.0) {
            set_action(76);
            return;
        }
        if (classify_fighter_x_boundary() && velocity_x_f4 <= -15.0) {
            set_action(78);
            return;
        }
    }
    if (77 == 73 || 77 == 75) {
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
                    return;
                }
                set_sequence(2);
                return;
            }
        }
        if (77 == 75)
            return;
        word_730 = static_cast<short>(word_730 - 1);
        if (word_730 < 0)
            word_730 = 0;
    } else if (77 == 71 && word_730 > 0) {
        --word_730;
    }
    if (77 == 71 || 77 == 72 || 77 == 73) {
        if (classify_fighter_x_boundary() && velocity_x_f4 < 0.0f) {
            velocity_x_f4 = static_cast<float>(velocity_x_f4 +
                (77 == 73 ? 2.5 : 1.0));
            if (velocity_x_f4 > 0.0f)
                velocity_x_f4 = 0.0f;
            if (byte_490)
                field_6ac = 77 == 72 ? velocity_x_f4
                    : static_cast<float>(word_730 * -2.0);
        }
        if (77 == 73)
            return;
    }

    if (77 == 76 || 77 == 78) {
        advance_frame_and_dispatch();
        if (frame_counter_144 == 0 && frame_timer_142 == 0
                && frame_index_140 == 0 && sequence_13e == 1) {
            facing_104 = static_cast<signed char>(-facing_104);
            velocity_x_f4 = 77 == 76 ? -3.0f : -5.0f;
            velocity_y_f8 = 77 == 76 ? 10.0f : 3.0f;
            acceleration_y_100 = 0.5f;
            if (word_7a4 == 0) {
                word_7a4 = 1;
                spawn_owned_object_via_manager(951, x_ec, y_f0,
                    static_cast<unsigned char>(facing_104), 1, 0, 0);
            }
        }
        return;
    }
    if (77 == 77 && frame_counter_144 == 0 && frame_timer_142 == 0
            && frame_index_140 == 0 && sequence_13e == 1 && word_7a4 == 0) {
        word_7a4 = 1;
        spawn_owned_object_via_manager(951, x_ec, y_f0,
            static_cast<unsigned char>(facing_104), 1, 0, 0);
    }
#ifdef TH105_REIMU_SHARED_LOW_ADVANCE
    if (77 == 71 || 77 == 72 || 77 == 74)
        goto reimu_advance_frame_and_return;
#endif
    advance_frame_and_dispatch();
    return;

    }
// Shared source fragment; include only within the matching staging context.
        case 78: {
// Shared source fragment; include only within the matching staging context.
    if (78 == 71 || 78 == 74) {
        if (frame_counter_144 == 0 && frame_timer_142 == 0
                && frame_index_140 == 0 && sequence_13e == 1 && word_7a4 == 0) {
            word_7a4 = 1;
            spawn_owned_object_via_manager(951, x_ec, y_f0,
                static_cast<unsigned char>(facing_104), 1, 0, 0);
        }
    }
    if ((78 == 71 || 78 == 72 || 78 == 74)
            && sequence_13e == 1 && velocity_y_f8 < 2.0f) {
        next_sequence_block();
        return;
    }

    if (78 == 74) {
        if (classify_fighter_x_boundary() && velocity_x_f4 <= -25.0) {
            set_action(76);
            return;
        }
        if (classify_fighter_x_boundary() && velocity_x_f4 <= -15.0) {
            set_action(78);
            return;
        }
    }
    if ((78 == 76 && sequence_13e > 0) || 78 == 77)
        angle_12c = static_cast<float>(angle_12c - 30.0);
    if (78 != 73 && 78 != 75) {
        velocity_y_f8 = static_cast<float>(velocity_y_f8 - acceleration_y_100);
        if (78 == 71 && velocity_y_f8 > 0.0f)
            velocity_y_f8 = static_cast<float>(velocity_y_f8 - acceleration_y_100);
    }

    if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
        if (78 >= 76)
            dispatch_indexed_event_member(22);
        // The target truncates each velocity before its wrapping WORD product.
        word_730 = static_cast<short>(static_cast<short>(static_cast<int>(velocity_x_f4)) * 100);
        word_732 = static_cast<short>(static_cast<short>(static_cast<int>(velocity_y_f8)) * 100);
        zero_velocity_acceleration();
        y_f0 = reimu_stage_surface_height_at_x(this);
        set_action(97);
        if (78 == 76 || 78 == 77)
            angle_12c = 0.0f;
        publish_battle_layout_scalar(78 == 73 || 78 == 75
            ? 5.0f : 78 == 76 ? 4.0f : 2.0f);
        if (78 == 76 || 78 == 77)
            reinterpret_cast<ReimuRecoverySpriteView *>(
                reinterpret_cast<unsigned char *>(this) + 4)->reset_fighter_action_scratch();
        if (78 < 76)
            dispatch_indexed_event_member(22);
        return;
    }

    if (78 == 75) {
        if (classify_fighter_x_boundary() && velocity_x_f4 <= -25.0) {
            set_action(76);
            return;
        }
        if (classify_fighter_x_boundary() && velocity_x_f4 <= -15.0) {
            set_action(78);
            return;
        }
    }
    if (78 == 73 || 78 == 75) {
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
                    return;
                }
                set_sequence(2);
                return;
            }
        }
        if (78 == 75)
            return;
        word_730 = static_cast<short>(word_730 - 1);
        if (word_730 < 0)
            word_730 = 0;
    } else if (78 == 71 && word_730 > 0) {
        --word_730;
    }
    if (78 == 71 || 78 == 72 || 78 == 73) {
        if (classify_fighter_x_boundary() && velocity_x_f4 < 0.0f) {
            velocity_x_f4 = static_cast<float>(velocity_x_f4 +
                (78 == 73 ? 2.5 : 1.0));
            if (velocity_x_f4 > 0.0f)
                velocity_x_f4 = 0.0f;
            if (byte_490)
                field_6ac = 78 == 72 ? velocity_x_f4
                    : static_cast<float>(word_730 * -2.0);
        }
        if (78 == 73)
            return;
    }

    if (78 == 76 || 78 == 78) {
        advance_frame_and_dispatch();
        if (frame_counter_144 == 0 && frame_timer_142 == 0
                && frame_index_140 == 0 && sequence_13e == 1) {
            facing_104 = static_cast<signed char>(-facing_104);
            velocity_x_f4 = 78 == 76 ? -3.0f : -5.0f;
            velocity_y_f8 = 78 == 76 ? 10.0f : 3.0f;
            acceleration_y_100 = 0.5f;
            if (word_7a4 == 0) {
                word_7a4 = 1;
                spawn_owned_object_via_manager(951, x_ec, y_f0,
                    static_cast<unsigned char>(facing_104), 1, 0, 0);
            }
        }
        return;
    }
    if (78 == 77 && frame_counter_144 == 0 && frame_timer_142 == 0
            && frame_index_140 == 0 && sequence_13e == 1 && word_7a4 == 0) {
        word_7a4 = 1;
        spawn_owned_object_via_manager(951, x_ec, y_f0,
            static_cast<unsigned char>(facing_104), 1, 0, 0);
    }
#ifdef TH105_REIMU_SHARED_LOW_ADVANCE
    if (78 == 71 || 78 == 72 || 78 == 74)
        goto reimu_advance_frame_and_return;
#endif
    advance_frame_and_dispatch();
    return;

    }
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
            return;
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
                    return;
                }
                set_sequence(2);
                return;
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
        return;
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
                return;
            }
        }
        advance_frame_and_dispatch();
        if (frame_counter_144 == 0 && frame_timer_142 == 0
                && frame_index_140 == 0 && sequence_13e == 1) {
            velocity_x_f4 = static_cast<float>(word_730 * static_cast<double>(0.0025f));
            velocity_y_f8 = static_cast<float>(static_cast<float>(-static_cast<int>(word_732)) * static_cast<double>(0.0025f));
            acceleration_y_100 = 0.25f;
            word_7a0 = 0;
            word_7a2 = static_cast<short>(reimu_frame_85);
            field_108 = static_cast<float>(word_7a0);
            field_10c = static_cast<float>(reimu_frame_85);
        }
        return;
        case 145:
        if (frame_counter_144 == 0 && frame_timer_142 == 0
                && frame_index_140 == 0 && sequence_13e == 1 && word_7a4 == 0) {
            word_7a4 = 1;
            spawn_owned_object_via_manager(951, x_ec, y_f0,
                static_cast<unsigned char>(facing_104), 1, 0, 0);
        }
        if (sequence_13e == 1 && velocity_y_f8 < 2.0f) {
            next_sequence_block();
            return;
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
            return;
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
        return;
        case 197:
        landing_sequence = 2;
        if (197 == 199 || (sequence_13e == 0 && frame_index_140 <= 2)
                || sequence_13e == 2)
            resolve_stage_surface_landing_transition();
        if (197 != 199) {
            if (sequence_13e < 2)
                velocity_y_f8 = static_cast<float>(velocity_y_f8 - acceleration_y_100);
            if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
                goto reimu_land_sequence_658;
            }
        }
        if (advance_frame_and_dispatch()) {
            if (byte_72c == 2) {
                set_action(700);
                word_4a8 = 3;
                word_4ac = 3;
                return;
            }
            set_action(0);
            if (field_6b8 > 0)
                set_action(1);
        }
        if (sequence_13e == 2 && frame_index_140 == (197 == 199 ? 2 : 4)
                && frame_timer_142 == 0) {
            if (x_ec > peer_170->x_ec)
                facing_104 = -1;
            if (x_ec < peer_170->x_ec)
                facing_104 = 1;
        }
        if (197 != 199 && sequence_13e == 0
                && frame_index_140 == 3 && frame_timer_142 == 0) {
            velocity_y_f8 = 4.5f;
            velocity_x_f4 = 197 == 197 ? 12.5f : -12.5f;
            acceleration_y_100 = 0.35f;
        }
        return;
        case 198:
        landing_sequence = 2;
        if (198 == 199 || (sequence_13e == 0 && frame_index_140 <= 2)
                || sequence_13e == 2)
            resolve_stage_surface_landing_transition();
        if (198 != 199) {
            if (sequence_13e < 2)
                velocity_y_f8 = static_cast<float>(velocity_y_f8 - acceleration_y_100);
            if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
                goto reimu_land_sequence_608;
            }
        }
        if (advance_frame_and_dispatch()) {
            if (byte_72c == 2) {
                set_action(700);
                word_4a8 = 3;
                word_4ac = 3;
                return;
            }
            set_action(0);
            if (field_6b8 > 0)
                set_action(1);
        }
        if (sequence_13e == 2 && frame_index_140 == (198 == 199 ? 2 : 4)
                && frame_timer_142 == 0) {
            if (x_ec > peer_170->x_ec)
                facing_104 = -1;
            if (x_ec < peer_170->x_ec)
                facing_104 = 1;
        }
        if (198 != 199 && sequence_13e == 0
                && frame_index_140 == 3 && frame_timer_142 == 0) {
            velocity_y_f8 = 4.5f;
            velocity_x_f4 = 198 == 197 ? 12.5f : -12.5f;
            acceleration_y_100 = 0.35f;
        }
        return;
        case 199:
        if (199 == 199 || (sequence_13e == 0 && frame_index_140 <= 2)
                || sequence_13e == 2)
            resolve_stage_surface_landing_transition();
        if (advance_frame_and_dispatch()) {
            if (byte_72c == 2) {
                set_action(700);
                word_4a8 = 3;
                word_4ac = 3;
                return;
            }
            set_action(0);
            if (field_6b8 > 0)
                set_action(1);
        }
        if (sequence_13e == 2 && frame_index_140 == (199 == 199 ? 2 : 4)
                && frame_timer_142 == 0) {
            if (x_ec > peer_170->x_ec)
                facing_104 = -1;
            if (x_ec < peer_170->x_ec)
                facing_104 = 1;
        }
        if (199 != 199 && sequence_13e == 0
                && frame_index_140 == 3 && frame_timer_142 == 0) {
            velocity_y_f8 = 4.5f;
            velocity_x_f4 = 199 == 197 ? 12.5f : -12.5f;
            acceleration_y_100 = 0.35f;
        }
        return;
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
                    return;
                }
                set_action(211);
                return;
            }
            word_730 = static_cast<short>(word_730 + 1);
            if ((directed_input <= 0 && word_730 > 5) || word_730 > 45) {
                set_action(204);
                return;
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
        return;
        case 201:
        landing_sequence = 3;
        if (sequence_13e == 0 || sequence_13e == landing_sequence)
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
            emit_fighter_effect_byte_direction(124,
                static_cast<float>(x_base - static_cast<float>(mt19937_next_u32() % 100)),
                static_cast<float>(static_cast<float>(mt19937_next_u32() % 200) + y_f0),
                static_cast<unsigned char>(-facing_104), 1);
        }
        if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())
                && sequence_13e < landing_sequence) {
            velocity_y_f8 = 0.0f;
            acceleration_y_100 = 0.0f;
            y_f0 = reimu_stage_surface_height_at_x(this);
            set_sequence(landing_sequence);
            return;
        }
        else {
            if (advance_frame_and_dispatch()) {
                set_action(0);
                velocity_x_f4 = 0.0f;
                return;
            }
            if (frame_counter_144 == 0 && frame_timer_142 == 0
                    && frame_index_140 == 0 && sequence_13e == 1) {
                velocity_x_f4 = -14.0f;
                velocity_y_f8 = 4.0f;
                const float effect_y = static_cast<float>(y_f0 + 80.0);
                emit_fighter_effect_byte_direction(125, x_ec, effect_y,
                    static_cast<unsigned char>(-facing_104), 1);
                emit_fighter_effect_byte_direction(126, x_ec, static_cast<float>(y_f0 + 80.0),
                    static_cast<unsigned char>(-facing_104), 1);
                dispatch_indexed_event_member(31);
            }
            return;
        }
reimu_action_shared_landing_sequence3_tail:
    y_f0 = reimu_stage_surface_height_at_x(this);
    set_sequence(landing_sequence);
    return;
        case 202:
        velocity_y_f8 = static_cast<float>(velocity_y_f8 - acceleration_y_100);
        if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
            // Keep Action202's landing edge inline; later actions use the
            // separate shared tail below to preserve their own branch layout.
            zero_velocity_acceleration();
            y_f0 = reimu_stage_surface_height_at_x(this);
            set_action(10);
            return;
        }
        if (sequence_13e == 1 && frame_counter_144 % 5 == 0) {
            const double x_base = static_cast<double>(x_ec) + 50.0;
            emit_fighter_effect_byte_direction(124,
                static_cast<float>(x_base - static_cast<float>(mt19937_next_u32() % 100)),
                static_cast<float>(static_cast<float>(mt19937_next_u32() % 200) + y_f0),
                static_cast<unsigned char>(facing_104), 1);
        }
        advance_frame_and_dispatch();
        if (sequence_13e == 0 && frame_index_140 == 3 && frame_timer_142 == 0) {
            word_730 = 0;
            velocity_x_f4 = 10.0f;
            velocity_y_f8 = 4.0f;
            acceleration_y_100 = 0.45f;
            const float effect_y = static_cast<float>(y_f0 + 110.0);
            const float effect_x = static_cast<float>(facing_104 * 80 + x_ec);
            emit_fighter_effect_byte_direction(125, effect_x, effect_y,
                static_cast<unsigned char>(facing_104), 1);
            emit_fighter_effect_byte_direction(126, x_ec, static_cast<float>(y_f0 + 110.0),
                static_cast<unsigned char>(facing_104), 1);
            dispatch_indexed_event_member(31);
        }
        if (frame_counter_144 == 0 && frame_timer_142 == 0
                && frame_index_140 == 0 && sequence_13e == 2)
            face_opponent_and_flip_horizontal_velocity();
        return;
        case 203:
        if (frame_counter_144 == 0 && frame_timer_142 == 0
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
            goto reimu_landed_action_10_other;
        }
        if (sequence_13e == 1 && frame_counter_144 % 5 == 0) {
            const double x_base = static_cast<double>(x_ec) + 50.0;
            const unsigned char direction = static_cast<unsigned char>(
                -facing_104);
            emit_fighter_effect(124,
                static_cast<float>(x_base - static_cast<float>(mt19937_next_u32() % 100)),
                static_cast<float>(static_cast<float>(mt19937_next_u32() % 200) + y_f0),
                direction, 1);
        }
        advance_frame_and_dispatch();
        if (frame_counter_144 == 0 && frame_timer_142 == 0
                && frame_index_140 == 0 && sequence_13e == 2)
            face_opponent_and_flip_horizontal_velocity();
        return;
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
        return;

// Shared source fragment; include only within the matching staging context.
        case 208:
        if (sequence_13e == 0)
            resolve_stage_surface_landing_transition();
        if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
            set_action(10);
            y_f0 = reimu_stage_surface_height_at_x(this);
            zero_velocity_acceleration();
            return;
        }
        if (is_at_stage_surface() || velocity_y_f8 > 0.0f)
            word_4ae = 2;
        if (sequence_13e > 0) {
            velocity_y_f8 = static_cast<float>(velocity_y_f8 - acceleration_y_100);
            if (velocity_y_f8 < -20.0f)
                velocity_y_f8 = -20.0f;
        }
        if (208 != 209 && 208 != 210 && 208 != 212
                && sequence_13e == 1 && frame_counter_144 % 5 == 0) {
            const double x_base = static_cast<double>(x_ec) + 50.0;
            const unsigned char direction = static_cast<unsigned char>(facing_104);
            emit_fighter_effect(123,
                static_cast<float>(x_base - static_cast<float>(mt19937_next_u32() % 100)),
                static_cast<float>(static_cast<float>(mt19937_next_u32() % 200) + y_f0),
                direction, 1);
        }
        if (208 != 211 && 208 != 212
                && sequence_13e == 1 && velocity_y_f8 < 4.0f)
            set_sequence(2);
        advance_frame_and_dispatch();
        if (frame_counter_144 == 0 && frame_timer_142 == 0
                && frame_index_140 == 0 && sequence_13e == 1) {
            velocity_x_f4 = 208 == 208 || 208 == 220 ? 0.0f
                : 208 == 209 || 208 == 221 ? 8.0f
                : 208 == 210 || 208 == 222 ? -8.0f
                : 208 == 211 ? 3.0f : 9.0f;
            velocity_y_f8 = 208 == 208 || 208 == 220 ? 20.0f
                : 208 == 211 || 208 == 212 ? 15.0f : 17.5f;
            acceleration_y_100 = 0.65f;
            byte_47e = 0;
            emit_fighter_effect(63, x_ec, y_f0, static_cast<unsigned char>(facing_104), 1);
        }
        return;
        case 209:
        if (sequence_13e == 0)
            resolve_stage_surface_landing_transition();
        if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
            set_action(10);
            y_f0 = reimu_stage_surface_height_at_x(this);
            zero_velocity_acceleration();
            return;
        }
        if (is_at_stage_surface() || velocity_y_f8 > 0.0f)
            word_4ae = 2;
        if (sequence_13e > 0) {
            velocity_y_f8 = static_cast<float>(velocity_y_f8 - acceleration_y_100);
            if (velocity_y_f8 < -20.0f)
                velocity_y_f8 = -20.0f;
        }
        if (209 != 209 && 209 != 210 && 209 != 212
                && sequence_13e == 1 && frame_counter_144 % 5 == 0) {
            const double x_base = static_cast<double>(x_ec) + 50.0;
            const unsigned char direction = static_cast<unsigned char>(facing_104);
            emit_fighter_effect(123,
                static_cast<float>(x_base - static_cast<float>(mt19937_next_u32() % 100)),
                static_cast<float>(static_cast<float>(mt19937_next_u32() % 200) + y_f0),
                direction, 1);
        }
        if (209 != 211 && 209 != 212
                && sequence_13e == 1 && velocity_y_f8 < 4.0f)
            set_sequence(2);
        advance_frame_and_dispatch();
        if (frame_counter_144 == 0 && frame_timer_142 == 0
                && frame_index_140 == 0 && sequence_13e == 1) {
            velocity_x_f4 = 209 == 208 || 209 == 220 ? 0.0f
                : 209 == 209 || 209 == 221 ? 8.0f
                : 209 == 210 || 209 == 222 ? -8.0f
                : 209 == 211 ? 3.0f : 9.0f;
            velocity_y_f8 = 209 == 208 || 209 == 220 ? 20.0f
                : 209 == 211 || 209 == 212 ? 15.0f : 17.5f;
            acceleration_y_100 = 0.65f;
            byte_47e = 0;
            emit_fighter_effect(63, x_ec, y_f0, static_cast<unsigned char>(facing_104), 1);
        }
        return;
        case 210:
        if (sequence_13e == 0)
            resolve_stage_surface_landing_transition();
        if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
            set_action(10);
            y_f0 = reimu_stage_surface_height_at_x(this);
            zero_velocity_acceleration();
            return;
        }
        if (is_at_stage_surface() || velocity_y_f8 > 0.0f)
            word_4ae = 2;
        if (sequence_13e > 0) {
            velocity_y_f8 = static_cast<float>(velocity_y_f8 - acceleration_y_100);
            if (velocity_y_f8 < -20.0f)
                velocity_y_f8 = -20.0f;
        }
        if (210 != 209 && 210 != 210 && 210 != 212
                && sequence_13e == 1 && frame_counter_144 % 5 == 0) {
            const double x_base = static_cast<double>(x_ec) + 50.0;
            const unsigned char direction = static_cast<unsigned char>(facing_104);
            emit_fighter_effect(123,
                static_cast<float>(x_base - static_cast<float>(mt19937_next_u32() % 100)),
                static_cast<float>(static_cast<float>(mt19937_next_u32() % 200) + y_f0),
                direction, 1);
        }
        if (210 != 211 && 210 != 212
                && sequence_13e == 1 && velocity_y_f8 < 4.0f)
            set_sequence(2);
        advance_frame_and_dispatch();
        if (frame_counter_144 == 0 && frame_timer_142 == 0
                && frame_index_140 == 0 && sequence_13e == 1) {
            velocity_x_f4 = 210 == 208 || 210 == 220 ? 0.0f
                : 210 == 209 || 210 == 221 ? 8.0f
                : 210 == 210 || 210 == 222 ? -8.0f
                : 210 == 211 ? 3.0f : 9.0f;
            velocity_y_f8 = 210 == 208 || 210 == 220 ? 20.0f
                : 210 == 211 || 210 == 212 ? 15.0f : 17.5f;
            acceleration_y_100 = 0.65f;
            byte_47e = 0;
            emit_fighter_effect(63, x_ec, y_f0, static_cast<unsigned char>(facing_104), 1);
        }
        return;
        case 211:
        if (sequence_13e == 0)
            resolve_stage_surface_landing_transition();
        if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
            set_action(10);
            y_f0 = reimu_stage_surface_height_at_x(this);
            zero_velocity_acceleration();
            return;
        }
        if (is_at_stage_surface() || velocity_y_f8 > 0.0f)
            word_4ae = 2;
        if (sequence_13e > 0) {
            velocity_y_f8 = static_cast<float>(velocity_y_f8 - acceleration_y_100);
            if (velocity_y_f8 < -20.0f)
                velocity_y_f8 = -20.0f;
        }
        if (211 != 209 && 211 != 210 && 211 != 212
                && sequence_13e == 1 && frame_counter_144 % 5 == 0) {
            const double x_base = static_cast<double>(x_ec) + 50.0;
            const unsigned char direction = static_cast<unsigned char>(facing_104);
            emit_fighter_effect(123,
                static_cast<float>(x_base - static_cast<float>(mt19937_next_u32() % 100)),
                static_cast<float>(static_cast<float>(mt19937_next_u32() % 200) + y_f0),
                direction, 1);
        }
        if (211 != 211 && 211 != 212
                && sequence_13e == 1 && velocity_y_f8 < 4.0f)
            set_sequence(2);
        advance_frame_and_dispatch();
        if (frame_counter_144 == 0 && frame_timer_142 == 0
                && frame_index_140 == 0 && sequence_13e == 1) {
            velocity_x_f4 = 211 == 208 || 211 == 220 ? 0.0f
                : 211 == 209 || 211 == 221 ? 8.0f
                : 211 == 210 || 211 == 222 ? -8.0f
                : 211 == 211 ? 3.0f : 9.0f;
            velocity_y_f8 = 211 == 208 || 211 == 220 ? 20.0f
                : 211 == 211 || 211 == 212 ? 15.0f : 17.5f;
            acceleration_y_100 = 0.65f;
            byte_47e = 0;
            emit_fighter_effect(63, x_ec, y_f0, static_cast<unsigned char>(facing_104), 1);
        }
        return;
        case 212:
        if (sequence_13e == 0)
            resolve_stage_surface_landing_transition();
        if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
            set_action(10);
            y_f0 = reimu_stage_surface_height_at_x(this);
            zero_velocity_acceleration();
            return;
        }
        if (is_at_stage_surface() || velocity_y_f8 > 0.0f)
            word_4ae = 2;
        if (sequence_13e > 0) {
            velocity_y_f8 = static_cast<float>(velocity_y_f8 - acceleration_y_100);
            if (velocity_y_f8 < -20.0f)
                velocity_y_f8 = -20.0f;
        }
        if (212 != 209 && 212 != 210 && 212 != 212
                && sequence_13e == 1 && frame_counter_144 % 5 == 0) {
            const double x_base = static_cast<double>(x_ec) + 50.0;
            const unsigned char direction = static_cast<unsigned char>(facing_104);
            emit_fighter_effect(123,
                static_cast<float>(x_base - static_cast<float>(mt19937_next_u32() % 100)),
                static_cast<float>(static_cast<float>(mt19937_next_u32() % 200) + y_f0),
                direction, 1);
        }
        if (212 != 211 && 212 != 212
                && sequence_13e == 1 && velocity_y_f8 < 4.0f)
            set_sequence(2);
        advance_frame_and_dispatch();
        if (frame_counter_144 == 0 && frame_timer_142 == 0
                && frame_index_140 == 0 && sequence_13e == 1) {
            velocity_x_f4 = 212 == 208 || 212 == 220 ? 0.0f
                : 212 == 209 || 212 == 221 ? 8.0f
                : 212 == 210 || 212 == 222 ? -8.0f
                : 212 == 211 ? 3.0f : 9.0f;
            velocity_y_f8 = 212 == 208 || 212 == 220 ? 20.0f
                : 212 == 211 || 212 == 212 ? 15.0f : 17.5f;
            acceleration_y_100 = 0.65f;
            byte_47e = 0;
            emit_fighter_effect(63, x_ec, y_f0, static_cast<unsigned char>(facing_104), 1);
        }
        return;
        case 214: {
        if (advance_frame_and_dispatch()) {
            set_action(9);
            return;
        }
        if (frame_counter_144 == 0 && frame_timer_142 == 0 && frame_index_140 == 0) {
            if (sequence_13e == 1)
                dispatch_indexed_event_member(31);
        }
        if (frame_counter_144 == 0 && frame_timer_142 == 0
                && frame_index_140 == 0 && sequence_13e == 6) {
            set_action(9);
            return;
        }
        const int directed_input = static_cast<int>(static_cast<unsigned int>(facing_104)
            * static_cast<unsigned int>(field_6b4));
        if (field_6b8 > 0)
            word_732 = directed_input > 0 ? -45 : directed_input < 0 ? -135 : -90;
        else if (field_6b8 < 0)
            word_732 = directed_input > 0 ? 45 : directed_input < 0 ? 135 : 90;
        else if (directed_input > 0)
            word_732 = 0;
        else if (directed_input < 0)
            word_732 = 180;
        if (sequence_13e == 5 || sequence_13e == 6)
            velocity_y_f8 = static_cast<float>(velocity_y_f8 - acceleration_y_100);
        if (sequence_13e > 0 && sequence_13e < 5) {
            word_736 = static_cast<short>(word_736 + 1);
            word_734 = static_cast<short>(word_732 - static_cast<short>(static_cast<int>(field_740)));
            if (word_734 > 180)
                word_734 = static_cast<short>(word_734 - 360);
            if (word_734 < -180)
                word_734 = static_cast<short>(word_734 + 360);
            if (word_734 > 0)
                field_740 = static_cast<float>(field_740 + (field_4b8 == 0 ? 3.0 : 1.0));
            if (word_734 < 0)
                field_740 = static_cast<float>(field_740 - (field_4b8 == 0 ? 3.0 : 1.0));
            velocity_x_f4 = static_cast<float>(lookup_orientation_cosine_quantized_abs(field_740) * field_73c);
            velocity_y_f8 = static_cast<float>(lookup_orientation_sine_quantized_abs(field_740) * field_73c);
            if (y_f0 > 680.0f && velocity_y_f8 > 0.0f)
                velocity_y_f8 = 0.0f;
            field_73c = static_cast<float>(field_73c + static_cast<double>(0.3f));
            if (field_73c > 10.0f)
                field_73c = 10.0f;
            adjust_counter_482(field_4b8 == 0 ? 5 : 10, 1);
            angle_12c = -field_740;
            if (velocity_x_f4 < 0.0f)
                angle_12c = static_cast<float>(180.0 - field_740);
            if (velocity_x_f4 < 0.0f && sequence_13e == 1)
                set_sequence(3);
            if (velocity_x_f4 >= 0.0f && sequence_13e == 3)
                set_sequence(1);
            if (velocity_x_f4 < 0.0f && sequence_13e == 2)
                set_sequence(4);
            if (velocity_x_f4 >= 0.0f && sequence_13e == 4)
                set_sequence(2);
            if (frame_counter_144 % 5 == 1) {
                const unsigned char direction = static_cast<unsigned char>(facing_104);
                emit_fighter_effect(125,
                    static_cast<float>(lookup_orientation_cosine_quantized_abs(field_740) * 100.0 * facing_104 + x_ec),
                    static_cast<float>((lookup_orientation_sine_quantized_abs(field_740) * 100.0 + y_f0) + 100.0),
                    direction, 1);
            }
            // Keep one ordinary resource condition; physical gate duplication
            // also depends on the facing branches and compiler visibility.
            if ((field_6c8 == 0 && word_736 > 10) || word_482 <= 0) {
                reinterpret_cast<ReimuRecoverySpriteView *>(
                    reinterpret_cast<unsigned char *>(this) + 4)->reset_fighter_action_scratch();
                if (sequence_13e == 1 || sequence_13e == 2) {
                    if (facing_104 == 1) {
                        if (x_ec > peer_170->x_ec) {
                            facing_104 = static_cast<signed char>(-facing_104);
                            velocity_x_f4 = -velocity_x_f4;
                            set_sequence(6);
                        } else {
                            set_sequence(5);
                        }
                    } else {
                        if (x_ec < peer_170->x_ec) {
                            facing_104 = static_cast<signed char>(-facing_104);
                            velocity_x_f4 = -velocity_x_f4;
                            set_sequence(6);
                        } else {
                            set_sequence(5);
                        }
                    }
                }
                if (sequence_13e == 3 || sequence_13e == 4) {
                    if (facing_104 == 1) {
                        if (x_ec > peer_170->x_ec) {
                            facing_104 = static_cast<signed char>(-facing_104);
                            velocity_x_f4 = -velocity_x_f4;
                            set_sequence(5);
                        } else {
                            set_sequence(6);
                        }
                    } else {
                        if (x_ec < peer_170->x_ec) {
                            facing_104 = static_cast<signed char>(-facing_104);
                            velocity_x_f4 = -velocity_x_f4;
                            set_sequence(5);
                        } else {
                            set_sequence(6);
                        }
                    }
                }
                return;
            }
        }
        if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
            y_f0 = reimu_stage_surface_height_at_x(this);
            velocity_y_f8 = 0.0f;
            if (sequence_13e < 5) {
                reinterpret_cast<ReimuRecoverySpriteView *>(
                    reinterpret_cast<unsigned char *>(this) + 4)->reset_fighter_action_scratch();
                set_action(215);
            } else {
                set_action(10);
                zero_velocity_acceleration();
            }
        }
        return;
    }
        case 215:
        resolve_stage_surface_landing_transition();
        if (velocity_x_f4 > 0.0f) {
            velocity_x_f4 = static_cast<float>(velocity_x_f4 - 0.75);
            if (velocity_x_f4 < 0.0f)
                velocity_x_f4 = 0.0f;
        }
        if (velocity_x_f4 < 0.0f) {
            velocity_x_f4 = static_cast<float>(velocity_x_f4 + 0.75);
            if (velocity_x_f4 > 0.0f)
                velocity_x_f4 = 0.0f;
        }
        if (advance_frame_and_dispatch())
            set_action(0);
        return;
        case 220:
        if (sequence_13e == 0)
            resolve_stage_surface_landing_transition();
        if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
            set_action(10);
            y_f0 = reimu_stage_surface_height_at_x(this);
            zero_velocity_acceleration();
            return;
        }
        if (is_at_stage_surface() || velocity_y_f8 > 0.0f)
            word_4ae = 2;
        if (sequence_13e > 0) {
            velocity_y_f8 = static_cast<float>(velocity_y_f8 - acceleration_y_100);
            if (velocity_y_f8 < -20.0f)
                velocity_y_f8 = -20.0f;
        }
        if (220 != 209 && 220 != 210 && 220 != 212
                && sequence_13e == 1 && frame_counter_144 % 5 == 0) {
            const double x_base = static_cast<double>(x_ec) + 50.0;
            const unsigned char direction = static_cast<unsigned char>(facing_104);
            emit_fighter_effect(123,
                static_cast<float>(x_base - static_cast<float>(mt19937_next_u32() % 100)),
                static_cast<float>(static_cast<float>(mt19937_next_u32() % 200) + y_f0),
                direction, 1);
        }
        if (220 != 211 && 220 != 212
                && sequence_13e == 1 && velocity_y_f8 < 4.0f)
            set_sequence(2);
        advance_frame_and_dispatch();
        if (frame_counter_144 == 0 && frame_timer_142 == 0
                && frame_index_140 == 0 && sequence_13e == 1) {
            velocity_x_f4 = 220 == 208 || 220 == 220 ? 0.0f
                : 220 == 209 || 220 == 221 ? 8.0f
                : 220 == 210 || 220 == 222 ? -8.0f
                : 220 == 211 ? 3.0f : 9.0f;
            velocity_y_f8 = 220 == 208 || 220 == 220 ? 20.0f
                : 220 == 211 || 220 == 212 ? 15.0f : 17.5f;
            acceleration_y_100 = 0.65f;
            byte_47e = 0;
            emit_fighter_effect(63, x_ec, y_f0, static_cast<unsigned char>(facing_104), 1);
        }
        return;
        case 221:
        if (sequence_13e == 0)
            resolve_stage_surface_landing_transition();
        if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
            set_action(10);
            y_f0 = reimu_stage_surface_height_at_x(this);
            zero_velocity_acceleration();
            return;
        }
        if (is_at_stage_surface() || velocity_y_f8 > 0.0f)
            word_4ae = 2;
        if (sequence_13e > 0) {
            velocity_y_f8 = static_cast<float>(velocity_y_f8 - acceleration_y_100);
            if (velocity_y_f8 < -20.0f)
                velocity_y_f8 = -20.0f;
        }
        if (221 != 209 && 221 != 210 && 221 != 212
                && sequence_13e == 1 && frame_counter_144 % 5 == 0) {
            const double x_base = static_cast<double>(x_ec) + 50.0;
            const unsigned char direction = static_cast<unsigned char>(facing_104);
            emit_fighter_effect(123,
                static_cast<float>(x_base - static_cast<float>(mt19937_next_u32() % 100)),
                static_cast<float>(static_cast<float>(mt19937_next_u32() % 200) + y_f0),
                direction, 1);
        }
        if (221 != 211 && 221 != 212
                && sequence_13e == 1 && velocity_y_f8 < 4.0f)
            set_sequence(2);
        advance_frame_and_dispatch();
        if (frame_counter_144 == 0 && frame_timer_142 == 0
                && frame_index_140 == 0 && sequence_13e == 1) {
            velocity_x_f4 = 221 == 208 || 221 == 220 ? 0.0f
                : 221 == 209 || 221 == 221 ? 8.0f
                : 221 == 210 || 221 == 222 ? -8.0f
                : 221 == 211 ? 3.0f : 9.0f;
            velocity_y_f8 = 221 == 208 || 221 == 220 ? 20.0f
                : 221 == 211 || 221 == 212 ? 15.0f : 17.5f;
            acceleration_y_100 = 0.65f;
            byte_47e = 0;
            emit_fighter_effect(63, x_ec, y_f0, static_cast<unsigned char>(facing_104), 1);
        }
        return;
        case 222:
        if (sequence_13e == 0)
            resolve_stage_surface_landing_transition();
        if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
            set_action(10);
            y_f0 = reimu_stage_surface_height_at_x(this);
            zero_velocity_acceleration();
            return;
        }
        if (is_at_stage_surface() || velocity_y_f8 > 0.0f)
            word_4ae = 2;
        if (sequence_13e > 0) {
            velocity_y_f8 = static_cast<float>(velocity_y_f8 - acceleration_y_100);
            if (velocity_y_f8 < -20.0f)
                velocity_y_f8 = -20.0f;
        }
        if (222 != 209 && 222 != 210 && 222 != 212
                && sequence_13e == 1 && frame_counter_144 % 5 == 0) {
            const double x_base = static_cast<double>(x_ec) + 50.0;
            const unsigned char direction = static_cast<unsigned char>(facing_104);
            emit_fighter_effect(123,
                static_cast<float>(x_base - static_cast<float>(mt19937_next_u32() % 100)),
                static_cast<float>(static_cast<float>(mt19937_next_u32() % 200) + y_f0),
                direction, 1);
        }
        if (222 != 211 && 222 != 212
                && sequence_13e == 1 && velocity_y_f8 < 4.0f)
            set_sequence(2);
        advance_frame_and_dispatch();
        if (frame_counter_144 == 0 && frame_timer_142 == 0
                && frame_index_140 == 0 && sequence_13e == 1) {
            velocity_x_f4 = 222 == 208 || 222 == 220 ? 0.0f
                : 222 == 209 || 222 == 221 ? 8.0f
                : 222 == 210 || 222 == 222 ? -8.0f
                : 222 == 211 ? 3.0f : 9.0f;
            velocity_y_f8 = 222 == 208 || 222 == 220 ? 20.0f
                : 222 == 211 || 222 == 212 ? 15.0f : 17.5f;
            acceleration_y_100 = 0.65f;
            byte_47e = 0;
            emit_fighter_effect(63, x_ec, y_f0, static_cast<unsigned char>(facing_104), 1);
        }
        return;
        case 223:
        resolve_stage_surface_landing_transition();
        byte_47e = 1;
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
            word_730 = static_cast<short>(word_730 + 1);
            const int directed_input = static_cast<int>(static_cast<unsigned int>(facing_104)
                * static_cast<unsigned int>(field_6b4));
            if ((directed_input <= 0 && word_730 > 12) || word_730 > 45) {
                set_action(204);
                return;
            }
        }
        if (sequence_13e == 0 && frame_index_140 == 3 && frame_timer_142 == 0) {
            velocity_x_f4 = 7.5f;
            word_730 = static_cast<short>(word_730 + 1);
            const float effect_y = static_cast<float>(y_f0 + 80.0);
            const float effect_x = static_cast<float>(facing_104 * 80 + x_ec);
            emit_fighter_effect(125, effect_x, effect_y, static_cast<unsigned char>(facing_104), 1);
            emit_fighter_effect(126, x_ec, static_cast<float>(y_f0 + 80.0),
                static_cast<unsigned char>(facing_104), 1);
            dispatch_indexed_event_member(31);
        }
        return;
        case 224:
        landing_sequence = 3;
        if (sequence_13e == 0 || sequence_13e == landing_sequence)
            resolve_stage_surface_landing_transition();
        if (sequence_13e == 1 || sequence_13e == 2)
            velocity_y_f8 = static_cast<float>(velocity_y_f8 - 0.5);
        if (sequence_13e == 3) {
            velocity_x_f4 = static_cast<float>(velocity_x_f4 + 2.0);
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
        if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())
                && sequence_13e < landing_sequence) {
            velocity_y_f8 = 0.0f;
            goto reimu_action_shared_landing_sequence3_tail;
        }
        if (advance_frame_and_dispatch()) {
            set_action(0);
            velocity_x_f4 = 0.0f;
            return;
        }
        if (frame_counter_144 == 0 && frame_timer_142 == 0 && frame_index_140 == 0
                && sequence_13e == 1 && word_730 == 0) {
            word_730 = 1;
            velocity_x_f4 = -14.0f;
            velocity_y_f8 = 4.0f;
            const float effect_y = static_cast<float>(y_f0 + 80.0);
            emit_fighter_effect(125, x_ec, effect_y, static_cast<unsigned char>(-facing_104), 1);
            emit_fighter_effect(126, x_ec, static_cast<float>(y_f0 + 80.0),
                static_cast<unsigned char>(-facing_104), 1);
            dispatch_indexed_event_member(31);
        }
        return;
        case 225:
        if (225 == 226 || sequence_13e >= 1)
            velocity_y_f8 = static_cast<float>(velocity_y_f8 - acceleration_y_100);
        if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
            goto reimu_landed_action_10_other;
        }
        if (sequence_13e == 2 && frame_counter_144 % 5 == 0) {
            const double x_base = static_cast<double>(x_ec) + 50.0;
            const unsigned char direction = static_cast<unsigned char>(
                225 == 226 ? facing_104 : -facing_104);
            emit_fighter_effect(124,
                static_cast<float>(x_base - static_cast<float>(mt19937_next_u32() % 100)),
                static_cast<float>(static_cast<float>(mt19937_next_u32() % 200) + y_f0),
                direction, 1);
        }
        if (advance_frame_and_dispatch())
            set_action(9);
        if (frame_counter_144 == 0 && frame_timer_142 == 0
                && frame_index_140 == 0 && sequence_13e == 1) {
            if (225 == 226)
                word_730 = 0;
            velocity_x_f4 = 225 == 226 ? 10.0f : -10.0f;
            velocity_y_f8 = 4.0f;
            acceleration_y_100 = 0.45f;
            const float effect_y = static_cast<float>(y_f0 + (225 == 226 ? 110.0 : 120.0));
            const float effect_x = 225 == 226 ? static_cast<float>(facing_104 * 80 + x_ec) : x_ec;
            const unsigned char direction = static_cast<unsigned char>(
                225 == 226 ? facing_104 : -facing_104);
            emit_fighter_effect(125, effect_x, effect_y, direction, 1);
            emit_fighter_effect(126, x_ec,
                static_cast<float>(y_f0 + (225 == 226 ? 110.0 : 120.0)),
                static_cast<unsigned char>(225 == 226 ? facing_104 : -facing_104), 1);
            dispatch_indexed_event_member(31);
        }
        if (225 == 226 && frame_counter_144 == 0 && frame_timer_142 == 0
                && frame_index_140 == 0 && sequence_13e == 3)
            face_opponent_and_flip_horizontal_velocity();
        return;
        case 226:
        if (226 == 226 || sequence_13e >= 1)
            velocity_y_f8 = static_cast<float>(velocity_y_f8 - acceleration_y_100);
        if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
            goto reimu_landed_action_10_other;
        }
        if (sequence_13e == 2 && frame_counter_144 % 5 == 0) {
            const double x_base = static_cast<double>(x_ec) + 50.0;
            const unsigned char direction = static_cast<unsigned char>(
                226 == 226 ? facing_104 : -facing_104);
            emit_fighter_effect(124,
                static_cast<float>(x_base - static_cast<float>(mt19937_next_u32() % 100)),
                static_cast<float>(static_cast<float>(mt19937_next_u32() % 200) + y_f0),
                direction, 1);
        }
        if (advance_frame_and_dispatch())
            set_action(9);
        if (frame_counter_144 == 0 && frame_timer_142 == 0
                && frame_index_140 == 0 && sequence_13e == 1) {
            if (226 == 226)
                word_730 = 0;
            velocity_x_f4 = 226 == 226 ? 10.0f : -10.0f;
            velocity_y_f8 = 4.0f;
            acceleration_y_100 = 0.45f;
            const float effect_y = static_cast<float>(y_f0 + (226 == 226 ? 110.0 : 120.0));
            const float effect_x = 226 == 226 ? static_cast<float>(facing_104 * 80 + x_ec) : x_ec;
            const unsigned char direction = static_cast<unsigned char>(
                226 == 226 ? facing_104 : -facing_104);
            emit_fighter_effect(125, effect_x, effect_y, direction, 1);
            emit_fighter_effect(126, x_ec,
                static_cast<float>(y_f0 + (226 == 226 ? 110.0 : 120.0)),
                static_cast<unsigned char>(226 == 226 ? facing_104 : -facing_104), 1);
            dispatch_indexed_event_member(31);
        }
        if (226 == 226 && frame_counter_144 == 0 && frame_timer_142 == 0
                && frame_index_140 == 0 && sequence_13e == 3)
            face_opponent_and_flip_horizontal_velocity();
        return;
        case 300: {
        resolve_stage_surface_landing_transition();
        reimu_directional_result = try_dispatch_directional_action_208_210(0);
        if (reimu_directional_result)
            return;
        if (byte_47e != reimu_directional_result) {
            velocity_x_f4 = static_cast<float>(velocity_x_f4 - 0.5);
            if (0.0f > velocity_x_f4) {
                velocity_x_f4 = 0.0f;
                byte_47e = 0;
            }
        }
        if (advance_frame_and_dispatch())
            set_action(0);
    }
reimu_action_300_320_event_gate:
    if (frame_timer_142 == 0 && frame_index_140 == 3) {
        dispatch_indexed_event_member(27);
        byte_47e = 0;
    }
    return;

// Shared source fragment for the first middle-table group; no function boundary.
        case 301:
        resolve_stage_surface_landing_transition();
        if (try_dispatch_directional_action_208_210(0))
            return;
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
        return;
        case 302:
        resolve_stage_surface_landing_transition();
        if (try_dispatch_directional_action_208_210(1))
            return;
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
                    return;
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
        return;
        case 303:
        resolve_stage_surface_landing_transition();
        if (try_dispatch_directional_action_208_210(0))
            return;
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
        return;
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
            return;
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
                return;
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
            return;
        }
        if (frame_counter_144 == 0 && frame_timer_142 == 0
                && frame_index_140 == 0 && sequence_13e == 4) {
            velocity_x_f4 = 18.0f;
            velocity_y_f8 = 5.0f;
            acceleration_y_100 = 1.0f;
        }
        return;
        case 305:
        resolve_stage_surface_landing_transition();
        if (try_dispatch_directional_action_208_210(1))
            return;
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
        return;
        case 306:
        velocity_y_f8 = static_cast<float>(velocity_y_f8 - acceleration_y_100);
        if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
            set_action(10);
            y_f0 = reimu_stage_surface_height_at_x(this);
            zero_velocity_acceleration();
            return;
        }
        if (306 == 306 && sequence_13e == 1 && frame_counter_144 > 12)
            next_sequence_block();
        if (306 == 307 && frame_index_140 > 2) {
            velocity_x_f4 = static_cast<float>(velocity_x_f4 - 0.5);
            if (velocity_x_f4 < 6.0f)
                velocity_x_f4 = 6.0f;
        }
        if (advance_frame_and_dispatch())
            set_action(9);
        if (306 == 306 && sequence_13e == 0
                && frame_index_140 == 1 && frame_timer_142 == 0) {
            dispatch_indexed_event_member(27);
            const float parameters[3] = {0.0f, 0.0f, 3.0f};
            spawn_owned_object_via_manager(848,
                static_cast<float>(static_cast<float>(facing_104 * 150) + x_ec),
                static_cast<float>(y_f0 + 65.0),
                static_cast<unsigned char>(facing_104), 1, parameters, 3);
        }
        if (306 == 307 && frame_timer_142 == 0 && frame_index_140 == 2) {
            dispatch_indexed_event_member(29);
            velocity_x_f4 = 15.0f;
            velocity_y_f8 = 5.0f;
            acceleration_y_100 = 0.35f;
        }
        if (306 == 308) {
            if (frame_timer_142 == 0 && frame_index_140 == 4) {
                dispatch_indexed_event_member(29);
                const float parameters[3] = {0.0f, 0.0f, 5.0f};
                spawn_owned_object_via_manager(848, x_ec, y_f0,
                    static_cast<unsigned char>(facing_104), 1, parameters, 3);
            }
            if (sequence_13e == 1 && frame_counter_144 > 10)
                next_sequence_block();
        }
        if (306 == 309 && frame_timer_142 == 0 && frame_index_140 == 2) {
            dispatch_indexed_event_member(29);
            velocity_x_f4 = 5.0f;
            velocity_y_f8 = 15.0f;
            acceleration_y_100 = 0.9f;
        }
        return;
        case 307:
        velocity_y_f8 = static_cast<float>(velocity_y_f8 - acceleration_y_100);
        if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
            set_action(10);
            y_f0 = reimu_stage_surface_height_at_x(this);
            zero_velocity_acceleration();
            return;
        }
        if (307 == 306 && sequence_13e == 1 && frame_counter_144 > 12)
            next_sequence_block();
        if (307 == 307 && frame_index_140 > 2) {
            velocity_x_f4 = static_cast<float>(velocity_x_f4 - 0.5);
            if (velocity_x_f4 < 6.0f)
                velocity_x_f4 = 6.0f;
        }
        if (advance_frame_and_dispatch())
            set_action(9);
        if (307 == 306 && sequence_13e == 0
                && frame_index_140 == 1 && frame_timer_142 == 0) {
            dispatch_indexed_event_member(27);
            const float parameters[3] = {0.0f, 0.0f, 3.0f};
            spawn_owned_object_via_manager(848,
                static_cast<float>(static_cast<float>(facing_104 * 150) + x_ec),
                static_cast<float>(y_f0 + 65.0),
                static_cast<unsigned char>(facing_104), 1, parameters, 3);
        }
        if (307 == 307 && frame_timer_142 == 0 && frame_index_140 == 2) {
            dispatch_indexed_event_member(29);
            velocity_x_f4 = 15.0f;
            velocity_y_f8 = 5.0f;
            acceleration_y_100 = 0.35f;
        }
        if (307 == 308) {
            if (frame_timer_142 == 0 && frame_index_140 == 4) {
                dispatch_indexed_event_member(29);
                const float parameters[3] = {0.0f, 0.0f, 5.0f};
                spawn_owned_object_via_manager(848, x_ec, y_f0,
                    static_cast<unsigned char>(facing_104), 1, parameters, 3);
            }
            if (sequence_13e == 1 && frame_counter_144 > 10)
                next_sequence_block();
        }
        if (307 == 309 && frame_timer_142 == 0 && frame_index_140 == 2) {
            dispatch_indexed_event_member(29);
            velocity_x_f4 = 5.0f;
            velocity_y_f8 = 15.0f;
            acceleration_y_100 = 0.9f;
        }
        return;
        case 308:
        velocity_y_f8 = static_cast<float>(velocity_y_f8 - acceleration_y_100);
        if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
            set_action(10);
            y_f0 = reimu_stage_surface_height_at_x(this);
            zero_velocity_acceleration();
            return;
        }
        if (308 == 306 && sequence_13e == 1 && frame_counter_144 > 12)
            next_sequence_block();
        if (308 == 307 && frame_index_140 > 2) {
            velocity_x_f4 = static_cast<float>(velocity_x_f4 - 0.5);
            if (velocity_x_f4 < 6.0f)
                velocity_x_f4 = 6.0f;
        }
        if (advance_frame_and_dispatch())
            set_action(9);
        if (308 == 306 && sequence_13e == 0
                && frame_index_140 == 1 && frame_timer_142 == 0) {
            dispatch_indexed_event_member(27);
            const float parameters[3] = {0.0f, 0.0f, 3.0f};
            spawn_owned_object_via_manager(848,
                static_cast<float>(static_cast<float>(facing_104 * 150) + x_ec),
                static_cast<float>(y_f0 + 65.0),
                static_cast<unsigned char>(facing_104), 1, parameters, 3);
        }
        if (308 == 307 && frame_timer_142 == 0 && frame_index_140 == 2) {
            dispatch_indexed_event_member(29);
            velocity_x_f4 = 15.0f;
            velocity_y_f8 = 5.0f;
            acceleration_y_100 = 0.35f;
        }
        if (308 == 308) {
            if (frame_timer_142 == 0 && frame_index_140 == 4) {
                dispatch_indexed_event_member(29);
                const float parameters[3] = {0.0f, 0.0f, 5.0f};
                spawn_owned_object_via_manager(848, x_ec, y_f0,
                    static_cast<unsigned char>(facing_104), 1, parameters, 3);
            }
            if (sequence_13e == 1 && frame_counter_144 > 10)
                next_sequence_block();
        }
        if (308 == 309 && frame_timer_142 == 0 && frame_index_140 == 2) {
            dispatch_indexed_event_member(29);
            velocity_x_f4 = 5.0f;
            velocity_y_f8 = 15.0f;
            acceleration_y_100 = 0.9f;
        }
        return;
        case 309:
        velocity_y_f8 = static_cast<float>(velocity_y_f8 - acceleration_y_100);
        if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
            set_action(10);
            y_f0 = reimu_stage_surface_height_at_x(this);
            zero_velocity_acceleration();
            return;
        }
        if (309 == 306 && sequence_13e == 1 && frame_counter_144 > 12)
            next_sequence_block();
        if (309 == 307 && frame_index_140 > 2) {
            velocity_x_f4 = static_cast<float>(velocity_x_f4 - 0.5);
            if (velocity_x_f4 < 6.0f)
                velocity_x_f4 = 6.0f;
        }
        if (advance_frame_and_dispatch())
            set_action(9);
        if (309 == 306 && sequence_13e == 0
                && frame_index_140 == 1 && frame_timer_142 == 0) {
            dispatch_indexed_event_member(27);
            const float parameters[3] = {0.0f, 0.0f, 3.0f};
            spawn_owned_object_via_manager(848,
                static_cast<float>(static_cast<float>(facing_104 * 150) + x_ec),
                static_cast<float>(y_f0 + 65.0),
                static_cast<unsigned char>(facing_104), 1, parameters, 3);
        }
        if (309 == 307 && frame_timer_142 == 0 && frame_index_140 == 2) {
            dispatch_indexed_event_member(29);
            velocity_x_f4 = 15.0f;
            velocity_y_f8 = 5.0f;
            acceleration_y_100 = 0.35f;
        }
        if (309 == 308) {
            if (frame_timer_142 == 0 && frame_index_140 == 4) {
                dispatch_indexed_event_member(29);
                const float parameters[3] = {0.0f, 0.0f, 5.0f};
                spawn_owned_object_via_manager(848, x_ec, y_f0,
                    static_cast<unsigned char>(facing_104), 1, parameters, 3);
            }
            if (sequence_13e == 1 && frame_counter_144 > 10)
                next_sequence_block();
        }
        if (309 == 309 && frame_timer_142 == 0 && frame_index_140 == 2) {
            dispatch_indexed_event_member(29);
            velocity_x_f4 = 5.0f;
            velocity_y_f8 = 15.0f;
            acceleration_y_100 = 0.9f;
        }
        return;
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
                return;
            }
        }
        if (sequence_13e == 2) {
            velocity_x_f4 = static_cast<float>(velocity_x_f4 - 1.0);
            if (velocity_x_f4 < 0.0f)
                velocity_x_f4 = 0.0f;
        }
        if (advance_frame_and_dispatch())
            set_action(0);
        return;
        case 320: {
        resolve_stage_surface_landing_transition();
        reimu_directional_result = try_dispatch_directional_action_208_210(0);
        if (reimu_directional_result)
            return;
        if (byte_47e == reimu_directional_result)
            goto reimu_action_320_advance;
        velocity_x_f4 = static_cast<float>(velocity_x_f4 - 0.5);
        if (velocity_x_f4 < 0.0f) {
            velocity_x_f4 = 0.0f;
            byte_47e = 0;
        }
reimu_action_320_advance:
        if (advance_frame_and_dispatch())
            set_action(0);

        goto reimu_action_300_320_event_gate;
    }
        case 321:
        resolve_stage_surface_landing_transition();
        if (try_dispatch_directional_action_208_210(0))
            return;
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
        return;
        case 322:
        resolve_stage_surface_landing_transition();
        if (try_dispatch_directional_action_208_210(1))
            return;
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
        return;

// Shared middle-table statements; not an original callable boundary.
        case 400: {
        const bool aerial = 400 == 404 || 400 == 406;
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
                return;
            }
        }
        if (sequence_13e == 0 && field_6c0 == 0)
            byte_750 = 0;
        if (word_730 > 0) {
            word_730 = static_cast<short>(word_730 + 1);
            if (byte_750 == 0) {
                if (word_730 % 3 == 1 && word_732 < 5) {
                    state_180 = 1;
                    if (aerial)
                        add_scaled_counter(10);
                    if (word_732 == 0)
                        adjust_counter_482(200, 45);
                    if (400 == 401)
                        add_scaled_counter(10);
                    const int x_offset = 400 == 400 ? 114
                        : 400 == 401 ? 90 : 400 == 404 ? 83 : 67;
                    const double y_offset = 400 == 400 ? 96.0
                        : 400 == 401 ? 158.0 : 400 == 404 ? 117.0 : 75.0;
                    float parameters[3] = {
                        static_cast<float>((word_732 - 2) * 5 + word_734), 15.0f, 0.0f};
                    if (400 == 400)
                        add_scaled_counter(10);
                    spawn_owned_object_via_manager(800,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    dispatch_character_wave_handle(0);
                    word_732 = static_cast<short>(word_732 + 1);
                }
            } else {
                if (word_730 % 3 == 1 && word_732 < 5) {
                    state_180 = 1;
                    if (aerial)
                        add_scaled_counter(10);
                    if (word_732 == 0)
                        adjust_counter_482(200, 45);
                    if (400 == 401)
                        add_scaled_counter(10);
                    const int x_offset = 400 == 400 ? 114
                        : 400 == 401 ? 90 : 400 == 404 ? 83 : 67;
                    const double y_offset = 400 == 400 ? 96.0
                        : 400 == 401 ? 158.0 : 400 == 404 ? 117.0 : 75.0;
                    float parameters[3] = {
                        static_cast<float>((word_732 - 2) * 5 + word_734), 15.0f, 0.0f};
                    if (400 == 400)
                        add_scaled_counter(10);
                    for (int count = 2; count != 0; --count) {
                        parameters[0] = static_cast<float>(
                            random_receiver_004()->selector_random_range(0, 30) + word_734 - 15);
                        parameters[1] = static_cast<float>(
                            15 - random_receiver_004()->selector_random_range(0, 5));
                        spawn_owned_object_via_manager(800,
                            static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                            static_cast<float>(y_f0 + y_offset),
                            static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    }
                    dispatch_character_wave_handle(0);
                    word_732 = static_cast<short>(word_732 + 1);
                }
            }
        }
        if (advance_frame_and_dispatch())
            set_action(0);
        if (frame_counter_144 == 0 && frame_timer_142 == 0
                && frame_index_140 == 0 && sequence_13e == 1 && byte_750 == 1) {
            if (400 != 406)
                set_sequence(4);
            emit_fighter_effect(62,
                aerial ? static_cast<float>(x_ec - static_cast<float>(facing_104 * 35))
                       : static_cast<float>(static_cast<float>(facing_104 * 65) + x_ec),
                static_cast<float>(y_f0 + (aerial ? 135.0 : 55.0)),
                static_cast<unsigned char>(facing_104), 1);
            if (400 == 406)
                set_sequence(4);
            return;
        }
        if (frame_counter_144 == 0 && frame_timer_142 == 0
                && frame_index_140 == 0 && sequence_13e == 2) {
            const float delta_x = static_cast<float>(
                (static_cast<double>(peer_170->x_ec) - x_ec) * facing_104);
            const short angle = static_cast<short>(static_cast<int>(atan2_degrees(
                static_cast<float>(static_cast<double>(peer_170->y_f0) - y_f0), delta_x)));
            word_734 = static_cast<short>(-angle);
            const short lower = 400 == 401 ? -60 : 400 == 406 ? 40 : -30;
            const short upper = 400 == 401 ? -40 : 400 == 406 ? 60 : 30;
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
            const short angle = static_cast<short>(static_cast<int>(atan2_degrees(
                static_cast<float>(static_cast<double>(peer_170->y_f0) - y_f0), delta_x)));
            word_734 = static_cast<short>(-angle);
            const short lower = 400 == 401 ? -60 : 400 == 406 ? 40 : -30;
            const short upper = 400 == 401 ? -40 : 400 == 406 ? 60 : 30;
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
        return;
    }
        case 401: {
        const bool aerial = 401 == 404 || 401 == 406;
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
                return;
            }
        }
        if (sequence_13e == 0 && field_6c0 == 0)
            byte_750 = 0;
        if (word_730 > 0) {
            word_730 = static_cast<short>(word_730 + 1);
            if (byte_750 == 0) {
                if (word_730 % 3 == 1 && word_732 < 5) {
                    state_180 = 1;
                    if (aerial)
                        add_scaled_counter(10);
                    if (word_732 == 0)
                        adjust_counter_482(200, 45);
                    if (401 == 401)
                        add_scaled_counter(10);
                    const int x_offset = 401 == 400 ? 114
                        : 401 == 401 ? 90 : 401 == 404 ? 83 : 67;
                    const double y_offset = 401 == 400 ? 96.0
                        : 401 == 401 ? 158.0 : 401 == 404 ? 117.0 : 75.0;
                    float parameters[3] = {
                        static_cast<float>((word_732 - 2) * 5 + word_734), 15.0f, 0.0f};
                    if (401 == 400)
                        add_scaled_counter(10);
                    spawn_owned_object_via_manager(800,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    dispatch_character_wave_handle(0);
                    word_732 = static_cast<short>(word_732 + 1);
                }
            } else {
                if (word_730 % 3 == 1 && word_732 < 5) {
                    state_180 = 1;
                    if (aerial)
                        add_scaled_counter(10);
                    if (word_732 == 0)
                        adjust_counter_482(200, 45);
                    if (401 == 401)
                        add_scaled_counter(10);
                    const int x_offset = 401 == 400 ? 114
                        : 401 == 401 ? 90 : 401 == 404 ? 83 : 67;
                    const double y_offset = 401 == 400 ? 96.0
                        : 401 == 401 ? 158.0 : 401 == 404 ? 117.0 : 75.0;
                    float parameters[3] = {
                        static_cast<float>((word_732 - 2) * 5 + word_734), 15.0f, 0.0f};
                    if (401 == 400)
                        add_scaled_counter(10);
                    for (int count = 2; count != 0; --count) {
                        parameters[0] = static_cast<float>(
                            random_receiver_004()->selector_random_range(0, 30) + word_734 - 15);
                        parameters[1] = static_cast<float>(
                            15 - random_receiver_004()->selector_random_range(0, 5));
                        spawn_owned_object_via_manager(800,
                            static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                            static_cast<float>(y_f0 + y_offset),
                            static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    }
                    dispatch_character_wave_handle(0);
                    word_732 = static_cast<short>(word_732 + 1);
                }
            }
        }
        if (advance_frame_and_dispatch())
            set_action(0);
        if (frame_counter_144 == 0 && frame_timer_142 == 0
                && frame_index_140 == 0 && sequence_13e == 1 && byte_750 == 1) {
            if (401 != 406)
                set_sequence(4);
            emit_fighter_effect(62,
                aerial ? static_cast<float>(x_ec - static_cast<float>(facing_104 * 35))
                       : static_cast<float>(static_cast<float>(facing_104 * 65) + x_ec),
                static_cast<float>(y_f0 + (aerial ? 135.0 : 55.0)),
                static_cast<unsigned char>(facing_104), 1);
            if (401 == 406)
                set_sequence(4);
            return;
        }
        if (frame_counter_144 == 0 && frame_timer_142 == 0
                && frame_index_140 == 0 && sequence_13e == 2) {
            const float delta_x = static_cast<float>(
                (static_cast<double>(peer_170->x_ec) - x_ec) * facing_104);
            const short angle = static_cast<short>(static_cast<int>(atan2_degrees(
                static_cast<float>(static_cast<double>(peer_170->y_f0) - y_f0), delta_x)));
            word_734 = static_cast<short>(-angle);
            const short lower = 401 == 401 ? -60 : 401 == 406 ? 40 : -30;
            const short upper = 401 == 401 ? -40 : 401 == 406 ? 60 : 30;
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
            const short angle = static_cast<short>(static_cast<int>(atan2_degrees(
                static_cast<float>(static_cast<double>(peer_170->y_f0) - y_f0), delta_x)));
            word_734 = static_cast<short>(-angle);
            const short lower = 401 == 401 ? -60 : 401 == 406 ? 40 : -30;
            const short upper = 401 == 401 ? -40 : 401 == 406 ? 60 : 30;
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
        return;
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
            return;
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
        return;
        case 404: {
        const bool aerial = 404 == 404 || 404 == 406;
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
                return;
            }
        }
        if (sequence_13e == 0 && field_6c0 == 0)
            byte_750 = 0;
        if (word_730 > 0) {
            word_730 = static_cast<short>(word_730 + 1);
            if (byte_750 == 0) {
                if (word_730 % 3 == 1 && word_732 < 5) {
                    state_180 = 1;
                    if (aerial)
                        add_scaled_counter(10);
                    if (word_732 == 0)
                        adjust_counter_482(200, 45);
                    if (404 == 401)
                        add_scaled_counter(10);
                    const int x_offset = 404 == 400 ? 114
                        : 404 == 401 ? 90 : 404 == 404 ? 83 : 67;
                    const double y_offset = 404 == 400 ? 96.0
                        : 404 == 401 ? 158.0 : 404 == 404 ? 117.0 : 75.0;
                    float parameters[3] = {
                        static_cast<float>((word_732 - 2) * 5 + word_734), 15.0f, 0.0f};
                    if (404 == 400)
                        add_scaled_counter(10);
                    spawn_owned_object_via_manager(800,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    dispatch_character_wave_handle(0);
                    word_732 = static_cast<short>(word_732 + 1);
                }
            } else {
                if (word_730 % 3 == 1 && word_732 < 5) {
                    state_180 = 1;
                    if (aerial)
                        add_scaled_counter(10);
                    if (word_732 == 0)
                        adjust_counter_482(200, 45);
                    if (404 == 401)
                        add_scaled_counter(10);
                    const int x_offset = 404 == 400 ? 114
                        : 404 == 401 ? 90 : 404 == 404 ? 83 : 67;
                    const double y_offset = 404 == 400 ? 96.0
                        : 404 == 401 ? 158.0 : 404 == 404 ? 117.0 : 75.0;
                    float parameters[3] = {
                        static_cast<float>((word_732 - 2) * 5 + word_734), 15.0f, 0.0f};
                    if (404 == 400)
                        add_scaled_counter(10);
                    for (int count = 2; count != 0; --count) {
                        parameters[0] = static_cast<float>(
                            random_receiver_004()->selector_random_range(0, 30) + word_734 - 15);
                        parameters[1] = static_cast<float>(
                            15 - random_receiver_004()->selector_random_range(0, 5));
                        spawn_owned_object_via_manager(800,
                            static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                            static_cast<float>(y_f0 + y_offset),
                            static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    }
                    dispatch_character_wave_handle(0);
                    word_732 = static_cast<short>(word_732 + 1);
                }
            }
        }
        if (advance_frame_and_dispatch())
            set_action(0);
        if (frame_counter_144 == 0 && frame_timer_142 == 0
                && frame_index_140 == 0 && sequence_13e == 1 && byte_750 == 1) {
            if (404 != 406)
                set_sequence(4);
            emit_fighter_effect(62,
                aerial ? static_cast<float>(x_ec - static_cast<float>(facing_104 * 35))
                       : static_cast<float>(static_cast<float>(facing_104 * 65) + x_ec),
                static_cast<float>(y_f0 + (aerial ? 135.0 : 55.0)),
                static_cast<unsigned char>(facing_104), 1);
            if (404 == 406)
                set_sequence(4);
            return;
        }
        if (frame_counter_144 == 0 && frame_timer_142 == 0
                && frame_index_140 == 0 && sequence_13e == 2) {
            const float delta_x = static_cast<float>(
                (static_cast<double>(peer_170->x_ec) - x_ec) * facing_104);
            const short angle = static_cast<short>(static_cast<int>(atan2_degrees(
                static_cast<float>(static_cast<double>(peer_170->y_f0) - y_f0), delta_x)));
            word_734 = static_cast<short>(-angle);
            const short lower = 404 == 401 ? -60 : 404 == 406 ? 40 : -30;
            const short upper = 404 == 401 ? -40 : 404 == 406 ? 60 : 30;
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
            const short angle = static_cast<short>(static_cast<int>(atan2_degrees(
                static_cast<float>(static_cast<double>(peer_170->y_f0) - y_f0), delta_x)));
            word_734 = static_cast<short>(-angle);
            const short lower = 404 == 401 ? -60 : 404 == 406 ? 40 : -30;
            const short upper = 404 == 401 ? -40 : 404 == 406 ? 60 : 30;
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
        return;
    }
        case 406: {
        const bool aerial = 406 == 404 || 406 == 406;
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
                return;
            }
        }
        if (sequence_13e == 0 && field_6c0 == 0)
            byte_750 = 0;
        if (word_730 > 0) {
            word_730 = static_cast<short>(word_730 + 1);
            if (byte_750 == 0) {
                if (word_730 % 3 == 1 && word_732 < 5) {
                    state_180 = 1;
                    if (aerial)
                        add_scaled_counter(10);
                    if (word_732 == 0)
                        adjust_counter_482(200, 45);
                    if (406 == 401)
                        add_scaled_counter(10);
                    const int x_offset = 406 == 400 ? 114
                        : 406 == 401 ? 90 : 406 == 404 ? 83 : 67;
                    const double y_offset = 406 == 400 ? 96.0
                        : 406 == 401 ? 158.0 : 406 == 404 ? 117.0 : 75.0;
                    float parameters[3] = {
                        static_cast<float>((word_732 - 2) * 5 + word_734), 15.0f, 0.0f};
                    if (406 == 400)
                        add_scaled_counter(10);
                    spawn_owned_object_via_manager(800,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    dispatch_character_wave_handle(0);
                    word_732 = static_cast<short>(word_732 + 1);
                }
            } else {
                if (word_730 % 3 == 1 && word_732 < 5) {
                    state_180 = 1;
                    if (aerial)
                        add_scaled_counter(10);
                    if (word_732 == 0)
                        adjust_counter_482(200, 45);
                    if (406 == 401)
                        add_scaled_counter(10);
                    const int x_offset = 406 == 400 ? 114
                        : 406 == 401 ? 90 : 406 == 404 ? 83 : 67;
                    const double y_offset = 406 == 400 ? 96.0
                        : 406 == 401 ? 158.0 : 406 == 404 ? 117.0 : 75.0;
                    float parameters[3] = {
                        static_cast<float>((word_732 - 2) * 5 + word_734), 15.0f, 0.0f};
                    if (406 == 400)
                        add_scaled_counter(10);
                    for (int count = 2; count != 0; --count) {
                        parameters[0] = static_cast<float>(
                            random_receiver_004()->selector_random_range(0, 30) + word_734 - 15);
                        parameters[1] = static_cast<float>(
                            15 - random_receiver_004()->selector_random_range(0, 5));
                        spawn_owned_object_via_manager(800,
                            static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                            static_cast<float>(y_f0 + y_offset),
                            static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    }
                    dispatch_character_wave_handle(0);
                    word_732 = static_cast<short>(word_732 + 1);
                }
            }
        }
        if (advance_frame_and_dispatch())
            set_action(0);
        if (frame_counter_144 == 0 && frame_timer_142 == 0
                && frame_index_140 == 0 && sequence_13e == 1 && byte_750 == 1) {
            if (406 != 406)
                set_sequence(4);
            emit_fighter_effect(62,
                aerial ? static_cast<float>(x_ec - static_cast<float>(facing_104 * 35))
                       : static_cast<float>(static_cast<float>(facing_104 * 65) + x_ec),
                static_cast<float>(y_f0 + (aerial ? 135.0 : 55.0)),
                static_cast<unsigned char>(facing_104), 1);
            if (406 == 406)
                set_sequence(4);
            return;
        }
        if (frame_counter_144 == 0 && frame_timer_142 == 0
                && frame_index_140 == 0 && sequence_13e == 2) {
            const float delta_x = static_cast<float>(
                (static_cast<double>(peer_170->x_ec) - x_ec) * facing_104);
            const short angle = static_cast<short>(static_cast<int>(atan2_degrees(
                static_cast<float>(static_cast<double>(peer_170->y_f0) - y_f0), delta_x)));
            word_734 = static_cast<short>(-angle);
            const short lower = 406 == 401 ? -60 : 406 == 406 ? 40 : -30;
            const short upper = 406 == 401 ? -40 : 406 == 406 ? 60 : 30;
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
            const short angle = static_cast<short>(static_cast<int>(atan2_degrees(
                static_cast<float>(static_cast<double>(peer_170->y_f0) - y_f0), delta_x)));
            word_734 = static_cast<short>(-angle);
            const short lower = 406 == 401 ? -60 : 406 == 406 ? 40 : -30;
            const short upper = 406 == 401 ? -40 : 406 == 406 ? 60 : 30;
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
        return;
    }
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
        return;

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
                return;
            }
        }
        if (field_6c4 == 0)
            byte_750 = 0;
        if (advance_frame_and_dispatch())
            set_action(0);
        if (frame_counter_144 == 0 && frame_timer_142 == 0 && frame_index_140 == 0
                && sequence_13e == 1) {
            set_action(aerial ? 9 : 0);
            return;
        }
        if (aerial && frame_counter_144 == 0 && frame_timer_142 == 0
                && frame_index_140 == 0 && sequence_13e == 3) {
            set_action(9);
            return;
        }
        if (sequence_13e != 0)
            goto reimu_action410_after_frame_gates;
        register unsigned short frame_timer_value = frame_timer_142;
        switch (frame_timer_value) {
        case 0:
            break;
        default:
            goto reimu_action410_frame3_done;
        }
        if (frame_index_140 != (aerial ? 4 : 6))
            goto reimu_action410_frame3_done;
        if (byte_750 != static_cast<unsigned char>(frame_timer_value)) {
            register int frame3_direction =
                static_cast<unsigned char>(facing_104);
            emit_fighter_effect(62,
                static_cast<float>(static_cast<float>(
                    static_cast<signed char>(frame3_direction) * 67) + x_ec),
                static_cast<float>(y_f0 + 57.0), frame3_direction, 1);
            typedef unsigned char (__thiscall *Action410EffectNextSequenceSlot)(ReimuActionStatePreludeView *);
            register void **action_vtable = *reinterpret_cast<void ***>(this);
            register Action410EffectNextSequenceSlot action_slot =
                reinterpret_cast<Action410EffectNextSequenceSlot>(action_vtable[5]);
            action_slot(this);
            return;
        }
reimu_action410_frame3_done:
        if (frame_timer_value == 0 && frame_index_140 == (aerial ? 5 : 8)) {
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
reimu_action410_after_frame_gates:
        if (sequence_13e == 1 && frame_counter_144 >= 25) {
            next_sequence_block();
            return;
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
        return;
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
            return;
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
        return;
        case 414: {
        const bool aerial = true;
        frame_threshold = 4;
        landing_sequence = 3;
        if (!aerial || sequence_13e == landing_sequence)
            resolve_stage_surface_landing_transition();
        if (aerial && ((sequence_13e == 0 && frame_index_140 >= 8)
                || (sequence_13e == 2 && frame_index_140 >= frame_threshold))) {
            acceleration_y_100 = 0.6f;
            velocity_y_f8 = static_cast<float>(velocity_y_f8 - static_cast<double>(0.6f));
            if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
                zero_velocity_acceleration();
                goto reimu_action_shared_landing_sequence3_tail;
            }
        }
        if (field_6c4 == 0)
            byte_750 = 0;
        if (advance_frame_and_dispatch())
            set_action(0);
        if (frame_counter_144 == 0 && frame_timer_142 == 0 && frame_index_140 == 0
                && sequence_13e == 1)
            goto reimu_action414_set_action9_exit;
        if (aerial && frame_counter_144 == 0 && frame_timer_142 == 0
                && frame_index_140 == 0 && sequence_13e == 3) {
reimu_action414_set_action9_exit:
            set_action(9);
            return;
        }
        if (sequence_13e == 0 && frame_timer_142 == 0) {
            if (frame_index_140 == (aerial ? frame_threshold : 6) && byte_750 != 0) {
                register int frame3_direction =
                    static_cast<unsigned char>(facing_104);
                emit_fighter_effect(62,
                    static_cast<float>(static_cast<float>(
                        static_cast<signed char>(frame3_direction) * 62) + x_ec),
                    static_cast<float>(y_f0 + 108.0), frame3_direction, 1);
                typedef unsigned char (__thiscall *Action414EffectNextSequenceSlot)(ReimuActionStatePreludeView *);
                register void **action_vtable = *reinterpret_cast<void ***>(this);
                register Action414EffectNextSequenceSlot action_slot =
                    reinterpret_cast<Action414EffectNextSequenceSlot>(action_vtable[5]);
                action_slot(this);
                return;
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
                    static_cast<unsigned char>(facing_104), 1, parameters, frame_threshold);
            }
        }
        if (sequence_13e == 1 && frame_counter_144 >= 25) {
            next_sequence_block();
            return;
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
                static_cast<unsigned char>(facing_104), 1, parameters, frame_threshold);
        }
        return;
    }
        case 416: {
        frame_threshold = 4;
        landing_sequence = 3;
        if (sequence_13e == landing_sequence)
            resolve_stage_surface_landing_transition();
        frame_one = action_13c - 415;
        if (sequence_13e == 0 && frame_index_140 >= frame_threshold)
            goto reimu_action416_gravity_frame_threshold;
        if (sequence_13e == 2 && frame_index_140 >= frame_one)
            goto reimu_action416_gravity;
reimu_action416_common:
        if (field_6c4 == 0)
            byte_750 = 0;
        if (advance_frame_and_dispatch())
            set_action(0);
        if (frame_counter_144 == 0 && frame_timer_142 == 0 && frame_index_140 == 0
                && sequence_13e == frame_one)
            goto reimu_shot_action9_exit;
        if (frame_counter_144 == 0 && frame_timer_142 == 0 && frame_index_140 == 0
                && sequence_13e == 3)
            goto reimu_shot_action9_exit;
        if (sequence_13e == 0) {
            if (frame_timer_142 == 0 && frame_index_140 == 3 && byte_750 != 0) {
                register int frame3_direction =
                    static_cast<unsigned char>(facing_104);
                emit_fighter_effect(62,
                    static_cast<float>(static_cast<float>(
                        static_cast<signed char>(frame3_direction) * 14) + x_ec),
                    static_cast<float>(y_f0 + 197.0), frame3_direction, frame_one);
                typedef unsigned char (__thiscall *Action416NextSequenceSlot)(ReimuActionStatePreludeView *);
                register void **action_vtable = *reinterpret_cast<void ***>(this);
                register Action416NextSequenceSlot action_slot =
                    reinterpret_cast<Action416NextSequenceSlot>(action_vtable[5]);
                action_slot(this);
                return;
            }
            goto reimu_action416_frame_threshold_check;
        }
        goto reimu_action416_after_frame_threshold;
reimu_action416_frame_threshold_check:
        if (frame_timer_142 == 0 && frame_index_140 == frame_threshold) {
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
                static_cast<unsigned char>(facing_104), 1, parameters, frame_threshold);
        }
reimu_action416_after_frame_threshold:
        if (sequence_13e == 1 && frame_counter_144 >= 25) {
            next_sequence_block();
            return;
        }
        if (sequence_13e == 2 && frame_timer_142 == 0 && frame_index_140 == frame_one) {
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
                static_cast<unsigned char>(facing_104), 1, parameters, frame_threshold);
        }
        return;
reimu_action416_gravity_frame_threshold:
reimu_action416_gravity:
        acceleration_y_100 = 0.6f;
        velocity_y_f8 = static_cast<float>(velocity_y_f8 - static_cast<double>(0.6f));
        if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
            zero_velocity_acceleration();
            y_f0 = reimu_stage_surface_height_at_x(this);
            set_sequence(3);
            return;
        }
        goto reimu_action416_common;
    }
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
        return;

// Twelve physical500-family bodies and their shared charge/landing exits.
        case 500: {
        const bool aerial = 500 == 502 || 500 == 503
            || 500 == 507 || 500 == 508
            || 500 == 512 || 500 == 513;
        const bool wide = 500 >= 510;
        const bool alternate = 500 >= 505;
        const bool second_input = 500 == 501 || 500 == 503
            || 500 == 506 || 500 == 508
            || 500 == 511 || 500 == 513;
        if (!aerial || sequence_13e == 5)
            resolve_stage_surface_landing_transition();
        byte_17c = wide ? 8 : alternate ? 4 : 0;
        if (sequence_13e <= 1 && (second_input ? field_6c4 : field_6c0) == 0)
            byte_750 = 0;
        if (aerial && sequence_13e < 5) {
            if (sequence_13e == 4) {
                acceleration_y_100 = 0.6f;
                velocity_y_f8 = static_cast<float>(velocity_y_f8 - static_cast<double>(0.6f));
            }
            if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
                zero_velocity_acceleration();
                y_f0 = reimu_stage_surface_height_at_x(this);
                set_sequence(5);
                return;
            }
        }
        if (sequence_13e == 2 && frame_timer_142 == 0
                && frame_index_140 == (aerial ? 1 : 2)) {
            adjust_counter_482(200, 120);
            state_180 = 1;
            add_scaled_counter(50);
            dispatch_character_wave_handle(wide ? 20 : 4);
            const int x_offset = aerial ? 50 : 114;
            const double y_offset = aerial ? 108.0 : 96.0;
            if (wide) {
                if (word_736 == 0) {
                    float parameters[3] = {30.0f, 15.0f, 0.0f};
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = 0.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -30.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                }
                if (word_736 == 1) {
                    float parameters[3] = {45.0f, 15.0f, 0.0f};
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = 15.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -15.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -45.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                }
                if (word_736 == 2) {
                    float parameters[3] = {60.0f, 15.0f, 0.0f};
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = 30.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = 0.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -30.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -60.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                }
            } else if (!alternate) {
                if (word_736 == 0) {
                    float parameters[3] = {20.0f, 15.0f, 0.0f};
                    spawn_owned_object_via_manager(810,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -20.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(810,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                }
                if (word_736 == 1) {
                    for (int angle = 20; angle < 60; angle += 20) {
                        float parameters[3] = {static_cast<float>(angle), 15.0f, 0.0f};
                        spawn_owned_object_via_manager(810,
                            static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                            static_cast<float>(y_f0 + y_offset),
                            static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    }
                    for (int angle = -20; angle > -60; angle -= 20) {
                        float parameters[3] = {static_cast<float>(angle), 15.0f, 0.0f};
                        spawn_owned_object_via_manager(810,
                            static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                            static_cast<float>(y_f0 + y_offset),
                            static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    }
                }
                if (word_736 == 2) {
                    for (int angle = 20; angle < 80; angle += 20) {
                        float parameters[3] = {static_cast<float>(angle), 15.0f, 0.0f};
                        spawn_owned_object_via_manager(810,
                            static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                            static_cast<float>(y_f0 + y_offset),
                            static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    }
                    for (int angle = -20; angle > -80; angle -= 20) {
                        float parameters[3] = {static_cast<float>(angle), 15.0f, 0.0f};
                        spawn_owned_object_via_manager(810,
                            static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                            static_cast<float>(y_f0 + y_offset),
                            static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    }
                }
            } else {
                if (word_736 == 0) {
                    float parameters[3] = {10.0f, 23.0f, 0.0f};
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = 0.0f; parameters[1] = 25.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -10.0f; parameters[1] = 23.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                }
                if (word_736 == 1) {
                    float parameters[3] = {15.0f, 25.0f, 0.0f};
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = 5.0f; parameters[1] = 27.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -5.0f; parameters[1] = 27.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -15.0f; parameters[1] = 25.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                }
                if (word_736 == 2) {
                    float parameters[3] = {20.0f, 26.0f, 0.0f};
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = 10.0f; parameters[1] = 27.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = 0.0f; parameters[1] = 29.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -10.0f; parameters[1] = 27.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -20.0f; parameters[1] = 26.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                }
            }
        }
        if (advance_frame_and_dispatch())
            set_action(0);
        if (aerial && frame_counter_144 == 0 && frame_timer_142 == 0
                && frame_index_140 == 0 && sequence_13e == 5) {
            set_action(9);
            return;
        }
        if (sequence_13e == 1) {
            if (frame_counter_144 > 20 && word_736 == 0) {
                word_736 = 1;
                emit_fighter_effect(62,
                    aerial ? static_cast<float>(x_ec - static_cast<float>(facing_104 * 35))
                           : static_cast<float>(static_cast<float>(facing_104 * 65) + x_ec),
                    static_cast<float>(y_f0 + (aerial ? 135.0 : 55.0)),
                    static_cast<unsigned char>(facing_104), 1);
            }
            if (frame_counter_144 > 60) {
                word_736 = 2;
                byte_750 = 0;
            }
            if (byte_750 == 0)
                next_sequence_block();
        }
        if (sequence_13e == 3 && frame_counter_144 > (word_736 + 1) * 10)
            next_sequence_block();
        return;
    }

// Mid-table trajectories and opponent-relative objects; no callable boundary.
        case 501: {
        const bool aerial = 501 == 502 || 501 == 503
            || 501 == 507 || 501 == 508
            || 501 == 512 || 501 == 513;
        const bool wide = 501 >= 510;
        const bool alternate = 501 >= 505;
        const bool second_input = 501 == 501 || 501 == 503
            || 501 == 506 || 501 == 508
            || 501 == 511 || 501 == 513;
        if (!aerial || sequence_13e == 5)
            resolve_stage_surface_landing_transition();
        byte_17c = wide ? 8 : alternate ? 4 : 0;
        if (sequence_13e <= 1 && (second_input ? field_6c4 : field_6c0) == 0)
            byte_750 = 0;
        if (aerial && sequence_13e < 5) {
            if (sequence_13e == 4) {
                acceleration_y_100 = 0.6f;
                velocity_y_f8 = static_cast<float>(velocity_y_f8 - static_cast<double>(0.6f));
            }
            if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
                zero_velocity_acceleration();
                y_f0 = reimu_stage_surface_height_at_x(this);
                set_sequence(5);
                return;
            }
        }
        if (sequence_13e == 2 && frame_timer_142 == 0
                && frame_index_140 == (aerial ? 1 : 2)) {
            adjust_counter_482(200, 120);
            state_180 = 1;
            add_scaled_counter(50);
            dispatch_character_wave_handle(wide ? 20 : 4);
            const int x_offset = aerial ? 50 : 114;
            const double y_offset = aerial ? 108.0 : 96.0;
            if (wide) {
                if (word_736 == 0) {
                    float parameters[3] = {30.0f, 15.0f, 0.0f};
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = 0.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -30.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                }
                if (word_736 == 1) {
                    float parameters[3] = {45.0f, 15.0f, 0.0f};
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = 15.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -15.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -45.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                }
                if (word_736 == 2) {
                    float parameters[3] = {60.0f, 15.0f, 0.0f};
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = 30.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = 0.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -30.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -60.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                }
            } else if (!alternate) {
                if (word_736 == 0) {
                    float parameters[3] = {20.0f, 15.0f, 0.0f};
                    spawn_owned_object_via_manager(810,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -20.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(810,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                }
                if (word_736 == 1) {
                    for (int angle = 20; angle < 60; angle += 20) {
                        float parameters[3] = {static_cast<float>(angle), 15.0f, 0.0f};
                        spawn_owned_object_via_manager(810,
                            static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                            static_cast<float>(y_f0 + y_offset),
                            static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    }
                    for (int angle = -20; angle > -60; angle -= 20) {
                        float parameters[3] = {static_cast<float>(angle), 15.0f, 0.0f};
                        spawn_owned_object_via_manager(810,
                            static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                            static_cast<float>(y_f0 + y_offset),
                            static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    }
                }
                if (word_736 == 2) {
                    for (int angle = 20; angle < 80; angle += 20) {
                        float parameters[3] = {static_cast<float>(angle), 15.0f, 0.0f};
                        spawn_owned_object_via_manager(810,
                            static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                            static_cast<float>(y_f0 + y_offset),
                            static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    }
                    for (int angle = -20; angle > -80; angle -= 20) {
                        float parameters[3] = {static_cast<float>(angle), 15.0f, 0.0f};
                        spawn_owned_object_via_manager(810,
                            static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                            static_cast<float>(y_f0 + y_offset),
                            static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    }
                }
            } else {
                if (word_736 == 0) {
                    float parameters[3] = {10.0f, 23.0f, 0.0f};
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = 0.0f; parameters[1] = 25.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -10.0f; parameters[1] = 23.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                }
                if (word_736 == 1) {
                    float parameters[3] = {15.0f, 25.0f, 0.0f};
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = 5.0f; parameters[1] = 27.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -5.0f; parameters[1] = 27.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -15.0f; parameters[1] = 25.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                }
                if (word_736 == 2) {
                    float parameters[3] = {20.0f, 26.0f, 0.0f};
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = 10.0f; parameters[1] = 27.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = 0.0f; parameters[1] = 29.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -10.0f; parameters[1] = 27.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -20.0f; parameters[1] = 26.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                }
            }
        }
        if (advance_frame_and_dispatch())
            set_action(0);
        if (aerial && frame_counter_144 == 0 && frame_timer_142 == 0
                && frame_index_140 == 0 && sequence_13e == 5) {
            set_action(9);
            return;
        }
        if (sequence_13e == 1) {
            if (frame_counter_144 > 20 && word_736 == 0) {
                word_736 = 1;
                emit_fighter_effect(62,
                    aerial ? static_cast<float>(x_ec - static_cast<float>(facing_104 * 35))
                           : static_cast<float>(static_cast<float>(facing_104 * 65) + x_ec),
                    static_cast<float>(y_f0 + (aerial ? 135.0 : 55.0)),
                    static_cast<unsigned char>(facing_104), 1);
            }
            if (frame_counter_144 > 60) {
                word_736 = 2;
                byte_750 = 0;
            }
            if (byte_750 == 0)
                next_sequence_block();
        }
        if (sequence_13e == 3 && frame_counter_144 > (word_736 + 1) * 10)
            next_sequence_block();
        return;
    }

// Mid-table trajectories and opponent-relative objects; no callable boundary.
        case 502: {
        const bool aerial = 502 == 502 || 502 == 503
            || 502 == 507 || 502 == 508
            || 502 == 512 || 502 == 513;
        const bool wide = 502 >= 510;
        const bool alternate = 502 >= 505;
        const bool second_input = 502 == 501 || 502 == 503
            || 502 == 506 || 502 == 508
            || 502 == 511 || 502 == 513;
        if (!aerial || sequence_13e == 5)
            resolve_stage_surface_landing_transition();
        byte_17c = wide ? 8 : alternate ? 4 : 0;
        if (sequence_13e <= 1 && (second_input ? field_6c4 : field_6c0) == 0)
            byte_750 = 0;
        if (aerial && sequence_13e < 5) {
            if (sequence_13e == 4) {
                acceleration_y_100 = 0.6f;
                velocity_y_f8 = static_cast<float>(velocity_y_f8 - static_cast<double>(0.6f));
            }
            if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
                zero_velocity_acceleration();
                y_f0 = reimu_stage_surface_height_at_x(this);
                set_sequence(5);
                return;
            }
        }
        if (sequence_13e == 2 && frame_timer_142 == 0
                && frame_index_140 == (aerial ? 1 : 2)) {
            adjust_counter_482(200, 120);
            state_180 = 1;
            add_scaled_counter(50);
            dispatch_character_wave_handle(wide ? 20 : 4);
            const int x_offset = aerial ? 50 : 114;
            const double y_offset = aerial ? 108.0 : 96.0;
            if (wide) {
                if (word_736 == 0) {
                    float parameters[3] = {30.0f, 15.0f, 0.0f};
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = 0.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -30.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                }
                if (word_736 == 1) {
                    float parameters[3] = {45.0f, 15.0f, 0.0f};
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = 15.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -15.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -45.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                }
                if (word_736 == 2) {
                    float parameters[3] = {60.0f, 15.0f, 0.0f};
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = 30.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = 0.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -30.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -60.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                }
            } else if (!alternate) {
                if (word_736 == 0) {
                    float parameters[3] = {20.0f, 15.0f, 0.0f};
                    spawn_owned_object_via_manager(810,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -20.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(810,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                }
                if (word_736 == 1) {
                    for (int angle = 20; angle < 60; angle += 20) {
                        float parameters[3] = {static_cast<float>(angle), 15.0f, 0.0f};
                        spawn_owned_object_via_manager(810,
                            static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                            static_cast<float>(y_f0 + y_offset),
                            static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    }
                    for (int angle = -20; angle > -60; angle -= 20) {
                        float parameters[3] = {static_cast<float>(angle), 15.0f, 0.0f};
                        spawn_owned_object_via_manager(810,
                            static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                            static_cast<float>(y_f0 + y_offset),
                            static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    }
                }
                if (word_736 == 2) {
                    for (int angle = 20; angle < 80; angle += 20) {
                        float parameters[3] = {static_cast<float>(angle), 15.0f, 0.0f};
                        spawn_owned_object_via_manager(810,
                            static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                            static_cast<float>(y_f0 + y_offset),
                            static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    }
                    for (int angle = -20; angle > -80; angle -= 20) {
                        float parameters[3] = {static_cast<float>(angle), 15.0f, 0.0f};
                        spawn_owned_object_via_manager(810,
                            static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                            static_cast<float>(y_f0 + y_offset),
                            static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    }
                }
            } else {
                if (word_736 == 0) {
                    float parameters[3] = {10.0f, 23.0f, 0.0f};
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = 0.0f; parameters[1] = 25.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -10.0f; parameters[1] = 23.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                }
                if (word_736 == 1) {
                    float parameters[3] = {15.0f, 25.0f, 0.0f};
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = 5.0f; parameters[1] = 27.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -5.0f; parameters[1] = 27.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -15.0f; parameters[1] = 25.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                }
                if (word_736 == 2) {
                    float parameters[3] = {20.0f, 26.0f, 0.0f};
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = 10.0f; parameters[1] = 27.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = 0.0f; parameters[1] = 29.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -10.0f; parameters[1] = 27.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -20.0f; parameters[1] = 26.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                }
            }
        }
        if (advance_frame_and_dispatch())
            set_action(0);
        if (aerial && frame_counter_144 == 0 && frame_timer_142 == 0
                && frame_index_140 == 0 && sequence_13e == 5) {
            set_action(9);
            return;
        }
        if (sequence_13e == 1) {
            if (frame_counter_144 > 20 && word_736 == 0) {
                word_736 = 1;
                emit_fighter_effect(62,
                    aerial ? static_cast<float>(x_ec - static_cast<float>(facing_104 * 35))
                           : static_cast<float>(static_cast<float>(facing_104 * 65) + x_ec),
                    static_cast<float>(y_f0 + (aerial ? 135.0 : 55.0)),
                    static_cast<unsigned char>(facing_104), 1);
            }
            if (frame_counter_144 > 60) {
                word_736 = 2;
                byte_750 = 0;
            }
            if (byte_750 == 0)
                next_sequence_block();
        }
        if (sequence_13e == 3 && frame_counter_144 > (word_736 + 1) * 10)
            next_sequence_block();
        return;
    }

// Mid-table trajectories and opponent-relative objects; no callable boundary.
        case 503: {
        const bool aerial = 503 == 502 || 503 == 503
            || 503 == 507 || 503 == 508
            || 503 == 512 || 503 == 513;
        const bool wide = 503 >= 510;
        const bool alternate = 503 >= 505;
        const bool second_input = 503 == 501 || 503 == 503
            || 503 == 506 || 503 == 508
            || 503 == 511 || 503 == 513;
        if (!aerial || sequence_13e == 5)
            resolve_stage_surface_landing_transition();
        byte_17c = wide ? 8 : alternate ? 4 : 0;
        if (sequence_13e <= 1 && (second_input ? field_6c4 : field_6c0) == 0)
            byte_750 = 0;
        if (aerial && sequence_13e < 5) {
            if (sequence_13e == 4) {
                acceleration_y_100 = 0.6f;
                velocity_y_f8 = static_cast<float>(velocity_y_f8 - static_cast<double>(0.6f));
            }
            if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
                zero_velocity_acceleration();
                y_f0 = reimu_stage_surface_height_at_x(this);
                set_sequence(5);
                return;
            }
        }
        if (sequence_13e == 2 && frame_timer_142 == 0
                && frame_index_140 == (aerial ? 1 : 2)) {
            adjust_counter_482(200, 120);
            state_180 = 1;
            add_scaled_counter(50);
            dispatch_character_wave_handle(wide ? 20 : 4);
            const int x_offset = aerial ? 50 : 114;
            const double y_offset = aerial ? 108.0 : 96.0;
            if (wide) {
                if (word_736 == 0) {
                    float parameters[3] = {30.0f, 15.0f, 0.0f};
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = 0.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -30.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                }
                if (word_736 == 1) {
                    float parameters[3] = {45.0f, 15.0f, 0.0f};
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = 15.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -15.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -45.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                }
                if (word_736 == 2) {
                    float parameters[3] = {60.0f, 15.0f, 0.0f};
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = 30.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = 0.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -30.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -60.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                }
            } else if (!alternate) {
                if (word_736 == 0) {
                    float parameters[3] = {20.0f, 15.0f, 0.0f};
                    spawn_owned_object_via_manager(810,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -20.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(810,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                }
                if (word_736 == 1) {
                    for (int angle = 20; angle < 60; angle += 20) {
                        float parameters[3] = {static_cast<float>(angle), 15.0f, 0.0f};
                        spawn_owned_object_via_manager(810,
                            static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                            static_cast<float>(y_f0 + y_offset),
                            static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    }
                    for (int angle = -20; angle > -60; angle -= 20) {
                        float parameters[3] = {static_cast<float>(angle), 15.0f, 0.0f};
                        spawn_owned_object_via_manager(810,
                            static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                            static_cast<float>(y_f0 + y_offset),
                            static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    }
                }
                if (word_736 == 2) {
                    for (int angle = 20; angle < 80; angle += 20) {
                        float parameters[3] = {static_cast<float>(angle), 15.0f, 0.0f};
                        spawn_owned_object_via_manager(810,
                            static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                            static_cast<float>(y_f0 + y_offset),
                            static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    }
                    for (int angle = -20; angle > -80; angle -= 20) {
                        float parameters[3] = {static_cast<float>(angle), 15.0f, 0.0f};
                        spawn_owned_object_via_manager(810,
                            static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                            static_cast<float>(y_f0 + y_offset),
                            static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    }
                }
            } else {
                if (word_736 == 0) {
                    float parameters[3] = {10.0f, 23.0f, 0.0f};
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = 0.0f; parameters[1] = 25.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -10.0f; parameters[1] = 23.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                }
                if (word_736 == 1) {
                    float parameters[3] = {15.0f, 25.0f, 0.0f};
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = 5.0f; parameters[1] = 27.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -5.0f; parameters[1] = 27.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -15.0f; parameters[1] = 25.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                }
                if (word_736 == 2) {
                    float parameters[3] = {20.0f, 26.0f, 0.0f};
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = 10.0f; parameters[1] = 27.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = 0.0f; parameters[1] = 29.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -10.0f; parameters[1] = 27.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -20.0f; parameters[1] = 26.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                }
            }
        }
        if (advance_frame_and_dispatch())
            set_action(0);
        if (aerial && frame_counter_144 == 0 && frame_timer_142 == 0
                && frame_index_140 == 0 && sequence_13e == 5) {
            set_action(9);
            return;
        }
        if (sequence_13e == 1) {
            if (frame_counter_144 > 20 && word_736 == 0) {
                word_736 = 1;
                emit_fighter_effect(62,
                    aerial ? static_cast<float>(x_ec - static_cast<float>(facing_104 * 35))
                           : static_cast<float>(static_cast<float>(facing_104 * 65) + x_ec),
                    static_cast<float>(y_f0 + (aerial ? 135.0 : 55.0)),
                    static_cast<unsigned char>(facing_104), 1);
            }
            if (frame_counter_144 > 60) {
                word_736 = 2;
                byte_750 = 0;
            }
            if (byte_750 == 0)
                next_sequence_block();
        }
        if (sequence_13e == 3 && frame_counter_144 > (word_736 + 1) * 10)
            next_sequence_block();
        return;
    }

// Mid-table trajectories and opponent-relative objects; no callable boundary.
        case 505: {
        const bool aerial = 505 == 502 || 505 == 503
            || 505 == 507 || 505 == 508
            || 505 == 512 || 505 == 513;
        const bool wide = 505 >= 510;
        const bool alternate = 505 >= 505;
        const bool second_input = 505 == 501 || 505 == 503
            || 505 == 506 || 505 == 508
            || 505 == 511 || 505 == 513;
        if (!aerial || sequence_13e == 5)
            resolve_stage_surface_landing_transition();
        byte_17c = wide ? 8 : alternate ? 4 : 0;
        if (sequence_13e <= 1 && (second_input ? field_6c4 : field_6c0) == 0)
            byte_750 = 0;
        if (aerial && sequence_13e < 5) {
            if (sequence_13e == 4) {
                acceleration_y_100 = 0.6f;
                velocity_y_f8 = static_cast<float>(velocity_y_f8 - static_cast<double>(0.6f));
            }
            if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
                zero_velocity_acceleration();
                y_f0 = reimu_stage_surface_height_at_x(this);
                set_sequence(5);
                return;
            }
        }
        if (sequence_13e == 2 && frame_timer_142 == 0
                && frame_index_140 == (aerial ? 1 : 2)) {
            adjust_counter_482(200, 120);
            state_180 = 1;
            add_scaled_counter(50);
            dispatch_character_wave_handle(wide ? 20 : 4);
            const int x_offset = aerial ? 50 : 114;
            const double y_offset = aerial ? 108.0 : 96.0;
            if (wide) {
                if (word_736 == 0) {
                    float parameters[3] = {30.0f, 15.0f, 0.0f};
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = 0.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -30.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                }
                if (word_736 == 1) {
                    float parameters[3] = {45.0f, 15.0f, 0.0f};
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = 15.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -15.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -45.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                }
                if (word_736 == 2) {
                    float parameters[3] = {60.0f, 15.0f, 0.0f};
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = 30.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = 0.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -30.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -60.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                }
            } else if (!alternate) {
                if (word_736 == 0) {
                    float parameters[3] = {20.0f, 15.0f, 0.0f};
                    spawn_owned_object_via_manager(810,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -20.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(810,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                }
                if (word_736 == 1) {
                    for (int angle = 20; angle < 60; angle += 20) {
                        float parameters[3] = {static_cast<float>(angle), 15.0f, 0.0f};
                        spawn_owned_object_via_manager(810,
                            static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                            static_cast<float>(y_f0 + y_offset),
                            static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    }
                    for (int angle = -20; angle > -60; angle -= 20) {
                        float parameters[3] = {static_cast<float>(angle), 15.0f, 0.0f};
                        spawn_owned_object_via_manager(810,
                            static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                            static_cast<float>(y_f0 + y_offset),
                            static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    }
                }
                if (word_736 == 2) {
                    for (int angle = 20; angle < 80; angle += 20) {
                        float parameters[3] = {static_cast<float>(angle), 15.0f, 0.0f};
                        spawn_owned_object_via_manager(810,
                            static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                            static_cast<float>(y_f0 + y_offset),
                            static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    }
                    for (int angle = -20; angle > -80; angle -= 20) {
                        float parameters[3] = {static_cast<float>(angle), 15.0f, 0.0f};
                        spawn_owned_object_via_manager(810,
                            static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                            static_cast<float>(y_f0 + y_offset),
                            static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    }
                }
            } else {
                if (word_736 == 0) {
                    float parameters[3] = {10.0f, 23.0f, 0.0f};
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = 0.0f; parameters[1] = 25.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -10.0f; parameters[1] = 23.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                }
                if (word_736 == 1) {
                    float parameters[3] = {15.0f, 25.0f, 0.0f};
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = 5.0f; parameters[1] = 27.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -5.0f; parameters[1] = 27.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -15.0f; parameters[1] = 25.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                }
                if (word_736 == 2) {
                    float parameters[3] = {20.0f, 26.0f, 0.0f};
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = 10.0f; parameters[1] = 27.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = 0.0f; parameters[1] = 29.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -10.0f; parameters[1] = 27.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -20.0f; parameters[1] = 26.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                }
            }
        }
        if (advance_frame_and_dispatch())
            set_action(0);
        if (aerial && frame_counter_144 == 0 && frame_timer_142 == 0
                && frame_index_140 == 0 && sequence_13e == 5) {
            set_action(9);
            return;
        }
        if (sequence_13e == 1) {
            if (frame_counter_144 > 20 && word_736 == 0) {
                word_736 = 1;
                emit_fighter_effect(62,
                    aerial ? static_cast<float>(x_ec - static_cast<float>(facing_104 * 35))
                           : static_cast<float>(static_cast<float>(facing_104 * 65) + x_ec),
                    static_cast<float>(y_f0 + (aerial ? 135.0 : 55.0)),
                    static_cast<unsigned char>(facing_104), 1);
            }
            if (frame_counter_144 > 60) {
                word_736 = 2;
                byte_750 = 0;
            }
            if (byte_750 == 0)
                next_sequence_block();
        }
        if (sequence_13e == 3 && frame_counter_144 > (word_736 + 1) * 10)
            next_sequence_block();
        return;
    }

// Mid-table trajectories and opponent-relative objects; no callable boundary.
        case 506: {
        const bool aerial = 506 == 502 || 506 == 503
            || 506 == 507 || 506 == 508
            || 506 == 512 || 506 == 513;
        const bool wide = 506 >= 510;
        const bool alternate = 506 >= 505;
        const bool second_input = 506 == 501 || 506 == 503
            || 506 == 506 || 506 == 508
            || 506 == 511 || 506 == 513;
        if (!aerial || sequence_13e == 5)
            resolve_stage_surface_landing_transition();
        byte_17c = wide ? 8 : alternate ? 4 : 0;
        if (sequence_13e <= 1 && (second_input ? field_6c4 : field_6c0) == 0)
            byte_750 = 0;
        if (aerial && sequence_13e < 5) {
            if (sequence_13e == 4) {
                acceleration_y_100 = 0.6f;
                velocity_y_f8 = static_cast<float>(velocity_y_f8 - static_cast<double>(0.6f));
            }
            if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
                zero_velocity_acceleration();
                y_f0 = reimu_stage_surface_height_at_x(this);
                set_sequence(5);
                return;
            }
        }
        if (sequence_13e == 2 && frame_timer_142 == 0
                && frame_index_140 == (aerial ? 1 : 2)) {
            adjust_counter_482(200, 120);
            state_180 = 1;
            add_scaled_counter(50);
            dispatch_character_wave_handle(wide ? 20 : 4);
            const int x_offset = aerial ? 50 : 114;
            const double y_offset = aerial ? 108.0 : 96.0;
            if (wide) {
                if (word_736 == 0) {
                    float parameters[3] = {30.0f, 15.0f, 0.0f};
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = 0.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -30.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                }
                if (word_736 == 1) {
                    float parameters[3] = {45.0f, 15.0f, 0.0f};
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = 15.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -15.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -45.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                }
                if (word_736 == 2) {
                    float parameters[3] = {60.0f, 15.0f, 0.0f};
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = 30.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = 0.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -30.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -60.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                }
            } else if (!alternate) {
                if (word_736 == 0) {
                    float parameters[3] = {20.0f, 15.0f, 0.0f};
                    spawn_owned_object_via_manager(810,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -20.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(810,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                }
                if (word_736 == 1) {
                    for (int angle = 20; angle < 60; angle += 20) {
                        float parameters[3] = {static_cast<float>(angle), 15.0f, 0.0f};
                        spawn_owned_object_via_manager(810,
                            static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                            static_cast<float>(y_f0 + y_offset),
                            static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    }
                    for (int angle = -20; angle > -60; angle -= 20) {
                        float parameters[3] = {static_cast<float>(angle), 15.0f, 0.0f};
                        spawn_owned_object_via_manager(810,
                            static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                            static_cast<float>(y_f0 + y_offset),
                            static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    }
                }
                if (word_736 == 2) {
                    for (int angle = 20; angle < 80; angle += 20) {
                        float parameters[3] = {static_cast<float>(angle), 15.0f, 0.0f};
                        spawn_owned_object_via_manager(810,
                            static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                            static_cast<float>(y_f0 + y_offset),
                            static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    }
                    for (int angle = -20; angle > -80; angle -= 20) {
                        float parameters[3] = {static_cast<float>(angle), 15.0f, 0.0f};
                        spawn_owned_object_via_manager(810,
                            static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                            static_cast<float>(y_f0 + y_offset),
                            static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    }
                }
            } else {
                if (word_736 == 0) {
                    float parameters[3] = {10.0f, 23.0f, 0.0f};
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = 0.0f; parameters[1] = 25.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -10.0f; parameters[1] = 23.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                }
                if (word_736 == 1) {
                    float parameters[3] = {15.0f, 25.0f, 0.0f};
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = 5.0f; parameters[1] = 27.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -5.0f; parameters[1] = 27.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -15.0f; parameters[1] = 25.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                }
                if (word_736 == 2) {
                    float parameters[3] = {20.0f, 26.0f, 0.0f};
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = 10.0f; parameters[1] = 27.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = 0.0f; parameters[1] = 29.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -10.0f; parameters[1] = 27.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -20.0f; parameters[1] = 26.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                }
            }
        }
        if (advance_frame_and_dispatch())
            set_action(0);
        if (aerial && frame_counter_144 == 0 && frame_timer_142 == 0
                && frame_index_140 == 0 && sequence_13e == 5) {
            set_action(9);
            return;
        }
        if (sequence_13e == 1) {
            if (frame_counter_144 > 20 && word_736 == 0) {
                word_736 = 1;
                emit_fighter_effect(62,
                    aerial ? static_cast<float>(x_ec - static_cast<float>(facing_104 * 35))
                           : static_cast<float>(static_cast<float>(facing_104 * 65) + x_ec),
                    static_cast<float>(y_f0 + (aerial ? 135.0 : 55.0)),
                    static_cast<unsigned char>(facing_104), 1);
            }
            if (frame_counter_144 > 60) {
                word_736 = 2;
                byte_750 = 0;
            }
            if (byte_750 == 0)
                next_sequence_block();
        }
        if (sequence_13e == 3 && frame_counter_144 > (word_736 + 1) * 10)
            next_sequence_block();
        return;
    }

// Mid-table trajectories and opponent-relative objects; no callable boundary.
        case 507: {
        const bool aerial = 507 == 502 || 507 == 503
            || 507 == 507 || 507 == 508
            || 507 == 512 || 507 == 513;
        const bool wide = 507 >= 510;
        const bool alternate = 507 >= 505;
        const bool second_input = 507 == 501 || 507 == 503
            || 507 == 506 || 507 == 508
            || 507 == 511 || 507 == 513;
        frame_threshold = 5;
        if (!aerial || sequence_13e == frame_threshold)
            resolve_stage_surface_landing_transition();
        byte_17c = wide ? 8 : alternate ? 4 : 0;
        frame_one = 1;
        if (sequence_13e <= frame_one && (second_input ? field_6c4 : field_6c0) == 0)
            byte_750 = 0;
        if (aerial && sequence_13e < frame_threshold) {
            if (sequence_13e == 4) {
                acceleration_y_100 = 0.6f;
                velocity_y_f8 = static_cast<float>(velocity_y_f8 - static_cast<double>(0.6f));
            }
            if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
                zero_velocity_acceleration();
                y_f0 = reimu_stage_surface_height_at_x(this);
                set_sequence(5);
                return;
            }
        }
        if (sequence_13e == 2 && frame_timer_142 == 0
                && frame_index_140 == (aerial ? frame_one : 2)) {
            adjust_counter_482(200, 120);
            state_180 = 1;
            add_scaled_counter(50);
            dispatch_character_wave_handle(wide ? 20 : 4);
            const int x_offset = aerial ? 50 : 114;
            const double y_offset = aerial ? 108.0 : 96.0;
            if (wide) {
                if (word_736 == 0) {
                    float parameters[3] = {30.0f, 15.0f, 0.0f};
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = 0.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -30.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                }
                if (word_736 == 1) {
                    float parameters[3] = {45.0f, 15.0f, 0.0f};
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = 15.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -15.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -45.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                }
                if (word_736 == 2) {
                    float parameters[3] = {60.0f, 15.0f, 0.0f};
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = 30.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = 0.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -30.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -60.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                }
            } else if (!alternate) {
                if (word_736 == 0) {
                    float parameters[3] = {20.0f, 15.0f, 0.0f};
                    spawn_owned_object_via_manager(810,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -20.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(810,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                }
                if (word_736 == 1) {
                    for (int angle = 20; angle < 60; angle += 20) {
                        float parameters[3] = {static_cast<float>(angle), 15.0f, 0.0f};
                        spawn_owned_object_via_manager(810,
                            static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                            static_cast<float>(y_f0 + y_offset),
                            static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    }
                    for (int angle = -20; angle > -60; angle -= 20) {
                        float parameters[3] = {static_cast<float>(angle), 15.0f, 0.0f};
                        spawn_owned_object_via_manager(810,
                            static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                            static_cast<float>(y_f0 + y_offset),
                            static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    }
                }
                if (word_736 == 2) {
                    for (int angle = 20; angle < 80; angle += 20) {
                        float parameters[3] = {static_cast<float>(angle), 15.0f, 0.0f};
                        spawn_owned_object_via_manager(810,
                            static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                            static_cast<float>(y_f0 + y_offset),
                            static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    }
                    for (int angle = -20; angle > -80; angle -= 20) {
                        float parameters[3] = {static_cast<float>(angle), 15.0f, 0.0f};
                        spawn_owned_object_via_manager(810,
                            static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                            static_cast<float>(y_f0 + y_offset),
                            static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    }
                }
            } else {
                if (word_736 == 0) {
                    float parameters[3] = {10.0f, 23.0f, 0.0f};
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = 0.0f; parameters[1] = 25.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -10.0f; parameters[1] = 23.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                }
                if (word_736 == 1) {
                    float parameters[3] = {15.0f, 25.0f, 0.0f};
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = 5.0f; parameters[1] = 27.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -5.0f; parameters[1] = 27.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -15.0f; parameters[1] = 25.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                }
                if (word_736 == 2) {
                    float parameters[3] = {20.0f, 26.0f, 0.0f};
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = 10.0f; parameters[1] = 27.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = 0.0f; parameters[1] = 29.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -10.0f; parameters[1] = 27.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -20.0f; parameters[1] = 26.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                }
            }
        }
        if (advance_frame_and_dispatch())
            set_action(0);
        if (aerial && frame_counter_144 == 0 && frame_timer_142 == 0
                && frame_index_140 == 0 && sequence_13e == 5) {
            set_action(9);
            return;
        }
        if (sequence_13e == 1) {
            if (frame_counter_144 > 20 && word_736 == 0) {
                word_736 = 1;
                emit_fighter_effect(62,
                    aerial ? static_cast<float>(x_ec - static_cast<float>(facing_104 * 35))
                           : static_cast<float>(static_cast<float>(facing_104 * 65) + x_ec),
                    static_cast<float>(y_f0 + (aerial ? 135.0 : 55.0)),
                    static_cast<unsigned char>(facing_104), 1);
            }
            if (frame_counter_144 > 60) {
                word_736 = 2;
                byte_750 = 0;
            }
            if (byte_750 == 0)
                next_sequence_block();
        }
        if (sequence_13e == 3 && frame_counter_144 > (word_736 + 1) * 10)
            next_sequence_block();
        return;
    }

// Mid-table trajectories and opponent-relative objects; no callable boundary.
        case 508: {
        const bool aerial = 508 == 502 || 508 == 503
            || 508 == 507 || 508 == 508
            || 508 == 512 || 508 == 513;
        const bool wide = 508 >= 510;
        const bool alternate = 508 >= 505;
        const bool second_input = 508 == 501 || 508 == 503
            || 508 == 506 || 508 == 508
            || 508 == 511 || 508 == 513;
        frame_threshold = 5;
        if (!aerial || sequence_13e == frame_threshold)
            resolve_stage_surface_landing_transition();
        byte_17c = wide ? 8 : alternate ? 4 : 0;
        frame_one = 1;
        if (sequence_13e <= frame_one && (second_input ? field_6c4 : field_6c0) == 0)
            byte_750 = 0;
        if (aerial && sequence_13e < frame_threshold) {
            if (sequence_13e == 4) {
                acceleration_y_100 = 0.6f;
                velocity_y_f8 = static_cast<float>(velocity_y_f8 - static_cast<double>(0.6f));
            }
            if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
                zero_velocity_acceleration();
                y_f0 = reimu_stage_surface_height_at_x(this);
                set_sequence(5);
                return;
            }
        }
        if (sequence_13e == 2 && frame_timer_142 == 0
                && frame_index_140 == (aerial ? frame_one : 2)) {
            adjust_counter_482(200, 120);
            state_180 = 1;
            add_scaled_counter(50);
            dispatch_character_wave_handle(wide ? 20 : 4);
            const int x_offset = aerial ? 50 : 114;
            const double y_offset = aerial ? 108.0 : 96.0;
            if (wide) {
                if (word_736 == 0) {
                    float parameters[3] = {30.0f, 15.0f, 0.0f};
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = 0.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -30.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                }
                if (word_736 == 1) {
                    float parameters[3] = {45.0f, 15.0f, 0.0f};
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = 15.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -15.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -45.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                }
                if (word_736 == 2) {
                    float parameters[3] = {60.0f, 15.0f, 0.0f};
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = 30.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = 0.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -30.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -60.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                }
            } else if (!alternate) {
                if (word_736 == 0) {
                    float parameters[3] = {20.0f, 15.0f, 0.0f};
                    spawn_owned_object_via_manager(810,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -20.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(810,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                }
                if (word_736 == 1) {
                    for (int angle = 20; angle < 60; angle += 20) {
                        float parameters[3] = {static_cast<float>(angle), 15.0f, 0.0f};
                        spawn_owned_object_via_manager(810,
                            static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                            static_cast<float>(y_f0 + y_offset),
                            static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    }
                    for (int angle = -20; angle > -60; angle -= 20) {
                        float parameters[3] = {static_cast<float>(angle), 15.0f, 0.0f};
                        spawn_owned_object_via_manager(810,
                            static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                            static_cast<float>(y_f0 + y_offset),
                            static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    }
                }
                if (word_736 == 2) {
                    for (int angle = 20; angle < 80; angle += 20) {
                        float parameters[3] = {static_cast<float>(angle), 15.0f, 0.0f};
                        spawn_owned_object_via_manager(810,
                            static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                            static_cast<float>(y_f0 + y_offset),
                            static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    }
                    for (int angle = -20; angle > -80; angle -= 20) {
                        float parameters[3] = {static_cast<float>(angle), 15.0f, 0.0f};
                        spawn_owned_object_via_manager(810,
                            static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                            static_cast<float>(y_f0 + y_offset),
                            static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    }
                }
            } else {
                if (word_736 == 0) {
                    float parameters[3] = {10.0f, 23.0f, 0.0f};
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = 0.0f; parameters[1] = 25.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -10.0f; parameters[1] = 23.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                }
                if (word_736 == 1) {
                    float parameters[3] = {15.0f, 25.0f, 0.0f};
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = 5.0f; parameters[1] = 27.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -5.0f; parameters[1] = 27.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -15.0f; parameters[1] = 25.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                }
                if (word_736 == 2) {
                    float parameters[3] = {20.0f, 26.0f, 0.0f};
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = 10.0f; parameters[1] = 27.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = 0.0f; parameters[1] = 29.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -10.0f; parameters[1] = 27.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -20.0f; parameters[1] = 26.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                }
            }
        }
        if (advance_frame_and_dispatch())
            set_action(0);
        if (aerial && frame_counter_144 == 0 && frame_timer_142 == 0
                && frame_index_140 == 0 && sequence_13e == 5) {
            set_action(9);
            return;
        }
        if (sequence_13e == 1) {
            if (frame_counter_144 > 20 && word_736 == 0) {
                word_736 = 1;
                emit_fighter_effect(62,
                    aerial ? static_cast<float>(x_ec - static_cast<float>(facing_104 * 35))
                           : static_cast<float>(static_cast<float>(facing_104 * 65) + x_ec),
                    static_cast<float>(y_f0 + (aerial ? 135.0 : 55.0)),
                    static_cast<unsigned char>(facing_104), 1);
            }
            if (frame_counter_144 > 60) {
                word_736 = 2;
                byte_750 = 0;
            }
            if (byte_750 == 0)
                next_sequence_block();
        }
        if (sequence_13e == 3 && frame_counter_144 > (word_736 + 1) * 10)
            next_sequence_block();
        return;
    }

// Mid-table trajectories and opponent-relative objects; no callable boundary.
        case 510: {
        const bool aerial = 510 == 502 || 510 == 503
            || 510 == 507 || 510 == 508
            || 510 == 512 || 510 == 513;
        const bool wide = 510 >= 510;
        const bool alternate = 510 >= 505;
        const bool second_input = 510 == 501 || 510 == 503
            || 510 == 506 || 510 == 508
            || 510 == 511 || 510 == 513;
        if (!aerial || sequence_13e == 5)
            resolve_stage_surface_landing_transition();
        byte_17c = wide ? 8 : alternate ? 4 : 0;
        if (sequence_13e <= 1 && (second_input ? field_6c4 : field_6c0) == 0)
            byte_750 = 0;
        if (aerial && sequence_13e < 5) {
            if (sequence_13e == 4) {
                acceleration_y_100 = 0.6f;
                velocity_y_f8 = static_cast<float>(velocity_y_f8 - static_cast<double>(0.6f));
            }
            if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
                zero_velocity_acceleration();
                y_f0 = reimu_stage_surface_height_at_x(this);
                set_sequence(5);
                return;
            }
        }
        if (sequence_13e == 2 && frame_timer_142 == 0
                && frame_index_140 == (aerial ? 1 : 2)) {
            adjust_counter_482(200, 120);
            state_180 = 1;
            add_scaled_counter(50);
            dispatch_character_wave_handle(wide ? 20 : 4);
            const int x_offset = aerial ? 50 : 114;
            const double y_offset = aerial ? 108.0 : 96.0;
            if (wide) {
                if (word_736 == 0) {
                    float parameters[3] = {30.0f, 15.0f, 0.0f};
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = 0.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -30.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                }
                if (word_736 == 1) {
                    float parameters[3] = {45.0f, 15.0f, 0.0f};
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = 15.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -15.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -45.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                }
                if (word_736 == 2) {
                    float parameters[3] = {60.0f, 15.0f, 0.0f};
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = 30.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = 0.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -30.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -60.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                }
            } else if (!alternate) {
                if (word_736 == 0) {
                    float parameters[3] = {20.0f, 15.0f, 0.0f};
                    spawn_owned_object_via_manager(810,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -20.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(810,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                }
                if (word_736 == 1) {
                    for (int angle = 20; angle < 60; angle += 20) {
                        float parameters[3] = {static_cast<float>(angle), 15.0f, 0.0f};
                        spawn_owned_object_via_manager(810,
                            static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                            static_cast<float>(y_f0 + y_offset),
                            static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    }
                    for (int angle = -20; angle > -60; angle -= 20) {
                        float parameters[3] = {static_cast<float>(angle), 15.0f, 0.0f};
                        spawn_owned_object_via_manager(810,
                            static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                            static_cast<float>(y_f0 + y_offset),
                            static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    }
                }
                if (word_736 == 2) {
                    for (int angle = 20; angle < 80; angle += 20) {
                        float parameters[3] = {static_cast<float>(angle), 15.0f, 0.0f};
                        spawn_owned_object_via_manager(810,
                            static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                            static_cast<float>(y_f0 + y_offset),
                            static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    }
                    for (int angle = -20; angle > -80; angle -= 20) {
                        float parameters[3] = {static_cast<float>(angle), 15.0f, 0.0f};
                        spawn_owned_object_via_manager(810,
                            static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                            static_cast<float>(y_f0 + y_offset),
                            static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    }
                }
            } else {
                if (word_736 == 0) {
                    float parameters[3] = {10.0f, 23.0f, 0.0f};
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = 0.0f; parameters[1] = 25.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -10.0f; parameters[1] = 23.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                }
                if (word_736 == 1) {
                    float parameters[3] = {15.0f, 25.0f, 0.0f};
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = 5.0f; parameters[1] = 27.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -5.0f; parameters[1] = 27.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -15.0f; parameters[1] = 25.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                }
                if (word_736 == 2) {
                    float parameters[3] = {20.0f, 26.0f, 0.0f};
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = 10.0f; parameters[1] = 27.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = 0.0f; parameters[1] = 29.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -10.0f; parameters[1] = 27.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -20.0f; parameters[1] = 26.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                }
            }
        }
        if (advance_frame_and_dispatch())
            set_action(0);
        if (aerial && frame_counter_144 == 0 && frame_timer_142 == 0
                && frame_index_140 == 0 && sequence_13e == 5) {
            set_action(9);
            return;
        }
        if (sequence_13e == 1) {
            if (frame_counter_144 > 20 && word_736 == 0) {
                word_736 = 1;
                emit_fighter_effect(62,
                    aerial ? static_cast<float>(x_ec - static_cast<float>(facing_104 * 35))
                           : static_cast<float>(static_cast<float>(facing_104 * 65) + x_ec),
                    static_cast<float>(y_f0 + (aerial ? 135.0 : 55.0)),
                    static_cast<unsigned char>(facing_104), 1);
            }
            if (frame_counter_144 > 60) {
                word_736 = 2;
                byte_750 = 0;
            }
            if (byte_750 == 0)
                next_sequence_block();
        }
        if (sequence_13e == 3 && frame_counter_144 > (word_736 + 1) * 10)
            next_sequence_block();
        return;
    }

// Mid-table trajectories and opponent-relative objects; no callable boundary.
        case 511: {
        const bool aerial = 511 == 502 || 511 == 503
            || 511 == 507 || 511 == 508
            || 511 == 512 || 511 == 513;
        const bool wide = 511 >= 510;
        const bool alternate = 511 >= 505;
        const bool second_input = 511 == 501 || 511 == 503
            || 511 == 506 || 511 == 508
            || 511 == 511 || 511 == 513;
        if (!aerial || sequence_13e == 5)
            resolve_stage_surface_landing_transition();
        byte_17c = wide ? 8 : alternate ? 4 : 0;
        if (sequence_13e <= 1 && (second_input ? field_6c4 : field_6c0) == 0)
            byte_750 = 0;
        if (aerial && sequence_13e < 5) {
            if (sequence_13e == 4) {
                acceleration_y_100 = 0.6f;
                velocity_y_f8 = static_cast<float>(velocity_y_f8 - static_cast<double>(0.6f));
            }
            if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
                zero_velocity_acceleration();
                y_f0 = reimu_stage_surface_height_at_x(this);
                set_sequence(5);
                return;
            }
        }
        if (sequence_13e == 2 && frame_timer_142 == 0
                && frame_index_140 == (aerial ? 1 : 2)) {
            adjust_counter_482(200, 120);
            state_180 = 1;
            add_scaled_counter(50);
            dispatch_character_wave_handle(wide ? 20 : 4);
            const int x_offset = aerial ? 50 : 114;
            const double y_offset = aerial ? 108.0 : 96.0;
            if (wide) {
                if (word_736 == 0) {
                    float parameters[3] = {30.0f, 15.0f, 0.0f};
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = 0.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -30.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                }
                if (word_736 == 1) {
                    float parameters[3] = {45.0f, 15.0f, 0.0f};
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = 15.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -15.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -45.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                }
                if (word_736 == 2) {
                    float parameters[3] = {60.0f, 15.0f, 0.0f};
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = 30.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = 0.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -30.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -60.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                }
            } else if (!alternate) {
                if (word_736 == 0) {
                    float parameters[3] = {20.0f, 15.0f, 0.0f};
                    spawn_owned_object_via_manager(810,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -20.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(810,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                }
                if (word_736 == 1) {
                    for (int angle = 20; angle < 60; angle += 20) {
                        float parameters[3] = {static_cast<float>(angle), 15.0f, 0.0f};
                        spawn_owned_object_via_manager(810,
                            static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                            static_cast<float>(y_f0 + y_offset),
                            static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    }
                    for (int angle = -20; angle > -60; angle -= 20) {
                        float parameters[3] = {static_cast<float>(angle), 15.0f, 0.0f};
                        spawn_owned_object_via_manager(810,
                            static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                            static_cast<float>(y_f0 + y_offset),
                            static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    }
                }
                if (word_736 == 2) {
                    for (int angle = 20; angle < 80; angle += 20) {
                        float parameters[3] = {static_cast<float>(angle), 15.0f, 0.0f};
                        spawn_owned_object_via_manager(810,
                            static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                            static_cast<float>(y_f0 + y_offset),
                            static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    }
                    for (int angle = -20; angle > -80; angle -= 20) {
                        float parameters[3] = {static_cast<float>(angle), 15.0f, 0.0f};
                        spawn_owned_object_via_manager(810,
                            static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                            static_cast<float>(y_f0 + y_offset),
                            static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    }
                }
            } else {
                if (word_736 == 0) {
                    float parameters[3] = {10.0f, 23.0f, 0.0f};
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = 0.0f; parameters[1] = 25.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -10.0f; parameters[1] = 23.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                }
                if (word_736 == 1) {
                    float parameters[3] = {15.0f, 25.0f, 0.0f};
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = 5.0f; parameters[1] = 27.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -5.0f; parameters[1] = 27.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -15.0f; parameters[1] = 25.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                }
                if (word_736 == 2) {
                    float parameters[3] = {20.0f, 26.0f, 0.0f};
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = 10.0f; parameters[1] = 27.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = 0.0f; parameters[1] = 29.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -10.0f; parameters[1] = 27.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -20.0f; parameters[1] = 26.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                }
            }
        }
        if (advance_frame_and_dispatch())
            set_action(0);
        if (aerial && frame_counter_144 == 0 && frame_timer_142 == 0
                && frame_index_140 == 0 && sequence_13e == 5) {
            set_action(9);
            return;
        }
        if (sequence_13e == 1) {
            if (frame_counter_144 > 20 && word_736 == 0) {
                word_736 = 1;
                emit_fighter_effect(62,
                    aerial ? static_cast<float>(x_ec - static_cast<float>(facing_104 * 35))
                           : static_cast<float>(static_cast<float>(facing_104 * 65) + x_ec),
                    static_cast<float>(y_f0 + (aerial ? 135.0 : 55.0)),
                    static_cast<unsigned char>(facing_104), 1);
            }
            if (frame_counter_144 > 60) {
                word_736 = 2;
                byte_750 = 0;
            }
            if (byte_750 == 0)
                next_sequence_block();
        }
        if (sequence_13e == 3 && frame_counter_144 > (word_736 + 1) * 10)
            next_sequence_block();
        return;
    }

// Mid-table trajectories and opponent-relative objects; no callable boundary.
        case 512: {
        const bool aerial = 512 == 502 || 512 == 503
            || 512 == 507 || 512 == 508
            || 512 == 512 || 512 == 513;
        const bool wide = 512 >= 510;
        const bool alternate = 512 >= 505;
        const bool second_input = 512 == 501 || 512 == 503
            || 512 == 506 || 512 == 508
            || 512 == 511 || 512 == 513;
        frame_threshold = 5;
        if (!aerial || sequence_13e == frame_threshold)
            resolve_stage_surface_landing_transition();
        byte_17c = wide ? 8 : alternate ? 4 : 0;
        frame_one = 1;
        if (sequence_13e <= frame_one && (second_input ? field_6c4 : field_6c0) == 0)
            byte_750 = 0;
        if (aerial && sequence_13e < frame_threshold) {
            if (sequence_13e == 4) {
                acceleration_y_100 = 0.6f;
                velocity_y_f8 = static_cast<float>(velocity_y_f8 - static_cast<double>(0.6f));
            }
            if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
                zero_velocity_acceleration();
                y_f0 = reimu_stage_surface_height_at_x(this);
                set_sequence(5);
                return;
            }
        }
        if (sequence_13e == 2 && frame_timer_142 == 0
                && frame_index_140 == (aerial ? frame_one : 2)) {
            adjust_counter_482(200, 120);
            state_180 = 1;
            add_scaled_counter(50);
            dispatch_character_wave_handle(wide ? 20 : 4);
            const int x_offset = aerial ? 50 : 114;
            const double y_offset = aerial ? 108.0 : 96.0;
            if (wide) {
                if (word_736 == 0) {
                    float parameters[3] = {30.0f, 15.0f, 0.0f};
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = 0.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -30.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                }
                if (word_736 == 1) {
                    float parameters[3] = {45.0f, 15.0f, 0.0f};
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = 15.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -15.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -45.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                }
                if (word_736 == 2) {
                    float parameters[3] = {60.0f, 15.0f, 0.0f};
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = 30.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = 0.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -30.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -60.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                }
            } else if (!alternate) {
                if (word_736 == 0) {
                    float parameters[3] = {20.0f, 15.0f, 0.0f};
                    spawn_owned_object_via_manager(810,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -20.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(810,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                }
                if (word_736 == 1) {
                    for (int angle = 20; angle < 60; angle += 20) {
                        float parameters[3] = {static_cast<float>(angle), 15.0f, 0.0f};
                        spawn_owned_object_via_manager(810,
                            static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                            static_cast<float>(y_f0 + y_offset),
                            static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    }
                    for (int angle = -20; angle > -60; angle -= 20) {
                        float parameters[3] = {static_cast<float>(angle), 15.0f, 0.0f};
                        spawn_owned_object_via_manager(810,
                            static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                            static_cast<float>(y_f0 + y_offset),
                            static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    }
                }
                if (word_736 == 2) {
                    for (int angle = 20; angle < 80; angle += 20) {
                        float parameters[3] = {static_cast<float>(angle), 15.0f, 0.0f};
                        spawn_owned_object_via_manager(810,
                            static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                            static_cast<float>(y_f0 + y_offset),
                            static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    }
                    for (int angle = -20; angle > -80; angle -= 20) {
                        float parameters[3] = {static_cast<float>(angle), 15.0f, 0.0f};
                        spawn_owned_object_via_manager(810,
                            static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                            static_cast<float>(y_f0 + y_offset),
                            static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    }
                }
            } else {
                if (word_736 == 0) {
                    float parameters[3] = {10.0f, 23.0f, 0.0f};
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = 0.0f; parameters[1] = 25.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -10.0f; parameters[1] = 23.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                }
                if (word_736 == 1) {
                    float parameters[3] = {15.0f, 25.0f, 0.0f};
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = 5.0f; parameters[1] = 27.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -5.0f; parameters[1] = 27.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -15.0f; parameters[1] = 25.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                }
                if (word_736 == 2) {
                    float parameters[3] = {20.0f, 26.0f, 0.0f};
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = 10.0f; parameters[1] = 27.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = 0.0f; parameters[1] = 29.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -10.0f; parameters[1] = 27.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -20.0f; parameters[1] = 26.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                }
            }
        }
        if (advance_frame_and_dispatch())
            set_action(0);
        if (aerial && frame_counter_144 == 0 && frame_timer_142 == 0
                && frame_index_140 == 0 && sequence_13e == 5) {
            set_action(9);
            return;
        }
        if (sequence_13e == 1) {
            if (frame_counter_144 > 20 && word_736 == 0) {
                word_736 = 1;
                emit_fighter_effect(62,
                    aerial ? static_cast<float>(x_ec - static_cast<float>(facing_104 * 35))
                           : static_cast<float>(static_cast<float>(facing_104 * 65) + x_ec),
                    static_cast<float>(y_f0 + (aerial ? 135.0 : 55.0)),
                    static_cast<unsigned char>(facing_104), 1);
            }
            if (frame_counter_144 > 60) {
                word_736 = 2;
                byte_750 = 0;
            }
            if (byte_750 == 0)
                next_sequence_block();
        }
        if (sequence_13e == 3 && frame_counter_144 > (word_736 + 1) * 10)
            next_sequence_block();
        return;
    }

// Mid-table trajectories and opponent-relative objects; no callable boundary.
        case 513: {
        const bool aerial = 513 == 502 || 513 == 503
            || 513 == 507 || 513 == 508
            || 513 == 512 || 513 == 513;
        const bool wide = 513 >= 510;
        const bool alternate = 513 >= 505;
        const bool second_input = 513 == 501 || 513 == 503
            || 513 == 506 || 513 == 508
            || 513 == 511 || 513 == 513;
        frame_threshold = 5;
        if (!aerial || sequence_13e == frame_threshold)
            resolve_stage_surface_landing_transition();
        byte_17c = wide ? 8 : alternate ? 4 : 0;
        frame_one = 1;
        if (sequence_13e <= frame_one && (second_input ? field_6c4 : field_6c0) == 0)
            byte_750 = 0;
        if (aerial && sequence_13e < frame_threshold) {
            if (sequence_13e == 4) {
                acceleration_y_100 = 0.6f;
                velocity_y_f8 = static_cast<float>(velocity_y_f8 - static_cast<double>(0.6f));
            }
            if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
                zero_velocity_acceleration();
                y_f0 = reimu_stage_surface_height_at_x(this);
                set_sequence(5);
                return;
            }
        }
        if (sequence_13e == 2 && frame_timer_142 == 0
                && frame_index_140 == (aerial ? frame_one : 2)) {
            adjust_counter_482(200, 120);
            state_180 = 1;
            add_scaled_counter(50);
            dispatch_character_wave_handle(wide ? 20 : 4);
            const int x_offset = aerial ? 50 : 114;
            const double y_offset = aerial ? 108.0 : 96.0;
            if (wide) {
                if (word_736 == 0) {
                    float parameters[3] = {30.0f, 15.0f, 0.0f};
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = 0.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -30.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                }
                if (word_736 == 1) {
                    float parameters[3] = {45.0f, 15.0f, 0.0f};
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = 15.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -15.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -45.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                }
                if (word_736 == 2) {
                    float parameters[3] = {60.0f, 15.0f, 0.0f};
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = 30.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = 0.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -30.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -60.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(812,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                }
            } else if (!alternate) {
                if (word_736 == 0) {
                    float parameters[3] = {20.0f, 15.0f, 0.0f};
                    spawn_owned_object_via_manager(810,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -20.0f;
                    parameters[1] = 15.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(810,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                }
                if (word_736 == 1) {
                    for (int angle = 20; angle < 60; angle += 20) {
                        float parameters[3] = {static_cast<float>(angle), 15.0f, 0.0f};
                        spawn_owned_object_via_manager(810,
                            static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                            static_cast<float>(y_f0 + y_offset),
                            static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    }
                    for (int angle = -20; angle > -60; angle -= 20) {
                        float parameters[3] = {static_cast<float>(angle), 15.0f, 0.0f};
                        spawn_owned_object_via_manager(810,
                            static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                            static_cast<float>(y_f0 + y_offset),
                            static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    }
                }
                if (word_736 == 2) {
                    for (int angle = 20; angle < 80; angle += 20) {
                        float parameters[3] = {static_cast<float>(angle), 15.0f, 0.0f};
                        spawn_owned_object_via_manager(810,
                            static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                            static_cast<float>(y_f0 + y_offset),
                            static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    }
                    for (int angle = -20; angle > -80; angle -= 20) {
                        float parameters[3] = {static_cast<float>(angle), 15.0f, 0.0f};
                        spawn_owned_object_via_manager(810,
                            static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                            static_cast<float>(y_f0 + y_offset),
                            static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    }
                }
            } else {
                if (word_736 == 0) {
                    float parameters[3] = {10.0f, 23.0f, 0.0f};
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = 0.0f; parameters[1] = 25.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -10.0f; parameters[1] = 23.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                }
                if (word_736 == 1) {
                    float parameters[3] = {15.0f, 25.0f, 0.0f};
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = 5.0f; parameters[1] = 27.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -5.0f; parameters[1] = 27.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -15.0f; parameters[1] = 25.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                }
                if (word_736 == 2) {
                    float parameters[3] = {20.0f, 26.0f, 0.0f};
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = 10.0f; parameters[1] = 27.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = 0.0f; parameters[1] = 29.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -10.0f; parameters[1] = 27.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    parameters[0] = -20.0f; parameters[1] = 26.0f; parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(811,
                        static_cast<float>(static_cast<float>(facing_104 * x_offset) + x_ec),
                        static_cast<float>(y_f0 + y_offset),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                }
            }
        }
        if (advance_frame_and_dispatch())
            set_action(0);
        if (aerial && frame_counter_144 == 0 && frame_timer_142 == 0
                && frame_index_140 == 0 && sequence_13e == 5) {
            set_action(9);
            return;
        }
        if (sequence_13e == 1) {
            if (frame_counter_144 > 20 && word_736 == 0) {
                word_736 = 1;
                emit_fighter_effect(62,
                    aerial ? static_cast<float>(x_ec - static_cast<float>(facing_104 * 35))
                           : static_cast<float>(static_cast<float>(facing_104 * 65) + x_ec),
                    static_cast<float>(y_f0 + (aerial ? 135.0 : 55.0)),
                    static_cast<unsigned char>(facing_104), 1);
            }
            if (frame_counter_144 > 60) {
                word_736 = 2;
                byte_750 = 0;
            }
            if (byte_750 == 0)
                next_sequence_block();
        }
        if (sequence_13e == 3 && frame_counter_144 > (word_736 + 1) * 10)
            next_sequence_block();
        return;
    }

// Mid-table trajectories and opponent-relative objects; no callable boundary.
        case 520: {
        const bool aerial = 520 == 522 || 520 == 523;
        const bool fast = 520 == 521 || 520 == 523;
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
                return;
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
            return;
        }
        if (sequence_13e == 1 && frame_counter_144 > 0)
            next_sequence_block();
        return;
    }
        case 521: {
        const bool aerial = 521 == 522 || 521 == 523;
        const bool fast = 521 == 521 || 521 == 523;
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
                return;
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
            return;
        }
        if (sequence_13e == 1 && frame_counter_144 > 0)
            next_sequence_block();
        return;
    }
        case 522: {
        const bool aerial = 522 == 522 || 522 == 523;
        const bool fast = 522 == 521 || 522 == 523;
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
                return;
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
            return;
        }
        if (sequence_13e == 1 && frame_counter_144 > 0)
            next_sequence_block();
        return;
    }
        case 523: {
        const bool aerial = 523 == 522 || 523 == 523;
        const bool fast = 523 == 521 || 523 == 523;
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
                return;
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
            return;
        }
        if (sequence_13e == 1 && frame_counter_144 > 0)
            next_sequence_block();
        return;
    }
        case 525:
        resolve_stage_surface_landing_transition();
        byte_17c = 5;
        if ((sequence_13e == 1 && frame_counter_144 > 10)
                || (sequence_13e == 2 && frame_counter_144 > 50)) {
            next_sequence_block();
            return;
        }
        if (advance_frame_and_dispatch())
            set_action(0);
        if (sequence_13e == 0 && frame_timer_142 == 0 && frame_index_140 == 7) {
            adjust_counter_482(200, 120);
            add_scaled_counter(50);
            state_180 = 1;
            float parameters[3];
            if (525 == 525) {
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
            if (525 == 526 || byte_609 >= 4) {
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
            if (525 == 526 && byte_609 >= 4) {
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
        return;
        case 526:
        resolve_stage_surface_landing_transition();
        byte_17c = 5;
        if ((sequence_13e == 1 && frame_counter_144 > 10)
                || (sequence_13e == 2 && frame_counter_144 > 50)) {
            next_sequence_block();
            return;
        }
        if (advance_frame_and_dispatch())
            set_action(0);
        if (sequence_13e == 0 && frame_timer_142 == 0 && frame_index_140 == 7) {
            adjust_counter_482(200, 120);
            add_scaled_counter(50);
            state_180 = 1;
            float parameters[3];
            if (526 == 525) {
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
            if (526 == 526 || byte_609 >= 4) {
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
            if (526 == 526 && byte_609 >= 4) {
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
        return;
        case 530:
        resolve_stage_surface_landing_transition();
        byte_17c = 9;
        if (sequence_13e == 1 && frame_counter_144 >= 18) {
            next_sequence_block();
            return;
        }
        if (advance_frame_and_dispatch())
            set_action(530 == 530 ? 0 : 2);
        if (frame_counter_144 == 0 && frame_timer_142 == 0
                && frame_index_140 == 0 && sequence_13e == 1) {
            adjust_counter_482(200, 120);
            add_scaled_counter(50);
            state_180 = 1;
            const float parameters[3] = {0.0f, 530 == 530 ? 0.0f : 20.0f,
                530 == 530 ? 0.0f : 9.0f};
            spawn_owned_object_via_manager(817,
                static_cast<float>(static_cast<float>(facing_104 * (530 == 530 ? 10 : 50)) + x_ec),
                static_cast<float>(y_f0 - 10.0),
                static_cast<unsigned char>(facing_104), -1, parameters, 3);
            dispatch_character_wave_handle(15);
        }
        return;

// Mid-table disappearance, movement and fan trajectories; no callable boundary.
        case 531:
        resolve_stage_surface_landing_transition();
        byte_17c = 9;
        if (sequence_13e == 1 && frame_counter_144 >= 18) {
            next_sequence_block();
            return;
        }
        if (advance_frame_and_dispatch())
            set_action(531 == 530 ? 0 : 2);
        if (frame_counter_144 == 0 && frame_timer_142 == 0
                && frame_index_140 == 0 && sequence_13e == 1) {
            adjust_counter_482(200, 120);
            add_scaled_counter(50);
            state_180 = 1;
            const float parameters[3] = {0.0f, 531 == 530 ? 0.0f : 20.0f,
                531 == 530 ? 0.0f : 9.0f};
            spawn_owned_object_via_manager(817,
                static_cast<float>(static_cast<float>(facing_104 * (531 == 530 ? 10 : 50)) + x_ec),
                static_cast<float>(y_f0 - 10.0),
                static_cast<unsigned char>(facing_104), -1, parameters, 3);
            dispatch_character_wave_handle(15);
        }
        return;

// Mid-table disappearance, movement and fan trajectories; no callable boundary.
        case 540: {
        const bool fan = 540 == 545 || 540 == 546;
        if ((540 == 540 && sequence_13e == 4)
                || (540 == 541 && sequence_13e >= 3 && sequence_13e <= 5)
                || (fan && sequence_13e == 6))
            resolve_stage_surface_landing_transition();
        byte_17c = fan ? 6 : 2;
        if (sequence_13e == 0) {
            if (frame_timer_142 == 0 && frame_index_140 == 4) {
                field_108 = 0.0f;
                field_10c = 100.0f;
                scale_11c = 1.0f;
                scale_120 = 1.0f;
                byte_113 = 255;
                byte_112 = 255;
                byte_111 = 255;
                byte_110 = 255;
                dispatch_character_wave_handle(6);
            }
            if (frame_index_140 > 3) {
                if (scale_11c > 0.0f) {
                    scale_11c = static_cast<float>(scale_11c - static_cast<double>(0.1f));
                    scale_120 = static_cast<float>(scale_120 + static_cast<double>(0.2f));
                }
                if (byte_113 > 25)
                    byte_113 = static_cast<unsigned char>(byte_113 - 25);
            }
        }
        if (sequence_13e == 2) {
            if (540 == 541)
                velocity_y_f8 = static_cast<float>(velocity_y_f8 - 1.0);
            if (540 == 541 || frame_index_140 < 5) {
                if (scale_11c < 1.0f) {
                    scale_11c = static_cast<float>(scale_11c + static_cast<double>(0.1f));
                    scale_120 = static_cast<float>(scale_120 - static_cast<double>(0.2f));
                    byte_113 = static_cast<unsigned char>(byte_113 + 25);
                } else {
                    scale_11c = 1.0f;
                    scale_120 = 1.0f;
                    byte_113 = 255;
                }
            }
            if (540 == 540 && frame_index_140 < 7)
                velocity_y_f8 = static_cast<float>(velocity_y_f8 - static_cast<double>(0.7f));
            if (540 == 541
                    && static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
                scale_11c = 1.0f;
                scale_120 = 1.0f;
                byte_113 = 255;
                y_f0 = reimu_stage_surface_height_at_x(this);
                velocity_y_f8 = 0.0f;
                set_sequence(3);
            }
        }
        if (540 == 540 && sequence_13e == 3
                && static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
            y_f0 = reimu_stage_surface_height_at_x(this);
            zero_velocity_acceleration();
            next_sequence_block();
            return;
        }
        if (540 == 541) {
            if (sequence_13e == 3) {
                if (state_180 != 0) {
                    word_734 = static_cast<short>(word_734 + 1);
                    if (word_734 > 5) {
                        state_180 = 0;
                        word_734 = 0;
                    }
                }
                if (frame_counter_144 > 15) {
                    next_sequence_block();
                    byte_184 = 1;
                }
            }
            if (sequence_13e == 4 && state_180 != 0) {
                word_734 = static_cast<short>(word_734 + 1);
                if (word_734 > 5) {
                    state_180 = 0;
                    word_734 = 0;
                }
            }
            if (sequence_13e > 3) {
                velocity_x_f4 = static_cast<float>(velocity_x_f4 - static_cast<double>(0.8f));
                if (velocity_x_f4 < 0.0f)
                    velocity_x_f4 = 0.0f;
            }
        }
        if (fan) {
            if (sequence_13e >= 2 && sequence_13e <= 5) {
                velocity_y_f8 -= acceleration_y_100;
                if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
                    y_f0 = reimu_stage_surface_height_at_x(this);
                    zero_velocity_acceleration();
                    set_sequence(6);
                    return;
                }
            }
            if (sequence_13e == 3 && frame_counter_144 >= 8) {
                next_sequence_block();
                return;
            }
        }
        if (advance_frame_and_dispatch())
            set_action(0);
        if (540 == 540) {
            if (frame_counter_144 == 0 && frame_timer_142 == 0
                    && frame_index_140 == 0 && sequence_13e == 2) {
                adjust_counter_482(200, 120);
                x_ec = static_cast<float>(peer_170->x_ec - facing_104 * 180);
                y_f0 = 200.0f;
                velocity_x_f4 = 6.0f;
                velocity_y_f8 = 8.0f;
                dispatch_character_wave_handle(6);
            }
            if (sequence_13e == 2 && frame_index_140 == 7 && frame_timer_142 == 0) {
                velocity_x_f4 = 7.5f;
                velocity_y_f8 = -24.0f;
                add_scaled_counter(50);
            }
        } else if (540 == 541) {
            if (frame_counter_144 == 0 && frame_timer_142 == 0
                    && frame_index_140 == 0 && sequence_13e == 1) {
                adjust_counter_482(200, 120);
                x_ec = static_cast<float>(facing_104 * 100 + x_ec);
                y_f0 = 50.0f;
                velocity_x_f4 = 15.0f;
                velocity_y_f8 = 6.0f;
                dispatch_character_wave_handle(6);
                add_scaled_counter(50);
            }
        } else {
            if (frame_counter_144 == 0 && frame_timer_142 == 0
                    && frame_index_140 == 0 && sequence_13e == 2) {
                adjust_counter_482(200, 120);
                if (540 == 546)
                    x_ec = static_cast<float>(x_ec - facing_104 * 320);
                y_f0 = static_cast<float>(y_f0 + 100.0);
                if (y_f0 > 350.0f)
                    y_f0 = 350.0f;
                velocity_x_f4 = 540 == 546 ? -5.0f : 5.0f;
                velocity_y_f8 = 15.0f;
                acceleration_y_100 = 0.5f;
                dispatch_character_wave_handle(6);
                const float parameters[3] = {0.0f, 0.0f, 3.0f};
                spawn_owned_object_via_manager(821, x_ec, static_cast<float>(y_f0 + 100.0),
                    static_cast<unsigned char>(facing_104), -1, parameters, 3);
            }
            if (frame_counter_144 == 0 && frame_timer_142 == 0
                    && frame_index_140 == 0 && sequence_13e == 3) {
                dispatch_character_wave_handle(14);
                add_scaled_counter(50);
                float parameters[3];
                for (int i = 0; i <= 5; ++i) {
                    if (byte_60a >= 4 && i <= 4) {
                        parameters[0] = static_cast<float>(540 == 546 ? 35.5 - i * 9.0 : i * 9.0 + 34.5);
                        parameters[1] = 22.0f;
                        parameters[2] = 0.0f;
                        spawn_owned_object_via_manager(821,
                            static_cast<float>(lookup_orientation_cosine_quantized_abs(-parameters[0])
                                * static_cast<float>(facing_104 * 50) + x_ec),
                            static_cast<float>(lookup_orientation_sine_quantized_abs(-parameters[0])
                                * 50.0 + y_f0 + 100.0),
                            static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    }
                    parameters[0] = static_cast<float>(540 == 546 ? 40.0 - i * 9.0 : i * 9.0 + 30.0);
                    parameters[1] = 25.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(821,
                        static_cast<float>(lookup_orientation_cosine_quantized_abs(-parameters[0])
                            * static_cast<float>(facing_104 * 50) + x_ec),
                        static_cast<float>(lookup_orientation_sine_quantized_abs(-parameters[0])
                            * 50.0 + y_f0 + 100.0),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                }
                parameters[0] = 0.0f;
                parameters[1] = 0.0f;
                parameters[2] = 4.0f;
                spawn_owned_object_via_manager(821, x_ec, static_cast<float>(y_f0 + 100.0),
                    static_cast<unsigned char>(facing_104), 1, parameters, 3);
                state_180 = 1;
            }
            if (frame_counter_144 == 0 && frame_timer_142 == 0
                    && frame_index_140 == 0 && sequence_13e == 5) {
                if (540 == 546)
                    goto reimu_shot_action9_exit;
                set_action(9);
            }
        }
        return;
    }



// Shared550/551 body and direct560, ending before the high-table selector.
        case 541: {
        const bool fan = 541 == 545 || 541 == 546;
        if ((541 == 540 && sequence_13e == 4)
                || (541 == 541 && sequence_13e >= 3 && sequence_13e <= 5)
                || (fan && sequence_13e == 6))
            resolve_stage_surface_landing_transition();
        byte_17c = fan ? 6 : 2;
        if (sequence_13e == 0) {
            if (frame_timer_142 == 0 && frame_index_140 == 4) {
                field_108 = 0.0f;
                field_10c = 100.0f;
                scale_11c = 1.0f;
                scale_120 = 1.0f;
                byte_113 = 255;
                byte_112 = 255;
                byte_111 = 255;
                byte_110 = 255;
                dispatch_character_wave_handle(6);
            }
            if (frame_index_140 > 3) {
                if (scale_11c > 0.0f) {
                    scale_11c = static_cast<float>(scale_11c - static_cast<double>(0.1f));
                    scale_120 = static_cast<float>(scale_120 + static_cast<double>(0.2f));
                }
                if (byte_113 > 25)
                    byte_113 = static_cast<unsigned char>(byte_113 - 25);
            }
        }
        if (sequence_13e == 2) {
            if (541 == 541)
                velocity_y_f8 = static_cast<float>(velocity_y_f8 - 1.0);
            if (541 == 541 || frame_index_140 < 5) {
                if (scale_11c < 1.0f) {
                    scale_11c = static_cast<float>(scale_11c + static_cast<double>(0.1f));
                    scale_120 = static_cast<float>(scale_120 - static_cast<double>(0.2f));
                    byte_113 = static_cast<unsigned char>(byte_113 + 25);
                } else {
                    scale_11c = 1.0f;
                    scale_120 = 1.0f;
                    byte_113 = 255;
                }
            }
            if (541 == 540 && frame_index_140 < 7)
                velocity_y_f8 = static_cast<float>(velocity_y_f8 - static_cast<double>(0.7f));
            if (541 == 541
                    && static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
                scale_11c = 1.0f;
                scale_120 = 1.0f;
                byte_113 = 255;
                y_f0 = reimu_stage_surface_height_at_x(this);
                velocity_y_f8 = 0.0f;
                set_sequence(3);
            }
        }
        if (541 == 540 && sequence_13e == 3
                && static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
            y_f0 = reimu_stage_surface_height_at_x(this);
            zero_velocity_acceleration();
            next_sequence_block();
            return;
        }
        if (541 == 541) {
            if (sequence_13e == 3) {
                if (state_180 != 0) {
                    word_734 = static_cast<short>(word_734 + 1);
                    if (word_734 > 5) {
                        state_180 = 0;
                        word_734 = 0;
                    }
                }
                if (frame_counter_144 > 15) {
                    next_sequence_block();
                    byte_184 = 1;
                }
            }
            if (sequence_13e == 4 && state_180 != 0) {
                word_734 = static_cast<short>(word_734 + 1);
                if (word_734 > 5) {
                    state_180 = 0;
                    word_734 = 0;
                }
            }
            if (sequence_13e > 3) {
                velocity_x_f4 = static_cast<float>(velocity_x_f4 - static_cast<double>(0.8f));
                if (velocity_x_f4 < 0.0f)
                    velocity_x_f4 = 0.0f;
            }
        }
        if (fan) {
            if (sequence_13e >= 2 && sequence_13e <= 5) {
                velocity_y_f8 -= acceleration_y_100;
                if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
                    y_f0 = reimu_stage_surface_height_at_x(this);
                    zero_velocity_acceleration();
                    set_sequence(6);
                    return;
                }
            }
            if (sequence_13e == 3 && frame_counter_144 >= 8) {
                next_sequence_block();
                return;
            }
        }
        if (advance_frame_and_dispatch())
            set_action(0);
        if (541 == 540) {
            if (frame_counter_144 == 0 && frame_timer_142 == 0
                    && frame_index_140 == 0 && sequence_13e == 2) {
                adjust_counter_482(200, 120);
                x_ec = static_cast<float>(peer_170->x_ec - facing_104 * 180);
                y_f0 = 200.0f;
                velocity_x_f4 = 6.0f;
                velocity_y_f8 = 8.0f;
                dispatch_character_wave_handle(6);
            }
            if (sequence_13e == 2 && frame_index_140 == 7 && frame_timer_142 == 0) {
                velocity_x_f4 = 7.5f;
                velocity_y_f8 = -24.0f;
                add_scaled_counter(50);
            }
        } else if (541 == 541) {
            if (frame_counter_144 == 0 && frame_timer_142 == 0
                    && frame_index_140 == 0 && sequence_13e == 1) {
                adjust_counter_482(200, 120);
                x_ec = static_cast<float>(facing_104 * 100 + x_ec);
                y_f0 = 50.0f;
                velocity_x_f4 = 15.0f;
                velocity_y_f8 = 6.0f;
                dispatch_character_wave_handle(6);
                add_scaled_counter(50);
            }
        } else {
            if (frame_counter_144 == 0 && frame_timer_142 == 0
                    && frame_index_140 == 0 && sequence_13e == 2) {
                adjust_counter_482(200, 120);
                if (541 == 546)
                    x_ec = static_cast<float>(x_ec - facing_104 * 320);
                y_f0 = static_cast<float>(y_f0 + 100.0);
                if (y_f0 > 350.0f)
                    y_f0 = 350.0f;
                velocity_x_f4 = 541 == 546 ? -5.0f : 5.0f;
                velocity_y_f8 = 15.0f;
                acceleration_y_100 = 0.5f;
                dispatch_character_wave_handle(6);
                const float parameters[3] = {0.0f, 0.0f, 3.0f};
                spawn_owned_object_via_manager(821, x_ec, static_cast<float>(y_f0 + 100.0),
                    static_cast<unsigned char>(facing_104), -1, parameters, 3);
            }
            if (frame_counter_144 == 0 && frame_timer_142 == 0
                    && frame_index_140 == 0 && sequence_13e == 3) {
                dispatch_character_wave_handle(14);
                add_scaled_counter(50);
                float parameters[3];
                for (int i = 0; i <= 5; ++i) {
                    if (byte_60a >= 4 && i <= 4) {
                        parameters[0] = static_cast<float>(541 == 546 ? 35.5 - i * 9.0 : i * 9.0 + 34.5);
                        parameters[1] = 22.0f;
                        parameters[2] = 0.0f;
                        spawn_owned_object_via_manager(821,
                            static_cast<float>(lookup_orientation_cosine_quantized_abs(-parameters[0])
                                * static_cast<float>(facing_104 * 50) + x_ec),
                            static_cast<float>(lookup_orientation_sine_quantized_abs(-parameters[0])
                                * 50.0 + y_f0 + 100.0),
                            static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    }
                    parameters[0] = static_cast<float>(541 == 546 ? 40.0 - i * 9.0 : i * 9.0 + 30.0);
                    parameters[1] = 25.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(821,
                        static_cast<float>(lookup_orientation_cosine_quantized_abs(-parameters[0])
                            * static_cast<float>(facing_104 * 50) + x_ec),
                        static_cast<float>(lookup_orientation_sine_quantized_abs(-parameters[0])
                            * 50.0 + y_f0 + 100.0),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                }
                parameters[0] = 0.0f;
                parameters[1] = 0.0f;
                parameters[2] = 4.0f;
                spawn_owned_object_via_manager(821, x_ec, static_cast<float>(y_f0 + 100.0),
                    static_cast<unsigned char>(facing_104), 1, parameters, 3);
                state_180 = 1;
            }
            if (frame_counter_144 == 0 && frame_timer_142 == 0
                    && frame_index_140 == 0 && sequence_13e == 5) {
                if (541 == 546)
                    goto reimu_shot_action9_exit;
                set_action(9);
            }
        }
        return;
    }



// Shared550/551 body and direct560, ending before the high-table selector.
        case 545: {
        const bool fan = 545 == 545 || 545 == 546;
        if ((545 == 540 && sequence_13e == 4)
                || (545 == 541 && sequence_13e >= 3 && sequence_13e <= 5)
                || (fan && sequence_13e == 6))
            resolve_stage_surface_landing_transition();
        byte_17c = fan ? 6 : 2;
        if (sequence_13e == 0) {
            if (frame_timer_142 == 0 && frame_index_140 == 4) {
                field_108 = 0.0f;
                field_10c = 100.0f;
                scale_11c = 1.0f;
                scale_120 = 1.0f;
                byte_113 = 255;
                byte_112 = 255;
                byte_111 = 255;
                byte_110 = 255;
                dispatch_character_wave_handle(6);
            }
            if (frame_index_140 > 3) {
                if (scale_11c > 0.0f) {
                    scale_11c = static_cast<float>(scale_11c - static_cast<double>(0.1f));
                    scale_120 = static_cast<float>(scale_120 + static_cast<double>(0.2f));
                }
                if (byte_113 > 25)
                    byte_113 = static_cast<unsigned char>(byte_113 - 25);
            }
        }
        if (sequence_13e == 2) {
            if (545 == 541)
                velocity_y_f8 = static_cast<float>(velocity_y_f8 - 1.0);
            if (545 == 541 || frame_index_140 < 5) {
                if (scale_11c < 1.0f) {
                    scale_11c = static_cast<float>(scale_11c + static_cast<double>(0.1f));
                    scale_120 = static_cast<float>(scale_120 - static_cast<double>(0.2f));
                    byte_113 = static_cast<unsigned char>(byte_113 + 25);
                } else {
                    scale_11c = 1.0f;
                    scale_120 = 1.0f;
                    byte_113 = 255;
                }
            }
            if (545 == 540 && frame_index_140 < 7)
                velocity_y_f8 = static_cast<float>(velocity_y_f8 - static_cast<double>(0.7f));
            if (545 == 541
                    && static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
                scale_11c = 1.0f;
                scale_120 = 1.0f;
                byte_113 = 255;
                y_f0 = reimu_stage_surface_height_at_x(this);
                velocity_y_f8 = 0.0f;
                set_sequence(3);
            }
        }
        if (545 == 540 && sequence_13e == 3
                && static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
            y_f0 = reimu_stage_surface_height_at_x(this);
            zero_velocity_acceleration();
            next_sequence_block();
            return;
        }
        if (545 == 541) {
            if (sequence_13e == 3) {
                if (state_180 != 0) {
                    word_734 = static_cast<short>(word_734 + 1);
                    if (word_734 > 5) {
                        state_180 = 0;
                        word_734 = 0;
                    }
                }
                if (frame_counter_144 > 15) {
                    next_sequence_block();
                    byte_184 = 1;
                }
            }
            if (sequence_13e == 4 && state_180 != 0) {
                word_734 = static_cast<short>(word_734 + 1);
                if (word_734 > 5) {
                    state_180 = 0;
                    word_734 = 0;
                }
            }
            if (sequence_13e > 3) {
                velocity_x_f4 = static_cast<float>(velocity_x_f4 - static_cast<double>(0.8f));
                if (velocity_x_f4 < 0.0f)
                    velocity_x_f4 = 0.0f;
            }
        }
        if (fan) {
            if (sequence_13e >= 2 && sequence_13e <= 5) {
                velocity_y_f8 -= acceleration_y_100;
                if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
                    y_f0 = reimu_stage_surface_height_at_x(this);
                    zero_velocity_acceleration();
                    set_sequence(6);
                    return;
                }
            }
            if (sequence_13e == 3 && frame_counter_144 >= 8) {
                next_sequence_block();
                return;
            }
        }
        if (advance_frame_and_dispatch())
            set_action(0);
        if (545 == 540) {
            if (frame_counter_144 == 0 && frame_timer_142 == 0
                    && frame_index_140 == 0 && sequence_13e == 2) {
                adjust_counter_482(200, 120);
                x_ec = static_cast<float>(peer_170->x_ec - facing_104 * 180);
                y_f0 = 200.0f;
                velocity_x_f4 = 6.0f;
                velocity_y_f8 = 8.0f;
                dispatch_character_wave_handle(6);
            }
            if (sequence_13e == 2 && frame_index_140 == 7 && frame_timer_142 == 0) {
                velocity_x_f4 = 7.5f;
                velocity_y_f8 = -24.0f;
                add_scaled_counter(50);
            }
        } else if (545 == 541) {
            if (frame_counter_144 == 0 && frame_timer_142 == 0
                    && frame_index_140 == 0 && sequence_13e == 1) {
                adjust_counter_482(200, 120);
                x_ec = static_cast<float>(facing_104 * 100 + x_ec);
                y_f0 = 50.0f;
                velocity_x_f4 = 15.0f;
                velocity_y_f8 = 6.0f;
                dispatch_character_wave_handle(6);
                add_scaled_counter(50);
            }
        } else {
            if (frame_counter_144 == 0 && frame_timer_142 == 0
                    && frame_index_140 == 0 && sequence_13e == 2) {
                adjust_counter_482(200, 120);
                if (545 == 546)
                    x_ec = static_cast<float>(x_ec - facing_104 * 320);
                y_f0 = static_cast<float>(y_f0 + 100.0);
                if (y_f0 > 350.0f)
                    y_f0 = 350.0f;
                velocity_x_f4 = 545 == 546 ? -5.0f : 5.0f;
                velocity_y_f8 = 15.0f;
                acceleration_y_100 = 0.5f;
                dispatch_character_wave_handle(6);
                const float parameters[3] = {0.0f, 0.0f, 3.0f};
                spawn_owned_object_via_manager(821, x_ec, static_cast<float>(y_f0 + 100.0),
                    static_cast<unsigned char>(facing_104), -1, parameters, 3);
            }
            if (frame_counter_144 == 0 && frame_timer_142 == 0
                    && frame_index_140 == 0 && sequence_13e == 3) {
                dispatch_character_wave_handle(14);
                add_scaled_counter(50);
                float parameters[3];
                for (int i = 0; i <= 5; ++i) {
                    if (byte_60a >= 4 && i <= 4) {
                        parameters[0] = static_cast<float>(545 == 546 ? 35.5 - i * 9.0 : i * 9.0 + 34.5);
                        parameters[1] = 22.0f;
                        parameters[2] = 0.0f;
                        spawn_owned_object_via_manager(821,
                            static_cast<float>(lookup_orientation_cosine_quantized_abs(-parameters[0])
                                * static_cast<float>(facing_104 * 50) + x_ec),
                            static_cast<float>(lookup_orientation_sine_quantized_abs(-parameters[0])
                                * 50.0 + y_f0 + 100.0),
                            static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    }
                    parameters[0] = static_cast<float>(545 == 546 ? 40.0 - i * 9.0 : i * 9.0 + 30.0);
                    parameters[1] = 25.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(821,
                        static_cast<float>(lookup_orientation_cosine_quantized_abs(-parameters[0])
                            * static_cast<float>(facing_104 * 50) + x_ec),
                        static_cast<float>(lookup_orientation_sine_quantized_abs(-parameters[0])
                            * 50.0 + y_f0 + 100.0),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                }
                parameters[0] = 0.0f;
                parameters[1] = 0.0f;
                parameters[2] = 4.0f;
                spawn_owned_object_via_manager(821, x_ec, static_cast<float>(y_f0 + 100.0),
                    static_cast<unsigned char>(facing_104), 1, parameters, 3);
                state_180 = 1;
            }
            if (frame_counter_144 == 0 && frame_timer_142 == 0
                    && frame_index_140 == 0 && sequence_13e == 5) {
                if (545 == 546)
                    goto reimu_shot_action9_exit;
                set_action(9);
            }
        }
        return;
    }



// Shared550/551 body and direct560, ending before the high-table selector.
        case 546: {
        const bool fan = 546 == 545 || 546 == 546;
        if ((546 == 540 && sequence_13e == 4)
                || (546 == 541 && sequence_13e >= 3 && sequence_13e <= 5)
                || (fan && sequence_13e == 6))
            resolve_stage_surface_landing_transition();
        byte_17c = fan ? 6 : 2;
        if (sequence_13e == 0) {
            if (frame_timer_142 == 0 && frame_index_140 == 4) {
                field_108 = 0.0f;
                field_10c = 100.0f;
                scale_11c = 1.0f;
                scale_120 = 1.0f;
                byte_113 = 255;
                byte_112 = 255;
                byte_111 = 255;
                byte_110 = 255;
                dispatch_character_wave_handle(6);
            }
            if (frame_index_140 > 3) {
                if (scale_11c > 0.0f) {
                    scale_11c = static_cast<float>(scale_11c - static_cast<double>(0.1f));
                    scale_120 = static_cast<float>(scale_120 + static_cast<double>(0.2f));
                }
                if (byte_113 > 25)
                    byte_113 = static_cast<unsigned char>(byte_113 - 25);
            }
        }
        if (sequence_13e == 2) {
            if (546 == 541)
                velocity_y_f8 = static_cast<float>(velocity_y_f8 - 1.0);
            if (546 == 541 || frame_index_140 < 5) {
                if (scale_11c < 1.0f) {
                    scale_11c = static_cast<float>(scale_11c + static_cast<double>(0.1f));
                    scale_120 = static_cast<float>(scale_120 - static_cast<double>(0.2f));
                    byte_113 = static_cast<unsigned char>(byte_113 + 25);
                } else {
                    scale_11c = 1.0f;
                    scale_120 = 1.0f;
                    byte_113 = 255;
                }
            }
            if (546 == 540 && frame_index_140 < 7)
                velocity_y_f8 = static_cast<float>(velocity_y_f8 - static_cast<double>(0.7f));
            if (546 == 541
                    && static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
                scale_11c = 1.0f;
                scale_120 = 1.0f;
                byte_113 = 255;
                y_f0 = reimu_stage_surface_height_at_x(this);
                velocity_y_f8 = 0.0f;
                set_sequence(3);
            }
        }
        if (546 == 540 && sequence_13e == 3
                && static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
            y_f0 = reimu_stage_surface_height_at_x(this);
            zero_velocity_acceleration();
            next_sequence_block();
            return;
        }
        if (546 == 541) {
            if (sequence_13e == 3) {
                if (state_180 != 0) {
                    word_734 = static_cast<short>(word_734 + 1);
                    if (word_734 > 5) {
                        state_180 = 0;
                        word_734 = 0;
                    }
                }
                if (frame_counter_144 > 15) {
                    next_sequence_block();
                    byte_184 = 1;
                }
            }
            if (sequence_13e == 4 && state_180 != 0) {
                word_734 = static_cast<short>(word_734 + 1);
                if (word_734 > 5) {
                    state_180 = 0;
                    word_734 = 0;
                }
            }
            if (sequence_13e > 3) {
                velocity_x_f4 = static_cast<float>(velocity_x_f4 - static_cast<double>(0.8f));
                if (velocity_x_f4 < 0.0f)
                    velocity_x_f4 = 0.0f;
            }
        }
        if (fan) {
            if (sequence_13e >= 2 && sequence_13e <= 5) {
                velocity_y_f8 -= acceleration_y_100;
                if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
                    y_f0 = reimu_stage_surface_height_at_x(this);
                    zero_velocity_acceleration();
                    set_sequence(6);
                    return;
                }
            }
            if (sequence_13e == 3 && frame_counter_144 >= 8) {
                next_sequence_block();
                return;
            }
        }
        if (advance_frame_and_dispatch())
            set_action(0);
        if (546 == 540) {
            if (frame_counter_144 == 0 && frame_timer_142 == 0
                    && frame_index_140 == 0 && sequence_13e == 2) {
                adjust_counter_482(200, 120);
                x_ec = static_cast<float>(peer_170->x_ec - facing_104 * 180);
                y_f0 = 200.0f;
                velocity_x_f4 = 6.0f;
                velocity_y_f8 = 8.0f;
                dispatch_character_wave_handle(6);
            }
            if (sequence_13e == 2 && frame_index_140 == 7 && frame_timer_142 == 0) {
                velocity_x_f4 = 7.5f;
                velocity_y_f8 = -24.0f;
                add_scaled_counter(50);
            }
        } else if (546 == 541) {
            if (frame_counter_144 == 0 && frame_timer_142 == 0
                    && frame_index_140 == 0 && sequence_13e == 1) {
                adjust_counter_482(200, 120);
                x_ec = static_cast<float>(facing_104 * 100 + x_ec);
                y_f0 = 50.0f;
                velocity_x_f4 = 15.0f;
                velocity_y_f8 = 6.0f;
                dispatch_character_wave_handle(6);
                add_scaled_counter(50);
            }
        } else {
            if (frame_counter_144 == 0 && frame_timer_142 == 0
                    && frame_index_140 == 0 && sequence_13e == 2) {
                adjust_counter_482(200, 120);
                if (546 == 546)
                    x_ec = static_cast<float>(x_ec - facing_104 * 320);
                y_f0 = static_cast<float>(y_f0 + 100.0);
                if (y_f0 > 350.0f)
                    y_f0 = 350.0f;
                velocity_x_f4 = 546 == 546 ? -5.0f : 5.0f;
                velocity_y_f8 = 15.0f;
                acceleration_y_100 = 0.5f;
                dispatch_character_wave_handle(6);
                const float parameters[3] = {0.0f, 0.0f, 3.0f};
                spawn_owned_object_via_manager(821, x_ec, static_cast<float>(y_f0 + 100.0),
                    static_cast<unsigned char>(facing_104), -1, parameters, 3);
            }
            if (frame_counter_144 == 0 && frame_timer_142 == 0
                    && frame_index_140 == 0 && sequence_13e == 3) {
                dispatch_character_wave_handle(14);
                add_scaled_counter(50);
                float parameters[3];
                for (int i = 0; i <= 5; ++i) {
                    if (byte_60a >= 4 && i <= 4) {
                        parameters[0] = static_cast<float>(546 == 546 ? 35.5 - i * 9.0 : i * 9.0 + 34.5);
                        parameters[1] = 22.0f;
                        parameters[2] = 0.0f;
                        spawn_owned_object_via_manager(821,
                            static_cast<float>(lookup_orientation_cosine_quantized_abs(-parameters[0])
                                * static_cast<float>(facing_104 * 50) + x_ec),
                            static_cast<float>(lookup_orientation_sine_quantized_abs(-parameters[0])
                                * 50.0 + y_f0 + 100.0),
                            static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    }
                    parameters[0] = static_cast<float>(546 == 546 ? 40.0 - i * 9.0 : i * 9.0 + 30.0);
                    parameters[1] = 25.0f;
                    parameters[2] = 0.0f;
                    spawn_owned_object_via_manager(821,
                        static_cast<float>(lookup_orientation_cosine_quantized_abs(-parameters[0])
                            * static_cast<float>(facing_104 * 50) + x_ec),
                        static_cast<float>(lookup_orientation_sine_quantized_abs(-parameters[0])
                            * 50.0 + y_f0 + 100.0),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                }
                parameters[0] = 0.0f;
                parameters[1] = 0.0f;
                parameters[2] = 4.0f;
                spawn_owned_object_via_manager(821, x_ec, static_cast<float>(y_f0 + 100.0),
                    static_cast<unsigned char>(facing_104), 1, parameters, 3);
                state_180 = 1;
            }
            if (frame_counter_144 == 0 && frame_timer_142 == 0
                    && frame_index_140 == 0 && sequence_13e == 5) {
                if (546 == 546)
                    goto reimu_shot_action9_exit;
                set_action(9);
            }
        }
        return;
    }



// Shared550/551 body and direct560, ending before the high-table selector.
    reimu_shot_action9_exit:
    set_action(9);
    return;
    case 550: case 551:
        byte_17c = 10;
        if (frame_counter_144 == 0 && frame_timer_142 == 0
                && frame_index_140 == 0 && sequence_13e == 2)
            velocity_x_f4 = -2.0f;
        switch (sequence_13e) {
        case 0:
            resolve_stage_surface_landing_transition();
            if (state_180 == 3) {
                state_180 = 0;
                next_sequence_block();
                dispatch_character_wave_handle(18);
                return;
            }
            break;
        case 1:
            if (frame_timer_142 % 3 == 0) {
                if (frame_timer_142 <= 9) {
                    float parameters[4];
                    parameters[1] = 0.0f;
                    parameters[2] = 4.0f;
                    parameters[3] = 0.0f;
                    for (float i = 0.0f; i < 8.0f; i += 1.0f) {
                        const unsigned int random = static_cast<unsigned int>(selector_random_roll(45));
                        parameters[0] = static_cast<float>(static_cast<double>(static_cast<float>(random)) + i * 45.0);
                        spawn_owned_object_via_manager(822,
                            static_cast<float>(lookup_orientation_cosine_quantized_abs(parameters[0])
                                * static_cast<float>(frame_timer_142 * 20) * facing_104 + x_ec),
                            static_cast<float>(lookup_orientation_sine_quantized_abs(parameters[0])
                                * static_cast<float>(frame_timer_142 * 20) + y_f0 + 100.0),
                            static_cast<unsigned char>(facing_104), 1, parameters, 4);
                    }
                }
                if (frame_timer_142 == 0) {
                    float parameters[4];
                    parameters[2] = 0.0f;
                    for (float sector = 0.0f; sector < 5.0f; sector += 1.0f) {
                        const double offset = sector * 72.0;
                        const float trajectory = static_cast<float>(offset - 90.0 + 162.0);
                        const float geometry = static_cast<float>(90.0 - offset);
                        for (float layer = 0.0f; layer < 5.0f; layer += 1.0f) {
                            parameters[0] = trajectory;
                            parameters[1] = static_cast<float>(layer * 18.0 + 8.0);
                            parameters[3] = static_cast<float>(layer + 30.0);
                            spawn_owned_object_via_manager(822,
                                static_cast<float>(lookup_orientation_cosine_quantized_abs(geometry)
                                    * 250.0 * facing_104 + x_ec),
                                static_cast<float>(lookup_orientation_sine_quantized_abs(geometry)
                                    * 250.0 + y_f0 + 100.0),
                                static_cast<unsigned char>(facing_104), 1, parameters, 4);
                        }
                    }
                }
            }
            break;
        case 2: case 3:
            velocity_y_f8 -= acceleration_y_100;
            if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
                set_action(10);
                y_f0 = reimu_stage_surface_height_at_x(this);
                zero_velocity_acceleration();
                byte_113 = 255;
                return;
            }
            if (byte_113 < 245)
                byte_113 = static_cast<unsigned char>(byte_113 + 10);
            else
                byte_113 = 255;
            break;
        }
        if (advance_frame_and_dispatch())
            set_action(0);
        if (frame_counter_144 == 0 && frame_timer_142 == 0
                && frame_index_140 == 0 && sequence_13e == 1) {
            set_action(0);
            return;
        }
        if (frame_counter_144 == 0 && frame_timer_142 == 0
                && frame_index_140 == 0 && sequence_13e == 2) {
            velocity_x_f4 = -200.0f;
            y_f0 = static_cast<float>(y_f0 + 100.0);
            velocity_y_f8 = 2.0f;
            byte_113 = 0;
            acceleration_y_100 = 0.5f;
        }
        if (sequence_13e == 0 && frame_timer_142 == 0 && frame_index_140 == 3) {
            adjust_counter_482(200, 120);
            add_scaled_counter(50);
        }
        return;
        case 560:
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
            return;
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
            velocity_y_f8 = 14.0f;
            acceleration_y_100 = 0.75f;
        }
        return;

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
            return;
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
        return;
        case 565: {
        if ((sequence_13e == 0 && frame_index_140 <= 1) || sequence_13e == 1
                || sequence_13e == 2 || sequence_13e == 3 || sequence_13e == 6 || sequence_13e == 8)
            resolve_stage_surface_landing_transition();
        byte_17c = 7;
        if ((565 == 565 ? field_6c0 : field_6c4) == 0)
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
                return;
            }
            if (frame_counter_144 > 25) {
                set_sequence(8);
                return;
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
            return;
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
            return;
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
        return;
    }
        case 566: {
        if ((sequence_13e == 0 && frame_index_140 <= 1) || sequence_13e == 1
                || sequence_13e == 2 || sequence_13e == 3 || sequence_13e == 6 || sequence_13e == 8)
            resolve_stage_surface_landing_transition();
        byte_17c = 7;
        if ((566 == 565 ? field_6c0 : field_6c4) == 0)
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
                return;
            }
            if (frame_counter_144 > 25) {
                set_sequence(8);
                return;
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
            return;
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
            return;
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
        return;
    }
        case 600: {
        resolve_stage_surface_landing_transition();
        publish_texture_state(6, 2);
        const int limit = 600 == 600 ? 30 : 600 == 601 ? 60 : 45;
        if (sequence_13e == 1 && frame_counter_144 > limit) {
            next_sequence_block();
            return;
        }
        const int count_limit = 600 == 600 ? 5 : 600 == 601 ? 10 : 14;
        if (600 == 602
                ? frame_counter_144 == 0 && frame_timer_142 == 0
                    && frame_index_140 == 0 && sequence_13e == 1 && word_730 < count_limit
                : sequence_13e == 1 && word_730 < count_limit && frame_counter_144 % 5 == 0) {
            dispatch_character_wave_handle(8);
            float angle;
            if (600 == 600)
                angle = static_cast<float>((word_730 - 2) * 45);
            else if (600 == 601)
                angle = static_cast<float>(word_730 * -36.0);
            else
                angle = static_cast<float>(static_cast<double>(static_cast<float>(mt19937_next_u32() % 70U)) - 35.0);
            float parameters[3] = {angle, 0.0f, static_cast<float>(word_730 % 3)};
            spawn_owned_object_via_manager(600 == 600 ? 850 : 600 == 601 ? 853 : 854,
                static_cast<float>(static_cast<float>(facing_104 * 18) + x_ec),
                static_cast<float>(y_f0 + 120.0),
                static_cast<unsigned char>(facing_104), 1, parameters, 3);
            if (600 == 601) {
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
            if (600 != 602)
                publish_texture_state(6, static_cast<short>(600 == 600 ? 30 : 60));
        }
        if (sequence_13e == 0 && frame_index_140 == 2 && frame_timer_142 == 0) {
            set_word_48a(40);
            dispatch_indexed_event_member(23);
            const int direction_bits = static_cast<unsigned char>(facing_104);
            emit_fighter_effect(115,
                static_cast<float>(x_ec - static_cast<signed char>(direction_bits) * 2),
                static_cast<float>(y_f0 + 120.0), direction_bits, 1);
            dispatch_indexed_sequence_window_45c8b0(0, 600 == 601 ? 5 : 2, 60);
            advance_secondary_event_effect_cycle();
        }
        return;
    }
        case 601: {
        resolve_stage_surface_landing_transition();
        publish_texture_state(6, 2);
        const int limit = 601 == 600 ? 30 : 601 == 601 ? 60 : 45;
        if (sequence_13e == 1 && frame_counter_144 > limit) {
            next_sequence_block();
            return;
        }
        const int count_limit = 601 == 600 ? 5 : 601 == 601 ? 10 : 14;
        if (601 == 602
                ? frame_counter_144 == 0 && frame_timer_142 == 0
                    && frame_index_140 == 0 && sequence_13e == 1 && word_730 < count_limit
                : sequence_13e == 1 && word_730 < count_limit && frame_counter_144 % 5 == 0) {
            dispatch_character_wave_handle(8);
            float angle;
            if (601 == 600)
                angle = static_cast<float>((word_730 - 2) * 45);
            else if (601 == 601)
                angle = static_cast<float>(word_730 * -36.0);
            else
                angle = static_cast<float>(static_cast<double>(static_cast<float>(mt19937_next_u32() % 70U)) - 35.0);
            float parameters[3] = {angle, 0.0f, static_cast<float>(word_730 % 3)};
            spawn_owned_object_via_manager(601 == 600 ? 850 : 601 == 601 ? 853 : 854,
                static_cast<float>(static_cast<float>(facing_104 * 18) + x_ec),
                static_cast<float>(y_f0 + 120.0),
                static_cast<unsigned char>(facing_104), 1, parameters, 3);
            if (601 == 601) {
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
            if (601 != 602)
                publish_texture_state(6, static_cast<short>(601 == 600 ? 30 : 60));
        }
        if (sequence_13e == 0 && frame_index_140 == 2 && frame_timer_142 == 0) {
            set_word_48a(40);
            dispatch_indexed_event_member(23);
            const int direction_bits = static_cast<unsigned char>(facing_104);
            emit_fighter_effect(115,
                static_cast<float>(x_ec - static_cast<signed char>(direction_bits) * 2),
                static_cast<float>(y_f0 + 120.0), direction_bits, 1);
            dispatch_indexed_sequence_window_45c8b0(0, 601 == 601 ? 5 : 2, 60);
            advance_secondary_event_effect_cycle();
        }
        return;
    }
        case 602: {
        resolve_stage_surface_landing_transition();
        publish_texture_state(6, 2);
        const int limit = 602 == 600 ? 30 : 602 == 601 ? 60 : 45;
        if (sequence_13e == 1 && frame_counter_144 > limit) {
            next_sequence_block();
            return;
        }
        const int count_limit = 602 == 600 ? 5 : 602 == 601 ? 10 : 14;
        if (602 == 602
                ? frame_counter_144 == 0 && frame_timer_142 == 0
                    && frame_index_140 == 0 && sequence_13e == 1 && word_730 < count_limit
                : sequence_13e == 1 && word_730 < count_limit && frame_counter_144 % 5 == 0) {
            dispatch_character_wave_handle(8);
            float angle;
            if (602 == 600)
                angle = static_cast<float>((word_730 - 2) * 45);
            else if (602 == 601)
                angle = static_cast<float>(word_730 * -36.0);
            else
                angle = static_cast<float>(static_cast<double>(static_cast<float>(mt19937_next_u32() % 70U)) - 35.0);
            float parameters[3] = {angle, 0.0f, static_cast<float>(word_730 % 3)};
            spawn_owned_object_via_manager(602 == 600 ? 850 : 602 == 601 ? 853 : 854,
                static_cast<float>(static_cast<float>(facing_104 * 18) + x_ec),
                static_cast<float>(y_f0 + 120.0),
                static_cast<unsigned char>(facing_104), 1, parameters, 3);
            if (602 == 601) {
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
            if (602 != 602)
                publish_texture_state(6, static_cast<short>(602 == 600 ? 30 : 60));
        }
        if (sequence_13e == 0 && frame_index_140 == 2 && frame_timer_142 == 0) {
            set_word_48a(40);
            dispatch_indexed_event_member(23);
            const int direction_bits = static_cast<unsigned char>(facing_104);
            emit_fighter_effect(115,
                static_cast<float>(x_ec - static_cast<signed char>(direction_bits) * 2),
                static_cast<float>(y_f0 + 120.0), direction_bits, 1);
            dispatch_indexed_sequence_window_45c8b0(0, 602 == 601 ? 5 : 2, 60);
            advance_secondary_event_effect_cycle();
        }
        return;
    }
        case 604:
        resolve_stage_surface_landing_transition();
        publish_texture_state(6, 2);
        if ((sequence_13e == 1 && frame_counter_144 > (604 == 606 ? 90 : 30))
                || (sequence_13e == 2 && 604 != 605
                    && frame_counter_144 > (604 == 606 ? 70 : 30))) {
            next_sequence_block();
            return;
        }
        if (sequence_13e == 0 && frame_index_140 == 6 && frame_timer_142 == 0) {
            set_word_48a(40);
            dispatch_indexed_event_member(23);
            const int direction_bits = static_cast<unsigned char>(facing_104);
            emit_fighter_effect(115, static_cast<float>(static_cast<float>(static_cast<signed char>(direction_bits) * 7) + x_ec),
                static_cast<float>(y_f0 + 226.0), direction_bits, 1);
            dispatch_indexed_sequence_window_45c8b0(0, 604 == 604 ? 2 : 604 == 605 ? 3 : 4, 60);
            advance_secondary_event_effect_cycle();
        }
        if (advance_frame_and_dispatch())
            set_action(0);
        if (sequence_13e == 0 && frame_timer_142 == 0 && frame_index_140 == 8) {
            const float parameters[1] = {0.0f};
            if (604 == 605) {
                spawn_owned_object_via_manager(855,
                    static_cast<float>(static_cast<float>(facing_104 * 75) + x_ec), y_f0,
                    static_cast<unsigned char>(facing_104), 1, parameters, 1);
                spawn_owned_object_via_manager(855,
                    static_cast<float>(x_ec - static_cast<float>(facing_104 * 75)), y_f0,
                    static_cast<unsigned char>(-facing_104), 1, parameters, 1);
            } else {
                spawn_owned_object_via_manager(604 == 604 ? 851 : 856, x_ec, y_f0,
                    static_cast<unsigned char>(facing_104), 1, parameters, 1);
            }
            dispatch_character_wave_handle(9);
        }
        return;

// Middle high-table families; no separate callable boundary.
        case 605:
        resolve_stage_surface_landing_transition();
        publish_texture_state(6, 2);
        if ((sequence_13e == 1 && frame_counter_144 > (605 == 606 ? 90 : 30))
                || (sequence_13e == 2 && 605 != 605
                    && frame_counter_144 > (605 == 606 ? 70 : 30))) {
            next_sequence_block();
            return;
        }
        if (sequence_13e == 0 && frame_index_140 == 6 && frame_timer_142 == 0) {
            set_word_48a(40);
            dispatch_indexed_event_member(23);
            const int direction_bits = static_cast<unsigned char>(facing_104);
            emit_fighter_effect(115, static_cast<float>(static_cast<float>(static_cast<signed char>(direction_bits) * 7) + x_ec),
                static_cast<float>(y_f0 + 226.0), direction_bits, 1);
            dispatch_indexed_sequence_window_45c8b0(0, 605 == 604 ? 2 : 605 == 605 ? 3 : 4, 60);
            advance_secondary_event_effect_cycle();
        }
        if (advance_frame_and_dispatch())
            set_action(0);
        if (sequence_13e == 0 && frame_timer_142 == 0 && frame_index_140 == 8) {
            const float parameters[1] = {0.0f};
            if (605 == 605) {
                spawn_owned_object_via_manager(855,
                    static_cast<float>(static_cast<float>(facing_104 * 75) + x_ec), y_f0,
                    static_cast<unsigned char>(facing_104), 1, parameters, 1);
                spawn_owned_object_via_manager(855,
                    static_cast<float>(x_ec - static_cast<float>(facing_104 * 75)), y_f0,
                    static_cast<unsigned char>(-facing_104), 1, parameters, 1);
            } else {
                spawn_owned_object_via_manager(605 == 604 ? 851 : 856, x_ec, y_f0,
                    static_cast<unsigned char>(facing_104), 1, parameters, 1);
            }
            dispatch_character_wave_handle(9);
        }
        return;

// Middle high-table families; no separate callable boundary.
        case 606:
        resolve_stage_surface_landing_transition();
        publish_texture_state(6, 2);
        if ((sequence_13e == 1 && frame_counter_144 > (606 == 606 ? 90 : 30))
                || (sequence_13e == 2 && 606 != 605
                    && frame_counter_144 > (606 == 606 ? 70 : 30))) {
            next_sequence_block();
            return;
        }
        if (sequence_13e == 0 && frame_index_140 == 6 && frame_timer_142 == 0) {
            set_word_48a(40);
            dispatch_indexed_event_member(23);
            const int direction_bits = static_cast<unsigned char>(facing_104);
            emit_fighter_effect(115, static_cast<float>(static_cast<float>(static_cast<signed char>(direction_bits) * 7) + x_ec),
                static_cast<float>(y_f0 + 226.0), direction_bits, 1);
            dispatch_indexed_sequence_window_45c8b0(0, 606 == 604 ? 2 : 606 == 605 ? 3 : 4, 60);
            advance_secondary_event_effect_cycle();
        }
        if (advance_frame_and_dispatch())
            set_action(0);
        if (sequence_13e == 0 && frame_timer_142 == 0 && frame_index_140 == 8) {
            const float parameters[1] = {0.0f};
            if (606 == 605) {
                spawn_owned_object_via_manager(855,
                    static_cast<float>(static_cast<float>(facing_104 * 75) + x_ec), y_f0,
                    static_cast<unsigned char>(facing_104), 1, parameters, 1);
                spawn_owned_object_via_manager(855,
                    static_cast<float>(x_ec - static_cast<float>(facing_104 * 75)), y_f0,
                    static_cast<unsigned char>(-facing_104), 1, parameters, 1);
            } else {
                spawn_owned_object_via_manager(606 == 604 ? 851 : 856, x_ec, y_f0,
                    static_cast<unsigned char>(facing_104), 1, parameters, 1);
            }
            dispatch_character_wave_handle(9);
        }
        return;

// Middle high-table families; no separate callable boundary.
        case 608:
        landing_sequence = 3;
        if ((sequence_13e == 0 && frame_index_140 <= 3) || sequence_13e == 3)
            resolve_stage_surface_landing_transition();
        publish_texture_state(6, 2);
        if (sequence_13e == 1 && frame_counter_144 > 20) {
            next_sequence_block();
            return;
        }
        if (sequence_13e < 3) {
            velocity_y_f8 -= acceleration_y_100;
            if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
            reimu_land_sequence_608:
                y_f0 = reimu_stage_surface_height_at_x(this);
                zero_velocity_acceleration();
                set_sequence(landing_sequence);
                return;
            }
        }
        if (advance_frame_and_dispatch()) {
            set_action(0);
            publish_texture_state(6, 60);
        }
        if (sequence_13e == 0 && frame_timer_142 == 0) {
            if (frame_index_140 == 4) {
                dispatch_indexed_sequence_window_45c8b0(0, 1, 60);
                advance_secondary_event_effect_cycle();
                set_word_48a(40);
                dispatch_indexed_event_member(23);
                const int direction_bits = static_cast<unsigned char>(facing_104);
                emit_fighter_effect(115, static_cast<float>(static_cast<float>(static_cast<signed char>(direction_bits) * 24) + x_ec),
                    static_cast<float>(y_f0 + 144.0), direction_bits, 1);
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
        return;
        case 609:
        resolve_stage_surface_landing_transition();
        publish_texture_state(6, 2);
        if ((sequence_13e == 1 && (frame_counter_144 > 40 || word_738 == 1))
                || (sequence_13e == 2 && frame_counter_144 > 24)) {
            next_sequence_block();
            return;
        }
        if (advance_frame_and_dispatch())
            set_action(0);
        if (sequence_13e == 0 && frame_timer_142 == 0 && frame_index_140 == 5) {
            const float parameters[3] = {0.0f, 0.0f, 0.0f};
            spawn_owned_object_via_manager(852,
                static_cast<float>(static_cast<float>(facing_104 * 228) + x_ec),
                static_cast<float>(y_f0 + 93.0),
                static_cast<unsigned char>(facing_104), 1, parameters, 3);
            dispatch_character_wave_handle(12);
        }
        return;
        case 610:
        resolve_stage_surface_landing_transition();
        publish_texture_state(6, 2);
        if (sequence_13e == 1 && frame_counter_144 > 60) {
            next_sequence_block();
            return;
        }
        if (advance_frame_and_dispatch()) {
            set_action(0);
            publish_texture_state(6, 120);
        }
        if (sequence_13e == 0 && frame_timer_142 == 0 && frame_index_140 == 7) {
            spawn_owned_object_via_manager(859,
                static_cast<float>(static_cast<float>(facing_104 * 280) + x_ec),
                static_cast<float>(y_f0 + 93.0),
                static_cast<unsigned char>(facing_104), 1, 0, 0);
            dispatch_character_wave_handle(13);
        }
        return;
        case 612: {
        if (sequence_13e == 0) {
            if (frame_timer_142 == 0 && frame_index_140 == 1) {
                field_108 = 0.0f;
                field_10c = 50.0f;
                scale_11c = 1.0f;
                scale_120 = 1.0f;
                byte_113 = 255;
                byte_112 = 255;
                byte_111 = 255;
                byte_110 = 255;
                dispatch_character_wave_handle(2);
            }
            if (frame_index_140 > 0) {
                if (scale_11c > 0.0f) {
                    scale_11c = static_cast<float>(scale_11c - static_cast<double>(0.1f));
                    scale_120 = static_cast<float>(scale_120 + static_cast<double>(0.2f));
                }
                byte_113 = byte_113 > 25 ? static_cast<unsigned char>(byte_113 - 25) : 0;
            }
        }
        if (sequence_13e == 2) {
            if (frame_index_140 == 0) {
                if (scale_11c < 1.0f) {
                    scale_11c = static_cast<float>(scale_11c + static_cast<double>(0.1f));
                    scale_120 = static_cast<float>(scale_120 - static_cast<double>(0.2f));
                    byte_113 = static_cast<unsigned char>(byte_113 + 25);
                } else {
                    scale_11c = 1.0f;
                    scale_120 = 1.0f;
                    byte_113 = 255;
                }
            }
            if (frame_index_140 < 3)
                velocity_y_f8 = static_cast<float>(velocity_y_f8 - static_cast<double>(0.7f));
        }
        if (sequence_13e == 3) {
            if (state_180 != 0 && static_cast<signed char>(byte_184) > 0)
                state_180 = 0;
            const double next_y = static_cast<double>(velocity_y_f8) + y_f0;
            if (reimu_stage_surface_height_at_x(this) >= next_y && velocity_y_f8 < 0.0f) {
                y_f0 = reimu_stage_surface_height_at_x(this);
                zero_velocity_acceleration();
                next_sequence_block();
                return;
            }
        }
        if (advance_frame_and_dispatch())
            set_action(0);
        if (sequence_13e == 0 && frame_timer_142 == 0 && frame_index_140 == 3) {
            dispatch_indexed_sequence_window_45c8b0(0, 2, 60);
            advance_secondary_event_effect_cycle();
            set_word_48a(40);
            dispatch_indexed_event_member(23);
        }
        if (frame_counter_144 == 0 && frame_timer_142 == 0 && frame_index_140 == 0 && sequence_13e == 2) {
            x_ec = static_cast<float>(peer_170->x_ec - facing_104 * 180);
            y_f0 = 150.0f;
            velocity_x_f4 = 6.0f;
            velocity_y_f8 = 8.0f;
            dispatch_character_wave_handle(6);
        }
        if (sequence_13e == 2 && frame_index_140 == 3 && frame_timer_142 == 0) {
            velocity_x_f4 = 7.5f;
            velocity_y_f8 = -24.0f;
        }
        return;
    }
        case 614:
        if (sequence_13e == 0 || sequence_13e == 3 || sequence_13e == 4 || sequence_13e == 7)
            resolve_stage_surface_landing_transition();
        publish_texture_state(6, 2);
        velocity_y_f8 -= acceleration_y_100;
        if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
            if (sequence_13e < 3) {
                zero_velocity_acceleration();
                y_f0 = reimu_stage_surface_height_at_x(this);
                set_sequence(3);
                return;
            }
            if (sequence_13e > 3 && sequence_13e < 7) {
                zero_velocity_acceleration();
                y_f0 = reimu_stage_surface_height_at_x(this);
                set_sequence(7);
                return;
            }
        }
        if (advance_frame_and_dispatch())
            set_action(0);
        if (sequence_13e == 0 && frame_timer_142 == 0) {
            if (frame_index_140 == 1) {
                dispatch_indexed_sequence_window_45c8b0(0, 3, 60);
                advance_secondary_event_effect_cycle();
                set_word_48a(40);
                dispatch_indexed_event_member(23);
                emit_fighter_effect(115, static_cast<float>(static_cast<float>(facing_104 * 24) + x_ec),
                    static_cast<float>(y_f0 + 144.0), static_cast<unsigned char>(facing_104), 1);
            }
            if (frame_timer_142 == 0 && frame_index_140 == 3) {
                const float parameters[3] = {0.0f, 12.0f, 0.0f};
                spawn_owned_object_via_manager(825, x_ec, y_f0,
                    static_cast<unsigned char>(facing_104), 1, parameters, 3);
                dispatch_character_wave_handle(7);
            }
        }
        if (frame_counter_144 == 0 && frame_timer_142 == 0 && frame_index_140 == 0 && sequence_13e == 1) {
            state_180 = 0;
            byte_184 = 1;
            velocity_x_f4 = 6.0f;
            velocity_y_f8 = 10.0f;
            acceleration_y_100 = 1.25f;
        }
        if (frame_counter_144 == 0 && frame_timer_142 == 0 && frame_index_140 == 0
                && sequence_13e == 4 && word_730 < 2) {
            word_730 = static_cast<short>(word_730 + 1);
            set_sequence(0);
            frame_timer_142 = 0;
            frame_index_140 = 3;
            const float parameters[3] = {0.0f, 12.0f, 0.0f};
            spawn_owned_object_via_manager(825, x_ec, y_f0,
                static_cast<unsigned char>(facing_104), 1, parameters, 3);
            dispatch_character_wave_handle(7);
        }
        if (sequence_13e == 4 && frame_timer_142 == 0 && frame_index_140 == 2) {
            const float parameters[3] = {0.0f, 12.0f, 0.0f};
            spawn_owned_object_via_manager(825, x_ec, y_f0,
                static_cast<unsigned char>(facing_104), 1, parameters, 3);
            dispatch_character_wave_handle(7);
        }
        if (frame_counter_144 == 0 && frame_timer_142 == 0 && frame_index_140 == 0 && sequence_13e == 5) {
            state_180 = 0;
            byte_184 = 1;
            velocity_x_f4 = 6.0f;
            velocity_y_f8 = 16.0f;
            acceleration_y_100 = 0.5f;
        }
        if (sequence_13e == 5 && frame_timer_142 == 0) {
            if (frame_index_140 == 5) {
                byte_184 = 1;
                state_180 = 0;
                const float parameters[3] = {-75.0f, 12.0f, 1.0f};
                spawn_owned_object_via_manager(825,
                    static_cast<float>(static_cast<float>(facing_104 * 85) + x_ec),
                    static_cast<float>(y_f0 + 117.0),
                    static_cast<unsigned char>(facing_104), 1, parameters, 3);
                dispatch_character_wave_handle(10);
            }
            if (frame_timer_142 == 0 && frame_index_140 == 6) {
                acceleration_y_100 = 0.1f;
                velocity_x_f4 = static_cast<float>(velocity_x_f4 * 0.5);
                velocity_y_f8 = static_cast<float>(velocity_y_f8 * 0.5);
            }
            if (frame_timer_142 == 0 && frame_index_140 == 8)
                acceleration_y_100 = 0.5f;
        }
        return;
        case 616: {
        if (sequence_13e == 8)
            resolve_stage_surface_landing_transition();
        publish_texture_state(6, 2);
        const int sequence_five_frame = 5;
        const int sequence_five_limit = sequence_five_frame + 115;
        // The target indexes this seven-entry table with sequence - 1 and
        // uses an unsigned upper-bound guard; retain that signed-load/unsigned
        // range behavior for zero and negative sequence values.
        switch (static_cast<unsigned int>(static_cast<int>(sequence_13e) - 1)) {
        case 0: case 1: {
            velocity_y_f8 -= acceleration_y_100;
            const double next_y = static_cast<double>(velocity_y_f8) + y_f0;
            if (reimu_stage_surface_height_at_x(this) + 300.0 >= next_y && velocity_y_f8 < 0.0f) {
                zero_velocity_acceleration();
                set_sequence(3);
                y_f0 = static_cast<float>(reimu_stage_surface_height_at_x(this) + 280.0);
                float parameters[3];
                parameters[2] = 2.0f;
                for (float i = 0.0f; i < 8.0f; i += 1.0f) {
                    parameters[0] = static_cast<float>(i * 45.0);
                    parameters[1] = 30.0f;
                    spawn_owned_object_via_manager(866, x_ec, reimu_stage_surface_height_at_x(this),
                        static_cast<unsigned char>(facing_104), 1, parameters, 3);
                }
                return;
            }
            break;
        }
        case 2:
            y_f0 = static_cast<float>(reimu_stage_surface_height_at_x(this) + 280.0 + field_73c);
            field_73c = static_cast<float>(field_73c + 2.0);
            if (field_73c > 20.0f)
                field_73c = 20.0f;
            break;
        case 3: case 4: {
            velocity_x_f4 = static_cast<float>(velocity_x_f4 + static_cast<double>(0.2f));
            if (velocity_x_f4 > 8.0f)
                velocity_x_f4 = 8.0f;
            const double current_y = y_f0;
            if (reimu_stage_surface_height_at_x(this) + 300.0 < current_y) {
                velocity_y_f8 = static_cast<float>(velocity_y_f8 - static_cast<double>(0.2f));
                const double next_y = static_cast<double>(velocity_y_f8) + y_f0;
                if (reimu_stage_surface_height_at_x(this) + 300.0 >= next_y) {
                    y_f0 = static_cast<float>(reimu_stage_surface_height_at_x(this) + 300.0);
                    velocity_y_f8 = 0.0f;
                }
            }
            if (sequence_13e == 5 && frame_counter_144 >= sequence_five_limit) {
                next_sequence_block();
                velocity_y_f8 = 4.5f;
                velocity_x_f4 = -4.0f;
                acceleration_y_100 = 0.5f;
            }
            break;
        }
        case 5: case 6:
            velocity_y_f8 -= acceleration_y_100;
            if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
                zero_velocity_acceleration();
                y_f0 = reimu_stage_surface_height_at_x(this);
                set_sequence(8);
            }
            break;
        default:
            // The target's unsigned range branch falls through to this shared post-switch continuation.
            break;
        }
        if (advance_frame_and_dispatch()) {
            goto reimu_complete_action0_619;
        }
        if (frame_counter_144 == 0 && frame_timer_142 == 0 && frame_index_140 == 0 && sequence_13e == 1) {
            velocity_x_f4 = 0.0f;
            velocity_y_f8 = 25.0f;
            acceleration_y_100 = 0.7f;
            const float parameters[3] = {0.0f, 0.0f, 0.0f};
            spawn_owned_object_via_manager(866, x_ec,
                static_cast<float>(reimu_stage_surface_height_at_x(this) + 150.0),
                static_cast<unsigned char>(facing_104), -1, parameters, 3);
            dispatch_indexed_sequence_window_45c8b0(0, 3, 60);
            advance_secondary_event_effect_cycle();
            set_word_48a(120);
            dispatch_indexed_event_member(23);
            const unsigned int direction_bits = static_cast<unsigned char>(facing_104);
            emit_fighter_effect(115,
                static_cast<float>(static_cast<float>(static_cast<signed char>(direction_bits) * 24) + x_ec),
                static_cast<float>(y_f0 + 144.0), direction_bits, 1);
        }
        if (sequence_13e == 3 && frame_timer_142 == 0 && frame_index_140 == sequence_five_frame)
            set_word_48a(1);
        return;
        }

        case 619:
        resolve_stage_surface_landing_transition();
        publish_texture_state(6, 2);
        if (sequence_13e == 1 && frame_counter_144 >= 20) {
            next_sequence_block();
            return;
        }
        if (advance_frame_and_dispatch()) {
reimu_complete_action0_619:
            set_action(0);
            return;
        }
        if (sequence_13e == 0 && frame_timer_142 == 0) {
            if (frame_index_140 == 3) {
                dispatch_indexed_sequence_window_45c8b0(0, 5, 60);
                advance_secondary_event_effect_cycle();
                set_word_48a(40);
                dispatch_indexed_event_member(23);
                emit_fighter_effect(115, x_ec, static_cast<float>(y_f0 + 120.0),
                    static_cast<unsigned char>(facing_104), 1);
            }
            if (frame_timer_142 == 0 && frame_index_140 == 5) {
                dispatch_character_wave_handle(22);
                for (float i = 0.0f; i < 7.0f; i += 1.0f) {
                    const float parameters[4] = {
                        static_cast<float>(static_cast<double>(51.4f) * i), 0.0f, 0.0f, i};
                    if (lookup_orientation_sine_quantized_abs(parameters[0]) > 0.0f) {
                        spawn_owned_object_via_manager(869, x_ec,
                            static_cast<float>(reimu_stage_surface_height_at_x(this) + 150.0),
                            static_cast<unsigned char>(facing_104), -1, parameters, 4);
                    } else {
                        spawn_owned_object_via_manager(869, x_ec,
                            static_cast<float>(reimu_stage_surface_height_at_x(this) + 150.0),
                            static_cast<unsigned char>(facing_104), 1, parameters, 4);
                    }
                }
                timer_7c8 = 900;
                count_7ca = 0;
                latch_7cc = 0;
            }
        }
        return;

// Late high-table actions; continuation of the same dispatcher.
        case 650: {
        if (sequence_13e == 4)
            resolve_stage_surface_landing_transition();
        publish_texture_state(6, 2);
        if (sequence_13e == 1 && frame_counter_144 > (650 == 650 ? 30 : 60)) {
            next_sequence_block();
            return;
        }
        if (650 == 650 && sequence_13e > 1 && sequence_13e < 4) {
            velocity_y_f8 -= acceleration_y_100;
            if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending()))
                goto reimu_action_650_651_landing_tail;
        }
        if (sequence_13e == 1 && word_730 < (650 == 650 ? 5 : 10)
                && frame_counter_144 % 5 == 0) {
            dispatch_character_wave_handle(8);
            float parameters[3] = {
                650 == 650 ? static_cast<float>((word_730 - 2) * 30)
                    : static_cast<float>(word_730 * -45.0),
                0.0f, static_cast<float>(word_730 % 3)};
            spawn_owned_object_via_manager(650 == 650 ? 850 : 853,
                static_cast<float>(static_cast<float>(facing_104 * 18) + x_ec),
                static_cast<float>(y_f0 + 120.0),
                static_cast<unsigned char>(facing_104), 1, parameters, 3);
            if (650 == 651) {
                parameters[0] = 0.0f;
                parameters[1] = 0.0f;
                spawn_owned_object_via_manager(860,
                    static_cast<float>(static_cast<float>(facing_104 * 18) + x_ec),
                    static_cast<float>(y_f0 + 120.0),
                    static_cast<unsigned char>(facing_104), 1, parameters, 3);
            }
            word_730 = static_cast<short>(word_730 + 1);
        }
        if (650 == 651 && sequence_13e > 1 && sequence_13e < 4) {
            velocity_y_f8 -= acceleration_y_100;
            if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
                y_f0 = reimu_stage_surface_height_at_x(this);
                zero_velocity_acceleration();
                set_sequence(4);
                return;
            }
        }
        if (advance_frame_and_dispatch())
            set_action(0);
        if (sequence_13e == 0 && frame_index_140 == 2 && frame_timer_142 == 0) {
            set_word_48a(40);
            dispatch_indexed_event_member(23);
            const int direction_bits = static_cast<unsigned char>(facing_104);
            emit_fighter_effect(115, static_cast<float>(x_ec - static_cast<signed char>(direction_bits) * 2),
                static_cast<float>(y_f0 + 120.0), direction_bits, 1);
            dispatch_indexed_sequence_window_45c8b0(0, 650 == 650 ? 2 : 5, 60);
            advance_secondary_event_effect_cycle();
        }
        return;
    }
reimu_action_650_651_landing_tail:
    y_f0 = reimu_stage_surface_height_at_x(this);
    zero_velocity_acceleration();
    set_sequence(4);
    return;
        case 651: {
        if (sequence_13e == 4)
            resolve_stage_surface_landing_transition();
        publish_texture_state(6, 2);
        if (sequence_13e == 1 && frame_counter_144 > (651 == 650 ? 30 : 60)) {
            next_sequence_block();
            return;
        }
        if (651 == 650 && sequence_13e > 1 && sequence_13e < 4) {
            velocity_y_f8 -= acceleration_y_100;
            if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
                y_f0 = reimu_stage_surface_height_at_x(this);
                zero_velocity_acceleration();
                set_sequence(4);
                return;
            }
        }
        if (sequence_13e == 1 && word_730 < (651 == 650 ? 5 : 10)
                && frame_counter_144 % 5 == 0) {
            dispatch_character_wave_handle(8);
            float parameters[3] = {
                651 == 650 ? static_cast<float>((word_730 - 2) * 30)
                    : static_cast<float>(word_730 * -45.0),
                0.0f, static_cast<float>(word_730 % 3)};
            spawn_owned_object_via_manager(651 == 650 ? 850 : 853,
                static_cast<float>(static_cast<float>(facing_104 * 18) + x_ec),
                static_cast<float>(y_f0 + 120.0),
                static_cast<unsigned char>(facing_104), 1, parameters, 3);
            if (651 == 651) {
                parameters[0] = 0.0f;
                parameters[1] = 0.0f;
                spawn_owned_object_via_manager(860,
                    static_cast<float>(static_cast<float>(facing_104 * 18) + x_ec),
                    static_cast<float>(y_f0 + 120.0),
                    static_cast<unsigned char>(facing_104), 1, parameters, 3);
            }
            word_730 = static_cast<short>(word_730 + 1);
        }
        if (651 == 651 && sequence_13e > 1 && sequence_13e < 4) {
            velocity_y_f8 -= acceleration_y_100;
            if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending()))
                goto reimu_action_650_651_landing_tail;
        }
        if (advance_frame_and_dispatch())
            set_action(0);
        if (sequence_13e == 0 && frame_index_140 == 2 && frame_timer_142 == 0) {
            set_word_48a(40);
            dispatch_indexed_event_member(23);
            const int direction_bits = static_cast<unsigned char>(facing_104);
            emit_fighter_effect(115, static_cast<float>(x_ec - static_cast<signed char>(direction_bits) * 2),
                static_cast<float>(y_f0 + 120.0), direction_bits, 1);
            dispatch_indexed_sequence_window_45c8b0(0, 651 == 650 ? 2 : 5, 60);
            advance_secondary_event_effect_cycle();
        }
        return;
    }
        case 658:
        landing_sequence = 3;
        if (sequence_13e == 3)
            resolve_stage_surface_landing_transition();
        publish_texture_state(6, 2);
        if (sequence_13e == 1 && frame_counter_144 > 20) {
            next_sequence_block();
            return;
        }
        velocity_y_f8 -= acceleration_y_100;
        if (sequence_13e < 3) {
            if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
            reimu_land_sequence_658:
                y_f0 = reimu_stage_surface_height_at_x(this);
                zero_velocity_acceleration();
                set_sequence(landing_sequence);
                return;
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
                const int direction_bits = static_cast<unsigned char>(facing_104);
                emit_fighter_effect(115, static_cast<float>(static_cast<float>(static_cast<signed char>(direction_bits) * 24) + x_ec),
                    static_cast<float>(y_f0 + 144.0), direction_bits, 1);
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
        return;
        case 669:
        publish_texture_state(6, 2);
        if (sequence_13e == 1) {
            if (frame_counter_144 >= 240) {
                next_sequence_block();
                acceleration_y_100 = 0.2f;
                return;
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
                return;
            }
        }
        if (advance_frame_and_dispatch()) {
            set_action(0);
            return;
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
        return;
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
        return;
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
        return;
        case 710:
        if (sequence_13e == 6)
            resolve_stage_surface_landing_transition();
        if (sequence_13e >= 1 && sequence_13e <= 5) {
            velocity_y_f8 -= acceleration_y_100;
            if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
                y_f0 = reimu_stage_surface_height_at_x(this);
                zero_velocity_acceleration();
                set_sequence(6);
                dispatch_indexed_event_member(30);
                return;
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
            acceleration_y_100 = 710 == 710 ? 0.1f : 0.0f;
            return;
        }
        if (sequence_13e == 4 && frame_timer_142 == 0) {
            if (frame_index_140 == 1) {
                dispatch_character_wave_handle(4);
                const unsigned int mode = static_cast<unsigned int>(g_match_identifier);
                float parameters[3];
                if (710 == 710) {
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
        return;

// Final high-table families; continuation of the same staged dispatcher.
        case 711:
        if (sequence_13e == 6)
            resolve_stage_surface_landing_transition();
        if (sequence_13e >= 1 && sequence_13e <= 5) {
            velocity_y_f8 -= acceleration_y_100;
            if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
                y_f0 = reimu_stage_surface_height_at_x(this);
                zero_velocity_acceleration();
                set_sequence(6);
                dispatch_indexed_event_member(30);
                return;
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
            acceleration_y_100 = 711 == 710 ? 0.1f : 0.0f;
            return;
        }
        if (sequence_13e == 4 && frame_timer_142 == 0) {
            if (frame_index_140 == 1) {
                dispatch_character_wave_handle(4);
                const unsigned int mode = static_cast<unsigned int>(g_match_identifier);
                float parameters[3];
                if (711 == 710) {
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
        return;

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
                return;
            }
        }
        if (sequence_13e == 4 || sequence_13e == 5) {
            velocity_y_f8 -= acceleration_y_100;
            if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
                zero_velocity_acceleration();
                y_f0 = reimu_stage_surface_height_at_x(this);
                set_sequence(6);
                return;
            }
        }
        if (advance_frame_and_dispatch())
            set_action(700);
        if (frame_counter_144 == 0 && frame_timer_142 == 0 && frame_index_140 == 0) {
            if (sequence_13e == 2) {
                x_ec = static_cast<float>(static_cast<float>(static_cast<unsigned int>(selector_random_roll(800))) + 240.0);
                y_f0 = static_cast<float>(static_cast<float>(static_cast<unsigned int>(selector_random_roll(250))) + 100.0);
            }
            if (frame_counter_144 == 0 && frame_timer_142 == 0 && frame_index_140 == 0 && sequence_13e == 3) {
                dispatch_character_wave_handle(13);
                const unsigned int mode = static_cast<unsigned int>(g_match_identifier);
                float parameters[4];
                switch (mode) {
                default:
                    return;
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
        return;
        case 730:
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
            if (730 == 730) {
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
            if (730 == 760)
                word_736 = 0;
            next_sequence_block();
            return;
        }
        if (730 == 730) {
            if (sequence_13e == 5) {
                const unsigned int mode = static_cast<unsigned int>(g_match_identifier);
                if (mode > 3)
                    return;
                float parameters[3];
                switch (mode) {
                case 0:
                    if (frame_counter_144 % 8 == 0) {
                        parameters[0] = field_73c;
                        parameters[1] = 4.0f;
                        parameters[2] = 2.0f;
                        spawn_owned_object_via_manager(902,
                            static_cast<float>(lookup_orientation_cosine_quantized_abs(-parameters[0])
                                * 100.0 * facing_104 + x_ec),
                            static_cast<float>(lookup_orientation_sine_quantized_abs(-parameters[0])
                                * 100.0 + y_f0 + 100.0),
                            static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    }
                    break;
                case 1:
                    if (frame_counter_144 % 6 == 0) {
                        parameters[0] = field_73c;
                        parameters[1] = 4.0f;
                        parameters[2] = 2.0f;
                        spawn_owned_object_via_manager(902,
                            static_cast<float>(lookup_orientation_cosine_quantized_abs(-parameters[0])
                                * 100.0 * facing_104 + x_ec),
                            static_cast<float>(lookup_orientation_sine_quantized_abs(-parameters[0])
                                * 100.0 + y_f0 + 100.0),
                            static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    }
                    break;
                case 2:
                    if (frame_counter_144 % 5 == 0) {
                        parameters[0] = field_73c;
                        parameters[1] = static_cast<float>(4.0
                            - static_cast<float>(static_cast<unsigned int>(selector_random_roll(5))) * static_cast<double>(0.1f));
                        parameters[2] = 2.0f;
                        spawn_owned_object_via_manager(902,
                            static_cast<float>(lookup_orientation_cosine_quantized_abs(-parameters[0])
                                * 100.0 * facing_104 + x_ec),
                            static_cast<float>(lookup_orientation_sine_quantized_abs(-parameters[0])
                                * 100.0 + y_f0 + 100.0),
                            static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    }
                    break;
                case 3:
                    if (frame_counter_144 % 4 == 0) {
                        const double angle = static_cast<double>(field_73c) + 7.0;
                        parameters[0] = static_cast<float>(angle - static_cast<float>(static_cast<unsigned int>(selector_random_roll(14))));
                        parameters[1] = static_cast<float>(4.0
                            - static_cast<float>(static_cast<unsigned int>(selector_random_roll(10))) * static_cast<double>(0.1f));
                        parameters[2] = 2.0f;
                        spawn_owned_object_via_manager(902,
                            static_cast<float>(lookup_orientation_cosine_quantized_abs(-parameters[0])
                                * 100.0 * facing_104 + x_ec),
                            static_cast<float>(lookup_orientation_sine_quantized_abs(-parameters[0])
                                * 100.0 + y_f0 + 100.0),
                            static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    }
                    break;
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
        return;
        case 740: {
        unsigned int mode = static_cast<unsigned int>(g_match_identifier);
        if (sequence_13e == 1) {
            // No default assignment: VC8 reproduces the target's indeterminate
            // fallback spill. Native checks stop before either unknown read.
            int cadence;
            int limit;
            int duration;
            switch (mode) {
            case 3:
                cadence = 5;
                limit = 14;
                duration = 80;
                break;
            case 2:
                cadence = 6;
                limit = 11;
                duration = 80;
                break;
            case 1:
                cadence = 8;
                limit = 8;
                duration = 80;
                break;
            case 0:
                cadence = 10;
                limit = 6;
                duration = 80;
                break;
            }
            if (frame_counter_144 % cadence == 0 && word_730 < limit) {
                dispatch_character_wave_handle(8);
                float parameters[3];
                parameters[0] = static_cast<float>(10.0 - static_cast<float>(static_cast<unsigned int>(selector_random_roll(200))));
                parameters[1] = static_cast<float>(static_cast<float>(static_cast<unsigned int>(selector_random_roll(30))) + 15.0);
                parameters[2] = static_cast<float>(word_730 % 3);
                spawn_owned_object_via_manager(903,
                    static_cast<float>(static_cast<float>(facing_104 * 18) + x_ec),
                    static_cast<float>(y_f0 + 120.0),
                    static_cast<unsigned char>(facing_104), 1, parameters, 3);
                word_730 = static_cast<short>(word_730 + 1);
                mode = static_cast<unsigned int>(g_match_identifier);
            }
            if (frame_counter_144 > duration) {
                next_sequence_block();
                return;
            }
        }
        if (sequence_13e == 6) {
            int cutoff;
            switch (mode) {
            case 3: cutoff = 30; break;
            case 2: cutoff = 50; break;
            case 1: case 0: cutoff = 60; break;
            }
            if (frame_counter_144 >= cutoff) {
                next_sequence_block();
                return;
            }
        }
        if (advance_frame_and_dispatch())
            set_action(700);
        if (frame_counter_144 == 0 && frame_timer_142 == 0 && frame_index_140 == 0 && sequence_13e == 6)
            dispatch_character_wave_handle(2);
        return;
    }
        case 760:
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
            if (760 == 730) {
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
            if (760 == 760)
                word_736 = 0;
            next_sequence_block();
            return;
        }
        if (760 == 730) {
            if (sequence_13e == 5) {
                const unsigned int mode = static_cast<unsigned int>(g_match_identifier);
                if (mode > 3)
                    return;
                float parameters[3];
                switch (mode) {
                case 0:
                    if (frame_counter_144 % 8 == 0) {
                        parameters[0] = field_73c;
                        parameters[1] = 4.0f;
                        parameters[2] = 2.0f;
                        spawn_owned_object_via_manager(902,
                            static_cast<float>(lookup_orientation_cosine_quantized_abs(-parameters[0])
                                * 100.0 * facing_104 + x_ec),
                            static_cast<float>(lookup_orientation_sine_quantized_abs(-parameters[0])
                                * 100.0 + y_f0 + 100.0),
                            static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    }
                    break;
                case 1:
                    if (frame_counter_144 % 6 == 0) {
                        parameters[0] = field_73c;
                        parameters[1] = 4.0f;
                        parameters[2] = 2.0f;
                        spawn_owned_object_via_manager(902,
                            static_cast<float>(lookup_orientation_cosine_quantized_abs(-parameters[0])
                                * 100.0 * facing_104 + x_ec),
                            static_cast<float>(lookup_orientation_sine_quantized_abs(-parameters[0])
                                * 100.0 + y_f0 + 100.0),
                            static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    }
                    break;
                case 2:
                    if (frame_counter_144 % 5 == 0) {
                        parameters[0] = field_73c;
                        parameters[1] = static_cast<float>(4.0
                            - static_cast<float>(static_cast<unsigned int>(selector_random_roll(5))) * static_cast<double>(0.1f));
                        parameters[2] = 2.0f;
                        spawn_owned_object_via_manager(902,
                            static_cast<float>(lookup_orientation_cosine_quantized_abs(-parameters[0])
                                * 100.0 * facing_104 + x_ec),
                            static_cast<float>(lookup_orientation_sine_quantized_abs(-parameters[0])
                                * 100.0 + y_f0 + 100.0),
                            static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    }
                    break;
                case 3:
                    if (frame_counter_144 % 4 == 0) {
                        const double angle = static_cast<double>(field_73c) + 7.0;
                        parameters[0] = static_cast<float>(angle - static_cast<float>(static_cast<unsigned int>(selector_random_roll(14))));
                        parameters[1] = static_cast<float>(4.0
                            - static_cast<float>(static_cast<unsigned int>(selector_random_roll(10))) * static_cast<double>(0.1f));
                        parameters[2] = 2.0f;
                        spawn_owned_object_via_manager(902,
                            static_cast<float>(lookup_orientation_cosine_quantized_abs(-parameters[0])
                                * 100.0 * facing_104 + x_ec),
                            static_cast<float>(lookup_orientation_sine_quantized_abs(-parameters[0])
                                * 100.0 + y_f0 + 100.0),
                            static_cast<unsigned char>(facing_104), 1, parameters, 3);
                    }
                    break;
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
        return;
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
        return;
        case 795:
        if (sequence_13e == 0) {
            if (795 == 795)
                velocity_y_f8 = static_cast<float>(velocity_y_f8 - static_cast<double>(0.3f));
            else
                velocity_y_f8 -= acceleration_y_100;
            if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
                set_sequence(1);
                if (795 != 795) {
                    dispatch_indexed_event_member(30);
                    x_ec = 795 == 797 ? 480.0f : 800.0f;
                }
                y_f0 = reimu_stage_surface_height_at_x(this);
                zero_velocity_acceleration();
                return;
            }
        }
        if (advance_frame_and_dispatch())
            set_action(795 == 797 ? 0 : 700);
        return;

        case 797:
        if (sequence_13e == 0) {
            if (797 == 795)
                velocity_y_f8 = static_cast<float>(velocity_y_f8 - static_cast<double>(0.3f));
            else
                velocity_y_f8 -= acceleration_y_100;
            if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
                set_sequence(1);
                if (797 != 795) {
                    dispatch_indexed_event_member(30);
                    x_ec = 797 == 797 ? 480.0f : 800.0f;
                }
                y_f0 = reimu_stage_surface_height_at_x(this);
                zero_velocity_acceleration();
                return;
            }
        }
        if (advance_frame_and_dispatch())
            set_action(797 == 797 ? 0 : 700);
        return;

        case 798:
        if (sequence_13e == 0) {
            if (798 == 795)
                velocity_y_f8 = static_cast<float>(velocity_y_f8 - static_cast<double>(0.3f));
            else
                velocity_y_f8 -= acceleration_y_100;
            if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
                set_sequence(1);
                if (798 != 795) {
                    dispatch_indexed_event_member(30);
                    x_ec = 798 == 797 ? 480.0f : 800.0f;
                }
                y_f0 = reimu_stage_surface_height_at_x(this);
                zero_velocity_acceleration();
                return;
            }
        }
        if (advance_frame_and_dispatch())
            set_action(798 == 797 ? 0 : 700);
        return;

        default:
        update_common_action_state();
        return;
    }

// Shared landing tail for actions203/225/226. Action202 keeps its own
// inline copy because VC8 otherwise outlines the target's hot fallthrough.
reimu_landed_action_10_other:
    zero_velocity_acceleration();
    y_f0 = reimu_stage_surface_height_at_x(this);
    set_action(10);
    return;

}

} // namespace th105
