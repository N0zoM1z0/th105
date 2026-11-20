// JP1.06a Suika primary action initialization 0x5AD4A0; exact callable and complete 3171-byte payload.
#include "SuikaActionInitialization.hpp"

namespace th105 {

void SuikaActionEntryView::initialize_action_entry()
{
    switch (action_id_13c) {
    case 4:
        velocity_x_f4 = 5.5f;
        return;

    case 5:
        velocity_x_f4 = -5.5f;
        return;

    case 214:
        field_736 = 0;
        velocity_x_f4 = 0;
        velocity_y_f8 = 0;
        acceleration_y_100 = 0.6f;
        field_108 = 0;
        field_10c = 72.0f;
        field_73c = 9.0f;
        field_74c = 0;
        return;

    case 300:
    case 301:
        field_750 = 1;
        if (field_47e == 0) {
            zero_motion();
        }
        phase_state_180 = 0;
        phase_index_184 = 1;
        return;

    case 302:
        zero_motion();
        phase_state_180 = 0;
        field_47e = 0;
        phase_index_184 = 1;
        field_750 = 1;
        return;

    case 303:
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
        velocity_x_f4 = 9.0f;
        phase_index_184 = 2;
        return;

    case 306:
        field_730 = 0;
        phase_state_180 = 0;
        phase_index_184 = 1;
        return;

    case 307:
        phase_index_184 = 1;
        phase_state_180 = 0;
        field_750 = 1;
        acceleration_y_100 = 0;
        velocity_x_f4 *= 0.2f;
        velocity_y_f8 *= 0.2f;
        return;

    case 308:
        phase_index_184 = 1;
        phase_state_180 = 0;
        field_750 = 1;
        return;

    case 309:
        phase_index_184 = 1;
        phase_state_180 = 0;
        if (velocity_x_f4>8.0f) {
            velocity_x_f4 = 8.0f;
        }
        if (velocity_x_f4 < -8.0f) {
            velocity_x_f4 = -8.0f;
        }
        field_750 = 1;
        return;

    case 310:
        velocity_x_f4 = 0;
        field_730 = 0;
        velocity_y_f8 = 0;
        phase_state_180 = 0;
        phase_index_184 = 99;
        acceleration_y_100 = 0.5f;
        return;

    case 320:
        field_47e = 0;
        phase_state_180 = 0;
        phase_index_184 = 1;
        return;

    case 321:
    case 322:
        if (field_47e == 0) {
            zero_motion();
        }
        phase_state_180 = 0;
        phase_index_184 = 1;
        return;

    case 330:
        phase_index_184 = 1;
        phase_state_180 = 0;
        velocity_x_f4 *= 0.5;
        velocity_y_f8 = 6.0f;
        return;

    case 331:
        zero_motion();
        phase_index_184 = 6;
        phase_state_180 = 0;
        return;

    case 400:
        phase_state_180 = 0;
        zero_motion();
        field_730 = 0;
        field_732 = 0;
        field_734 = 0;
        field_750 = 1;
        return;

    case 401:
        phase_state_180 = 0;
        zero_motion();
        field_736 = 0;
        field_732 = 0;
        field_730 = 0;
        field_750 = 1;
        return;

    case 402:
        phase_state_180 = 0;
        phase_index_184 = 1;
        zero_motion();
        field_736 = 0;
        field_732 = 0;
        field_730 = 0;
        field_750 = 1;
        return;

    case 404:
    case 405:
    case 406:
        phase_state_180 = 0;
        field_730 = 0;
        field_732 = 0;
        field_734 = 0;
        field_750 = 1;
        acceleration_y_100 = 0;
        velocity_x_f4 *= 0.2f;
        velocity_y_f8 *= 0.2f;
        return;

    case 408:
        velocity_x_f4 = 10.0f;
        field_47e = 0;
        field_730 = 0;
        phase_state_180 = 0;
        velocity_y_f8 = 0;
        phase_index_184 = 3;
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
    case 412:
        phase_state_180 = 0;
        zero_motion();
        field_732 = 0;
        field_730 = 0;
        field_750 = 1;
        return;

    case 414:
    case 415:
    case 416:
        acceleration_y_100 = 0;
        phase_state_180 = 0;
        velocity_x_f4 *= 0.2f;
        velocity_y_f8 *= 0.2f;
        field_732 = 0;
        field_730 = 0;
        field_750 = 1;
        return;

    case 418:
        velocity_x_f4 = 17.5f;
        if (field_47e == 0) {
            zero_motion();
        }
        phase_state_180 = 0;
        phase_index_184 = 1;
        return;

    case 500:
    case 501:
        field_750 = 1;
        field_17c = 0;
        zero_motion();
        phase_state_180 = 0;
        field_47e = 0;
        phase_index_184 = 1;
        field_730 = 0;
        field_732 = 0;
        return;

    case 505:
    case 506:
    case 507:
    case 508:
        field_17c = 4;
        field_750 = 1;
        zero_motion();
        phase_index_184 = 0;
        field_47e = 0;
        field_730 = 0;
        field_732 = 0;
        phase_state_180 = 1;
        return;

    case 520:
    case 521:
    case 522:
    case 523:
        field_17c = 1;
        zero_motion();
        phase_state_180 = 0;
        phase_index_184 = 1;
        field_47e = 0;
        field_730 = 0;
        return;

    case 525:
    case 526:
        field_17c = 5;
        zero_motion();
        phase_state_180 = 0;
        field_47e = 0;
        phase_index_184 = 1;
        field_730 = 0;
        return;

    case 530:
    case 531:
        field_17c = 9;
        zero_motion();
        phase_index_184 = 0;
        field_47e = 0;
        phase_state_180 = 1;
        return;

    case 540:
    case 541:
        field_17c = 2;
        phase_state_180 = 0;
        zero_motion();
        field_730 = 0;
        field_732 = 0;
        field_736 = 0;
        field_738 = 0;
        field_750 = 0;
        return;

    case 542:
        phase_state_180 = 0;
        field_17c = 2;
        phase_index_184 = 1;
        field_750 = 0;
        return;

    case 545:
    case 546:
        field_730 = 0;
        field_17c = 6;
        phase_state_180 = 0;
        zero_motion();
        field_750 = 0;
        return;

    case 560:
    case 561:
        field_17c = 3;
        phase_state_180 = 1;
        zero_motion();
        field_750 = 1;
        return;

    case 565:
    case 566:
        field_17c = 7;
        phase_state_180 = 1;
        zero_motion();
        field_736 = 0;
        field_732 = 0;
        field_730 = 0;
        field_750 = 1;
        return;

    case 567:
        field_17c = 7;
        phase_state_180 = 0;
        field_730 = 0;
        field_732 = 0;
        field_736 = 0;
        field_750 = 1;
        acceleration_y_100 = 0;
        velocity_x_f4 *= 0.2f;
        velocity_y_f8 *= 0.2f;
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
    case 650:
        phase_state_180 = 1;
        zero_motion();
        field_730 = 0;
        return;

    case 601:
    case 604:
        phase_index_184 = 1;
        phase_state_180 = 0;
        zero_motion();
        return;

    case 602:
        field_730 = 0;
        field_73c = 1;
        phase_state_180 = 0;
        phase_index_184 = 1;
        zero_motion();
        return;

    case 603:
        field_730 = 0;
        field_732 = 0;
        phase_state_180 = 0;
        phase_index_184 = 1;
        zero_motion();
        return;

    case 605:
    case 730:
        field_730 = 0;
        field_73c = 2;
        phase_state_180 = 0;
        phase_index_184 = 1;
        zero_motion();
        return;

    case 606:
        zero_motion();
        phase_state_180 = 0;
        field_47e = 0;
        return;

    case 607:
        zero_motion();
        field_47e = 0;
        field_730 = 0;
        return;

    case 608:
        field_730 = 0;
        field_732 = 0;
        phase_index_184 = 0;
        phase_state_180 = 0;
        zero_motion();
        return;

    case 610:
    case 611:
        field_730 = 0;
        field_732 = 0;
        phase_state_180 = 1;
        zero_motion();
        return;

    case 612:
    case 615:
        phase_state_180 = 1;
        zero_motion();
        field_738 = 0;
        field_736 = 0;
        field_732 = 0;
        field_730 = 0;
        field_750 = 1;
        return;

    case 613:
        phase_state_180 = 0;
        field_750 = 1;
        return;

    case 700:
        return;

    case 701:
    case 702:
    case 703:
        if (field_47e == 0) {
            zero_motion();
        }
        return;

    case 704:
    case 707:
    case 710:
    case 711:
    case 720:
        zero_motion();
        return;

    case 705:
        velocity_x_f4 = 6.0f;
        return;

    case 706:
        velocity_x_f4 = -6.0f;
        return;

    case 708:
        field_730 = 0;
        velocity_x_f4 = 0;
        return;

    case 709:
        field_730 = 0;
        return;

    case 740:
        field_73c = 0;
        field_730 = 0;
        field_740 = 0;
        field_732 = 0;
        field_734 = 0;
        field_748 = 0;
        phase_index_184 = 0;
        phase_state_180 = 0;
        zero_motion();
        return;

    case 751:
        zero_motion();
        field_73c = 0;
        phase_index_184 = 0;
        phase_state_180 = 0;
        field_47e = 0;
        field_730 = 0;
        field_732 = 0;
        return;

    case 795:
        field_73c = 200.0f;
        field_734 = 0;
        dispatch_character_wave_handle(19);
        return;

    case 797:
    case 798: {
        float payload[3];
        velocity_y_f8 = 3.0f;
        field_734 = 0;
        acceleration_y_100 = 0.1f;
        dispatch_character_wave_handle(19);
        for (float index = 0; index < 8.0f; index += 1.0f) {
            payload[0] = static_cast<float>(static_cast<float>(static_cast<unsigned>(selector_random_roll(40))) + (index * 45.0 - 20.0));
            payload[1] = static_cast<float>(static_cast<float>(static_cast<unsigned>(selector_random_roll(12))) + 16.0);
            payload[2] = 0;
            spawn_owned_object(999, x_ec, static_cast<float>(y_f0 + 100.0), facing_104, 1, payload, 3);
        }
        return;
    }

    default:
        initialize_common_action_entry();
        return;
    }
}

} // namespace th105
