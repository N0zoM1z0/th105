#include <stddef.h>
#include "battle/Collision.hpp"
#include "battle/SpellRuntime.hpp"

namespace th105 {

int __cdecl selector_random_roll(int limit);

struct RemiliaControlPeerView {
    unsigned char unknown_000[0x174];
    short value_174;
};

class RemiliaControlModeView {
public:
    virtual void slot_00();
    virtual void slot_04();
    virtual void set_action(int action);
    virtual void slot_0c();
    virtual void slot_10();
    virtual void slot_14();
    virtual void slot_18();
    virtual void slot_1c();
    virtual void slot_20();
    virtual void slot_24();
    virtual void slot_28();
    virtual void slot_2c();
    virtual void slot_30();
    virtual void slot_34();
    virtual void slot_38();
    virtual void slot_3c();
    virtual void slot_40();
    virtual void slot_44();
    virtual void slot_48();
    virtual void slot_4c();
    virtual void slot_50();
    virtual void slot_54();
    virtual void update_cpu_action_policy();

    void update_control_mode();
    void face_opponent_and_flip_horizontal_velocity();

    unsigned char unknown_004[0x138];
    short action_13c;
    unsigned char unknown_13e[0x32];
    RemiliaControlPeerView *other_fighter_170;
    unsigned char unknown_174[0x3e6];
    signed char sequence_state_55a;
    signed char sequence_state_55b;
    FighterSequenceController sequence_controller_55c;
    unsigned char unknown_570[0x144];
    int control_6b4;
    int control_6b8;
    int control_6bc;
    int control_6c0;
    int control_6c4;
    int control_6c8;
    int control_6cc;
    int control_6d0;
    unsigned char unknown_6d4[0x50];
    int command_flags_724;
    int command_flags_728;
    unsigned char unknown_72c[0x38];
    short policy_counter_764;
    short policy_counter_766;
    short policy_counter_768;
    short policy_counter_76a;
    short policy_counter_76c;
    unsigned char unknown_76e[0x12];
    float policy_x_780;
    float policy_y_784;
    float policy_scale_788;
};

typedef char RemiliaControl_action_offset[
    offsetof(RemiliaControlModeView, action_13c) == 0x13c ? 1 : -1];
typedef char RemiliaControl_sequence_offset[
    offsetof(RemiliaControlModeView, sequence_controller_55c) == 0x55c ? 1 : -1];
typedef char RemiliaControl_policy_offset[
    offsetof(RemiliaControlModeView, policy_counter_764) == 0x764 ? 1 : -1];
typedef char RemiliaControl_derived_offset[
    offsetof(RemiliaControlModeView, policy_x_780) == 0x780 ? 1 : -1];

void RemiliaControlModeView::update_control_mode()
{
    --policy_counter_768;
    command_flags_724 = 0;
    command_flags_728 = 0;
    control_6b4 = 0;
    control_6b8 = 0;
    control_6bc = 0;
    control_6c0 = 0;
    control_6c4 = 0;
    control_6c8 = 0;
    control_6cc = 0;
    control_6d0 = 0;

    if (action_13c > 49 && action_13c < 150) {
        policy_counter_76c = 0;
        policy_counter_76a = 0;
        policy_counter_766 = 0;
        policy_counter_768 = 0;
        policy_counter_764 = 0;
    }
    if (action_13c <= 199) {
        policy_counter_76c = 0;
        policy_counter_764 = 0;
    }

    if (sequence_state_55a >= 1) {
        const short record_id = sequence_controller_55c.entry_at_checked(0)->record_id_00;
        switch (record_id) {
        case 0:
        case 1:
        case 2:
        case 3:
            if (policy_counter_76a == 0) {
                if (action_13c == 700 || action_13c == 0) {
                    set_action(770);
                    policy_counter_76a = 1;
                    break;
                }
            }
            if (policy_counter_76a == 1 && other_fighter_170->value_174 > 0) {
                if (action_13c == 700 || action_13c == 0) {
                    face_opponent_and_flip_horizontal_velocity();
                    policy_x_780 = static_cast<float>(
                        15.0 - static_cast<float>(
                            static_cast<unsigned int>(selector_random_roll(30))));
                    policy_y_784 = static_cast<float>(
                        static_cast<float>(
                            static_cast<unsigned int>(selector_random_roll(4))) + 15.0);
                    policy_scale_788 = 0.75f;
                    set_action(701);
                    policy_counter_76a = 2;
                    break;
                }
            }
            if (policy_counter_76a == 2) {
                if (other_fighter_170->value_174 <= 0) {
                    policy_counter_76a = 1;
                    break;
                }
                if (action_13c == 700 || action_13c == 0) {
                    face_opponent_and_flip_horizontal_velocity();
                    set_action(710);
                    policy_counter_76a = 1;
                }
            }
            break;

        case 4:
        case 5:
        case 6:
        case 7:
            if (policy_counter_76a == 0) {
                if (action_13c == 700 || action_13c == 0) {
                    set_action(770);
                    policy_counter_76a = 1;
                    break;
                }
            }
            if (policy_counter_76a == 1) {
                if (action_13c == 700 || action_13c == 0) {
                    face_opponent_and_flip_horizontal_velocity();
                    set_action(720);
                    policy_counter_76a = 3;
                    break;
                }
            }
            if (policy_counter_76a == 2 && other_fighter_170->value_174 > 0) {
                if (action_13c == 700 || action_13c == 0) {
                    face_opponent_and_flip_horizontal_velocity();
                    policy_x_780 = static_cast<float>(
                        15.0 - static_cast<float>(
                            static_cast<unsigned int>(selector_random_roll(30))));
                    policy_y_784 = static_cast<float>(
                        static_cast<float>(
                            static_cast<unsigned int>(selector_random_roll(4))) + 15.0);
                    policy_scale_788 = 0.75f;
                    set_action(701);
                    policy_counter_76a = 3;
                    break;
                }
            }
            if (policy_counter_76a == 3) {
                if (action_13c == 700 || action_13c == 0) {
                    face_opponent_and_flip_horizontal_velocity();
                    set_action(721);
                    policy_counter_76a = 1;
                }
            }
            break;

        case 8:
        case 9:
        case 10:
        case 11:
            if (policy_counter_76a == 0) {
                if (action_13c == 700 || action_13c == 0) {
                    set_action(770);
                    policy_counter_76a = 1;
                    break;
                }
            }
            if (policy_counter_76a == 1) {
                face_opponent_and_flip_horizontal_velocity();
                if (action_13c == 700 || action_13c == 0) {
                    policy_counter_76a = 1;
                    if (static_cast<unsigned int>(selector_random_roll(100)) <= 50)
                        set_action(731);
                    else
                        set_action(730);
                }
            }
            break;

        case 248:
        case 249:
        case 250:
        case 251:
        case 252:
        case 253:
        case 254:
        case 255:
            if (action_13c == 700)
                set_action(0);
            update_cpu_action_policy();
            break;

        case 12:
        case 13:
        case 14:
        case 15:
            if (policy_counter_76a == 0 &&
                (action_13c == 700 || action_13c == 0)) {
                set_action(740);
                policy_counter_76a = 1;
            }
            break;

        default:
            break;
        }
    }
}

} // namespace th105
