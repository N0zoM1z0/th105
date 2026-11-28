#include "characters/RemiliaObjectActionEntry.hpp"

namespace th105 {

__forceinline static float random_float(int limit) {
    return static_cast<float>(static_cast<unsigned>(selector_random_roll(limit)));
}

void RemiliaObjectEntryView::initialize_action_entry() {
    velocity_x_f4 = 0.0f;
    velocity_y_f8 = 0.0f;
    field_370 = 0.0f;
    field_374 = 0.0f;
    field_378 = 0.0f;
    field_37c = 0.0f;
    word_384 = 0;
    field_380 = 0.0f;
    word_386 = 0;
    byte_184 = 0;
    word_364 = 0;
    word_366 = 0;
    word_368 = 0;
    word_36a = 0;
    word_36c = 0;
    switch (action_id_13c) {
    case 800:
        select_sequence(static_cast<int>(params_340[2]));
        if (sequence_id_13e == 0) {
            byte_184 = 1;
            motion_004.set_components(params_340[0], params_340[1]);
            rotation_12c = params_340[0];
            float payload[3];
            payload[0] = params_340[0];
            payload[1] = 0.0f;
            payload[2] = 1.0f;
            spawn_parented(800, x_ec, y_f0, facing_104, -1,
                           reinterpret_cast<const unsigned *>(payload), 3);
        }
        if (sequence_id_13e == 1)
            rotation_12c = params_340[0];
        if (sequence_id_13e == 2 || sequence_id_13e == 3) {
            rotation_12c = random_float(360);
            scale_y_120 = scale_x_11c = random_float(10) * 0.05f + 1.0f;
            motion_004.set_components(params_340[0], params_340[1]);
        }
        return;
    case 801:
        select_sequence(static_cast<int>(params_340[2]));
        if (sequence_id_13e == 0) {
            byte_184 = 10;
            motion_004.set_components(params_340[0], params_340[1]);
            rotation_12c = params_340[0];
        }
        return;
    case 803:
        byte_184 = 1;
        select_sequence(static_cast<int>(params_340[2]));
        return;
    case 810:
        byte_17c = 0;
        select_sequence(static_cast<int>(params_340[2]));
        if (sequence_id_13e == 0) {
            rotation_12c = random_float(360);
            scale_y_120 = scale_x_11c = random_float(10) * 0.05f + 1.0f;
        }
        return;
    case 811:
        select_sequence(static_cast<int>(params_340[2]));
        return;
    case 815:
        byte_184 = 1;
        rotation_12c = params_340[0];
        byte_17c = 1;
        select_sequence(static_cast<int>(params_340[2]));
        if (sequence_id_13e == 0) {
            field_128 = 70.0f;
            field_370 = 1.0f;
            field_374 = random_float(360) - 180.0f;
            field_37c = (field_374 < 0.0f) * 2;
            field_380 = 10.0f;
        }
        if (sequence_id_13e == 1) {
            replace_secondary(991, 10.0f, 20, 1, 2);
            byte_184 = 2;
            motion_004.set_components(params_340[0], params_340[1]);
            rotation_12c = params_340[0];
        }
        if (sequence_id_13e == 2) {
            field_128 = 70.0f;
            field_370 = 0.15f;
        }
        if (sequence_id_13e == 3) {
            field_128 = 70.0f;
            field_370 = 0.2f;
            field_374 = 12.0f;
        }
        return;
    case 816:
        byte_184 = 1;
        rotation_12c = params_340[0];
        byte_17c = 5;
        select_sequence(static_cast<int>(params_340[2]));
        return;
    case 817:
        byte_184 = 1;
        rotation_12c = params_340[0];
        byte_17c = 9;
        select_sequence(static_cast<int>(params_340[2]));
        if (sequence_id_13e == 0)
            motion_004.set_components(params_340[0], params_340[1]);
        return;
    case 820:
        select_sequence(static_cast<int>(params_340[2]));
        return;
    case 821:
        byte_17c = 6;
        rotation_12c = params_340[0];
        select_sequence(static_cast<int>(params_340[2]));
        if (sequence_id_13e == 0)
            byte_184 = 4;
        if (sequence_id_13e == 3)
            byte_184 = 4;
        if (sequence_id_13e == 4)
            byte_184 = 4;
        return;
    case 825:
        byte_17c = 3;
        select_sequence(static_cast<int>(params_340[2]));
        if (sequence_id_13e == 0) {
            field_108 = 0.0f;
            field_10c = 80.0f;
            rotation_12c = params_340[0];
        }
        return;
    case 826:
        byte_17c = 7;
        select_sequence(static_cast<int>(params_340[2]));
        switch (sequence_id_13e) {
        case 0:
            rotation_12c = random_float(360);
            field_124 = 85 * facing_104;
            return;
        case 1:
            rotation_12c = random_float(360);
            field_374 = random_float(20) * 0.1f - 1.0f;
            return;
        case 3:
            rotation_12c = random_float(360);
            field_124 = static_cast<float>(static_cast<unsigned>(selector_random_roll(20) + 50)) * facing_104;
            if (static_cast<unsigned>(selector_random_roll(100)) < 50)
                field_128 = 180.0f;
            scale_y_120 = scale_x_11c = random_float(40) * 0.01f + 0.8f;
            return;
        case 4:
        case 6:
            byte_184 = 1;
            return;
        case 5:
            scale_x_11c = static_cast<float>(random_float(200) * 0.01f) + 1.0f;
            scale_y_120 = static_cast<float>(random_float(100) * 0.01f) + 1.0f;
            return;
        case 7:
            scale_x_11c = static_cast<float>(random_float(200) * 0.01f) + 1.0f;
            scale_y_120 = static_cast<float>(random_float(100) * 0.01f) + 1.0f;
            return;
        }
        return;
    case 848:
        rotation_12c = params_340[0];
        select_sequence(static_cast<int>(params_340[2]));
        return;
    case 850:
        word_344 = 1;
        byte_184 = 1;
        if (params_340[2] != 0.0f)
            select_sequence(static_cast<int>(params_340[2]));
        return;
    case 851:
        if (params_340[2] != 0.0f)
            select_sequence(static_cast<int>(params_340[2]));
        if (sequence_id_13e == 0 || sequence_id_13e == 1)
            word_344 = 1;
        if (sequence_id_13e == 2 || sequence_id_13e == 3) {
            double const angle = params_340[0];
            byte_184 = 1;
            rotation_12c = static_cast<float>(angle);
        }
        if (sequence_id_13e == 4)
            field_370 = 0.25f;
        return;
    case 852:
        word_344 = 1;
        if (params_340[2] != 0.0f)
            select_sequence(static_cast<int>(params_340[2]));
        if (sequence_id_13e == 0 || sequence_id_13e == 1) {
            rotation_12c = random_float(360);
            field_128 = 45.0f;
            field_124 = -45 * facing_104;
            field_370 = 0.3f;
            field_374 = 12.0f;
        }
        return;
    case 853:
        word_344 = 1;
        byte_184 = 1;
        if (params_340[2] != 0.0f)
            select_sequence(static_cast<int>(params_340[2]));
        if (sequence_id_13e == 4)
            field_370 = 1.0f;
        if (sequence_id_13e == 6) {
            scale_x_11c = static_cast<float>(random_float(100) * 0.01f) + 0.25f;
            replace_auxiliary(990);
            aux_154->scale_x_f8 = 10.0f;
            aux_154->scale_y_fc = 10.0f;
            aux_154->x_e8 = x_ec;
            aux_154->y_ec = y_f0;
            aux_154->facing_104 = facing_104;
            velocity_y_f8 = 30.0f;
        }
        return;
    case 854:
        if (params_340[2] != 0.0f)
            select_sequence(static_cast<int>(params_340[2]));
        if (sequence_id_13e == 0 || sequence_id_13e == 1)
            word_344 = 1;
        if (sequence_id_13e == 2) {
            rotation_12c = params_340[0];
            byte_184 = 5;
            float payload[3];
            payload[0] = params_340[0];
            payload[1] = 0.0f;
            payload[2] = 6.0f;
            spawn_parented(854, x_ec, y_f0, facing_104, 1,
                           reinterpret_cast<const unsigned *>(payload), 3);
        }
        if (sequence_id_13e == 3)
            rotation_12c = params_340[0];
        if (sequence_id_13e == 4)
            field_370 = 0.25f;
        if (sequence_id_13e == 5) {
            field_128 = 70.0f;
            field_370 = 0.4f;
            field_374 = 12.0f;
        }
        if (sequence_id_13e == 6)
            rotation_12c = params_340[0];
        if (sequence_id_13e == 7)
            field_370 = 0.4f;
        return;
    case 855:
        if (params_340[2] != 0.0f)
            select_sequence(static_cast<int>(params_340[2]));
        if (sequence_id_13e == 0 || sequence_id_13e == 1) {
            rotation_12c = random_float(360);
            field_128 = 60.0f;
            field_124 = -50 * facing_104;
            field_370 = 0.6f;
            field_374 = 12.0f;
        }
        if (sequence_id_13e == 2) {
            rotation_12c = -120.0f;
            field_370 = 1.0f;
        }
        return;
    case 856:
        if (params_340[2] != 0.0f)
            select_sequence(static_cast<int>(params_340[2]));
        if (sequence_id_13e == 0 || sequence_id_13e == 1) {
            rotation_12c = random_float(360);
            field_128 = 60.0f;
            field_124 = 50 * facing_104;
            field_370 = 0.6f;
            field_374 = 12.0f;
        }
        if (sequence_id_13e == 2) {
            rotation_12c = -60.0f;
            field_370 = 1.0f;
        }
        return;
    case 857:
        byte_184 = 1;
        rotation_12c = params_340[0];
        select_sequence(static_cast<int>(params_340[2]));
        return;
    case 900:
        byte_184 = 1;
        rotation_12c = params_340[0];
        select_sequence(static_cast<int>(params_340[2]));
        return;
    case 901:
        select_sequence(static_cast<int>(params_340[2]));
        switch (sequence_id_13e) {
        case 0:
            rotation_12c = random_float(360);
            field_124 = 85 * facing_104;
            return;
        case 1:
            rotation_12c = random_float(360);
            field_374 = random_float(20) * 0.1f - 1.0f;
            return;
        case 2:
            rotation_12c = params_340[0];
            return;
        case 3:
            rotation_12c = random_float(360);
            field_124 = static_cast<float>(static_cast<unsigned>(selector_random_roll(20) + 50)) * facing_104;
            if (static_cast<unsigned>(selector_random_roll(100)) < 50)
                field_128 = 180.0f;
            scale_y_120 = scale_x_11c = random_float(40) * 0.01f + 0.8f;
            return;
        case 4:
            byte_184 = 1;
            return;
        case 5:
            scale_x_11c = static_cast<float>(random_float(200) * 0.01f) + 1.0f;
            scale_y_120 = static_cast<float>(random_float(100) * 0.01f) + 1.0f;
            return;
        case 6:
            scale_y_120 = scale_x_11c = 3.0f;
            alpha_113 = 0;
            field_124 = 85.0f;
            return;
        case 7:
            byte_184 = 1;
            motion_004.set_components(params_340[0], params_340[1]);
            return;
        case 8:
            rotation_12c = params_340[0];
            return;
        case 9:
            rotation_12c = params_340[0];
            return;
        case 10:
            rotation_12c = random_float(360);
            field_128 = static_cast<float>(static_cast<unsigned>(selector_random_roll(20) + 50));
            if (static_cast<unsigned>(selector_random_roll(100)) < 50)
                field_124 = 180.0f;
            scale_y_120 = scale_x_11c = random_float(40) * 0.01f + 0.8f;
            return;
        }
        return;
    case 902:
        select_sequence(static_cast<int>(params_340[2]));
        if (sequence_id_13e == 0 || sequence_id_13e == 5) {
            byte_184 = 1;
            rotation_12c = params_340[0];
            motion_004.set_components(params_340[0], params_340[1]);
        }
        if (sequence_id_13e == 1) {
            alpha_113 = 0;
            byte_184 = 0;
            rotation_12c = params_340[0];
            motion_004.set_components(params_340[0], params_340[1]);
        }
        if (sequence_id_13e == 2) {
            field_370 = 1.0f;
            rotation_12c = random_float(360);
            field_124 = random_float(140) - 70.0f;
            field_128 = random_float(140) - 70.0f;
        }
        if (sequence_id_13e == 3)
            scale_y_120 = scale_x_11c = random_float(10) * 0.1f + 0.5f;
        return;
    case 903:
        select_sequence(static_cast<int>(params_340[2]));
        if (sequence_id_13e == 0)
            rotation_12c = params_340[0];
        if (sequence_id_13e == 1)
            byte_184 = 1;
        if (sequence_id_13e == 2)
            scale_y_120 = scale_x_11c = random_float(10) * 0.1f + 0.5f;
        if (sequence_id_13e == 3) {
            byte_184 = 1;
            rotation_12c = params_340[0];
            motion_004.set_components(params_340[0], params_340[1]);
        }
        if (sequence_id_13e == 5)
            scale_y_120 = scale_x_11c = random_float(15) * 0.1f + 0.25f;
        if (sequence_id_13e == 6) {
            field_370 = 1.0f;
            rotation_12c = random_float(360);
            field_124 = random_float(140) - 70.0f;
            field_128 = random_float(140) - 70.0f;
        }
        if (sequence_id_13e == 7) {
            field_370 = 1.0f;
            alpha_113 = 0;
        }
        return;
    case 980:
        continue_action_980();
        return;
    case 998:
        return;
    }
}

} // namespace th105
