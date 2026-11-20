// JP1.06a58A4F0: complete target-reviewed action initialization.
#include "YukariActionInitialization.hpp"

namespace th105 {

void YukariActionEntryView::initialize_action_entry()
{
    switch (action_id_13c) {
    case 4:
        velocity_x_f4 = 4.5f;
        return;

    case 5:
        velocity_x_f4 = -4.5f;
        return;

    case 70:
        field_730 = 0;
        velocity_x_f4 = -field_18c;
        velocity_y_f8 = field_190;
        acceleration_y_100 = 0.8f;
        if (velocity_x_f4>0.0f) {
            field_730 = 1;
        }
        if (velocity_x_f4 < 0.0f) {
            field_730 = -1;
        }
        field_12c = 0;
        return;

    case 71:
        velocity_x_f4 = -field_18c;
        velocity_y_f8 = field_190;
        acceleration_y_100 = 0.5f;
        field_730 = 7;
        field_12c = 0;
        return;

    case 72:
        velocity_x_f4 = -field_18c;
        velocity_y_f8 = field_190;
        acceleration_y_100 = 1.3f;
        field_12c = 0;
        return;

    case 73:
    case 88:
        velocity_x_f4 = -field_18c;
        velocity_y_f8 = field_190;
        acceleration_y_100 = 0.8f;
        field_730 = 7;
        field_12c = 0;
        return;

    case 74:
    case 75:
        velocity_x_f4 = -field_18c;
        velocity_y_f8 = field_190;
        acceleration_y_100 = 0.8f;
        field_12c = 0;
        return;

    case 76:
        advance_secondary_event_effect_cycle();
        for (int i = 0; i < 5; ++i) {
            emit_effect(201, x_ec, static_cast<float>(y_f0 + 100.0), static_cast<unsigned char>(facing_104), 1);
        }
        ++field_730;
        field_186 = 5;
        field_7a0 = 0;
        field_7a2 = 85;
        emit_effect(38, static_cast<float>(x_ec-facing_104 * 50), static_cast<float>(y_f0 + 100.0), static_cast<unsigned char>(facing_104), 1);
        emit_effect(59, static_cast<float>(x_ec-facing_104 * 50), static_cast<float>(y_f0 + 100.0), static_cast<unsigned char>(facing_104), 1);
        field_108 = field_7a0;
        field_10c = field_7a2;
        velocity_x_f4 = 0;
        velocity_y_f8 = 0;
        acceleration_y_100 = 0;
        publish_layout_scalar(6.0f);
        dispatch_event(22);
        field_12c = 0;
        return;

    case 77:
        field_7a0 = 0;
        velocity_x_f4 = -field_18c;
        field_7a2 = 85;
        velocity_y_f8 = field_190;
        acceleration_y_100 = 0.8f;
        field_108 = 0;
        field_10c = 85.0f;
        field_12c = 0;
        return;

    case 78:
        advance_secondary_event_effect_cycle();
        for (int i = 0; i < 5; ++i) {
            emit_effect(201, x_ec, static_cast<float>(y_f0 + 100.0), static_cast<unsigned char>(facing_104), 1);
        }
        ++field_730;
        velocity_x_f4 = 0;
        velocity_y_f8 = 0;
        acceleration_y_100 = 0;
        publish_layout_scalar(4.0f);
        dispatch_event(22);
        emit_effect(38, static_cast<float>(x_ec-facing_104 * 50), static_cast<float>(y_f0 + 100.0), static_cast<unsigned char>(facing_104), 1);
        emit_effect(59, static_cast<float>(x_ec-facing_104 * 50), static_cast<float>(y_f0 + 100.0), static_cast<unsigned char>(facing_104), 1);
        field_12c = 0;
        return;

    case 89:
        advance_secondary_event_effect_cycle();
        for (int i = 0; i < 5; ++i) {
            emit_effect(201, x_ec, static_cast<float>(y_f0 + 100.0), static_cast<unsigned char>(facing_104), 1);
        }
        if (field_7a4 == 0) {
            field_7a4 = 1;
            spawn_owned_object(999, x_ec, y_f0, static_cast<unsigned char>(facing_104), 1, 0, 0);
        }
        emit_effect(58, x_ec, 0, static_cast<unsigned char>(facing_104), -1);
        field_12c = 0;
        return;

    case 145:
        velocity_x_f4 = -10.0f;
        velocity_y_f8 = 14.0f;
        acceleration_y_100 = 0.5f;
        field_730 = 7;
        field_12c = 0;
        return;

    case 214:
        reinterpret_cast<YukariEntryScratchView *>(reinterpret_cast<unsigned char *>(this) + 4)->reset();
        velocity_x_f4 = 0;
        velocity_y_f8 = 0;
        field_736 = 0;
        acceleration_y_100 = 0.6f;
        field_108 = 0;
        field_10c = 115.0f;
        field_73c = 10.0f;
        field_74c = 0;
        return;

    case 300:
        if (frame_timer_142 == 0 && frame_index_140 == 0) {
            if (field_47e == 0) {
                zero_motion();
            }
            phase_index_184 = 1;
            phase_state_180 = 0;
        }
        if (field_47e != 0) {
            velocity_x_f4 = static_cast<float>(velocity_x_f4 - 0.5);
            if (velocity_x_f4 < 0) {
                velocity_x_f4 = 0;
                field_47e = 0;
            }
        }
        if (advance_frame_and_dispatch()) {
            set_action(0);
        }
        if (frame_timer_142 == 0 && frame_index_140 == 3) {
            dispatch_event(27);
            field_47e = 0;
        }
        return;

    case 301:
    case 303:
    case 320:
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
        velocity_y_f8 = 0;
        acceleration_y_100 = 0;
        phase_index_184 = 1;
        phase_state_180 = 0;
        zero_motion();
        field_47e = 0;
        field_750 = 1;
        return;

    case 305:
        velocity_x_f4 = 10.0f;
        phase_state_180 = 0;
        field_47e = 0;
        field_738 = 0;
        phase_index_184 = 1;
        return;

    case 306:
    case 307:
    case 309:
        field_730 = 0;
        phase_state_180 = 0;
        phase_index_184 = 1;
        return;

    case 308:
        phase_index_184 = 1;
        phase_state_180 = 0;
        zero_motion();
        return;

    case 310:
        velocity_x_f4 = 15.0f;
        field_730 = 0;
        acceleration_y_100 = 0.5f;
        phase_state_180 = 0;
        field_108 = 0;
        phase_index_184 = 3;
        field_10c = 105.0f;
        return;

    case 321:
        field_47e = 0;
        phase_state_180 = 0;
        phase_index_184 = 1;
        return;

    case 322:
        zero_motion();
        phase_index_184 = 1;
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
    case 410:
    case 411:
    case 412:
        phase_state_180 = 0;
        zero_motion();
        field_738 = 0;
        field_736 = 0;
        field_732 = 0;
        field_730 = 0;
        field_750 = 1;
        return;

    case 402:
        phase_state_180 = 0;
        zero_motion();
        field_740 = 0;
        field_730 = 0;
        field_732 = 0;
        field_736 = 0;
        field_738 = 0;
        return;

    case 404:
        acceleration_y_100 = 0;
        velocity_x_f4 *= 0.2f;
        velocity_y_f8 *= 0.2f;
        field_738 = 0;
        field_736 = 0;
        field_734 = 0;
        field_732 = 0;
        field_730 = 0;
        phase_state_180 = 0;
        field_750 = 1;
        return;

    case 406:
        field_740 = 0;
        acceleration_y_100 = 0;
        velocity_x_f4 *= 0.1f;
        velocity_y_f8 *= 0.1f;
        field_738 = 0;
        field_736 = 0;
        field_734 = 0;
        field_732 = 0;
        field_730 = 0;
        phase_state_180 = 0;
        field_750 = 1;
        return;

    case 408:
    case 418:
        velocity_x_f4 = 12.5f;
        velocity_y_f8 = 0;
        acceleration_y_100 = 0;
        field_47e = 0;
        phase_state_180 = 0;
        phase_index_184 = 1;
        return;

    case 414:
    case 415:
    case 416:
        phase_state_180 = 0;
        velocity_x_f4 *= 0.25;
        velocity_y_f8 *= 0.25;
        field_738 = 0;
        field_736 = 0;
        field_732 = 0;
        field_730 = 0;
        field_750 = 1;
        return;

    case 500:
    case 501:
    case 502:
    case 503:
        field_17c = 0;
        phase_state_180 = 1;
        zero_motion();
        field_750 = 1;
        return;

    case 505:
    case 506:
        field_17c = 4;
        phase_state_180 = 1;
        zero_motion();
        field_736 = 0;
        field_732 = 0;
        field_730 = 0;
        field_750 = 1;
        return;

    case 510:
    case 511:
        field_17c = 8;
        phase_state_180 = 1;
        zero_motion();
        field_736 = 0;
        field_732 = 0;
        field_730 = 0;
        field_750 = 1;
        return;

    case 520:
    case 521:
        field_17c = 1;
        field_730 = 0;
        phase_index_184 = 4;
        phase_state_180 = 0;
        zero_motion();
        if (action_id_13c == 520 && field_605 >= 4) {
            field_4a8 = 2;
        }
        return;

    case 522:
    case 523:
        field_17c = 1;
        phase_state_180 = 0;
        velocity_x_f4 *= 0.25;
        velocity_y_f8 *= 0.25;
        return;

    case 525:
    case 526:
        field_17c = 5;
        field_730 = 0;
        phase_index_184 = 0;
        phase_state_180 = 1;
        zero_motion();
        field_750 = 1;
        return;

    case 540:
    case 541:
    case 542:
    case 543:
        field_17c = 2;
        zero_motion();
        phase_state_180 = 1;
        field_47e = 0;
        return;

    case 545:
    case 546:
        field_17c = 6;
        zero_motion();
        phase_index_184 = 1;
        phase_state_180 = 1;
        field_47e = 0;
        return;

    case 547:
    case 548:
        field_17c = 6;
        zero_motion();
        phase_state_180 = 1;
        field_47e = 0;
        return;

    case 560:
    case 561:
        field_17c = 3;
        zero_motion();
        field_740 = 0;
        phase_index_184 = 0;
        phase_state_180 = 0;
        field_730 = 0;
        return;

    case 562:
    case 563:
        field_17c = 3;
        zero_motion();
        field_740 = 0;
        phase_index_184 = 0;
        phase_state_180 = 0;
        field_730 = 0;
        return;

    case 565:
        field_17c = 7;
        zero_motion();
        field_47e = 0;
        phase_index_184 = 1;
        phase_state_180 = 0;
        field_730 = 0;
        field_750 = 1;
        return;

    case 566:
        field_17c = 7;
        zero_motion();
        field_47e = 0;
        phase_index_184 = 10;
        phase_state_180 = 0;
        field_730 = 0;
        field_750 = 1;
        return;

    case 600:
    case 601:
    case 602:
    case 603:
        phase_state_180 = 1;
        zero_motion();
        return;

    case 604:
    case 605:
        field_730 = 0;
        field_732 = 0;
        phase_state_180 = 1;
        zero_motion();
        return;

    case 606:
    case 656:
        field_73c = 0;
        field_730 = 0;
        field_738 = 0;
        phase_state_180 = 0;
        zero_motion();
        return;

    case 607:
    case 740:
    case 741:
    case 750:
        phase_state_180 = 0;
        zero_motion();
        field_730 = 0;
        field_732 = 0;
        field_734 = 0;
        field_736 = 0;
        return;

    case 615:
        zero_motion();
        phase_state_180 = 0;
        return;

    case 700:
    case 701:
        field_730 = 0;
        field_732 = 0;
        phase_state_180 = 1;
        zero_motion();
        acceleration_y_100 = 0.25f;
        return;

    case 708:
        field_730 = 0;
        field_732 = 0;
        field_734 = 0;
        phase_state_180 = 1;
        zero_motion();
        return;

    case 710:
        field_730 = 0;
        field_732 = 0;
        field_734 = 0;
        zero_motion();
        return;

    case 720:
        zero_motion();
        field_730 = 0;
        field_738 = 0;
        phase_state_180 = 0;
        phase_index_184 = 1;
        return;

    case 721:
        zero_motion();
        field_730 = 0;
        field_47e = 0;
        phase_state_180 = 0;
        phase_index_184 = 10;
        return;

    case 730:
        field_730 = 0;
        field_738 = 0;
        phase_state_180 = 0;
        return;

    case 797: {
        float payload[3];
        zero_motion();
        payload[0] = 0;
        payload[1] = 0;
        payload[2] = 0;
        field_730 = 0;
        spawn_owned_object(899, 360.0f, 100.0f, static_cast<unsigned char>(facing_104), -1, payload, 3);
        dispatch_character_wave_handle(1);
        return;
    }

    case 798: {
        float payload[3];
        zero_motion();
        payload[0] = 0;
        payload[1] = 0;
        payload[2] = 0;
        field_730 = 0;
        spawn_owned_object(899, 920.0f, 100.0f, static_cast<unsigned char>(facing_104), -1, payload, 3);
        dispatch_character_wave_handle(1);
        return;
    }

    default:
        initialize_common_action_entry();
        return;
    }
}

} // namespace th105
