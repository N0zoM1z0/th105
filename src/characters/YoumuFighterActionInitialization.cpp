// JP1.06a53A1D0: complete independently reviewed Fighter initializer.
#include "YoumuFighterActionInitialization.hpp"

namespace th105 {

void YoumuFighterActionEntryView::initialize_action_entry()
{
    if (spawned_899_7e4 == 0) {
        float payload[3] = {0, 0, 0};
        spawn_owned_object(899, static_cast<float>(x_ec - facing_104 * 600),
                           static_cast<float>(y_f0 + 100.0),
                           static_cast<unsigned char>(facing_104), -1, payload, 3);
        spawned_899_7e4 = 1;
    }

    unsigned char phase;
    switch (action_id_13c) {
    case 4:
        velocity_x_f4 = 4.0f;
        return;

    case 5:
        velocity_x_f4 = -4.0f;
        return;

    case 214:
        velocity_x_f4 = 0;
        field_736 = 0;
        velocity_y_f8 = 0;
        acceleration_y_100 = 0.6f;
        field_108 = 0;
        field_10c = 95.0f;
        field_73c = 14.5f;
        field_74c = 0;
        return;

    case 300:
    case 301:
    case 303:
    case 311:
    case 321:
    case 322:
    case 323:
        if (field_47e == 0) {
            zero_motion();
        }
        phase_state_180 = 0;
        phase_index_184 = 1;
        field_7cd = 1;
        return;

    case 302:
        if (field_47e == 0) {
            zero_motion();
        }
        phase_state_180 = 0;
        field_738 = 0;
        field_750 = 1;
        phase_index_184 = 1;
        field_7cd = 1;
        return;

    case 304:
        field_47e = 0;
        phase_state_180 = 0;
        field_750 = 1;
        phase_index_184 = 1;
        field_7cd = 1;
        zero_motion();
        return;

    case 305:
    case 308:
        phase_state_180 = 0;
        phase_index_184 = 1;
        field_7cd = 1;
        return;

    case 306:
    case 309:
        phase_state_180 = 0;
        field_730 = 0;
        phase_index_184 = 1;
        field_7cd = 1;
        return;

    case 307:
        zero_motion();
        phase_state_180 = 0;
        field_73c = 0;
        field_730 = 0;
        phase_index_184 = 1;
        field_7cd = 1;
        return;

    case 310:
        velocity_x_f4 = 0;
        phase_state_180 = 0;
        velocity_y_f8 = 0;
        field_730 = 0;
        phase_index_184 = 99;
        acceleration_y_100 = 0.5f;
        return;

    case 320:
        field_47e = 0;
        phase_state_180 = 0;
        phase_index_184 = 1;
        field_7cd = 1;
        return;

    case 400:
    case 401:
    case 402:
    case 410:
    case 411:
    case 412:
        phase_state_180 = 1;
        zero_motion();
        field_738 = 0;
        field_736 = 0;
        field_734 = 0;
        field_732 = 0;
        field_730 = 0;
        field_750 = 1;
        return;

    case 404:
        phase_state_180 = 1;
        field_738 = 0;
        field_736 = 0;
        field_734 = 0;
        field_732 = 0;
        field_730 = 0;
        field_750 = 1;
        return;

    case 408:
        velocity_x_f4 = 14.0f;
        field_47e = 0;
        phase_state_180 = 0;
        field_730 = 0;
        velocity_y_f8 = 0;
        phase_index_184 = 1;
        acceleration_y_100 = 0;
        field_7cd = 1;
        return;

    case 414:
    case 415:
    case 416:
        acceleration_y_100 = 0;
        phase_state_180 = 1;
        velocity_x_f4 *= 0.2f;
        velocity_y_f8 *= 0.2f;
        field_738 = 0;
        field_736 = 0;
        field_734 = 0;
        field_732 = 0;
        field_730 = 0;
        field_750 = 1;
        return;

    case 418:
        velocity_x_f4 = 14.0f;
        field_47e = 0;
        phase_state_180 = 0;
        field_730 = 0;
        velocity_y_f8 = 0;
        phase_index_184 = 1;
        field_7cd = 1;
        return;

    case 500:
    case 501:
        phase_state_180 = 0;
        zero_motion();
        field_750 = 1;
        return;

    case 505:
    case 506:
    case 510:
    case 511:
    case 560:
    case 561:
    case 565:
    case 566:
    case 570:
    case 571:
        phase_state_180 = 0;
        zero_motion();
        field_730 = 0;
        field_750 = 1;
        return;

    case 520:
    case 521:
    case 540:
    case 541:
    case 545:
        phase_state_180 = 0;
        phase_index_184 = 1;
        field_7cd = 1;
        zero_motion();
        field_750 = 1;
        return;

    case 525:
    case 526: {
        phase_state_180 = 0;
        phase_index_184 = 1;
        field_7cd = 1;
        zero_motion();
        signed char sequence = field_609;
        field_750 = 1;
        if (sequence >= 2) {
            select_sequence(static_cast<short>(sequence));
        }
        return;
    }

    case 529:
        field_47e = 0;
        phase_state_180 = 0;
        field_750 = 1;
        phase_index_184 = 1;
        field_7cd = 1;
        zero_motion();
        return;

    case 530:
    case 531:
        phase_state_180 = 0;
        phase_index_184 = 0;
        zero_motion();
        field_750 = 1;
        return;

    case 546:
        phase_state_180 = 0;
        phase_index_184 = 3;
        field_7cd = 3;
        zero_motion();
        field_730 = 0;
        field_750 = 1;
        return;

    case 600:
    case 603:
        phase_state_180 = 0;
        phase_index_184 = 1;
        field_7cd = 1;
        zero_motion();
        field_730 = 0;
        return;

    case 601:
        phase = 5;
        phase_state_180 = 0;
        phase_index_184 = phase;
        field_7cd = phase;
        zero_motion();
        field_730 = 0;
        return;

    case 604:
        phase = 6;
        phase_state_180 = 0;
        phase_index_184 = phase;
        field_7cd = phase;
        zero_motion();
        field_730 = 0;
        return;

    // Keep the reset-only cases after both phase changes for VC8 tail merging.
    case 602:
    case 605:
    case 606:
    case 607:
    case 710:
        phase_state_180 = 0;
        zero_motion();
        field_730 = 0;
        return;

    case 720:
    case 730:
        phase_state_180 = 0;
        zero_motion();
        field_732 = 0;
        field_734 = 0;
        field_730 = 0;
        return;

    case 797:
        zero_motion();
        dispatch_event(31);
        velocity_x_f4 = 17.5f;
        field_730 = 0;
        velocity_y_f8 = 0;
        acceleration_y_100 = 1.2f;
        return;

    case 798:
        zero_motion();
        dispatch_event(31);
        velocity_x_f4 = 17.5f;
        field_730 = 0;
        velocity_y_f8 = 0;
        acceleration_y_100 = 1.2f;
        return;

    default:
        initialize_common_action_entry();
        return;
    }
}

} // namespace th105
