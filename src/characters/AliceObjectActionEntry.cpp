// JP1.06a AliceObject slot+3C @ 0x0050C1C0. Numeric states and offset views
// precede naming; complete callable and emitted metadata are compared together.
#include "AliceObjectActionEntry.hpp"
#include "engine/AngleAtan2.hpp"
#include <math.h>
namespace th105 {
#define MOTION reinterpret_cast<AliceEntryMotionView *>(reinterpret_cast<unsigned char *>(this)+4)
#define SELECT() select_sequence(static_cast<int>(parameters_340[2]))
#define MOVE() MOTION->set_components(parameters_340[0],parameters_340[1])
#define SPAWN(a,l,c) spawn_parented(a,x_ec,y_f0,facing_104,l,reinterpret_cast<const unsigned *>(payload),c)
#define UNSPAWN(a,l,c) spawn_unparented(a,x_ec,y_f0,facing_104,l,reinterpret_cast<const unsigned *>(payload),c)
#define AIM() { \
 field_12c=-atan2_degrees(static_cast<float>(peer_170->y_f0+100.0-y_f0),static_cast<float>(peer_170->x_ec-x_ec)); \
 field_370=(linked_object_34c->x_ec-x_ec)*(linked_object_34c->x_ec-x_ec); \
 field_374=(linked_object_34c->y_f0-y_f0)*(linked_object_34c->y_f0-y_f0); \
 float const distance=static_cast<float>(sqrt(field_374+field_370)); field_378=distance; field_11c=field_378*0.00390625; \
}
__forceinline static float random_float(int n) { return static_cast<float>(static_cast<unsigned>(selector_random_roll(n))); }
void AliceObjectEntryView::initialize_action_entry()
{
    velocity_x_f4 = 0;
    velocity_y_f8 = 0;
    field_370 = 0;
    field_374 = 0;
    field_378 = 0;
    field_384 = 0;
    field_37c = 0;
    field_386 = 0;
    field_380 = 0;
    phase_index_184 = 0;
    field_364 = 0;
    field_366 = 0;
    field_368 = 0;
    field_36a = 0;
    field_36c = 0;
    switch (action_id_13c) {
    case 800:
        phase_index_184 = 1;
        field_12c = parameters_340[0];
        SELECT();
        return;

    case 801: {
        float payload[3];
        if (parameters_340[2] >= 2)
            SELECT();
        if (sequence_id_13e == 0) {
            velocity_x_f4 = 40;
            velocity_y_f8 = 10;
        }
        if (sequence_id_13e == 7) {
            payload[0] = 0;
            payload[1] = 0;
            payload[2] = 6;
            SPAWN(803, 1, 3);
        }
        if (sequence_id_13e == 10) {
            payload[0] = 0;
            payload[1] = 0;
            payload[2] = 12;
            phase_index_184 = 8;
            SPAWN(801, 1, 3);
            for (float n = 0; n <= 3; n += 1.0) {
                payload[0] = 0;
                payload[1] = n * 90.0;
                payload[2] = 11;
                SPAWN(801, 1, 3);
            }
        }
        if (sequence_id_13e == 11) {
            field_12c = parameters_340[1];
            field_11c = 1;
            field_120 = 0;
        }
        if (sequence_id_13e == 12) {
            field_11c = 0;
            field_120 = 0;
        }
        return;
    }

    case 802:
        velocity_x_f4 = 40;
        velocity_y_f8 = 10;
        return;

    case 803: {
        float payload[3];
        SELECT();
        if (sequence_id_13e == 0) {
            velocity_x_f4 = 40;
            velocity_y_f8 = 0;
            payload[0] = 0;
            payload[1] = 0;
            payload[2] = 6;
            SPAWN(803, 1, 3);
        }
        if (sequence_id_13e == 6 && linked_object_34c)
            AIM();
        return;
    }

    case 804:
        phase_index_184 = 1;
        SELECT();
        if (sequence_id_13e >= 7) {
            field_364 = selector_random_roll(15) + 5;
            float product = random_float(15)*static_cast<double>(0.1f);
            field_120 = field_11c = static_cast<float>(product + 0.5);
        }
        return;

    case 805: {
        float payload[3];
        if (parameters_340[2] >= 2)
            SELECT();
        if (sequence_id_13e == 0) {
            velocity_x_f4 = 40;
            velocity_y_f8 = 0;
            payload[0] = 0;
            payload[1] = 0;
            payload[2] = 7;
            SPAWN(805, 1, 3);
        }
        if (sequence_id_13e == 7 && linked_object_34c)
            AIM();
        return;
    }

    case 806:
        phase_index_184 = 1;
        field_12c = parameters_340[0];
        SELECT();
        return;

    case 807:
        field_11c = 4;
        field_120 = 0.1f;
        field_12c = parameters_340[0];
        SELECT();
        field_364 = 0;
        return;

    case 810: {
        float payload[3];
        field_17c = 0;
        SELECT();
        if (sequence_id_13e == 0) {
            phase_index_184 = 4;
            if ((*reinterpret_cast<signed char *>(reinterpret_cast<unsigned char *>(owner_348) + 0x604)) >= 2)
                phase_index_184 = 5;
            if ((*reinterpret_cast<signed char *>(reinterpret_cast<unsigned char *>(owner_348) + 0x604)) >= 4)
                ++phase_index_184;
            payload[0] = 0;
            payload[1] = 0;
            payload[2] = 4;
            SPAWN(810, 1, 3);
        }
        if (sequence_id_13e == 4 && linked_object_34c)
            AIM();
        if (sequence_id_13e == 5) {
            field_120 = field_11c = 2.5f;
            field_124 = random_float(5) + 70.0;
            field_12c = random_float(360);
            alpha_113 = 0;
        }
        return;
    }

    case 811: {
        float payload[3];
        phase_index_184 = 1;
        field_17c = 4;
        SELECT();
        if (sequence_id_13e == 0) {
            payload[0] = 0;
            payload[1] = 0;
            payload[2] = 2;
            SPAWN(811, 1, 3);
        }
        if (sequence_id_13e == 2 && linked_object_34c)
            AIM();
        if (sequence_id_13e == 3) {
            field_120 = field_11c = 2;
            field_124 = random_float(5) + 70.0;
            field_12c = random_float(360);
            alpha_113 = 0;
        }
        return;
    }

    case 815: {
        float payload[3];
        field_17c = 1;
        phase_index_184 = 1;
        SELECT();
        if (sequence_id_13e == 0)
            MOVE();
        if (sequence_id_13e == 2) {
            payload[0] = 0;
            payload[1] = 0;
            payload[2] = 3;
            UNSPAWN(815, 1, 3);
            payload[2] = 4;
            UNSPAWN(815, 1, 3);
        }
        if (sequence_id_13e == 4)
            field_12c = random_float(360);
        return;
    }

    case 816: {
        float payload[3];
        field_17c = 5;
        phase_index_184 = 1;
        SELECT();
        if (sequence_id_13e == 0) {
            velocity_x_f4 = parameters_340[0];
            velocity_y_f8 = parameters_340[1];
            phase_index_184 = (*reinterpret_cast<signed char *>(reinterpret_cast<unsigned char *>(owner_348) + 0x609)) >= 4;
        }
        if (sequence_id_13e == 2) {
            payload[0] = 0;
            payload[1] = 0;
            payload[2] = 3;
            UNSPAWN(816, 1, 3);
            payload[2] = 4;
            UNSPAWN(816, 1, 3);
        }
        if (sequence_id_13e == 4)
            field_12c = random_float(360);
        return;
    }

    case 817: {
        float payload[3];
        field_17c = 9;
        phase_index_184 = 1;
        SELECT();
        if (sequence_id_13e == 0 || sequence_id_13e == 9) {
            field_135 = 1;
            velocity_x_f4 = parameters_340[0];
            velocity_y_f8 = parameters_340[1];
        }
        if (sequence_id_13e == 2) {
            payload[0] = 0;
            payload[1] = 0;
            payload[2] = 3;
            UNSPAWN(817, 1, 3);
            payload[2] = 4;
            UNSPAWN(817, 1, 3);
        }
        if (sequence_id_13e == 4)
            field_12c = random_float(360);
        return;
    }

    case 820: {
        float payload[4];
        field_17c = 2;
        SELECT();
        if (sequence_id_13e == 0) {
            phase_index_184 = 1;
            velocity_x_f4 = parameters_340[0];
            velocity_y_f8 = parameters_340[1];
            payload[0] = 0;
            payload[1] = 0;
            payload[2] = 6;
            payload[3] = 0;
            SPAWN(820, 1, 4);
        }
        if (sequence_id_13e == 6 && linked_object_34c)
            AIM();
        return;
    }

    case 821: {
        float payload[3];
        field_17c = 6;
        phase_index_184 = 1;
        SELECT();
        if (sequence_id_13e == 0) {
            velocity_x_f4 = -2;
            velocity_y_f8 = 0;
        }
        if (sequence_id_13e == 4) {
            payload[0] = 0;
            payload[1] = 0;
            payload[2] = 5;
            spawn_unparented(821, static_cast<float>(x_ec-static_cast<signed char>(facing_104) * 140), y_f0, facing_104, 1, reinterpret_cast<const unsigned *>(payload), 3);
        }
        return;
    }

    case 825: {
        float payload[3];
        field_17c = 3;
        SELECT();
        if (sequence_id_13e == 0) {
            phase_index_184 = 4;
            if ((*reinterpret_cast<signed char *>(reinterpret_cast<unsigned char *>(owner_348) + 0x607)) >= 2)
                phase_index_184 = 5;
            if ((*reinterpret_cast<signed char *>(reinterpret_cast<unsigned char *>(owner_348) + 0x607)) >= 4)
                ++phase_index_184;
            payload[0] = 0;
            payload[1] = 0;
            payload[2] = 4;
            SPAWN(810, 1, 3);
        }
        if (sequence_id_13e == 4 && linked_object_34c)
            AIM();
        if (sequence_id_13e == 5) {
            field_120 = field_11c = 2.5f;
            field_124 = random_float(5) + 70.0;
            field_12c = random_float(360);
            alpha_113 = 0;
        }
        return;
    }

    case 827:
        field_17c = 11;
        SELECT();
        if (sequence_id_13e == 0 || sequence_id_13e == 3 || sequence_id_13e == 5 || sequence_id_13e == 6)
            phase_index_184 = 1;
        if (sequence_id_13e == 2 || sequence_id_13e == 4)
            field_370 = 0.4f;
        return;

    case 830:
        field_374 = 20;
        phase_index_184 = 1;
        return;

    case 831: {
        float payload[3];
        field_17c = 7;
        phase_index_184 = 1;
        phase_state_180 = 0;
        SELECT();
        if (sequence_id_13e == 5) {
            payload[0] = 0;
            payload[1] = 0;
            payload[2] = 6;
            SPAWN(831, 1, 3);
        }
        if (sequence_id_13e == 6) {
            phase_index_184 = 0;
            field_11c = 50;
            field_120 = 0.1f;
        }
        return;
    }

    case 834: {
        float payload[3];
        phase_index_184 = 1;
        field_17c = 7;
        SELECT();
        if (sequence_id_13e == 5) {
            payload[0] = 0;
            payload[1] = 0;
            payload[2] = 6;
            SPAWN(834, 1, 3);
        }
        if (sequence_id_13e == 6) {
            phase_index_184 = 0;
            field_11c = 50;
            field_120 = 0.1f;
        }
        return;
    }

    case 849: {
        float payload[3];
        SELECT();
        if (sequence_id_13e == 1) {
            payload[0] = 0;
            payload[1] = 0;
            payload[2] = 10;
            SPAWN(849, 1, 3);
        }
        if (sequence_id_13e == 5 || sequence_id_13e == 13)
            field_12c = parameters_340[0];
        if (sequence_id_13e == 6) {
            payload[0] = 0;
            payload[1] = 0;
            payload[2] = 10;
            SPAWN(849, 1, 3);
        }
        if (sequence_id_13e == 8) {
            for (int n = 0; n < 6; ++n) {
                payload[0] = n * 60.0 + 30.0;
                payload[1] = 0;
                payload[2] = 6;
                if (!(payload[0] <= 90.0) && !(payload[0] >= 270.0))
                    SPAWN(849, 1, 3);
                else
                    SPAWN(849, -1, 3);
            }
        }
        if (sequence_id_13e == 10 && linked_object_34c)
            AIM();
        if (sequence_id_13e == 11) {
            payload[0] = 0;
            payload[1] = 0;
            payload[2] = 10;
            SPAWN(849, 1, 3);
            phase_index_184 = 1;
            phase_state_180 = 0;
            field_12c = parameters_340[0];
        }
        if (sequence_id_13e == 14) {
            payload[0] = 0;
            payload[1] = 0;
            payload[2] = 10;
            SPAWN(849, 1, 3);
        }
        if (sequence_id_13e == 16) {
            for (int n = 0; n < 6; ++n) {
                payload[0] = n * 60.0 + 30.0;
                payload[1] = 0;
                payload[2] = 14;
                if (!(payload[0] <= 90.0) && !(payload[0] >= 270.0))
                    SPAWN(849, 1, 3);
                else
                    SPAWN(849, -1, 3);
            }
        }
        if (sequence_id_13e == 19) {
            payload[0] = 0;
            payload[1] = 0;
            payload[2] = 10;
            SPAWN(849, 1, 3);
        }
        if (sequence_id_13e == 22) {
            field_120 = field_11c = 2;
            field_124 = random_float(5) + 70.0;
            field_12c = random_float(360);
            alpha_113 = 0;
        }
        return;
    }

    case 850: {
        float payload[3];
        phase_index_184 = 1;
        SELECT();
        if (sequence_id_13e == 0) {
            float const dx = peer_170->x_ec-x_ec;
            float const magnitude = static_cast<float>(fabs(static_cast<double>(dx)));
            velocity_x_f4 = magnitude / 42.0;
            if (velocity_x_f4 < 2)
                velocity_x_f4 = 2;
            velocity_y_f8 = 20;
        }
        if (sequence_id_13e == 2) {
            payload[0] = 0;
            payload[1] = 0;
            payload[2] = 3;
            UNSPAWN(850, -1, 3);
            payload[2] = 4;
            UNSPAWN(850, 1, 3);
            for (int angle = 0; angle < 360; angle += 45) {
                payload[0] = angle;
                payload[1] = 30;
                payload[2] = 5;
                UNSPAWN(850, 1, 3);
            }
        }
        if (sequence_id_13e == 5)
            field_12c = random_float(360);
        return;
    }

    case 851: {
        float payload[4];
        field_378 = 20;
        field_37c = 100;
        SELECT();
        if (sequence_id_13e == 0) {
            field_370 = x_ec;
            field_374 = y_f0;
            payload[0] = 0;
            payload[1] = 0;
            payload[2] = 4;
            payload[3] = 0;
            SPAWN(851, 1, 4);
        }
        if (sequence_id_13e == 4 && linked_object_34c)
            AIM();
        if (sequence_id_13e == 5) {
            field_120 = field_11c = 2;
            field_124 = 70;
        }
        return;
    }

    case 852: {
        float payload[3];
        phase_index_184 = 1;
        SELECT();
        if (sequence_id_13e == 5) {
            payload[0] = 0;
            payload[1] = 0;
            payload[2] = 6;
            SPAWN(852, 1, 3);
        }
        if (sequence_id_13e == 6) {
            owner_348->dispatch_character_wave_handle(23);
            field_11c = 50;
            phase_index_184 = 0;
            field_120 = 0.1f;
        }
        if (sequence_id_13e == 7)
            field_128 = 70;
        return;
    }

    case 853: {
        float payload[3];
        phase_index_184 = 1;
        SELECT();
        if (sequence_id_13e == 0) {
            float const dx = peer_170->x_ec-x_ec;
            float const magnitude = static_cast<float>(fabs(static_cast<double>(dx)));
            velocity_x_f4 = magnitude / 22.0;
            if (velocity_x_f4 < 2)
                velocity_x_f4 = 2;
            velocity_y_f8 = 20;
        }
        if (sequence_id_13e == 2) {
            payload[0] = 0;
            payload[1] = 0;
            payload[2] = 3;
            UNSPAWN(853, -1, 3);
            payload[2] = 4;
            UNSPAWN(853, 1, 3);
            for (int angle = 0; angle < 360; angle += 30) {
                payload[0] = angle;
                payload[1] = 40;
                payload[2] = 5;
                UNSPAWN(853, 1, 3);
            }
        }
        if (sequence_id_13e == 5)
            field_12c = random_float(360);
        return;
    }

    case 854: {
        float payload[4];
        field_378 = 30;
        SELECT();
        if (sequence_id_13e == 0) {
            field_370 = x_ec;
            field_374 = y_f0;
            payload[0] = 0;
            payload[1] = 0;
            payload[2] = 4;
            payload[3] = 0;
            SPAWN(851, 1, 4);
        }
        if (sequence_id_13e == 4 && linked_object_34c)
            AIM();
        if (sequence_id_13e == 5) {
            field_120 = field_11c = 2;
            field_124 = 70;
            field_12c = 0;
        }
        if (sequence_id_13e == 6) {
            field_120 = field_11c = 2.5f;
            field_124 = 70;
            field_12c = 0;
        }
        return;
    }

    case 855: {
        float payload[3];
        phase_index_184 = 1;
        SELECT();
        if (sequence_id_13e == 5) {
            payload[0] = 0;
            payload[1] = 0;
            payload[2] = 6;
            SPAWN(855, 1, 3);
        }
        if (sequence_id_13e == 6) {
            owner_348->dispatch_character_wave_handle(27);
            field_11c = 50;
            field_120 = 0.1f;
        }
        return;
    }

    case 856: {
        float payload[4];
        SELECT();
        if (sequence_id_13e == 0) {
            payload[0] = 0;
            payload[1] = 0;
            payload[2] = 7;
            SPAWN(856, 1, 3);
        }
        if (sequence_id_13e == 7 && linked_object_34c)
            AIM();
        if (sequence_id_13e == 8) {
            field_370 = (static_cast<int>(parameters_340[3])%2) * 4 - 2.0;
            phase_state_180 = 0;
            phase_index_184 = 0;
            field_11c = 4;
            field_120 = 0.1f;
            field_12c = parameters_340[0];
            payload[0] = 0;
            payload[1] = 0;
            payload[2] = 9;
            payload[3] = 0;
            SPAWN(856, 1, 4);
        }
        return;
    }

    case 857: {
        float payload[3];
        SELECT();
        if (sequence_id_13e == 0) {
            payload[0] = 0;
            payload[1] = 0;
            payload[2] = 7;
            SPAWN(857, -1, 3);
        }
        if (sequence_id_13e == 3) {
            field_370 = 1;
            field_120 = field_11c = 0.25f;
        }
        if (sequence_id_13e == 2) {
            field_12c = parameters_340[0];
            field_120 = 0;
            field_11c = 1.5f;
        }
        return;
    }

    case 858: {
        float payload[3];
        SELECT();
        if (sequence_id_13e == 1) {
            velocity_x_f4 = 10;
            payload[0] = 0;
            payload[1] = 0;
            payload[2] = 20;
            SPAWN(858, -1, 3);
            payload[2] = 24;
            SPAWN(858, -1, 3);
        }
        if (sequence_id_13e == 21 || sequence_id_13e == 22) {
            field_12c = parameters_340[0];
            MOVE();
        }
        if (sequence_id_13e == 23) {
            field_120 = field_11c = 2.5f;
            field_124 = random_float(5) + 70.0;
            field_12c = random_float(360);
            alpha_113 = 0;
        }
        if (sequence_id_13e >= 26 && sequence_id_13e <= 32) {
            phase_index_184 = 1;
            field_12c = parameters_340[0];
        }
        if (sequence_id_13e == 33) {
            payload[0] = 0;
            payload[1] = 0;
            payload[2] = 34;
            SPAWN(858, 1, 3);
        }
        if (sequence_id_13e == 34) {
            owner_348->dispatch_character_wave_handle(23);
            phase_index_184 = 0;
            field_11c = 50;
            field_120 = 0.1f;
        }
        return;
    }

    case 859:
        SELECT();
        if (sequence_id_13e == 6)
            field_120 = field_11c = static_cast<float>(random_float(10)*static_cast<double>(0.1f) + 0.5);
        return;

    case 900: {
        float payload[3];
        field_17c = 1;
        phase_index_184 = 1;
        SELECT();
        if (sequence_id_13e == 0)
            MOVE();
        if (sequence_id_13e == 3) {
            payload[0] = 0;
            payload[1] = 0;
            payload[2] = 4;
            UNSPAWN(900, 1, 3);
            payload[2] = 5;
            UNSPAWN(900, 1, 3);
        }
        if (sequence_id_13e == 5)
            field_12c = random_float(360);
        return;
    }

    case 901: {
        float payload[3];
        phase_index_184 = 1;
        SELECT();
        if (sequence_id_13e == 0) {
            payload[0] = 0;
            payload[1] = 0;
            payload[2] = 2;
            SPAWN(901, 1, 3);
        }
        if (sequence_id_13e == 2 && linked_object_34c)
            AIM();
        if (sequence_id_13e == 3 || sequence_id_13e == 4) {
            field_120 = field_11c = 2;
            field_124 = random_float(5) + 70.0;
            field_12c = random_float(360);
            alpha_113 = 0;
        }
        return;
    }

    case 902:
        SELECT();
        if (sequence_id_13e == 0) {
            phase_index_184 = 1;
            field_12c = parameters_340[0];
            MOTION->set_components(parameters_340[0], 10);
            field_370 = x_ec;
            field_374 = y_f0;
        }
        if (sequence_id_13e == 5)
            field_12c = parameters_340[0];
        return;

    case 903: {
        float payload[3];
        phase_index_184 = 1;
        field_12c = parameters_340[0];
        SELECT();
        if (sequence_id_13e <= 6) {
            payload[0] = 0;
            payload[1] = 0;
            payload[2] = sequence_id_13e + 7.0;
            UNSPAWN(903, 1, 3);
            field_120 = 0.5f;
            field_11c = 3;
        }
        return;
    }

    case 980:
        continue_action_980();
        return;
        // Explicit no-op state has its own observed switch-table entry.

    case 998:
        return;

    case 999:
        SELECT();
        if (sequence_id_13e == 0) {
            velocity_x_f4 = parameters_340[0];
            velocity_y_f8 = parameters_340[1];
        }
        return;
    }
}
#undef AIM
#undef UNSPAWN
#undef SPAWN
#undef MOVE
#undef SELECT
#undef MOTION
}
