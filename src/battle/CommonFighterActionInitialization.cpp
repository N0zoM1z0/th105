// JP1.06a 0x477830, exact.
#include "CommonFighterActionInitialization.hpp"
#include "battle/SpellRuntime.hpp"
#include <deque>
namespace th105 {
#define DIR static_cast<unsigned char>(facing_104)
void CommonActionEntryView::initialize_common_action_entry()
{
    switch (action_id_13c) {
    case 0:
    case 1:
    case 2:
    case 3:
        if (field_47e == 0)
            zero_motion();
        return;

    case 6:
        if ((field_724&4) || (field_6c8>0 && field_6b8 < 0 && field_6b4 == 0)) {
            set_action(208);
            return;
        }
        if (field_47e == 0)
            zero_motion();
        acceleration_y_100 = 0;
        return;

    case 7:
        if ((field_724&16) || (field_6c8>0 && field_6b8 < 0 && facing_104*field_6b4>0))
            set_action(209);
        else {
            if (field_47e == 0)
                zero_motion();
            acceleration_y_100 = 0;
        }
        return;

    case 8:
        if ((field_724&8) || (field_6c8>0 && field_6b8 < 0 && facing_104*field_6b4 < 0))
            set_action(210);
        else {
            if (field_47e == 0)
                zero_motion();
            acceleration_y_100 = 0;
        }
        return;

    case 10:
        dispatch_event(30);
        zero_motion();
        return;

    case 50:
    case 57:
    case 63:
        velocity_x_f4 = -15.0f;
        velocity_y_f8 = 0;
        field_18c = 0;
        field_190 = 0;
        field_12c = 0;
        return;

    case 51:
        velocity_x_f4 = -20.0f;
        velocity_y_f8 = 0;
        field_18c = 0;
        field_190 = 0;
        field_12c = 0;
        return;

    case 53:
        field_730 = 0;
        field_732 = 0;
        // The raw case53 prefix falls into the separate case52 literal load.

    case 52:
        velocity_x_f4 = -25.0f;
        velocity_y_f8 = 0;
        field_18c = 0;
        field_190 = 0;
        field_12c = 0;
        return;

    case 54:
    case 60:
    case 66:
        velocity_x_f4 = 0;
        velocity_y_f8 = 0;
        field_18c = 0;
        field_190 = 0;
        field_12c = 0;
        return;

    case 55:
    case 58:
    case 61:
    case 64:
    case 67:
        velocity_x_f4 = -20.0f;
        velocity_y_f8 = 0;
        field_18c = 0;
        field_190 = 0;
        field_12c = 0;
        return;

    case 56:
    case 62:
        velocity_x_f4 = -10.0f;
        velocity_y_f8 = 0;
        field_18c = 0;
        field_190 = 0;
        field_12c = 0;
        return;

    case 59:
    case 65:
        field_730 = 0;
        field_732 = 0;
        velocity_x_f4 = -25.0f;
        velocity_y_f8 = 0;
        field_18c = 0;
        field_190 = 0;
        field_12c = 0;
        return;

    case 70:
        field_730 = 0;
        velocity_x_f4 = -field_18c;
        velocity_y_f8 = field_190;
        acceleration_y_100 = 0.8f;
        if (velocity_x_f4>0)
            field_730 = 1;
        if (velocity_x_f4 < 0)
            field_730 = -1;
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
        for (int i = 0; i < 5; ++i)
            emit_effect(201, x_ec, static_cast<float>(y_f0 + 100.0), DIR, 1);
        ++field_730;
        field_108 = field_7a0;
        field_10c = field_7a2;
        field_186 = 5;
        emit_effect(38, static_cast<float>(x_ec-facing_104 * 50), static_cast<float>(y_f0 + 100.0), DIR, 1);
        emit_effect(59, static_cast<float>(x_ec-facing_104 * 50), static_cast<float>(y_f0 + 100.0), DIR, 1);
        velocity_x_f4 = 0;
        velocity_y_f8 = 0;
        acceleration_y_100 = 0;
        publish_layout_scalar(2.0f);
        dispatch_event(22);
        field_12c = 0;
        return;

    case 77:
        velocity_x_f4 = -field_18c;
        velocity_y_f8 = field_190;
        acceleration_y_100 = 0.8f;
        field_108 = field_7a0;
        field_10c = field_7a2;
        field_12c = 0;
        return;

    case 78:
        advance_secondary_event_effect_cycle();
        for (int i = 0; i < 5; ++i)
            emit_effect(201, x_ec, y_f0, DIR, 1);
        ++field_730;
        velocity_x_f4 = 0;
        velocity_y_f8 = 0;
        acceleration_y_100 = 0;
        publish_layout_scalar(4.0f);
        dispatch_event(22);
        emit_effect(38, static_cast<float>(x_ec-facing_104 * 50), static_cast<float>(y_f0 + 100.0), DIR, 1);
        emit_effect(59, static_cast<float>(x_ec-facing_104 * 50), static_cast<float>(y_f0 + 100.0), DIR, 1);
        field_12c = 0;
        return;

    case 89:
        advance_secondary_event_effect_cycle();
        emit_effect(58, x_ec, y_f0, DIR, -1);
        for (int i = 0; i < 5; ++i)
            emit_effect(201, x_ec, static_cast<float>(y_f0 + 100.0), DIR, 1);
        field_12c = 0;
        return;

    case 97:
        advance_secondary_event_effect_cycle();
        emit_effect(58, x_ec, y_f0, DIR, -1);
        for (int i = 0; i < 5; ++i)
            emit_effect(201, x_ec, y_f0, DIR, 1);
        field_12c = 0;
        return;

    case 98:
        zero_motion();
        field_47f = 0;
        field_730 = 0;
        return;

    case 99:
        zero_motion();
        field_73c = 0;
        field_740 = 0;
        field_744 = 0;
        field_47f = 0;
        field_748 = 0;
        field_730 = 0;
        field_74c = 0;
        field_732 = 0;
        field_734 = 0;
        field_736 = 0;
        field_738 = 0;
        return;

    case 140:
        velocity_x_f4 = -11.0f;
        field_730 = 0;
        velocity_y_f8 = 0;
        field_12c = 0;
        return;

    case 143:
    case 144:
        velocity_x_f4 = -12.0f;
        field_730 = 0;
        velocity_y_f8 = 0;
        field_12c = 0;
        return;

    case 145:
        velocity_x_f4 = -10.0f;
        velocity_y_f8 = 14.0f;
        acceleration_y_100 = 0.5f;
        field_12c = 0;
        return;

    case 149:
        velocity_x_f4 = -10.0f;
        velocity_y_f8 = 14.0f;
        acceleration_y_100 = 0.5f;
        return;

    case 150:
    case 154:
        field_730 = 0;
        velocity_x_f4 = -6.0f;
        velocity_y_f8 = 0;
        phase_state_180 = 0;
        return;

    case 151:
    case 155:
        field_730 = 0;
        velocity_x_f4 = -10.0f;
        velocity_y_f8 = 0;
        phase_state_180 = 0;
        return;

    case 152:
    case 156:
        field_730 = 0;
        velocity_x_f4 = -13.0f;
        velocity_y_f8 = 0;
        phase_state_180 = 0;
        return;

    case 153:
    case 157:
        field_730 = 0;
        velocity_x_f4 = -14.5f;
        velocity_y_f8 = 0;
        phase_state_180 = 0;
        return;

    case 158:
        velocity_x_f4 = -6.0f;
        field_730 = 7;
        velocity_y_f8 = 14.0f;
        field_732 = 0;
        acceleration_y_100 = 0.75f;
        return;

    case 159:
    case 163:
        field_730 = 0;
        velocity_x_f4 = -12.0f;
        velocity_y_f8 = 0;
        phase_state_180 = 0;
        return;

    case 160:
    case 164:
        field_730 = 0;
        velocity_x_f4 = -20.0f;
        velocity_y_f8 = 0;
        phase_state_180 = 0;
        return;

    case 161:
    case 165:
        field_730 = 0;
        velocity_x_f4 = -26.0f;
        velocity_y_f8 = 0;
        phase_state_180 = 0;
        return;

    case 162:
    case 166:
        field_730 = 0;
        velocity_x_f4 = -29.0f;
        velocity_y_f8 = 0;
        phase_state_180 = 0;
        return;

    case 167:
        velocity_x_f4 = -6.0f;
        field_730 = 7;
        velocity_y_f8 = 8.0f;
        acceleration_y_100 = 0.75f;
        return;

    case 180:
        zero_motion();
        velocity_x_f4 = 8.0f;
        velocity_y_f8 = 12.5f;
        acceleration_y_100 = 0.75f;
        emit_effect(61, x_ec, static_cast<float>(y_f0 + 100.0), DIR, 1);
        field_12c = 0;
        return;

    case 181:
        zero_motion();
        velocity_x_f4 = -8.0f;
        velocity_y_f8 = 12.5f;
        acceleration_y_100 = 0.75f;
        emit_effect(61, x_ec, static_cast<float>(y_f0 + 100.0), DIR, 1);
        field_12c = 0;
        return;

    case 197:
    case 198:
    case 199:
        zero_motion();
        return;

    case 200:
        field_47e = 1;
        // The target case200 prefix joins the201..203 actual clear/reset tail.

    case 201:
    case 202:
    case 203:
        zero_motion();
        field_730 = 0;
        field_732 = 0;
        field_734 = 0;
        return;

    case 208:
    case 209:
    case 210:
    case 211:
    case 212:
        if (field_47e == 0)
            zero_motion();
        acceleration_y_100 = 0;
        return;

    case 220:
    case 221:
    case 222:
        zero_motion();
        emit_effect(69, x_ec, static_cast<float>(y_f0 + 100.0), DIR, 1);
        return;

    case 223:
        field_47e = 1;
        zero_motion();
        emit_effect(69, x_ec, static_cast<float>(y_f0 + 100.0), DIR, 1);
        field_730 = 0;
        field_732 = 0;
        field_734 = 0;
        return;

    case 224:
        zero_motion();
        emit_effect(69, x_ec, static_cast<float>(y_f0 + 100.0), DIR, 1);
        field_730 = 0;
        field_732 = 0;
        field_734 = 0;
        return;

    case 225:
    case 226:
        zero_motion();
        emit_effect(69, x_ec, static_cast<float>(y_f0 + 100.0), DIR, 1);
        field_730 = 0;
        field_732 = 0;
        field_734 = 0;
        return;

    case 690: {
        emit_effect(71, x_ec, static_cast<float>(y_f0 + 100.0), DIR, 1);
        field_730 = 0;
        field_732 = 0;
        if (field_55a>0) {
            field_738 = (*reinterpret_cast<std::deque<FighterSequenceSlot> *>(reinterpret_cast<unsigned char *>(this) + 0x55c))[0].record_id_00;
            phase_state_180 = 1;
            zero_motion();
            switch (field_738) {
            case 100:
                if (++skill_levels_624[0][0] == 0)
                    skill_levels_624[0][0] = 1;
                if (skill_levels_624[0][0] >= 5)
                    skill_levels_624[0][0] = 4;
                skill_levels_624[1][0] = -1;
                skill_levels_624[2][0] = -1;
                skill_levels_624[3][0] = -1;
                break;

            case 101:
                if (++skill_levels_624[0][1] == 0)
                    skill_levels_624[0][1] = 1;
                if (skill_levels_624[0][1] >= 5)
                    skill_levels_624[0][1] = 4;
                skill_levels_624[1][1] = -1;
                skill_levels_624[2][1] = -1;
                skill_levels_624[3][1] = -1;
                break;

            case 102:
                if (++skill_levels_624[0][2] == 0)
                    skill_levels_624[0][2] = 1;
                if (skill_levels_624[0][2] >= 5)
                    skill_levels_624[0][2] = 4;
                skill_levels_624[1][2] = -1;
                skill_levels_624[2][2] = -1;
                skill_levels_624[3][2] = -1;
                break;

            case 103:
                if (++skill_levels_624[0][3] == 0)
                    skill_levels_624[0][3] = 1;
                if (skill_levels_624[0][3] >= 5)
                    skill_levels_624[0][3] = 4;
                skill_levels_624[1][3] = -1;
                skill_levels_624[2][3] = -1;
                skill_levels_624[3][3] = -1;
                break;

            case 104:
                if (++skill_levels_624[1][0] == 0)
                    skill_levels_624[1][0] = 1;
                if (skill_levels_624[1][0] >= 5)
                    skill_levels_624[1][0] = 4;
                skill_levels_624[0][0] = -1;
                skill_levels_624[2][0] = -1;
                skill_levels_624[3][0] = -1;
                break;

            case 105:
                if (++skill_levels_624[1][1] == 0)
                    skill_levels_624[1][1] = 1;
                if (skill_levels_624[1][1] >= 5)
                    skill_levels_624[1][1] = 4;
                skill_levels_624[0][1] = -1;
                skill_levels_624[2][1] = -1;
                skill_levels_624[3][1] = -1;
                break;

            case 106:
                if (++skill_levels_624[1][2] == 0)
                    skill_levels_624[1][2] = 1;
                if (skill_levels_624[1][2] >= 5)
                    skill_levels_624[1][2] = 4;
                skill_levels_624[0][2] = -1;
                skill_levels_624[2][2] = -1;
                skill_levels_624[3][2] = -1;
                break;

            case 107:
                if (++skill_levels_624[1][3] == 0)
                    skill_levels_624[1][3] = 1;
                if (skill_levels_624[1][3] >= 5)
                    skill_levels_624[1][3] = 4;
                skill_levels_624[0][3] = -1;
                skill_levels_624[2][3] = -1;
                skill_levels_624[3][3] = -1;
                break;

            case 108:
                if (++skill_levels_624[2][0] == 0)
                    skill_levels_624[2][0] = 1;
                if (skill_levels_624[2][0] >= 5)
                    skill_levels_624[2][0] = 4;
                skill_levels_624[0][0] = -1;
                skill_levels_624[1][0] = -1;
                skill_levels_624[3][0] = -1;
                break;

            case 109:
                if (++skill_levels_624[2][1] == 0)
                    skill_levels_624[2][1] = 1;
                if (skill_levels_624[2][1] >= 5)
                    skill_levels_624[2][1] = 4;
                skill_levels_624[0][1] = -1;
                skill_levels_624[1][1] = -1;
                skill_levels_624[3][1] = -1;
                break;

            case 110:
                if (++skill_levels_624[2][2] == 0)
                    skill_levels_624[2][2] = 1;
                if (skill_levels_624[2][2] >= 5)
                    skill_levels_624[2][2] = 4;
                skill_levels_624[0][2] = -1;
                skill_levels_624[1][2] = -1;
                skill_levels_624[3][2] = -1;
                break;

            case 111:
                if (++skill_levels_624[2][3] == 0)
                    skill_levels_624[2][3] = 1;
                if (skill_levels_624[2][3] >= 5)
                    skill_levels_624[2][3] = 4;
                skill_levels_624[0][3] = -1;
                skill_levels_624[1][3] = -1;
                skill_levels_624[3][3] = -1;
                break;

            case 112:
                if (++skill_levels_624[3][0] == 0)
                    skill_levels_624[3][0] = 1;
                if (skill_levels_624[3][0] >= 5)
                    skill_levels_624[3][0] = 4;
                skill_levels_624[0][0] = -1;
                skill_levels_624[1][0] = -1;
                skill_levels_624[2][0] = -1;
                break;

            case 113:
                if (++skill_levels_624[3][1] == 0)
                    skill_levels_624[3][1] = 1;
                if (skill_levels_624[3][1] >= 5)
                    skill_levels_624[3][1] = 4;
                skill_levels_624[0][1] = -1;
                skill_levels_624[1][1] = -1;
                skill_levels_624[2][1] = -1;
                break;

            case 114:
                if (++skill_levels_624[3][2] == 0)
                    skill_levels_624[3][2] = 1;
                if (skill_levels_624[3][2] >= 5)
                    skill_levels_624[3][2] = 4;
                skill_levels_624[0][2] = -1;
                skill_levels_624[1][2] = -1;
                skill_levels_624[2][2] = -1;
                break;

            case 115:
                if (++skill_levels_624[3][3] == 0)
                    skill_levels_624[3][3] = 1;
                if (skill_levels_624[3][3] >= 5)
                    skill_levels_624[3][3] = 4;
                skill_levels_624[0][3] = -1;
                skill_levels_624[1][3] = -1;
                skill_levels_624[2][3] = -1;
                break;
            }
        }
        emit_effect(static_cast<short>(reinterpret_cast<signed char *>(this)[0x5c0 + field_738] + 130), x_ec, y_f0, 1, 1);
        dispatch_sequence_window(0, 1, 60);
        return;
    }

    case 691:
        field_730 = 0;
        field_732 = 0;
        phase_state_180 = 1;
        zero_motion();
        return;

    case 692:
        emit_effect(71, x_ec, static_cast<float>(y_f0 + 100.0), DIR, 1);
        field_730 = 0;
        field_732 = 0;
        phase_state_180 = 1;
        zero_motion();
        dispatch_sequence_window(0, 1, 60);
        return;

    case 693:
        emit_effect(71, x_ec, static_cast<float>(y_f0 + 100.0), DIR, 1);
        field_730 = 0;
        field_732 = 0;
        phase_state_180 = 1;
        zero_motion();
        dispatch_sequence_window(0, 1, 60);
        return;

    case 694:
        emit_effect(71, x_ec, static_cast<float>(y_f0 + 100.0), DIR, 1);
        field_730 = 0;
        field_732 = 0;
        phase_state_180 = 1;
        zero_motion();
        dispatch_sequence_window(0, 1, 60);
        return;

    case 695:
        phase_index_184 = 1;
        phase_state_180 = 0;
        zero_motion();
        dispatch_sequence_window(0, 1, 60);
        return;

    case 696:
        phase_index_184 = 1;
        phase_state_180 = 0;
        field_47e = 0;
        zero_motion();
        emit_effect(69, x_ec, static_cast<float>(y_f0 + 100.0), DIR, 1);
        field_48a = 15;
        dispatch_sequence_window(0, 1, 60);
        return;

    case 700:
        zero_motion();
        acceleration_y_100 = 0;
        phase_state_180 = 1;
        return;

    case 701:
    case 702:
    case 703:
        zero_motion();
        acceleration_y_100 = 0;
        return;

    case 704:
        if (acceleration_y_100 == 0.0f)
            acceleration_y_100 = 0.5f;
        return;

    case 705:
        zero_motion();
        velocity_x_f4 = field_778;
        return;

    case 706:
        zero_motion();
        velocity_x_f4 = field_77c;
        return;

    case 709:
        dispatch_event(30);
        zero_motion();
        return;

    case 789:
        field_738 = 0;
        zero_motion();
        return;

    case 790:
        field_730 = 0;
        zero_motion();
        return;

    case 795:
        field_730 = 0;
        return;

    case 796:
    case 799:
        field_73c = 0;
        zero_motion();
        return;

    default:
        return;
    }
}
#undef DIR
}
