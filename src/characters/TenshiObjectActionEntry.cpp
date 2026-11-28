#include "characters/TenshiObjectActionEntry.hpp"

// JP1.06a 0x00657150: TenshiObject primary slot +0x3C action entry initializer.
// Evidence and finite trials: docs/TENSHI_OBJECT_ENTRY_2026_10_24.md.
namespace th105 {

#define SELECT() select_sequence(static_cast<int>(params_340[2]))
#define MOVE() motion_004.set_components(params_340[0], params_340[1])
#define SPAWN(a, x, y, l) spawn_parented(a, x, y, static_cast<unsigned char>(facing_104), l, reinterpret_cast<const unsigned *>(payload), 3)
#define UNSPAWN(a, l) spawn_unparented(a, x_ec, y_f0, static_cast<unsigned char>(facing_104), l, reinterpret_cast<const unsigned *>(payload), 3)

__forceinline static float random_float(int n) {
    return static_cast<float>(static_cast<unsigned>(selector_random_roll(n)));
}

void TenshiObjectEntryView::initialize_action_entry() {
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
        rotation_12c = params_340[0];
        SELECT();
        if (sequence_id_13e == 0) {
            payload[0] = 0;
            payload[1] = 0;
            payload[2] = 2;
            byte_184 = 1;
            UNSPAWN(800, 1);
            payload[2] = 3;
            UNSPAWN(800, 1);
        }
        if (sequence_id_13e == 3)
            field_128 = 60;
        if (sequence_id_13e == 4) {
            payload[0] = 0;
            payload[1] = 0;
            payload[2] = 2;
            byte_184 = 6;
            UNSPAWN(800, 1);
            payload[2] = 3;
            UNSPAWN(800, 1);
        }
        return;
    }
    case 801:
        SELECT();
        if (sequence_id_13e == 0) {
            MOVE();
            double const heading = params_340[0];
            byte_184 = 1;
            rotation_12c = heading;
            scale_y_120 = 0.1f;
        }
        if (sequence_id_13e == 3) {
            float scale = random_float(10) * static_cast<double>(0.1f);
            scale_y_120 = scale_x_11c = static_cast<float>(scale + 0.5);
        }
        if (sequence_id_13e == 4) {
            field_370 = x_ec - owner_348->x_ec;
            field_374 = y_f0 - owner_348->y_f0;
            word_36c = static_cast<unsigned>(selector_random_roll(100)) <= 50;
        }
        return;
    case 810:
        byte_17c = 0;
        rotation_12c = params_340[0];
        SELECT();
        if (sequence_id_13e == 1) {
            float scale = random_float(50) * static_cast<double>(0.01f);
            scale_y_120 = scale_x_11c = static_cast<float>(scale + 0.5);
            replace_auxiliary(990);
            aux_154->scale_x_f8 = 10;
            aux_154->scale_y_fc = 10;
            aux_154->x_e8 = x_ec;
            aux_154->y_ec = stage_height();
            aux_154->facing_104 = static_cast<unsigned char>(facing_104);
            MOVE();
        }
        if (sequence_id_13e == 2 || sequence_id_13e == 3 || sequence_id_13e == 4) {
            float scale = random_float(20) * static_cast<double>(0.01f);
            scale_y_120 = scale_x_11c = static_cast<float>(scale + 0.75);
            MOVE();
            field_374 = random_float(20) - 10.0;
        }
        if (sequence_id_13e == 5) {
            if (static_cast<unsigned>(selector_random_roll(100)) <= 49)
                field_374 = 1;
            else
                field_374 = -1;
        }
        if (sequence_id_13e == 6)
            byte_184 = 1;
        return;
    case 811:
        byte_17c = 4;
        rotation_12c = params_340[0];
        SELECT();
        if (sequence_id_13e == 2 || sequence_id_13e == 3 || sequence_id_13e == 4) {
            float scale = random_float(20) * static_cast<double>(0.01f);
            scale_y_120 = scale_x_11c = static_cast<float>(scale + 0.75);
            MOVE();
            field_374 = random_float(20) - 10.0;
        }
        if (sequence_id_13e == 5) {
            if (static_cast<unsigned>(selector_random_roll(100)) <= 49)
                field_374 = 1;
            else
                field_374 = -1;
        }
        if (sequence_id_13e == 6)
            byte_184 = 1;
        return;
    case 815:
        byte_17c = 1;
        SELECT();
        if (sequence_id_13e == 0) {
            MOVE();
            byte_184 = 1;
            replace_auxiliary(990);
            aux_154->scale_x_f8 = 10;
            aux_154->scale_y_fc = 10;
            aux_154->x_e8 = x_ec;
            aux_154->y_ec = stage_height();
            aux_154->facing_104 = static_cast<unsigned char>(facing_104);
        }
        if (sequence_id_13e == 2 || sequence_id_13e == 3 || sequence_id_13e == 1) {
            rotation_12c = params_340[0];
            float scale = random_float(20) * static_cast<double>(0.01f);
            scale_y_120 = scale_x_11c = static_cast<float>(scale + 0.75);
            MOVE();
            field_374 = random_float(20) - 10.0;
        }
        if (sequence_id_13e == 4) {
            if (static_cast<unsigned>(selector_random_roll(100)) <= 49)
                field_374 = 1;
            else
                field_374 = -1;
        }
        return;
    case 816:
        byte_17c = 5;
        SELECT();
        if (sequence_id_13e == 0) {
            alpha_113 = 0;
            field_370 = 0.25f;
            byte_184 = 1;
            field_374 = 100;
        }
        if (sequence_id_13e == 3 || sequence_id_13e == 4) {
            float scale = random_float(20) * static_cast<double>(0.01f);
            scale_y_120 = scale_x_11c = static_cast<float>(scale + 0.75);
            MOVE();
            field_374 = random_float(20) - 10.0;
        }
        return;
    case 820: {
        float payload[3];
        byte_17c = 2;
        SELECT();
        if (sequence_id_13e == 1) {
            field_37c = 1;
            scale_x_11c = 32;
            payload[0] = 0;
            payload[1] = 0;
            payload[2] = 0;
            SPAWN(820, x_ec, y_f0, layer_33c);
            rotation_12c = params_340[0];
            scale_y_120 = 0;
            if (target_34c) {
                byte_184 = 1;
                field_370 = x_ec - target_34c->x_ec;
                field_374 = y_f0 - target_34c->y_f0;
            }
        }
        if (sequence_id_13e == 2) {
            scale_y_120 = 0;
            rotation_12c = params_340[0];
            if (target_34c) {
                byte_184 = 1;
                field_370 = x_ec - target_34c->x_ec;
                field_374 = y_f0 - target_34c->y_f0;
            }
        }
        if (sequence_id_13e == 3) {
            field_370 = x_ec - owner_348->x_ec;
            field_374 = y_f0 - owner_348->y_f0;
            field_378 = 5;
        }
        if (sequence_id_13e == 5) {
            scale_x_11c = 32;
            field_37c = 2;
            payload[0] = 0;
            payload[1] = 0;
            payload[2] = 4;
            SPAWN(820, x_ec, y_f0, layer_33c);
            rotation_12c = params_340[0];
            scale_y_120 = 0;
            if (target_34c) {
                byte_184 = 1;
                field_370 = x_ec - target_34c->x_ec;
                field_374 = y_f0 - target_34c->y_f0;
            }
        }
        return;
    }
    case 821:
        byte_17c = 6;
        SELECT();
        if (sequence_id_13e == 1) {
            byte_184 = 1;
            field_374 = 15;
            alpha_113 = 0;
        }
        if (sequence_id_13e == 4 || sequence_id_13e == 5 || sequence_id_13e == 6) {
            float scale = random_float(20) * static_cast<double>(0.01f);
            scale_y_120 = scale_x_11c = static_cast<float>(scale + 0.75);
            MOVE();
            field_374 = random_float(20) - 10.0;
        }
        if (sequence_id_13e == 7)
            byte_184 = 1;
        if (sequence_id_13e == 8)
            rotation_12c = params_340[0];
        return;
    case 825:
        byte_17c = 3;
        SELECT();
        if (sequence_id_13e == 0) {
            scale_y_120 = scale_x_11c = static_cast<float>(random_float(50) * static_cast<double>(0.01f) + 0.5);
            rotation_12c = random_float(360);
        }
        return;
    case 848:
        SELECT();
        if (sequence_id_13e == 0)
            field_370 = params_340[0];
        if (sequence_id_13e == 1) {
            if (static_cast<unsigned>(selector_random_roll(100)) <= 49)
                field_374 = 1;
            else
                field_374 = -1;
        }
        if (sequence_id_13e == 2) {
            scale_x_11c = 0;
            scale_y_120 = 0;
            field_370 = 1;
        }
        if (sequence_id_13e == 3) {
            if (static_cast<unsigned>(selector_random_roll(100)) <= 49)
                field_374 = 1;
            else
                field_374 = -1;
        }
        return;
    case 850:
        rotation_12c = params_340[0];
        SELECT();
        if (sequence_id_13e == 1) {
            float scale = random_float(25) * static_cast<double>(0.01f);
            scale_y_120 = scale_x_11c = static_cast<float>(scale + 1.0);
            replace_auxiliary(990);
            aux_154->scale_x_f8 = 10;
            aux_154->scale_y_fc = 10;
            aux_154->x_e8 = x_ec;
            aux_154->y_ec = stage_height();
            aux_154->facing_104 = static_cast<unsigned char>(facing_104);
            MOVE();
        }
        if (sequence_id_13e == 2 || sequence_id_13e == 3 || sequence_id_13e == 4) {
            float scale = random_float(20) * static_cast<double>(0.01f);
            scale_y_120 = scale_x_11c = static_cast<float>(scale + 0.75);
            MOVE();
            field_374 = random_float(20) - 10.0;
        }
        if (sequence_id_13e == 5) {
            if (static_cast<unsigned>(selector_random_roll(100)) <= 49)
                field_374 = 1;
            else
                field_374 = -1;
        }
        if (sequence_id_13e == 6)
            byte_184 = 1;
        return;
    case 851:
        SELECT();
        if (sequence_id_13e == 0)
            scale_y_120 = scale_x_11c = static_cast<float>(params_340[1] + 1.0);
        if (sequence_id_13e == 5)
            scale_y_120 = scale_x_11c = static_cast<float>(random_float(15) * static_cast<double>(0.1f) + 0.5);
        return;
    case 852:
        rotation_12c = params_340[0];
        SELECT();
        if (sequence_id_13e == 1) {
            if (static_cast<unsigned>(selector_random_roll(100)) <= 49)
                field_374 = 1;
            else
                field_374 = -1;
        }
        if (sequence_id_13e == 2) {
            scale_y_120 = scale_x_11c = static_cast<float>(random_float(10) * static_cast<double>(0.1f) + 1.0);
            rotation_12c = random_float(360);
            field_370 = random_float(10) - 5.0;
        }
        return;
    case 853:
        rotation_12c = params_340[0];
        SELECT();
        if (sequence_id_13e == 2 || sequence_id_13e == 3 || sequence_id_13e == 4) {
            float scale = random_float(20) * static_cast<double>(0.01f);
            scale_y_120 = scale_x_11c = static_cast<float>(scale + 0.75);
            MOVE();
            field_374 = random_float(20) - 10.0;
        }
        if (sequence_id_13e == 5) {
            if (static_cast<unsigned>(selector_random_roll(100)) <= 49)
                field_374 = 1;
            else
                field_374 = -1;
        }
        if (sequence_id_13e == 6 || sequence_id_13e == 7)
            byte_184 = 1;
        return;
    case 854:
        SELECT();
        if (sequence_id_13e == 0) {
            byte_184 = 5;
            rotation_12c = params_340[0];
        }
        if (sequence_id_13e == 1)
            field_370 = 0.4f;
        if (sequence_id_13e == 2) {
            float scale = random_float(40) * static_cast<double>(0.01f);
            field_370 = scale + static_cast<double>(0.2f);
        }
        if (sequence_id_13e == 3) {
            word_344 = 1;
            alpha_113 = 0;
            if (static_cast<unsigned>(selector_random_roll(100)) <= 49)
                field_374 = 1;
            else
                field_374 = -1;
            x_ec = lookup_orientation_cosine_quantized_abs(-params_340[0]) * params_340[1] * facing_104 + owner_348->x_ec;
            y_f0 = lookup_orientation_sine_quantized_abs(-params_340[0]) * params_340[1] + (owner_348->y_f0 + 100.0);
        }
        if (sequence_id_13e == 4)
            scale_y_120 = scale_x_11c = static_cast<float>(random_float(10) * static_cast<double>(0.1f) + 0.5);
        if (sequence_id_13e == 5) {
            if (static_cast<unsigned>(selector_random_roll(100)) <= 49)
                field_374 = 1;
            else
                field_374 = -1;
        }
        if (sequence_id_13e == 6) {
            byte_184 = 10;
            rotation_12c = params_340[0];
        }
        if (sequence_id_13e == 7) {
            scale_y_120 = 40;
            rotation_12c = params_340[0];
        }
        if (sequence_id_13e == 8) {
            if (static_cast<unsigned>(selector_random_roll(100)) <= 49)
                field_374 = 1;
            else
                field_374 = -1;
        }
        return;
    case 855:
        SELECT();
        if (sequence_id_13e == 0)
            byte_184 = 1;
        if (sequence_id_13e == 2 || sequence_id_13e == 3 || sequence_id_13e == 4) {
            float scale = random_float(20) * static_cast<double>(0.01f);
            scale_y_120 = scale_x_11c = static_cast<float>(scale + 0.75);
            MOVE();
            field_374 = random_float(20) - 10.0;
        }
        return;
    case 856:
        SELECT();
        if (sequence_id_13e == 1) {
            rotation_12c = params_340[0];
            float scale = random_float(20) * static_cast<double>(0.01f);
            scale_y_120 = scale_x_11c = static_cast<float>(scale + 0.75);
            MOVE();
            field_374 = random_float(20) - 10.0;
        }
        return;
    case 857: {
        float payload[3];
        SELECT();
        if (sequence_id_13e == 1) {
            float scale = random_float(10) * static_cast<double>(0.1f);
            scale_y_120 = scale_x_11c = static_cast<float>(scale + 0.5);
            rotation_12c = random_float(360);
            if (static_cast<unsigned>(selector_random_roll(100)) <= 49)
                field_374 = 1;
            else
                field_374 = -1;
        }
        if (sequence_id_13e == 3) {
            rotation_12c = params_340[0];
            byte_184 = 1;
            scale_y_120 = 2;
            payload[0] = params_340[0];
            payload[1] = 0;
            payload[2] = 5;
            SPAWN(857, x_ec, y_f0, 1);
        }
        if (sequence_id_13e == 6)
            rotation_12c = params_340[0];
        return;
    }
    case 899:
        byte_184 = 1;
        SELECT();
        if (sequence_id_13e == 1)
            rotation_12c = random_float(360);
        return;
    case 900:
        SELECT();
        if (sequence_id_13e == 0) {
            alpha_113 = 0;
            scale_x_11c = 0;
            scale_y_120 = 3;
        }
        if (sequence_id_13e == 1) {
            byte_184 = 1;
            MOVE();
        }
        if (sequence_id_13e == 3) {
            rotation_12c = random_float(360);
            scale_y_120 = scale_x_11c = static_cast<float>(random_float(75) * static_cast<double>(0.01f) + 0.75);
            MOVE();
        }
        return;
    case 920: {
        float payload[3];
        SELECT();
        if (sequence_id_13e == 0) {
            word_364 = static_cast<short>(static_cast<int>(params_340[0]));
            field_370 = 200;
            byte_184 = 1;
            replace_auxiliary(990);
            aux_154->scale_x_f8 = 4;
            aux_154->scale_y_fc = 4;
            aux_154->x_e8 = x_ec;
            aux_154->y_ec = stage_height();
            aux_154->facing_104 = static_cast<unsigned char>(facing_104);
        }
        if (sequence_id_13e == 1) {
            scale_x_11c = 1.5f;
            scale_y_120 = 1.5f;
            word_364 = static_cast<short>(static_cast<int>(params_340[0]));
            byte_184 = 1;
            motion_004.set_components(-90, params_340[1]);
            replace_auxiliary(990);
            aux_154->x_e8 = x_ec;
            aux_154->y_ec = stage_height();
            aux_154->facing_104 = static_cast<unsigned char>(facing_104);
        }
        if (sequence_id_13e == 4) {
            MOVE();
            double const heading = params_340[0];
            byte_184 = 1;
            rotation_12c = heading;
            scale_y_120 = 0.1f;
        }
        if (sequence_id_13e == 6) {
            float scale = random_float(10) * static_cast<double>(0.1f);
            scale_y_120 = scale_x_11c = static_cast<float>(scale + 0.5);
        }
        if (sequence_id_13e == 8) {
            field_370 = x_ec - owner_348->x_ec;
            field_374 = y_f0 - owner_348->y_f0;
            word_36c = static_cast<unsigned>(selector_random_roll(100)) <= 50;
        }
        if (sequence_id_13e == 9) {
            MOVE();
            payload[0] = 0;
            payload[1] = 0;
            payload[2] = 10;
            SPAWN(920, x_ec, stage_height(), -1);
            replace_auxiliary(990);
            aux_154->scale_x_f8 = 4;
            aux_154->scale_y_fc = 4;
            aux_154->x_e8 = x_ec;
            aux_154->y_ec = stage_height();
            aux_154->facing_104 = static_cast<unsigned char>(facing_104);
        }
        if (sequence_id_13e == 10)
            alpha_113 = 0;
        return;
    }
    case 930:
        SELECT();
        if (sequence_id_13e == 0) {
            MOVE();
            byte_184 = 1;
        }
        if (sequence_id_13e == 2) {
            float scale = random_float(10) * static_cast<double>(0.1f);
            scale_y_120 = scale_x_11c = static_cast<float>(scale + 0.5);
        }
        return;
    case 940: {
        float payload[3];
        SELECT();
        if (sequence_id_13e == 1) {
            rotation_12c = random_float(360);
            word_344 = 1;
            alpha_113 = 0;
            if (static_cast<unsigned>(selector_random_roll(100)) <= 49)
                field_374 = 1;
            else
                field_374 = -1;
            float scale = random_float(10) * static_cast<double>(0.1f);
            scale_y_120 = scale_x_11c = static_cast<float>(scale + 0.5);
            x_ec = lookup_orientation_cosine_quantized_abs(-params_340[0]) * params_340[1] * facing_104 + owner_348->x_ec;
            y_f0 = lookup_orientation_sine_quantized_abs(-params_340[0]) * params_340[1] + owner_348->y_f0;
        }
        if (sequence_id_13e == 2) {
            MOVE();
            rotation_12c = params_340[0];
            scale_y_120 = 0.1f;
            payload[0] = 0;
            payload[1] = 0;
            payload[2] = 5;
            byte_184 = 1;
            UNSPAWN(940, 1);
        }
        if (sequence_id_13e == 4)
            scale_y_120 = scale_x_11c = static_cast<float>(random_float(10) * static_cast<double>(0.1f) + 0.5);
        if (sequence_id_13e == 7) {
            scale_x_11c = 40;
            rotation_12c = params_340[0];
            scale_y_120 = 0;
            field_370 = 1;
            payload[0] = params_340[0];
            payload[1] = 0;
            payload[2] = 6;
            SPAWN(940, x_ec, y_f0, 1);
        }
        if (sequence_id_13e == 8) {
            float scale = random_float(10) * static_cast<double>(0.1f);
            scale_y_120 = scale_x_11c = static_cast<float>(scale + 0.5);
            rotation_12c = random_float(360);
            if (static_cast<unsigned>(selector_random_roll(100)) <= 49)
                field_374 = 1;
            else
                field_374 = -1;
        }
        if (sequence_id_13e == 9) {
            rotation_12c = params_340[0];
            byte_184 = 1;
            payload[0] = params_340[0];
            payload[1] = 0;
            payload[2] = 11;
            SPAWN(940, x_ec, y_f0, 1);
        }
        if (sequence_id_13e == 12)
            rotation_12c = params_340[0];
        if (sequence_id_13e == 13) {
            owner_348->dispatch_character_wave_handle(56);
            int_144 = 0;
            payload[0] = params_340[0];
            payload[1] = 180;
            payload[2] = 9;
            SPAWN(940, static_cast<float>(lookup_orientation_cosine_quantized_abs(-params_340[0]) * 100.0 * facing_104 + x_ec), static_cast<float>(lookup_orientation_sine_quantized_abs(-params_340[0]) * 100.0 + y_f0), 1);
        }
        return;
    }
    case 960:
    case 961:
        SELECT();
        if (sequence_id_13e <= 7) {
            if (g_event_effect_id == 14) {
                color_111 = 128;
                color_112 = 128;
            }
            replace_auxiliary(989);
            aux_154->scale_x_f8 = 1.05f;
            aux_154->scale_y_fc = 1;
            aux_154->x_e8 = x_ec;
            aux_154->y_ec = 0;
            aux_154->facing_104 = static_cast<unsigned char>(facing_104);
        }
        return;
    case 962: {
        float payload[3];
        SELECT();
        if (sequence_id_13e <= 7) {
            if (g_event_effect_id == 14) {
                color_111 = 128;
                color_112 = 128;
            }
            replace_auxiliary(989);
            aux_154->scale_x_f8 = 1.05f;
            aux_154->scale_y_fc = 1;
            aux_154->x_e8 = x_ec;
            aux_154->y_ec = -owner_348->field_828;
            aux_154->facing_104 = static_cast<unsigned char>(facing_104);
            payload[1] = 20;
            payload[2] = 4;
            for (float n = 0; n < 8; n += 1.0) {
                payload[0] = random_float(30) + n * 45.0;
                if (payload[0] >= 0 && payload[0] <= 180)
                    spawn_unparented(815, x_ec, stage_height(), static_cast<unsigned char>(facing_104), 1, reinterpret_cast<const unsigned *>(payload), 3);
                else
                    spawn_unparented(815, x_ec, stage_height(), static_cast<unsigned char>(facing_104), -1, reinterpret_cast<const unsigned *>(payload), 3);
            }
        }
        return;
    }
    case 980:
        continue_action_980();
        return;
    case 997:
        velocity_x_f4 = 5;
        velocity_y_f8 = 20;
        SELECT();
        if (sequence_id_13e == 3) {
            float scale = random_float(10) * static_cast<double>(0.1f);
            scale_y_120 = scale_x_11c = static_cast<float>(scale + 0.5);
            rotation_12c = random_float(360);
            if (static_cast<unsigned>(selector_random_roll(100)) <= 49)
                field_374 = 1;
            else
                field_374 = -1;
        }
        if (sequence_id_13e == 4)
            rotation_12c = -90;
        return;
    }
}

#undef UNSPAWN
#undef SPAWN
#undef MOVE
#undef SELECT

} // namespace th105
