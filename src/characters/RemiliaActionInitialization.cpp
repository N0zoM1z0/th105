// JP1.06a554D50: complete action initializer, independently reviewed.
#include "RemiliaActionInitialization.hpp"

namespace th105 {

void RemiliaActionEntryView::initialize_action_entry()
{
    switch (action_id_13c) {
    case 4:
        velocity_x_f4 = 6.5f;
        return;

    case 5:
        velocity_x_f4 = -6.5f;
        return;

    case 214:
        field_736 = 0;
        velocity_x_f4 = 0;
        velocity_y_f8 = 0;
        acceleration_y_100 = 0.6f;
        field_108 = 0;
        field_10c = 75.0f;
        field_73c = 25.0f;
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
        field_47e = 0;
        phase_state_180 = 0;
        velocity_x_f4 = 17.5f;
        phase_index_184 = 1;
        acceleration_y_100 = 0;
        return;

    case 306:
    case 325:
        field_730 = 0;
        phase_state_180 = 0;
        phase_index_184 = 1;
        return;

    case 307:
        zero_motion();
        phase_index_184 = 1;
        phase_state_180 = 0;
        field_750 = 1;
        return;

    case 308:
    case 309:
        phase_index_184 = 1;
        phase_state_180 = 0;
        field_750 = 1;
        return;

    case 310:
        velocity_x_f4 = 0;
        field_730 = 0;
        phase_index_184 = 99;
        phase_state_180 = 0;
        velocity_y_f8 = 0;
        acceleration_y_100 = 0.5f;
        return;

    case 320:
        field_47e = 0;
        phase_state_180 = 0;
        phase_index_184 = 1;
        return;

    case 321:
        if (field_47e == 0) {
            zero_motion();
        }
        phase_state_180 = 0;
        phase_index_184 = 2;
        return;

    case 400:
    case 401:
    case 402:
    case 410:
    case 411:
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
        velocity_x_f4 = 17.5f;
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

    case 412:
        phase_state_180 = 0;
        zero_motion();
        field_730 = 0;
        field_732 = 0;
        field_736 = 0;
        field_738 = 0;
        return;

    case 414:
        acceleration_y_100 = 0;
        phase_state_180 = 0;
        velocity_x_f4 *= 0.2f;
        field_730 = 0;
        field_732 = 0;
        field_736 = 0;
        field_738 = 0;
        field_750 = 1;
        velocity_y_f8 *= 0.2f;
        return;

    case 415:
        phase_state_180 = 0;
        field_730 = 0;
        field_732 = 0;
        field_736 = 0;
        acceleration_y_100 = 0;
        field_750 = 1;
        velocity_x_f4 *= 0.2f;
        velocity_y_f8 *= 0.2f;
        return;

    case 416:
        field_750 = 1;
        phase_state_180 = 0;
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
        field_17c = 0;
        zero_motion();
        phase_index_184 = 1;
        phase_state_180 = 0;
        field_47e = 0;
        return;

    case 505:
    case 506: {
        field_17c = 4;
        zero_motion();
        short sequence = static_cast<unsigned short>(field_730);
        phase_index_184 = 1;
        phase_state_180 = 0;
        field_47e = 0;
        select_sequence(sequence);
        return;
    }

    case 520:
    case 521:
        field_17c = 1;
        field_750 = 1;
        zero_motion();
        phase_state_180 = 1;
        field_47e = 0;
        return;

    case 525:
    case 526:
        field_17c = 5;
        field_750 = 1;
        zero_motion();
        phase_state_180 = 1;
        field_47e = 0;
        return;

    case 530:
    case 531:
        field_17c = 9;
        zero_motion();
        phase_index_184 = 0;
        field_47e = 0;
        phase_state_180 = 1;
        field_750 = 1;
        return;

    case 540:
    case 541:
        field_730 = 0;
        phase_index_184 = 4;
        field_17c = 2;
        phase_state_180 = 0;
        zero_motion();
        field_750 = 1;
        return;

    case 542:
    case 547:
        field_17c = 2;
        phase_index_184 = 1;
        phase_state_180 = 0;
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
        field_750 = 0;
        return;

    case 560:
    case 561:
        field_17c = 3;
        phase_index_184 = 1;
        phase_state_180 = 0;
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
        zero_motion();
        phase_index_184 = 1;
        field_750 = 1;
        return;

    case 567:
        field_17c = 7;
        phase_state_180 = 0;
        field_730 = 0;
        field_732 = 0;
        field_736 = 0;
        acceleration_y_100 = 0;
        field_750 = 1;
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
        field_73c = 240.0f;
        phase_state_180 = 1;
        zero_motion();
        return;

    case 601:
    case 604:
        phase_state_180 = 1;
        zero_motion();
        return;

    case 602:
    case 605:
        field_730 = 0;
        field_732 = 0;
        phase_state_180 = 0;
        phase_index_184 = 20;
        zero_motion();
        return;

    case 603:
        phase_state_180 = 1;
        field_73c = 320.0f;
        zero_motion();
        return;

    case 606:
        field_730 = 0;
        field_732 = 0;
        phase_state_180 = 0;
        phase_index_184 = 1;
        zero_motion();
        return;

    case 607:
    case 710:
    case 711:
        phase_state_180 = 1;
        zero_motion();
        field_73c = 0;
        field_744 = 0;
        return;

    case 608:
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

    case 707:
        zero_motion();
        return;

    case 708:
        velocity_x_f4 = 0;
        field_730 = 0;
        return;

    case 709:
        field_730 = 0;
        return;

    case 720:
    case 721:
        phase_state_180 = 0;
        phase_index_184 = 1;
        zero_motion();
        field_730 = 0;
        return;

    case 730:
    case 731:
    case 740:
        phase_state_180 = 0;
        phase_index_184 = 0;
        zero_motion();
        field_730 = 0;
        field_732 = 0;
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
        velocity_x_f4 = 12.0f;
        field_730 = 0;
        velocity_y_f8 = 0;
        acceleration_y_100 = 0.5f;
        return;

    default:
        initialize_common_action_entry();
        return;
    }
}

} // namespace th105
