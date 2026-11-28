// JP1.06a 0x00557690: RemiliaObject_update_action_state (slot +0x28).
// See docs/REMILIA_OBJECT_UPDATE_2026_10_25.md.
#include "characters/RemiliaObjectActionState.hpp"
#include <math.h>

namespace th105 {

#define D(v) static_cast<double>(v)
#define MOVE() motion_004.set_components(params_340[0], params_340[1])
#define SPAWN(a, l, c) spawn_unparented(a, x_ec, y_f0, facing_104, l, reinterpret_cast<const unsigned *>(payload), c)
#define SPAWN_AT(a, x, y, l, c) spawn_unparented(a, x, y, facing_104, l, reinterpret_cast<const unsigned *>(payload), c)
#define OUTSIDE(xhi, xlo, yhi, ylo) (x_ec > xhi || x_ec < xlo || y_f0 > yhi || y_f0 < ylo)

#define ACTIVE_821(period) { \
    if (emit_repeated(0, 3, 5)) { retire(); return; } \
    if (field_180 == 6) { ++word_384; ++byte_184; field_180 = 0; } \
    advance_phase(5); \
    int const state = field_180; \
    if (state == 4 || state == 8) byte_184 = 0; \
    if (state != 0 && ++word_364 >= 3 && byte_184 > 0) { field_180 = 0; word_364 = 0; } \
    if (time_counter_144 % period == 0) { \
        float payload[3]; \
        payload[0] = rotation_12c; \
        payload[1] = 0; \
        payload[2] = 1; \
        SPAWN(821, 1, 3); \
    } \
    MOVE(); \
    rotation_12c = params_340[0]; \
}

__forceinline static float random_float(int n) {
    return static_cast<float>(static_cast<unsigned>(selector_random_roll(n)));
}

void RemiliaObjectUpdateView::update_action_state() {
    switch (action_id_13c) {
    case 800: {
        if (field_180 == 5 || OUTSIDE(1380.0f, -100.0, 1060.0f, -100.0)) { retire(); return; }
        if (sequence_index_13e == 0) {
            if (emit_repeated(0, 0, 3)) { retire(); return; }
            if (frame_timer_142 >= 90 || field_180 != 0) {
                retire();
                float payload[3];
                payload[2] = 2;
                for (int n = 0; n < 3; ++n) {
                    payload[0] = random_float(360);
                    payload[1] = random_float(5) + 10.0;
                    SPAWN(800, 1, 3);
                }
                payload[2] = 3;
                for (int n = 0; n < 3; ++n) {
                    payload[0] = random_float(360);
                    payload[1] = random_float(10) + 5.0;
                    SPAWN(800, 1, 3);
                }
                return;
            }
        }
        if (sequence_index_13e == 1) {
            if (!related_34c) { retire(); return; }
            x_ec = related_34c->x_ec;
            y_f0 = related_34c->y_f0;
            facing_104 = related_34c->facing_104;
            rotation_12c = related_34c->rotation_12c;
            velocity_x_f4 = related_34c->velocity_x_f4;
            velocity_y_f8 = related_34c->velocity_y_f8;
        }
        if (sequence_index_13e == 2 || sequence_index_13e == 3) {
            velocity_y_f8 -= 0.5;
            if (color_a_113 < 10) { retire(); return; }
            color_a_113 -= 10;
        }
        x_ec += facing_104 * velocity_x_f4;
        y_f0 += velocity_y_f8;
        if (advance_frame()) retire();
        return;
    }

    case 801: {
        if (field_180 == 5) { retire(); return; }
        if (sequence_index_13e == 0) {
            if (emit_repeated(0, 2, 2)) { retire(); return; }
            if (time_counter_144 == 0 && frame_timer_142 == 0 && frame_index_140 == 0 && sequence_index_13e == 0) {
                replace_secondary(991, 20, 20, 1, 2);
            }
            if (field_180 == 6 && ++word_384 < 10) { ++byte_184; field_180 = 0; }
            advance_phase(1);
            int const state = field_180;
            if (state == 4 || state == 8) byte_184 = 0;
            if (state != 0) {
                params_340[1] = 2;
                ++word_364;
                if (word_364 >= 3) {
                    if (byte_184 <= 0) goto burst_801;
                    field_180 = 0;
                    word_364 = 0;
                }
            }
            if (byte_184 <= 0) {
            burst_801:
                float payload[3];
                payload[0] = 0;
                payload[1] = 0;
                payload[2] = 1;
                SPAWN(801, 1, 3);
                retire();
                return;
            }
            params_340[1] += 0.5;
            if (params_340[1] >= 6.0f) turn_heading(0, 0.5f, 100);
            if (params_340[1] > 12.0f) params_340[1] = 12;
            MOVE();
            rotation_12c = params_340[0];
        }
        if (sequence_index_13e == 1) {
            scale_y_120 = scale_x_11c = static_cast<float>(scale_x_11c * D(0.9f));
            if (time_counter_144 >= 10) {
                if (color_a_113 < 10) { retire(); return; }
                color_a_113 -= 10;
                color_g_111 -= 10;
                color_b_110 -= 10;
            }
        }
        if (OUTSIDE(1380.0f, -100.0, 1060.0f, -100.0)) { retire(); return; }
        x_ec += facing_104 * velocity_x_f4;
        y_f0 += velocity_y_f8;
        if (advance_frame()) retire();
        return;
    }

    case 810:
        if (field_180 == 5) { retire(); return; }
        if (sequence_index_13e == 0) {
            params_340[1] *= D(0.9f);
            MOVE();
            if (time_counter_144 >= 15) {
                if (color_a_113 < 10) { retire(); return; }
                color_a_113 -= 10;
            }
            x_ec += facing_104 * velocity_x_f4;
            y_f0 += velocity_y_f8 * D(0.15f);
        }
        if (advance_frame()) retire();
        return;

    case 811:
        if (owner_348->action_id_13c != 505 && owner_348->action_id_13c != 506) { retire(); return; }
        switch (sequence_index_13e) {
        case 0: if (owner_348->sequence_index_13e == 0) position_relative(0, 0); break;
        case 1: if (owner_348->sequence_index_13e == 1) position_relative(0, 0); break;
        case 2: if (owner_348->sequence_index_13e == 2) position_relative(0, 0); break;
        }
        if (advance_frame()) retire();
        if (time_counter_144 == 0 && frame_timer_142 == 0 && frame_index_140 == 0 && sequence_index_13e == 1) retire();
        if (time_counter_144 == 0 && frame_timer_142 == 0 && frame_index_140 == 0 && sequence_index_13e == 2) retire();
        return;

    case 815: {
        if (field_180 == 5) { retire(); return; }
        switch (sequence_index_13e) {
        case 0: {
            if (emit_repeated(0, 1, 2)) { retire(); return; }
            scale_x_11c = 1.0f - field_370;
            field_370 *= D(0.85f);
            scale_y_120 = scale_x_11c;
            rotation_12c = field_378 + field_374;
            field_374 *= D(0.95f);
            field_378 = field_37c + field_378;
            if (static_cast<double>(time_counter_144) >= params_340[3]) {
                owner_348->dispatch_character_wave_handle(1);
                float payload[3];
                payload[0] = 0;
                payload[1] = 15;
                payload[2] = 1;
                SPAWN(815, 1, 3);
                payload[2] = 2;
                SPAWN(815, 1, 3);
                payload[2] = 3;
                SPAWN(815, 1, 3);
                retire();
                return;
            }
            MOVE();
            params_340[1] *= D(0.95f);
            velocity_x_f4 += field_380;
            field_380 *= D(0.95f);
            x_ec += facing_104 * velocity_x_f4 * 0.25;
            y_f0 += velocity_y_f8;
            break;
        }
        case 1:
            if (emit_repeated(0, 1, 2)) { retire(); return; }
            if (field_180 == 6 && ++word_384 < 10) { ++byte_184; field_180 = 0; }
            advance_phase(3);
            if (field_180 != 0) {
                params_340[1] = 2;
                ++word_364;
                if (word_364 >= 3) {
                    if (byte_184 <= 0) { retire(); return; }
                    field_180 = 0;
                    word_364 = 0;
                }
            }
            if (byte_184 <= 0) { retire(); return; }
            params_340[1] += 0.5;
            if (params_340[1] >= 6.0f) turn_heading(0, 0.5f, 100);
            if (params_340[1] > 12.0f) params_340[1] = 12;
            MOVE();
            rotation_12c = params_340[0];
            x_ec += facing_104 * velocity_x_f4;
            y_f0 += velocity_y_f8;
            break;
        case 2:
            if (color_a_113 < 5) { retire(); return; }
            scale_y_120 = scale_x_11c = static_cast<float>(field_370 + scale_x_11c);
            field_370 *= D(0.9f);
            color_a_113 -= 5;
            color_g_111 -= 5;
            color_b_110 -= 5;
            break;
        case 3:
            if (color_a_113 < 5) { retire(); return; }
            scale_y_120 = scale_x_11c = static_cast<float>(field_370 + scale_x_11c);
            rotation_12c -= field_374;
            field_374 *= D(0.9f);
            field_370 = D(0.9f) * field_370;
            color_a_113 -= 5;
            color_g_111 -= 5;
            color_b_110 -= 5;
            break;
        }
        if (OUTSIDE(1380.0f, -100.0, 1060.0f, -100.0)) { retire(); return; }
        if (advance_frame()) retire();
        return;
    }

    case 816: {
        if (field_180 == 5) { retire(); return; }
        switch (sequence_index_13e) {
        case 0:
            if ((owner_348->action_id_13c != 525 && owner_348->action_id_13c != 526) || owner_348->sequence_index_13e >= 3) {
                scale_y_120 = scale_x_11c = static_cast<float>(scale_x_11c * D(0.9f));
                if (color_a_113 >= 30) color_a_113 -= 30;
                else { retire(); return; }
            } else {
                position_relative(20, 100);
            }
            break;
        case 1:
        case 2: {
            if (emit_repeated(0, 0, 2)) { retire(); return; }
            if (time_counter_144 == 1 && (owner_348->action_id_13c == 525 || owner_348->action_id_13c == 526) &&
                (owner_348->sequence_index_13e == 1 || owner_348->sequence_index_13e == 2)) {
                field_378 = params_340[0];
                float const wanted = -atan2_degrees(
                    static_cast<float>(target_170->y_f0 + 100.0 - y_f0),
                    static_cast<float>((target_170->x_ec - x_ec) * facing_104));
                float const delta = static_cast<float>(wanted - params_340[0]);
                float diff = static_cast<float>(static_cast<int>(delta) % 360);
                if (diff > 180.0f) diff -= 360.0;
                if (diff < -180.0f) diff = 360.0 + diff;
                float const magnitude = static_cast<float>(fabs(diff));
                if (magnitude <= 20.0f) field_378 = wanted;
                else if (diff < 0.0f) field_378 -= 20.0;
                else if (diff > 0.0f) field_378 += 20.0;
                float payload[4];
                payload[0] = field_378;
                payload[1] = 0;
                payload[3] = params_340[3] + 1.0;
                if (sequence_index_13e == 1) {
                    payload[2] = 2;
                    SPAWN_AT(816,
                        static_cast<float>(lookup_orientation_cosine_quantized_abs(-params_340[0]) * 28.0 * facing_104 + x_ec),
                        static_cast<float>(lookup_orientation_sine_quantized_abs(-params_340[0]) * 28.0 + y_f0), 1, 4);
                } else {
                    payload[2] = 1;
                    SPAWN_AT(816,
                        static_cast<float>(lookup_orientation_cosine_quantized_abs(-params_340[0]) * 28.0 * facing_104 + x_ec),
                        static_cast<float>(lookup_orientation_sine_quantized_abs(-params_340[0]) * 28.0 + y_f0), 1, 4);
                }
                payload[2] = 3;
                SPAWN_AT(816,
                    static_cast<float>(lookup_orientation_cosine_quantized_abs(-params_340[0]) * 28.0 * facing_104 + x_ec),
                    static_cast<float>(lookup_orientation_sine_quantized_abs(-params_340[0]) * 28.0 + y_f0), 1, 4);
                dispatch_slot20();
            }
            if (time_counter_144 >= 90) {
                float payload[4];
                payload[0] = 0;
                payload[1] = 0;
                payload[2] = 4;
                payload[3] = 0;
                SPAWN_AT(816,
                    static_cast<float>(lookup_orientation_cosine_quantized_abs(-params_340[0]) * 28.0 * facing_104 + x_ec),
                    static_cast<float>(lookup_orientation_sine_quantized_abs(-params_340[0]) * 28.0 + y_f0), 1, 4);
                owner_348->dispatch_character_wave_handle(17);
                retire();
                return;
            }
            break;
        }
        case 3:
            scale_y_120 = scale_x_11c = static_cast<float>(scale_x_11c * D(0.9f));
            if (time_counter_144 >= 4) {
                if (color_a_113 >= 30) color_a_113 -= 30;
                else { retire(); return; }
            }
            break;
        case 4:
            scale_y_120 = scale_x_11c = static_cast<float>(scale_x_11c * D(0.9f));
            if (time_counter_144 >= 4) {
                byte_184 = 0;
                if (color_a_113 >= 30) color_a_113 -= 30;
                else { retire(); return; }
            }
            break;
        }
        if (advance_frame()) retire();
        return;
    }

    case 817:
        if (field_180 == 5 || OUTSIDE(1480.0f, -200.0, 1160.0f, -400.0)) { retire(); return; }
        if (sequence_index_13e == 0) {
            if (emit_repeated(0, 1, 4)) { retire(); return; }
            if (field_180 == 6) { ++byte_184; field_180 = 0; }
            if (byte_184 <= 0) {
                if (color_a_113 < 15) { retire(); return; }
                color_a_113 -= 15;
                color_g_111 -= 15;
                color_b_110 -= 15;
            } else if (time_counter_144 % 2 == 0) {
                float payload[3];
                payload[0] = rotation_12c;
                payload[1] = 0;
                payload[2] = 2;
                SPAWN(817, 1, 3);
            }
            MOVE();
            x_ec += facing_104 * velocity_x_f4;
            y_f0 += velocity_y_f8;
        }
        if (sequence_index_13e == 2) {
            scale_x_11c += D(0.05f);
            scale_y_120 *= D(0.95f);
            if (color_a_113 < 15) { retire(); return; }
            color_a_113 -= 15;
            color_g_111 -= 15;
            color_b_110 -= 15;
        }
        if (advance_frame()) retire();
        return;

    case 820:
        switch (sequence_index_13e) {
        case 0:
            if (owner_348->action_id_13c != 540) { retire(); return; }
            if (owner_348->sequence_index_13e <= 3) position_relative(0, 0);
            else { if (color_a_113 <= 20) { retire(); return; } goto fade_820; }
            break;
        case 1:
            if (owner_348->action_id_13c != 541) { retire(); return; }
            if (owner_348->sequence_index_13e <= 3) position_relative(0, 0);
            else { if (color_a_113 <= 20) { retire(); return; } goto fade_820; }
            break;
        fade_820:
            color_a_113 -= 20;
            color_g_111 -= 20;
            color_b_110 -= 20;
            break;
        }
        if (owner_348->word_186 != 0) return;
        if (advance_frame()) retire();
        return;

    case 821:
        if (field_180 == 5) { retire(); return; }
        if (sequence_index_13e == 0) ACTIVE_821(10);
        if (sequence_index_13e == 1) {
            scale_y_120 = scale_x_11c = static_cast<float>(scale_x_11c + D(0.15f));
            if (time_counter_144 >= 10) {
                if (color_a_113 < 10) { retire(); return; }
                color_a_113 -= 10;
                color_g_111 -= 10;
                color_b_110 -= 10;
            }
        }
        if (sequence_index_13e == 2) {
            scale_y_120 = scale_x_11c = static_cast<float>(params_340[1] + scale_x_11c);
            params_340[1] *= D(0.8f);
            if (color_a_113 < 10) { retire(); return; }
            color_a_113 -= 10;
            color_g_111 -= 10;
            color_b_110 -= 10;
        }
        if (sequence_index_13e == 3) ACTIVE_821(7);
        if (sequence_index_13e == 4) ACTIVE_821(5);
        if (OUTSIDE(1380.0f, -100.0, 1060.0f, -100.0)) { retire(); return; }
        x_ec += facing_104 * velocity_x_f4;
        y_f0 += velocity_y_f8;
        if (advance_frame()) retire();
        return;

    case 825:
        if (sequence_index_13e == 0) {
            if ((owner_348->action_id_13c != 560 && owner_348->action_id_13c != 561) || owner_348->sequence_index_13e != 4) {
                retire();
                return;
            }
            position_relative(0, 0);
        }
        if (advance_frame()) retire();
        return;

    case 826: {
        if (OUTSIDE(1380.0f, -100.0, 1060.0f, -100.0) || field_180 == 5) { retire(); return; }
        switch (sequence_index_13e) {
        case 0:
            scale_y_120 = scale_x_11c = static_cast<float>(scale_x_11c + D(0.2f));
            if (color_a_113 < 15) { retire(); return; }
            color_a_113 -= 15;
            color_g_111 -= 15;
            color_b_110 -= 15;
            break;
        case 1:
            MOVE();
            params_340[1] -= 0.5;
            if (params_340[1] < 0.5f) params_340[1] = 0.5f;
            x_ec += facing_104 * velocity_x_f4;
            y_f0 += velocity_y_f8 * 0.25;
            rotation_12c = field_374 + rotation_12c;
            scale_y_120 = scale_x_11c = static_cast<float>(scale_x_11c + D(0.02f));
            if (time_counter_144 >= 0) {
                if (color_a_113 <= 5) { retire(); return; }
                color_a_113 -= 5;
            }
            break;
        case 2:
            if ((owner_348->action_id_13c != 565 && owner_348->action_id_13c != 566) || owner_348->sequence_index_13e != 3) {
                retire();
                return;
            }
            x_ec = facing_104 * owner_348->velocity_x_f4 + owner_348->x_ec;
            y_f0 = owner_348->velocity_y_f8 + owner_348->y_f0;
            break;
        case 3:
            rotation_12c += 5.0;
            scale_y_120 = scale_x_11c = static_cast<float>(scale_x_11c + D(0.05f));
            if (color_a_113 <= 10) { retire(); return; }
            color_a_113 -= 10;
            break;
        case 4: {
            if (field_180 == 6) { ++byte_184; field_180 = 0; }
            double const y = y_f0;
            if (y - stage_surface_height_at_x() > 10.0) retire();
            else {
                double const next_y = y_f0;
                if (next_y - stage_surface_height_at_x() < -10.0 || byte_184 <= 0) retire();
            }
            MOVE();
            params_340[1] -= 3.0;
            if (params_340[1] < 0.5f) params_340[1] = 0.5f;
            x_ec += velocity_x_f4 * facing_104;
            y_f0 = static_cast<float>(velocity_y_f8 + y_f0);
            float payload[3];
            payload[0] = 0;
            payload[1] = 0;
            payload[2] = 5;
            SPAWN_AT(826, static_cast<float>(static_cast<float>(static_cast<unsigned>(selector_random_roll(40))) + x_ec - 20.0), y_f0, 1, 3);
            break;
        }
        case 6: {
            if (field_180 == 6) { ++byte_184; field_180 = 0; }
            double const y = y_f0;
            if (y - stage_surface_height_at_x() > 10.0) retire();
            else {
                double const next_y = y_f0;
                if (next_y - stage_surface_height_at_x() < -10.0 || byte_184 <= 0) retire();
            }
            MOVE();
            params_340[1] -= 3.0;
            if (params_340[1] < 0.5f) params_340[1] = 0.5f;
            x_ec += velocity_x_f4 * facing_104;
            y_f0 = static_cast<float>(velocity_y_f8 + y_f0);
            float payload[3];
            payload[0] = 0;
            payload[1] = 0;
            payload[2] = 7;
            SPAWN_AT(826, static_cast<float>(static_cast<float>(static_cast<unsigned>(selector_random_roll(40))) + x_ec - 20.0), y_f0, 1, 3);
            break;
        }
        case 5:
        case 7:
            scale_x_11c += D(0.05f);
            scale_y_120 *= D(0.98f);
            if (time_counter_144 >= 0) {
                if (color_a_113 > 10) {
                    color_a_113 -= 10;
                    color_g_111 -= 10;
                    color_b_110 -= 10;
                } else {
                    retire();
                    return;
                }
            }
            break;
        }
        if (advance_frame()) retire();
        if (time_counter_144 == 0 && frame_timer_142 == 0 && frame_index_140 == 0 && sequence_index_13e == 5) { retire(); return; }
        if (time_counter_144 == 0 && frame_timer_142 == 0 && frame_index_140 == 0 && sequence_index_13e == 7) { retire(); return; }
        return;
    }

    case 848:
        switch (sequence_index_13e) {
        case 0:
            position_relative(0, 0);
            if (owner_348->action_id_13c != 302 && owner_348->action_id_13c != 322) { retire(); return; }
            if (owner_348->frame_index_140 == 0) { retire(); return; }
            break;
        case 1:
        case 2:
            position_relative(0, 0);
            if (owner_348->action_id_13c != 321) { retire(); return; }
            if (owner_348->frame_index_140 == 0) { retire(); return; }
            break;
        case 3:
            position_relative(0, 0);
            if (owner_348->action_id_13c != 303) { retire(); return; }
            if (owner_348->frame_index_140 == 0) { retire(); return; }
            break;
        case 4:
            position_relative(0, 0);
            if (owner_348->action_id_13c != 308 || owner_348->frame_index_140 == 0) { retire(); return; }
            break;
        }
        if (owner_348->word_186 != 0) return;
        if (advance_frame()) { retire(); return; }
        if (sequence_index_13e > 9 || frame_index_140 != 0 || frame_timer_142 != 0) return;
        retire();
        return;

    case 850:
        if (field_180 == 6) { ++word_384; ++byte_184; field_180 = 0; }
        if (field_180 != 0 && ++word_364 >= 6) { field_180 = 0; byte_184 = 1; word_364 = 0; }
        if (sequence_index_13e <= 1) {
            if (owner_348->action_id_13c != 600 || owner_348->sequence_index_13e >= 4) {
                select_sequence(2);
                byte_184 = 0;
                return;
            }
            x_ec = owner_348->x_ec;
        }
        y_f0 = stage_surface_height_at_x();
        if (advance_frame()) retire();
        return;

    case 851:
        switch (sequence_index_13e) {
        case 0:
        case 1:
            if (owner_348->action_id_13c != 601) { retire(); return; }
            position_relative(0, 0);
            break;
        case 2: {
            if (field_180 == 6) { ++word_384; ++byte_184; field_180 = 0; }
            MOVE();
            float const angle = params_340[0];
            rotation_12c = angle;
            if (x_ec > 1680.0 || x_ec < -400.0) { retire(); return; }
            float payload[3];
            payload[0] = angle;
            payload[1] = 5;
            payload[2] = 3;
            SPAWN(851, 1, 3);
            break;
        }
        case 3:
            if (color_a_113 < 5) { retire(); return; }
            color_a_113 -= 5;
            color_g_111 -= 5;
            color_b_110 -= 5;
            scale_y_120 *= D(0.95f);
            scale_x_11c += D(0.01f);
            rotation_12c = params_340[0];
            params_340[1] = D(0.95f) * params_340[1];
            MOVE();
            break;
        case 4:
            if (color_a_113 < 5) { retire(); return; }
            scale_y_120 = scale_x_11c = static_cast<float>(field_370 + scale_x_11c);
            color_a_113 -= 5;
            color_g_111 -= 5;
            color_b_110 -= 5;
            field_370 *= D(0.9f);
            break;
        }
        x_ec += facing_104 * velocity_x_f4;
        y_f0 += velocity_y_f8;
        if (advance_frame()) retire();
        if (time_counter_144 != 0 || frame_timer_142 != 0 || frame_index_140 != 0 || sequence_index_13e != 2) return;
        retire();
        return;

    case 852:
        switch (sequence_index_13e) {
        case 0:
            if (color_a_113 < 10) { retire(); return; }
            color_a_113 -= 10;
            color_g_111 -= 10;
            color_b_110 -= 10;
            scale_y_120 = scale_x_11c = static_cast<float>(field_370 + scale_x_11c);
            rotation_12c -= field_374;
            field_374 *= D(0.9f);
            field_370 = D(0.9f) * field_370;
            break;
        case 1:
            if (color_a_113 >= 10) {
                color_a_113 -= 10;
                color_g_111 -= 10;
                color_b_110 -= 10;
                scale_y_120 = scale_x_11c = static_cast<float>(field_370 + scale_x_11c);
                rotation_12c -= field_374;
                field_374 *= D(0.9f);
                field_370 = D(0.9f) * field_370;
            } else {
                retire();
                return;
            }
            break;
        }
        if (advance_frame()) retire();
        return;

    case 853:
        if (field_180 == 6) { ++word_384; ++byte_184; field_180 = 0; }
        if (field_180 != 0 && ++word_364 >= 6) { field_180 = 0; byte_184 = 1; word_364 = 0; }
        if (sequence_index_13e <= 1) {
            if (owner_348->action_id_13c != 603 || owner_348->sequence_index_13e >= 3) {
                select_sequence(2);
                byte_184 = 0;
                return;
            }
            x_ec = owner_348->x_ec;
            y_f0 = stage_surface_height_at_x();
        }
        if (sequence_index_13e == 4) {
            scale_y_120 = scale_x_11c = static_cast<float>(1.0f - field_370);
            field_370 *= D(0.85f);
            if (word_364 == 0) {
                if (owner_348->action_id_13c == 603 && owner_348->sequence_index_13e < 3) x_ec = owner_348->x_ec;
                else word_364 = 1;
            }
            if (word_364 == 1) {
                if (color_a_113 <= 20) { retire(); return; }
                color_a_113 -= 20;
            }
            y_f0 = stage_surface_height_at_x();
        }
        if (sequence_index_13e == 5) {
            if (frame_index_140 == 17) {
                if (color_a_113 <= 10) { retire(); return; }
                color_a_113 -= 10;
                color_g_111 -= 10;
                color_b_110 -= 10;
            }
            scale_y_120 = scale_x_11c = static_cast<float>(scale_x_11c + D(0.6f));
            y_f0 = owner_348->y_f0 + 200.0;
            x_ec = owner_348->x_ec;
        }
        if (sequence_index_13e == 6) {
            velocity_y_f8 = static_cast<float>(velocity_y_f8 + 0.25);
            y_f0 = static_cast<float>(velocity_y_f8 + y_f0);
            if (y_f0 >= 1400.0f) { retire(); return; }
        }
        if (advance_frame()) retire();
        return;

    case 854:
        switch (sequence_index_13e) {
        case 0:
        case 1:
            if (owner_348->action_id_13c != 604) { retire(); return; }
            position_relative(0, 0);
            break;
        case 2: {
            if (field_180 == 6) { ++word_384; ++byte_184; field_180 = 0; }
            if (field_180 != 0 && byte_184 > 0 && ++word_364 >= 2) { word_364 = 0; field_180 = 0; }
            MOVE();
            float const angle = params_340[0];
            rotation_12c = angle;
            if (x_ec > 1680.0 || x_ec < -400.0) { retire(); return; }
            float payload[3];
            payload[0] = angle;
            payload[1] = 5;
            payload[2] = 3;
            SPAWN(854, 1, 3);
            if (time_counter_144 % 2 == 0) {
                double const y = y_f0;
                if (stage_surface_height_at_x() <= y) {
                    double const next_y = y_f0;
                    if (next_y - stage_surface_height_at_x() <= 300.0) {
                        float ground_payload[3];
                        ground_payload[0] = 0;
                        ground_payload[1] = 0;
                        ground_payload[2] = 7;
                        spawn_unparented(854, x_ec, stage_surface_height_at_x(), facing_104, 1, reinterpret_cast<const unsigned *>(ground_payload), 3);
                    }
                }
            }
            break;
        }
        case 3:
            if (color_a_113 < 5) { retire(); return; }
            color_a_113 -= 5;
            color_g_111 -= 5;
            color_b_110 -= 5;
            scale_y_120 *= D(0.95f);
            scale_x_11c += D(0.01f);
            rotation_12c = params_340[0];
            params_340[1] = D(0.95f) * params_340[1];
            MOVE();
            break;
        case 4:
            if (color_a_113 < 5) { retire(); return; }
            scale_y_120 = scale_x_11c = static_cast<float>(field_370 + scale_x_11c);
            color_a_113 -= 5;
            color_g_111 -= 5;
            color_b_110 -= 5;
            field_370 *= D(0.9f);
            break;
        case 5:
            if (color_a_113 < 5) { retire(); return; }
            color_a_113 -= 5;
            color_g_111 -= 5;
            color_b_110 -= 5;
            scale_y_120 = scale_x_11c = static_cast<float>(field_370 + scale_x_11c);
            rotation_12c -= field_374;
            field_374 *= D(0.9f);
            field_370 = D(0.9f) * field_370;
            break;
        case 6:
            if (!related_34c) { retire(); return; }
            x_ec = related_34c->x_ec;
            y_f0 = related_34c->y_f0;
            break;
        case 7:
            if (color_a_113 >= 5) {
                scale_x_11c = field_370 + scale_x_11c;
                scale_y_120 *= D(0.95f);
                color_a_113 -= 5;
                color_g_111 -= 5;
                color_b_110 -= 5;
                field_370 *= D(0.9f);
            } else {
                retire();
                return;
            }
            break;
        }
        x_ec += facing_104 * velocity_x_f4;
        y_f0 += velocity_y_f8;
        if (advance_frame()) retire();
        if (time_counter_144 != 0 || frame_timer_142 != 0 || frame_index_140 != 0 || sequence_index_13e != 2) return;
        retire();
        return;

    case 855:
        switch (sequence_index_13e) {
        case 0:
            if (color_a_113 < 10) { retire(); return; }
            color_a_113 -= 10;
            color_g_111 -= 10;
            color_b_110 -= 10;
            scale_y_120 = scale_x_11c = static_cast<float>(field_370 + scale_x_11c);
            rotation_12c -= field_374;
            field_374 *= D(0.9f);
            field_370 = D(0.9f) * field_370;
            break;
        case 1:
            if (color_a_113 >= 10) {
                color_a_113 -= 10;
                color_g_111 -= 10;
                color_b_110 -= 10;
                scale_y_120 = scale_x_11c = static_cast<float>(field_370 + scale_x_11c);
                rotation_12c -= field_374;
                field_374 *= D(0.9f);
                field_370 = D(0.9f) * field_370;
            } else {
                retire();
                return;
            }
            break;
        case 2:
            scale_y_120 = scale_x_11c = static_cast<float>(1.0f - field_370);
            field_370 *= D(0.9f);
            if (owner_348->action_id_13c != 605 || owner_348->sequence_index_13e > 2) { retire(); return; }
            position_relative(90, 125);
            break;
        }
        if (advance_frame()) retire();
        return;

    case 856:
        switch (sequence_index_13e) {
        case 0:
            if (color_a_113 < 10) { retire(); return; }
            color_a_113 -= 10;
            color_g_111 -= 10;
            color_b_110 -= 10;
            scale_y_120 = scale_x_11c = static_cast<float>(field_370 + scale_x_11c);
            rotation_12c -= field_374;
            field_374 *= D(0.9f);
            field_370 = D(0.9f) * field_370;
            break;
        case 1:
            if (color_a_113 >= 10) {
                color_a_113 -= 10;
                color_g_111 -= 10;
                color_b_110 -= 10;
                scale_y_120 = scale_x_11c = static_cast<float>(field_370 + scale_x_11c);
                rotation_12c -= field_374;
                field_374 *= D(0.9f);
                field_370 = D(0.9f) * field_370;
            } else {
                retire();
                return;
            }
            break;
        case 2:
            scale_y_120 = scale_x_11c = static_cast<float>(1.0f - field_370);
            field_370 *= D(0.9f);
            if (owner_348->action_id_13c != 606 || owner_348->sequence_index_13e != 4) { retire(); return; }
            position_relative(90, 25);
            break;
        }
        if (advance_frame()) retire();
        return;

    case 857: {
        switch (sequence_index_13e) {
        case 0:
            if (owner_348->action_id_13c != 607 || owner_348->sequence_index_13e >= 2) {
                scale_y_120 = scale_x_11c = static_cast<float>(scale_x_11c * D(0.9f));
                if (color_a_113 >= 30) color_a_113 -= 30;
                else { retire(); return; }
            } else {
                position_relative(20, 100);
            }
            break;
        case 1:
        case 2: {
            if (owner_348->word_174 <= 0) { retire(); return; }
            if (time_counter_144 == 1 && owner_348->action_id_13c == 607 && owner_348->sequence_index_13e <= 1 && params_340[3] <= 45.0f) {
                field_378 = params_340[0];
                float const wanted = -atan2_degrees(
                    static_cast<float>(target_170->y_f0 + 100.0 - y_f0),
                    static_cast<float>((target_170->x_ec - x_ec) * facing_104));
                float const delta = static_cast<float>(wanted - params_340[0]);
                float diff = static_cast<float>(static_cast<int>(delta) % 360);
                if (diff > 180.0f) diff -= 360.0;
                if (diff < -180.0f) diff = 360.0 + diff;
                float const magnitude = static_cast<float>(fabs(diff));
                if (magnitude <= 7.0) field_378 = wanted;
                else if (diff < 0.0f) field_378 -= 7.0;
                else if (diff > 0.0f) field_378 += 7.0;
                float payload[4];
                payload[0] = field_378;
                payload[1] = 0;
                payload[3] = params_340[3] + 1.0;
                if (sequence_index_13e == 1) {
                    payload[2] = 2;
                    SPAWN_AT(857,
                        static_cast<float>(lookup_orientation_cosine_quantized_abs(-params_340[0]) * 28.0 * facing_104 + x_ec),
                        static_cast<float>(lookup_orientation_sine_quantized_abs(-params_340[0]) * 28.0 + y_f0), 1, 4);
                } else {
                    payload[2] = 1;
                    SPAWN_AT(857,
                        static_cast<float>(lookup_orientation_cosine_quantized_abs(-params_340[0]) * 28.0 * facing_104 + x_ec),
                        static_cast<float>(lookup_orientation_sine_quantized_abs(-params_340[0]) * 28.0 + y_f0), 1, 4);
                }
                payload[2] = 3;
                SPAWN_AT(857,
                    static_cast<float>(lookup_orientation_cosine_quantized_abs(-params_340[0]) * 28.0 * facing_104 + x_ec),
                    static_cast<float>(lookup_orientation_sine_quantized_abs(-params_340[0]) * 28.0 + y_f0), 1, 4);
                dispatch_slot20();
            }
            if (time_counter_144 >= 30) {
                float payload[4];
                payload[0] = 0;
                payload[1] = 0;
                payload[2] = 4;
                payload[3] = 0;
                SPAWN_AT(857,
                    static_cast<float>(lookup_orientation_cosine_quantized_abs(-params_340[0]) * 28.0 * facing_104 + x_ec),
                    static_cast<float>(lookup_orientation_sine_quantized_abs(-params_340[0]) * 28.0 + y_f0), 1, 4);
                owner_348->dispatch_character_wave_handle(17);
                retire();
                return;
            }
            break;
        }
        case 3:
            scale_y_120 = scale_x_11c = static_cast<float>(scale_x_11c * D(0.9f));
            if (time_counter_144 >= 4) {
                if (color_a_113 >= 30) color_a_113 -= 30;
                else { retire(); return; }
            }
            break;
        case 4:
            scale_y_120 = scale_x_11c = static_cast<float>(scale_x_11c * D(0.9f));
            if (time_counter_144 >= 4) {
                byte_184 = 0;
                if (color_a_113 >= 30) color_a_113 -= 30;
                else { retire(); return; }
            }
            break;
        }
        if (advance_frame()) retire();
        return;
    }

    case 900: {
        if (field_180 == 5) { retire(); return; }
        switch (sequence_index_13e) {
        case 0:
            if ((owner_348->action_id_13c != 710 && owner_348->action_id_13c != 711) ||
                (owner_348->action_id_13c == 710 && owner_348->sequence_index_13e >= 2) ||
                (owner_348->action_id_13c == 711 && owner_348->sequence_index_13e >= 3)) {
                scale_y_120 = scale_x_11c = static_cast<float>(scale_x_11c * D(0.9f));
                if (color_a_113 >= 30) color_a_113 -= 30;
                else { retire(); return; }
            } else {
                if (owner_348->action_id_13c == 710) position_relative(20, 100);
                if (owner_348->action_id_13c == 711) position_relative(0, 200);
            }
            break;
        case 1:
        case 2: {
            if (owner_348->word_174 <= 0) { retire(); return; }
            if (time_counter_144 == 1 &&
                ((owner_348->action_id_13c == 710 && owner_348->sequence_index_13e <= 1) ||
                 (owner_348->action_id_13c == 711 && owner_348->sequence_index_13e <= 2))) {
                field_378 = params_340[0];
                float const wanted = -atan2_degrees(
                    static_cast<float>(target_170->y_f0 + 100.0 - y_f0),
                    static_cast<float>((target_170->x_ec - x_ec) * facing_104));
                float const delta = static_cast<float>(wanted - params_340[0]);
                float diff = static_cast<float>(static_cast<int>(delta) % 360);
                if (diff > 180.0f) diff -= 360.0;
                if (diff < -180.0f) diff = 360.0 + diff;
                float const magnitude = static_cast<float>(fabs(diff));
                if (magnitude <= 7.0) field_378 = wanted;
                else if (diff < 0.0f) field_378 -= 7.0;
                else if (diff > 0.0f) field_378 += 7.0;
                float payload[4];
                payload[0] = field_378;
                payload[1] = 0;
                payload[3] = params_340[3] + 1.0;
                if (sequence_index_13e == 1) {
                    payload[2] = 2;
                    SPAWN_AT(900,
                        static_cast<float>(lookup_orientation_cosine_quantized_abs(-params_340[0]) * 28.0 * facing_104 + x_ec),
                        static_cast<float>(lookup_orientation_sine_quantized_abs(-params_340[0]) * 28.0 + y_f0), 1, 4);
                } else {
                    payload[2] = 1;
                    SPAWN_AT(900,
                        static_cast<float>(lookup_orientation_cosine_quantized_abs(-params_340[0]) * 28.0 * facing_104 + x_ec),
                        static_cast<float>(lookup_orientation_sine_quantized_abs(-params_340[0]) * 28.0 + y_f0), 1, 4);
                }
                payload[2] = 3;
                SPAWN_AT(900,
                    static_cast<float>(lookup_orientation_cosine_quantized_abs(-params_340[0]) * 28.0 * facing_104 + x_ec),
                    static_cast<float>(lookup_orientation_sine_quantized_abs(-params_340[0]) * 28.0 + y_f0), 1, 4);
                dispatch_slot20();
            }
            if (time_counter_144 >= 45) {
                float payload[4];
                payload[0] = 0;
                payload[1] = 0;
                payload[2] = 4;
                payload[3] = 0;
                SPAWN_AT(900,
                    static_cast<float>(lookup_orientation_cosine_quantized_abs(-params_340[0]) * 28.0 * facing_104 + x_ec),
                    static_cast<float>(lookup_orientation_sine_quantized_abs(-params_340[0]) * 28.0 + y_f0), 1, 4);
                owner_348->dispatch_character_wave_handle(17);
                retire();
                return;
            }
            break;
        }
        case 3:
            scale_y_120 = scale_x_11c = static_cast<float>(scale_x_11c * D(0.9f));
            if (time_counter_144 >= 4) {
                if (color_a_113 >= 30) color_a_113 -= 30;
                else { retire(); return; }
            }
            break;
        case 4:
            scale_y_120 = scale_x_11c = static_cast<float>(scale_x_11c * D(0.9f));
            if (time_counter_144 >= 4) {
                byte_184 = 0;
                if (color_a_113 >= 30) color_a_113 -= 30;
                else { retire(); return; }
            }
            break;
        }
        if (advance_frame()) retire();
        return;
    }

    case 901: {
        if (OUTSIDE(1380.0f, -100.0, 1360.0f, -100.0) || field_180 == 5) { retire(); return; }
        switch (sequence_index_13e) {
        case 0:
            scale_y_120 = scale_x_11c = static_cast<float>(scale_x_11c + D(0.2f));
            if (color_a_113 >= 15) {
                color_a_113 -= 15;
                color_g_111 -= 15;
                color_b_110 -= 15;
            } else {
                retire();
                return;
            }
            break;
        case 1:
            MOVE();
            params_340[1] -= 0.5;
            if (params_340[1] < 0.5f) params_340[1] = 0.5f;
            x_ec += facing_104 * velocity_x_f4;
            y_f0 += velocity_y_f8 * 0.25;
            rotation_12c = field_374 + rotation_12c;
            scale_y_120 = scale_x_11c = static_cast<float>(scale_x_11c + D(0.02f));
            if (time_counter_144 >= 0) {
                if (color_a_113 > 5) color_a_113 -= 5;
                else { retire(); return; }
            }
            break;
        case 2:
            if (owner_348->action_id_13c != 720 || owner_348->sequence_index_13e != 3) { retire(); return; }
            x_ec = owner_348->velocity_x_f4 * facing_104 + owner_348->x_ec;
            y_f0 = owner_348->velocity_y_f8 + owner_348->y_f0;
            break;
        case 3:
        case 10:
            rotation_12c += 5.0;
            scale_y_120 = scale_x_11c = static_cast<float>(scale_x_11c + D(0.05f));
            if (color_a_113 <= 10) { retire(); return; }
            color_a_113 -= 10;
            break;
        case 4: {
            if (field_180 == 6) { ++word_384; ++byte_184; field_180 = 0; }
            if (field_180 != 0 && ++word_364 >= 5) { word_364 = 0; byte_184 = 1; field_180 = 0; }
            double const y = y_f0;
            if (y - stage_surface_height_at_x() > 10.0) retire();
            else {
                double const next_y = y_f0;
                if (next_y - stage_surface_height_at_x() < -10.0) retire();
            }
            MOVE();
            if (params_340[1] < 0.5f) params_340[1] = 0.5f;
            x_ec += velocity_x_f4 * facing_104;
            y_f0 = static_cast<float>(velocity_y_f8 + y_f0);
            float payload[3];
            payload[0] = 0;
            payload[1] = 0;
            payload[2] = 5;
            SPAWN_AT(901, static_cast<float>(static_cast<float>(static_cast<unsigned>(selector_random_roll(40))) + x_ec - 20.0), y_f0, 1, 3);
            break;
        }
        case 5:
            scale_x_11c += D(0.05f);
            scale_y_120 *= D(0.98f);
            if (time_counter_144 >= 0) {
                if (color_a_113 > 10) {
                    color_a_113 -= 10;
                    color_g_111 -= 10;
                    color_b_110 -= 10;
                } else {
                    retire();
                    return;
                }
            }
            break;
        case 6:
            rotation_12c += 3.0;
            if (owner_348->action_id_13c != 720 || owner_348->sequence_index_13e >= 4) word_364 = 1;
            if (word_364 == 0) {
                if (color_a_113 < 250) color_a_113 += 5;
                else color_a_113 = 255;
                scale_y_120 = scale_x_11c = static_cast<float>(scale_x_11c + D(0.05f));
                x_ec = owner_348->x_ec;
            } else {
                if (color_a_113 > 15) {
                    color_a_113 -= 15;
                    color_g_111 -= 15;
                    color_b_110 -= 15;
                } else {
                    retire();
                    return;
                }
            }
            break;
        case 7:
            if (field_180 == 6 && ++word_384 < 10) { ++byte_184; field_180 = 0; }
            if (time_counter_144 % 5 == 0) {
                float payload[3];
                payload[0] = rotation_12c;
                payload[1] = 0;
                payload[2] = 8;
                SPAWN(901, 1, 3);
            }
            if (field_180 != 0) { retire(); return; }
            x_ec += facing_104 * velocity_x_f4;
            y_f0 += velocity_y_f8;
            break;
        case 8:
            if (color_a_113 > 15) {
                color_a_113 -= 15;
                color_g_111 -= 15;
                color_b_110 -= 15;
            } else {
                retire();
                return;
            }
            break;
        case 9:
            if (owner_348->action_id_13c != 721 || owner_348->sequence_index_13e != 4) { retire(); return; }
            x_ec = owner_348->velocity_x_f4 * facing_104 + owner_348->x_ec;
            y_f0 = owner_348->velocity_y_f8 + owner_348->y_f0;
            break;
        }
        if (advance_frame()) retire();
        if (time_counter_144 != 0 || frame_timer_142 != 0 || frame_index_140 != 0 || sequence_index_13e != 6) return;
        retire();
        return;
    }

    case 902:
        if (field_180 == 5) { retire(); return; }
        switch (sequence_index_13e) {
        case 0:
            if (owner_348->word_174 <= 0 || time_counter_144 >= 120) {
                float payload[3];
                payload[0] = 0;
                payload[1] = 0;
                payload[2] = 4;
                SPAWN(902, 1, 3);
                retire();
                return;
            }
            if (time_counter_144 == 0 && frame_timer_142 == 0 && frame_index_140 == 0 && sequence_index_13e == 0) {
                replace_secondary(991, 20, 10, 1, 2);
            }
            if (field_180 == 6) { ++word_384; ++byte_184; field_180 = 0; }
            params_340[1] += 0.25;
            MOVE();
            break;
        case 1:
            if (owner_348->word_174 <= 0 || time_counter_144 >= 60) {
                float payload[3];
                payload[0] = 0;
                payload[1] = 0;
                payload[2] = 4;
                SPAWN(902, 1, 3);
                retire();
                return;
            }
            if (word_364 == 0) {
                if (color_a_113 <= 245) color_a_113 += 10;
                else {
                    color_a_113 = 255;
                    byte_184 = 1;
                    word_364 = 1;
                    replace_secondary(991, 20, 10, 1, 2);
                }
            }
            if (field_180 == 6) { ++word_384; ++byte_184; field_180 = 0; }
            break;
        case 2:
            scale_y_120 = scale_x_11c = static_cast<float>((1.0f - field_370) * 4.0);
            field_370 *= D(0.95f);
            if (time_counter_144 >= 15) {
                if (color_a_113 >= 5) color_a_113 -= 5;
                else { retire(); return; }
            }
            break;
        case 3:
            MOVE();
            params_340[1] *= D(0.95f);
            if (time_counter_144 >= 15) {
                scale_y_120 = scale_x_11c = static_cast<float>(scale_x_11c * D(0.99f));
                if (color_a_113 >= 5) color_a_113 -= 5;
                else { retire(); return; }
            }
            break;
        case 4:
            scale_y_120 = scale_x_11c = static_cast<float>(scale_x_11c * D(0.95f));
            if (color_a_113 < 10) { retire(); return; }
            color_a_113 -= 10;
            break;
        case 5:
            if (field_180 == 6 && ++word_384 < 10) { ++byte_184; field_180 = 0; }
            if (owner_348->word_174 <= 0 || time_counter_144 >= 240 || byte_184 <= 0) {
                float payload[3];
                payload[0] = 0;
                payload[1] = 0;
                payload[2] = 4;
                SPAWN(902, 1, 3);
                retire();
                return;
            }
            MOVE();
            rotation_12c = params_340[0];
            if (x_ec > 1380.0f || x_ec < -100.0 || y_f0 < -200.0 || y_f0 > 960.0) { retire(); return; }
            break;
        }
        x_ec += facing_104 * velocity_x_f4;
        y_f0 += velocity_y_f8;
        if (advance_frame()) retire();
        return;

    case 903:
        if (field_180 == 5) { retire(); return; }
        switch (sequence_index_13e) {
        case 0:
            if (word_364 == 0) {
                scale_x_11c = static_cast<float>(scale_x_11c + D(0.3f));
                if (scale_x_11c >= 10.0f) scale_x_11c = 10;
                scale_y_120 = (1.0f - field_370) * D(0.8f) + D(0.2f);
                field_370 *= D(0.95f);
                if (owner_348->word_174 <= 0) word_364 = 1;
                if (owner_348->word_730 == 2) {
                    word_364 = 1;
                    float payload[3];
                    payload[0] = params_340[0];
                    payload[1] = 40;
                    payload[2] = 1;
                    SPAWN(903, 1, 3);
                }
                x_ec = owner_348->x_ec;
                y_f0 = owner_348->y_f0 + 230.0;
            }
            if (word_364 == 1) {
                if (color_a_113 < 5) { retire(); return; }
                color_a_113 -= 5;
                color_b_110 -= 5;
                color_g_111 -= 5;
            }
            break;
        case 1:
            if (time_counter_144 == 0 && frame_timer_142 == 0 && frame_index_140 == 0 && sequence_index_13e == 1) {
                replace_secondary(991, 60, 10, 1, 2);
            }
            if (owner_348->word_174 <= 0) {
                byte_184 = 0;
                if (color_a_113 < 25) { retire(); return; }
                color_a_113 -= 25;
                color_b_110 -= 25;
                color_g_111 -= 25;
            } else if (time_counter_144 % 2 == 0) {
                float payload[3];
                payload[0] = random_float(360);
                payload[1] = random_float(11) + 4.0;
                payload[2] = 2;
                SPAWN(903, 1, 3);
            }
            MOVE();
            if (x_ec > 1380.0f || x_ec < -100.0 || y_f0 < -200.0 || y_f0 > 960.0) { retire(); return; }
            break;
        case 2:
            MOVE();
            params_340[1] *= D(0.95f);
            scale_y_120 = scale_x_11c = static_cast<float>(scale_x_11c * D(0.99f));
            if (color_a_113 < 15) { retire(); return; }
            color_a_113 -= 15;
            color_g_111 -= 15;
            color_b_110 -= 15;
            break;
        case 3:
            if (field_180 == 6 && ++word_384 < 2) { ++byte_184; field_180 = 0; }
            if (owner_348->word_174 <= 0 || time_counter_144 >= 240 || byte_184 <= 0) {
                select_sequence(4);
                velocity_x_f4 = 0;
                velocity_y_f8 = 0;
            }
            MOVE();
            rotation_12c = params_340[0];
            if (x_ec > 1380.0f || x_ec < -100.0 || y_f0 < -200.0 || y_f0 > 960.0) { retire(); return; }
            break;
        case 4:
            scale_y_120 = scale_x_11c = static_cast<float>(scale_x_11c * D(0.95f));
            if (color_a_113 < 10) { retire(); return; }
            color_a_113 -= 10;
            break;
        case 5:
            if (word_364 == 0) {
                double const horizontal = lookup_orientation_cosine_quantized_abs(-params_340[0]) * params_340[1];
                x_ec = horizontal * facing_104 + owner_348->x_ec;
                y_f0 = lookup_orientation_sine_quantized_abs(-params_340[0]) * params_340[1] + (owner_348->y_f0 + 230.0);
                params_340[1] *= D(0.9f);
                scale_y_120 = scale_x_11c = static_cast<float>(scale_x_11c * D(0.99f));
                if (owner_348->action_id_13c != 741) word_364 = 1;
                if (time_counter_144 >= 20) {
                    if (color_a_113 < 5) { retire(); return; }
                    color_a_113 -= 5;
                    color_g_111 -= 5;
                    color_b_110 -= 5;
                }
            }
            if (word_364 == 1) {
                scale_y_120 = scale_x_11c = static_cast<float>(scale_x_11c * D(0.99f));
                if (color_a_113 < 5) { retire(); return; }
                color_a_113 -= 5;
                color_g_111 -= 5;
                color_b_110 -= 5;
            }
            break;
        case 6:
            scale_y_120 = scale_x_11c = static_cast<float>((1.0f - field_370) * 4.0);
            field_370 *= D(0.95f);
            if (time_counter_144 >= 15) {
                if (color_a_113 >= 5) color_a_113 -= 5;
                else { retire(); return; }
            }
            break;
        case 7:
            scale_y_120 = scale_x_11c = static_cast<float>(1.0f - field_370);
            field_370 *= D(0.95f);
            if (owner_348->word_730 != 1 || owner_348->action_id_13c != 741) word_364 = 1;
            if (word_364 == 0) {
                if (color_a_113 <= 235) color_a_113 += 20;
                else color_a_113 = 255;
                x_ec = owner_348->x_ec;
                y_f0 = owner_348->y_f0 + 230.0;
            } else {
                if (color_a_113 >= 5) color_a_113 -= 5;
                else { retire(); return; }
            }
            break;
        }
        x_ec += facing_104 * velocity_x_f4;
        y_f0 += velocity_y_f8;
        if (advance_frame()) retire();
        return;

    case 980:
        update_ping_pong_motion();
        if (advance_frame()) retire();
        return;

    case 990:
        x_ec = owner_348->x_ec - facing_104 * 82;
        y_f0 = owner_348->y_f0 + 132.0;
        if (owner_348->action_id_13c != 600 || owner_348->sequence_index_13e != 1) { retire(); return; }
        if (advance_frame()) retire();
        return;

    case 998:
        if (sequence_index_13e == 0) {
            if (owner_348->action_id_13c > 153 && owner_348->action_id_13c < 158) position_relative(55, 55);
            if (owner_348->action_id_13c > 149 && owner_348->action_id_13c < 154) position_relative(35, 95);
            if (owner_348->action_id_13c == 158) position_relative(85, 90);
        }
        if (advance_frame()) {
            retire();
            owner_348->byte_751 = 0;
        }
        return;

    default:
        advance_frame();
        return;
    }
}

} // namespace th105
