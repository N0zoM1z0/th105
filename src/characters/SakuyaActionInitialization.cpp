#include "SakuyaActionInitialization.hpp"

namespace th105 {

void SakuyaActionEntryView::initialize_action_entry()
{
    switch (action_id_13c) {
    case 4:
        velocity_x_f4 = 6.0f;
        return;

    case 5:
        velocity_x_f4 = -6.0f;
        return;

    case 214:
        field_736 = 0;
        velocity_x_f4 = 0;
        velocity_y_f8 = 0;
        acceleration_y_100 = 0.6f;
        field_108 = 0;
        field_10c = 75.0f;
        field_73c = 10.5f;
        field_74c = 0;
        return;

    case 300:
    case 301:
    case 303:
    case 321:
    case 322:
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

    case 304:
        field_47e = 0;
        phase_index_184 = 2;
        phase_state_180 = 0;
        zero_motion();
        field_750 = 1;
        return;

    case 305:
        velocity_y_f8 = 0;
        if (velocity_x_f4 < 12.5) {
            velocity_x_f4 = 12.5f;
        }
        acceleration_y_100 = 0;
        field_47e = 0;
        phase_state_180 = 0;
        phase_index_184 = 1;
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
        velocity_x_f4 *= 0.2f;
        velocity_y_f8 *= 0.2f;
        acceleration_y_100 = 0;
        phase_index_184 = 1;
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
        phase_state_180 = 0;
        phase_index_184 = 1;
        return;

    case 400:
    case 401:
    case 402:
        phase_state_180 = 0;
        zero_motion();
        field_750 = 1;
        field_730 = 0;
        field_732 = 0;
        field_734 = 0;
        return;

    case 404:
    case 405:
    case 406:
        field_734 = 0;
        field_732 = 0;
        acceleration_y_100 = 0;
        field_730 = 0;
        phase_state_180 = 0;
        field_750 = 1;
        velocity_x_f4 *= 0.2f;
        velocity_y_f8 *= 0.2f;
        return;

    case 408:
        velocity_x_f4 = 12.5f;
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
        phase_state_180 = 0;
        zero_motion();
        field_730 = 0;
        field_73c = 0;
        field_732 = 0;
        field_734 = 0;
        field_750 = 1;
        return;

    case 411:
        phase_state_180 = 0;
        zero_motion();
        field_750 = 1;
        field_736 = 0;
        field_732 = 0;
        field_730 = 0;
        return;

    case 412:
        phase_state_180 = 0;
        zero_motion();
        field_730 = 0;
        field_732 = 0;
        field_736 = 0;
        field_738 = 0;
        return;

    case 414:
        field_73c = 0;
        phase_state_180 = 0;
        acceleration_y_100 = 0;
        velocity_x_f4 *= 0.2f;
        field_730 = 0;
        field_732 = 0;
        field_734 = 0;
        field_750 = 1;
        velocity_y_f8 *= 0.2f;
        return;

    case 415:
    case 416:
        acceleration_y_100 = 0;
        phase_state_180 = 0;
        field_750 = 1;
        velocity_x_f4 *= 0.2f;
        field_730 = 0;
        field_732 = 0;
        field_734 = 0;
        velocity_y_f8 *= 0.2f;
        return;

    case 418:
        if (velocity_x_f4 < 12.5) {
            velocity_x_f4 = 12.5f;
        }
        if (field_47e == 0) {
            zero_motion();
        }
        phase_state_180 = 0;
        phase_index_184 = 1;
        return;

    case 500:
        field_17c = 0;
        zero_motion();
        phase_index_184 = 4;
        phase_state_180 = 0;
        field_47e = 0;
        field_730 = 0;
        return;

    case 501:
        field_17c = 0;
        zero_motion();
        phase_index_184 = 5;
        phase_state_180 = 0;
        field_47e = 0;
        field_730 = 0;
        return;

    case 502:
        field_17c = 0;
        velocity_x_f4 *= 0.25;
        velocity_y_f8 *= 0.25;
        phase_index_184 = 4;
        phase_state_180 = 0;
        field_47e = 0;
        field_730 = 0;
        return;

    case 503:
        field_17c = 0;
        velocity_x_f4 *= 0.25;
        velocity_y_f8 *= 0.25;
        phase_index_184 = 5;
        phase_state_180 = 0;
        field_47e = 0;
        field_730 = 0;
        return;

    case 504:
        field_17c = 0;
        zero_motion();
        velocity_x_f4 = 10.0f;
        field_47e = 0;
        velocity_y_f8 = 10.0f;
        field_730 = 0;
        phase_index_184 = 1;
        acceleration_y_100 = 0.55f;
        phase_state_180 = 1;
        return;

    case 505:
    case 506:
        field_17c = 4;
        zero_motion();
        phase_index_184 = 0;
        field_47e = 0;
        phase_state_180 = 1;
        return;

    case 520:
    case 521:
        field_17c = 1;
        zero_motion();
        field_73c = 0;
        field_47e = 0;
        field_730 = 0;
        field_732 = 0;
        phase_state_180 = 1;
        field_750 = 1;
        return;

    case 525:
    case 526:
        field_17c = 5;
        zero_motion();
        field_73c = 0;
        field_47e = 0;
        field_730 = 0;
        field_732 = 0;
        phase_state_180 = 1;
        field_750 = 1;
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
    case 543:
        acceleration_y_100 = 0;
        phase_state_180 = 0;
        velocity_x_f4 *= 0.2f;
        field_730 = 0;
        field_732 = 0;
        field_736 = 0;
        field_738 = 0;
        field_750 = 0;
        field_17c = 2;
        velocity_y_f8 *= 0.2f;
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
        field_750 = 0;
        return;

    case 547:
    case 548:
        acceleration_y_100 = 0;
        field_17c = 6;
        phase_state_180 = 0;
        velocity_x_f4 *= 0.2f;
        velocity_y_f8 *= 0.2f;
        field_730 = 0;
        field_732 = 0;
        field_736 = 0;
        field_738 = 0;
        field_750 = 0;
        return;

    case 560:
    case 561:
        field_17c = 3;
        phase_state_180 = 0;
        zero_motion();
        field_750 = 1;
        field_736 = 0;
        field_732 = 0;
        field_730 = 0;
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
        field_17c = 7;
        phase_state_180 = 0;
        zero_motion();
        field_750 = 1;
        field_736 = 0;
        field_732 = 0;
        field_730 = 0;
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
        phase_state_180 = 1;
        zero_motion();
        return;

    case 601:
    case 602:
    case 605:
    case 607:
        field_730 = 0;
        field_732 = 0;
        phase_state_180 = 0;
        zero_motion();
        return;

    case 603:
    case 604:
    case 608:
    case 609:
    case 610:
    case 611:
    case 720:
        field_730 = 0;
        field_732 = 0;
        phase_state_180 = 1;
        zero_motion();
        return;

    case 606:
    case 656:
    case 710:
    case 711:
        zero_motion();
        field_47e = 0;
        return;

    case 612:
    case 615:
        phase_state_180 = 1;
        zero_motion();
        field_750 = 1;
        field_738 = 0;
        field_736 = 0;
        field_732 = 0;
        field_730 = 0;
        return;

    case 613:
        phase_state_180 = 0;
        field_750 = 1;
        return;

    case 707:
        zero_motion();
        return;

    case 708:
        field_730 = 0;
        velocity_x_f4 = 0;
        return;

    case 721:
        field_740 = 0;
        field_730 = 0;
        zero_motion();
        field_47e = 0;
        return;

    case 722:
    case 730:
        phase_state_180 = 0;
        zero_motion();
        field_730 = 0;
        field_732 = 0;
        field_736 = 0;
        return;

    case 740:
        phase_state_180 = 0;
        zero_motion();
        field_730 = 0;
        field_73c = 0;
        field_732 = 0;
        field_736 = 0;
        return;

    case 797:
        zero_motion();
        velocity_x_f4 = 12.0f;
        field_730 = 0;
        velocity_y_f8 = 0;
        acceleration_y_100 = 0.5f;
        return;

    case 798:
        zero_motion();
        field_730 = 0;
        return;

    default:
        initialize_common_action_entry();
        return;
    }
}

} // namespace th105
