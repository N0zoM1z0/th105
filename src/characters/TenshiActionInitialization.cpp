// JP1.06a64A0A0: complete target-reviewed action initializer.
#include "TenshiActionInitialization.hpp"
#include <cmath>

namespace th105 {

void TenshiActionEntryView::initialize_action_entry()
{
    float payload404[3];
    switch (action_id_13c) {
    case 4:
        velocity_x_f4 = 4.5f;
        return;

    case 5:
        velocity_x_f4 = -4.5f;
        return;

    case 214:
        field_736 = 0;
        velocity_x_f4 = 0;
        velocity_y_f8 = 0;
        acceleration_y_100 = 0.6f;
        field_108 = 0;
        field_10c = 95.0f;
        field_73c = 12.0f;
        field_74c = 0;
        return;

    case 300:
    case 301:
    case 303:
    case 322:
        if (field_47e == 0) {
            zero_motion();
        }
        phase_state_180 = 0;
        phase_index_184 = 1;
        return;

    case 302:
        if (field_47e == 0) {
            zero_motion();
        }
        phase_state_180 = 0;
        phase_index_184 = 1;
        field_750 = 1;
        return;

    case 304:
        field_47e = 0;
        phase_index_184 = 1;
        phase_state_180 = 0;
        zero_motion();
        field_750 = 1;
        return;

    case 305:
        velocity_y_f8 = 0;
        field_47e = 0;
        phase_state_180 = 0;
        velocity_x_f4 = 13.5f;
        phase_index_184 = 1;
        acceleration_y_100 = 0;
        return;

    case 306:
        field_730 = 0;
        phase_state_180 = 0;
        phase_index_184 = 1;
        return;

    case 307:
        phase_state_180 = 0;
        field_730 = 0;
        phase_index_184 = 1;
        field_750 = 1;
        return;

    case 308:
        zero_motion();
        phase_index_184 = 1;
        phase_state_180 = 0;
        field_750 = 1;
        return;

    case 309:
        phase_index_184 = 1;
        phase_state_180 = 0;
        field_750 = 1;
        return;

    case 310:
        field_730 = 0;
        acceleration_y_100 = 0.5f;
        phase_state_180 = 0;
        phase_index_184 = 4;
        return;

    case 320:
        field_47e = 0;
        phase_index_184 = 1;
        phase_state_180 = 0;
        zero_motion();
        return;

    case 321:
        zero_motion();
        phase_index_184 = 1;
        phase_state_180 = 0;
        return;

    case 400:
        phase_state_180 = 0;
        zero_motion();
        field_73c = 0;
        field_730 = 0;
        field_732 = 0;
        field_744 = 0;
        field_750 = 1;
        return;

    case 401:
    case 402:
        phase_state_180 = 0;
        zero_motion();
        field_730 = 0;
        field_732 = 0;
        field_736 = 0;
        field_750 = 1;
        return;

    case 404: {
        acceleration_y_100 = 0;
        phase_state_180 = 0;
        velocity_x_f4 *= 0.2f;
        field_730 = 0;
        field_732 = 0;
        field_736 = 0;
        field_750 = 1;
        velocity_y_f8 *= 0.2f;
        payload404[0] = 0;
        payload404[1] = 0;
        payload404[2] = 2;
        spawn_owned_object(848, x_ec, y_f0, static_cast<unsigned char>(facing_104), -1, payload404, 3);
        return;
    }

    case 406: {
        float payload[3];
        acceleration_y_100 = 0;
        phase_state_180 = 0;
        velocity_x_f4 *= 0.2f;
        velocity_y_f8 *= 0.2f;
        field_730 = 0;
        field_732 = 0;
        field_736 = 0;
        field_750 = 1;
        payload[0] = 0;
        payload[1] = 0;
        payload[2] = 2;
        spawn_owned_object(848, x_ec, y_f0, static_cast<unsigned char>(facing_104), -1, payload, 3);
        return;
    }

    case 408:
        velocity_x_f4 = 13.5f;
        field_47e = 0;
        field_730 = 0;
        phase_state_180 = 0;
        velocity_y_f8 = 0;
        phase_index_184 = 4;
        return;

    case 409:
        field_47e = 0;
        acceleration_y_100 = 0.35f;
        field_730 = 0;
        phase_state_180 = 0;
        phase_index_184 = 1;
        return;

    case 410:
    case 411:
        phase_state_180 = 0;
        zero_motion();
        field_750 = 1;
        return;

    case 412:
        phase_state_180 = 0;
        zero_motion();
        return;

    case 414: {
        float payload[3];
        acceleration_y_100 = 0;
        phase_state_180 = 0;
        velocity_x_f4 *= 0.2f;
        field_750 = 1;
        velocity_y_f8 *= 0.2f;
        payload[0] = 0;
        payload[1] = 0;
        payload[2] = 2;
        spawn_owned_object(848, x_ec, y_f0, static_cast<unsigned char>(facing_104), -1, payload, 3);
        return;
    }

    case 415: {
        float payload[3];
        phase_state_180 = 0;
        acceleration_y_100 = 0;
        field_750 = 1;
        velocity_x_f4 *= 0.2f;
        velocity_y_f8 *= 0.2f;
        payload[0] = 0;
        payload[1] = 0;
        payload[2] = 2;
        spawn_owned_object(848, x_ec, y_f0, static_cast<unsigned char>(facing_104), -1, payload, 3);
        return;
    }

    case 416:
        phase_state_180 = 0;
        acceleration_y_100 = 0;
        velocity_x_f4 *= 0.2f;
        velocity_y_f8 *= 0.2f;
        return;

    case 418:
        velocity_x_f4 = 11.0f;
        if (field_47e == 0) {
            zero_motion();
        }
        phase_state_180 = 0;
        phase_index_184 = 1;
        return;

    case 500:
    case 501:
        field_17c = 0;
        zero_motion();
        field_47e = 0;
        acceleration_y_100 = 0.55f;
        field_730 = 0;
        phase_index_184 = 1;
        phase_state_180 = 1;
        return;

    case 505:
        field_17c = 4;
        zero_motion();
        phase_index_184 = 0;
        field_47e = 0;
        field_730 = 0;
        phase_state_180 = 1;
        return;

    case 520:
    case 521:
        field_17c = 1;
        zero_motion();
        field_47e = 0;
        field_730 = 0;
        phase_index_184 = 99;
        phase_state_180 = 1;
        return;

    case 525:
    case 526:
    case 527:
        field_17c = 5;
        zero_motion();
        phase_index_184 = 0;
        field_47e = 0;
        field_730 = 0;
        phase_state_180 = 1;
        return;

    case 540:
        field_17c = 2;
        phase_state_180 = 1;
        zero_motion();
        field_730 = 0;
        field_732 = 0;
        field_736 = 0;
        field_738 = 0;
        field_750 = 0;
        return;

    case 542:
        field_17c = 2;
        phase_index_184 = 1;
        phase_state_180 = 1;
        field_750 = 0;
        return;

    case 545:
    case 546:
    case 547:
    case 548: {
        field_17c = 6;
        phase_state_180 = 1;
        zero_motion();
        field_750 = 1;
        if (action_id_13c == 547 || action_id_13c == 548) {
            float payload[3];
            payload[0] = 0;
            payload[1] = 0;
            payload[2] = 2;
            spawn_owned_object(848, x_ec, y_f0, static_cast<unsigned char>(facing_104), -1, payload, 3);
        }
        return;
    }

    case 560:
    case 561:
        field_17c = 3;
        phase_state_180 = 0;
        phase_index_184 = 1;
        zero_motion();
        field_730 = 0;
        field_732 = 0;
        field_736 = 0;
        field_750 = 1;
        return;

    case 565:
    case 566:
        field_17c = 7;
        phase_state_180 = 0;
        phase_index_184 = 0;
        zero_motion();
        return;

    case 599:
        phase_state_180 = 1;
        zero_motion();
        field_730 = 0;
        field_732 = 0;
        field_736 = 0;
        field_738 = 0;
        return;

    case 600:
    case 603:
    case 606:
    case 607:
    case 657:
        zero_motion();
        phase_state_180 = 0;
        field_47e = 0;
        return;

    case 601:
    case 604:
        zero_motion();
        phase_index_184 = 1;
        phase_state_180 = 0;
        field_47e = 0;
        return;

    case 602:
        zero_motion();
        phase_state_180 = 0;
        phase_index_184 = 1;
        field_47e = 0;
        return;

    case 605:
        zero_motion();
        phase_index_184 = 1;
        phase_state_180 = 0;
        field_47e = 0;
        field_730 = 0;
        return;

    case 700:
        return;

    case 720: {
        phase_state_180 = 0;
        phase_index_184 = 1;
        zero_motion();
        field_784 = 25.0f;
        field_730 = 0;
        field_732 = 0;
        field_734 = 0;
        field_736 = 0;
        TenshiActionEntryView *peer = other_fighter_170;
        float distance = static_cast<float>((x_ec-peer->x_ec) / 45.0);
        distance = static_cast<float>(std::fabs(distance));
        field_780 = distance;
        field_788 = 0.5555555820465088f;
        return;
    }

    case 730:
        face_opponent_and_flip_horizontal_velocity();
        phase_state_180 = 0;
        zero_motion();
        field_730 = 0;
        field_73c = 0;
        return;

    case 731:
        zero_motion();
        field_730 = 0;
        field_732 = 0;
        field_736 = 0;
        field_738 = 0;
        return;

    case 740:
    case 741:
        phase_state_180 = 1;
        zero_motion();
        field_73c = 0;
        field_730 = 0;
        field_740 = 0;
        return;

    case 750: {
        float payload[3];
        field_74c = 0;
        payload[0] = 0;
        payload[1] = 0;
        payload[2] = 0;
        field_730 = 0;
        field_732 = 0;
        field_734 = 0;
        field_736 = 0;
        field_738 = 0;
        spawn_owned_object(940, static_cast<float>(x_ec + facing_104 * 30), static_cast<float>(y_f0 + 120.0), static_cast<unsigned char>(facing_104), 1, payload, 3);
        return;
    }

    case 780:
        zero_motion();
        return;

    case 788:
        field_730 = 0;
        return;

    case 795:
    case 797:
    case 798:
        field_730 = 0;
        velocity_x_f4 = 0;
        velocity_y_f8 = -15.0f;
        acceleration_y_100 = 0.5f;
        return;

    default:
        initialize_common_action_entry();
        return;
    }
}

} // namespace th105
