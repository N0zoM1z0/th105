#include "IkuObjectActionEntry.hpp"
// JP1.06a 0x0063B310, exact.
namespace th105 {
#define SKILL (*reinterpret_cast<signed char *>(owner_348+0x60F))
#define MOTION reinterpret_cast<IkuEntryMotionView *>(reinterpret_cast<unsigned char *>(this)+4)
#define SELECT() select_sequence(static_cast<int>(parameters_340[2]))
#define MOVE() MOTION->set_components(parameters_340[0],parameters_340[1])
#define SPAWN(a,x,y,layer) spawn_parented(a,x,y,facing_104,layer,reinterpret_cast<const unsigned *>(payload),3)
#define UNSPAWN(a) spawn_unparented(a,x_ec,y_f0,facing_104,1,reinterpret_cast<const unsigned *>(payload),3)
__forceinline static float random_float(int n) { return static_cast<float>(static_cast<unsigned>(selector_random_roll(n))); }
void IkuObjectEntryView::initialize_action_entry()
{
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
    case 800:
        phase_index_184 = 1;
        field_12c = parameters_340[0];
        SELECT();
        return;

    case 801: {
        float payload[3];
        phase_index_184 = 1;
        field_12c = parameters_340[0];
        SELECT();
        if (sequence_id_13e == 0)
            phase_index_184 = 3;
        if (sequence_id_13e == 3) {
            payload[0] = 0;
            payload[1] = 0;
            payload[2] = 4;
            phase_index_184 = 1;
            SPAWN(801, x_ec, y_f0, 1);
        }
        if (sequence_id_13e == 4) {
            field_364 = 255;
            replace_secondary(991, 32, 30, 1, 2);
        }
        if (sequence_id_13e == 5) {
            phase_index_184 = 1;
            MOVE();
        }
        if (sequence_id_13e == 6)
            field_120 = 0.5f;
        return;
    }

    case 802: {
        float payload[3];
        SELECT();
        if (sequence_id_13e == 0) {
            payload[0] = -20;
            payload[1] = 0;
            payload[2] = 3;
            phase_index_184 = 3;
            SPAWN(802, x_ec, y_f0, 1);
        }
        if (sequence_id_13e == 2) {
            field_12c = parameters_340[0];
            if (static_cast<unsigned>(selector_random_roll(100)) <= 49)
                field_374 = 1;
            else
                field_374 = -1;
        }
        if (sequence_id_13e == 3) {
            field_124 = static_cast<signed char>(facing_104)*parameters_340[0];
            field_128 = 70;
        }
        if (sequence_id_13e == 4) {
            field_128 = 70;
            field_12c = parameters_340[0];
            field_124 = static_cast<signed char>(facing_104)*-20.0;
        }
        if (sequence_id_13e == 5) {
            field_12c = parameters_340[0];
            if (static_cast<unsigned>(selector_random_roll(100)) <= 49)
                field_374 = 1;
            else
                field_374 = -1;
        }
        return;
    }

    case 810:
        field_11c = 2;
        field_17c = 0;
        field_120 = 0.75f;
        return;

    case 811:
        field_12c = parameters_340[0];
        SELECT();
        if (sequence_id_13e == 0)
            field_344 = 1;
        return;

    case 812:
        field_12c = parameters_340[0];
        phase_index_184 = 3;
        field_17c = 2;
        SELECT();
        field_370 = 1000;
        if (sequence_id_13e == 2)
            phase_index_184 = 1;
        return;

    case 813: {
        float payload[3];
        field_12c = parameters_340[0];
        phase_index_184 = 1;
        field_17c = 3;
        SELECT();
        if (sequence_id_13e == 0) {
            payload[0] = random_float(360);
            payload[1] = 0;
            payload[2] = 1;
            UNSPAWN(813);
        }
        return;
    }

    case 815:
        field_17c = 4;
        SELECT();
        if (sequence_id_13e == 0 || sequence_id_13e == 3)
            phase_index_184 = 4;
        if (sequence_id_13e == 1 || sequence_id_13e == 4)
            phase_index_184 = 5;
        if (sequence_id_13e == 2) {
            field_12c = parameters_340[0];
            if (static_cast<unsigned>(selector_random_roll(100)) <= 49)
                field_374 = 1;
            else
                field_374 = -1;
        }
        return;

    case 816: {
        float payload[3];
        field_17c = 5;
        SELECT();
        if (sequence_id_13e == 0 || sequence_id_13e == 6) {
            payload[0] = 0;
            payload[1] = 0;
            payload[2] = 3;
            phase_index_184 = 1;
            SPAWN(816, x_ec, y_f0, 1);
        }
        if (sequence_id_13e == 2) {
            field_12c = parameters_340[0];
            if (static_cast<unsigned>(selector_random_roll(100)) <= 49)
                field_374 = 1;
            else
                field_374 = -1;
        }
        if (sequence_id_13e == 3)
            field_128 = 70;
        if (sequence_id_13e == 4) {
            field_128 = 70;
            field_12c = parameters_340[0];
            velocity_x_f4 = -4;
        }
        if (sequence_id_13e == 5) {
            field_12c = parameters_340[0];
            if (static_cast<unsigned>(selector_random_roll(100)) <= 49)
                field_374 = 1;
            else
                field_374 = -1;
        }
        return;
    }

    case 817: {
        float payload[3];
        field_17c = 6;
        SELECT();
        if (sequence_id_13e == 0)
            field_370 = 0.5f;
        if (sequence_id_13e == 2) {
            phase_index_184 = 1;
            field_120 = 4;
        }
        if (sequence_id_13e == 3)
            field_370 = 0.5f;
        if (sequence_id_13e == 6) {
            field_120 = 30;
            payload[0] = 0;
            payload[1] = 0;
            payload[2] = 9;
            SPAWN(817, x_ec, 0, -1);
        }
        if (sequence_id_13e == 9)
            alpha_113 = 0;
        return;
    }

    case 818: {
        float payload[3];
        field_17c = 7;
        field_12c = parameters_340[0];
        SELECT();
        if (sequence_id_13e == 0) {
            velocity_x_f4 = parameters_340[0];
            velocity_y_f8 = parameters_340[1];
            payload[0] = 0;
            payload[1] = 0;
            payload[2] = 1;
            SPAWN(818, x_ec, y_f0, 1);
            payload[0] = 0;
            payload[1] = 0;
            payload[2] = 3;
            UNSPAWN(818);
        }
        if (sequence_id_13e == 1) {
            field_364 = 255;
            replace_secondary(990, 15, 30, 1, 2);
        }
        if (sequence_id_13e == 2) {
            float scale = random_float(5)*static_cast<double>(0.1f);
            field_120 = field_11c = static_cast<float>(scale + 0.75);
        }
        if (sequence_id_13e == 3) {
            payload[0] = 0;
            payload[1] = 0;
            payload[2] = 4;
            UNSPAWN(818);
        }
        if (sequence_id_13e == 4) {
            float scale = random_float(10)*static_cast<double>(0.01f);
            field_370 = scale + 0.25;
            field_124 = random_float(120) - 60.0;
            field_128 = random_float(120) - 60.0;
        }
        return;
    }

    case 823: {
        float payload[3];
        field_12c = parameters_340[0];
        field_17c = 11;
        SELECT();
        if (sequence_id_13e == 2) {
            field_11c = 0;
            phase_index_184 = 2;
            if (SKILL >= 2)
                phase_index_184 = 3;
            if (SKILL >= 4)
                phase_index_184 = 4;
            payload[0] = 0;
            payload[1] = 1;
            payload[2] = 0;
            SPAWN(823, x_ec, y_f0, 1);
            payload[0] = 0;
            payload[1] = -1;
            payload[2] = 0;
            SPAWN(823, x_ec, y_f0, 1);
        }
        if (sequence_id_13e == 3) {
            float scale = random_float(5)*static_cast<double>(0.1f);
            field_120 = field_11c = static_cast<float>(scale + 0.75);
        }
        return;
    }

    case 850:
        phase_index_184 = 1;
        field_12c = parameters_340[0];
        SELECT();
        if (sequence_id_13e == 0)
            phase_index_184 = 3;
        if (sequence_id_13e == 1) {
            field_370 = x_ec;
            field_374 = y_f0;
            field_378 = 1;
        }
        if (sequence_id_13e == 3) {
            float scale = random_float(10)*static_cast<double>(0.1f);
            field_120 = field_11c = static_cast<float>(scale + 0.5);
        }
        if (sequence_id_13e == 4)
            field_370 = 1;
        if (sequence_id_13e == 5) {
            field_12c = random_float(360);
            field_120 = field_11c = static_cast<float>(random_float(60)*static_cast<double>(0.01f) + 1.0);
        }
        return;

    case 851:
        field_11c = 2;
        field_120 = 0.75f;
        return;

    case 852: {
        float payload[3];
        phase_index_184 = 1;
        SELECT();
        field_370 = 1000;
        if (sequence_id_13e == 2)
            phase_index_184 = 1;
        if (sequence_id_13e == 5) {
            payload[0] = 0;
            payload[1] = 0;
            payload[2] = 6;
            UNSPAWN(852);
        }
        return;
    }

    case 853:
        field_12c = parameters_340[0];
        SELECT();
        if (sequence_id_13e == 0) {
            field_11c = 0;
            field_120 = 0;
        }
        if (sequence_id_13e == 1)
            field_120 = 4;
        if (sequence_id_13e == 2) {
            field_370 = 1;
            phase_index_184 = 99;
        }
        return;

    case 856: {
        float payload[3];
        field_12c = parameters_340[0];
        phase_index_184 = 1;
        SELECT();
        if (sequence_id_13e == 0) {
            payload[0] = random_float(360);
            payload[1] = 0;
            payload[2] = 1;
            UNSPAWN(856);
        }
        return;
    }

    case 857:
        field_344 = 1;
        SELECT();
        if (sequence_id_13e == 1) {
            field_120 = field_11c = static_cast<float>(random_float(5)*static_cast<double>(0.1f) + 0.5);
            field_12c = random_float(360);
            field_128 = random_float(90) - 45.0;
            field_124 = random_float(90) - 45.0;
        }
        return;

    case 859: {
        float payload[3];
        SELECT();
        if (sequence_id_13e == 1) {
            phase_index_184 = 1;
            field_120 = 4;
        }
        if (sequence_id_13e == 2) {
            phase_state_180 = 0;
            phase_index_184 = 1;
            payload[0] = 0;
            payload[1] = 0;
            payload[2] = 3;
            SPAWN(859, x_ec, stage_height(), -1);
            payload[2] = 5;
            SPAWN(859, x_ec, y_f0, 1);
            payload[2] = 6;
            SPAWN(859, x_ec, y_f0, 1);
            payload[2] = 9;
            SPAWN(859, x_ec, y_f0, -1);
        }
        if (sequence_id_13e == 3)
            alpha_113 = 0;
        if (sequence_id_13e == 4) {
            float scale = random_float(50)*static_cast<double>(0.01f);
            field_120 = field_11c = static_cast<float>(scale + 0.5);
        }
        if (sequence_id_13e == 7) {
            float scale = random_float(50)*static_cast<double>(0.01f);
            field_120 = field_11c = static_cast<float>(scale + 0.5);
            field_12c = random_float(360);
            phase_index_184 = 1;
        }
        return;
    }

    case 860:
        field_12c = parameters_340[0];
        SELECT();
        if (sequence_id_13e == 0) {
            field_370 = x_ec;
            field_374 = y_f0;
            field_378 = 45;
            field_37c = parameters_340[0];
            MOVE();
        }
        if (sequence_id_13e == 2)
            phase_index_184 = 1;
        if (sequence_id_13e == 3) {
            float scale = random_float(10)*static_cast<double>(0.1f);
            field_120 = field_11c = static_cast<float>(scale + 0.5);
        }
        if (sequence_id_13e == 4) {
            field_11c = 0;
            field_120 = 0;
        }
        if (sequence_id_13e == 6)
            phase_index_184 = 1;
        return;

    case 898:
        SELECT();
        if (sequence_id_13e == 1) {
            field_11c = 2;
            field_120 = 2;
        }
        return;

    case 899:
        field_12c = parameters_340[0];
        if (parameters_340[2]>0.0f)
            SELECT();
        return;

    case 900: {
        float payload[3];
        field_12c = parameters_340[0];
        SELECT();
        if (sequence_id_13e == 2) {
            field_11c = 0;
            payload[0] = 0;
            payload[1] = 1;
            payload[2] = 0;
            phase_index_184 = 4;
            SPAWN(900, x_ec, y_f0, 1);
            payload[0] = 0;
            payload[1] = -1;
            payload[2] = 0;
            SPAWN(900, x_ec, y_f0, 1);
        }
        if (sequence_id_13e == 3) {
            float scale = random_float(5)*static_cast<double>(0.1f);
            field_120 = field_11c = static_cast<float>(scale + 0.75);
        }
        if (sequence_id_13e == 4) {
            field_120 = 4;
            phase_index_184 = 1;
            field_11c = 0.25f;
        }
        if (sequence_id_13e == 5) {
            payload[0] = 0;
            payload[1] = 0;
            payload[2] = 4;
            SPAWN(900, x_ec, y_f0, 1);
        }
        if (sequence_id_13e == 7)
            phase_index_184 = 1;
        return;
    }

    case 910: {
        float payload[3];
        SELECT();
        if (sequence_id_13e == 1) {
            phase_index_184 = 1;
            field_120 = 4;
        }
        if (sequence_id_13e == 2)
            field_370 = 0.5f;
        if (sequence_id_13e == 4) {
            field_120 = 30;
            payload[0] = 0;
            payload[1] = 0;
            payload[2] = 6;
            SPAWN(910, x_ec, 0, -1);
        }
        if (sequence_id_13e == 6)
            alpha_113 = 0;
        if (sequence_id_13e == 7) {
            float scale = random_float(50)*static_cast<double>(0.01f);
            field_120 = field_11c = static_cast<float>(scale + 0.5);
            field_12c = random_float(360);
            phase_index_184 = 1;
        }
        return;
    }

    case 920: {
        float payload[3];
        SELECT();
        if (sequence_id_13e == 1) {
            phase_index_184 = 1;
            field_120 = 4;
        }
        if (sequence_id_13e == 2) {
            phase_index_184 = 1;
            payload[0] = 0;
            payload[1] = 0;
            payload[2] = 3;
            SPAWN(920, x_ec, stage_height(), -1);
            payload[2] = 5;
            SPAWN(920, x_ec, y_f0, 1);
            payload[2] = 6;
            SPAWN(920, x_ec, y_f0, 1);
            payload[2] = 9;
            SPAWN(920, x_ec, y_f0, -1);
        }
        if (sequence_id_13e == 3)
            alpha_113 = 0;
        if (sequence_id_13e == 4) {
            float scale = random_float(50)*static_cast<double>(0.01f);
            field_120 = field_11c = static_cast<float>(scale + 0.5);
        }
        if (sequence_id_13e == 7) {
            float scale = random_float(50)*static_cast<double>(0.01f);
            field_120 = field_11c = static_cast<float>(scale + 0.5);
            field_12c = random_float(360);
            phase_index_184 = 1;
        }
        return;
    }

    case 930:
        field_12c = parameters_340[0];
        SELECT();
        if (sequence_id_13e == 0)
            phase_index_184 = 1;
        if (sequence_id_13e == 2) {
            phase_index_184 = 1;
            field_12c += 90.0;
            field_11c = 15;
            field_120 = 0;
        }
        return;

    case 980:
        continue_action_980();
        return;

    case 995:
        field_134 = 1;
        if (parameters_340[2]>0.0f)
            SELECT();
        if (sequence_id_13e == 1) {
            float scale = random_float(10)*static_cast<double>(0.1f);
            field_120 = field_11c = static_cast<float>(scale + 1.0);
        }
        return;

    case 998:
        field_12c = random_float(360);
        field_128 = 60;
        return;
    }
}
#undef UNSPAWN
#undef SPAWN
#undef MOVE
#undef SELECT
#undef MOTION
#undef SKILL
}
