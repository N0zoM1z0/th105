// JP1.06a51D650: complete target-reviewed action initialization.
#include "PatchouliActionInitialization.hpp"
#include "battle/SpellRuntime.hpp"
#include <deque>

namespace th105 {

void PatchouliActionEntryView::initialize_action_entry()
{
    switch (action_id_13c) {
    case 4:
        velocity_x_f4 = 4.0f;
        return;

    case 5:
        velocity_x_f4 = -4.0f;
        return;

    case 197:
        velocity_x_f4 = 11.0f;
        return;

    case 198:
        velocity_x_f4 = -11.0f;
        return;

    case 214:
        reinterpret_cast<PatchouliEntryScratchView *>(reinterpret_cast<unsigned char *>(this) + 4)->reset();
        velocity_x_f4 = 0;
        field_736 = 0;
        velocity_y_f8 = 0;
        acceleration_y_100 = 0.6f;
        field_73c = 9.0f;
        field_74c = 0;
        return;

    case 300:
    case 301:
        if (field_47e == 0) {
            zero_motion();
        }
        phase_state_180 = 0;
        phase_index_184 = 1;
        field_750 = 1;
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

    case 303:
    case 321:
    case 322:
        if (field_47e == 0) {
            zero_motion();
        }
        phase_state_180 = 0;
        phase_index_184 = 1;
        return;

    case 304:
        field_47e = 0;
        phase_index_184 = 1;
        phase_state_180 = 0;
        zero_motion();
        field_750 = 1;
        return;

    case 305:
        field_47e = 0;
        velocity_x_f4 = 10.0f;
        phase_state_180 = 0;
        phase_index_184 = 1;
        return;

    case 306:
        field_730 = 0;
        phase_state_180 = 0;
        phase_index_184 = 3;
        return;

    case 307:
        phase_index_184 = 1;
        phase_state_180 = 0;
        velocity_x_f4 *= 0.2f;
        velocity_y_f8 *= 0.2f;
        field_750 = 1;
        acceleration_y_100 = 0;
        return;

    case 308:
        phase_index_184 = 1;
        phase_state_180 = 0;
        field_750 = 1;
        return;

    case 309:
        phase_index_184 = 0;
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
        field_730 = 0;
        zero_motion();
        field_47e = 0;
        phase_state_180 = 0;
        phase_index_184 = 3;
        return;

    case 400:
    case 401:
    case 402:
    case 407:
        phase_state_180 = 0;
        zero_motion();
        field_730 = 0;
        field_732 = 0;
        field_736 = 0;
        field_750 = 1;
        return;

    case 404:
    case 406:
    case 409:
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
        velocity_y_f8 = 0;
        field_730 = 0;
        field_47e = 0;
        velocity_x_f4 = 10.0f;
        phase_state_180 = 0;
        phase_index_184 = 3;
        acceleration_y_100 = 0;
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

    case 411:
        phase_state_180 = 0;
        zero_motion();
        field_730 = 0;
        field_732 = 0;
        field_750 = 1;
        return;

    case 412:
        phase_state_180 = 1;
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
        velocity_x_f4 = 8.5f;
        if (field_47e == 0) {
            zero_motion();
        }
        phase_state_180 = 0;
        phase_index_184 = 1;
        return;

    case 500:
    case 501:
    case 502:
    case 503:
        field_750 = 1;
        field_17c = 0;
        zero_motion();
        field_47e = 0;
        phase_state_180 = 1;
        return;

    case 505:
    case 506:
        field_17c = 5;
        field_750 = 1;
        zero_motion();
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
        phase_state_180 = 1;
        return;

    case 525:
    case 526:
        field_17c = 6;
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
        phase_state_180 = 0;
        field_750 = 0;
        field_17c = 2;
        phase_index_184 = 1;
        return;

    case 545:
    case 546:
        field_17c = 6;
        phase_state_180 = 0;
        zero_motion();
        field_750 = 1;
        return;

    case 560:
    case 561:
        field_17c = 3;
        phase_state_180 = 0;
        zero_motion();
        field_730 = 0;
        field_744 = 0;
        field_732 = 0;
        field_750 = 1;
        return;

    case 565:
    case 566:
        field_17c = 8;
        phase_state_180 = 0;
        zero_motion();
        field_750 = 1;
        return;

    case 567:
    case 568:
        field_17c = 8;
        phase_state_180 = 0;
        field_750 = 1;
        acceleration_y_100 = 0;
        velocity_x_f4 *= 0.2f;
        velocity_y_f8 *= 0.2f;
        return;

    case 580:
    case 581:
        field_17c = 4;
        phase_state_180 = 1;
        zero_motion();
        field_730 = 0;
        field_744 = 0;
        field_732 = 0;
        field_750 = 1;
        return;

    case 585:
    case 586:
        field_17c = 10;
        phase_state_180 = 0;
        zero_motion();
        field_750 = 1;
        return;

    case 600:
    case 604:
        phase_state_180 = 0;
        zero_motion();
        return;

    case 601:
    case 651:
        field_730 = 0;
        field_73c = 10.0f;
        field_732 = 0;
        phase_state_180 = 0;
        zero_motion();
        return;

    case 602:
        field_730 = 0;
        phase_state_180 = 0;
        phase_index_184 = 99;
        zero_motion();
        return;

    case 603:
        field_730 = 0;
        field_732 = 0;
        phase_state_180 = 0;
        zero_motion();
        return;

    case 605:
    case 606:
        zero_motion();
        phase_state_180 = 0;
        field_47e = 0;
        return;

    case 607:
        zero_motion();
        field_47e = 0;
        return;

    case 610:
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

    case 690: {
        emit_effect(71, x_ec, static_cast<float>(y_f0 + 100.0), static_cast<unsigned char>(facing_104), 1);
        field_730 = 0;
        field_732 = 0;
        field_738 = (*reinterpret_cast<std::deque<FighterSequenceSlot> *>(reinterpret_cast<unsigned char *>(this) + 0x55c))[0].record_id_00;
        phase_state_180 = 1;
        zero_motion();
        const int card = field_738;
        switch (card) {
        case 100:
            if (++field_624 == 0) {
                field_624 = 1;
            }
            if (field_624 >= 5) {
                field_624 = 4;
            }
            field_629 = -1;
            field_62e = -1;
            break;

        case 101:
            if (++field_625 == 0) {
                field_625 = 1;
            }
            if (field_625 >= 5) {
                field_625 = 4;
            }
            field_62a = -1;
            field_62f = -1;
            break;

        case 102:
            if (++field_626 == 0) {
                field_626 = 1;
            }
            if (field_626 >= 5) {
                field_626 = 4;
            }
            field_62b = -1;
            field_630 = -1;
            break;

        case 103:
            if (++field_627 == 0) {
                field_627 = 1;
            }
            if (field_627 >= 5) {
                field_627 = 4;
            }
            field_62c = -1;
            field_631 = -1;
            break;

        case 104:
            if (++field_628 == 0) {
                field_628 = 1;
            }
            if (field_628 >= 5) {
                field_628 = 4;
            }
            field_632 = -1;
            field_62d = -1;
            break;

        case 105:
            if (++field_629 == 0) {
                field_629 = 1;
            }
            if (field_629 >= 5) {
                field_629 = 4;
            }
            field_624 = -1;
            field_62e = -1;
            break;

        case 106:
            if (++field_62a == 0) {
                field_62a = 1;
            }
            if (field_62a >= 5) {
                field_62a = 4;
            }
            field_625 = -1;
            field_62f = -1;
            break;

        case 107:
            if (++field_62b == 0) {
                field_62b = 1;
            }
            if (field_62b >= 5) {
                field_62b = 4;
            }
            field_626 = -1;
            field_630 = -1;
            break;

        case 108:
            if (++field_62c == 0) {
                field_62c = 1;
            }
            if (field_62c >= 5) {
                field_62c = 4;
            }
            field_627 = -1;
            field_631 = -1;
            break;

        case 109:
            if (++field_62d == 0) {
                field_62d = 1;
            }
            if (field_62d >= 5) {
                field_62d = 4;
            }
            field_628 = -1;
            field_632 = -1;
            break;

        case 110:
            if (++field_62e == 0) {
                field_62e = 1;
            }
            if (field_62e >= 5) {
                field_62e = 4;
            }
            field_624 = -1;
            field_629 = -1;
            break;

        case 111:
            if (++field_62f == 0) {
                field_62f = 1;
            }
            if (field_62f >= 5) {
                field_62f = 4;
            }
            field_625 = -1;
            field_62a = -1;
            break;

        case 112:
            if (++field_630 == 0) {
                field_630 = 1;
            }
            if (field_630 >= 5) {
                field_630 = 4;
            }
            field_626 = -1;
            field_62b = -1;
            break;

        case 113:
            if (++field_631 == 0) {
                field_631 = 1;
            }
            if (field_631 >= 5) {
                field_631 = 4;
            }
            field_627 = -1;
            field_62c = -1;
            break;

        case 114:
            if (++field_632 == 0) {
                field_632 = 1;
            }
            if (field_632 >= 5) {
                field_632 = 4;
            }
            field_628 = -1;
            field_62d = -1;
            break;
        }
        emit_effect(static_cast<short>(reinterpret_cast<signed char *>(this)[0x5c0 + card] + 130), x_ec, y_f0, 1, 1);
        dispatch_sequence_window(0, 1, 60);
        return;
    }

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
        zero_motion();
        field_740 = 0;
        return;

    case 720: {
        const double y = y_f0;
        if (stage_surface_height_at_x(this) >= y) {
            zero_motion();
        }
        return;
    }

    case 721: {
        const double y = y_f0;
        if (stage_surface_height_at_x(this) >= y) {
            zero_motion();
        }
        return;
    }

    case 730:
        zero_motion();
        field_655 = 1;
        finalize_sequence_entry(-1);
        publish_texture_state(2, -1);
        copy_action_word_176_to_174();
        field_76c = 0;
        field_76a = 1;
        field_766 = 0;
        field_768 = 0;
        field_764 = 0;
        dispatch_event(23);
        return;

    case 797:
        zero_motion();
        acceleration_y_100 = 0.4f;
        field_730 = 0;
        return;

    case 798:
        zero_motion();
        acceleration_y_100 = 0.4f;
        field_730 = 0;
        return;

    default:
        initialize_common_action_entry();
        return;
    }
}

} // namespace th105
