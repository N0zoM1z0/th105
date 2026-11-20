// JP1.06a4B89C0: complete target-reviewed action initializer.
#include "MarisaActionInitialization.hpp"

namespace th105 {

void MarisaActionEntryView::initialize_action_entry()
{
    switch (action_id_13c) {
    case 4:
        velocity_x_f4 = 6.0f;
        return;

    case 5:
        velocity_x_f4 = -5.0f;
        return;

    case 214:
        reinterpret_cast<MarisaEntryScratchView *>(reinterpret_cast<unsigned char *>(this) + 4)->reset();
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
        phase_index_184 = 1;
        phase_state_180 = 0;
        field_750 = 1;
        return;

    case 309:
        phase_index_184 = 1;
        phase_state_180 = 0;
        field_750 = 1;
        zero_motion();
        return;

    case 310:
        field_730 = 0;
        acceleration_y_100 = 0.5f;
        phase_state_180 = 0;
        phase_index_184 = 1;
        return;

    case 320:
        field_47e = 0;
        phase_state_180 = 0;
        phase_index_184 = 1;
        return;

    case 400:
    case 401:
    case 402:
    case 411:
        phase_state_180 = 0;
        zero_motion();
        field_736 = 0;
        field_732 = 0;
        field_730 = 0;
        field_750 = 1;
        return;

    case 404:
    case 406:
    case 415:
        phase_state_180 = 0;
        field_730 = 0;
        field_732 = 0;
        field_736 = 0;
        field_750 = 1;
        acceleration_y_100 = 0;
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
        phase_state_180 = 0;
        zero_motion();
        field_730 = 0;
        field_732 = 0;
        field_736 = 0;
        field_738 = 0;
        field_750 = 1;
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

    case 416:
        phase_state_180 = 0;
        field_738 = 0;
        phase_index_184 = 1;
        return;

    case 418:
        velocity_x_f4 = 17.5f;
        if (field_47e == 0) {
            zero_motion();
        }
        phase_state_180 = 0;
        phase_index_184 = 1;
        return;

    case 420:
    case 421:
        phase_state_180 = 0;
        zero_motion();
        field_730 = 0;
        field_732 = 0;
        field_736 = 0;
        field_7a8 = 0;
        field_7a4 = 0;
        return;

    case 422:
        acceleration_y_100 = 0;
        phase_state_180 = 0;
        velocity_x_f4 *= 0.2f;
        field_730 = 0;
        field_732 = 0;
        field_736 = 0;
        field_7a8 = 0;
        field_7a4 = 0;
        velocity_y_f8 *= 0.2f;
        return;

    case 430:
    case 431:
        phase_state_180 = 0;
        zero_motion();
        field_730 = 0;
        field_732 = 0;
        field_736 = 0;
        field_738 = 0;
        field_7a8 = 0;
        field_7a4 = 0;
        return;

    case 432:
        acceleration_y_100 = 0;
        phase_state_180 = 0;
        velocity_x_f4 *= 0.2f;
        field_730 = 0;
        field_732 = 0;
        field_736 = 0;
        field_738 = 0;
        field_7a8 = 0;
        field_7a4 = 0;
        velocity_y_f8 *= 0.2f;
        return;

    case 500:
        field_17c = 0;
        zero_motion();
        phase_state_180 = 0;
        acceleration_y_100 = 0.55f;
        field_47e = 0;
        field_730 = 0;
        phase_index_184 = 1;
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
        field_47e = 0;
        field_730 = 0;
        phase_index_184 = 1;
        phase_state_180 = 1;
        return;

    case 510:
    case 512:
        field_17c = 8;
        zero_motion();
        field_73c = 0;
        phase_index_184 = 0;
        phase_state_180 = 0;
        field_47e = 0;
        return;

    case 520:
    case 521:
        field_17c = 1;
        zero_motion();
        phase_index_184 = 99;
        phase_state_180 = 0;
        field_47e = 0;
        field_730 = 0;
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

    case 530:
    case 531:
        field_17c = 9;
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
        field_730 = 0;
        field_732 = 0;
        field_736 = 0;
        field_738 = 0;
        field_750 = 0;
        return;

    case 542:
        field_17c = 2;
        phase_index_184 = 1;
        phase_state_180 = 0;
        field_750 = 0;
        return;

    case 545:
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
        field_17c = 6;
        phase_index_184 = 1;
        phase_state_180 = 0;
        field_750 = 0;
        return;

    case 550:
    case 551:
        field_17c = 10;
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
        phase_state_180 = 0;
        zero_motion();
        field_736 = 0;
        field_732 = 0;
        field_730 = 0;
        field_750 = 1;
        return;

    case 562:
    case 563:
        field_17c = 3;
        phase_state_180 = 0;
        field_730 = 0;
        field_732 = 0;
        field_736 = 0;
        field_750 = 1;
        acceleration_y_100 = 0;
        velocity_x_f4 *= 0.2f;
        velocity_y_f8 *= 0.2f;
        return;

    case 565:
    case 566:
        field_17c = 7;
        phase_state_180 = 0;
        zero_motion();
        field_736 = 0;
        field_732 = 0;
        field_730 = 0;
        field_750 = 1;
        return;

    case 567:
    case 568:
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

    case 570:
    case 571:
        field_17c = 11;
        phase_state_180 = 0;
        zero_motion();
        field_736 = 0;
        field_732 = 0;
        field_730 = 0;
        field_750 = 1;
        return;

    case 572:
    case 573:
        field_17c = 11;
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
    case 601:
    case 602:
    case 608:
    case 610:
    case 611:
    case 658:
        field_730 = 0;
        field_732 = 0;
        phase_state_180 = 1;
        zero_motion();
        return;

    case 603: {
        float payload[3];
        field_730 = 0;
        field_732 = 0;
        phase_state_180 = 1;
        zero_motion();
        if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending()) == 0) {
            payload[0] = 0;
            payload[1] = 0;
            payload[2] = 10.0f;
            spawn_owned_object(853, x_ec, y_f0, facing_104, -1, payload, 3);
        }
        return;
    }

    case 605:
        field_730 = 0;
        phase_state_180 = 0;
        phase_index_184 = 6;
        zero_motion();
        field_732 = 0;
        field_734 = 0;
        return;

    case 606:
        zero_motion();
        phase_index_184 = 99;
        phase_state_180 = 0;
        field_47e = 0;
        field_730 = 0;
        return;

    case 607:
        zero_motion();
        field_47e = 0;
        field_730 = 0;
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

    case 619:
    case 730:
    case 732:
        field_730 = 0;
        field_732 = 0;
        zero_motion();
        return;

    case 707:
    case 720:
    case 722:
        zero_motion();
        return;

    case 708:
        zero_motion();
        field_730 = 0;
        return;

    case 710:
    case 711:
        zero_motion();
        face_opponent_and_flip_horizontal_velocity();
        return;

    case 721:
        zero_motion();
        field_732 = 0;
        field_738 = 0;
        field_736 = 0;
        return;

    case 731:
    case 733:
        field_730 = 0;
        field_73c = 0;
        field_732 = 0;
        zero_motion();
        return;

    case 797:
        field_730 = 0;
        dispatch_character_wave_handle(5);
        return;

    case 798:
        dispatch_character_wave_handle(5);
        zero_motion();
        velocity_x_f4 = 15.0f;
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
