// JP1.06a5F6700: complete action initializer, independently reviewed.
#include "KomachiActionInitialization.hpp"

namespace th105 {

void KomachiActionEntryView::initialize_action_entry()
{
    switch (action_id_13c) {
    case 4:
        velocity_x_f4 = 6.0f;
        return;

    case 5:
        velocity_x_f4 = -5.0f;
        return;

    case 214:
        reinterpret_cast<KomachiEntryScratchView *>(reinterpret_cast<unsigned char *>(this) + 4)->reset();
        velocity_x_f4 = 0;
        field_736 = 0;
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
        field_47e = 0;
        phase_state_180 = 0;
        velocity_x_f4 = 17.5f;
        phase_index_184 = 1;
        acceleration_y_100 = 0;
        return;

    case 306:
        field_730 = 0;
        phase_state_180 = 0;
        phase_index_184 = 1;
        return;

    case 307:
    case 308:
    case 309:
        phase_index_184 = 1;
        phase_state_180 = 0;
        field_750 = 1;
        return;

    case 310:
        acceleration_y_100 = 0.5f;
        phase_index_184 = 1;
        phase_state_180 = 0;
        return;

    case 320:
        field_47e = 0;
        phase_state_180 = 0;
        phase_index_184 = 1;
        return;

    case 400:
    case 401:
    case 402:
        phase_state_180 = 1;
        zero_motion();
        field_73c = 0;
        field_740 = 0;
        field_730 = 0;
        field_732 = 0;
        field_744 = 0;
        field_734 = 0;
        field_750 = 1;
        return;

    case 404:
    case 405:
    case 406:
        field_73c = 0;
        field_730 = 0;
        field_740 = 0;
        field_732 = 0;
        field_744 = 0;
        field_734 = 0;
        acceleration_y_100 = 0;
        phase_state_180 = 1;
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

    case 410:
        phase_state_180 = 1;
        zero_motion();
        field_730 = 0;
        field_732 = 0;
        field_736 = 0;
        field_738 = 0;
        field_750 = 1;
        return;

    case 411:
        phase_state_180 = 1;
        zero_motion();
        field_730 = 0;
        field_732 = 0;
        field_736 = 0;
        field_750 = 1;
        return;

    case 412:
        phase_state_180 = 1;
        zero_motion();
        field_732 = 0;
        field_736 = 0;
        field_730 = 0;
        field_738 = 0;
        return;

    case 414:
        acceleration_y_100 = 0;
        field_730 = 0;
        velocity_x_f4 *= 0.2f;
        field_732 = 0;
        field_736 = 0;
        field_738 = 0;
        phase_state_180 = 1;
        field_750 = 1;
        velocity_y_f8 *= 0.2f;
        return;

    case 415:
    case 416:
        acceleration_y_100 = 0;
        field_730 = 0;
        phase_state_180 = 1;
        field_750 = 1;
        velocity_x_f4 *= 0.2f;
        field_732 = 0;
        field_736 = 0;
        velocity_y_f8 *= 0.2f;
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
        phase_index_184 = 0;
        field_47e = 0;
        phase_state_180 = 1;
        return;

    case 505:
    case 506:
        field_17c = 4;
        zero_motion();
        phase_index_184 = 0;
        field_47e = 0;
        phase_state_180 = 1;
        field_750 = 1;
        return;

    case 507:
    case 508:
        velocity_x_f4 *= 0.1f;
        phase_index_184 = 0;
        field_47e = 0;
        field_17c = 4;
        phase_state_180 = 1;
        field_750 = 1;
        velocity_y_f8 *= 0.1f;
        acceleration_y_100 = 0;
        return;

    case 510:
    case 511:
        field_17c = 8;
        zero_motion();
        phase_index_184 = 0;
        field_47e = 0;
        phase_state_180 = 1;
        return;

    case 520:
    case 521:
        field_17c = 1;
        zero_motion();
        phase_state_180 = 1;
        field_47e = 0;
        field_730 = 0;
        field_732 = 0;
        field_734 = 0;
        return;

    case 525:
        field_17c = 5;
        zero_motion();
        phase_index_184 = 8;
        phase_state_180 = 0;
        field_47e = 0;
        field_730 = 0;
        return;

    case 526:
        field_17c = 5;
        zero_motion();
        phase_index_184 = 12;
        phase_state_180 = 0;
        field_47e = 0;
        field_730 = 0;
        return;

    case 540:
    case 541:
    case 542:
    case 543:
        field_17c = 2;
        field_738 = 0;
        phase_state_180 = 1;
        zero_motion();
        field_750 = 0;
        return;

    case 545:
    case 546:
        field_17c = 6;
        phase_state_180 = 1;
        zero_motion();
        field_750 = 1;
        return;

    case 550:
        field_73c = 0;
        phase_index_184 = 1;
        field_17c = 10;
        phase_state_180 = 0;
        zero_motion();
        field_750 = 1;
        return;

    case 551:
        phase_index_184 = 1;
        field_73c = 1;
        field_17c = 10;
        phase_state_180 = 0;
        zero_motion();
        field_750 = 1;
        return;

    case 560:
    case 561:
        field_17c = 3;
        phase_state_180 = 1;
        zero_motion();
        field_730 = 0;
        field_732 = 0;
        field_734 = 0;
        field_736 = 0;
        field_750 = 1;
        return;

    case 565:
    case 566:
        field_17c = 7;
        phase_state_180 = 1;
        zero_motion();
        field_730 = 0;
        field_732 = 0;
        field_734 = 0;
        field_736 = 0;
        field_750 = 1;
        return;

    case 599:
        phase_state_180 = 1;
        zero_motion();
        field_732 = 0;
        field_736 = 0;
        field_730 = 0;
        field_738 = 0;
        return;

    case 600:
        field_730 = 0;
        phase_state_180 = 0;
        phase_index_184 = 1;
        zero_motion();
        return;

    case 601:
        phase_state_180 = 0;
        phase_index_184 = 1;
        zero_motion();
        return;

    case 602:
    case 605:
    case 606:
        zero_motion();
        field_730 = 0;
        field_732 = 0;
        field_734 = 0;
        return;

    case 603:
        field_730 = 0;
        phase_index_184 = 0;
        phase_state_180 = 1;
        zero_motion();
        return;

    case 604:
        phase_state_180 = 0;
        phase_index_184 = 1;
        zero_motion();
        field_730 = 0;
        field_732 = 0;
        return;

    case 611:
        phase_index_184 = 1;
        phase_state_180 = 0;
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

    case 710:
    case 720:
    case 730:
        zero_motion();
        field_730 = 0;
        return;

    case 711:
        zero_motion();
        field_730 = 0;
        field_732 = 0;
        return;

    case 732:
        zero_motion();
        field_730 = 0;
        field_738 = 0;
        return;

    case 797:
        zero_motion();
        dispatch_indexed_event_member(31);
        velocity_x_f4 = 12.0f;
        field_730 = 0;
        velocity_y_f8 = 0;
        acceleration_y_100 = 0.5f;
        return;

    case 798:
        zero_motion();
        dispatch_indexed_event_member(31);
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
