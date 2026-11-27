#include "characters/UdongeActionState.hpp"
// Canonical JP1.06a 0x005BFD50 Udonge Fighter +0x28 action-state root.
// See docs/UDONGE_ACTION_STATE_2026_10_28.md.

namespace th105 {

void UdongeActionStateView::dispatch_action_state_vslot28() {
    word_7a0 = 0;
    word_7a2 = 95;
    if (word_7ae > 0 && !word_48c) --word_7ae;
    if (word_7ac > 0) {
        ++word_4ac;
        if (!word_48c) --word_7ac;
        if (field_7a8 >= 0.5f) {
            field_7a8 = static_cast<float>(field_7a8 - static_cast<double>(0.05f));
            if (field_7a8 <= 0.5f) field_7a8 = 0.5f;
        }
    } else {
        if (field_7a8 < 1.0f) {
            field_7a8 = static_cast<float>(field_7a8 + static_cast<double>(0.05f));
            if (field_7a8 > 1.0f) field_7a8 = 1.0f;
        }
    }
    if (action_id_13c > 149 && action_id_13c < 159 && !byte_751) {
        byte_751 = 1;
        float p[3];
        p[0] = 0.0f;
        p[2] = 0.0f;
        if (action_id_13c > 149 && action_id_13c < 154) {
            p[1] = 0.0f; spawn_offset(998, 20, 130.0, p, 3);
            p[1] = 1.0f; spawn_offset(998, 60, 130.0, p, 3);
        }
        if (action_id_13c > 153 && action_id_13c < 158) {
            p[1] = 0.0f; spawn_offset(998, 30, 80.0, p, 3);
            p[1] = 1.0f; spawn_offset(998, 70, 80.0, p, 3);
        }
        if (action_id_13c == 158) {
            p[1] = 0.0f; spawn_offset(998, 30, 150.0, p, 3);
            p[1] = 1.0f; spawn_offset(998, 70, 150.0, p, 3);
        }
    }
    if (field_7b4 != 0.0f) {
        if (field_7b4 > 4.0f) field_7b4 = 4.0f;
        field_4bc = static_cast<float>((field_7b4 * static_cast<double>(0.05f) + static_cast<double>(1.05f)) * field_4bc);
        field_4c0 = static_cast<float>((static_cast<double>(0.975f) - field_7b4 * static_cast<double>(0.025f)) * field_4c0);
        if (field_7b8 % 30 == 0) {
            float p[3] = {0.0f, 0.0f, 4.0f};
            spawn_offset(859, 0, 100.0, p, 3);
        }
        if (field_7b4 > 1.0f && field_7b8 % 45 == 0) {
            float p[3] = {0.0f, 0.0f, 5.0f};
            spawn(859,
                  static_cast<float>(static_cast<float>(udonge_random(200)) + x_ec - 100.0),
                  static_cast<float>(static_cast<float>(udonge_random(100)) + y_f0 - 50.0),
                  facing_104, 1, p, 3);
        }
        if (field_7b4 > 2.0f && field_7b8 % 40 == 0) {
            float p[3] = {0.0f, 0.0f, 5.0f};
            spawn(859,
                  static_cast<float>(static_cast<float>(udonge_random(200)) + x_ec - 100.0),
                  static_cast<float>(static_cast<float>(udonge_random(100)) + y_f0 - 50.0),
                  facing_104, 1, p, 3);
        }
        ++field_7b8;
    } else {
        field_7b8 = 0;
    }
    if (word_174 > 0) {
        float scale = field_7a8;
        float alpha = scale * word_7a6;
        byte_113 = static_cast<unsigned char>(alpha);
        if (word_7a6 <= 235) word_7a6 = static_cast<short>(word_7a6 + 20);
        else word_7a6 = 255;
    }
    if (word_186 || fighter_170->word_48c) return;

    switch (action_id_13c) {
    case 0:
        landing();
        if (velocity_x_f4 == 0.0f) byte_47e = 0;
        idle_motion();
        break;
    case 1:
        landing();
        idle_motion();
        if (advance() && !frame_index_140) set_action_and_finalize(2);
        return;
    case 2:
        landing();
        idle_motion();
        break;
    case 3:
        landing();
        idle_motion();
        if (advance() && !frame_index_140) set_action_and_finalize(0);
        return;
    case 4:
        landing();
        velocity_x_f4 = 4.0f;
        break;
    case 5:
        landing();
        velocity_x_f4 = -4.0f;
        break;
    case 6:
        if (!sequence_index_13e) landing();
        if (!sequence_index_13e && !byte_47e) zero_motion();
        if (sequence_index_13e > 0) {
            velocity_y_f8 -= acceleration_y_100;
            if (static_cast<unsigned char>(crossed())) {
                set_action_and_finalize(10);
                y_f0 = udonge_surface(this);
                zero_motion();
                return;
            }
        }
        advance();
        if (entry(1)) { velocity_x_f4 = 0.0f; velocity_y_f8 = 15.0f; acceleration_y_100 = 0.6f; byte_47e = 0; }
        return;
    case 7:
        if (!sequence_index_13e) landing();
        if (!sequence_index_13e && !byte_47e) zero_motion();
        if (sequence_index_13e > 0) {
            velocity_y_f8 -= acceleration_y_100;
            if (static_cast<unsigned char>(crossed())) {
                set_action_and_finalize(10);
                y_f0 = udonge_surface(this);
                zero_motion();
                return;
            }
        }
        advance();
        if (entry(1)) { velocity_x_f4 = 5.0f; velocity_y_f8 = 15.0f; acceleration_y_100 = 0.6f; byte_47e = 0; }
        return;
    case 8:
        if (!sequence_index_13e) landing();
        if (!sequence_index_13e && !byte_47e) zero_motion();
        if (sequence_index_13e > 0) {
            velocity_y_f8 -= acceleration_y_100;
            if (static_cast<unsigned char>(crossed())) {
                set_action_and_finalize(10);
                y_f0 = udonge_surface(this);
                zero_motion();
                return;
            }
        }
        advance();
        if (entry(1)) { velocity_x_f4 = -5.0f; velocity_y_f8 = 15.0f; acceleration_y_100 = 0.6f; byte_47e = 0; }
        return;
    case 9:
    case 11:
        if (acceleration_y_100 == 0.0f) acceleration_y_100 = 0.6f;
        velocity_y_f8 -= acceleration_y_100;
        if (static_cast<unsigned char>(crossed())) {
            set_action_and_finalize(10);
            y_f0 = udonge_surface(this);
            zero_motion();
            return;
        }
        break;
    case 10:
        landing();
        zero_motion();
        if (advance()) {
            if (!field_6b8) { set_action_and_finalize(0); return; }
            set_action_and_finalize(2);
        }
        return;
    case 197:
        if ((!sequence_index_13e && frame_index_140 <= 2) || sequence_index_13e == 3) landing();
        if (sequence_index_13e < 3) {
            velocity_y_f8 -= acceleration_y_100;
            if (static_cast<unsigned char>(crossed())) {
                y_f0 = udonge_surface(this);
                zero_motion();
                select_sequence(3);
                return;
            }
        }
        if (advance()) {
            if (byte_72c == 2) { set_action_and_finalize(700); word_4a8 = 3; word_4ac = 3; return; }
            set_action_and_finalize(0);
            if (field_6b8 > 0) set_action_and_finalize(1);
        }
        if (sequence_index_13e == 3 && frame_index_140 == 2 && !frame_timer_142) face_without_velocity();
        if (entry(1)) { velocity_y_f8 = 4.5f; velocity_x_f4 = 12.5f; acceleration_y_100 = 0.35f; }
        return;
    case 198:
        if ((!sequence_index_13e && frame_index_140 <= 2) || sequence_index_13e == 3) landing();
        if (sequence_index_13e < 3) {
            velocity_y_f8 -= acceleration_y_100;
            if (static_cast<unsigned char>(crossed())) {
                y_f0 = udonge_surface(this);
                zero_motion();
                select_sequence(3);
                return;
            }
        }
        if (advance()) {
            if (byte_72c == 2) { set_action_and_finalize(700); word_4a8 = 3; word_4ac = 3; return; }
            set_action_and_finalize(0);
            if (field_6b8 > 0) set_action_and_finalize(1);
        }
        if (sequence_index_13e == 3 && frame_index_140 == 2 && !frame_timer_142) face_without_velocity();
        if (entry(1)) { velocity_y_f8 = 4.5f; velocity_x_f4 = -12.5f; acceleration_y_100 = 0.35f; }
        return;
    case 199:
        landing();
        if (advance()) {
            if (byte_72c == 2) { set_action_and_finalize(700); word_4a8 = 3; word_4ac = 3; return; }
            set_action_and_finalize(0);
            if (field_6b8 > 0) set_action_and_finalize(1);
        }
        if (!sequence_index_13e && frame_index_140 == 11 && !frame_timer_142) face_without_velocity();
        return;
    case 200:
        landing(); byte_47e = 1; advance();
        if (sequence_index_13e == 1) {
            if (time_counter_144 % 5 == 0) dash_dust(false);
            if (field_6b8 < 0) {
                if (field_6b4 * facing_104 > 0) { set_action_and_finalize(212); return; }
                set_action_and_finalize(211); return;
            }
            ++word_730;
            if ((field_6b4 * facing_104 <= 0 && word_730 > 5) || word_730 > 45) {
                set_action_and_finalize(204); return;
            }
        }
        if (entry(1)) { velocity_x_f4 = 9.0f; dash_effects(false, 80.0, true); }
        return;
    case 201:
        if ((!sequence_index_13e && frame_index_140 <= 1) || sequence_index_13e == 3) landing();
        if (sequence_index_13e == 2) {
            velocity_x_f4 = static_cast<float>(velocity_x_f4 + 2.0);
            if (velocity_x_f4 > 0.0f) velocity_x_f4 = 0.0f;
        }
        if (!udonge_on_surface(this) && time_counter_144 % 5 == 0) dash_dust(true);
        if (sequence_index_13e < 3) {
            velocity_y_f8 -= acceleration_y_100;
            if (static_cast<unsigned char>(crossed())) {
                velocity_y_f8 = 0.0f; acceleration_y_100 = 0.0f; y_f0 = udonge_surface(this); select_sequence(3); return;
            }
        }
        if (advance()) { set_action_and_finalize(0); velocity_x_f4 = 0.0f; return; }
        if (!sequence_index_13e && frame_index_140 == 2 && !frame_timer_142) {
            velocity_x_f4 = -12.0f; velocity_y_f8 = 4.0f; acceleration_y_100 = 0.5f; dash_effects(true, 80.0, false);
        }
        return;
    case 202:
        velocity_y_f8 -= acceleration_y_100;
        if (static_cast<unsigned char>(crossed())) { zero_motion(); y_f0 = udonge_surface(this); set_action_and_finalize(10); return; }
        if ((sequence_index_13e == 1 || sequence_index_13e == 2) && time_counter_144 % 5 == 0) dash_dust(false);
        advance();
        if (!sequence_index_13e && !frame_timer_142 && frame_index_140 == 3) {
            word_730 = 0; velocity_x_f4 = 9.0f; velocity_y_f8 = 4.0f; acceleration_y_100 = 0.5f; dash_effects(false, 110.0, true);
        }
        if (entry(2)) flip();
        return;
    case 203:
        velocity_y_f8 -= acceleration_y_100;
        if (static_cast<unsigned char>(crossed())) { zero_motion(); y_f0 = udonge_surface(this); set_action_and_finalize(10); return; }
        if (sequence_index_13e < 3 && time_counter_144 % 5 == 0) dash_dust(true);
        advance();
        if (entry(1)) { velocity_x_f4 = -9.0f; velocity_y_f8 = 4.0f; acceleration_y_100 = 0.5f; dash_effects(true, 120.0, false); }
        if (entry(2)) flip();
        return;
    case 204:
        landing();
        velocity_x_f4 = static_cast<float>(velocity_x_f4 - 0.5);
        if (velocity_x_f4 < 0.0f) { velocity_x_f4 = 0.0f; byte_47e = 0; }
        if (advance()) { set_action_and_finalize(0); byte_47e = 0; }
        return;
    case 208:
        if (!sequence_index_13e) landing();
        if (static_cast<unsigned char>(crossed())) { set_action_and_finalize(10); y_f0 = udonge_surface(this); zero_motion(); return; }
        if (udonge_on_surface(this) || velocity_y_f8 > 0.0f) word_4ae = 2;
        if (sequence_index_13e > 0) { velocity_y_f8 -= acceleration_y_100; if (velocity_y_f8 < -20.0f) velocity_y_f8 = -20.0f; }
        if (sequence_index_13e == 1 && velocity_y_f8 < 4.0f) select_sequence(2);
        advance();
        if (entry(1)) { velocity_x_f4 = 0.0f; velocity_y_f8 = 20.0f; acceleration_y_100 = 0.75f; byte_47e = 0; effect(63, x_ec, y_f0, facing_104, 1); }
        return;
    case 211:
        if (!sequence_index_13e) landing();
        if (static_cast<unsigned char>(crossed())) { set_action_and_finalize(10); y_f0 = udonge_surface(this); zero_motion(); return; }
        if (udonge_on_surface(this) || velocity_y_f8 > 0.0f) word_4ae = 2;
        if (sequence_index_13e > 0) { velocity_y_f8 -= acceleration_y_100; if (velocity_y_f8 < -20.0f) velocity_y_f8 = -20.0f; }
        if (sequence_index_13e == 1 && velocity_y_f8 < 4.0f) select_sequence(2);
        advance();
        if (entry(1)) { velocity_x_f4 = 2.0f; velocity_y_f8 = 20.0f; acceleration_y_100 = 0.75f; byte_47e = 0; effect(63, x_ec, y_f0, facing_104, 1); }
        return;
    case 212:
        if (!sequence_index_13e) landing();
        if (static_cast<unsigned char>(crossed())) { set_action_and_finalize(10); y_f0 = udonge_surface(this); zero_motion(); return; }
        if (udonge_on_surface(this) || velocity_y_f8 > 0.0f) word_4ae = 2;
        if (sequence_index_13e > 0) { velocity_y_f8 -= acceleration_y_100; if (velocity_y_f8 < -20.0f) velocity_y_f8 = -20.0f; }
        if (sequence_index_13e == 1 && velocity_y_f8 < 4.0f) select_sequence(2);
        advance();
        if (entry(1)) { velocity_x_f4 = 8.5f; velocity_y_f8 = 15.5f; acceleration_y_100 = 0.65f; byte_47e = 0; effect(63, x_ec, y_f0, facing_104, 1); }
        return;
    case 214: {
        if (advance()) { flip(); set_action_and_finalize(9); return; }
        if (entry(6)) { flip(); set_action_and_finalize(9); return; }
        if (entry(1)) event(31);
        if (field_6b8 > 0) { if (field_6b4 * facing_104 > 0) word_732 = -45; else if (field_6b4 * facing_104 < 0) word_732 = -135; else word_732 = -90; }
        else if (field_6b8 < 0) { if (field_6b4 * facing_104 > 0) word_732 = 45; else if (field_6b4 * facing_104 < 0) word_732 = 135; else word_732 = 90; }
        else { if (field_6b4 * facing_104 > 0) word_732 = 0; else if (field_6b4 * facing_104 < 0) word_732 = 180; }
        if (sequence_index_13e == 5 || sequence_index_13e == 6) velocity_y_f8 -= acceleration_y_100;
        if (sequence_index_13e > 0 && sequence_index_13e < 5) {
            ++word_736;
            word_734 = static_cast<short>(word_732 - static_cast<short>(static_cast<int>(field_740)));
            if (word_734 > 180) word_734 = static_cast<short>(word_734 - 360);
            if (word_734 < -180) word_734 = static_cast<short>(word_734 + 360);
            if (word_734 > 0) {
                if (!field_4b8) field_740 = static_cast<float>(field_740 + 1.5);
                else field_740 = static_cast<float>(field_740 + 0.5);
            }
            if (word_734 < 0) {
                if (!field_4b8) field_740 = static_cast<float>(field_740 - 1.5);
                else field_740 = static_cast<float>(field_740 - 0.5);
            }
            velocity_x_f4 = static_cast<float>(udonge_cosine(field_740) * field_73c);
            velocity_y_f8 = static_cast<float>(udonge_sine(field_740) * field_73c);
            if (y_f0 > 680.0f && velocity_y_f8 > 0.0f) velocity_y_f8 = 0.0f;
            field_73c = static_cast<float>(field_73c + static_cast<double>(0.3f));
            if (field_73c > 12.0f) field_73c = 12.0f;
            if (!field_4b8) counter(5, 1);
            else counter(10, 1);
            field_12c = -field_740;
            if (velocity_x_f4 < 0.0f) field_12c = static_cast<float>(180.0 - field_740);
            if (velocity_x_f4 < 0.0f && sequence_index_13e == 1) select_sequence(3);
            if (velocity_x_f4 >= 0.0f && sequence_index_13e == 3) select_sequence(1);
            if (velocity_x_f4 < 0.0f && sequence_index_13e == 2) select_sequence(4);
            if (velocity_x_f4 >= 0.0f && sequence_index_13e == 4) select_sequence(2);
            if (time_counter_144 % 5 == 1) {
                effect(
                    125,
                    static_cast<float>(udonge_cosine(field_740) * 100.0 * static_cast<signed char>(facing_104) + x_ec),
                    static_cast<float>(udonge_sine(field_740) * 100.0 + y_f0 + 100.0),
                    facing_104,
                    1);
            }
            if ((!field_6c8 && word_736 > 10) || word_482 <= 0) {
                reset_action_scratch();
                if (sequence_index_13e == 1 || sequence_index_13e == 2) {
                    if (facing_104 == 1) {
                        if (x_ec > fighter_170->x_ec) { facing_104 = -1; velocity_x_f4 = -velocity_x_f4; select_sequence(6); }
                        else select_sequence(5);
                    } else {
                        if (x_ec < fighter_170->x_ec) { facing_104 = static_cast<signed char>(-facing_104); velocity_x_f4 = -velocity_x_f4; select_sequence(6); }
                        else select_sequence(5);
                    }
                }
                if (sequence_index_13e == 3 || sequence_index_13e == 4) {
                    if (facing_104 == 1) {
                        if (x_ec > fighter_170->x_ec) { facing_104 = -1; velocity_x_f4 = -velocity_x_f4; select_sequence(5); return; }
                        select_sequence(6); return;
                    }
                    if (x_ec < fighter_170->x_ec) { facing_104 = static_cast<signed char>(-facing_104); velocity_x_f4 = -velocity_x_f4; select_sequence(5); return; }
                    select_sequence(6); return;
                }
                return;
            }
        }
        if (static_cast<unsigned char>(crossed())) {
            y_f0 = udonge_surface(this); velocity_y_f8 = 0.0f; acceleration_y_100 = 0.0f;
            if (sequence_index_13e < 5) { reset_action_scratch(); set_action_and_finalize(215); return; }
            set_action_and_finalize(10); zero_motion(); return;
        }
        return;
    }
    case 215:
        landing();
        if (velocity_x_f4 > 0.0f) { velocity_x_f4 = static_cast<float>(velocity_x_f4 - 0.75); if (velocity_x_f4 < 0.0f) velocity_x_f4 = 0.0f; }
        if (velocity_x_f4 < 0.0f) { velocity_x_f4 = static_cast<float>(velocity_x_f4 + 0.75); if (velocity_x_f4 > 0.0f) velocity_x_f4 = 0.0f; }
        if (advance()) set_action_and_finalize(0);
        return;
    case 220:
        if (!sequence_index_13e) landing();
        if (static_cast<unsigned char>(crossed())) { set_action_and_finalize(10); y_f0 = udonge_surface(this); zero_motion(); return; }
        if (udonge_on_surface(this) || velocity_y_f8 > 0.0f) word_4ae = 2;
        if (sequence_index_13e > 0) { velocity_y_f8 -= acceleration_y_100; if (velocity_y_f8 < -20.0f) velocity_y_f8 = -20.0f; }
        if (sequence_index_13e == 1 && velocity_y_f8 < 4.0f) select_sequence(2);
        advance();
        if (entry(1)) { velocity_x_f4 = 0.0f; velocity_y_f8 = 20.0f; acceleration_y_100 = 0.75f; byte_47e = 0; effect(63, x_ec, y_f0, facing_104, 1); }
        return;
    case 209:
    case 221:
        if (!sequence_index_13e) landing();
        if (static_cast<unsigned char>(crossed())) { set_action_and_finalize(10); y_f0 = udonge_surface(this); zero_motion(); return; }
        if (udonge_on_surface(this) || velocity_y_f8 > 0.0f) word_4ae = 2;
        if (sequence_index_13e > 0) { velocity_y_f8 -= acceleration_y_100; if (velocity_y_f8 < -20.0f) velocity_y_f8 = -20.0f; }
        if (sequence_index_13e == 1 && velocity_y_f8 < 4.0f) select_sequence(2);
        advance();
        if (entry(1)) { velocity_x_f4 = 8.0f; velocity_y_f8 = 17.5f; acceleration_y_100 = 0.75f; byte_47e = 0; effect(63, x_ec, y_f0, facing_104, 1); }
        return;
    case 210:
    case 222:
        if (!sequence_index_13e) landing();
        if (static_cast<unsigned char>(crossed())) { set_action_and_finalize(10); y_f0 = udonge_surface(this); zero_motion(); return; }
        if (udonge_on_surface(this) || velocity_y_f8 > 0.0f) word_4ae = 2;
        if (sequence_index_13e > 0) { velocity_y_f8 -= acceleration_y_100; if (velocity_y_f8 < -20.0f) velocity_y_f8 = -20.0f; }
        if (sequence_index_13e == 1 && velocity_y_f8 < 4.0f) select_sequence(2);
        advance();
        if (entry(1)) { velocity_x_f4 = -8.0f; velocity_y_f8 = 17.5f; acceleration_y_100 = 0.75f; byte_47e = 0; effect(63, x_ec, y_f0, facing_104, 1); }
        return;
    case 223:
        landing(); byte_47e = 1; advance();
        if (sequence_index_13e == 1) {
            if (time_counter_144 % 5 == 0) dash_dust(false);
            ++word_730;
            if ((field_6b4 * facing_104 <= 0 && word_730 > 15) || word_730 > 45) {
                set_action_and_finalize(204); return;
            }
        }
        if (entry(1)) { velocity_x_f4 = 4.5f; dash_effects(false, 80.0, true); }
        return;
    case 224:
        if ((!sequence_index_13e && frame_index_140 <= 1) || sequence_index_13e == 3) landing();
        if (sequence_index_13e == 2) {
            velocity_x_f4 = static_cast<float>(velocity_x_f4 + 2.0);
            if (velocity_x_f4 > 0.0f) velocity_x_f4 = 0.0f;
        }
        if (!udonge_on_surface(this) && time_counter_144 % 5 == 0) dash_dust(true);
        if (sequence_index_13e < 3) {
            velocity_y_f8 -= acceleration_y_100;
            if (static_cast<unsigned char>(crossed())) {
                velocity_y_f8 = 0.0f; y_f0 = udonge_surface(this); select_sequence(3); return;
            }
        }
        if (advance()) { set_action_and_finalize(0); velocity_x_f4 = 0.0f; return; }
        if (!sequence_index_13e && frame_index_140 == 2 && !frame_timer_142) {
            velocity_x_f4 = -12.0f; velocity_y_f8 = 4.0f; acceleration_y_100 = 0.5f; dash_effects(true, 80.0, false);
        }
        return;
    case 225:
        velocity_y_f8 -= acceleration_y_100;
        if (static_cast<unsigned char>(crossed())) { zero_motion(); y_f0 = udonge_surface(this); set_action_and_finalize(10); return; }
        if (sequence_index_13e < 3 && time_counter_144 % 5 == 0) dash_dust(true);
        advance();
        if (entry(1)) { velocity_x_f4 = -9.0f; velocity_y_f8 = 4.0f; acceleration_y_100 = 0.5f; dash_effects(true, 120.0, false); }
        if (entry(2)) flip();
        return;
    case 226:
        velocity_y_f8 -= acceleration_y_100;
        if (static_cast<unsigned char>(crossed())) { zero_motion(); y_f0 = udonge_surface(this); set_action_and_finalize(10); return; }
        if ((sequence_index_13e == 1 || sequence_index_13e == 2) && time_counter_144 % 5 == 0) dash_dust(false);
        advance();
        if (!sequence_index_13e && !frame_timer_142 && frame_index_140 == 3) {
            word_730 = 0; velocity_x_f4 = 9.0f; velocity_y_f8 = 4.0f; acceleration_y_100 = 0.5f; dash_effects(false, 110.0, true);
        }
        if (entry(2)) flip();
        return;
    case 300:
        landing(); if (directional(0)) return;
        if (byte_47e) { velocity_x_f4 = static_cast<float>(velocity_x_f4 - 0.5); if (velocity_x_f4 < 0.0f) { velocity_x_f4 = 0.0f; byte_47e = 0; } }
        if (advance()) set_action_and_finalize(0);
        if (!frame_timer_142 && frame_index_140 == 4) { event(27); byte_47e = 0; }
        return;
    case 301:
        landing(); if (directional(0)) return;
        if (byte_47e || frame_index_140 >= 4) { velocity_x_f4 = static_cast<float>(velocity_x_f4 - 0.5); if (velocity_x_f4 < 0.0f) { velocity_x_f4 = 0.0f; byte_47e = 0; } }
        if (advance()) set_action_and_finalize(0);
        if (!frame_timer_142 && frame_index_140 == 4) { float p[3] = {0.0f, 0.0f, 1.0f}; spawn_offset(849, 0, 0.0, p, 3); }
        if (!frame_timer_142 && frame_index_140 == 5) dispatch_character_wave_handle(0);
        if (!frame_timer_142 && frame_index_140 == 4) { velocity_x_f4 = 7.5f; byte_47e = 0; }
        return;
    case 302:
        landing(); if (directional(1)) return;
        if (!field_6bc) byte_750 = 0;
        if (entry(1)) velocity_x_f4 = 17.5f;
        if (!sequence_index_13e) { if (velocity_x_f4 > 0.0f) velocity_x_f4 = static_cast<float>(velocity_x_f4 - 0.75); if (velocity_x_f4 < 0.0f) velocity_x_f4 = 0.0f; }
        if (advance()) set_action_and_finalize(0);
        if (entry(1)) {
            if (byte_750 == 1) { select_sequence(3); effect(62, static_cast<float>(x_ec - 86 * facing_104), static_cast<float>(y_f0 + 108.0), facing_104, 1); byte_184 = 1; return; }
            event(29); float p[3] = {0.0f, 0.0f, 4.0f}; spawn_offset(848, 0, 0.0, p, 3); word_7a6 = 0; byte_113 = 0; velocity_x_f4 = -250.0f;
        }
        if (entry(3)) set_action_and_finalize(0);
        if (entry(4)) { velocity_x_f4 = 17.5f; event(29); }
        if (sequence_index_13e == 1) {
            velocity_x_f4 = static_cast<float>(velocity_x_f4 - static_cast<double>(0.05f));
            if (word_7a6 <= 250) word_7a6 = static_cast<short>(word_7a6 + 5); else word_7a6 = 255;
            if (time_counter_144 >= 18 || field_180) { word_7a6 = 255; next_sequence_block(); return; }
        }
        if (sequence_index_13e == 2) { velocity_x_f4 = static_cast<float>(velocity_x_f4 - 1.0); if (velocity_x_f4 < 0.0f) velocity_x_f4 = 0.0f; }
        if (sequence_index_13e == 4) { velocity_x_f4 = static_cast<float>(velocity_x_f4 - static_cast<double>(0.1f)); if (time_counter_144 >= 24 || field_180) { next_sequence_block(); return; } }
        if (sequence_index_13e == 5) { velocity_x_f4 = static_cast<float>(velocity_x_f4 - 1.0); if (velocity_x_f4 < 0.0f) velocity_x_f4 = 0.0f; }
        return;
    case 303:
        landing(); if (directional(0)) return;
        if (entry(0)) { if (!byte_47e) zero_motion(); byte_184 = 1; field_180 = 0; }
        if (byte_47e > 0) { velocity_x_f4 = static_cast<float>(velocity_x_f4 - static_cast<double>(0.6f)); if (velocity_x_f4 < 0.0f) { velocity_x_f4 = 0.0f; byte_47e = 0; } }
        if (advance()) set_action_and_finalize(2);
        if (!frame_timer_142 && frame_index_140 == 2) event(27);
        return;
    case 304:
        landing(); if (directional(1)) return;
        if (entry(0)) { byte_47e = 0; byte_184 = 1; field_180 = 0; zero_motion(); byte_750 = 1; }
        if (entry(3)) { velocity_x_f4 = field_73c; byte_184 = 1; }
        if (!field_6bc) byte_750 = 0;
        if ((!sequence_index_13e || sequence_index_13e == 2 || sequence_index_13e == 4) && velocity_x_f4 > 0.0f) {
            velocity_x_f4 = static_cast<float>(velocity_x_f4 - 1.0); if (velocity_x_f4 < 0.0f) velocity_x_f4 = 0.0f;
        }
        if (advance()) set_action_and_finalize(0);
        if (entry(3)) { set_action_and_finalize(0); return; }
        if (!sequence_index_13e && !frame_timer_142 && frame_index_140 == 3) { velocity_x_f4 = 12.5f; event(28); }
        if (sequence_index_13e == 1 && time_counter_144 > 16) {
            if (!byte_750) { next_sequence_block(); return; }
            float p[3] = {0.0f, velocity_x_f4, 10.0f}; spawn_offset(848, 0, 0.0, p, 3);
            word_7a6 = 0; byte_113 = 0; byte_184 = 0; field_180 = 0; field_73c = velocity_x_f4; velocity_x_f4 = -280.0f; select_sequence(3);
            effect(62, static_cast<float>(x_ec - 15 * facing_104), static_cast<float>(y_f0 + 60.0), facing_104, 1);
            return;
        }
        if (sequence_index_13e == 3 && time_counter_144 > 32) { next_sequence_block(); return; }
        return;
    case 305:
        landing(); if (directional(1)) return;
        if (frame_index_140 > 5) { velocity_x_f4 = static_cast<float>(velocity_x_f4 - 0.5); if (velocity_x_f4 < 0.0f) velocity_x_f4 = 0.0f; }
        if (advance()) set_action_and_finalize(0);
        if (!frame_timer_142 && frame_index_140 == 3) { float p[3] = {0.0f, 0.0f, 5.0f}; spawn_offset(849, 0, 0.0, p, 3); }
        if (!frame_timer_142 && frame_index_140 == 5) dispatch_character_wave_handle(1);
        return;
    case 306:
        velocity_y_f8 -= acceleration_y_100;
        if (static_cast<unsigned char>(crossed())) { set_action_and_finalize(10); y_f0 = udonge_surface(this); zero_motion(); return; }
        if (advance()) set_action_and_finalize(11);
        if (!frame_timer_142 && frame_index_140 == 4) event(28);
        return;
    case 307:
        if (!field_6bc) byte_750 = 0;
        velocity_y_f8 -= acceleration_y_100;
        if (static_cast<unsigned char>(crossed())) { set_action_and_finalize(10); y_f0 = udonge_surface(this); zero_motion(); return; }
        if (advance()) set_action_and_finalize(9);
        if (entry(1)) set_action_and_finalize(9);
        if (!sequence_index_13e && !frame_timer_142) {
            if (frame_index_140 == 5) { float p[3] = {0.0f, 0.0f, 3.0f}; spawn_offset(849, 0, 0.0, p, 3); }
            if (!frame_timer_142 && frame_index_140 == 6) { dispatch_character_wave_handle(1); velocity_x_f4 = -7.0f; velocity_y_f8 = 6.0f; acceleration_y_100 = 0.5f; }
        }
        if (sequence_index_13e == 1 && !frame_timer_142 && frame_index_140 == 2) { dispatch_character_wave_handle(1); velocity_x_f4 = -7.0f; velocity_y_f8 = 6.0f; acceleration_y_100 = 0.5f; }
        return;
    case 308:
        ++word_730; if (word_730 <= 10) word_7a6 = 0;
        if (!sequence_index_13e) {
            velocity_y_f8 -= acceleration_y_100;
            if (static_cast<unsigned char>(crossed())) { select_sequence(1); y_f0 = udonge_surface(this); zero_motion(); return; }
        }
        if (!field_6bc) byte_750 = 0;
        if (advance()) { set_action_and_finalize(0); return; }
        if (entry(1)) { set_action_and_finalize(9); return; }
        if (!sequence_index_13e && !frame_timer_142 && frame_index_140 == 9) event(28);
        return;
    case 309:
        if (!field_6bc) byte_750 = 0;
        if (sequence_index_13e != 1) velocity_y_f8 -= acceleration_y_100;
        if (static_cast<unsigned char>(crossed())) { set_action_and_finalize(10); y_f0 = udonge_surface(this); zero_motion(); return; }
        if (advance()) set_action_and_finalize(9);
        if (entry(2)) velocity_y_f8 = static_cast<float>(velocity_y_f8 * 0.25);
        if (!sequence_index_13e && !frame_timer_142 && frame_index_140 == 5) {
            dispatch_character_wave_handle(1); velocity_x_f4 = 4.0f; velocity_y_f8 = 15.0f; acceleration_y_100 = 0.5f;
            float p[3] = {0.0f, 0.0f, 7.0f}; spawn_offset(849, 0, 0.0, p, 3);
        }
        return;
    case 310:
        if (entry(0)) { velocity_x_f4 = 0.0f; velocity_y_f8 = 0.0f; acceleration_y_100 = 0.5f; word_730 = 0; byte_184 = 99; field_180 = 0; }
        if (field_180) { ++word_730; if (word_730 > 5) { field_180 = 0; word_730 = 0; } }
        if (sequence_index_13e == 1) {
            if (!time_counter_144) velocity_x_f4 = 15.0f;
            if (time_counter_144 % 8 == 0) event(27);
            if (field_180) { ++word_730; if (word_730 > 5) { field_180 = 0; word_730 = 0; } }
            if (time_counter_144 > 30) { next_sequence_block(); velocity_y_f8 = 6.0f; velocity_x_f4 = static_cast<float>(velocity_x_f4 * 0.5); }
        }
        if (sequence_index_13e == 2) {
            velocity_y_f8 -= acceleration_y_100;
            if (static_cast<unsigned char>(crossed())) { velocity_y_f8 = 0.0f; acceleration_y_100 = 0.0f; y_f0 = udonge_surface(this); set_action_and_finalize(9); return; }
        }
        if (advance()) set_action_and_finalize(9);
        return;
    case 320:
        landing(); if (directional(0)) return;
        if (!frame_timer_142 && !frame_index_140) { byte_47e = 0; byte_184 = 1; field_180 = 0; }
        if (advance()) set_action_and_finalize(0);
        if (!frame_timer_142 && frame_index_140 == 2) { event(27); byte_47e = 0; }
        return;
    case 321:
        landing(); if (directional(0)) return;
        if (!frame_timer_142 && !frame_index_140) { if (!byte_47e) zero_motion(); byte_184 = 1; field_180 = 0; }
        if (frame_index_140 > 4) { velocity_x_f4 = static_cast<float>(velocity_x_f4 - 0.75); if (velocity_x_f4 < 0.0f) velocity_x_f4 = 0.0f; }
        if (advance()) set_action_and_finalize(0);
        if (!frame_timer_142 && frame_index_140 == 3) { float p[3] = {0.0f, 0.0f, 1.0f}; spawn_offset(849, 0, 0.0, p, 3); }
        if (!frame_timer_142 && frame_index_140 == 4) { dispatch_character_wave_handle(0); velocity_x_f4 = 10.0f; byte_47e = 0; }
        if (!frame_timer_142 && frame_index_140 == 6) velocity_x_f4 = 0.0f;
        return;
    case 322:
        landing(); if (directional(1)) return;
        if (!frame_timer_142 && !frame_index_140) { if (!byte_47e) zero_motion(); byte_184 = 1; field_180 = 0; }
        if (frame_index_140 >= 5) { velocity_x_f4 = static_cast<float>(velocity_x_f4 - 0.5); if (velocity_x_f4 < 0.0f) velocity_x_f4 = 0.0f; }
        if (advance()) set_action_and_finalize(0);
        if (!frame_timer_142 && frame_index_140 == 3) { velocity_x_f4 = 15.0f; float p[3] = {0.0f, 0.0f, 5.0f}; spawn_offset(849, 0, 0.0, p, 3); }
        if (!frame_timer_142 && frame_index_140 == 5) { dispatch_character_wave_handle(1); velocity_x_f4 = 5.0f; byte_47e = 0; }
        return;
    case 400:
        landing(); if (!field_6c0) byte_750 = 0; if (advance()) { set_action_and_finalize(0); return; }
        if (entry(1)) { set_action_and_finalize(0); return; }
        if (!sequence_index_13e) {
            if (!frame_timer_142 && frame_index_140 == 3 && byte_750) { next_sequence_block(); effect(62, static_cast<float>(80 * facing_104 + x_ec), static_cast<float>(y_f0 + 108.0), facing_104, 1); return; }
            if (!frame_timer_142 && (frame_index_140 == 3 || frame_index_140 == 6 || frame_index_140 == 9)) {
                if (frame_index_140 == 3) { counter(200, 45); field_180 = 1; }
                aim_to_peer(); if (field_744 < -20.0f) field_744 = -20.0f; if (field_744 > 20.0f) field_744 = 20.0f;
                fan800(76, 106.0, true);
            }
        }
        if (sequence_index_13e == 1 && !frame_timer_142 && (frame_index_140 == 1 || frame_index_140 == 4 || frame_index_140 == 7 || frame_index_140 == 10 || frame_index_140 == 13)) {
            if (frame_index_140 == 1) { counter(200, 45); field_180 = 1; }
            aim_to_peer(); if (field_744 < -20.0f) field_744 = -20.0f; if (field_744 > 20.0f) field_744 = 20.0f;
            fan800(76, 106.0, true);
        }
        return;
    case 401:
        landing(); if (!field_6c0) byte_750 = 0; if (advance()) { set_action_and_finalize(0); return; }
        if (entry(1)) { set_action_and_finalize(0); return; }
        if (!sequence_index_13e) {
            if (!frame_timer_142 && frame_index_140 == 3 && byte_750) { next_sequence_block(); effect(62, static_cast<float>(72 * facing_104 + x_ec), static_cast<float>(y_f0 + 136.0), facing_104, 1); return; }
            if (!frame_timer_142 && (frame_index_140 == 3 || frame_index_140 == 6 || frame_index_140 == 9)) {
                if (frame_index_140 == 3) { counter(200, 45); field_180 = 1; }
                aim_to_peer(); if (field_744 < -60.0) field_744 = -60.0f; if (field_744 > -20.0f) field_744 = -20.0f;
                fan800(73, 138.0, true);
            }
        }
        if (sequence_index_13e == 1 && !frame_timer_142 && (frame_index_140 == 1 || frame_index_140 == 4 || frame_index_140 == 7 || frame_index_140 == 10 || frame_index_140 == 13)) {
            if (frame_index_140 == 1) { counter(200, 45); field_180 = 1; }
            aim_to_peer(); if (field_744 < -60.0) field_744 = -60.0f; if (field_744 > -20.0f) field_744 = -20.0f;
            fan800(73, 138.0, true);
        }
        return;
    case 402:
        landing(); if (!field_6c0) byte_750 = 0; if (advance()) set_action_and_finalize(2);
        if (entry(1)) { set_action_and_finalize(2); return; }
        if (!sequence_index_13e) {
            if (!frame_timer_142 && frame_index_140 == 3 && byte_750) { next_sequence_block(); effect(62, static_cast<float>(70 * facing_104 + x_ec), static_cast<float>(y_f0 + 64.0), facing_104, 1); return; }
            if (!frame_timer_142 && (frame_index_140 == 3 || frame_index_140 == 6 || frame_index_140 == 9)) {
                if (frame_index_140 == 3) { counter(200, 45); field_180 = 1; }
                fan800(70, 64.0, false);
            }
        }
        if (sequence_index_13e == 1 && !frame_timer_142 && (frame_index_140 == 1 || frame_index_140 == 4 || frame_index_140 == 7 || frame_index_140 == 10 || frame_index_140 == 13)) {
            if (frame_index_140 == 1) { counter(200, 45); field_180 = 1; }
            fan800(70, 64.0, false);
        }
        return;
    case 404:
        if (sequence_index_13e == 2) landing(); if (!field_6c0) byte_750 = 0;
        if (sequence_index_13e < 2) { velocity_y_f8 -= acceleration_y_100; if (static_cast<unsigned char>(crossed())) { select_sequence(2); byte_47f = 0; y_f0 = udonge_surface(this); zero_motion(); return; } }
        if (advance()) { set_action_and_finalize(0); return; }
        if (entry(1)) { set_action_and_finalize(9); return; }
        if (entry(2)) { set_action_and_finalize(9); return; }
        if (!sequence_index_13e) {
            if (!frame_timer_142 && frame_index_140 == 3 && byte_750) { next_sequence_block(); effect(62, static_cast<float>(66 * facing_104 + x_ec), static_cast<float>(y_f0 + 129.0), facing_104, 1); return; }
            if (!frame_timer_142 && (frame_index_140 == 3 || frame_index_140 == 6 || frame_index_140 == 9)) {
                if (frame_index_140 == 3) { counter(200, 45); field_180 = 1; }
                aim_to_peer(); if (field_744 < -20.0f) field_744 = -20.0f; if (field_744 > 20.0f) field_744 = 20.0f; fan800(67, 130.0, true);
            }
            if (!frame_timer_142 && frame_index_140 == 12) acceleration_y_100 = 0.6f;
        }
        if (sequence_index_13e == 1) {
            if (!frame_timer_142 && (frame_index_140 == 1 || frame_index_140 == 4 || frame_index_140 == 7 || frame_index_140 == 10 || frame_index_140 == 13)) {
                if (frame_index_140 == 1) { counter(200, 45); field_180 = 1; }
                aim_to_peer(); if (field_744 < -20.0f) field_744 = -20.0f; if (field_744 > 20.0f) field_744 = 20.0f; fan800(67, 130.0, true);
            }
            if (!frame_timer_142 && frame_index_140 == 15) acceleration_y_100 = 0.6f;
        }
        return;
    case 406:
        if (sequence_index_13e == 2) landing(); if (!field_6c0) byte_750 = 0;
        if (sequence_index_13e < 2) { velocity_y_f8 -= acceleration_y_100; if (static_cast<unsigned char>(crossed())) { select_sequence(2); byte_47f = 0; y_f0 = udonge_surface(this); zero_motion(); return; } }
        if (advance()) { set_action_and_finalize(0); return; }
        if (entry(1)) { set_action_and_finalize(9); return; }
        if (entry(2)) { set_action_and_finalize(9); return; }
        if (!sequence_index_13e) {
            if (!frame_timer_142 && frame_index_140 == 4 && byte_750) { next_sequence_block(); effect(62, static_cast<float>(56 * facing_104 + x_ec), static_cast<float>(y_f0 + 100.0), facing_104, 1); return; }
            if (!frame_timer_142 && (frame_index_140 == 4 || frame_index_140 == 7 || frame_index_140 == 10)) {
                if (frame_index_140 == 4) { counter(200, 45); field_180 = 1; }
                aim_to_peer(); if (field_744 < 20.0f) field_744 = 20.0f; if (field_744 > 60.0) field_744 = 60.0f; fan800(56, 100.0, true);
            }
            if (!frame_timer_142 && frame_index_140 == 12) acceleration_y_100 = 0.6f;
        }
        if (sequence_index_13e == 1) {
            if (!frame_timer_142 && (frame_index_140 == 1 || frame_index_140 == 4 || frame_index_140 == 7 || frame_index_140 == 10 || frame_index_140 == 13)) {
                if (frame_index_140 == 1) { counter(200, 45); field_180 = 1; }
                aim_to_peer(); if (field_744 < 20.0f) field_744 = 20.0f; if (field_744 > 60.0) field_744 = 60.0f; fan800(56, 100.0, true);
            }
            if (!frame_timer_142 && frame_index_140 == 15) acceleration_y_100 = 0.6f;
        }
        return;
    case 408:
        landing();
        if (entry(0)) { byte_47e = 0; byte_184 = 1; velocity_x_f4 = 12.0f; field_180 = 0; zero_motion(); byte_750 = 1; }
        if (!field_6bc) byte_750 = 0;
        if (sequence_index_13e == 2 && velocity_x_f4 > 0.0f) { velocity_x_f4 = static_cast<float>(velocity_x_f4 - 1.0); if (velocity_x_f4 < 0.0f) velocity_x_f4 = 0.0f; }
        if (advance()) set_action_and_finalize(0);
        if (!sequence_index_13e && !frame_timer_142 && frame_index_140 == 1) { velocity_x_f4 = 12.0f; float p[3] = {0.0f, 0.0f, 3.0f}; spawn_offset(848, 0, 0.0, p, 3); byte_113 = 0; word_7a6 = 0; }
        if (sequence_index_13e == 1) { if (!time_counter_144) event(29); if (time_counter_144 > 12) { next_sequence_block(); return; } }
        return;
    case 409:
        if (entry(0)) { acceleration_y_100 = 0.35f; byte_47e = 0; word_730 = 0; byte_184 = 1; field_180 = 0; }
        velocity_y_f8 -= acceleration_y_100;
        if (static_cast<unsigned char>(crossed())) { set_action_and_finalize(10); zero_motion(); y_f0 = udonge_surface(this); return; }
        if (advance()) set_action_and_finalize(9);
        return;
    case 410:
        if (entry(0)) { field_180 = 1; zero_motion(); word_730 = 0; word_732 = 0; word_736 = 0; byte_750 = 1; }
        if (!field_6c4) byte_750 = 0;
        if (advance() || entry(1)) { set_action_and_finalize(0); return; }
        if (!sequence_index_13e) {
            if (!frame_timer_142 && frame_index_140 == 3 && byte_750 == 1) { effect(62, static_cast<float>(x_ec - 46 * facing_104), static_cast<float>(y_f0 + 128.0), facing_104, 1); next_sequence_block(); return; }
            if (!frame_timer_142 && frame_index_140 == 4) { counter(200, 60); aim_short(-10, 10); fan801(72, 95.0, false); }
        }
        if (sequence_index_13e == 1 && !frame_timer_142 && frame_index_140 == 2) { counter(200, 60); aim_short(-10, 10); fan801(72, 95.0, true); }
        return;
    case 411:
        if (entry(0)) { field_180 = 1; zero_motion(); word_730 = 0; word_732 = 0; word_736 = 0; byte_750 = 1; }
        if (!field_6c4) byte_750 = 0;
        if (advance() || entry(1)) { set_action_and_finalize(0); return; }
        if (!sequence_index_13e) {
            if (!frame_timer_142 && frame_index_140 == 3 && byte_750 == 1) { effect(62, static_cast<float>(x_ec - 46 * facing_104), static_cast<float>(y_f0 + 128.0), facing_104, 1); next_sequence_block(); return; }
            if (!frame_timer_142 && frame_index_140 == 4) { counter(200, 60); aim_short(-50, -20); fan801(66, 128.0, false); }
        }
        if (sequence_index_13e == 1 && !frame_timer_142 && frame_index_140 == 2) { counter(200, 60); aim_short(-50, -20); fan801(66, 128.0, true); }
        return;
    case 412:
        if (!sequence_index_13e && frame_index_140 == 3 && !frame_timer_142) { dispatch_character_wave_handle(7); field_180 = 1; spawn(802, x_ec, y_f0, facing_104, 1, 0, 0); counter(200, 60); phase_counter(50); }
        if (advance()) set_action_and_finalize(2);
        return;
    case 414:
        if (!field_6c4) byte_750 = 0;
        if (sequence_index_13e < 2) { velocity_y_f8 -= acceleration_y_100; if (static_cast<unsigned char>(crossed())) { select_sequence(2); zero_motion(); y_f0 = udonge_surface(this); return; } }
        if (advance()) { set_action_and_finalize(0); return; }
        if (entry(1)) { set_action_and_finalize(9); return; }
        if (entry(2)) { set_action_and_finalize(9); return; }
        if (!sequence_index_13e) {
            if (!frame_timer_142 && frame_index_140 == 3 && byte_750 == 1) { effect(62, static_cast<float>(x_ec - 47 * facing_104), static_cast<float>(y_f0 + 142.0), facing_104, 1); next_sequence_block(); return; }
            if (!frame_timer_142 && frame_index_140 == 4) { counter(200, 60); aim_short(-10, 10); fan801(62, 127.0, false, true); }
        }
        if (sequence_index_13e == 1 && !frame_timer_142 && frame_index_140 == 2) { counter(200, 60); aim_short(-10, 10); fan801(62, 127.0, true, true); }
        return;
    case 415:
        if (!field_6c4) byte_750 = 0;
        if (sequence_index_13e < 2) { velocity_y_f8 -= acceleration_y_100; if (static_cast<unsigned char>(crossed())) { select_sequence(2); zero_motion(); y_f0 = udonge_surface(this); return; } }
        if (advance()) { set_action_and_finalize(0); return; }
        if (entry(1)) { set_action_and_finalize(9); return; }
        if (entry(2)) { set_action_and_finalize(9); return; }
        if (!sequence_index_13e) {
            if (!frame_timer_142 && frame_index_140 == 3 && byte_750 == 1) { effect(62, static_cast<float>(x_ec - 47 * facing_104), static_cast<float>(y_f0 + 142.0), facing_104, 1); next_sequence_block(); return; }
            if (!frame_timer_142 && frame_index_140 == 4) { counter(200, 60); aim_short(-10, 10); fan801(62, 127.0, false, true); }
        }
        if (sequence_index_13e == 1 && !frame_timer_142 && frame_index_140 == 2) { counter(200, 60); aim_short(-10, 10); fan801(62, 127.0, true, true); }
        return;
    case 416:
        if (!field_6c4) byte_750 = 0;
        if (sequence_index_13e < 2) { velocity_y_f8 -= acceleration_y_100; if (static_cast<unsigned char>(crossed())) { select_sequence(2); zero_motion(); y_f0 = udonge_surface(this); return; } }
        if (advance()) { set_action_and_finalize(0); return; }
        if (entry(1)) { set_action_and_finalize(9); return; }
        if (entry(2)) { set_action_and_finalize(9); return; }
        if (!sequence_index_13e) {
            if (!frame_timer_142 && frame_index_140 == 3 && byte_750 == 1) { next_sequence_block(); effect(62, static_cast<float>(x_ec - 47 * facing_104), static_cast<float>(y_f0 + 142.0), facing_104, 1); return; }
            if (!frame_timer_142 && frame_index_140 == 4) { counter(200, 60); aim_short(20, 50); fan801(64, 105.0, false, true); }
        }
        if (sequence_index_13e == 1 && !frame_timer_142 && frame_index_140 == 2) { counter(200, 60); aim_short(-10, 10); fan801(64, 105.0, true, true); }
        return;
    case 418:
        if ((sequence_index_13e > 0 && sequence_index_13e < 5) || (!sequence_index_13e && frame_index_140 > 0)) {
            velocity_y_f8 -= acceleration_y_100;
            if (static_cast<unsigned char>(crossed())) { y_f0 = udonge_surface(this); zero_motion(); select_sequence(5); return; }
            if (field_180 && sequence_index_13e == 1) { zero_motion(); select_sequence(4); return; }
        }
        if (!sequence_index_13e && !frame_index_140) { velocity_x_f4 = static_cast<float>(velocity_x_f4 - 0.5); if (velocity_x_f4 < 0.0f) velocity_x_f4 = 0.0f; }
        if (sequence_index_13e == 1 && time_counter_144 >= 24) { next_sequence_block(); return; }
        if (sequence_index_13e == 4) { velocity_x_f4 = static_cast<float>(velocity_x_f4 + static_cast<double>(0.2f)); if (velocity_x_f4 > 0.0f) velocity_x_f4 = 0.0f; }
        if (advance()) set_action_and_finalize(0);
        if (entry(5)) { select_sequence(3); return; }
        if (!sequence_index_13e) {
            if (!frame_timer_142) {
                if (frame_index_140 == 1) { velocity_x_f4 = 12.0f; velocity_y_f8 = 6.0f; acceleration_y_100 = 0.35f; float p[3] = {0.0f, velocity_x_f4, 9.0f}; spawn_offset(848, 0, 0.0, p, 3); }
                if (!frame_timer_142 && frame_index_140 == 8) event(29);
            }
            if (frame_index_140 >= 1 && frame_index_140 <= 3) word_7a6 = 0;
        }
        if (sequence_index_13e == 4 && !frame_timer_142 && frame_index_140 == 3) { acceleration_y_100 = 0.5f; velocity_x_f4 = -10.0f; velocity_y_f8 = 7.0f; }
        return;
    case 500:
        landing(); if (!field_6c0) byte_750 = 0;
        if (advance()) set_action_and_finalize(0); if (entry(1)) set_action_and_finalize(0);
        if (!sequence_index_13e && !frame_timer_142 && frame_index_140 == 4) {
            field_180 = 1; counter(200, 120); phase_counter(50); aim_to_peer(); if (field_744 < -10.0f) field_744 = -10.0f; if (field_744 > 10.0f) field_744 = 10.0f;
            float p[3] = {field_744, 1.0f, 0.0f}; spawn_offset(810, 72, 95.0, p, 3);
            p[2] = 5.0f; spawn_offset(810, 72, 95.0, p, 3);
            dispatch_character_wave_handle(5);
        }
        if (sequence_index_13e == 1 && !frame_timer_142 && frame_index_140 == 2) { field_180 = 1; dispatch_character_wave_handle(5); }
        return;
    case 501:
        landing(); if (!field_6c4) byte_750 = 0;
        if (advance()) set_action_and_finalize(0); if (entry(1)) set_action_and_finalize(0);
        if (!sequence_index_13e && !frame_timer_142 && frame_index_140 == 4) {
            field_180 = 1; counter(200, 120); phase_counter(50); aim_to_peer(); if (field_744 < -50.0) field_744 = -50.0f; if (field_744 > -30.0) field_744 = -30.0f;
            float p[3] = {field_744, 1.0f, 0.0f}; spawn_offset(810, 68, 127.0, p, 3);
            p[2] = 5.0f; spawn_offset(810, 68, 127.0, p, 3);
            dispatch_character_wave_handle(5);
        }
        if (sequence_index_13e == 1 && !frame_timer_142 && frame_index_140 == 2) { field_180 = 1; dispatch_character_wave_handle(5); }
        return;
    case 505:
        landing(); if (!field_6c0) byte_750 = 0;
        if (advance()) set_action_and_finalize(0); if (entry(1)) set_action_and_finalize(0);
        if (!sequence_index_13e && !frame_timer_142 && frame_index_140 == 4) {
            field_180 = 1; counter(200, 120); phase_counter(50); aim_to_peer(); if (field_744 < -10.0f) field_744 = -10.0f; if (field_744 > 10.0f) field_744 = 10.0f;
            float p[3] = {field_744, 20.0f, 0.0f}; spawn_offset(811, 72, 95.0, p, 3);
            p[2] = 4.0f; spawn_offset(811, 72, 95.0, p, 3);
            dispatch_character_wave_handle(15);
        }
        if (sequence_index_13e == 1 && !frame_timer_142 && frame_index_140 == 2) { field_180 = 1; dispatch_character_wave_handle(5); }
        return;
    case 506:
        landing(); if (!field_6c4) byte_750 = 0;
        if (advance()) set_action_and_finalize(0); if (entry(1)) set_action_and_finalize(0);
        if (!sequence_index_13e && !frame_timer_142 && frame_index_140 == 4) {
            field_180 = 1; counter(200, 120); phase_counter(50); aim_to_peer(); if (field_744 < -50.0) field_744 = -50.0f; if (field_744 > -30.0) field_744 = -30.0f;
            float p[3] = {field_744, 20.0f, 0.0f}; spawn_offset(811, 68, 127.0, p, 3);
            p[2] = 4.0f;
            dispatch_character_wave_handle(15);
        }
        if (sequence_index_13e == 1 && !frame_timer_142 && frame_index_140 == 2) { field_180 = 1; dispatch_character_wave_handle(5); }
        return;
    case 510:
        landing(); if (!field_6c0) byte_750 = 0;
        if (advance()) set_action_and_finalize(0); if (entry(1)) set_action_and_finalize(0);
        if (!sequence_index_13e && !frame_timer_142 && frame_index_140 == 4) {
            field_180 = 1; counter(200, 120); phase_counter(50);
            float p[3] = {-40.0f, 30.0f, 0.0f}; spawn_offset(812, 68, 127.0, p, 3);
            p[2] = 5.0f; spawn_offset(812, 68, 127.0, p, 3);
            dispatch_character_wave_handle(5);
        }
        if (sequence_index_13e == 1 && !frame_timer_142 && frame_index_140 == 2) { field_180 = 1; dispatch_character_wave_handle(5); }
        return;
    case 511:
        landing(); if (!field_6c4) byte_750 = 0;
        if (advance()) set_action_and_finalize(0); if (entry(1)) set_action_and_finalize(0);
        if (!sequence_index_13e && !frame_timer_142 && frame_index_140 == 4) {
            field_180 = 1; counter(200, 120); phase_counter(50);
            float p[3] = {-30.0f, 50.0f, 0.0f}; spawn_offset(812, 68, 127.0, p, 3);
            p[2] = 5.0f; spawn_offset(812, 68, 127.0, p, 3);
            dispatch_character_wave_handle(5);
        }
        if (sequence_index_13e == 1 && !frame_timer_142 && frame_index_140 == 2) { field_180 = 1; dispatch_character_wave_handle(5); }
        return;
    case 520:
        landing(); if (!field_6c0) byte_750 = 0; if (advance()) set_action_and_finalize(0); if (entry(4)) set_action_and_finalize(0);
        if (!sequence_index_13e && !frame_timer_142 && frame_index_140 == 8) { dispatch_character_wave_handle(7); field_180 = 1; counter(200, 120); phase_counter(50); float p[3] = {0.0f, 0.0f, 0.0f}; spawn_offset(815, 60, 108.0, p, 3); }
        if (sequence_index_13e == 2 && time_counter_144 >= 20) next_sequence_block();
        if (sequence_index_13e == 4 && !frame_timer_142 && frame_index_140 == 6) { dispatch_character_wave_handle(7); field_180 = 1; }
        if (sequence_index_13e == 6 && time_counter_144 >= 20) next_sequence_block();
        return;
    case 521:
        landing(); if (!field_6c4) byte_750 = 0; if (advance()) set_action_and_finalize(0); if (entry(4)) set_action_and_finalize(0);
        if (!sequence_index_13e && !frame_timer_142 && frame_index_140 == 4) { dispatch_character_wave_handle(7); field_180 = 1; counter(200, 120); phase_counter(50); float p[3] = {-25.0f, -0.5f, 0.0f}; spawn_offset(815, 20, 145.0, p, 3); }
        if (sequence_index_13e == 2 && time_counter_144 >= 30) next_sequence_block();
        if (entry(5)) { dispatch_character_wave_handle(7); field_180 = 1; }
        if (sequence_index_13e == 6 && time_counter_144 >= 20) next_sequence_block();
        return;
    case 525:
        landing(); if (!field_6c0) byte_750 = 0; expand_cone();
        if (sequence_index_13e == 1) {
            if (time_counter_144 % 30 == 0) { float p[3] = {0.0f, 1.0f, 4.0f}; spawn_offset(816, 50, 110.0, p, 3); p[1] = -1.0f; p[2] = 4.0f; spawn_offset(816, 50, 110.0, p, 3); }
            if (!byte_750 || time_counter_144 >= 180) { next_sequence_block(); word_730 = 0; return; }
        }
        if (word_730 == 1) { if (word_732 % 60 == 0) dispatch_character_wave_handle(13); ++word_732; }
        if (entry(2)) {
            float p[3] = {static_cast<float>(udonge_random(360)), 0.0f, 3.0f}; spawn_at_peer(816, p); dispatch_character_wave_handle(14);
            if (peer_in_cone()) { p[2] = 1.0f; spawn_at_peer(816, p); }
        }
        if (advance()) set_action_and_finalize(0);
        if (!sequence_index_13e && !frame_timer_142 && frame_index_140 == 8) {
            word_730 = 1; counter(200, 120); phase_counter(50); field_180 = 1;
            float p[3] = {0.0f, 0.0f, 0.0f}; spawn_offset(816, 50, 110.0, p, 3); p[1] = 1.0f; p[2] = 0.0f; spawn_offset(816, 50, 110.0, p, 3);
            field_7b0 = 0.0f; field_73c = 1.2f;
        }
        return;
    case 526:
        landing(); if (!field_6c4) byte_750 = 0; expand_cone();
        if (sequence_index_13e == 1) {
            if (time_counter_144 % 30 == 0) { float p[3] = {0.0f, 1.0f, 4.0f}; spawn_offset(816, 50, 110.0, p, 3); p[1] = -1.0f; p[2] = 4.0f; spawn_offset(816, 50, 110.0, p, 3); }
            if (!byte_750 || time_counter_144 >= 180) { next_sequence_block(); word_730 = 0; return; }
        }
        if (word_730 == 1) { if (word_732 % 60 == 0) dispatch_character_wave_handle(13); ++word_732; }
        if (entry(2)) {
            float p[3] = {static_cast<float>(udonge_random(360)), 0.0f, 3.0f}; spawn_at_peer(816, p); dispatch_character_wave_handle(14);
            if (peer_in_cone()) { p[2] = 1.0f; spawn_at_peer(816, p); }
        }
        if (advance()) set_action_and_finalize(0);
        if (!sequence_index_13e && !frame_timer_142 && frame_index_140 == 8) {
            word_730 = 1; counter(200, 120); phase_counter(50); field_180 = 1;
            float p[3] = {0.0f, 0.0f, 0.0f}; spawn_offset(816, 50, 110.0, p, 3); p[1] = 1.0f; p[2] = 0.0f; spawn_offset(816, 50, 110.0, p, 3);
            field_7b0 = 0.0f; field_73c = 1.2f;
        }
        return;
    case 527:
        if (!field_6c0) byte_750 = 0; expand_cone();
        velocity_y_f8 -= acceleration_y_100;
        if (static_cast<unsigned char>(crossed())) { zero_motion(); y_f0 = udonge_surface(this); set_action_and_finalize(529); return; }
        if (sequence_index_13e == 1) {
            if (time_counter_144 % 30 == 0) { float p[3] = {0.0f, 1.0f, 4.0f}; spawn_offset(816, 50, 140.0, p, 3); p[1] = -1.0f; p[2] = 4.0f; spawn_offset(816, 50, 140.0, p, 3); }
            if (!byte_750 || time_counter_144 >= 180) { next_sequence_block(); word_730 = 0; return; }
        }
        if (word_730 == 1) { if (word_732 % 60 == 0) dispatch_character_wave_handle(13); ++word_732; }
        if (entry(2)) {
            float p[3] = {static_cast<float>(udonge_random(360)), 0.0f, 3.0f}; spawn_at_peer(816, p); dispatch_character_wave_handle(14);
            if (peer_in_cone()) { p[2] = 1.0f; spawn_at_peer(816, p); }
        }
        if (advance()) set_action_and_finalize(9);
        if (entry(3)) acceleration_y_100 = 0.5f;
        if (!sequence_index_13e && !frame_timer_142 && frame_index_140 == 6) {
            word_730 = 1; counter(200, 120); phase_counter(50); field_180 = 1;
            float p[3] = {0.0f, 0.0f, 0.0f}; spawn_offset(816, 50, 140.0, p, 3); p[1] = 1.0f; p[2] = 0.0f; spawn_offset(816, 50, 140.0, p, 3);
            field_7b0 = 0.0f; field_73c = 1.2f;
        }
        return;
    case 528:
        if (!field_6c4) byte_750 = 0; expand_cone();
        velocity_y_f8 -= acceleration_y_100;
        if (static_cast<unsigned char>(crossed())) { zero_motion(); y_f0 = udonge_surface(this); set_action_and_finalize(529); return; }
        if (sequence_index_13e == 1) {
            if (time_counter_144 % 30 == 0) { float p[3] = {0.0f, 1.0f, 4.0f}; spawn_offset(816, 50, 140.0, p, 3); p[1] = -1.0f; p[2] = 4.0f; spawn_offset(816, 50, 140.0, p, 3); }
            if (!byte_750 || time_counter_144 >= 180) { next_sequence_block(); word_730 = 0; return; }
        }
        if (word_730 == 1) { if (word_732 % 60 == 0) dispatch_character_wave_handle(13); ++word_732; }
        if (entry(2)) {
            float p[3] = {static_cast<float>(udonge_random(360)), 0.0f, 3.0f}; spawn_at_peer(816, p); dispatch_character_wave_handle(14);
            if (peer_in_cone()) { p[2] = 1.0f; spawn_at_peer(816, p); }
        }
        if (advance()) set_action_and_finalize(9);
        if (entry(3)) acceleration_y_100 = 0.5f;
        if (!sequence_index_13e && !frame_timer_142 && frame_index_140 == 6) {
            word_730 = 1; counter(200, 120); phase_counter(50); field_180 = 1;
            float p[3] = {0.0f, 0.0f, 0.0f}; spawn_offset(816, 50, 140.0, p, 3); p[1] = 1.0f; p[2] = 0.0f; spawn_offset(816, 50, 140.0, p, 3);
            field_7b0 = 0.0f; field_73c = 1.2f;
        }
        return;
    case 529:
        landing(); if (advance()) set_action_and_finalize(0);
        return;
    case 530:
        landing(); if (!field_6c0) byte_750 = 0; if (advance()) set_action_and_finalize(0); if (entry(1)) { set_action_and_finalize(0); return; }
        if (!sequence_index_13e && !frame_timer_142) {
            if (frame_index_140 == 4 && byte_750 == 1) { next_sequence_block(); effect(62, static_cast<float>(x_ec - 45 * facing_104), static_cast<float>(y_f0 + 132.0), facing_104, 1); }
            if (!frame_timer_142 && frame_index_140 == 6) { float p[3] = {0.0f, 10.0f, 0.0f}; spawn_offset(817, 60, 100.0, p, 3); field_180 = 1; counter(200, 120); phase_counter(50); dispatch_character_wave_handle(12); }
        }
        if (sequence_index_13e == 1 && !frame_timer_142 && frame_index_140 == 3) { float p[3] = {0.0f, 10.0f, 1.0f}; spawn_offset(817, 60, 100.0, p, 3); field_180 = 1; counter(200, 120); phase_counter(50); dispatch_character_wave_handle(12); }
        return;
    case 531:
        landing(); if (!field_6c4) byte_750 = 0; if (advance()) set_action_and_finalize(0); if (entry(1)) { set_action_and_finalize(0); return; }
        if (!sequence_index_13e && !frame_timer_142) {
            if (frame_index_140 == 3 && byte_750 == 1) { next_sequence_block(); effect(62, static_cast<float>(32 * facing_104 + x_ec), static_cast<float>(y_f0 + 57.0), facing_104, 1); }
            if (!frame_timer_142 && frame_index_140 == 5) { float p[3] = {-30.0f, 10.0f, 0.0f}; spawn_offset(817, 25, 145.0, p, 3); field_180 = 1; counter(200, 120); phase_counter(50); dispatch_character_wave_handle(12); }
        }
        if (sequence_index_13e == 1 && !frame_timer_142 && frame_index_140 == 2) { float p[3] = {-30.0f, 10.0f, 1.0f}; spawn_offset(817, 25, 145.0, p, 3); field_180 = 1; counter(200, 120); phase_counter(50); dispatch_character_wave_handle(12); }
        return;
    case 540:
        landing(); if (!field_6c0) byte_750 = 0; if (advance()) set_action_and_finalize(0); if (entry(4)) set_action_and_finalize(0);
        if (entry(1)) { dispatch_character_wave_handle(8); field_180 = 1; counter(200, 120); phase_counter(50); float p[3] = {2.5f, static_cast<float>(byte_606 * 45.0 + 120.0), 0.0f}; spawn_offset(820, -8, 120.0, p, 3); }
        if (sequence_index_13e == 2 && time_counter_144 >= 12) next_sequence_block();
        if (entry(5)) { dispatch_character_wave_handle(8); field_180 = 1; }
        if (sequence_index_13e == 6 && time_counter_144 >= 20) next_sequence_block();
        return;
    case 541:
        landing(); if (!field_6c0) byte_750 = 0; if (advance()) set_action_and_finalize(0); if (entry(4)) set_action_and_finalize(0);
        if (entry(1)) { dispatch_character_wave_handle(8); field_180 = 1; counter(200, 120); phase_counter(50); float p[3] = {1.5f, static_cast<float>(byte_606 * 20.0 + 60.0), 0.0f}; spawn(820, fighter_170->x_ec, static_cast<float>(fighter_170->y_f0 + 120.0), facing_104, 1, p, 3); }
        if (sequence_index_13e == 2 && time_counter_144 >= 12) next_sequence_block();
        if (entry(5)) { dispatch_character_wave_handle(8); field_180 = 1; }
        if (sequence_index_13e == 6 && time_counter_144 >= 20) next_sequence_block();
        return;
    case 545:
        landing(); if (!field_6c0) byte_750 = 0; if (advance()) set_action_and_finalize(0); if (entry(4)) set_action_and_finalize(0);
        if (entry(1)) { dispatch_character_wave_handle(17); field_180 = 1; counter(200, 120); phase_counter(50); float p[3] = {static_cast<float>(byte_60a * static_cast<double>(0.3f) + static_cast<double>(2.2f)), 180.0f, 0.0f}; spawn_offset(821, -8, 120.0, p, 3); }
        if (sequence_index_13e == 2 && time_counter_144 >= 12) next_sequence_block();
        if (entry(5)) { dispatch_character_wave_handle(8); field_180 = 1; }
        if (sequence_index_13e == 6 && time_counter_144 >= 20) next_sequence_block();
        return;
    case 546:
        landing(); if (!field_6c4) byte_750 = 0; if (advance()) set_action_and_finalize(0); if (entry(4)) set_action_and_finalize(0);
        if (entry(1)) { dispatch_character_wave_handle(8); field_180 = 1; counter(200, 120); phase_counter(50); float p[3] = {static_cast<float>(byte_60a * 0.25 + 1.5), 90.0f, 0.0f}; spawn(821, fighter_170->x_ec, static_cast<float>(fighter_170->y_f0 + 120.0), facing_104, 1, p, 3); }
        if (sequence_index_13e == 2 && time_counter_144 >= 12) next_sequence_block();
        if (entry(5)) { dispatch_character_wave_handle(8); field_180 = 1; }
        if (sequence_index_13e == 6 && time_counter_144 >= 20) next_sequence_block();
        return;
    case 550:
        landing(); if (!field_6c0) byte_750 = 0; if (word_736 && !sequence_index_13e) word_4ae = 2;
        if (advance()) set_action_and_finalize(0);
        if (!time_counter_144 && !frame_timer_142 && !frame_index_140) {
            if (sequence_index_13e != 1) return;
            dispatch_character_wave_handle(18); field_180 = 1; counter(200, 120); phase_counter(50); float p[3] = {0.0f, 0.0f, 0.0f}; spawn_offset(822, 0, 120.0, p, 3);
        }
        if (sequence_index_13e == 1 && time_counter_144 >= 25) next_sequence_block();
        return;
    case 551:
        landing(); if (!field_6c0) byte_750 = 0; if (word_736 && !sequence_index_13e) word_4ae = 2;
        if (advance()) set_action_and_finalize(0);
        if (!time_counter_144 && !frame_timer_142 && !frame_index_140) {
            if (sequence_index_13e != 1) return;
            dispatch_character_wave_handle(18); field_180 = 1; counter(200, 120); phase_counter(50); float p[3] = {0.0f, 0.0f, 0.0f}; spawn_offset(822, 0, 120.0, p, 3);
        }
        if (sequence_index_13e == 1 && time_counter_144 >= 25) next_sequence_block();
        return;
    case 560:
        if (!field_6c0) byte_750 = 0; if (!sequence_index_13e) landing();
        velocity_y_f8 -= acceleration_y_100;
        if (static_cast<unsigned char>(crossed())) { zero_motion(); y_f0 = udonge_surface(this); set_action_and_finalize(10); return; }
        if (sequence_index_13e == 1 || sequence_index_13e == 2) { if (byte_113 <= 245) byte_113 += 10; else byte_113 = 255; }
        if (advance()) set_action_and_finalize(0);
        if (entry(1)) { byte_113 = 0; dispatch_character_wave_handle(9); field_180 = 1; velocity_x_f4 = -4.0f; velocity_y_f8 = 12.5f; acceleration_y_100 = 0.45f; counter(200, 120); phase_counter(50); float p[3] = {0.0f, 0.0f, 0.0f}; spawn_offset(825, 0, 0.0, p, 3); }
        return;
    case 561:
        landing(); if (!field_6c0) byte_750 = 0;
        if (sequence_index_13e == 1 || sequence_index_13e == 2) { if (byte_113 <= 245) byte_113 += 10; else byte_113 = 255; }
        if (advance()) set_action_and_finalize(0);
        if (entry(1)) { dispatch_character_wave_handle(9); field_180 = 1; byte_113 = 0; counter(200, 120); phase_counter(50); float p[3] = {0.0f, 0.0f, 2.0f}; spawn_offset(825, 0, 0.0, p, 3); }
        return;
    case 565:
        if (!field_6c0) byte_750 = 0;
        if (sequence_index_13e == 2) landing();
        if (sequence_index_13e == 1) {
            if (!word_730) { field_73c = field_740 + field_73c; if (field_73c >= 200.0) { field_73c = 200.0f; word_730 = 1; } }
            if (word_730 >= 1 && word_730 < 20) { field_73c += field_740; field_740 = static_cast<float>(field_740 - 8.0); if (field_740 < 1.0) { field_740 = 1.0f; ++word_730; } }
            if (word_730 >= 20) { field_73c = static_cast<float>(field_73c - 40.0); if (field_73c < 0.0f) { field_73c = 0.0f; next_sequence_block(); return; } }
        }
        if (advance()) set_action_and_finalize(0);
        if (entry(1)) begin_beams826(false);
        return;
    case 566:
        if (!field_6c0) byte_750 = 0;
        if (sequence_index_13e == 2) landing();
        if (sequence_index_13e == 1) {
            if (!word_730) { field_73c = field_740 + field_73c; if (field_73c >= 200.0) { field_73c = 200.0f; word_730 = 1; } }
            if (word_730 >= 1 && word_730 < 20) { field_73c += field_740; field_740 = static_cast<float>(field_740 - 8.0); if (field_740 < 1.0) { field_740 = 1.0f; ++word_730; } }
            if (word_730 >= 20) { field_73c = static_cast<float>(field_73c - 40.0); if (field_73c < 0.0f) { field_73c = 0.0f; next_sequence_block(); return; } }
        }
        if (advance()) set_action_and_finalize(0);
        if (entry(1)) begin_beams826(true);
        return;
    case 567:
        if (!field_6c0) byte_750 = 0;
        if (sequence_index_13e == 4) landing();
        velocity_y_f8 -= acceleration_y_100;
        if (sequence_index_13e < 4 && static_cast<unsigned char>(crossed())) { zero_motion(); y_f0 = udonge_surface(this); select_sequence(4); return; }
        if (sequence_index_13e == 1) {
            if (!word_730) { field_73c = field_740 + field_73c; if (field_73c >= 200.0) { field_73c = 200.0f; word_730 = 1; } }
            if (word_730 >= 1 && word_730 < 20) { field_73c += field_740; field_740 = static_cast<float>(field_740 - 8.0); if (field_740 < 1.0) { field_740 = 1.0f; ++word_730; } }
            if (word_730 >= 20) { field_73c = static_cast<float>(field_73c - 40.0); if (field_73c < 0.0f) { field_73c = 0.0f; next_sequence_block(); return; } }
        }
        if (advance()) set_action_and_finalize(0);
        if (entry(1)) begin_beams826(false);
        if (entry(4)) { set_action_and_finalize(9); return; }
        if (sequence_index_13e == 2 && !frame_timer_142 && frame_index_140 == 6) acceleration_y_100 = 0.5f;
        return;
    case 568:
        if (!field_6c0) byte_750 = 0;
        if (sequence_index_13e == 4) landing();
        velocity_y_f8 -= acceleration_y_100;
        if (sequence_index_13e < 4 && static_cast<unsigned char>(crossed())) { zero_motion(); y_f0 = udonge_surface(this); select_sequence(4); return; }
        if (sequence_index_13e == 1) {
            if (!word_730) { field_73c = field_740 + field_73c; if (field_73c >= 200.0) { field_73c = 200.0f; word_730 = 1; } }
            if (word_730 >= 1 && word_730 < 20) { field_73c += field_740; field_740 = static_cast<float>(field_740 - 8.0); if (field_740 < 1.0) { field_740 = 1.0f; ++word_730; } }
            if (word_730 >= 20) { field_73c = static_cast<float>(field_73c - 40.0); if (field_73c < 0.0f) { field_73c = 0.0f; next_sequence_block(); return; } }
        }
        if (advance()) set_action_and_finalize(0);
        if (entry(1)) begin_beams826(true);
        if (entry(4)) { set_action_and_finalize(9); return; }
        if (sequence_index_13e == 2 && !frame_timer_142 && frame_index_140 == 6) acceleration_y_100 = 0.5f;
        return;
    case 600:
        landing(); texture(0, 2); if (advance()) set_action_and_finalize(0);
        if (!frame_timer_142) {
            if (frame_index_140 == 3) spell_flash(-45, 143.0, 1);
            if (!frame_timer_142 && frame_index_140 == 6) { float p[3] = {0.0f, 10.0f, 0.0f}; spawn_offset(850, 60, 100.0, p, 3); dispatch_character_wave_handle(12); }
        }
        return;
    case 602:
        texture(0, 2); if (sequence_index_13e == 1 && time_counter_144 >= 30) { next_sequence_block(); return; }
        if (advance()) set_action_and_finalize(0);
        if (entry(1)) {
            { float n = 0.0f; float p[4]; do { p[0] = static_cast<float>(n * 60.0); p[1] = 25.0f; p[2] = 0.0f; p[3] = 5.0f; orbit852(p); n = static_cast<float>(n + 1.0); } while (n < 6.0f); }
            { float n = 0.0f; float p[4]; do { p[0] = static_cast<float>(n * 60.0 + 30.0); p[1] = 25.0f; p[2] = 0.0f; p[3] = 20.0f; orbit852(p); n = static_cast<float>(n + 1.0); } while (n < 6.0f); }
            { float n = 0.0f; float p[4]; do { p[0] = static_cast<float>(60.0 + n * 60.0); p[1] = 25.0f; p[2] = 0.0f; p[3] = 35.0f; orbit852(p); n = static_cast<float>(n + 1.0); } while (n < 6.0f); }
        }
        if (!sequence_index_13e && frame_index_140 == 7 && !frame_timer_142) spell_flash(0, 100.0, 3);
        return;
    case 603:
        landing(); texture(0, 2);
        if (sequence_index_13e == 1) {
            if (time_counter_144 % 10 == 0 && word_730 < 10) { float p[3] = {0.0f, 25.0f, 0.0f}; spawn_offset(853, 60, 100.0, p, 3); dispatch_character_wave_handle(12); ++word_730; }
            if (time_counter_144 >= 120) { next_sequence_block(); return; }
        }
        if (advance()) set_action_and_finalize(0);
        if (entry(1)) time_counter_144 = 0;
        if (!sequence_index_13e && !frame_timer_142 && frame_index_140 == 3) spell_flash(-45, 143.0, 3);
        return;
    case 605:
        if (sequence_index_13e > 0 || (!sequence_index_13e && frame_index_140 >= 7)) texture(0, 2);
        if (sequence_index_13e == 1) {
            if (time_counter_144 >= 120) { next_sequence_block(); return; }
            if (time_counter_144 % 5 == 0) {
                if (!time_counter_144) dispatch_character_wave_handle(50);
                if (word_730 <= 15) {
                    float p[3] = {0.0f, 0.0f, 0.0f};
                    if (word_730 == 15) { dispatch_character_wave_handle(51); p[2] = 1.0f; }
                    spawn_offset(855, 0, 130.0, p, 3); ++word_730;
                }
            }
        }
        if (advance()) set_action_and_finalize(0);
        if (!sequence_index_13e && frame_index_140 == 7 && !frame_timer_142) spell_flash(0, 100.0, 5);
        return;
    case 606:
        landing(); texture(0, 2); if (advance()) set_action_and_finalize(0);
        if (!frame_timer_142) {
            if (frame_index_140 == 3) spell_flash(-45, 143.0, 1);
            if (!frame_timer_142 && frame_index_140 == 5) {
                float p[3] = {0.0f, 10.0f, 0.0f}; spawn_offset(856, 150, 110.0, p, 3);
                int angle = 0;
                do {
                    p[0] = static_cast<float>(static_cast<float>(udonge_random(30)) + (static_cast<float>(angle) + 30.0));
                    p[1] = 10.0f; p[2] = 8.0f;
                    if (p[0] >= 0.0f && p[0] <= 180.0f) spawn_offset(856, 150, 0.0, p, 3, 1);
                    else spawn_offset(856, 150, 0.0, p, 3, -1);
                    angle += 60;
                } while (angle < 360);
                dispatch_character_wave_handle(55);
            }
        }
        return;
    case 607:
        landing(); texture(0, 2); if (advance()) set_action_and_finalize(0);
        if (!frame_timer_142) {
            if (frame_index_140 == 2) spell_flash(-47, 122.0, 3);
            if (!frame_timer_142 && frame_index_140 == 4) {
                float p[3] = {0.0f, 5.0f, 9.0f}; spawn_offset(857, 70, 96.0, p, 3);
                p[2] = 1.0f; spawn_offset(857, 70, 96.0, p, 3);
                int angle = 0;
                do {
                    p[0] = static_cast<float>(static_cast<float>(udonge_random(30)) + (static_cast<float>(angle) + 30.0));
                    p[1] = 10.0f; p[2] = 8.0f;
                    if (p[0] >= 0.0f && p[0] <= 180.0f) spawn_offset(856, 96, 0.0, p, 3, 1);
                    else spawn_offset(856, 96, 0.0, p, 3, -1);
                    angle += 60;
                } while (angle < 360);
                dispatch_character_wave_handle(5);
            }
        }
        return;
    case 608:
        landing(); if (sequence_index_13e > 0 || (!sequence_index_13e && frame_index_140 >= 7)) texture(0, 2);
        if (advance()) set_action_and_finalize(0);
        if (!frame_timer_142) {
            if (frame_index_140 == 3) spell_flash(35, 160.0, 2);
            if (!frame_timer_142 && frame_index_140 == 6) { float p[3] = {80.0f, 40.0f, 0.0f}; spawn_offset(858, 50, 50.0, p, 3); }
        }
        return;
    case 609:
        if (sequence_index_13e <= 2) landing();
        else {
            velocity_y_f8 -= acceleration_y_100;
            if (static_cast<unsigned char>(crossed())) {
                word_730 = static_cast<short>(static_cast<short>(static_cast<int>(velocity_x_f4)) * 100);
                word_732 = static_cast<short>(static_cast<short>(static_cast<int>(velocity_y_f8)) * 100);
                zero_motion(); y_f0 = 0.0f; set_action_and_finalize(97); layout(5.0f); event(22); return;
            }
        }
        if (sequence_index_13e > 0 || (!sequence_index_13e && frame_index_140 >= 7)) texture(0, 2);
        if (sequence_index_13e == 1 && time_counter_144 >= 45) {
            if (word_730 == 1) {
                field_7b4 = 0.0f; layout(10.0f); float p[3] = {0.0f, 0.0f, 6.0f}; spawn_offset(859, 0, 100.0, p, 3);
                select_sequence(3); dispatch_character_wave_handle(56); velocity_x_f4 = -30.0f; velocity_y_f8 = 15.0f; acceleration_y_100 = 0.5f; return;
            }
            next_sequence_block(); return;
        }
        if (advance()) set_action_and_finalize(0);
        if (!sequence_index_13e && !frame_timer_142 && frame_index_140 == 3) spell_flash(35, 160.0, 3);
        if (!time_counter_144) {
            if (!frame_timer_142 && !frame_index_140 && sequence_index_13e == 1) {
                if (field_7b4 <= 2.0f) field_7b4 = static_cast<float>(field_7b4 + 1.0);
                else word_730 = 1;
                dispatch_character_wave_handle(54); float p[3] = {0.0f, 0.0f, 0.0f}; spawn_offset(859, 0, 100.0, p, 3);
            }
            if (entry(3)) { set_action_and_finalize(0); return; }
        }
        return;
    case 650:
        texture(0, 2); velocity_y_f8 -= acceleration_y_100;
        if (sequence_index_13e == 2 && static_cast<unsigned char>(crossed())) { zero_motion(); y_f0 = udonge_surface(this); set_action_and_finalize(10); return; }
        if (advance()) set_action_and_finalize(9);
        if (!sequence_index_13e && !frame_timer_142) {
            if (frame_index_140 == 4) { spell_flash(-10, 145.0, 1); zero_motion(); }
            if (!frame_timer_142 && frame_index_140 == 6) { float p[3] = {0.0f, 10.0f, 0.0f}; spawn_offset(850, 60, 135.0, p, 3); dispatch_character_wave_handle(12); velocity_x_f4 = -7.0f; velocity_y_f8 = 6.0f; acceleration_y_100 = 0.35f; }
        }
        return;
    case 652:
        texture(0, 2); if (sequence_index_13e == 1 && time_counter_144 >= 30) { next_sequence_block(); acceleration_y_100 = 0.5f; return; }
        if (sequence_index_13e == 2) { velocity_y_f8 -= acceleration_y_100; if (static_cast<unsigned char>(crossed())) { zero_motion(); y_f0 = udonge_surface(this); set_action_and_finalize(10); return; } }
        if (advance()) set_action_and_finalize(9);
        if (entry(1)) {
            { float n = 0.0f; float p[4]; do { p[0] = static_cast<float>(n * 60.0); p[1] = 25.0f; p[2] = 0.0f; p[3] = 5.0f; orbit852(p); n = static_cast<float>(n + 1.0); } while (n < 6.0f); }
            { float n = 0.0f; float p[4]; do { p[0] = static_cast<float>(n * 60.0 + 30.0); p[1] = 25.0f; p[2] = 0.0f; p[3] = 20.0f; orbit852(p); n = static_cast<float>(n + 1.0); } while (n < 6.0f); }
            { float n = 0.0f; float p[4]; do { p[0] = static_cast<float>(60.0 + n * 60.0); p[1] = 25.0f; p[2] = 0.0f; p[3] = 35.0f; orbit852(p); n = static_cast<float>(n + 1.0); } while (n < 6.0f); }
        }
        if (!sequence_index_13e && frame_index_140 == 7 && !frame_timer_142) spell_flash(0, 100.0, 3);
        return;
    case 655:
        if (sequence_index_13e > 0 || (!sequence_index_13e && frame_index_140 >= 7)) texture(0, 2);
        if (sequence_index_13e == 1) {
            if (time_counter_144 >= 120) { next_sequence_block(); acceleration_y_100 = 0.5f; return; }
            if (time_counter_144 % 5 == 0) {
                if (!time_counter_144) dispatch_character_wave_handle(50);
                if (word_730 <= 15) {
                    float p[3] = {0.0f, 0.0f, 0.0f};
                    if (word_730 == 15) { dispatch_character_wave_handle(51); p[2] = 1.0f; }
                    spawn_offset(855, 0, 130.0, p, 3); ++word_730;
                }
            }
        }
        if (sequence_index_13e >= 2) { velocity_y_f8 -= acceleration_y_100; if (static_cast<unsigned char>(crossed())) { set_action_and_finalize(10); y_f0 = udonge_surface(this); zero_motion(); return; } }
        if (advance()) set_action_and_finalize(9);
        if (!sequence_index_13e && frame_index_140 == 7 && !frame_timer_142) spell_flash(0, 100.0, 5);
        return;
    case 695:
        landing(); if (advance()) set_action_and_finalize(0);
        if (!sequence_index_13e && !frame_timer_142 && frame_index_140 == 5) {
            event(55);
            effect(140, x_ec, static_cast<float>(y_f0 + 100.0), facing_104, 1);
            effect(140, x_ec, static_cast<float>(y_f0 + 100.0), facing_104, 1);
            effect(140, x_ec, static_cast<float>(y_f0 + 100.0), facing_104, 1);
            effect(141, x_ec, static_cast<float>(y_f0 + 100.0), facing_104, -1);
            effect(142, x_ec, y_f0, facing_104, -1);
        }
        return;
    case 696:
        landing();
        if (!frame_timer_142 && !frame_index_140) { if (!byte_47e) zero_motion(); byte_184 = 1; field_180 = 0; }
        if (frame_index_140 >= 5) { velocity_x_f4 = static_cast<float>(velocity_x_f4 - 0.5); if (velocity_x_f4 < 0.0f) velocity_x_f4 = 0.0f; }
        if (advance()) set_action_and_finalize(0);
        if (!frame_timer_142) {
            if (frame_index_140 == 3) velocity_x_f4 = 15.0f;
            if (!frame_timer_142 && frame_index_140 == 5) { dispatch_character_wave_handle(1); velocity_x_f4 = 5.0f; byte_47e = 0; }
        }
        return;
    case 710:
        landing(); if (advance()) set_action_and_finalize(700);
        if (!time_counter_144 && !frame_timer_142 && !frame_index_140) {
            if (sequence_index_13e != 1) return;
            field_73c = 90.0f;
            switch (g_match_identifier) {
            case 3: word_730 = 8; break;
            case 2: word_730 = 6; break;
            case 1: word_730 = 4; break;
            case 0: word_730 = 2; break;
            }
        }
        if (sequence_index_13e != 1) return;
        if (time_counter_144 % 12 == 0 && word_730 > 0) {
            float p[3] = {field_73c, 20.0f, 0.0f}; orbit900(p);
            p[0] = -field_73c; p[1] = 20.0f; p[2] = 0.0f; orbit900(p);
            dispatch_character_wave_handle(5); --word_730; field_73c = static_cast<float>(field_73c + 10.0);
        }
        if (!word_730) { ++word_732; if (word_732 >= 90) next_sequence_block(); }
        return;
    case 725:
        landing(); if (advance()) set_action_and_finalize(0);
        if (!time_counter_144 && !frame_timer_142 && !frame_index_140) {
            if (sequence_index_13e != 1) return;
            dispatch_character_wave_handle(8); float p[3];
            switch (g_match_identifier) {
            case 3: p[0] = 3.0f; p[1] = 360.0f; p[2] = 0.0f; spawn_offset(911, -8, 120.0, p, 3); break;
            case 2: p[0] = 2.75f; p[1] = 300.0f; p[2] = 0.0f; spawn_offset(911, -8, 120.0, p, 3); break;
            case 1: p[0] = 2.5f; p[1] = 240.0f; p[2] = 0.0f; spawn_offset(911, -8, 120.0, p, 3); break;
            case 0: p[0] = 2.5f; p[1] = 240.0f; p[2] = 0.0f; spawn_offset(911, -8, 120.0, p, 3); break;
            }
        }
        if (sequence_index_13e == 1 && time_counter_144 >= 48) next_sequence_block();
        return;
    case 726:
        landing(); expand_cone();
        if (sequence_index_13e == 1) {
            if (time_counter_144 % 30 == 0) {
                float p[3] = {0.0f, 1.0f, 4.0f}; spawn_offset(912, 50, 110.0, p, 3);
                p[1] = -1.0f; p[2] = 4.0f; spawn_offset(912, 50, 110.0, p, 3);
            }
            if (peer_in_cone()) word_7ae = 3;
            if (time_counter_144 >= 180) { next_sequence_block(); word_730 = 0; return; }
        }
        if (word_730 == 1) { if (word_732 % 60 == 0) dispatch_character_wave_handle(13); ++word_732; }
        if (entry(2)) {
            float p[3] = {static_cast<float>(udonge_random(360)), 0.0f, 3.0f}; spawn_at_peer(912, p); dispatch_character_wave_handle(14);
        }
        if (advance()) set_action_and_finalize(0);
        if (!sequence_index_13e && !frame_timer_142 && frame_index_140 == 8) {
            word_730 = 1; float p[3] = {0.0f, 0.0f, 0.0f}; spawn_offset(912, 50, 110.0, p, 3);
            p[1] = 1.0f; p[2] = 0.0f; spawn_offset(912, 50, 110.0, p, 3); field_7b0 = 0.0f;
            switch (g_match_identifier) {
            case 3: field_73c = 1.5f; return;
            case 2: field_73c = 1.2f; return;
            case 1: field_73c = 0.8f; return;
            case 0: field_73c = 0.6f; return;
            }
        }
        return;
    case 730:
        if (sequence_index_13e == 1) {
            switch (g_match_identifier) {
            case 3: word_736 = 6; break;
            case 2: word_736 = 5; break;
            case 1: word_736 = 4; break;
            case 0: word_736 = 2; break;
            }
            if (entry(1)) word_732 = static_cast<short>(udonge_random(word_736));
            if (word_730 >= word_736) { if (word_7a6 < 30) { next_sequence_block(); return; } word_7a6 = static_cast<short>(word_7a6 - 30); }
            if (time_counter_144 % 15 == 0 && word_730 < word_736) {
                dispatch_character_wave_handle(19);
                float p[4]; p[0] = static_cast<float>(-45.0 - static_cast<float>(udonge_random(40)));
                p[1] = static_cast<float>(static_cast<float>(udonge_random(5)) + 20.0); p[2] = 1.0f; p[3] = 0.0f;
                if (word_732 == word_730) p[3] = 1.0f;
                if (word_730 % 2 == 0) spawn(920, x_ec, y_f0, facing_104, 1, p, 4);
                else spawn(920, x_ec, y_f0, static_cast<unsigned char>(-facing_104), 1, p, 4);
                ++word_730;
            }
        }
        if (advance()) set_action_and_finalize(0);
        return;
    case 770:
        if (advance()) set_action_and_finalize(700);
        if (!sequence_index_13e && !frame_timer_142 && frame_index_140 == 5) {
            byte_655 = 1; finalize(-1); texture(2, -1); copy_health();
            word_76c = 0; word_76a = 1; word_766 = 0; word_768 = 0; word_764 = 0; event(23);
        }
        return;
    case 795:
        if (!sequence_index_13e) {
            velocity_y_f8 = static_cast<float>(velocity_y_f8 - static_cast<double>(0.3f));
            if (static_cast<unsigned char>(crossed())) { select_sequence(1); y_f0 = udonge_surface(this); zero_motion(); event(30); return; }
        }
        if (advance()) set_action_and_finalize(700);
        return;
    case 797:
        velocity_x_f4 = 3.0f;
        if (word_730 < 252) word_730 = static_cast<short>(word_730 + 3); else word_730 = 255;
        word_7a6 = word_730;
        if (x_ec >= 480.0) { x_ec = 480.0f; word_7a6 = 255; zero_motion(); set_action_and_finalize(0); return; }
        if (advance()) set_action_and_finalize(0);
        return;
    case 798:
        velocity_x_f4 = 3.0f;
        if (word_730 < 252) word_730 = static_cast<short>(word_730 + 3); else word_730 = 255;
        word_7a6 = word_730;
        if (x_ec <= 800.0) { x_ec = 800.0f; word_7a6 = 255; zero_motion(); set_action_and_finalize(700); return; }
        if (advance()) set_action_and_finalize(700);
        return;
    default:
        common_update();
        return;
    }
    advance();
}

}
