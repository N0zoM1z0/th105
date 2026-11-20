// JP1.06a617000: complete action initializer, independently reviewed.
#include "AyaActionInitialization.hpp"

namespace th105 {

void AyaActionEntryView::initialize_action_entry()
{
    switch (action_id_13c) {
    case 4:
        velocity_x_f4 = 5.5f;
        return;

    case 5:
        velocity_x_f4 = -5.5f;
        return;

    case 214:
        reinterpret_cast<AyaEntryScratchView *>(reinterpret_cast<unsigned char *>(this) + 4)->reset();
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
    case 320:
    case 321:
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
        velocity_x_f4 = 0;
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
        velocity_x_f4 = 17.5f;
        acceleration_y_100 = 0;
        phase_index_184 = 1;
        field_47e = 0;
        phase_state_180 = 0;
        return;

    case 306:
        field_730 = 0;
        phase_state_180 = 0;
        phase_index_184 = 1;
        return;

    case 307:
        velocity_x_f4 = 0;
        field_730 = 0;
        velocity_y_f8 = 0;
        phase_state_180 = 0;
        acceleration_y_100 = 0;
        phase_index_184 = 1;
        field_73c = 25.0f;
        return;

    case 308:
        phase_index_184 = 1;
        velocity_x_f4 = 0;
        phase_state_180 = 0;
        velocity_y_f8 = 0;
        return;

    case 309:
        phase_index_184 = 1;
        phase_state_180 = 0;
        return;

    case 310:
        velocity_x_f4 = 0;
        field_730 = 0;
        velocity_y_f8 = 0;
        phase_state_180 = 0;
        phase_index_184 = 99;
        acceleration_y_100 = 0.5f;
        return;

    case 322:
        if (field_47e == 0) {
            zero_motion();
        }
        phase_state_180 = 0;
        field_47e = 0;
        velocity_x_f4 = 0;
        phase_index_184 = 1;
        return;

    case 400:
    case 401:
    case 410:
    case 412:
        phase_state_180 = 0;
        zero_motion();
        field_730 = 0;
        field_732 = 0;
        field_736 = 0;
        field_750 = 1;
        return;

    case 402:
        phase_state_180 = 0;
        zero_motion();
        field_732 = 0;
        field_736 = 0;
        field_730 = 0;
        field_738 = 0;
        return;

    case 404:
    case 406:
        phase_state_180 = 0;
        velocity_x_f4 *= 0.25;
        velocity_y_f8 *= 0.25;
        acceleration_y_100 = 0.5f;
        field_730 = 0;
        field_732 = 0;
        field_736 = 0;
        field_750 = 1;
        return;

    case 408: {
        if (field_144 == 0 && frame_timer_142 == 0 && frame_index_140 == 0 && field_13e == 0) {
            velocity_x_f4 = 17.5f;
            field_47e = 0;
            field_730 = 0;
            phase_index_184 = 1;
            velocity_y_f8 = 0;
            phase_state_180 = 0;
        }
        float speed = static_cast<float>(velocity_x_f4 - 0.5);
        velocity_x_f4 = speed;
        if (speed < 0) {
            velocity_x_f4 = 0;
        }
        if (advance_frame_and_dispatch()) {
            set_action_and_finalize(0);
        }
        if (frame_timer_142 == 0 && frame_index_140 == 6) {
            dispatch_character_wave_handle(27);
        }
        return;
    }

    case 409:
        field_47e = 0;
        acceleration_y_100 = 0.35f;
        field_730 = 0;
        phase_state_180 = 0;
        phase_index_184 = 1;
        return;

    case 411:
        phase_state_180 = 0;
        zero_motion();
        field_730 = 0;
        field_732 = 0;
        field_736 = 0;
        field_750 = 0;
        return;

    case 414:
    case 416:
        acceleration_y_100 = 0.5f;
        phase_state_180 = 0;
        velocity_x_f4 *= 0.25;
        velocity_y_f8 *= 0.25;
        field_730 = 0;
        field_732 = 0;
        field_736 = 0;
        field_750 = 1;
        return;

    case 415:
        acceleration_y_100 = 0.5f;
        phase_state_180 = 0;
        velocity_x_f4 *= 0.25;
        velocity_y_f8 *= 0.25;
        field_730 = 0;
        field_732 = 0;
        field_736 = 0;
        field_750 = 0;
        return;

    case 418:
        velocity_y_f8 = 0;
        acceleration_y_100 = 0;
        field_73c = 25.0f;
        phase_index_184 = 1;
        field_47e = 0;
        phase_state_180 = 0;
        return;

    case 500:
        field_17c = 0;
        phase_state_180 = 0;
        zero_motion();
        field_732 = 0;
        field_736 = 0;
        field_730 = 0;
        field_738 = 0;
        return;

    case 502:
        field_17c = 0;
        phase_state_180 = 0;
        zero_motion();
        field_732 = 0;
        field_736 = 0;
        field_730 = 0;
        field_738 = 0;
        return;

    case 505:
    case 506:
        field_17c = 4;
        phase_state_180 = 0;
        zero_motion();
        field_732 = 0;
        field_736 = 0;
        field_730 = 0;
        field_738 = 0;
        return;

    case 507:
    case 508:
        field_17c = 4;
        phase_state_180 = 0;
        velocity_x_f4 *= 0.25;
        velocity_y_f8 *= 0.25;
        field_732 = 0;
        field_736 = 0;
        field_730 = 0;
        field_738 = 0;
        return;

    case 510:
        field_17c = 8;
        phase_state_180 = 0;
        zero_motion();
        field_732 = 0;
        field_736 = 0;
        field_730 = 0;
        field_738 = 0;
        return;

    case 520:
    case 521:
    case 522:
    case 523:
        field_17c = 1;
        zero_motion();
        phase_state_180 = 0;
        field_47e = 0;
        field_730 = 0;
        phase_index_184 = 1;
        return;

    case 525:
    case 526:
    case 527:
    case 528:
        field_17c = 255;
        zero_motion();
        phase_state_180 = 0;
        field_47e = 0;
        field_730 = 0;
        field_738 = 0;
        phase_index_184 = 1;
        return;

    case 529:
        field_17c = 255;
        zero_motion();
        phase_state_180 = 0;
        field_47e = 0;
        phase_index_184 = 1;
        return;

    case 530:
    case 531:
    case 532:
    case 533:
        field_17c = 9;
        zero_motion();
        phase_state_180 = 1;
        field_47e = 0;
        return;

    case 540:
        field_17c = 2;
        phase_state_180 = 0;
        zero_motion();
        acceleration_y_100 = 0;
        field_730 = 0;
        velocity_x_f4 *= 0.25;
        field_732 = 0;
        field_736 = 0;
        field_738 = 0;
        velocity_y_f8 *= 0.25;
        return;

    case 545:
        field_17c = 6;
        phase_index_184 = 1;
        velocity_x_f4 = 0;
        phase_state_180 = 0;
        velocity_y_f8 = 0;
        return;

    case 546:
        velocity_x_f4 = 0;
        phase_index_184 = 0;
        phase_state_180 = 0;
        velocity_y_f8 = 0;
        field_17c = 6;
        return;

    case 550:
    case 551:
    case 552:
    case 553:
        field_17c = 10;
        field_730 = 0;
        phase_index_184 = 1;
        phase_state_180 = 0;
        zero_motion();
        return;

    case 554:
        field_17c = 10;
        phase_index_184 = 1;
        phase_state_180 = 0;
        return;

    case 560:
    case 561:
        field_17c = 3;
        field_730 = 0;
        field_732 = 0;
        zero_motion();
        phase_state_180 = 0;
        return;

    case 565:
    case 567:
        field_17c = 7;
        field_730 = 0;
        field_732 = 0;
        zero_motion();
        phase_state_180 = 0;
        return;

    case 600:
    case 601:
    case 602:
    case 604:
    case 605:
    case 611:
    case 661:
        field_730 = 0;
        field_732 = 0;
        phase_state_180 = 1;
        zero_motion();
        return;

    case 603:
        phase_state_180 = 0;
        zero_motion();
        acceleration_y_100 = 0;
        field_730 = 0;
        velocity_x_f4 *= 0.25;
        field_732 = 0;
        field_736 = 0;
        field_738 = 0;
        velocity_y_f8 *= 0.25;
        return;

    case 606:
        field_730 = 0;
        field_73c = 0;
        field_732 = 0;
        field_734 = 0;
        field_736 = 0;
        field_738 = 0;
        phase_state_180 = 0;
        phase_index_184 = 1;
        zero_motion();
        return;

    case 612:
    case 662:
        zero_motion();
        phase_state_180 = 0;
        field_47e = 0;
        field_730 = 0;
        phase_index_184 = 1;
        return;

    case 710:
    case 720:
    case 721:
    case 730:
        field_730 = 0;
        field_732 = 0;
        field_734 = 0;
        zero_motion();
        return;

    case 740:
        field_73c = 0;
        field_730 = 0;
        field_740 = 0;
        field_732 = 0;
        field_744 = 0;
        field_734 = 0;
        field_748 = 0;
        field_736 = 0;
        field_738 = 0;
        field_74c = 0;
        zero_motion();
        return;

    case 791:
        zero_motion();
        return;

    case 797:
        zero_motion();
        velocity_x_f4 = 6.0f;
        velocity_y_f8 = -30.0f;
        field_730 = 0;
        dispatch_character_wave_handle(14);
        return;

    case 798:
        zero_motion();
        velocity_x_f4 = 6.0f;
        velocity_y_f8 = -30.0f;
        field_730 = 0;
        dispatch_character_wave_handle(14);
        return;

    default:
        initialize_common_action_entry();
        return;
    }
}

} // namespace th105
