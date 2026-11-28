#include "characters/SuikaObjectActionEntry.hpp"

// JP1.06a 0x005BD380: SuikaObject primary slot +0x3C action entry initializer.
// See docs/SUIKA_OBJECT_ENTRY_2026_10_24.md.
namespace th105 {

#define SELECT() select_sequence(static_cast<int>(params_340[2]))
#define MOVE() motion_004.set_components(params_340[0], params_340[1])
#define SPAWN(a, l) spawn_unparented(a, x_ec, y_f0, facing_104, l, reinterpret_cast<const unsigned *>(payload), 3)

__forceinline static float random_float(int n) {
    return static_cast<float>(static_cast<unsigned>(selector_random_roll(n)));
}

void SuikaObjectEntryView::initialize_action_entry() {
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
        byte_184 = 1;
        SELECT();
        if (sequence_id_13e == 0) {
            velocity_x_f4 = params_340[0];
            velocity_y_f8 = params_340[1];
        }
        if (sequence_id_13e == 3)
            MOVE();
        if (sequence_id_13e == 5) {
            scale_y_120 = scale_x_11c = static_cast<float>(random_float(10) * static_cast<double>(0.1f) + 1.0);
            rotation_12c = random_float(360);
            field_370 = random_float(40) * static_cast<double>(0.1f) - 2.0;
        }
        return;
    case 801:
        byte_184 = 1;
        SELECT();
        if (sequence_id_13e == 0) {
            velocity_x_f4 = params_340[0];
            velocity_y_f8 = params_340[1];
        }
        if (sequence_id_13e == 1)
            MOVE();
        if (sequence_id_13e == 4)
            MOVE();
        return;
    case 810: {
        float payload[3];
        byte_17c = 0;
        byte_184 = 1;
        rotation_12c = params_340[0];
        MOVE();
        SELECT();
        if (sequence_id_13e == 1 || sequence_id_13e == 5) {
            payload[2] = 3;
            for (float n = 0; n < 4; n += 1.0) {
                payload[0] = random_float(360);
                payload[1] = random_float(8) + 4.0;
                SPAWN(810, 1);
            }
        }
        if (sequence_id_13e == 2) {
            field_124 = random_float(360);
            field_128 = random_float(360);
        }
        if (sequence_id_13e == 3) {
            float product = random_float(100) * static_cast<double>(0.1f);
            field_370 = product - 5.0;
            rotation_12c = random_float(360);
            scale_y_120 = scale_x_11c = static_cast<float>(random_float(10) * static_cast<double>(0.1f) + 1.0);
        }
        return;
    }
    case 811:
        byte_17c = 1;
        byte_184 = 1;
        SELECT();
        if (sequence_id_13e == 0) {
            MOVE();
            if (velocity_x_f4 > 0)
                field_370 = -0.15f;
            else
                field_370 = 0.15f;
        }
        if (sequence_id_13e == 1) {
            rotation_12c = random_float(360);
            scale_y_120 = scale_x_11c = static_cast<float>(random_float(10) * static_cast<double>(0.05f) + 1.0);
        }
        if (sequence_id_13e == 2)
            field_124 = 80;
        if (sequence_id_13e == 3) {
            MOVE();
            if (velocity_x_f4 > 0)
                field_370 = -0.15f;
            else
                field_370 = 0.15f;
        }
        if (sequence_id_13e == 4) {
            MOVE();
            if (velocity_x_f4 > 0)
                field_370 = -0.15f;
            else
                field_370 = 0.15f;
        }
        return;
    case 812:
        byte_17c = 2;
        byte_184 = 1;
        SELECT();
        if (sequence_id_13e == 0) {
            velocity_x_f4 = params_340[0];
            velocity_y_f8 = params_340[1];
            if (velocity_y_f8 > 0)
                field_370 = -0.1f;
            else
                field_370 = 0.1f;
        }
        if (sequence_id_13e == 2)
            MOVE();
        return;
    case 813:
        byte_17c = 3;
        byte_184 = 5;
        SELECT();
        if (sequence_id_13e == 0 || sequence_id_13e == 3) {
            velocity_x_f4 = params_340[0];
            velocity_y_f8 = params_340[1];
        }
        if (sequence_id_13e == 2 || sequence_id_13e == 5)
            rotation_12c = random_float(360);
        return;
    case 815:
        byte_17c = 4;
        byte_184 = 1;
        rotation_12c = params_340[0];
        MOVE();
        SELECT();
        if (sequence_id_13e == 3)
            scale_y_120 = scale_x_11c = params_340[3];
        if (sequence_id_13e == 4) {
            float product = random_float(100) * static_cast<double>(0.1f);
            field_370 = product - 5.0;
            rotation_12c = random_float(360);
            double const delta = random_float(10) * static_cast<double>(0.1f);
            scale_y_120 = scale_x_11c = static_cast<float>(delta + params_340[3]);
        }
        if (sequence_id_13e == 5) {
            float product = random_float(100) * static_cast<double>(0.1f);
            field_370 = product - 5.0;
            rotation_12c = random_float(360);
            double const delta = random_float(10) * static_cast<double>(0.1f);
            scale_y_120 = scale_x_11c = static_cast<float>(delta + params_340[3]);
        }
        if (sequence_id_13e == 10) {
            velocity_x_f4 = 0;
            velocity_y_f8 = 0;
            if (target_34c) {
                x_ec = lookup_orientation_cosine_quantized_abs(params_340[0]) * params_340[1] + target_34c->x_ec;
                y_f0 = lookup_orientation_sine_quantized_abs(params_340[0]) * params_340[1] + target_34c->y_f0;
            }
        }
        return;
    case 816:
        byte_17c = 5;
        rotation_12c = params_340[0];
        SELECT();
        if (sequence_id_13e == 0) {
            byte_184 = 1;
            MOVE();
            if (velocity_x_f4 > 0)
                field_370 = -0.15f;
            else
                field_370 = 0.15f;
        }
        if (sequence_id_13e == 1)
            velocity_y_f8 = 5;
        if (sequence_id_13e == 2) {
            rotation_12c = random_float(360);
            scale_y_120 = scale_x_11c = static_cast<float>(random_float(10) * static_cast<double>(0.05f) + 1.0);
        }
        if (sequence_id_13e == 3)
            field_124 = 80;
        return;
    case 817:
        byte_17c = 6;
        rotation_12c = params_340[0];
        SELECT();
        if (sequence_id_13e == 1 || sequence_id_13e == 2 || sequence_id_13e == 4 || sequence_id_13e == 5) {
            if (sequence_id_13e == 5)
                alpha_113 = 0;
            float product = random_float(50) * static_cast<double>(0.01f);
            scale_y_120 = scale_x_11c = static_cast<float>(product + 1.0);
            field_370 = random_float(10) - 5.0;
        }
        if (sequence_id_13e == 3)
            byte_184 = 1;
        return;
    case 818:
        byte_17c = 7;
        SELECT();
        if (sequence_id_13e == 0 || sequence_id_13e == 3) {
            velocity_x_f4 = params_340[0];
            velocity_y_f8 = params_340[1];
        }
        if (sequence_id_13e == 2 || sequence_id_13e == 5)
            rotation_12c = random_float(360);
        if (sequence_id_13e == 7) {
            byte_184 = 1;
            MOVE();
            scale_y_120 = scale_x_11c = static_cast<float>(random_float(40) * static_cast<double>(0.01f) + static_cast<double>(0.9f));
        }
        return;
    case 821: {
        float payload[3];
        byte_17c = 9;
        SELECT();
        if (sequence_id_13e == 0) {
            byte_184 = 1;
            MOVE();
            payload[0] = 0;
            payload[1] = 0;
            payload[2] = 1;
            SPAWN(821, -1);
        }
        if (sequence_id_13e == 2 || sequence_id_13e == 3 || sequence_id_13e == 8) {
            rotation_12c = params_340[0];
            float product = random_float(25) * static_cast<double>(0.01f);
            scale_y_120 = scale_x_11c = static_cast<float>(product + 1.0);
            field_370 = 0.2f;
        }
        if (sequence_id_13e == 4) {
            rotation_12c = params_340[0];
            float product = random_float(25) * static_cast<double>(0.01f);
            scale_y_120 = scale_x_11c = static_cast<float>(product + 1.0);
            field_370 = random_float(10) - 5.0;
        }
        if (sequence_id_13e == 5 || sequence_id_13e == 8) {
            field_370 = 0.2f;
            field_374 = 0.4f;
        }
        if (sequence_id_13e == 6) {
            byte_184 = 1;
            MOVE();
        }
        return;
    }
    case 848:
        SELECT();
        if (sequence_id_13e == 2)
            rotation_12c = params_340[0];
        return;
    case 850:
        word_344 = 1;
        SELECT();
        if (sequence_id_13e == 0)
            byte_184 = 1;
        if (sequence_id_13e == 1) {
            MOVE();
            float product = random_float(10) * static_cast<double>(0.1f);
            scale_y_120 = scale_x_11c = static_cast<float>(product + 1.0);
            rotation_12c = random_float(360);
        }
        return;
    case 851:
        SELECT();
        if (sequence_id_13e == 0) {
            alpha_113 = 0;
            color_112 = 0;
            color_111 = 0;
        }
        return;
    case 852:
        SELECT();
        return;
    case 853:
        SELECT();
        if (sequence_id_13e == 1) {
            MOVE();
            float product = random_float(10) * static_cast<double>(0.1f);
            scale_y_120 = scale_x_11c = static_cast<float>(product + 1.0);
            rotation_12c = random_float(360);
        }
        return;
    case 854:
        SELECT();
        if (sequence_id_13e == 0)
            alpha_113 = 0;
        if (sequence_id_13e == 1) {
            rotation_12c = random_float(360);
            scale_y_120 = scale_x_11c = static_cast<float>(random_float(10) * static_cast<double>(0.1f) + 0.5);
        }
        return;
    case 855: {
        float payload[3];
        SELECT();
        if (sequence_id_13e == 1) {
            rotation_12c = random_float(360);
            scale_y_120 = scale_x_11c = static_cast<float>(random_float(15) * static_cast<double>(0.1f) + 1.0);
            field_370 = random_float(10);
            if (static_cast<unsigned>(selector_random_roll(100)) <= 50)
                field_370 = field_370 * -1.0;
            word_364 = selector_random_roll(35) + 45;
            MOVE();
        }
        if (sequence_id_13e == 2) {
            rotation_12c = random_float(360);
            field_370 = random_float(10) - 5.0;
        }
        if (sequence_id_13e == 3) {
            byte_184 = 1;
            MOVE();
        }
        if (sequence_id_13e == 5)
            MOVE();
        if (sequence_id_13e == 6) {
            byte_184 = 1;
            payload[2] = 8;
            for (float n = 0; n < 4; n += 1.0) {
                payload[0] = random_float(360);
                payload[1] = random_float(8) + 4.0;
                SPAWN(855, 1);
            }
        }
        if (sequence_id_13e == 7) {
            field_124 = random_float(360);
            field_128 = random_float(360);
        }
        if (sequence_id_13e == 8) {
            float product = random_float(100) * static_cast<double>(0.1f);
            field_370 = product - 5.0;
            rotation_12c = random_float(360);
            scale_y_120 = scale_x_11c = static_cast<float>(random_float(10) * static_cast<double>(0.1f) + 1.0);
        }
        return;
    }
    case 856:
        SELECT();
        if (sequence_id_13e == 0)
            byte_184 = 1;
        if (sequence_id_13e == 1)
            byte_184 = 1;
        if (sequence_id_13e == 2) {
            float product = random_float(15) * static_cast<double>(0.1f);
            scale_y_120 = scale_x_11c = static_cast<float>(product + 0.5);
            rotation_12c = random_float(360);
            alpha_113 = 0;
        }
        if (sequence_id_13e == 3) {
            float product = random_float(20) * static_cast<double>(0.01f);
            scale_y_120 = scale_x_11c = static_cast<float>(product + static_cast<double>(0.8f));
            rotation_12c = random_float(360);
            MOVE();
        }
        return;
    case 857: {
        float payload[3];
        SELECT();
        if (sequence_id_13e == 0 || sequence_id_13e == 9) {
            byte_184 = 1;
            MOVE();
            payload[0] = 0;
            payload[1] = 0;
            payload[2] = 1;
            SPAWN(857, -1);
        }
        if (sequence_id_13e == 2 || sequence_id_13e == 3 || sequence_id_13e == 8) {
            rotation_12c = params_340[0];
            float product = random_float(25) * static_cast<double>(0.01f);
            scale_y_120 = scale_x_11c = static_cast<float>(product + 1.0);
            field_370 = 0.2f;
        }
        if (sequence_id_13e == 4) {
            rotation_12c = params_340[0];
            float product = random_float(25) * static_cast<double>(0.01f);
            scale_y_120 = scale_x_11c = static_cast<float>(product + 1.0);
            field_370 = random_float(10) - 5.0;
        }
        if (sequence_id_13e == 5 || sequence_id_13e == 8 || sequence_id_13e == 10) {
            field_370 = 0.2f;
            field_374 = 0.4f;
        }
        if (sequence_id_13e == 6) {
            byte_184 = 1;
            MOVE();
        }
        return;
    }
    case 858:
        SELECT();
        if (sequence_id_13e == 0) {
            rotation_12c = random_float(360);
            scale_y_120 = scale_x_11c = static_cast<float>(random_float(75) * static_cast<double>(0.01f) + 0.75);
            field_370 = random_float(50) * static_cast<double>(0.1f) - 2.5;
        }
        if (sequence_id_13e == 4)
            rotation_12c = params_340[0];
        return;
    case 900:
        SELECT();
        if (sequence_id_13e == 0) {
            scale_x_11c = 0;
            scale_y_120 = 0;
            rotation_12c = random_float(360);
        }
        if (sequence_id_13e == 1)
            rotation_12c = random_float(360);
        if (sequence_id_13e == 2) {
            byte_184 = 1;
            MOVE();
        }
        return;
    case 901:
        SELECT();
        if (sequence_id_13e == 0) {
            scale_x_11c = 0;
            scale_y_120 = 0;
            rotation_12c = random_float(360);
        }
        if (sequence_id_13e == 1)
            rotation_12c = random_float(360);
        if (sequence_id_13e == 2) {
            byte_184 = 1;
            MOVE();
        }
        return;
    case 910: {
        float payload[3];
        SELECT();
        if (sequence_id_13e == 0) {
            byte_184 = 1;
            MOVE();
            payload[0] = 0;
            payload[1] = 0;
            payload[2] = 1;
            SPAWN(910, -1);
        }
        if (sequence_id_13e == 2 || sequence_id_13e == 3 || sequence_id_13e == 8) {
            rotation_12c = params_340[0];
            float product = random_float(25) * static_cast<double>(0.01f);
            scale_y_120 = scale_x_11c = static_cast<float>(product + 1.0);
            field_370 = 0.2f;
        }
        if (sequence_id_13e == 4) {
            rotation_12c = params_340[0];
            float product = random_float(25) * static_cast<double>(0.01f);
            scale_y_120 = scale_x_11c = static_cast<float>(product + 1.0);
            field_370 = random_float(10) - 5.0;
        }
        if (sequence_id_13e == 5 || sequence_id_13e == 8) {
            field_370 = 0.2f;
            field_374 = 0.4f;
        }
        if (sequence_id_13e == 6) {
            byte_184 = 1;
            MOVE();
        }
        return;
    }
    case 920:
        SELECT();
        if (sequence_id_13e == 2) {
            rotation_12c = random_float(360);
            field_370 = random_float(10) - 5.0;
        }
        return;
    case 921: {
        float payload[3];
        byte_184 = 1;
        rotation_12c = params_340[0];
        MOVE();
        SELECT();
        if (sequence_id_13e == 1) {
            payload[2] = 3;
            for (float n = 0; n < 4; n += 1.0) {
                payload[0] = random_float(360);
                payload[1] = random_float(8) + 4.0;
                SPAWN(921, 1);
            }
        }
        if (sequence_id_13e == 2) {
            field_124 = random_float(360);
            field_128 = random_float(360);
        }
        if (sequence_id_13e == 3) {
            float product = random_float(100) * static_cast<double>(0.1f);
            field_370 = product - 5.0;
            rotation_12c = random_float(360);
            scale_y_120 = scale_x_11c = static_cast<float>(random_float(10) * static_cast<double>(0.1f) + 1.0);
        }
        if (sequence_id_13e == 4) {
            scale_y_120 = scale_x_11c = static_cast<float>(random_float(30) * static_cast<double>(0.01f) + static_cast<double>(0.85f));
            byte_184 = 1;
        }
        return;
    }
    case 930:
        SELECT();
        if (sequence_id_13e == 1) {
            field_370 = random_float(60) * static_cast<double>(0.1f) - 3.0;
            scale_y_120 = scale_x_11c = static_cast<float>(random_float(75) * static_cast<double>(0.01f) + 1.0);
            rotation_12c = random_float(360);
        }
        if (sequence_id_13e == 2) {
            rotation_12c = random_float(360);
            float product = random_float(50) * static_cast<double>(0.01f);
            scale_y_120 = scale_x_11c = static_cast<float>(product + 1.0);
            field_370 = random_float(10) - 5.0;
        }
        if (sequence_id_13e == 4) {
            scale_y_120 = scale_x_11c = 3;
            alpha_113 = 0;
        }
        return;
    case 940:
        rotation_12c = params_340[0];
        MOVE();
        SELECT();
        if (sequence_id_13e <= 2)
            byte_184 = 1;
        if (sequence_id_13e == 4) {
            float product = random_float(100) * static_cast<double>(0.1f);
            field_370 = product - 5.0;
            rotation_12c = random_float(360);
            double const delta = random_float(10) * static_cast<double>(0.1f);
            scale_y_120 = scale_x_11c = static_cast<float>(delta + params_340[3]);
        }
        if (sequence_id_13e == 5) {
            float product = random_float(100) * static_cast<double>(0.1f);
            field_370 = product - 5.0;
            rotation_12c = random_float(360);
            double const delta = random_float(10) * static_cast<double>(0.1f);
            scale_y_120 = scale_x_11c = static_cast<float>(delta + params_340[3]);
        }
        if (sequence_id_13e == 10) {
            velocity_x_f4 = 0;
            velocity_y_f8 = 0;
            scale_y_120 = scale_x_11c = static_cast<float>(random_float(15) * static_cast<double>(0.1f) + 0.5);
            if (target_34c) {
                x_ec = lookup_orientation_cosine_quantized_abs(params_340[0]) * params_340[1] + target_34c->x_ec;
                y_f0 = lookup_orientation_sine_quantized_abs(params_340[0]) * params_340[1] + target_34c->y_f0;
            }
        }
        if (sequence_id_13e == 14) {
            byte_184 = 1;
            field_370 = 0.55f;
            scale_x_11c = 0.1f;
            scale_y_120 = 0.1f;
        }
        if (sequence_id_13e == 16) {
            alpha_113 = 0;
            field_370 = 0.4f;
            scale_x_11c = 0.1f;
            scale_y_120 = 0.1f;
        }
        if (sequence_id_13e == 17) {
            byte_184 = 1;
            scale_x_11c = 2;
        }
        if (sequence_id_13e == 18) {
            scale_x_11c = 0.1f;
            scale_y_120 = 0.1f;
        }
        return;
    case 980:
        continue_action_980();
        return;
    case 998:
        rotation_12c = 0;
        field_128 = 60;
        return;
    case 999:
        SELECT();
        if (sequence_id_13e == 0) {
            rotation_12c = random_float(360);
            float product = random_float(50) * static_cast<double>(0.01f);
            scale_y_120 = scale_x_11c = static_cast<float>(product + 1.0);
            field_370 = random_float(10) - 5.0;
        }
        if (sequence_id_13e == 1) {
            rotation_12c = random_float(360);
            float product = random_float(50) * static_cast<double>(0.01f);
            scale_y_120 = scale_x_11c = static_cast<float>(product + 1.0);
            field_370 = random_float(10) - 5.0;
        }
        return;
    }
}

#undef SPAWN
#undef MOVE
#undef SELECT

} // namespace th105
