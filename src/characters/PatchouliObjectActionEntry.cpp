// JP1.06a 0x0052D200: PatchouliObject primary slot +0x3C action entry initializer.
// See docs/PATCHOULI_OBJECT_ENTRY_2026_10_24.md.
#include "characters/PatchouliObjectActionEntry.hpp"

namespace th105 {

#define SELECT() select_sequence(static_cast<int>(params_340[2]))
#define MOVE() motion_004.set_components(params_340[0], params_340[1])
#define SPAWN(a, l, c) spawn_parented(a, x_ec, y_f0, static_cast<unsigned char>(facing_104), l, reinterpret_cast<const unsigned *>(payload), c)
#define UNSPAWN(a, l, c) spawn_unparented(a, x_ec, y_f0, static_cast<unsigned char>(facing_104), l, reinterpret_cast<const unsigned *>(payload), c)
#define SCALE(n, factor, base) scale_y_120 = scale_x_11c = static_cast<float>(random_float(n) * static_cast<double>(factor) + static_cast<double>(base))
#define ROUND_SCALE(n, factor, base) { float const product = random_float(n) * static_cast<double>(factor); scale_y_120 = scale_x_11c = static_cast<float>(product + static_cast<double>(base)); }

__forceinline static float random_float(int n) {
    return static_cast<float>(static_cast<unsigned>(selector_random_roll(n)));
}

void PatchouliObjectEntryView::initialize_action_entry() {
    velocity_x_f4 = 0;
    velocity_y_f8 = 0;
    field_370 = 0;
    field_374 = 0;
    field_378 = 0;
    word_384 = 0;
    field_37c = 0;
    word_386 = 0;
    field_380 = 0;
    byte_184 = 0;
    word_364 = 0;
    word_366 = 0;
    word_368 = 0;
    word_36a = 0;
    word_36c = 0;
    switch (action_id_13c) {
    case 800:
        rotation_12c = params_340[0];
        SELECT();
        if (sequence_id_13e == 0)
            byte_184 = 1;
        if (sequence_id_13e == 1)
            ROUND_SCALE(50, 0.01f, 1.0);
        if (sequence_id_13e == 2)
            byte_184 = 3;
        return;
    case 801:
        byte_184 = 1;
        rotation_12c = params_340[0];
        SELECT();
        if (sequence_id_13e == 2)
            field_370 = 0.7f;
        if (sequence_id_13e == 6)
            MOVE();
        if (sequence_id_13e == 8) {
            field_370 = 0.5f;
            MOVE();
            ROUND_SCALE(50, 0.01f, 1.0);
        }
        if (sequence_id_13e == 9) {
            byte_184 = 6;
            MOVE();
        }
        if (sequence_id_13e == 10) {
            ROUND_SCALE(50, 0.01f, 1.0);
            field_370 = random_float(10) - 5.0;
        }
        if (sequence_id_13e == 11)
            ROUND_SCALE(50, 0.01f, 1.0);
        return;
    case 810: {
        float payload[3];
        byte_184 = 1;
        rotation_12c = params_340[0];
        byte_17c = 0;
        SELECT();
        if (sequence_id_13e == 0 || sequence_id_13e == 6) {
            payload[0] = params_340[0];
            payload[1] = 0;
            payload[2] = 4;
            UNSPAWN(810, 1, 3);
        }
        if (sequence_id_13e == 0 || sequence_id_13e == 1 || sequence_id_13e == 6)
            MOVE();
        if (sequence_id_13e == 5) {
            SCALE(70, 0.01f, 0.8f);
            field_370 = 3.0 - random_float(6);
        }
        return;
    }
    case 811:
        byte_184 = 1;
        rotation_12c = params_340[0];
        byte_17c = 5;
        SELECT();
        if (sequence_id_13e == 0) {
            rotation_12c = random_float(360);
            MOVE();
            field_370 = random_float(10) - 5.0;
        }
        return;
    case 815:
        field_370 = 0.5f;
        rotation_12c = params_340[0];
        byte_17c = 1;
        SELECT();
        if (sequence_id_13e == 0) {
            scale_y_120 = 1.75f;
            byte_184 = 3;
            replace_auxiliary(990);
            aux_154->x_e8 = x_ec;
            aux_154->y_ec = stage_height();
            aux_154->facing_104 = static_cast<unsigned char>(facing_104);
            velocity_y_f8 = 60;
            byte_184 = 3;
            int_180 = 0;
        }
        if (sequence_id_13e == 3)
            field_124 = 85;
        if (sequence_id_13e == 5) {
            rotation_12c = random_float(360);
            SCALE(50, 0.01f, 1.0);
            MOVE();
        }
        return;
    case 816:
        byte_17c = 6;
        SELECT();
        if (sequence_id_13e == 0 || sequence_id_13e == 3) {
            scale_y_120 = scale_x_11c = 0.1f;
            byte_184 = 1;
            MOVE();
            field_370 = velocity_x_f4;
            field_374 = velocity_y_f8;
            velocity_x_f4 = 0;
            velocity_y_f8 = 0;
        }
        if (sequence_id_13e == 2) {
            rotation_12c = random_float(360);
            SCALE(75, 0.01f, 1.0);
            MOVE();
        }
        if (sequence_id_13e == 5 || sequence_id_13e == 6) {
            SCALE(30, 0.01f, 0.9f);
            MOVE();
            byte_184 = 1;
        }
        return;
    case 820:
        field_370 = random_float(10) + 5.0;
        byte_17c = 2;
        SELECT();
        if (sequence_id_13e == 1) {
            field_124 = random_float(80) + 50.0;
            field_128 = random_float(80) - 40.0;
            rotation_12c = random_float(360);
        }
        if (sequence_id_13e == 2)
            byte_184 = 1;
        return;
    case 821:
        byte_17c = 7;
        SELECT();
        if (sequence_id_13e == 1) {
            alpha_113 = 0;
            scale_y_120 = scale_x_11c = 3;
        }
        if (sequence_id_13e == 2)
            rotation_12c = params_340[0];
        if (sequence_id_13e == 3)
            byte_184 = 1;
        if (sequence_id_13e == 5) {
            SCALE(100, 0.01f, 0.5);
        }
        if (sequence_id_13e == 7) {
            rotation_12c = random_float(360);
            SCALE(50, 0.01f, 1.0);
        }
        if (sequence_id_13e == 8)
            byte_184 = 1;
        if (sequence_id_13e == 9) {
            rotation_12c = random_float(360);
            field_128 = random_float(150) - 75.0;
            field_124 = random_float(150) - 75.0;
        }
        return;
    case 825: {
        float payload[3];
        rotation_12c = params_340[0];
        byte_17c = 3;
        SELECT();
        if (sequence_id_13e == 0) {
            alpha_113 = 0;
            field_370 = x_ec - owner_348->x_ec;
            field_374 = y_f0 - owner_348->y_f0;
            payload[0] = params_340[0];
            payload[1] = 40;
            payload[2] = 2;
            UNSPAWN(825, 1, 3);
        }
        if (sequence_id_13e == 2) {
            alpha_113 = 0;
            field_370 = x_ec - owner_348->x_ec;
            field_374 = y_f0 - owner_348->y_f0;
            byte_184 = 1;
        }
        return;
    }
    case 826: {
        float payload[3];
        byte_17c = 8;
        SELECT();
        if (sequence_id_13e == 0) {
            MOVE();
            byte_184 = 3;
            if (owner_348->byte_60c >= 2)
                byte_184 = 4;
            if (owner_348->byte_60c >= 4)
                byte_184 = 5;
            payload[0] = rotation_12c;
            payload[1] = 0;
            payload[2] = 1;
            SPAWN(826, 1, 3);
        }
        if (sequence_id_13e == 2)
            rotation_12c = params_340[0];
        return;
    }
    case 827: {
        float payload[3];
        rotation_12c = params_340[0];
        byte_17c = 13;
        SELECT();
        if (sequence_id_13e == 0) {
            velocity_y_f8 = 5;
            payload[0] = rotation_12c;
            payload[1] = 0;
            payload[2] = 3;
            byte_184 = 1;
            SPAWN(827, 1, 3);
            replace_auxiliary(990);
            aux_154->scale_x_f8 = 3;
            aux_154->scale_y_fc = 2;
            aux_154->x_e8 = x_ec;
            aux_154->y_ec = stage_height();
            aux_154->facing_104 = static_cast<unsigned char>(facing_104);
        }
        return;
    }
    case 830: {
        float payload[4];
        byte_17c = 4;
        SELECT();
        if (sequence_id_13e == 0) {
            replace_auxiliary(990);
            aux_154->x_e8 = x_ec;
            aux_154->y_ec = stage_height();
            aux_154->facing_104 = static_cast<unsigned char>(facing_104);
            velocity_y_f8 = 60;
            byte_184 = 1;
            payload[1] = 15;
            payload[2] = 3;
            payload[3] = 0;
            for (float n = 0; n < 6; n += 1.0) {
                payload[0] = static_cast<float>(static_cast<unsigned>(selector_random_roll(40) - 20)) + n * 60.0;
                UNSPAWN(830, 1, 4);
            }
        }
        if (sequence_id_13e == 2) {
            field_370 = random_float(10) - 5.0;
            byte_184 = 1;
            rotation_12c = random_float(360);
            MOVE();
            SCALE(25, 0.01f, 1.0);
        }
        if (sequence_id_13e == 3) {
            rotation_12c = random_float(360);
            ROUND_SCALE(60, 0.01f, 0.7f);
        }
        if (sequence_id_13e == 4) {
            rotation_12c = random_float(360);
            ROUND_SCALE(10, 0.1f, 0.5);
        }
        if (sequence_id_13e == 5) {
            field_370 = random_float(14) - 7.0;
            rotation_12c = random_float(360);
            MOVE();
            SCALE(100, 0.01f, 0.5);
        }
        return;
    }
    case 831: {
        float payload[3];
        byte_17c = 9;
        SELECT();
        if (sequence_id_13e == 0) {
            byte_184 = 1;
            replace_auxiliary(990);
            aux_154->x_e8 = x_ec;
            aux_154->y_ec = static_cast<float>(y_f0 + 320.0);
            aux_154->scale_x_f8 = 2;
            aux_154->scale_y_fc = 2;
            aux_154->facing_104 = static_cast<unsigned char>(facing_104);
            velocity_y_f8 = 80;
            payload[1] = 15;
            payload[2] = 1;
            for (float n = 0; n < 6; n += 1.0) {
                payload[0] = static_cast<float>(static_cast<unsigned>(selector_random_roll(40) - 20)) + n * 60.0;
                spawn_unparented(831, x_ec, static_cast<float>(y_f0 + 320.0), static_cast<unsigned char>(facing_104), 1, reinterpret_cast<const unsigned *>(payload), 3);
            }
        }
        if (sequence_id_13e == 1) {
            rotation_12c = random_float(360);
            ROUND_SCALE(60, 0.01f, 0.7f);
            field_370 = random_float(10) - 5.0;
        }
        if (sequence_id_13e == 2) {
            rotation_12c = random_float(360);
            ROUND_SCALE(60, 0.01f, 0.7f);
            field_370 = random_float(10) - 5.0;
        }
        if (sequence_id_13e == 3) {
            byte_184 = 1;
            replace_auxiliary(990);
            aux_154->x_e8 = x_ec;
            aux_154->y_ec = static_cast<float>(y_f0 + 480.0);
            aux_154->scale_x_f8 = 3;
            aux_154->scale_y_fc = 3;
            aux_154->facing_104 = static_cast<unsigned char>(facing_104);
            velocity_y_f8 = 80;
            payload[1] = 15;
            payload[2] = 1;
            for (float n = 0; n < 6; n += 1.0) {
                payload[0] = static_cast<float>(static_cast<unsigned>(selector_random_roll(40) - 20)) + n * 60.0;
                spawn_unparented(831, x_ec, static_cast<float>(y_f0 + 480.0), static_cast<unsigned char>(facing_104), 1, reinterpret_cast<const unsigned *>(payload), 3);
            }
        }
        return;
    }
    case 822:
        byte_184 = 3;
        replace_auxiliary(990);
        aux_154->x_e8 = x_ec;
        aux_154->y_ec = 0;
        aux_154->facing_104 = static_cast<unsigned char>(facing_104);
        return;
    case 823:
        byte_184 = 1;
        scale_y_120 = scale_x_11c = 2;
        return;
    case 848: {
        float payload[3];
        SELECT();
        if (sequence_id_13e == 5) {
            scale_y_120 = scale_x_11c = 0.2f;
            field_370 = x_ec - owner_348->x_ec;
            field_374 = y_f0 - owner_348->y_f0;
            byte_184 = 4;
        }
        if (sequence_id_13e == 7 && params_340[1] == 1)
            scale_y_120 = scale_x_11c = 1.5f;
        if (sequence_id_13e == 8) {
            scale_y_120 = scale_x_11c = 0.2f;
            word_366 = 0;
            field_370 = x_ec - owner_348->x_ec;
            field_374 = y_f0 - owner_348->y_f0;
            byte_184 = 0;
        }
        if (sequence_id_13e == 9)
            word_364 = 1;
        if (sequence_id_13e == 10) {
            word_364 = 1;
            payload[0] = 0;
            payload[1] = 0;
            payload[2] = 11;
            UNSPAWN(848, 1, 3);
        }
        if (sequence_id_13e == 11) {
            word_364 = 1;
            field_128 = 70;
        }
        if (sequence_id_13e == 12) {
            byte_184 = 0;
            word_364 = 1;
        }
        if (sequence_id_13e == 13) {
            word_364 = 1;
            field_370 = random_float(10) + 5.0;
            field_124 = random_float(80) + 50.0;
            field_128 = random_float(80) - 40.0;
            rotation_12c = random_float(360);
        }
        return;
    }
    case 850:
        byte_184 = 1;
        SELECT();
        if (sequence_id_13e == 0) {
            word_344 = 1;
            scale_y_120 = scale_x_11c = 0;
            byte_184 = 1;
        }
        if (sequence_id_13e == 2) {
            byte_184 = 1;
            rotation_12c = params_340[0];
        }
        if (sequence_id_13e == 3)
            field_370 = 0.5f;
        if (sequence_id_13e == 4) {
            ROUND_SCALE(10, 0.1f, 0.25);
            word_364 = selector_random_roll(40);
        }
        if (sequence_id_13e == 5) {
            MOVE();
            field_370 = random_float(10) - 5.0;
        }
        if (sequence_id_13e == 6) {
            ROUND_SCALE(10, 0.1f, 0.75);
            rotation_12c = random_float(360);
        }
        return;
    case 851:
        byte_184 = 1;
        rotation_12c = params_340[0];
        SELECT();
        if (sequence_id_13e == 1)
            MOVE();
        if (sequence_id_13e == 3) {
            field_370 = 0.5f;
            MOVE();
            ROUND_SCALE(50, 0.01f, 1.0);
        }
        return;
    case 852:
        scale_y_120 = scale_x_11c = 0;
        SELECT();
        if (sequence_id_13e == 3) {
            ROUND_SCALE(75, 0.01f, 0.75);
            rotation_12c = random_float(360);
            field_370 = random_float(10) + 10.0;
        }
        return;
    case 853:
        rotation_12c = params_340[0];
        word_344 = 1;
        SELECT();
        if (sequence_id_13e == 0)
            field_370 = 1;
        if (sequence_id_13e == 4) {
            scale_y_120 = 0;
            if (params_340[1] == 0) {
                field_378 = 2;
                float product = random_float(5) * static_cast<double>(0.1f);
                field_370 = product + 0.5;
                field_374 = 1;
            }
            if (params_340[1] == 1) {
                field_378 = -4;
                float product = random_float(2) * static_cast<double>(0.1f);
                field_370 = product + static_cast<double>(0.2f);
                field_374 = 1;
            }
        }
        if (sequence_id_13e == 6)
            ROUND_SCALE(10, 0.1f, 0.5);
        if (sequence_id_13e == 7)
            ROUND_SCALE(125, 0.01f, 0.75);
        return;
    case 854: {
        float payload[3];
        SELECT();
        if (sequence_id_13e == 0) {
            field_370 = 1;
            scale_y_120 = scale_x_11c = 0;
            word_344 = 1;
            payload[0] = 0;
            payload[1] = 0;
            payload[2] = 1;
            SPAWN(854, -1, 3);
            payload[2] = 2;
            SPAWN(854, -1, 3);
            field_124 = 75;
        }
        if (sequence_id_13e == 1) {
            alpha_113 = 0;
            field_370 = 1;
            word_344 = 1;
            scale_y_120 = scale_x_11c = 0;
            field_124 = 75;
        }
        if (sequence_id_13e == 2) {
            word_344 = 1;
            field_370 = 1;
            scale_y_120 = scale_x_11c = 0;
            field_124 = 75;
        }
        if (sequence_id_13e == 3) {
            alpha_113 = 0;
            field_370 = 1;
            color_111 = 0;
            color_112 = 0;
            ROUND_SCALE(20, 0.1f, 1.0);
            field_370 = random_float(4) + 2.0;
            if (static_cast<unsigned>(selector_random_roll(100)) <= 50)
                field_370 = field_370 * -1.0;
            field_124 = 75;
        }
        if (sequence_id_13e == 4) {
            if (target_34c) {
                x_ec = lookup_orientation_cosine_quantized_abs(-params_340[0]) * params_340[1] * facing_104 + target_34c->x_ec;
                y_f0 = lookup_orientation_sine_quantized_abs(-params_340[0]) * params_340[1] * static_cast<double>(0.2f) + target_34c->y_f0;
            }
            scale_y_120 = 0.01f;
            scale_x_11c = 0.01f;
            payload[0] = 0;
            payload[1] = 0;
            payload[2] = 5;
            byte_184 = 99;
            SPAWN(854, layer_33c, 3);
            payload[2] = 6;
            SPAWN(854, layer_33c, 3);
        }
        if (sequence_id_13e == 5 || sequence_id_13e == 6)
            scale_y_120 = scale_x_11c = 0.1f;
        if (sequence_id_13e == 7)
            ROUND_SCALE(125, 0.01f, 0.75);
        if (sequence_id_13e == 8) {
            field_124 = 75;
            byte_184 = 1;
        }
        if (sequence_id_13e == 9) {
            alpha_113 = static_cast<unsigned char>(params_340[1]);
            color_112 = static_cast<unsigned char>(params_340[1]);
            color_111 = static_cast<unsigned char>(params_340[1]);
            color_110 = static_cast<unsigned char>(params_340[1]);
            scale_y_120 = scale_x_11c = params_340[3];
            field_124 = 75;
        }
        return;
    }
    case 855:
        SELECT();
        if (sequence_id_13e <= 4) {
            field_370 = x_ec;
            field_374 = y_f0;
            field_378 = 1;
        }
        if (sequence_id_13e >= 5 && sequence_id_13e <= 9) {
            SCALE(10, 0.1f, 0.5);
        }
        if (sequence_id_13e >= 15 && sequence_id_13e <= 19)
            byte_184 = 1;
        return;
    case 856:
        SELECT();
        if (sequence_id_13e == 0)
            scale_y_120 = scale_x_11c = 0.1f;
        if (sequence_id_13e == 2 || sequence_id_13e == 4) {
            rotation_12c = random_float(360);
            SCALE(75, 0.01f, 1.0);
            MOVE();
        }
        if (sequence_id_13e == 3) {
            MOVE();
            scale_y_120 = scale_x_11c = 0.1f;
        }
        if (sequence_id_13e == 5) {
            MOVE();
            byte_184 = 1;
            SCALE(20, 0.01f, 0.9f);
        }
        return;
    case 857:
        SELECT();
        if (sequence_id_13e == 0 || sequence_id_13e == 1) {
            field_370 = x_ec;
            field_374 = y_f0;
            field_378 = 8;
            replace_secondary(static_cast<unsigned short>(992 + (sequence_id_13e == 1)), 20, 20, 1, 2);
        }
        if (sequence_id_13e == 2 || sequence_id_13e == 3)
            field_370 = 1;
        if (sequence_id_13e == 4 || sequence_id_13e == 5)
            byte_184 = 1;
        if (sequence_id_13e == 6 || sequence_id_13e == 7)
            ROUND_SCALE(5, 0.1f, 1.0);
        if (sequence_id_13e == 8 || sequence_id_13e == 9)
            field_370 = 1;
        if (sequence_id_13e == 10 || sequence_id_13e == 11)
            ROUND_SCALE(10, 0.1f, 0.5);
        return;
    case 860:
        SELECT();
        if (sequence_id_13e == 0) {
            alpha_113 = 0;
            field_370 = 1;
        }
        return;
    case 861:
        word_344 = 1;
        rotation_12c = params_340[0];
        SELECT();
        if (sequence_id_13e == 0) {
            field_124 = random_float(180) - 90.0;
            field_128 = random_float(180) - 90.0;
            rotation_12c = random_float(180) - 90.0;
        }
        return;
    case 890:
        word_344 = 1;
        return;
    case 900:
        rotation_12c = params_340[0];
        SELECT();
        if (sequence_id_13e == 0 || sequence_id_13e == 2) {
            byte_184 = 1;
            rotation_12c = random_float(360);
            MOVE();
            field_370 = random_float(10) - 5.0;
            switch (g_match_identifier) {
            case 3: word_36a = 90; break;
            case 2: word_36a = 85; break;
            case 1: word_36a = 75; break;
            case 0: word_36a = 60; break;
            }
        }
        if (sequence_id_13e == 1 || sequence_id_13e == 3) {
            MOVE();
            rotation_12c = random_float(360);
            field_370 = random_float(10) - 5.0;
            SCALE(10, 0.1f, 0.75);
        }
        if (sequence_id_13e == 4 || sequence_id_13e == 5) {
            MOVE();
            rotation_12c = random_float(360);
            field_370 = random_float(10) - 5.0;
            SCALE(10, 0.1f, 0.5);
        }
        return;
    case 910:
        SELECT();
        if (sequence_id_13e == 0)
            scale_y_120 = scale_x_11c = 0.1f;
        if (sequence_id_13e == 2 || sequence_id_13e == 4) {
            rotation_12c = random_float(360);
            SCALE(75, 0.01f, 1.0);
            MOVE();
        }
        if (sequence_id_13e == 3) {
            MOVE();
            scale_y_120 = scale_x_11c = 0.1f;
        }
        if (sequence_id_13e == 5) {
            MOVE();
            byte_184 = 1;
            SCALE(20, 0.01f, 0.9f);
        }
        return;
    case 920:
        SELECT();
        if (sequence_id_13e == 0)
            field_128 = 90;
        if (sequence_id_13e == 7 || sequence_id_13e == 8) {
            MOVE();
            SCALE(6, 0.1f, 0.75);
        }
        if (sequence_id_13e == 9 || sequence_id_13e == 10) {
            rotation_12c = random_float(360);
            MOVE();
            SCALE(6, 0.1f, 0.75);
        }
        return;
    case 980:
        continue_action_980();
        return;
    case 998:
        rotation_12c = 0;
        field_128 = 60;
        return;
    }
}

#undef ROUND_SCALE
#undef SCALE
#undef UNSPAWN
#undef SPAWN
#undef MOVE
#undef SELECT

} // namespace th105
