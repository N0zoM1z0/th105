// JP1.06a56C840: complete target-reviewed action initializer.
#include "YuyukoActionInitialization.hpp"

namespace th105 {

void YuyukoActionEntryView::initialize_action_entry()
{
    switch (action_id_13c) {
    case 4:
        velocity_x_f4 = 4.0f;
        return;

    case 5:
        velocity_x_f4 = -4.0f;
        return;

    case 214:
        field_736 = 0;
        velocity_x_f4 = 0;
        velocity_y_f8 = 0;
        acceleration_y_100 = 0.6f;
        field_108 = 0;
        field_10c = 95.0f;
        field_73c = 9.0f;
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
        velocity_x_f4 = 12.0f;
        phase_index_184 = 1;
        acceleration_y_100 = 0;
        return;

    case 306:
        field_730 = 0;
        phase_state_180 = 0;
        phase_index_184 = 1;
        return;

    case 307:
    case 309:
        phase_index_184 = 1;
        phase_state_180 = 0;
        field_750 = 1;
        return;

    case 308:
        phase_index_184 = 4;
        phase_state_180 = 0;
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
        zero_motion();
        phase_state_180 = 0;
        phase_index_184 = 1;
        return;

    case 321:
        zero_motion();
        phase_index_184 = 1;
        phase_state_180 = 0;
        return;

    case 400:
    case 401:
    case 411:
        phase_state_180 = 0;
        zero_motion();
        field_730 = 0;
        field_732 = 0;
        field_736 = 0;
        field_750 = 1;
        return;

    case 402:
    case 410:
    case 412:
        phase_state_180 = 0;
        zero_motion();
        field_730 = 0;
        field_732 = 0;
        field_734 = 0;
        field_750 = 1;
        return;

    case 404:
    case 406:
        field_736 = 0;
        field_732 = 0;
        acceleration_y_100 = 0;
        field_730 = 0;
        phase_state_180 = 0;
        field_750 = 1;
        velocity_x_f4 *= 0.2f;
        velocity_y_f8 *= 0.2f;
        return;

    case 408:
        velocity_x_f4 = 14.5f;
        field_47e = 0;
        field_730 = 0;
        phase_state_180 = 0;
        velocity_y_f8 = 0;
        phase_index_184 = 1;
        return;

    case 409:
        field_47e = 0;
        acceleration_y_100 = 0.35f;
        field_730 = 0;
        phase_state_180 = 0;
        phase_index_184 = 1;
        return;

    case 414:
    case 416:
        acceleration_y_100 = 0;
        phase_state_180 = 0;
        velocity_x_f4 *= 0.2f;
        field_730 = 0;
        field_732 = 0;
        field_734 = 0;
        field_750 = 1;
        velocity_y_f8 *= 0.2f;
        return;

    case 415:
        field_734 = 0;
        field_732 = 0;
        acceleration_y_100 = 0;
        field_730 = 0;
        phase_state_180 = 0;
        field_750 = 1;
        velocity_x_f4 *= 0.2f;
        velocity_y_f8 *= 0.2f;
        return;

    case 418:
        velocity_x_f4 = 15.0f;
        phase_index_184 = 1;
        phase_state_180 = 0;
        return;

    case 500:
    case 501:
        field_17c = 0;
        zero_motion();
        field_47e = 0;
        field_730 = 0;
        phase_state_180 = 1;
        return;

    case 502:
    case 503:
        field_17c = 0;
        velocity_x_f4 *= 0.2f;
        velocity_y_f8 *= 0.2f;
        acceleration_y_100 = 0;
        field_47e = 0;
        field_730 = 0;
        phase_state_180 = 1;
        return;

    case 505:
    case 506:
        field_17c = 4;
        zero_motion();
        field_47e = 0;
        field_730 = 0;
        phase_state_180 = 1;
        return;

    case 507:
    case 508:
        field_17c = 4;
        velocity_x_f4 *= 0.2f;
        velocity_y_f8 *= 0.2f;
        acceleration_y_100 = 0;
        field_47e = 0;
        field_730 = 0;
        phase_state_180 = 1;
        return;

    case 510:
    case 511:
        field_17c = 8;
        zero_motion();
        phase_state_180 = 1;
        field_47e = 0;
        field_730 = 0;
        field_740 = 0;
        return;

    case 512:
    case 513:
        velocity_x_f4 *= 0.2f;
        field_47e = 0;
        field_730 = 0;
        field_17c = 8;
        phase_state_180 = 1;
        velocity_y_f8 *= 0.2f;
        acceleration_y_100 = 0;
        field_740 = 0;
        return;

    case 520:
    case 521:
        field_17c = 1;
        zero_motion();
        phase_state_180 = 0;
        field_47e = 0;
        return;

    case 522:
    case 523:
        velocity_x_f4 *= 0.2f;
        phase_state_180 = 0;
        field_47e = 0;
        field_17c = 1;
        velocity_y_f8 *= 0.2f;
        acceleration_y_100 = 0;
        return;

    case 525:
    case 526:
        field_17c = 5;
        zero_motion();
        phase_state_180 = 0;
        field_47e = 0;
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

    case 545:
    case 546:
        field_17c = 6;
        phase_state_180 = 0;
        zero_motion();
        field_730 = 0;
        field_732 = 0;
        field_736 = 0;
        field_738 = 0;
        field_750 = 1;
        return;

    case 547:
        field_17c = 2;
        phase_index_184 = 1;
        phase_state_180 = 0;
        field_750 = 0;
        return;

    case 560:
    case 561:
        field_17c = 3;
        phase_index_184 = 1;
        phase_state_180 = 0;
        zero_motion();
        field_750 = 1;
        return;

    case 562:
        field_17c = 3;
        field_736 = 0;
        field_732 = 0;
        acceleration_y_100 = 0;
        field_730 = 0;
        phase_state_180 = 0;
        field_750 = 1;
        velocity_x_f4 *= 0.2f;
        velocity_y_f8 *= 0.2f;
        return;

    case 565:
    case 566:
    case 567:
        field_17c = 7;
        phase_index_184 = 1;
        phase_state_180 = 0;
        zero_motion();
        field_750 = 1;
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
    case 602:
    case 605:
    case 606:
        phase_state_180 = 1;
        zero_motion();
        return;

    case 601:
    case 604:
    case 608:
    case 610:
    case 611:
        field_730 = 0;
        field_732 = 0;
        phase_state_180 = 1;
        zero_motion();
        return;

    case 651:
        acceleration_y_100 = 0;
        field_730 = 0;
        velocity_y_f8 *= 0.2f;
        field_732 = 0;
        phase_state_180 = 1;
        velocity_x_f4 *= 0.2f;
        return;

    case 603:
        field_730 = 0;
        field_740 = 0;
        field_732 = 0;
        phase_state_180 = 1;
        zero_motion();
        return;

    case 607:
    case 657:
        phase_state_180 = 1;
        zero_motion();
        field_730 = 0;
        field_732 = 0;
        return;

    case 612:
    case 615:
        phase_state_180 = 1;
        zero_motion();
        field_730 = 0;
        field_732 = 0;
        field_736 = 0;
        field_738 = 0;
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
        zero_motion();
        return;

    case 705:
        velocity_x_f4 = 6.0f;
        return;

    case 706:
        velocity_x_f4 = -6.0f;
        return;

    case 708:
        velocity_x_f4 = 0;
        field_730 = 0;
        return;

    case 709:
        field_730 = 0;
        return;

    case 710:
        phase_state_180 = 0;
        zero_motion();
        field_730 = 0;
        field_732 = 0;
        field_736 = 0;
        field_738 = 0;
        return;

    case 720:
    case 730:
        phase_state_180 = 0;
        zero_motion();
        field_730 = 0;
        field_73c = 0;
        return;

    case 725:
        velocity_x_f4 = 4.0f;
        field_730 = 0;
        return;

    case 726:
        field_730 = 0;
        velocity_x_f4 = -4.0f;
        return;

    case 731:
        phase_state_180 = 0;
        zero_motion();
        field_73c = 0;
        field_730 = 0;
        field_740 = y_f0;
        field_744 = 0;
        return;

    case 797:
        field_730 = 0;
        dispatch_character_wave_handle(50);
        return;

    case 798:
        field_730 = 0;
        dispatch_character_wave_handle(50);
        return;

    default:
        initialize_common_action_entry();
        return;
    }
}

} // namespace th105
