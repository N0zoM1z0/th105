#include "characters/KomachiObjectActionEntry.hpp"

// JP1.06a 0x00600390: KomachiObject primary slot +0x3C action entry initializer.
// Evidence: docs/KOMACHI_OBJECT_ENTRY_2026_10_24.md.
namespace th105 {

#define SELECT() select_sequence(static_cast<int>(params_340[2]))
#define MOVE() motion_004.set_components(params_340[0], params_340[1])
#define SPAWN(a) spawn_unparented(a, x_ec, y_f0, facing_104, 1, reinterpret_cast<const unsigned *>(payload), 3)

__forceinline static float random_float(int n) {
    return static_cast<float>(static_cast<unsigned>(selector_random_roll(n)));
}

void KomachiObjectEntryView::initialize_action_entry() {
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
        byte_184 = 1;
        SELECT();
        return;
    case 801:
        byte_184 = 1;
        SELECT();
        if (sequence_id_13e == 0) {
            replace_secondary(991, 20, 30, 2, 2);
            field_370 = x_ec;
            field_374 = y_f0;
            MOVE();
        }
        if (sequence_id_13e == 1) {
            MOVE();
            rotation_12c = random_float(360);
            scale_x_11c = 1.25f;
            scale_y_120 = 1.25f;
        }
        if (sequence_id_13e == 3)
            rotation_12c = params_340[0];
        if (sequence_id_13e == 4) {
            field_128 = params_340[0];
            field_124 = params_340[1];
        }
        return;
    case 810:
        byte_17c = 0;
        SELECT();
        if (sequence_id_13e == 0)
            byte_184 = 1;
        if (sequence_id_13e == 1 || sequence_id_13e == 4 || sequence_id_13e == 5) {
            byte_184 = 1;
            field_370 = 2;
        }
        if (sequence_id_13e == 2) {
            float scale = static_cast<float>(random_float(15) * static_cast<double>(0.1f));
            scale_y_120 = scale_x_11c = static_cast<float>(scale + 1.0);
            rotation_12c = random_float(360);
        }
        if (sequence_id_13e == 3) {
            float scale = static_cast<float>(random_float(15) * static_cast<double>(0.1f));
            scale_y_120 = scale_x_11c = static_cast<float>(scale + 1.0);
            word_364 = static_cast<short>(selector_random_roll(20) + 10);
            rotation_12c = random_float(360);
        }
        return;
    case 811:
        byte_17c = 4;
        byte_184 = 1;
        SELECT();
        return;
    case 812:
        byte_17c = 8;
        SELECT();
        if (sequence_id_13e == 0) {
            byte_184 = 1;
            y_f0 = stage_height();
        }
        if (sequence_id_13e == 1) {
            float scale = static_cast<float>(random_float(15) * static_cast<double>(0.1f));
            scale_y_120 = scale_x_11c = static_cast<float>(scale + 1.0);
            word_364 = static_cast<short>(selector_random_roll(20) + 10);
            rotation_12c = random_float(360);
        }
        if (sequence_id_13e == 2) {
            byte_184 = 1;
            y_f0 = stage_height();
        }
        if (sequence_id_13e == 3) {
            float scale = static_cast<float>(random_float(15) * static_cast<double>(0.1f));
            scale_y_120 = scale_x_11c = static_cast<float>(scale + 1.0);
            rotation_12c = random_float(360);
            field_370 = static_cast<float>(random_float(25) * static_cast<double>(0.01f) + 0.25);
        }
        return;
    case 815:
        byte_17c = 1;
        byte_184 = 1;
        scale_y_120 = scale_x_11c = static_cast<float>(random_float(40) * static_cast<double>(0.01f) + static_cast<double>(0.8f));
        rotation_12c = static_cast<float>(mt19937_next_u32() % 360);
        SELECT();
        word_364 = 0;
        if (sequence_id_13e == 0)
            MOVE();
        if (sequence_id_13e == 2) {
            MOVE();
            rotation_12c = random_float(360);
            scale_x_11c = 1.25f;
            scale_y_120 = 1.25f;
        }
        return;
    case 817:
        byte_17c = 5;
        SELECT();
        if (sequence_id_13e == 0) {
            double scale = static_cast<float>(random_float(50) * static_cast<double>(0.01f));
            scale_y_120 = scale_x_11c = static_cast<float>(scale + params_340[0]);
            rotation_12c = random_float(360);
            field_124 = static_cast<float>(random_float(30) - 15.0);
            field_128 = static_cast<float>(random_float(20) + 50.0);
        }
        if (sequence_id_13e == 2) {
            rotation_12c = params_340[0];
            if (static_cast<unsigned>(selector_random_roll(100)) <= 49)
                field_374 = 1;
            else
                field_374 = -1;
        }
        return;
    case 820: {
        float payload[3];
        byte_17c = 2;
        SELECT();
        if (sequence_id_13e == 0)
            alpha_113 = 0;
        if (sequence_id_13e == 1) {
            for (int n = 12; n != 0; --n) {
                payload[0] = random_float(360);
                payload[1] = static_cast<float>(random_float(30) + 10.0);
                payload[2] = 3;
                SPAWN(820);
            }
        }
        if (sequence_id_13e == 3)
            scale_y_120 = scale_x_11c = static_cast<float>(random_float(15) * static_cast<double>(0.1f) + 0.5);
        if (sequence_id_13e == 4)
            byte_184 = 1;
        if (sequence_id_13e == 5)
            velocity_y_f8 = 4;
        return;
    }
    case 821:
        byte_17c = 6;
        SELECT();
        if (sequence_id_13e == 1) {
            byte_184 = 1;
            field_370 = 1;
        }
        if (sequence_id_13e == 4)
            field_370 = 0.35f;
        if (sequence_id_13e == 2 || sequence_id_13e == 3)
            scale_x_11c = params_340[0];
        return;
    case 822:
        byte_17c = 10;
        SELECT();
        if (sequence_id_13e == 0) {
            field_370 = static_cast<float>(10.0 - random_float(20));
            rotation_12c = random_float(360);
            scale_y_120 = scale_x_11c = static_cast<float>(random_float(10) * static_cast<double>(0.1f) + 0.5);
            alpha_113 = 0;
        }
        return;
    case 825:
        byte_184 = 1;
        byte_17c = 3;
        SELECT();
        if (sequence_id_13e == 0) {
            replace_secondary(994, 20, 30, 2, 2);
            field_370 = x_ec;
            field_374 = y_f0;
            MOVE();
        }
        word_364 = 0;
        if (sequence_id_13e == 1) {
            MOVE();
            rotation_12c = random_float(360);
            scale_x_11c = 1.25f;
            scale_y_120 = 1.25f;
        }
        if (sequence_id_13e == 3)
            rotation_12c = params_340[0];
        return;
    case 826:
        byte_184 = 1;
        SELECT();
        if (sequence_id_13e == 1) {
            MOVE();
            rotation_12c = random_float(360);
        }
        if (sequence_id_13e == 3)
            rotation_12c = params_340[0];
        return;
    case 827:
        SELECT();
        if (sequence_id_13e == 0) {
            replace_secondary(993, 20, 30, 2, 2);
            MOVE();
        }
        if (sequence_id_13e == 1) {
            MOVE();
            rotation_12c = random_float(360);
            scale_x_11c = 1.25f;
            scale_y_120 = 1.25f;
        }
        return;
    case 850:
        SELECT();
        if (sequence_id_13e == 1) {
            rotation_12c = random_float(360);
            field_370 = 0.5f;
            MOVE();
            float scale = static_cast<float>(random_float(10) * static_cast<double>(0.1f));
            scale_y_120 = scale_x_11c = static_cast<float>(scale + 1.0);
        }
        return;
    case 852:
        byte_184 = 1;
        SELECT();
        if (sequence_id_13e == 0) {
            replace_secondary(991, 20, 30, 2, 2);
            field_370 = x_ec;
            field_374 = y_f0;
            MOVE();
        }
        if (sequence_id_13e == 1) {
            MOVE();
            rotation_12c = random_float(360);
            scale_x_11c = 1.25f;
            scale_y_120 = 1.25f;
        }
        return;
    case 853:
        SELECT();
        if (sequence_id_13e == 0) {
            velocity_x_f4 = params_340[0];
            byte_184 = 1;
            time_counter_144 = static_cast<short>(selector_random_roll(360));
            float scale = static_cast<float>(random_float(50) * static_cast<double>(0.01f));
            scale_y_120 = scale_x_11c = static_cast<float>(scale + 1.0);
        }
        if (sequence_id_13e == 3) {
            rotation_12c = random_float(360);
            field_370 = 0.5f;
            MOVE();
            float scale = static_cast<float>(random_float(10) * static_cast<double>(0.1f));
            scale_y_120 = scale_x_11c = static_cast<float>(scale + 1.0);
        }
        return;
    case 854:
        SELECT();
        if (sequence_id_13e == 0 || sequence_id_13e == 1) {
            field_374 = 10;
            velocity_y_f8 = 10;
        }
        if (sequence_id_13e == 2 || sequence_id_13e == 3) {
            rotation_12c = random_float(360);
            field_370 = 0.5f;
            MOVE();
            float scale = static_cast<float>(random_float(10) * static_cast<double>(0.1f));
            scale_y_120 = scale_x_11c = static_cast<float>(scale + 1.0);
        }
        if (sequence_id_13e == 4) {
            float scale = static_cast<float>(random_float(15) * static_cast<double>(0.1f));
            scale_y_120 = scale_x_11c = static_cast<float>(scale + 0.5);
        }
        return;
    case 855:
        SELECT();
        if (sequence_id_13e == 0) {
            replace_secondary(993, 20, 30, 2, 2);
            MOVE();
        }
        if (sequence_id_13e == 1) {
            MOVE();
            rotation_12c = random_float(360);
            scale_x_11c = 1.25f;
            scale_y_120 = 1.25f;
        }
        return;
    case 856:
        SELECT();
        if (sequence_id_13e == 0) {
            byte_184 = 1;
            velocity_y_f8 = params_340[1];
        }
        if (sequence_id_13e == 1) {
            float scale = static_cast<float>(random_float(25) * static_cast<double>(0.1f));
            scale_y_120 = scale_x_11c = static_cast<float>(scale + 1.0);
            word_364 = static_cast<short>(selector_random_roll(20) + 10);
            rotation_12c = random_float(360);
        }
        if (sequence_id_13e == 2)
            field_370 = 1;
        if (sequence_id_13e == 3) {
            float scale = static_cast<float>(random_float(15) * static_cast<double>(0.1f));
            scale_y_120 = scale_x_11c = static_cast<float>(scale + 1.0);
            word_364 = static_cast<short>(selector_random_roll(20) + 10);
            rotation_12c = random_float(360);
            field_374 = static_cast<float>(random_float(8) - 4.0);
        }
        if (sequence_id_13e == 4)
            field_370 = 0.6f;
        return;
    case 861:
        SELECT();
        if (sequence_id_13e == 1) {
            byte_184 = 1;
            field_370 = 1;
        }
        if (sequence_id_13e == 4)
            field_370 = 0.5f;
        return;
    case 900:
        SELECT();
        if (sequence_id_13e == 0) {
            alpha_113 = 0;
            field_370 = static_cast<float>(random_float(20) * static_cast<double>(0.1f) + 2.0);
            if (static_cast<unsigned>(selector_random_roll(100)) < 50)
                field_370 = -field_370;
        }
        if (sequence_id_13e == 1)
            scale_y_120 = scale_x_11c = static_cast<float>(random_float(10) * static_cast<double>(0.1f) + 0.5);
        if (sequence_id_13e == 2)
            byte_184 = 1;
        if (sequence_id_13e == 3)
            rotation_12c = params_340[0];
        if (sequence_id_13e == 4) {
            byte_184 = 1;
            field_370 = 1;
        }
        if (sequence_id_13e == 5)
            scale_y_120 = scale_x_11c = static_cast<float>(random_float(10) * static_cast<double>(0.1f) + 0.5);
        return;
    case 901:
        SELECT();
        if (sequence_id_13e == 1)
            field_370 = 1;
        if (sequence_id_13e == 2 || sequence_id_13e == 3)
            scale_x_11c = 2;
        if (sequence_id_13e == 4)
            field_370 = 0.6f;
        if (sequence_id_13e == 6) {
            float scale = static_cast<float>(random_float(15) * static_cast<double>(0.1f));
            scale_y_120 = scale_x_11c = static_cast<float>(scale + 1.0);
            word_364 = static_cast<short>(selector_random_roll(20) + 10);
            rotation_12c = random_float(360);
            field_374 = static_cast<float>(random_float(8) - 4.0);
        }
        if (sequence_id_13e == 7) {
            float scale = static_cast<float>(random_float(25) * static_cast<double>(0.1f));
            scale_y_120 = scale_x_11c = static_cast<float>(scale + 1.0);
            word_364 = static_cast<short>(selector_random_roll(20) + 10);
            rotation_12c = random_float(360);
        }
        if (sequence_id_13e >= 10 && sequence_id_13e <= 13) {
            byte_184 = 1;
            velocity_y_f8 = params_340[1];
        }
        return;
    case 902: {
        float payload[3];
        SELECT();
        if (sequence_id_13e == 0) {
            byte_184 = 1;
            rotation_12c = params_340[0];
            payload[0] = 0;
            payload[1] = 0;
            payload[2] = 2;
            SPAWN(902);
            payload[2] = 3;
            SPAWN(902);
            switch (g_match_identifier) {
            case 2: case 3: word_364 = 480; break;
            case 1: word_364 = 300; break;
            case 0: word_364 = 240; break;
            }
        }
        if (sequence_id_13e == 1) {
            float scale = static_cast<float>(random_float(15) * static_cast<double>(0.1f));
            scale_y_120 = scale_x_11c = static_cast<float>(scale + 1.0);
            word_364 = static_cast<short>(selector_random_roll(20) + 10);
            rotation_12c = random_float(360);
        }
        return;
    }
    case 930: {
        float payload[3];
        byte_17c = 2;
        SELECT();
        if (sequence_id_13e == 0)
            alpha_113 = 0;
        if (sequence_id_13e == 1) {
            for (int n = 12; n != 0; --n) {
                payload[0] = random_float(360);
                payload[1] = static_cast<float>(random_float(30) + 10.0);
                payload[2] = 3;
                SPAWN(930);
            }
        }
        if (sequence_id_13e == 3)
            scale_y_120 = scale_x_11c = static_cast<float>(random_float(15) * static_cast<double>(0.1f) + 0.5);
        return;
    }
    case 980:
        continue_action_980();
        return;
    case 999:
        SELECT();
        if (sequence_id_13e == 2) {
            velocity_x_f4 = params_340[0];
            velocity_y_f8 = params_340[1];
        }
        return;
    }
}

#undef SPAWN
#undef MOVE
#undef SELECT

} // namespace th105
