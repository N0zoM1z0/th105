#include "ReimuActionStateStaging.hpp"

namespace th105 {

// Remaining low-table actions and the direct300 edge of the original root.
// This source phase is not an original callable or a complete root.
bool ReimuActionStatePreludeView::try_run_checked_late_low_action()
{
    const short selected_action = action_13c;
    switch (selected_action) {
    case 208: case 209: case 210: case 211: case 212:
    case 220: case 221: case 222:
        if (sequence_13e == 0)
            resolve_stage_surface_landing_transition();
        if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
            set_action(10);
            y_f0 = reimu_stage_surface_height_at_x(this);
            zero_velocity_acceleration();
            return true;
        }
        if (is_at_stage_surface() || velocity_y_f8 > 0.0f)
            word_4ae = 2;
        if (sequence_13e > 0) {
            velocity_y_f8 = static_cast<float>(velocity_y_f8 - acceleration_y_100);
            if (velocity_y_f8 < -20.0f)
                velocity_y_f8 = -20.0f;
        }
        if (selected_action != 209 && selected_action != 210 && selected_action != 212
                && sequence_13e == 1 && frame_counter_144 % 5 == 0) {
            const double x_base = static_cast<double>(x_ec) + 50.0;
            const unsigned char direction = static_cast<unsigned char>(facing_104);
            const float effect_y = static_cast<float>(static_cast<float>(mt19937_next_u32() % 200) + y_f0);
            const float effect_x = static_cast<float>(x_base - static_cast<float>(mt19937_next_u32() % 100));
            emit_fighter_effect(123, effect_x, effect_y, direction, 1);
        }
        if (selected_action != 211 && selected_action != 212
                && sequence_13e == 1 && velocity_y_f8 < 4.0f)
            set_sequence(2);
        advance_frame_and_dispatch();
        if (frame_counter_144 == 0 && frame_timer_142 == 0
                && frame_index_140 == 0 && sequence_13e == 1) {
            velocity_x_f4 = selected_action == 208 || selected_action == 220 ? 0.0f
                : selected_action == 209 || selected_action == 221 ? 8.0f
                : selected_action == 210 || selected_action == 222 ? -8.0f
                : selected_action == 211 ? 3.0f : 9.0f;
            velocity_y_f8 = selected_action == 208 || selected_action == 220 ? 20.0f
                : selected_action == 211 || selected_action == 212 ? 15.0f : 17.5f;
            acceleration_y_100 = 0.65f;
            byte_47e = 0;
            emit_fighter_effect(63, x_ec, y_f0, static_cast<unsigned char>(facing_104), 1);
        }
        return true;
    case 214: {
        if (advance_frame_and_dispatch()) {
            set_action(9);
            return true;
        }
        if (frame_counter_144 == 0 && frame_timer_142 == 0 && frame_index_140 == 0) {
            if (sequence_13e == 1)
                dispatch_indexed_event_member(31);
        }
        if (frame_counter_144 == 0 && frame_timer_142 == 0
                && frame_index_140 == 0 && sequence_13e == 6) {
            set_action(9);
            return true;
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
                const float effect_y = static_cast<float>(
                    (lookup_orientation_sine_quantized_abs(field_740) * 100.0 + y_f0) + 100.0);
                const float effect_x = static_cast<float>(
                    lookup_orientation_cosine_quantized_abs(field_740) * 100.0 * facing_104 + x_ec);
                emit_fighter_effect(125, effect_x, effect_y, direction, 1);
            }
            // The target repeats this unchanged gate twice without intervening
            // writes/calls. One ordinary condition preserves its behavior.
            if ((field_6c8 == 0 && word_736 > 10) || word_482 <= 0) {
                reinterpret_cast<ReimuRecoverySpriteView *>(
                    reinterpret_cast<unsigned char *>(this) + 4)->reset_fighter_action_scratch();
                if (sequence_13e == 1 || sequence_13e == 2) {
                    if (facing_104 == 1 ? x_ec > peer_170->x_ec : x_ec < peer_170->x_ec) {
                        facing_104 = static_cast<signed char>(-facing_104);
                        velocity_x_f4 = -velocity_x_f4;
                        set_sequence(6);
                    } else {
                        set_sequence(5);
                    }
                }
                if (sequence_13e == 3 || sequence_13e == 4) {
                    if (facing_104 == 1 ? x_ec > peer_170->x_ec : x_ec < peer_170->x_ec) {
                        facing_104 = static_cast<signed char>(-facing_104);
                        velocity_x_f4 = -velocity_x_f4;
                        set_sequence(5);
                    } else {
                        set_sequence(6);
                    }
                }
                return true;
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
        return true;
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
        return true;
    case 223:
        resolve_stage_surface_landing_transition();
        byte_47e = 1;
        advance_frame_and_dispatch();
        if (sequence_13e == 1) {
            if (frame_counter_144 % 5 == 0) {
                const double x_base = static_cast<double>(x_ec) + 50.0;
                const unsigned char direction = static_cast<unsigned char>(facing_104);
                const float effect_y = static_cast<float>(static_cast<float>(mt19937_next_u32() % 200) + y_f0);
                const float effect_x = static_cast<float>(x_base - static_cast<float>(mt19937_next_u32() % 100));
                emit_fighter_effect(124, effect_x, effect_y, direction, 1);
            }
            word_730 = static_cast<short>(word_730 + 1);
            const int directed_input = static_cast<int>(static_cast<unsigned int>(facing_104)
                * static_cast<unsigned int>(field_6b4));
            if ((directed_input <= 0 && word_730 > 12) || word_730 > 45) {
                set_action(204);
                return true;
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
        return true;
    case 224:
        if (sequence_13e == 0 || sequence_13e == 3)
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
            const float effect_y = static_cast<float>(static_cast<float>(mt19937_next_u32() % 200) + y_f0);
            const float effect_x = static_cast<float>(x_base - static_cast<float>(mt19937_next_u32() % 100));
            emit_fighter_effect(124, effect_x, effect_y, direction, 1);
        }
        if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending()) && sequence_13e < 3) {
            velocity_y_f8 = 0.0f;
            y_f0 = reimu_stage_surface_height_at_x(this);
            set_sequence(3);
            return true;
        }
        if (advance_frame_and_dispatch()) {
            set_action(0);
            velocity_x_f4 = 0.0f;
            return true;
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
        return true;
    case 225:
    case 226:
        if (selected_action == 226 || sequence_13e >= 1)
            velocity_y_f8 = static_cast<float>(velocity_y_f8 - acceleration_y_100);
        if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
            zero_velocity_acceleration();
            y_f0 = reimu_stage_surface_height_at_x(this);
            set_action(10);
            return true;
        }
        if (sequence_13e == 2 && frame_counter_144 % 5 == 0) {
            const double x_base = static_cast<double>(x_ec) + 50.0;
            const unsigned char direction = static_cast<unsigned char>(
                selected_action == 226 ? facing_104 : -facing_104);
            const float effect_y = static_cast<float>(static_cast<float>(mt19937_next_u32() % 200) + y_f0);
            const float effect_x = static_cast<float>(x_base - static_cast<float>(mt19937_next_u32() % 100));
            emit_fighter_effect(124, effect_x, effect_y, direction, 1);
        }
        if (advance_frame_and_dispatch())
            set_action(9);
        if (frame_counter_144 == 0 && frame_timer_142 == 0
                && frame_index_140 == 0 && sequence_13e == 1) {
            if (selected_action == 226)
                word_730 = 0;
            velocity_x_f4 = selected_action == 226 ? 10.0f : -10.0f;
            velocity_y_f8 = 4.0f;
            acceleration_y_100 = 0.45f;
            const float effect_y = static_cast<float>(y_f0 + (selected_action == 226 ? 110.0 : 120.0));
            const float effect_x = selected_action == 226 ? static_cast<float>(facing_104 * 80 + x_ec) : x_ec;
            const unsigned char direction = static_cast<unsigned char>(
                selected_action == 226 ? facing_104 : -facing_104);
            emit_fighter_effect(125, effect_x, effect_y, direction, 1);
            emit_fighter_effect(126, x_ec,
                static_cast<float>(y_f0 + (selected_action == 226 ? 110.0 : 120.0)),
                static_cast<unsigned char>(selected_action == 226 ? facing_104 : -facing_104), 1);
            dispatch_indexed_event_member(31);
        }
        if (selected_action == 226 && frame_counter_144 == 0 && frame_timer_142 == 0
                && frame_index_140 == 0 && sequence_13e == 3)
            face_opponent_and_flip_horizontal_velocity();
        return true;
    case 300:
        resolve_stage_surface_landing_transition();
        if (try_dispatch_directional_action_208_210(0))
            return true;
        if (byte_47e) {
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
    default:
        return false;
    }
}

} // namespace th105
