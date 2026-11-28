// JP1.06a 0x00578000: YuyukoObject primary slot +0x3C action entry initializer.
// See docs/YUYUKO_OBJECT_ENTRY_2026_10_24.md.
#include "characters/YuyukoObjectActionEntry.hpp"

namespace th105 {

#define SELECT() select_sequence(static_cast<int>(params_340[2]))
#define MOVE() motion_004.set_components(params_340[0], params_340[1])
#define SPAWN(a, l, c) spawn_parented(a, x_ec, y_f0, static_cast<unsigned char>(facing_104), l, reinterpret_cast<const unsigned *>(payload), c)
#define UNSPAWN(a, l, c) spawn_unparented(a, x_ec, y_f0, static_cast<unsigned char>(facing_104), l, reinterpret_cast<const unsigned *>(payload), c)
#define SCALE(n, factor, base) scale_y_120 = scale_x_11c = static_cast<float>(random_float(n) * static_cast<double>(factor) + static_cast<double>(base))
#define ROUND_SCALE(n, factor, base) { float const product = random_float(n) * static_cast<double>(factor); scale_y_120 = scale_x_11c = static_cast<float>(product + static_cast<double>(base)); }
#define JITTER() { float const product = random_float(100) * static_cast<double>(0.1f); field_370 = product - 5.0; }

__forceinline static float random_float(int n) {
    return static_cast<float>(static_cast<unsigned>(selector_random_roll(n)));
}

void YuyukoObjectEntryView::initialize_action_entry() {
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
    case 800: {
        float payload[3];
        byte_184 = 1;
        rotation_12c = params_340[0];
        SELECT();
        if (sequence_id_13e >= 0 && sequence_id_13e <= 3) {
            scale_y_120 = scale_x_11c = 0.1f;
            payload[0] = 0;
            payload[1] = 0;
            payload[2] = sequence_id_13e + 8;
            SPAWN(800, -1, 3);
        }
        if (sequence_id_13e >= 4 && sequence_id_13e <= 7) {
            JITTER();
            MOVE();
            SCALE(10, 0.1f, 0.5);
        }
        if (sequence_id_13e >= 12 && sequence_id_13e <= 15) {
            payload[0] = 0;
            payload[1] = 0;
            payload[2] = sequence_id_13e - 4;
            SPAWN(800, -1, 3);
        }
        return;
    }
    case 801:
        SELECT();
        if (sequence_id_13e == 1) {
            MOVE();
            byte_184 = 1;
        }
        if (sequence_id_13e == 2) {
            velocity_y_f8 = y_f0;
            velocity_x_f4 = 0;
        }
        if (sequence_id_13e == 3)
            byte_184 = 3;
        if (sequence_id_13e == 4)
            velocity_y_f8 = 2;
        if (sequence_id_13e == 5) {
            MOVE();
            byte_184 = 1;
        }
        return;
    case 810: {
        float payload[3];
        byte_184 = 1;
        rotation_12c = params_340[0];
        byte_17c = 0;
        SELECT();
        if (sequence_id_13e >= 0 && sequence_id_13e <= 3) {
            payload[0] = 0;
            payload[1] = 0;
            payload[2] = sequence_id_13e + 8;
            SPAWN(810, -1, 3);
        }
        if (sequence_id_13e >= 4 && sequence_id_13e <= 7) {
            JITTER();
            JITTER();
            MOVE();
            SCALE(10, 0.1f, 0.5);
        }
        if (sequence_id_13e == 13)
            velocity_y_f8 = 5;
        return;
    }
    case 811: {
        float payload[3];
        rotation_12c = params_340[0];
        byte_17c = 4;
        SELECT();
        if (sequence_id_13e >= 0 && sequence_id_13e <= 3) {
            payload[0] = 0;
            payload[1] = 0;
            payload[2] = sequence_id_13e + 8;
            SPAWN(811, 1, 3);
        }
        if (sequence_id_13e >= 4 && sequence_id_13e <= 7) {
            JITTER();
            JITTER();
            MOVE();
            SCALE(10, 0.1f, 0.5);
        }
        if (sequence_id_13e >= 8 && sequence_id_13e <= 11) {
            byte_184 = 1;
            field_370 = x_ec;
            field_374 = y_f0;
            scale_x_11c = 0;
            scale_y_120 = 2;
        }
        if (sequence_id_13e == 13)
            velocity_y_f8 = 5;
        if (sequence_id_13e == 14) {
            if (owner_348->byte_608 <= 1) {
                for (float n = 0; n < 3; n += 1.0) {
                    payload[0] = n * 15.0 - params_340[0];
                    payload[1] = 20;
                    payload[2] = n;
                    SPAWN(811, 1, 3);
                }
                word_36c = 3;
            } else if (owner_348->byte_608 <= 3) {
                for (float n = 0; n < 4; n += 1.0) {
                    payload[0] = n * 15.0 - params_340[0];
                    payload[1] = 20;
                    payload[2] = n;
                    SPAWN(811, 1, 3);
                }
                word_36c = 4;
            } else {
                for (float n = 0; n < 5; n += 1.0) {
                    payload[0] = n * 15.0 - params_340[0];
                    payload[1] = 20;
                    payload[2] = static_cast<int>(n) % 4;
                    SPAWN(811, 1, 3);
                }
                word_36c = 5;
            }
        }
        return;
    }
    case 812:
        rotation_12c = params_340[0];
        byte_17c = 8;
        SELECT();
        if (sequence_id_13e == 1 || sequence_id_13e == 4 || sequence_id_13e == 5)
            byte_184 = 1;
        if (sequence_id_13e == 2) {
            JITTER();
            MOVE();
            SCALE(10, 0.1f, 0.5);
        }
        if (sequence_id_13e == 3) {
            SCALE(10, 0.1f, 0.5);
        }
        return;
    case 815:
        byte_184 = 5;
        byte_17c = 1;
        SELECT();
        if (sequence_id_13e == 1) {
            scale_x_11c = 10;
            scale_y_120 = 0.1f;
        }
        return;
    case 816: {
        float payload[3];
        byte_184 = 1;
        byte_17c = 5;
        rotation_12c = params_340[0];
        SELECT();
        if (sequence_id_13e >= 0 && sequence_id_13e <= 3) {
            SCALE(4, 0.1f, 0.8f);
            payload[0] = 0;
            payload[1] = 0;
            payload[2] = sequence_id_13e + 8;
            SPAWN(816, -1, 3);
        }
        if (sequence_id_13e >= 4 && sequence_id_13e <= 7) {
            JITTER();
            JITTER();
            MOVE();
            SCALE(10, 0.1f, 0.5);
        }
        // The first request leaves payload[1] untouched in the original frame.
        if (sequence_id_13e == 12) {
            MOVE();
            payload[0] = 0;
            payload[2] = 13;
            UNSPAWN(816, 1, 3);
            payload[1] = 0.5f;
            payload[2] = 14;
            UNSPAWN(816, 1, 3);
        }
        if (sequence_id_13e == 15)
            scale_y_120 = scale_x_11c = params_340[1];
        if (sequence_id_13e == 16) {
            alpha_113 = 0;
            byte_184 = 0;
            rotation_12c = params_340[0] + 180.0;
            payload[0] = 0;
            payload[1] = 0;
            payload[2] = 8;
            SPAWN(816, -1, 3);
        }
        return;
    }
    case 820:
        byte_17c = 2;
        byte_184 = 3;
        field_370 = owner_348->x_ec + facing_104 * 50;
        field_374 = owner_348->y_f0 + 170.0;
        field_378 = 1;
        SELECT();
        if (sequence_id_13e == 3)
            velocity_y_f8 = 5;
        return;
    case 821:
        byte_17c = 6;
        SELECT();
        if (sequence_id_13e == 0)
            MOVE();
        if (sequence_id_13e == 1) {
            field_370 = 255;
            byte_184 = 1;
            MOVE();
        }
        if (sequence_id_13e == 3) {
            x_ec = lookup_orientation_cosine_quantized_abs(params_340[0]) * params_340[1] + target_34c->x_ec;
            y_f0 = lookup_orientation_sine_quantized_abs(params_340[0]) * params_340[1] + target_34c->y_f0;
            ROUND_SCALE(10, 0.1f, 0.5);
        }
        return;
    case 825:
        SELECT();
        if (sequence_id_13e == 0) {
            field_124 = 40;
            field_128 = facing_104 * -40;
            rotation_12c = random_float(360);
        }
        if (sequence_id_13e == 1) {
            JITTER();
            JITTER();
            MOVE();
            SCALE(10, 0.1f, 0.5);
        }
        return;
    case 826: {
        float payload[3];
        rotation_12c = params_340[0];
        byte_17c = 7;
        SELECT();
        if (sequence_id_13e == 0) {
            for (int n = 0; n < 8; ++n) {
                payload[0] = random_float(360);
                payload[1] = random_float(50) * static_cast<double>(0.1f) + 5.0;
                payload[2] = 1;
                UNSPAWN(826, 1, 3);
            }
            return;
        }
        if (sequence_id_13e >= 1 && sequence_id_13e <= 4) {
            JITTER();
            JITTER();
            MOVE();
            SCALE(10, 0.1f, 0.5);
        }
        return;
    }
    case 848:
        rotation_12c = params_340[0];
        SELECT();
        if (sequence_id_13e == 3)
            field_124 = facing_104 * 60;
        if (sequence_id_13e == 4)
            field_124 = facing_104 * 20;
        if (sequence_id_13e == 10) {
            field_370 = x_ec - owner_348->x_ec;
            field_374 = y_f0 - owner_348->y_f0;
            velocity_x_f4 = 25;
            velocity_y_f8 = -3;
        }
        if (sequence_id_13e == 11) {
            ROUND_SCALE(5, 0.1f, 0.75);
        }
        if (sequence_id_13e == 12)
            field_124 = facing_104 * 70;
        return;
    case 850: {
        float payload[3];
        byte_184 = 1;
        SELECT();
        if (sequence_id_13e >= 0 && sequence_id_13e <= 3) {
            payload[0] = 0;
            payload[1] = 0;
            payload[2] = sequence_id_13e + 8;
            SPAWN(850, 1, 3);
            params_340[0] = params_340[0] + 30.0;
            field_370 = 2;
        }
        if (sequence_id_13e >= 4 && sequence_id_13e <= 7) {
            JITTER();
            JITTER();
            MOVE();
            SCALE(10, 0.1f, 0.5);
        }
        rotation_12c = params_340[0];
        return;
    }
    case 851:
        SELECT();
        if (sequence_id_13e == 1) {
            replace_secondary(990, 20, 10, 1, 2);
            velocity_x_f4 = params_340[1];
            byte_184 = 1;
            int_144 = static_cast<short>(selector_random_roll(360));
            ROUND_SCALE(50, 0.01f, 1.0);
            field_374 = random_float(5) + 3.0;
        }
        if (sequence_id_13e == 2) {
            rotation_12c = random_float(360);
            ROUND_SCALE(50, 0.01f, 1.0);
        }
        if (sequence_id_13e == 4) {
            scale_y_120 = scale_x_11c = 0;
            field_370 = 1;
        }
        return;
    case 852:
        SELECT();
        if (sequence_id_13e == 0)
            byte_184 = 1;
        if (sequence_id_13e == 1) {
            rotation_12c = random_float(360);
            ROUND_SCALE(50, 0.01f, 1.0);
        }
        if (sequence_id_13e == 2) {
            rotation_12c = random_float(360);
            ROUND_SCALE(50, 0.01f, 1.0);
        }
        if (sequence_id_13e == 3) {
            ROUND_SCALE(100, 0.01f, 1.0);
            word_364 = selector_random_roll(180) + 60;
            field_370 = random_float(360);
            float const product = random_float(20) * static_cast<double>(0.1f);
            field_374 = product + 1.0;
            if (static_cast<unsigned>(selector_random_roll(100)) < 50)
                field_374 = field_374 * -1.0;
            alpha_113 = 0;
        }
        if (sequence_id_13e == 4)
            alpha_113 = 0;
        return;
    case 853: {
        float payload[3];
        byte_184 = 1;
        SELECT();
        if (sequence_id_13e >= 0 && sequence_id_13e <= 3) {
            payload[0] = 0;
            payload[1] = 0;
            payload[2] = sequence_id_13e + 8;
            SPAWN(853, 1, 3);
            params_340[0] = params_340[0] + 30.0;
            field_370 = 2;
        }
        if (sequence_id_13e >= 4 && sequence_id_13e <= 7) {
            JITTER();
            JITTER();
            MOVE();
            SCALE(10, 0.1f, 0.5);
        }
        rotation_12c = params_340[0];
        return;
    }
    case 854:
        SELECT();
        if (sequence_id_13e == 1) {
            float const width = random_float(10) + 10.0;
            int const divisions = selector_random_roll(10) + 5;
            replace_secondary(990, width, divisions, 1, 2);
            velocity_y_f8 = params_340[1];
            byte_184 = 1;
            int_144 = static_cast<short>(selector_random_roll(360));
            ROUND_SCALE(100, 0.01f, 1.0);
            field_374 = random_float(5) + 3.0;
        }
        if (sequence_id_13e == 2) {
            rotation_12c = random_float(360);
            ROUND_SCALE(50, 0.01f, 1.0);
        }
        if (sequence_id_13e == 3) {
            rotation_12c = random_float(360);
            if (static_cast<unsigned>(selector_random_roll(100)) <= 49)
                field_374 = 1;
            else
                field_374 = -1;
        }
        if (sequence_id_13e == 4) {
            scale_y_120 = scale_x_11c = 0;
            field_370 = 1;
        }
        if (sequence_id_13e == 5) {
            JITTER();
            JITTER();
            MOVE();
            SCALE(10, 0.1f, 0.5);
        }
        if (sequence_id_13e == 5) {
            JITTER();
            JITTER();
            MOVE();
            SCALE(10, 0.1f, 0.5);
        }
        return;
    case 855:
        SELECT();
        if (sequence_id_13e == 0)
            byte_184 = 1;
        if (sequence_id_13e == 1) {
            rotation_12c = random_float(360);
            ROUND_SCALE(50, 0.01f, 1.0);
        }
        if (sequence_id_13e == 2) {
            rotation_12c = random_float(360);
            ROUND_SCALE(50, 0.01f, 1.0);
        }
        if (sequence_id_13e == 3) {
            field_370 = random_float(360);
            float const product = random_float(20) * static_cast<double>(0.1f);
            field_374 = product + 1.0;
            field_378 = 200;
            if (static_cast<unsigned>(selector_random_roll(100)) < 50)
                field_374 = field_374 * -1.0;
            alpha_113 = 0;
        }
        if (sequence_id_13e == 4)
            alpha_113 = 0;
        if (sequence_id_13e == 5) {
            JITTER();
            MOVE();
            SCALE(10, 0.1f, 0.5);
        }
        if (sequence_id_13e == 6) {
            MOVE();
            SCALE(10, 0.1f, 0.5);
        }
        if (sequence_id_13e == 7)
            byte_184 = 1;
        if (sequence_id_13e == 9) {
            JITTER();
            MOVE();
            SCALE(15, 0.1f, 1.0);
        }
        return;
    case 856: {
        float payload[3];
        byte_184 = 1;
        rotation_12c = params_340[0];
        SELECT();
        if (sequence_id_13e >= 0 && sequence_id_13e <= 3) {
            payload[0] = 0;
            payload[1] = 0;
            payload[2] = sequence_id_13e + 8;
            SPAWN(856, -1, 3);
        }
        if (sequence_id_13e >= 4 && sequence_id_13e <= 7) {
            JITTER();
            JITTER();
            MOVE();
            SCALE(10, 0.1f, 0.5);
        }
        if (sequence_id_13e == 13)
            velocity_y_f8 = 5;
        return;
    }
    case 857: {
        float payload[3];
        byte_184 = 1;
        rotation_12c = params_340[0];
        SELECT();
        if (sequence_id_13e >= 0 && sequence_id_13e <= 3) {
            SCALE(4, 0.1f, 0.8f);
            payload[0] = 0;
            payload[1] = 0;
            payload[2] = sequence_id_13e + 8;
            SPAWN(816, -1, 3);
        }
        if (sequence_id_13e >= 4 && sequence_id_13e <= 7) {
            JITTER();
            JITTER();
            MOVE();
            SCALE(10, 0.1f, 0.5);
        }
        if (sequence_id_13e == 12) {
            MOVE();
            for (float n = 0; n < 6; n += 1.0) {
                payload[0] = static_cast<float>(static_cast<unsigned>(selector_random_roll(20))) + static_cast<double>(params_340[0]) - 10.0;
                payload[1] = random_float(20) + 10.0;
                payload[2] = 0;
                UNSPAWN(857, -1, 3);
            }
            payload[0] = 0;
            payload[2] = 13;
            UNSPAWN(857, -1, 3);
            payload[1] = 0.5f;
            payload[2] = 15;
            UNSPAWN(857, 1, 3);
        }
        if (sequence_id_13e == 14) {
            scale_y_120 = scale_x_11c = 0.1f;
            word_344 = 1;
            field_370 = 1;
            field_10c = 200;
        }
        return;
    }
    case 858:
        SELECT();
        if (sequence_id_13e == 1) {
            field_378 = 1;
            field_370 = x_ec;
            field_374 = y_f0;
            byte_184 = 1;
            x_ec = lookup_orientation_cosine_quantized_abs(params_340[0] + word_36c * 4) * params_340[1] * facing_104 + field_370;
            y_f0 = lookup_orientation_sine_quantized_abs(params_340[0] + word_36c * 4) * params_340[1] + field_374;
        }
        if (sequence_id_13e == 3) {
            velocity_y_f8 = 5;
            rotation_12c = random_float(360);
            SCALE(4, 0.1f, 0.8f);
        }
        return;
    case 900:
        field_370 = owner_348->x_ec + facing_104 * 50;
        field_374 = owner_348->y_f0 + 170.0;
        field_378 = 1;
        SELECT();
        if (sequence_id_13e == 0)
            alpha_113 = 0;
        if (sequence_id_13e == 3)
            velocity_y_f8 = 5;
        if (sequence_id_13e == 4)
            alpha_113 = 0;
        if (sequence_id_13e == 5)
            rotation_12c = random_float(360);
        return;
    case 901:
        byte_184 = 1;
        rotation_12c = params_340[0];
        SELECT();
        if (sequence_id_13e == 3)
            velocity_y_f8 = 5;
        if (sequence_id_13e == 5)
            rotation_12c = random_float(360);
        return;
    case 902: {
        float payload[3];
        rotation_12c = params_340[0];
        SELECT();
        if (sequence_id_13e >= 0 && sequence_id_13e <= 3) {
            payload[0] = 0;
            payload[1] = 0;
            payload[2] = sequence_id_13e + 8;
            byte_184 = 1;
            SPAWN(902, -1, 3);
        }
        if (sequence_id_13e >= 4 && sequence_id_13e <= 7) {
            JITTER();
            JITTER();
            MOVE();
            SCALE(10, 0.1f, 0.5);
        }
        return;
    }
    case 920:
        rotation_12c = params_340[0];
        SELECT();
        if (sequence_id_13e == 0) {
            field_370 = x_ec;
            field_374 = y_f0;
            x_ec = lookup_orientation_cosine_quantized_abs(-params_340[0]) * params_340[1] * facing_104 + field_370;
            y_f0 = lookup_orientation_sine_quantized_abs(-params_340[0]) * params_340[1] + field_374;
            alpha_113 = 0;
        }
        return;
    case 922:
        SELECT();
        if (sequence_id_13e == 0) {
            scale_y_120 = scale_x_11c = 0.05f;
            field_108 = 0;
            field_10c = 100;
            field_374 = field_370 = 1;
        }
        if (sequence_id_13e == 1) {
            field_370 = 0.4f;
            field_108 = 0;
            field_10c = 100;
        }
        if (sequence_id_13e == 3) {
            SCALE(15, 0.1f, 0.5);
        }
        if (sequence_id_13e == 4) {
            field_370 = 0.6f;
            rotation_12c = random_float(360);
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

#undef JITTER
#undef ROUND_SCALE
#undef SCALE
#undef UNSPAWN
#undef SPAWN
#undef MOVE
#undef SELECT

} // namespace th105
