// JP1.06a62FFF0: complete action initializer, independently reviewed.
#include "IkuActionInitialization.hpp"

namespace th105 {

void IkuActionEntryView::initialize_action_entry()
{
    switch (action_id_13c) {
    case 4:
        velocity_x_f4 = 6.0f;
        return;

    case 5:
        velocity_x_f4 = -5.0f;
        return;

    case 214:
        reinterpret_cast<IkuEntryScratchView *>(reinterpret_cast<unsigned char *>(this) + 4)->reset();
        velocity_x_f4 = 0;
        field_736 = 0;
        velocity_y_f8 = 0;
        acceleration_y_100 = 0.6f;
        field_108 = 0;
        field_10c = 95.0f;
        field_73c = 10.0f;
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
        if (field_47e == 0) {
            zero_motion();
        }
        phase_state_180 = 0;
        field_47e = 0;
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
        velocity_x_f4 = 8.5f;
        acceleration_y_100 = 0;
        field_47e = 0;
        phase_state_180 = 0;
        phase_index_184 = 1;
        return;

    case 306:
        phase_state_180 = 0;
        field_730 = 0;
        phase_index_184 = 1;
        return;

    case 307:
    case 308:
        phase_index_184 = 1;
        phase_state_180 = 0;
        field_750 = 1;
        return;

    case 309:
        phase_index_184 = 4;
        phase_state_180 = 0;
        field_750 = 1;
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
        return;

    case 400:
    case 401:
    case 402:
        phase_state_180 = 0;
        zero_motion();
        field_750 = 1;
        return;

    case 404:
    case 406:
        phase_state_180 = 0;
        acceleration_y_100 = 0;
        field_750 = 1;
        velocity_x_f4 *= 0.2f;
        velocity_y_f8 *= 0.2f;
        return;

    case 408:
        velocity_x_f4 = 12.5f;
        velocity_y_f8 = 0;
        phase_index_184 = 1;
        field_47e = 0;
        phase_state_180 = 0;
        field_730 = 0;
        return;

    case 409:
        acceleration_y_100 = 0.35f;
        phase_index_184 = 1;
        field_47e = 0;
        phase_state_180 = 0;
        field_730 = 0;
        return;

    case 410:
        phase_state_180 = 0;
        zero_motion();
        field_736 = 0;
        field_738 = 0;
        field_732 = 0;
        field_730 = 0;
        field_750 = 1;
        return;

    case 411:
        phase_state_180 = 0;
        zero_motion();
        field_736 = 0;
        field_732 = 0;
        field_730 = 0;
        field_750 = 1;
        return;

    case 412:
        phase_state_180 = 0;
        zero_motion();
        field_736 = 0;
        field_738 = 0;
        field_732 = 0;
        field_730 = 0;
        return;

    case 414:
        acceleration_y_100 = 0;
        phase_state_180 = 0;
        velocity_x_f4 *= 0.2f;
        field_736 = 0;
        field_738 = 0;
        field_732 = 0;
        field_730 = 0;
        field_750 = 1;
        velocity_y_f8 *= 0.2f;
        return;

    case 415:
        field_736 = 0;
        acceleration_y_100 = 0;
        field_750 = 1;
        velocity_x_f4 *= 0.2f;
        phase_state_180 = 0;
        field_732 = 0;
        field_730 = 0;
        velocity_y_f8 *= 0.2f;
        return;

    case 416:
    case 417:
        acceleration_y_100 = 0;
        field_736 = 0;
        field_750 = 1;
        velocity_x_f4 *= 0.15f;
        phase_state_180 = 0;
        field_732 = 0;
        field_730 = 0;
        velocity_y_f8 *= 0.15f;
        return;

    case 418:
        velocity_x_f4 = 10.5f;
        phase_index_184 = 1;
        phase_state_180 = 0;
        return;

    case 500:
        field_17c = 0;
        zero_motion();
        phase_state_180 = 0;
        field_47e = 0;
        field_730 = 0;
        phase_index_184 = 4;
        return;

    case 501:
        field_17c = 0;
        zero_motion();
        phase_state_180 = 0;
        field_47e = 0;
        field_730 = 0;
        phase_index_184 = 6;
        return;

    case 505:
    case 506:
        field_17c = 4;
        zero_motion();
        phase_index_184 = 0;
        field_47e = 0;
        field_730 = 0;
        phase_state_180 = 1;
        field_750 = 1;
        return;

    case 520:
    case 521:
        field_17c = 1;
        zero_motion();
        phase_state_180 = 0;
        field_47e = 0;
        field_730 = 0;
        phase_index_184 = 1;
        return;

    case 525:
    case 526:
        field_17c = 5;
        zero_motion();
        phase_index_184 = 0;
        phase_state_180 = 0;
        field_47e = 0;
        field_730 = 0;
        return;

    case 540:
    case 541:
        field_17c = 2;
        phase_state_180 = 0;
        zero_motion();
        field_750 = 0;
        return;

    case 545:
    case 546:
        field_17c = 6;
        phase_state_180 = 0;
        zero_motion();
        return;

    case 547:
        phase_state_180 = 0;
        field_750 = 0;
        field_17c = 2;
        phase_index_184 = 1;
        return;

    case 560:
    case 561:
    case 562:
    case 563:
        field_17c = 3;
        phase_state_180 = 0;
        zero_motion();
        field_750 = 1;
        return;

    case 565:
    case 566:
        field_17c = 7;
        phase_state_180 = 0;
        zero_motion();
        field_734 = 0;
        field_732 = 0;
        field_730 = 0;
        field_750 = 1;
        return;

    case 567:
    case 568:
        field_17c = 7;
        field_734 = 0;
        acceleration_y_100 = 0;
        field_750 = 1;
        velocity_x_f4 *= 0.2f;
        phase_state_180 = 0;
        field_732 = 0;
        field_730 = 0;
        velocity_y_f8 *= 0.2f;
        return;

    case 570:
    case 571:
    case 572:
    case 573:
        field_17c = 11;
        phase_state_180 = 0;
        zero_motion();
        field_750 = 1;
        return;

    case 599:
        phase_state_180 = 1;
        zero_motion();
        field_736 = 0;
        field_738 = 0;
        field_732 = 0;
        field_730 = 0;
        return;

    case 600:
    case 602:
    case 606:
    case 650:
    case 710:
    case 720:
        phase_state_180 = 0;
        zero_motion();
        return;

    case 601:
        zero_motion();
        phase_state_180 = 0;
        field_47e = 0;
        field_730 = 0;
        phase_index_184 = 99;
        return;

    case 603:
        phase_state_180 = 1;
        zero_motion();
        return;

    case 605:
        field_730 = 0;
        phase_state_180 = 0;
        phase_index_184 = 6;
        zero_motion();
        field_732 = 0;
        field_734 = 0;
        return;

    case 607:
        zero_motion();
        field_47e = 0;
        field_730 = 0;
        return;

    case 608:
    case 609:
    case 610:
    case 611:
    case 660:
        field_730 = 0;
        field_732 = 0;
        phase_state_180 = 1;
        zero_motion();
        return;

    case 612:
    case 615:
        phase_state_180 = 1;
        zero_motion();
        field_736 = 0;
        field_738 = 0;
        field_732 = 0;
        field_730 = 0;
        field_750 = 1;
        return;

    case 613:
        phase_state_180 = 0;
        field_750 = 1;
        return;

    case 730:
        phase_state_180 = 0;
        zero_motion();
        field_734 = 0;
        return;

    case 740:
        zero_motion();
        field_736 = 0;
        field_738 = 0;
        field_732 = 0;
        field_730 = 0;
        return;

    case 780:
        zero_motion();
        return;

    case 781:
        field_73c = 13.0f;
        field_732 = 0;
        field_740 = 200.0f;
        field_730 = 0;
        return;

    case 797:
    case 798:
        velocity_x_f4 = 10.0f;
        velocity_y_f8 = -5.0f;
        acceleration_y_100 = -0.12f;
        return;

    default:
        initialize_common_action_entry();
        return;
    }
}

} // namespace th105
