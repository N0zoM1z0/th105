// JP1.06a 0x005DF0E0: complete source.
#include "UdongeObjectActionEntry.hpp"
namespace th105 {
#define MOTION reinterpret_cast<UdongeEntryMotionView *>(reinterpret_cast<unsigned char *>(this)+4)
#define SELECT() select_sequence(static_cast<int>(parameters_340[2]))
#define MOVE() MOTION->set_components(parameters_340[0],parameters_340[1])
#define SPAWN(a,l,c) spawn_parented(a,x_ec,y_f0,facing_104,l,reinterpret_cast<const unsigned *>(payload),c)
#define UNSPAWN(a,l,c) spawn_unparented(a,x_ec,y_f0,facing_104,l,reinterpret_cast<const unsigned *>(payload),c)
#define SCALE(n,factor,base) field_120=field_11c=static_cast<float>(random_float(n)*static_cast<double>(factor)+static_cast<double>(base))
#define ROUND_SCALE(n,factor,base) { float const product=random_float(n)*static_cast<double>(factor); field_120=field_11c=static_cast<float>(product+static_cast<double>(base)); }
__forceinline static float random_float(int n) { return static_cast<float>(static_cast<unsigned>(selector_random_roll(n))); }
void UdongeObjectEntryView::initialize_action_entry()
{
    // This live float shares the observed inner-index/result storage lifetime.
    float input_scale;
    velocity_x_f4 = 0;
    velocity_y_f8 = 0;
    field_370 = 0;
    field_374 = 0;
    field_378 = 0;
    field_37c = 0;
    field_384 = 0;
    field_380 = 0;
    field_386 = 0;
    phase_index_184 = 0;
    field_364 = 0;
    field_366 = 0;
    field_368 = 0;
    field_36a = 0;
    field_36c = 0;
    switch (action_id_13c) {
    case 800: {
        float payload[3];
        field_12c = parameters_340[0];
        SELECT();
        if (sequence_id_13e == 0) {
            payload[0] = field_12c;
            payload[1] = 0;
            payload[2] = 3;
            phase_index_184 = 1;
            SPAWN(800, -1, 3);
        }
        if (sequence_id_13e == 1) {
            owner_348->dispatch_character_wave_handle(2);
            field_12c = random_float(360);
            SCALE(20, 0.1f, 0.8f);
            for (int n = 0; n < 5; ++n) {
                payload[0] = random_float(360);
                payload[1] = static_cast<float>(static_cast<unsigned>(selector_random_roll(15) + 10));
                payload[2] = 2;
                UNSPAWN(800, 1, 3);
            }
        }
        if (sequence_id_13e == 2) {
            SCALE(50, 0.01f, 0.5);
        }
        if (sequence_id_13e == 3)
            field_11c = 2;
        if (sequence_id_13e == 4) {
            payload[0] = field_12c;
            payload[1] = 0;
            payload[2] = 3;
            phase_index_184 = 0;
            SPAWN(800, -1, 3);
            alpha_113 = 128;
        }
        return;
    }

    case 801:
        field_12c = parameters_340[0];
        SELECT();
        if (sequence_id_13e == 0 || sequence_id_13e == 7)
            phase_index_184 = 1;
        if (sequence_id_13e == 1 || sequence_id_13e == 10 || sequence_id_13e == 12)
            field_120 = field_11c = 0.2f;
        if (sequence_id_13e == 2)
            field_370 = 0.4f;
        if (sequence_id_13e == 3) {
            ROUND_SCALE(100, 0.01f, 1.0);
        }
        if (sequence_id_13e == 5 || sequence_id_13e == 6) {
            field_12c = random_float(360);
            field_124 = 30.0-random_float(60);
            field_128 = 30.0-random_float(60);
            field_370 = random_float(8) + 4.0;
            float const product = random_float(8)*static_cast<double>(0.01f);
            field_374 = product + static_cast<double>(0.04f);
            ROUND_SCALE(100, 0.01f, 1.0);
        }
        return;

    case 802:
        phase_index_184 = 1;
        return;

    case 810:
        field_17c = 0;
        SELECT();
        if (sequence_id_13e == 0) {
            phase_index_184 = 1;
            field_12c = parameters_340[0];
        }
        if (sequence_id_13e == 1)
            field_120 = field_11c = 0.2f;
        if (sequence_id_13e == 2) {
            ROUND_SCALE(100, 0.01f, 1.0);
        }
        if (sequence_id_13e == 3) {
            SCALE(40, 0.01f, 0.8f);
            field_12c = random_float(360);
        }
        if (sequence_id_13e == 4) {
            SCALE(40, 0.01f, 0.8f);
            field_124 = parameters_340[0];
            field_128 = static_cast<float>(static_cast<unsigned>(selector_random_roll(30) + 45));
            field_12c = random_float(360);
        }
        if (sequence_id_13e == 5)
            field_12c = random_float(360);
        if (sequence_id_13e == 7 || sequence_id_13e == 6) {
            field_12c = random_float(360);
            field_124 = 30.0-random_float(60);
            field_128 = 30.0-random_float(60);
            field_370 = random_float(8) + 4.0;
            float const product = random_float(15)*static_cast<double>(0.01f);
            field_374 = product + static_cast<double>(0.1f);
            ROUND_SCALE(100, 0.01f, 1.0);
        }
        return;

    case 811:
        field_17c = 4;
        SELECT();
        if (sequence_id_13e == 0) {
            phase_index_184 = 1;
            field_12c = parameters_340[0];
        }
        if (sequence_id_13e == 1 || sequence_id_13e == 6)
            phase_index_184 = 1;
        if (sequence_id_13e == 3) {
            SCALE(40, 0.01f, 0.8f);
            field_124 = parameters_340[0];
            field_128 = static_cast<float>(static_cast<unsigned>(selector_random_roll(30) + 45));
            field_12c = random_float(360);
        }
        if (sequence_id_13e == 4)
            field_12c = random_float(360);
        if (sequence_id_13e == 8 || sequence_id_13e == 10 || sequence_id_13e == 11) {
            phase_index_184 = 1;
            field_120 = field_11c = 0.2f;
        }
        if (sequence_id_13e == 9) {
            ROUND_SCALE(100, 0.01f, 1.0);
        }
        return;

    case 812:
        field_17c = 8;
        field_12c = parameters_340[0];
        SELECT();
        if (sequence_id_13e == 0) {
            phase_index_184 = 1;
            MOVE();
        }
        if (sequence_id_13e == 1) {
            phase_index_184 = 1;
            MOVE();
            velocity_y_f8 = velocity_y_f8 * 0.25;
        }
        if (sequence_id_13e == 3)
            phase_index_184 = 1;
        if (sequence_id_13e == 4) {
            SCALE(40, 0.01f, 0.8f);
            field_124 = parameters_340[0];
            field_128 = static_cast<float>(static_cast<unsigned>(selector_random_roll(30) + 45));
            field_12c = random_float(360);
        }
        if (sequence_id_13e == 5)
            field_12c = random_float(360);
        if (sequence_id_13e == 7) {
            SCALE(40, 0.01f, 0.8f);
            field_12c = random_float(360);
        }
        return;

    case 815: {
        float payload[3];
        field_17c = 1;
        phase_index_184 = 10;
        field_12c = parameters_340[0];
        SELECT();
        if (sequence_id_13e == 0) {
            field_11c = 4;
            field_120 = 3;
            payload[0] = 0;
            payload[1] = 0;
            payload[2] = 3;
            SPAWN(815, 1, 3);
        }
        return;
    }

    case 816:
        field_17c = 5;
        field_12c = parameters_340[0];
        SELECT();
        if (sequence_id_13e == 0 || sequence_id_13e == 4)
            field_11c = 35;
        if (sequence_id_13e == 1)
            phase_index_184 = 7;
        return;

    case 817:
        field_128 = 60;
        field_17c = 9;
        field_124 = static_cast<signed char>(facing_104)*parameters_340[0];
        field_17c = 9;
        SELECT();
        if (sequence_id_13e == 0)
            phase_index_184 = 1;
        if (sequence_id_13e == 1)
            phase_index_184 = 3;
        if (sequence_id_13e == 2) {
            field_11c = parameters_340[3];
            field_120 = parameters_340[3];
        }
        if (sequence_id_13e == 3) {
            phase_index_184 = 1;
            goto input3_scales;
        }
        return;

    case 820:
        field_17c = 2;
        goto entry_820_821;

    case 821:
        field_17c = 6;
    entry_820_821:
        SELECT();
        if (sequence_id_13e == 3) {
            input_scale = parameters_340[0]-static_cast<double>(0.3f);
            goto heading_scale;
        }
        return;

    case 822:
        field_17c = 10;
        field_12c = random_float(360);
        SELECT();
        if (sequence_id_13e == 0)
            phase_index_184 = 10;
        if (sequence_id_13e == 1) {
            if (static_cast<unsigned>(selector_random_roll(100)) >= 50)
                field_128 = 180;
            SCALE(60, 0.01f, 0.7f);
        }
        if (sequence_id_13e == 3) {
            float const product1 = random_float(100)*static_cast<double>(0.01f);
            field_11c = product1 + 0.5;
            float const product2 = random_float(50)*static_cast<double>(0.01f);
            field_120 = product2 + 0.5;
        }
        return;

    case 825: {
        float payload[3];
        field_17c = 3;
        field_12c = parameters_340[0];
        acceleration_y_100 = 0;
        field_36c = (*reinterpret_cast<signed char *>(reinterpret_cast<unsigned char *>(owner_348) + 0x607));
        SELECT();
        if (sequence_id_13e == 2) {
            velocity_x_f4 = -4;
            velocity_y_f8 = 12.5f;
            acceleration_y_100 = 0.45f;
        }
        if (sequence_id_13e == 8) {
            payload[0] = field_12c;
            payload[1] = 0;
            payload[2] = 3;
            phase_index_184 = 1;
            SPAWN(800, -1, 3);
        }
        if (sequence_id_13e == 9)
            phase_index_184 = 1;
        if (sequence_id_13e == 10)
            field_120 = field_11c = 0.2f;
        return;
    }

    case 826:
        acceleration_y_100 = 0;
        field_17c = 7;
        SELECT();
        if (sequence_id_13e == 1)
            phase_index_184 = 1;
        if (sequence_id_13e <= 4) {
            field_108 = 0;
            field_10c = 80;
        }
        if (sequence_id_13e == 5)
            field_370 = 0.71f;
        field_12c = -parameters_340[0]*static_cast<signed char>(facing_104);
        return;

    case 848:
        SELECT();
        if (sequence_id_13e <= 2)
            set_sequence_frame(static_cast<short>(parameters_340[1]));
        if (sequence_id_13e == 3) {
            velocity_x_f4 = 12;
            velocity_y_f8 = 7;
        }
        if (sequence_id_13e == 5) {
            velocity_x_f4 = parameters_340[0];
            velocity_y_f8 = parameters_340[1];
        }
        return;

    case 849:
        SELECT();
        return;

    case 850: {
        float payload[3];
        field_128 = 60;
        SELECT();
        if (sequence_id_13e == 0) {
            phase_index_184 = 5;
            payload[1] = 0;
            payload[2] = 1;
            for (float n = 0; n < 4; n += 1.0) {
                payload[0] = n * 90.0;
                SPAWN(850, 1, 3);
            }
        }
        if (sequence_id_13e == 2) {
            field_11c = parameters_340[3];
            field_120 = parameters_340[3];
        }
        return;
    }

    case 852:
        SELECT();
        if (sequence_id_13e == 0) {
            phase_index_184 = 1;
            field_12c = parameters_340[0];
        }
        if (sequence_id_13e == 1)
            field_120 = field_11c = 0.2f;
        if (sequence_id_13e == 2) {
            ROUND_SCALE(100, 0.01f, 1.0);
        }
        if (sequence_id_13e == 3) {
            SCALE(40, 0.01f, 0.8f);
            field_12c = random_float(360);
        }
        if (sequence_id_13e == 4) {
            SCALE(40, 0.01f, 0.8f);
            field_124 = parameters_340[0];
            field_128 = static_cast<float>(static_cast<unsigned>(selector_random_roll(30) + 45));
            field_12c = random_float(360);
        }
        if (sequence_id_13e == 5)
            field_12c = random_float(360);
        return;

    case 853: {
        float payload[3];
        field_128 = 60;
        SELECT();
        if (sequence_id_13e == 0) {
            payload[1] = 0;
            payload[2] = 1;
            payload[0] = 0;
            phase_index_184 = 1;
            SPAWN(853, 1, 3);
        }
        if (sequence_id_13e == 2) {
        input3_scales:
            field_11c = parameters_340[3];
            field_120 = parameters_340[3];
        }
        return;
    }

    case 855:
        phase_index_184 = 1;
        SELECT();
        return;

    case 856: {
        float payload[3];
        SELECT();
        if (sequence_id_13e == 0) {
            payload[0] = 0;
            payload[1] = 0;
            payload[2] = 2;
            phase_index_184 = 1;
            UNSPAWN(856, 1, 3);
        }
        if (sequence_id_13e == 2)
            field_370 = 0.3f;
        if (sequence_id_13e >= 3 && sequence_id_13e <= 6) {
            field_12c = random_float(360);
            field_370 = 3.0-random_float(6);
            ROUND_SCALE(10, 0.1f, 0.5);
            MOVE();
        }
        if (sequence_id_13e == 7) {
            ROUND_SCALE(10, 0.1f, 0.5);
        }
        if (sequence_id_13e == 8) {
            ROUND_SCALE(4, 0.1f, 0.8f);
            field_12c = random_float(360);
            if (static_cast<unsigned>(selector_random_roll(100)) <= 49)
                field_374 = 1;
            else
                field_374 = -1;
        }
        return;
    }

    case 857: {
        float payload[3];
        SELECT();
        if (sequence_id_13e == 0) {
            payload[0] = 0;
            payload[1] = 0;
            payload[2] = 2;
            phase_index_184 = 1;
            UNSPAWN(857, 1, 3);
            for (int n = 0; n < 6; ++n) {
                payload[0] = random_float(360);
                payload[1] = 0;
                payload[2] = 12;
                UNSPAWN(857, 1, 3);
            }
        }
        if (sequence_id_13e == 2)
            field_370 = 0.4f;
        if (sequence_id_13e >= 3 && sequence_id_13e <= 6) {
            field_12c = random_float(360);
            field_370 = 3.0-random_float(6);
            ROUND_SCALE(10, 0.1f, 0.5);
            MOVE();
        }
        if (sequence_id_13e == 7) {
            ROUND_SCALE(10, 0.1f, 0.5);
        }
        if (sequence_id_13e == 8) {
            ROUND_SCALE(4, 0.1f, 0.8f);
            field_12c = random_float(360);
            if (static_cast<unsigned>(selector_random_roll(100)) <= 49)
                field_374 = 1;
            else
                field_374 = -1;
        }
        if (sequence_id_13e == 9)
            phase_index_184 = 1;
        if (sequence_id_13e == 10) {
            field_12c = parameters_340[0];
            field_128 = 75;
        }
        if (sequence_id_13e == 11)
            field_12c = random_float(360);
        if (sequence_id_13e == 12) {
            field_12c = parameters_340[0];
            float const product1 = random_float(5)*static_cast<double>(0.1f);
            field_11c = product1 + 1.0;
            float const product2 = random_float(10)*static_cast<double>(0.1f);
            field_120 = product2 + 1.0;
        }
        return;
    }

    case 858:
        SELECT();
        switch (sequence_id_13e) {
        case 0:
            MOVE();
            return;

        case 1:
            return;

        case 2:
            field_12c = random_float(360);
            SCALE(50, 0.01f, 1.0);
            field_370 = random_float(20)*static_cast<double>(0.1f) - 1.0;
            return;

        case 3:
            field_120 = field_11c = 3;
            alpha_113 = 0;
            return;
        }
        return;

    case 859: {
        float payload[3];
        SELECT();
        switch (sequence_id_13e) {
        case 0:
            field_12c = random_float(360);
            return;

        case 1:
            field_12c = random_float(360);
            SCALE(50, 0.01f, 1.0);
            field_128 = random_float(60) - 30.0;
            field_124 = random_float(60) - 30.0;
            if (static_cast<unsigned>(selector_random_roll(100)) >= 50)
                field_128 = field_128 + 180.0;
            return;

        case 3:
            SCALE(100, 0.01f, 1.0);
            field_12c = random_float(360);
            return;

        case 4:
            alpha_113 = static_cast<signed char>((*reinterpret_cast<float *>(reinterpret_cast<unsigned char *>(owner_348) + 0x7b4))) * 60;
            return;

        case 5:
            field_11c = 0.05f;
            return;

        case 6:
            payload[0] = 0;
            payload[1] = 0;
            payload[2] = 7;
            phase_index_184 = 1;
            UNSPAWN(859, 1, 3);
            UNSPAWN(859, 1, 3);
            UNSPAWN(859, 1, 3);
            for (float n = 0; n < 4; ++n) {
                float const angle = random_float(40)-n * 60.0 - 20.0;
                for (input_scale = 0; input_scale < 8; ++input_scale) {
                    payload[0] = static_cast<float>(static_cast<unsigned>(selector_random_roll(30))) + static_cast<double>(angle) - 15.0;
                    payload[1] = random_float(6) + input_scale * 7.0 + 12.0;
                    payload[2] = 10;
                    UNSPAWN(859, 1, 3);
                }
            }
            return;

        case 7:
            field_12c = random_float(360);
            SCALE(50, 0.01f, 1.0);
            field_128 = random_float(60) - 30.0;
            field_124 = random_float(60) - 30.0;
            if (static_cast<unsigned>(selector_random_roll(100)) >= 50)
                field_128 = field_128 + 180.0;
            return;

        case 10:
            SCALE(10, 0.1f, 1.0);
            field_12c = random_float(360);
            field_370 = 20.0-random_float(10);
            return;
        }
        return;
    }

    case 900: {
        float payload[3];
        SELECT();
        if (sequence_id_13e == 0) {
            phase_index_184 = 1;
            field_12c = parameters_340[0];
            payload[0] = 0;
            payload[1] = 0;
            payload[2] = 5;
            UNSPAWN(900, 1, 3);
        }
        if (sequence_id_13e == 1)
            field_120 = field_11c = 0.2f;
        if (sequence_id_13e == 2) {
            ROUND_SCALE(100, 0.01f, 1.0);
        }
        if (sequence_id_13e == 3) {
            SCALE(40, 0.01f, 0.8f);
            field_12c = random_float(360);
        }
        if (sequence_id_13e == 4) {
            SCALE(40, 0.01f, 0.8f);
            field_124 = parameters_340[0];
            field_128 = static_cast<float>(static_cast<unsigned>(selector_random_roll(30) + 45));
            field_12c = random_float(360);
        }
        if (sequence_id_13e == 5)
            field_12c = random_float(360);
        if (sequence_id_13e == 7 || sequence_id_13e == 6) {
            field_12c = random_float(360);
            field_124 = 30.0-random_float(60);
            field_128 = 30.0-random_float(60);
            field_370 = random_float(8) + 4.0;
            float const product = random_float(15)*static_cast<double>(0.01f);
            field_374 = product + static_cast<double>(0.1f);
            ROUND_SCALE(100, 0.01f, 1.0);
        }
        if (sequence_id_13e == 8) {
            field_12c = random_float(360);
            field_370 = random_float(10) - 5.0;
        }
        return;
    }

    case 910: {
        float payload[3];
        field_12c = parameters_340[0];
        SELECT();
        if (sequence_id_13e == 1) {
            owner_348->dispatch_character_wave_handle(2);
            field_12c = random_float(360);
            SCALE(20, 0.1f, 0.8f);
            for (int n = 0; n < 5; ++n) {
                payload[0] = random_float(360);
                payload[1] = static_cast<float>(static_cast<unsigned>(selector_random_roll(15) + 10));
                payload[2] = 2;
                UNSPAWN(800, 1, 3);
            }
        }
        if (sequence_id_13e == 2) {
            SCALE(50, 0.01f, 0.5);
        }
        if (sequence_id_13e == 3)
            field_11c = 2;
        if (sequence_id_13e == 4) {
            payload[0] = field_12c;
            payload[1] = 0;
            payload[2] = 3;
            phase_index_184 = 0;
            SPAWN(910, -1, 3);
            payload[2] = 1;
            UNSPAWN(910, -1, 3);
            alpha_113 = 128;
        }
        return;
    }

    case 911:
        SELECT();
        if (sequence_id_13e == 0) {
            field_374 = -atan2_degrees(static_cast<float>(peer_170->y_f0 + 100.0-y_f0), static_cast<float>((peer_170->x_ec-x_ec)*static_cast<signed char>(facing_104)));
        }
        if (sequence_id_13e == 3) {
            field_12c = random_float(360);
            input_scale = parameters_340[0]-static_cast<double>(0.3f);
        heading_scale:
            alpha_113 = 0;
            field_120 = field_11c = input_scale;
        }
        return;

    case 912:
        field_12c = parameters_340[0];
        SELECT();
        if (sequence_id_13e == 0 || sequence_id_13e == 4)
            field_11c = 35;
        return;

    case 920: {
        float payload[3];
        SELECT();
        if (sequence_id_13e == 1) {
            MOVE();
            alpha_113 = 192;
        }
        if (sequence_id_13e == 14) {
            owner_348->dispatch_character_wave_handle(2);
            field_12c = parameters_340[0];
            MOVE();
            payload[0] = field_12c;
            payload[1] = 0;
            payload[2] = 15;
            phase_index_184 = 1;
            UNSPAWN(920, 1, 3);
            payload[0] = field_12c;
            payload[1] = 0;
            payload[2] = 17;
            SPAWN(920, -1, 3);
        }
        if (sequence_id_13e == 15) {
            field_12c = random_float(360);
            SCALE(20, 0.1f, 0.8f);
            for (int n = 0; n < 2; ++n) {
                payload[0] = random_float(360);
                payload[1] = static_cast<float>(static_cast<unsigned>(selector_random_roll(15) + 10));
                payload[2] = 16;
                UNSPAWN(920, 1, 3);
            }
        }
        if (sequence_id_13e == 16) {
            SCALE(50, 0.01f, 0.5);
        }
        if (sequence_id_13e == 17)
            field_11c = 2;
        return;
    }

    case 980:
        continue_action_980();
        return;

    case 998:
        return;
    }
}
}
