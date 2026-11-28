#include "characters/YukariObjectActionEntry.hpp"

// JP1.06a 0x005964C0: YukariObject primary slot +0x3C action entry initializer.
// Evidence and finite trials: docs/YUKARI_OBJECT_ENTRY_2026_10_24.md.
namespace th105 {

#define SELECT() select_sequence(static_cast<int>(params_340[2]))
#define MAYSELECT() if (params_340[2] != 0.0f) SELECT()
#define SPAWN(a, x, y, layer, count) spawn_parented(a, x, y, static_cast<unsigned char>(facing_104), layer, reinterpret_cast<const unsigned *>(payload), count)
#define UNSPAWN(a, x, y, layer, count) spawn_unparented(a, x, y, static_cast<unsigned char>(facing_104), layer, reinterpret_cast<const unsigned *>(payload), count)

__forceinline static float random_float(int n) {
    return static_cast<float>(static_cast<unsigned>(selector_random_roll(n)));
}

void YukariObjectEntryView::initialize_action_entry() {
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
        rotation_12c = params_340[0];
        SELECT();
        if (sequence_id_13e == 1) {
            replace_auxiliary(992);
            aux_154->x_e8 = x_ec;
            aux_154->y_ec = static_cast<float>(stage_height() - 3.0);
            aux_154->facing_104 = static_cast<unsigned char>(facing_104);
        }
        if (sequence_id_13e == 2) {
            replace_auxiliary(990);
            aux_154->x_e8 = x_ec;
            aux_154->y_ec = static_cast<float>(y_f0 - 10.0);
            aux_154->facing_104 = static_cast<unsigned char>(facing_104);
        }
        return;
    case 801:
        byte_184 = 1;
        rotation_12c = params_340[0];
        field_370 = 255;
        SELECT();
        if (sequence_id_13e == 4)
            scale_y_120 = scale_x_11c = static_cast<float>(motion_004.random_range(5, 15) * static_cast<double>(0.1f));
        return;
    case 810:
        byte_184 = 1;
        byte_17c = 0;
        SELECT();
        if (sequence_id_13e == 0)
            y_f0 = stage_height() + 650.0;
        if (sequence_id_13e == 1 || sequence_id_13e == 2 || sequence_id_13e == 3) {
            velocity_y_f8 = -25;
            replace_auxiliary(990);
            aux_154->x_e8 = x_ec;
            aux_154->y_ec = y_f0;
            aux_154->facing_104 = static_cast<unsigned char>(facing_104);
        }
        return;
    case 811:
        byte_184 = 1;
        byte_17c = 4;
        rotation_12c = params_340[0];
        SELECT();
        if (sequence_id_13e == 1) {
            velocity_y_f8 = -25;
            replace_auxiliary(993);
            aux_154->x_e8 = static_cast<float>(x_ec - (lookup_orientation_cosine_quantized_abs(-params_340[0]) * 100.0 - 105.0) * facing_104);
            aux_154->y_ec = static_cast<float>(y_f0 - lookup_orientation_sine_quantized_abs(-params_340[0]) * 100.0);
            aux_154->scale_x_f8 = 4;
            aux_154->scale_y_fc = 4;
            aux_154->facing_104 = static_cast<unsigned char>(facing_104);
        }
        return;
    case 812: {
        float payload[3];
        byte_17c = 8;
        rotation_12c = params_340[0];
        SELECT();
        if (sequence_id_13e == 0) {
            field_370 = 1;
            scale_x_11c = 0;
            scale_y_120 = 0;
            payload[0] = 0;
            payload[1] = 0;
            payload[2] = 5;
            UNSPAWN(812, x_ec, y_f0, 1, 3);
        }
        if (sequence_id_13e == 1)
            field_370 = 18;
        if (sequence_id_13e == 2) {
            byte_184 = 1;
            scale_y_120 = 4;
        }
        if (sequence_id_13e == 4) {
            field_370 = 1;
            scale_x_11c = 0;
            scale_y_120 = 0;
            payload[0] = 0;
            payload[1] = 0;
            payload[2] = 5;
            UNSPAWN(812, x_ec, y_f0, 1, 3);
        }
        return;
    }
    case 815:
        byte_17c = 1;
        SELECT();
        return;
    case 816:
        byte_184 = 0;
        if (owner_348->byte_609 >= 3)
            byte_184 = 1;
        int_180 = 0;
        byte_17c = 5;
        SELECT();
        return;
    case 820:
        byte_17c = 2;
        byte_184 = 1;
        SELECT();
        if (sequence_id_13e == 0 || sequence_id_13e == 3)
            scale_x_11c = 0;
        if (sequence_id_13e == 7)
            rotation_12c = params_340[0];
        if (sequence_id_13e == 8) {
            field_124 = random_float(360);
            field_128 = random_float(360);
            rotation_12c = random_float(360);
        }
        return;
    case 821:
        byte_17c = 6;
        SELECT();
        if (sequence_id_13e == 2)
            byte_184 = 0;
        if (sequence_id_13e == 4) {
            rotation_12c = params_340[0];
            scale_x_11c = 0.25f;
            scale_y_120 = 0.25f;
        }
        if (sequence_id_13e == 5) {
            rotation_12c = params_340[0];
            scale_y_120 = scale_x_11c = static_cast<float>(motion_004.random_range(5, 15) * static_cast<double>(0.1f));
        }
        if (sequence_id_13e == 6) {
            field_370 = 0.25f;
            rotation_12c = params_340[0];
            scale_x_11c = 0.5f;
            scale_y_120 = 0.5f;
        }
        return;
    case 825:
        byte_17c = 3;
        SELECT();
        if (sequence_id_13e == 0) {
            scale_x_11c = 0;
            field_370 = 0.2f;
        }
        if (sequence_id_13e == 1) {
            scale_x_11c = 0;
            field_370 = 0.1f;
            owner_348->replace_auxiliary(993);
            owner_348->aux_154->x_e8 = x_ec;
            owner_348->aux_154->y_ec = y_f0;
            owner_348->aux_154->scale_x_f8 = 2;
            owner_348->aux_154->scale_y_fc = 2;
            owner_348->aux_154->facing_104 = static_cast<unsigned char>(facing_104);
        }
        if (sequence_id_13e == 2) {
            owner_348->replace_auxiliary(990);
            owner_348->aux_154->x_e8 = x_ec;
            owner_348->aux_154->y_ec = y_f0;
            owner_348->aux_154->scale_x_f8 = 4;
            owner_348->aux_154->scale_y_fc = 2;
            owner_348->aux_154->facing_104 = static_cast<unsigned char>(facing_104);
        }
        return;
    case 826: {
        float payload[3];
        SELECT();
        if (sequence_id_13e == 0) {
            replace_auxiliary(992);
            aux_154->x_e8 = x_ec;
            aux_154->y_ec = owner_348->y_f0;
            aux_154->scale_x_f8 = 10;
            aux_154->scale_y_fc = 2;
            aux_154->facing_104 = static_cast<unsigned char>(facing_104);
        }
        if (sequence_id_13e == 4) {
            field_124 = 85;
            rotation_12c = random_float(360);
            field_370 = random_float(20) - 10.0;
        }
        if (sequence_id_13e == 5) {
            replace_auxiliary(992);
            aux_154->x_e8 = x_ec;
            aux_154->y_ec = y_f0;
            aux_154->scale_x_f8 = 2;
            aux_154->scale_y_fc = 2;
            aux_154->facing_104 = static_cast<unsigned char>(facing_104);
        }
        if (sequence_id_13e == 9) {
            field_108 = 0;
            field_10c = 135;
            byte_184 = 1;
            velocity_x_f4 = 6;
            velocity_y_f8 = 30;
            field_370 = -230;
            replace_auxiliary(992);
            aux_154->x_e8 = x_ec;
            aux_154->y_ec = owner_348->y_f0;
            aux_154->scale_x_f8 = 10;
            aux_154->scale_y_fc = 2;
            aux_154->facing_104 = static_cast<unsigned char>(facing_104);
            payload[0] = 0;
            payload[1] = 0;
            payload[2] = 0;
            SPAWN(826, x_ec, static_cast<float>(y_f0 + 130.0), 1, 3);
        }
        if (sequence_id_13e == 10) {
            field_108 = 0;
            field_10c = 135;
            byte_184 = 1;
            field_370 = -250;
            replace_auxiliary(992);
            aux_154->x_e8 = x_ec;
            aux_154->y_ec = owner_348->y_f0;
            aux_154->scale_x_f8 = 10;
            aux_154->scale_y_fc = 2;
            aux_154->facing_104 = static_cast<unsigned char>(facing_104);
            payload[0] = 0;
            payload[1] = 0;
            payload[2] = 0;
            SPAWN(826, x_ec, static_cast<float>(y_f0 + 130.0), 1, 3);
        }
        return;
    }
    case 848:
        SELECT();
        return;
    case 849:
        SELECT();
        if (sequence_id_13e == 0) {
            velocity_x_f4 = -6;
            velocity_y_f8 = 4;
        }
        if (sequence_id_13e == 1)
            velocity_x_f4 = 6;
        return;
    case 850:
        rotation_12c = params_340[0];
        field_124 = -30 * facing_104;
        field_128 = 60;
        MAYSELECT();
        if (sequence_id_13e == 0) {
            scale_x_11c = 0.2f;
            scale_y_120 = 0.2f;
        }
        if (sequence_id_13e == 2)
            scale_y_120 = scale_x_11c = params_340[1];
        return;
    case 851:
        MAYSELECT();
        if (sequence_id_13e == 0) {
            field_370 = 1;
            word_344 = 1;
            scale_x_11c = 0;
            scale_y_120 = 3;
        }
        return;
    case 852:
        MAYSELECT();
        if (sequence_id_13e == 0)
            byte_184 = 1;
        return;
    case 853:
        rotation_12c = params_340[0];
        field_124 = -30 * facing_104;
        field_128 = 60;
        MAYSELECT();
        if (sequence_id_13e == 0) {
            scale_x_11c = 0.2f;
            scale_y_120 = 0.2f;
        }
        if (sequence_id_13e == 2)
            scale_y_120 = scale_x_11c = params_340[1];
        if (sequence_id_13e == 3)
            scale_y_120 = scale_x_11c = params_340[1];
        if (sequence_id_13e == 4) {
            field_124 = 75;
            rotation_12c = 0;
            alpha_113 = 0;
            field_128 = 0;
        }
        return;
    case 854:
        MAYSELECT();
        if (sequence_id_13e == 0) {
            field_370 = 1;
            byte_184 = 1;
            scale_x_11c = 0;
            word_344 = 1;
            scale_y_120 = 3;
        }
        return;
    case 855:
        MAYSELECT();
        if (sequence_id_13e == 1)
            scale_y_120 = scale_x_11c = static_cast<float>(random_float(10) * static_cast<double>(0.1f) + 0.5);
        if (sequence_id_13e == 3) {
            byte_184 = 1;
            motion_004.set_components(params_340[0], params_340[1]);
        }
        if (sequence_id_13e == 4) {
            scale_x_11c = random_float(10) * static_cast<double>(0.05f) + 1.0;
            scale_y_120 = random_float(10) * static_cast<double>(0.1f) + 1.0;
            rotation_12c = params_340[0];
        }
        return;
    case 856:
        rotation_12c = params_340[0];
        SELECT();
        if (sequence_id_13e == 0) {
            scale_x_11c = 0;
            word_344 = 1;
            scale_y_120 = 0;
            field_370 = random_float(75) * static_cast<double>(0.01f) + 0.75;
            field_374 = 1;
            field_378 = 1;
        }
        if (sequence_id_13e == 1) {
            motion_004.set_components(params_340[0], params_340[1]);
            byte_184 = 1;
            replace_auxiliary(993);
            aux_154->x_e8 = x_ec;
            aux_154->y_ec = y_f0;
            aux_154->facing_104 = static_cast<unsigned char>(facing_104);
            scale_x_11c = 1.5f;
            scale_y_120 = random_float(5) * static_cast<double>(0.1f) + 0.5;
        }
        if (sequence_id_13e == 2)
            field_370 = 0.4f;
        return;
    case 857: {
        float payload[3];
        rotation_12c = params_340[0];
        SELECT();
        if (sequence_id_13e == 0) {
            field_370 = 1;
            scale_x_11c = 0;
            scale_y_120 = 0;
            payload[0] = 0;
            payload[1] = 0;
            payload[2] = 5;
            UNSPAWN(857, x_ec, y_f0, 1, 3);
        }
        if (sequence_id_13e == 1)
            field_370 = 18;
        if (sequence_id_13e == 2) {
            byte_184 = 1;
            scale_y_120 = 4;
        }
        if (sequence_id_13e == 4) {
            field_370 = 1;
            scale_x_11c = 0;
            scale_y_120 = 0;
            payload[0] = 0;
            payload[1] = 0;
            payload[2] = 5;
            UNSPAWN(857, x_ec, y_f0, 1, 3);
        }
        return;
    }
    case 865:
        byte_184 = 1;
        SELECT();
        if (sequence_id_13e == 0)
            field_370 = 0.3f;
        if (sequence_id_13e == 1) {
            byte_135 = 1;
            replace_auxiliary(993);
            aux_154->x_e8 = x_ec;
            aux_154->y_ec = y_f0;
            aux_154->scale_x_f8 = 20;
            aux_154->scale_y_fc = 4;
            aux_154->facing_104 = static_cast<unsigned char>(facing_104);
        }
        return;
    case 899:
        SELECT();
        if (sequence_id_13e == 0) {
            scale_x_11c = 0;
            field_370 = 0.1f;
            owner_348->replace_auxiliary(993);
            owner_348->aux_154->x_e8 = x_ec;
            owner_348->aux_154->y_ec = y_f0;
            owner_348->aux_154->scale_x_f8 = 2;
            owner_348->aux_154->scale_y_fc = 2;
            owner_348->aux_154->facing_104 = static_cast<unsigned char>(owner_348->facing_104);
        }
        if (sequence_id_13e == 4) {
            field_124 = 85;
            rotation_12c = random_float(360);
            field_370 = random_float(20) - 10.0;
        }
        if (sequence_id_13e == 5) {
            replace_auxiliary(992);
            aux_154->x_e8 = x_ec;
            aux_154->y_ec = y_f0;
            aux_154->scale_x_f8 = 2;
            aux_154->scale_y_fc = 2;
            aux_154->facing_104 = static_cast<unsigned char>(facing_104);
        }
        return;
    case 900:
        SELECT();
        if (sequence_id_13e == 0) {
            byte_184 = 1;
            field_378 = 10;
            field_370 = x_ec;
            field_374 = y_f0;
        }
        if (sequence_id_13e == 1) {
            field_378 = 12;
            byte_184 = 1;
            field_370 = x_ec;
            field_374 = y_f0;
        }
        return;
    case 910: {
        float payload[3];
        SELECT();
        if (sequence_id_13e == 0) {
            replace_auxiliary(992);
            aux_154->x_e8 = x_ec;
            aux_154->y_ec = owner_348->y_f0;
            aux_154->scale_x_f8 = 10;
            aux_154->scale_y_fc = 2;
            aux_154->facing_104 = static_cast<unsigned char>(facing_104);
        }
        if (sequence_id_13e == 4) {
            field_124 = 85;
            rotation_12c = random_float(360);
            field_370 = random_float(20) - 10.0;
        }
        if (sequence_id_13e == 5) {
            replace_auxiliary(992);
            aux_154->x_e8 = x_ec;
            aux_154->y_ec = y_f0;
            aux_154->scale_x_f8 = 2;
            aux_154->scale_y_fc = 2;
            aux_154->facing_104 = static_cast<unsigned char>(facing_104);
        }
        if (sequence_id_13e == 9) {
            field_108 = 0;
            byte_184 = 1;
            field_10c = 135;
            velocity_x_f4 = 0;
            velocity_y_f8 = 20;
            field_370 = -230;
            replace_auxiliary(992);
            aux_154->x_e8 = x_ec;
            aux_154->y_ec = owner_348->y_f0;
            aux_154->scale_x_f8 = 10;
            aux_154->scale_y_fc = 2;
            aux_154->facing_104 = static_cast<unsigned char>(facing_104);
            payload[0] = 0;
            payload[1] = 0;
            payload[2] = 0;
            SPAWN(910, x_ec, static_cast<float>(y_f0 + 130.0), 1, 3);
        }
        if (sequence_id_13e == 10) {
            field_108 = 0;
            byte_184 = 1;
            field_10c = 135;
            field_370 = -250;
            replace_auxiliary(992);
            aux_154->x_e8 = x_ec;
            aux_154->y_ec = owner_348->y_f0;
            aux_154->scale_x_f8 = 10;
            aux_154->scale_y_fc = 2;
            aux_154->facing_104 = static_cast<unsigned char>(facing_104);
            payload[0] = 0;
            payload[1] = 0;
            payload[2] = 0;
            SPAWN(910, x_ec, static_cast<float>(y_f0 + 130.0), 1, 3);
        }
        if (sequence_id_13e == 12) {
            motion_004.set_components(params_340[0], params_340[1]);
            byte_184 = 1;
            scale_y_120 = scale_x_11c = static_cast<float>(random_float(6) * static_cast<double>(0.1f) + 0.75);
            for (int n = 3; n != 0; --n) {
                payload[0] = -10.0 - random_float(80);
                payload[1] = random_float(8) + 5.0;
                payload[2] = 13;
                UNSPAWN(910, x_ec, y_f0, 1, 3);
            }
        }
        if (sequence_id_13e == 13) {
            motion_004.set_components(params_340[0], params_340[1]);
            scale_y_120 = scale_x_11c = static_cast<float>(random_float(6) * static_cast<double>(0.1f) + 0.75);
        }
        return;
    }
    case 920:
        rotation_12c = params_340[0];
        SELECT();
        if (sequence_id_13e == 0) {
            scale_x_11c = 0;
            scale_y_120 = 0;
            field_370 = random_float(75) * static_cast<double>(0.01f) + 0.75;
            field_374 = 1;
            field_378 = 1;
        }
        if (sequence_id_13e == 1) {
            motion_004.set_components(params_340[0], params_340[1]);
            byte_184 = 1;
            replace_auxiliary(993);
            aux_154->x_e8 = x_ec;
            aux_154->y_ec = y_f0;
            aux_154->facing_104 = static_cast<unsigned char>(facing_104);
            scale_x_11c = 1.5f;
            scale_y_120 = random_float(5) * static_cast<double>(0.1f) + 0.5;
        }
        if (sequence_id_13e == 2)
            field_370 = 0.4f;
        return;
    case 930: {
        float payload[3];
        rotation_12c = params_340[0];
        SELECT();
        if (sequence_id_13e == 0) {
            field_370 = 1;
            scale_x_11c = 0;
            scale_y_120 = 0;
            payload[0] = 0;
            payload[1] = 0;
            payload[2] = 5;
            UNSPAWN(930, x_ec, y_f0, 1, 3);
        }
        if (sequence_id_13e == 1)
            field_370 = 18;
        if (sequence_id_13e == 2) {
            byte_184 = 1;
            scale_y_120 = 4;
        }
        if (sequence_id_13e == 4) {
            field_370 = 1;
            scale_x_11c = 0;
            scale_y_120 = 0;
            payload[0] = 0;
            payload[1] = 0;
            payload[2] = 5;
            UNSPAWN(930, x_ec, y_f0, 1, 3);
        }
        return;
    }
    case 940:
        rotation_12c = params_340[0];
        SELECT();
        if (sequence_id_13e == 1) {
            field_370 = 1;
            field_374 = 1;
            scale_x_11c = 0;
            scale_y_120 = 0.1f;
        }
        if (sequence_id_13e == 3) {
            byte_184 = 1;
            motion_004.set_components(params_340[0], params_340[1]);
        }
        return;
    case 980:
        continue_action_980();
        return;
    case 981:
        SELECT();
        if (sequence_id_13e == 6) {
            field_124 = 85;
            rotation_12c = random_float(360);
            field_370 = random_float(20) - 10.0;
        }
        return;
    case 998:
        field_124 = facing_104 * -30.0;
        field_128 = 65;
        return;
    case 999:
        field_108 = 60;
        byte_134 = 0;
        field_10c = 135;
        return;
    }
}

#undef UNSPAWN
#undef SPAWN
#undef MAYSELECT
#undef SELECT

} // namespace th105
