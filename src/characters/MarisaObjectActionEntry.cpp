#include "characters/MarisaObjectActionEntry.hpp"

// JP1.06a 0x004C8050: MarisaObject primary slot +0x3C action entry initializer.
// Evidence: docs/MARISA_OBJECT_ENTRY_2026_10_24.md.
namespace th105 {

#define SELECT() select_sequence(static_cast<int>(params_340[2]))
#define FRAME() select_frame(static_cast<int>(params_340[3]))
#define MOVE() motion_004.set_components(params_340[0], params_340[1])
#define SPAWN(a, l, c) spawn_parented(a, x_ec, y_f0, static_cast<unsigned char>(facing_104), l, reinterpret_cast<const unsigned *>(payload), c)
#define UNSPAWN(a, l, c) spawn_unparented(a, x_ec, y_f0, static_cast<unsigned char>(facing_104), l, reinterpret_cast<const unsigned *>(payload), c)

__forceinline static float random_float(int n) {
    return static_cast<float>(static_cast<unsigned>(selector_random_roll(n)));
}

__forceinline static float modulo_float(unsigned n) {
    return static_cast<float>(mt19937_next_u32() % n);
}

void MarisaObjectEntryView::initialize_action_entry() {
    velocity_x_f4 = 0;
    velocity_y_f8 = 0;
    field_370 = 0;
    field_374 = 0;
    field_378 = 0;
    field_37c = 0;
    word_384 = 0;
    field_380 = 0;
    word_386 = 0;
    byte_184 = 0;
    word_364 = 0;
    word_366 = 0;
    word_368 = 0;
    word_36a = 0;
    word_36c = 0;
    switch (action_id_13c) {
    case 800:
        scale_y_120 = scale_x_11c = 2;
        byte_184 = 1;
        rotation_12c = params_340[0];
        SELECT();
        if (sequence_id_13e > 1 && sequence_id_13e < 6)
            scale_y_120 = scale_x_11c = 1;
        if (sequence_id_13e == 7) {
            scale_y_120 = scale_x_11c = static_cast<float>(random_float(200) * static_cast<double>(0.01f) + 2.0);
            rotation_12c = random_float(360);
            float const magnitude = static_cast<float>(random_float(15) * static_cast<double>(0.1f) + 10.0);
            params_340[1] = magnitude;
        }
        return;
    case 801:
        byte_184 = 1;
        SELECT();
        if (sequence_id_13e == 0)
            replace_secondary(989, 20, 6, 2, 2);
        if (sequence_id_13e == 1)
            replace_secondary(989, 20, 6, 2, 2);
        if (sequence_id_13e == 2) {
            unsigned const roll = selector_random_roll(80);
            rotation_12c = static_cast<float>(static_cast<float>(roll) + params_340[0] - 40.0);
        }
        if (sequence_id_13e == 3)
            byte_184 = 3;
        if (sequence_id_13e == 4)
            byte_184 = 5;
        if (sequence_id_13e == 5) {
            scale_y_120 = scale_x_11c = static_cast<float>(random_float(200) * static_cast<double>(0.01f) + 2.0);
            rotation_12c = random_float(360);
            float const magnitude = static_cast<float>(random_float(15) * static_cast<double>(0.1f) + 10.0);
            params_340[1] = magnitude;
            unsigned const heading = selector_random_roll(360);
            params_340[0] = static_cast<float>(heading);
        }
        return;
    case 802:
        byte_184 = 1;
        SELECT();
        if (sequence_id_13e == 0) {
            velocity_x_f4 = 6;
            velocity_y_f8 = 12.5f;
        }
        if (sequence_id_13e == 2) {
            field_370 = static_cast<float>(random_float(10) - 5.0);
            scale_y_120 = scale_x_11c = static_cast<float>(random_float(200) * static_cast<double>(0.01f) + 1.0);
            rotation_12c = random_float(360);
            float const magnitude = static_cast<float>(random_float(15) * static_cast<double>(0.1f) + 15.0);
            params_340[1] = magnitude;
            unsigned const heading = selector_random_roll(360);
            params_340[0] = static_cast<float>(heading);
        }
        if (sequence_id_13e == 3) {
            field_370 = static_cast<float>(random_float(10) - 5.0);
            scale_y_120 = scale_x_11c = static_cast<float>(random_float(200) * static_cast<double>(0.01f) + 1.0);
            rotation_12c = random_float(360);
            float const magnitude = static_cast<float>(random_float(15) * static_cast<double>(0.1f) + 15.0);
            params_340[1] = magnitude;
            unsigned const heading = selector_random_roll(360);
            params_340[0] = static_cast<float>(heading);
        }
        return;
    case 803:
        field_108 = -40;
        byte_184 = 10;
        return;
    case 804:
        byte_184 = 1;
        return;
    case 809:
        scale_x_11c = params_340[1];
        scale_y_120 = params_340[1];
        color_a_113 = 128;
        SELECT();
        rotation_12c = params_340[0];
        return;
    case 810:
        rotation_12c = random_float(360);
        SELECT();
        scale_y_120 = scale_x_11c = static_cast<float>(random_float(50) * static_cast<double>(0.01f) + 0.5);
        return;
    case 811: {
        float payload[4];
        byte_17c = 4;
        SELECT();
        if (sequence_id_13e == 0) {
            field_370 = 5;
            byte_184 = 1;
            for (int n = 0; n < 16; ++n) {
                payload[0] = static_cast<float>(80.0 - random_float(160));
                payload[1] = static_cast<float>(random_float(250) * static_cast<double>(0.1f) + 10.0);
                payload[2] = 3;
                payload[3] = random_float(45);
                UNSPAWN(811, 1, 4);
            }
            payload[0] = 0;
            payload[1] = 0;
            payload[2] = 4;
            payload[3] = 0;
            UNSPAWN(811, 1, 4);
            MOVE();
            rotation_12c = params_340[0];
        }
        if (sequence_id_13e == 2)
            field_370 = 1;
        if (sequence_id_13e == 3) {
            rotation_12c = random_float(360);
            scale_y_120 = scale_x_11c = static_cast<float>(random_float(100) * static_cast<double>(0.04f) + 1.0);
            field_370 = static_cast<float>(random_float(20) - 10.0);
            field_374 = static_cast<float>(random_float(20) + 5.0);
        }
        if (sequence_id_13e == 4)
            field_370 = 1;
        if (sequence_id_13e == 5) {
            scale_y_120 = scale_x_11c = static_cast<float>(modulo_float(100) * static_cast<double>(0.01f) + 1.0);
            rotation_12c = modulo_float(360);
        }
        return;
    }
    case 812:
        byte_17c = 8;
        byte_184 = 4;
        SELECT();
        return;
    case 817:
        byte_17c = 9;
        rotation_12c = params_340[0];
        SELECT();
        if (sequence_id_13e == 0) {
            byte_184 = 1;
            MOVE();
        }
        if (sequence_id_13e == 1 || sequence_id_13e == 6)
            byte_184 = 6;
        if (sequence_id_13e == 5) {
            scale_y_120 = scale_x_11c = static_cast<float>(modulo_float(100) * static_cast<double>(0.01f) + 1.0);
            rotation_12c = modulo_float(360);
        }
        return;
    case 820: {
        float payload[3];
        byte_17c = 2;
        byte_184 = 1;
        SELECT();
        if (sequence_id_13e == 0) {
            velocity_y_f8 = 10;
            velocity_x_f4 = params_340[0];
            payload[0] = 0;
            payload[1] = 0;
            payload[2] = 7;
            SPAWN(820, -1, 3);
        }
        if (sequence_id_13e == 1) {
            velocity_y_f8 = -25;
            velocity_x_f4 = 5;
            payload[0] = 0;
            payload[1] = 0;
            payload[2] = 7;
            SPAWN(820, -1, 3);
        }
        if (sequence_id_13e == 5) {
            scale_y_120 = scale_x_11c = static_cast<float>(modulo_float(100) * static_cast<double>(0.01f) + 1.0);
            rotation_12c = modulo_float(360);
        }
        return;
    }
    case 821: {
        float payload[1];
        byte_17c = 6;
        byte_184 = 1;
        select_sequence(static_cast<int>(params_340[0]));
        if (sequence_id_13e <= 2) {
            velocity_x_f4 = 6;
            velocity_y_f8 = 4.5f;
        }
        if (sequence_id_13e == 5) {
            velocity_y_f8 = params_340[1];
            payload[0] = 7;
            UNSPAWN(821, 1, 1);
            payload[0] = 8;
            UNSPAWN(821, -1, 1);
        }
        if (sequence_id_13e == 6)
            velocity_y_f8 = 0;
        return;
    }
    case 822: {
        float payload[3];
        byte_17c = 10;
        SELECT();
        word_384 = 0;
        if (sequence_id_13e <= 5) {
            payload[0] = 0;
            payload[1] = 0;
            payload[2] = 12;
            SPAWN(822, -1, 3);
        } else {
            rotation_12c = params_340[0];
        }
        if (sequence_id_13e == 6) {
            byte_184 = 1;
            payload[0] = params_340[0];
            payload[1] = 0;
            payload[2] = 7;
            SPAWN(822, -1, 3);
            payload[2] = 8;
            SPAWN(822, -1, 3);
        }
        return;
    }
    case 825:
        byte_17c = 3;
        byte_184 = 1;
        SELECT();
        if (sequence_id_13e <= 3)
            replace_secondary(sequence_id_13e + 991, 20, 6, 2, 2);
        word_364 = 0;
        return;
    case 826:
        byte_17c = 7;
        byte_184 = 15;
        SELECT();
        if (sequence_id_13e == 0) {
            field_108 = -60;
            field_10c = 0;
            scale_y_120 = 1.2f;
        }
        if (sequence_id_13e == 6) {
            field_108 = -60;
            field_10c = 0;
            scale_y_120 = 1.8f;
        }
        return;
    case 827:
        field_374 = 255;
        byte_17c = 11;
        SELECT();
        field_180 = 0;
        if (sequence_id_13e == 6)
            byte_184 = 1;
        if (sequence_id_13e == 1) {
            scale_x_11c = 0;
            scale_y_120 = 0;
        }
        if (sequence_id_13e == 5) {
            float product = static_cast<float>(random_float(150) * static_cast<double>(0.01f));
            scale_y_120 = scale_x_11c = static_cast<float>(product + 1.0);
        }
        return;
    case 848:
        rotation_12c = params_340[0];
        SELECT();
        if (sequence_id_13e == 2) {
            rotation_12c = params_340[0];
            if (static_cast<unsigned>(selector_random_roll(100)) <= 49)
                field_374 = 1;
            else
                field_374 = -1;
        }
        return;
    case 849:
        rotation_12c = params_340[0];
        SELECT();
        if (sequence_id_13e == 2)
            scale_y_120 = scale_x_11c = 2;
        if (sequence_id_13e == 3 || sequence_id_13e == 4 || sequence_id_13e == 5) {
            byte_17c = 5;
            byte_184 = 5;
        }
        return;
    case 850:
        byte_184 = 1;
        scale_x_11c = 3;
        scale_y_120 = 1.5f;
        SELECT();
        if (sequence_id_13e == 2)
            scale_y_120 = scale_x_11c = 2;
        return;
    case 851:
        scale_x_11c = 10;
        scale_y_120 = 0;
        SELECT();
        if (sequence_id_13e == 2)
            scale_y_120 = scale_x_11c = 2;
        return;
    case 852:
        scale_x_11c = 4;
        scale_y_120 = 0;
        rotation_12c = -30;
        SELECT();
        if (sequence_id_13e == 2)
            scale_y_120 = scale_x_11c = 3;
        if (sequence_id_13e == 5) {
            scale_x_11c = 1;
            scale_y_120 = 1;
            field_124 = static_cast<float>(modulo_float(20) - 50.0);
            field_128 = static_cast<float>(modulo_float(20) + 50.0);
            rotation_12c = modulo_float(360);
        }
        return;
    case 853:
        scale_x_11c = 4;
        scale_y_120 = 0;
        rotation_12c = params_340[0];
        SELECT();
        if (sequence_id_13e == 0 || sequence_id_13e == 4) {
            replace_auxiliary(995);
            aux_154->field_f8 = 22;
            aux_154->field_fc = 22;
            aux_154->field_e8 = 640;
            aux_154->field_ec = 0;
            aux_154->facing_104 = static_cast<unsigned char>(facing_104);
        }
        if (sequence_id_13e == 2)
            scale_y_120 = scale_x_11c = 3;
        if (sequence_id_13e == 5) {
            scale_x_11c = 1;
            scale_y_120 = 1;
            field_124 = facing_104 * params_340[0];
            field_128 = static_cast<float>(modulo_float(20) + 50.0);
            rotation_12c = modulo_float(360);
        }
        if (sequence_id_13e == 10) {
            word_344 = 1;
            field_370 = 1;
            scale_x_11c = 0;
            scale_y_120 = 0;
            field_124 = 75;
        }
        if (sequence_id_13e == 11) {
            word_344 = 1;
            scale_y_120 = scale_x_11c = params_340[1];
            field_124 = 75;
        }
        return;
    case 854:
        scale_x_11c = 10;
        byte_184 = 1;
        scale_y_120 = 1;
        rotation_12c = params_340[0];
        return;
    case 855:
        scale_x_11c = 2;
        byte_184 = 1;
        scale_y_120 = 1;
        return;
    case 856:
        SELECT();
        if (sequence_id_13e == 6) {
            field_180 = 0;
            byte_184 = 1;
        }
        return;
    case 857:
        rotation_12c = params_340[0];
        SELECT();
        return;
    case 858:
        word_344 = 1;
        SELECT();
        if (sequence_id_13e == 4) {
            byte_184 = 1;
            field_180 = 0;
        }
        if (sequence_id_13e == 5)
            rotation_12c = modulo_float(360);
        return;
    case 859: {
        float payload[4];
        if (static_cast<unsigned>(selector_random_roll(100)) <= 50)
            field_370 = 8;
        else
            field_370 = -8;
        SELECT();
        FRAME();
        if (sequence_id_13e < 4 && frame_id_140 == 0) {
            rotation_12c = random_float(360);
            payload[0] = 0;
            payload[1] = 0;
            payload[2] = 4;
            payload[3] = sequence_id_13e;
            byte_184 = 1;
            field_180 = 0;
            owner_348->spawn_owned(859, x_ec, y_f0, static_cast<unsigned char>(facing_104), 1, reinterpret_cast<const unsigned *>(payload), 4);
        }
        if (sequence_id_13e < 4 && frame_id_140 == 1)
            rotation_12c = params_340[0];
        return;
    }
    case 860: {
        float payload[4];
        SELECT();
        FRAME();
        if (sequence_id_13e == 0) {
            field_370 = 5;
            payload[0] = 0;
            payload[1] = 0;
            payload[2] = 3;
            payload[3] = 0;
            byte_184 = 6;
            UNSPAWN(860, 1, 4);
            payload[2] = 4;
            payload[3] = 0;
            SPAWN(860, 1, 4);
        }
        if (sequence_id_13e == 2) {
            rotation_12c = random_float(360);
            scale_y_120 = scale_x_11c = static_cast<float>(random_float(100) * static_cast<double>(0.01f) + 0.5);
            unsigned const heading = selector_random_roll(360);
            params_340[0] = static_cast<float>(heading);
            unsigned const magnitude = selector_random_roll(30) + 10;
            params_340[1] = static_cast<float>(magnitude);
            field_370 = static_cast<float>(random_float(20) - 10.0);
            field_374 = static_cast<float>(random_float(20) + 5.0);
        }
        if (sequence_id_13e == 4)
            field_370 = 5;
        return;
    }
    case 861:
        SELECT();
        FRAME();
        if (sequence_id_13e < 4 && frame_id_140 == 0) {
            rotation_12c = random_float(360);
            byte_184 = 1;
            field_180 = 0;
            word_364 = 0;
        }
        if (sequence_id_13e < 4 && frame_id_140 == 1) {
            rotation_12c = random_float(360);
            scale_y_120 = scale_x_11c = static_cast<float>(random_float(100) * static_cast<double>(0.01f) + 0.5);
        }
        if (sequence_id_13e == 5)
            field_370 = 0.75f;
        return;
    case 863: {
        float payload[4];
        SELECT();
        if (sequence_id_13e == 0) {
            velocity_y_f8 = 10;
            velocity_x_f4 = static_cast<float>(((owner_348->target_170->x_ec - x_ec) / 50.0) * facing_104);
        }
        if (sequence_id_13e == 1) {
            velocity_y_f8 = -25;
            velocity_x_f4 = 5;
        }
        if (sequence_id_13e == 3) {
            field_180 = 0;
            field_370 = 1;
            byte_184 = 1;
            for (int n = 0; n < 3; ++n) {
                payload[0] = -modulo_float(180);
                payload[1] = static_cast<float>(modulo_float(50) * static_cast<double>(0.1f) + 15.0);
                payload[2] = 5;
                payload[3] = random_float(15);
                if (payload[0] < 0)
                    word_364 = 1;
                else
                    word_364 = -1;
                spawn_unparented(863, static_cast<float>(static_cast<int>(facing_104 * time_counter_144 * 20) + x_ec), y_f0, static_cast<unsigned char>(facing_104), static_cast<unsigned char>(word_364), reinterpret_cast<const unsigned *>(payload), 4);
            }
        }
        if (sequence_id_13e == 4)
            field_370 = 1;
        if (sequence_id_13e == 5) {
            scale_y_120 = scale_x_11c = static_cast<float>(modulo_float(100) * static_cast<double>(0.01f) + 1.0);
            rotation_12c = modulo_float(360);
        }
        return;
    }
    case 865:
        SELECT();
        if (sequence_id_13e == 8) {
            double const heading = params_340[0];
            byte_184 = 1;
            rotation_12c = static_cast<float>(heading);
        }
        if (sequence_id_13e == 19) {
            scale_x_11c = 2;
            byte_184 = 1;
            if (related_34c)
                rotation_12c = static_cast<float>(lookup_orientation_sine_quantized_abs(static_cast<float>(-related_34c->params_340[0] - owner_348->field_7ac)) * -4.0);
            scale_y_120 = 0.1f;
        }
        return;
    case 869: {
        float payload[4];
        rotation_12c = params_340[0];
        SELECT();
        if (sequence_id_13e == 1 || sequence_id_13e == 3 || sequence_id_13e == 5)
            scale_x_11c = 10;
        if (sequence_id_13e == 2)
            scale_x_11c = 10;
        if (sequence_id_13e == 4)
            scale_x_11c = 6;
        if (sequence_id_13e == 6)
            scale_x_11c = 4;
        if (sequence_id_13e == 10) {
            scale_x_11c = 10;
            scale_y_120 = 0;
        }
        if (sequence_id_13e == 11) {
            payload[0] = params_340[0];
            payload[1] = 0;
            payload[2] = 10;
            SPAWN(869, 1, 3);
            payload[1] = 5;
            payload[2] = 9;
            payload[3] = 0.2f;
            SPAWN(869, 1, 4);
            payload[1] = 15;
            payload[3] = 0.4f;
            SPAWN(869, 1, 4);
        }
        if (sequence_id_13e == 12)
            scale_y_120 = scale_x_11c = static_cast<float>(random_float(5) * static_cast<double>(0.1f) + 0.5);
        return;
    }
    case 900: {
        float payload[4];
        SELECT();
        if (sequence_id_13e <= 3) {
            rotation_12c = random_float(360);
            byte_184 = 1;
            field_370 = target_170->x_ec;
            field_374 = static_cast<float>(target_170->y_f0 + 100.0);
            replace_secondary(sequence_id_13e + 991, 30, 10, 1, 2);
            payload[0] = 0;
            payload[1] = 0;
            payload[2] = static_cast<float>(sequence_id_13e + 4);
            payload[3] = 0;
            UNSPAWN(900, 1, 4);
            field_378 = static_cast<float>(random_float(10) - 5.0);
        }
        if (sequence_id_13e == 12) {
            switch (g_match_identifier) {
            case 3: word_366 = 240; break;
            case 2: word_366 = 180; break;
            case 0: case 1: word_366 = 120; break;
            }
        }
        if (sequence_id_13e == 13) {
            byte_184 = 0;
            scale_y_120 = scale_x_11c = 0.1f;
        }
        if (sequence_id_13e >= 14 && sequence_id_13e <= 17) {
            rotation_12c = random_float(360);
            scale_y_120 = scale_x_11c = static_cast<float>(random_float(50) * static_cast<double>(0.01f) + 0.75);
        }
        if (sequence_id_13e == 18)
            byte_184 = 1;
        return;
    }
    case 901:
        SELECT();
        if (sequence_id_13e == 8) {
            double const heading = params_340[0];
            byte_184 = 1;
            rotation_12c = static_cast<float>(heading);
        }
        if (sequence_id_13e >= 11 && sequence_id_13e <= 14) {
            rotation_12c = random_float(360);
            byte_184 = 1;
        }
        if (sequence_id_13e >= 15 && sequence_id_13e <= 18)
            rotation_12c = params_340[0];
        if (sequence_id_13e == 19) {
            scale_x_11c = 2;
            byte_184 = 0;
            rotation_12c = params_340[0];
            scale_y_120 = 0.1f;
        }
        return;
    case 902:
        byte_184 = 1;
        SELECT();
        if (sequence_id_13e == 1) {
            scale_y_120 = scale_x_11c = static_cast<float>(modulo_float(100) * static_cast<double>(0.01f) + 1.0);
            rotation_12c = modulo_float(360);
        }
        return;
    case 910: {
        float payload[3];
        rotation_12c = params_340[0];
        SELECT();
        if (sequence_id_13e == 1) {
            velocity_x_f4 = 0;
            velocity_y_f8 = 0;
            payload[0] = 0;
            payload[1] = 0;
            payload[2] = 2;
            SPAWN(910, 1, 3);
        }
        if (sequence_id_13e == 3) {
            payload[0] = 0;
            payload[1] = 0;
            payload[2] = 4;
            SPAWN(910, 1, 3);
        }
        if (sequence_id_13e == 4)
            byte_184 = 15;
        if (sequence_id_13e == 5) {
            field_108 = 0;
            field_10c = 95;
            rotation_12c = params_340[0];
        }
        if (sequence_id_13e == 6) {
            payload[0] = 0;
            payload[1] = 0;
            payload[2] = 7;
            SPAWN(910, 1, 3);
        }
        if (sequence_id_13e == 8) {
            color_r_112 = 0;
            color_g_111 = 48;
        }
        return;
    }
    case 912:
        byte_184 = 1;
        rotation_12c = params_340[0];
        SELECT();
        FRAME();
        word_364 = 0;
        return;
    case 913:
        color_a_113 = 255;
        scale_x_11c = 1;
        color_r_112 = 255;
        color_g_111 = 255;
        scale_y_120 = 1;
        color_b_110 = 255;
        byte_184 = 1;
        field_180 = 0;
        rotation_12c = params_340[0];
        SELECT();
        FRAME();
        if (sequence_id_13e <= 3) {
            scale_x_11c = 0.5f;
            scale_y_120 = 0.5f;
            field_370 = static_cast<float>(random_float(1) * 16.0 - 8.0);
            MOVE();
        }
        return;
    case 920: {
        float payload[4];
        rotation_12c = params_340[0];
        SELECT();
        if (sequence_id_13e == 1 || sequence_id_13e == 3 || sequence_id_13e == 5)
            scale_x_11c = 10;
        if (sequence_id_13e == 2)
            scale_x_11c = 10;
        if (sequence_id_13e == 4)
            scale_x_11c = 6;
        if (sequence_id_13e == 6)
            scale_x_11c = 4;
        if (sequence_id_13e == 10) {
            scale_x_11c = 10;
            scale_y_120 = 0;
        }
        if (sequence_id_13e == 11) {
            payload[0] = params_340[0];
            payload[1] = 0;
            payload[2] = 10;
            SPAWN(920, 1, 3);
            payload[1] = 5;
            payload[2] = 9;
            payload[3] = 0.2f;
            SPAWN(920, 1, 4);
            payload[1] = 15;
            payload[3] = 0.4f;
            SPAWN(920, 1, 4);
        }
        if (sequence_id_13e == 12)
            scale_y_120 = scale_x_11c = static_cast<float>(random_float(5) * static_cast<double>(0.1f) + 0.5);
        return;
    }
    case 921:
        rotation_12c = random_float(360);
        SELECT();
        byte_184 = 1;
        MOVE();
        scale_y_120 = scale_x_11c = static_cast<float>(random_float(50) * static_cast<double>(0.01f) + 0.75);
        return;
    case 989: {
        float payload[3];
        byte_184 = 1;
        rotation_12c = params_340[0];
        SELECT();
        if (sequence_id_13e == 0) {
            payload[0] = 0;
            payload[1] = 0;
            payload[2] = 1;
            SPAWN(989, 1, 3);
            color_r_112 = 0;
            color_g_111 = 0;
            color_b_110 = 0;
        }
        if (sequence_id_13e == 1)
            color_a_113 = 0;
        return;
    }
    case 980:
        continue_action_980();
        return;
    case 990:
        byte_134 = 0;
        return;
    case 998:
        rotation_12c = 0;
        field_128 = 60;
        return;
    case 999:
        SELECT();
        if (sequence_id_13e == 4) {
            velocity_x_f4 = params_340[0];
            velocity_y_f8 = params_340[1];
        }
        return;
    }
}

#undef UNSPAWN
#undef SPAWN
#undef MOVE
#undef FRAME
#undef SELECT

} // namespace th105
