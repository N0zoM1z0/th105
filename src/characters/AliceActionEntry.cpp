#include <stddef.h>

namespace th105 {

class FighterActionScratchView {
public:
    void reset_fighter_action_scratch();
};

class AliceActionEntryView {
public:
    virtual void slot_00();

    void zero_velocity_acceleration();
    void dispatch_indexed_event_member(unsigned index);
    void initialize_common_action_state();
    void initialize_action_entry();

    unsigned char unknown_004[0xe8];
    float x_ec;
    float y_f0;
    float velocity_x_f4;
    float velocity_y_f8;
    float acceleration_x_fc;
    float acceleration_y_100;
    signed char facing_104;
    unsigned char unknown_105[0x37];
    short action_13c;
    unsigned char unknown_13e[0x42];
    int state_180;
    signed char state_184;
    unsigned char unknown_185[0x2f9];
    signed char gate_47e;
    unsigned char unknown_47f[0x2b1];
    short state_730;
    short state_732;
    short state_734;
    short state_736;
    short state_738;
    unsigned char unknown_73a[2];
    float state_73c;
    unsigned char unknown_740[0x0c];
    float state_74c;
    signed char state_750;
    unsigned char unknown_751[0x7f];
    signed char state_7d0;

    FighterActionScratchView *action_scratch()
    {
        return reinterpret_cast<FighterActionScratchView *>(
            reinterpret_cast<unsigned char *>(this) + 4);
    }
};

typedef char AliceActionEntry_action_offset[
    offsetof(AliceActionEntryView, action_13c) == 0x13c ? 1 : -1];
typedef char AliceActionEntry_state180_offset[
    offsetof(AliceActionEntryView, state_180) == 0x180 ? 1 : -1];
typedef char AliceActionEntry_gate_offset[
    offsetof(AliceActionEntryView, gate_47e) == 0x47e ? 1 : -1];
typedef char AliceActionEntry_state730_offset[
    offsetof(AliceActionEntryView, state_730) == 0x730 ? 1 : -1];
typedef char AliceActionEntry_state7d0_offset[
    offsetof(AliceActionEntryView, state_7d0) == 0x7d0 ? 1 : -1];

void AliceActionEntryView::initialize_action_entry()
{
    int action = static_cast<short>(action_13c);

    if (action <= 500) {
        if (action != 500) {
            switch (action_13c) {
            case 4:
                velocity_x_f4 = 6.0f;
                return;

            case 5:
                velocity_x_f4 = -6.0f;
                return;

            case 197:
                zero_velocity_acceleration();
                velocity_x_f4 = 15.0f;
                return;

            case 198:
            zero_velocity_acceleration();
            velocity_x_f4 = -15.0f;
            return;

            case 214:
            action_scratch()->reset_fighter_action_scratch();
            velocity_x_f4 = 0.0f;
            state_736 = 0;
            velocity_y_f8 = 0.0f;
            acceleration_y_100 = 0.6000000238418579f;
            *reinterpret_cast<float *>(reinterpret_cast<unsigned char *>(this) + 0x108) = 0.0f;
            *reinterpret_cast<float *>(reinterpret_cast<unsigned char *>(this) + 0x10c) = 95.0f;
            state_73c = 12.0f;
            state_74c = 0.0f;
            return;

            case 300:
            case 303:
            case 321:
            if (!gate_47e)
            zero_velocity_acceleration();
            state_180 = 0;
            state_184 = 1;
            return;

            case 301:
            case 302:
            if (!gate_47e)
            zero_velocity_acceleration();
            state_180 = 0;
            return;

            case 304:
            gate_47e = 0;
            state_184 = 0;
            state_180 = 0;
            zero_velocity_acceleration();
            state_730 = 0;
            state_732 = 0;
            return;

            case 305:
            velocity_y_f8 = 0.0f;
            velocity_x_f4 = 15.0f;
            acceleration_y_100 = 0.0f;
            // fall through
            case 320:
            gate_47e = 0;
            state_180 = 0;
            state_184 = 1;
            return;

            case 306:
            state_730 = 0;
            state_180 = 0;
            state_184 = 1;
            return;

            case 307:
            state_180 = 0;
            velocity_x_f4 = static_cast<float>(velocity_x_f4 * 0.25f);
            velocity_y_f8 = static_cast<float>(0.25f * velocity_y_f8);
            return;

            case 308:
            state_180 = 0;
            state_730 = 0;
            state_732 = 0;
            state_184 = 4;
            return;

            case 309:
            state_180 = 0;
            state_730 = 0;
            state_732 = 0;
            state_184 = 4;
            velocity_x_f4 = static_cast<float>(velocity_x_f4 * 0.2f);
            velocity_y_f8 = static_cast<float>(0.2f * velocity_y_f8);
            acceleration_y_100 = 0.0f;
            return;

            case 310:
            velocity_x_f4 = 0.0f;
            state_730 = 0;
            velocity_y_f8 = 0.0f;
            state_180 = 0;
            state_184 = 99;
            acceleration_y_100 = 0.5f;
            return;

            case 322:
            zero_velocity_acceleration();
            gate_47e = 0;
            state_180 = 0;
            state_184 = 1;
            state_750 = 1;
            return;

            case 400:
            case 401:
            case 410:
            case 411:
            case 412:
            state_180 = 0;
            zero_velocity_acceleration();
            state_730 = 0;
            state_732 = 0;
            state_736 = 0;
            state_738 = 0;
            state_750 = 1;
            return;

            case 402:
            state_180 = 0;
            zero_velocity_acceleration();
            state_730 = 0;
            state_732 = 0;
            state_736 = 0;
            state_738 = 0;
            return;

            case 404:
            case 406:
            state_180 = 0;
            state_730 = 0;
            state_732 = 0;
            state_736 = 0;
            velocity_x_f4 = static_cast<float>(velocity_x_f4 * 0.2f);
            state_738 = 0;
            state_750 = 1;
            velocity_y_f8 = static_cast<float>(0.2f * velocity_y_f8);
            acceleration_y_100 = 0.6000000238418579f;
            return;

            case 408:
            state_180 = 0;
            gate_47e = 0;
            if (velocity_x_f4 < 7.5)
            velocity_x_f4 = 7.5f;
            return;

            case 409:
            gate_47e = 0;
            acceleration_y_100 = 0.3499999940395355f;
            state_730 = 0;
            state_180 = 0;
            state_184 = 1;
            return;

            case 414:
            case 415:
            case 416:
            state_180 = 0;
            velocity_x_f4 = static_cast<float>(velocity_x_f4 * 0.2f);
            velocity_y_f8 = static_cast<float>(0.2f * velocity_y_f8);
            acceleration_y_100 = 0.5f;
            state_730 = 0;
            state_732 = 0;
            state_736 = 0;
            state_738 = 0;
            state_750 = 1;
            return;

            case 418:
            state_180 = 0;
            gate_47e = 0;
            if (velocity_x_f4 < 10.0f)
            velocity_x_f4 = 10.0f;
            return;


            default:
                break;
            }
        } else {
            state_180 = 1;
            zero_velocity_acceleration();
            state_730 = 0;
            state_732 = 0;
            state_736 = 0;
            state_738 = 0;
            return;
        }
    } else {
        if (action <= 797) {
            switch (action_13c) {
                case 501:
                case 505:
                case 506:
                case 540:
                case 541:
                state_180 = 1;
                zero_velocity_acceleration();
                state_730 = 0;
                state_732 = 0;
                state_736 = 0;
                state_738 = 0;
                return;

                case 507:
                case 508:
                acceleration_y_100 = 0.0f;
                state_180 = 1;
                velocity_x_f4 = static_cast<float>(velocity_x_f4 * 0.25f);
                velocity_y_f8 = static_cast<float>(0.25f * velocity_y_f8);
                state_730 = 0;
                state_732 = 0;
                state_736 = 0;
                state_738 = 0;
                return;

                case 520:
                case 521:
                case 522:
                case 523:
                case 525:
                case 526:
                state_180 = 0;
                zero_velocity_acceleration();
                state_730 = 0;
                state_732 = 0;
                state_736 = 0;
                state_738 = 0;
                state_750 = 1;
                return;

                case 530:
                case 531:
                state_180 = 0;
                zero_velocity_acceleration();
                state_750 = 1;
                return;

                case 542:
                case 543:
                acceleration_y_100 = 0.0f;
                state_180 = 1;
                velocity_x_f4 = static_cast<float>(velocity_x_f4 * 0.2f);
                velocity_y_f8 = static_cast<float>(0.2f * velocity_y_f8);
                state_730 = 0;
                state_732 = 0;
                state_736 = 0;
                state_738 = 0;
                return;

                case 545:
                case 546:
                case 568:
                state_180 = 0;
                zero_velocity_acceleration();
                state_730 = 0;
                state_732 = 0;
                state_736 = 0;
                state_738 = 0;
                return;

                case 547:
                case 548:
                state_180 = 0;
                velocity_x_f4 = static_cast<float>(velocity_x_f4 * 0.25f);
                velocity_y_f8 = static_cast<float>(0.25f * velocity_y_f8);
                acceleration_y_100 = 0.5f;
                state_730 = 0;
                state_732 = 0;
                state_736 = 0;
                state_738 = 0;
                return;

                case 560:
                case 570:
                state_180 = 0;
                zero_velocity_acceleration();
                return;

                case 565:
                case 566:
                state_180 = 0;
                zero_velocity_acceleration();
                state_730 = 0;
                state_732 = 0;
                state_736 = 0;
                state_738 = 0;
                state_7d0 = 1;
                return;

                case 600:
                case 601:
                case 603:
                case 604:
                case 607:
                case 608:
                case 609:
                state_730 = 0;
                state_732 = 0;
                state_180 = 1;
                zero_velocity_acceleration();
                return;

                case 602:
                case 605:
                case 606:
                state_180 = 1;
                zero_velocity_acceleration();
                state_730 = 0;
                state_732 = 0;
                state_736 = 0;
                state_738 = 0;
                state_7d0 = 1;
                return;

                case 710:
                zero_velocity_acceleration();
                state_730 = 0;
                return;

                case 711:
                zero_velocity_acceleration();
                state_730 = 1;
                return;

                case 720:
                case 721:
                case 730:
                zero_velocity_acceleration();
                return;


            case 797:
                zero_velocity_acceleration();
                dispatch_indexed_event_member(31);
                velocity_x_f4 = 12.0f;
                state_730 = 0;
                velocity_y_f8 = 0.0f;
                acceleration_y_100 = 0.5f;
                return;

            default:
                break;
            }
        } else if (action == 798) {
            zero_velocity_acceleration();
            dispatch_indexed_event_member(31);
            velocity_x_f4 = 12.0f;
            state_730 = 0;
            velocity_y_f8 = 0.0f;
            acceleration_y_100 = 0.5f;
            return;
        }

    }

    initialize_common_action_state();
}

} // namespace th105
