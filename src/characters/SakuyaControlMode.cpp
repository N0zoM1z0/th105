#include <stddef.h>
#include "battle/Collision.hpp"
#include "battle/SpellRuntime.hpp"

namespace th105 {

int __cdecl selector_random_roll(int limit);
extern int g_match_identifier;

struct SakuyaControlPeerView {
    unsigned char unknown_000[0x174];
    short value_174;
};

class SakuyaControlModeView {
public:
    virtual void slot_00();
    virtual void slot_04();
    virtual void set_action(int action);
    virtual void set_sequence(int sequence);
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
    short sequence_13e;
    unsigned char unknown_140[0x30];
    SakuyaControlPeerView *other_fighter_170;
    unsigned char unknown_174[0x334];
    short state_4a8;
    unsigned char unknown_4aa[2];
    short state_4ac;
    unsigned char unknown_4ae[0xac];
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
    unsigned char unknown_76e[0x0a];
    float motion_x_778;
    float motion_y_77c;
    float policy_x_780;
    float policy_y_784;
    float policy_scale_788;
};

typedef char SakuyaControl_action_offset[
    offsetof(SakuyaControlModeView, action_13c) == 0x13c ? 1 : -1];
typedef char SakuyaControl_sequence_offset[
    offsetof(SakuyaControlModeView, sequence_controller_55c) == 0x55c ? 1 : -1];
typedef char SakuyaControl_state4a8_offset[
    offsetof(SakuyaControlModeView, state_4a8) == 0x4a8 ? 1 : -1];
typedef char SakuyaControl_policy_offset[
    offsetof(SakuyaControlModeView, policy_counter_764) == 0x764 ? 1 : -1];
typedef char SakuyaControl_motion_offset[
    offsetof(SakuyaControlModeView, motion_x_778) == 0x778 ? 1 : -1];

void SakuyaControlModeView::update_control_mode()
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
                    return;
                }
            }
            if (policy_counter_76a == 1 && other_fighter_170->value_174 > 0) {
                if (action_13c == 700 || action_13c == 0) {
                    face_opponent_and_flip_horizontal_velocity();
                    if (static_cast<unsigned int>(selector_random_roll(100)) <= 50) {
                        set_action(710);
                        policy_counter_76a = 2;
                        return;
                    }
                    set_action(711);
                    policy_x_780 = static_cast<float>(
                        static_cast<unsigned int>(selector_random_roll(6))) - 3.0f;
                    policy_y_784 = static_cast<float>(
                        static_cast<unsigned int>(selector_random_roll(3))) + 12.0f;
                    policy_counter_76a = 2;
                    policy_scale_788 = 0.5f;
                    return;
                }
            }
            if (policy_counter_76a == 2 && other_fighter_170->value_174 > 0) {
                if (action_13c == 700 || action_13c == 0) {
                    face_opponent_and_flip_horizontal_velocity();
                    if (facing_104 == 1) {
                        if (x_ec < 180.0f) {
                            set_action(705);
                            motion_x_778 = 6.0f;
                            policy_counter_768 = static_cast<short>(selector_random_roll(60) + 60);
                            return;
                        }
                        if (static_cast<unsigned int>(selector_random_roll(100)) > 50) {
                            set_action(705);
                            motion_x_778 = 6.0f;
                            policy_counter_768 = static_cast<short>(selector_random_roll(60) + 90);
                            return;
                        } else {
                            set_action(706);
                            motion_y_77c = -6.0f;
                            policy_counter_768 = static_cast<short>(selector_random_roll(60) + 90);
                            return;
                        }
                    } else {
                        if (x_ec > 1100.0f) {
                            set_action(705);
                            motion_x_778 = 6.0f;
                            policy_counter_768 = static_cast<short>(selector_random_roll(60) + 60);
                            return;
                        }
                        if (static_cast<unsigned int>(selector_random_roll(100)) > 50) {
                            set_action(705);
                            motion_x_778 = 6.0f;
                            policy_counter_768 = static_cast<short>(selector_random_roll(60) + 90);
                            return;
                        } else {
                            set_action(706);
                            motion_y_77c = -6.0f;
                            policy_counter_768 = static_cast<short>(selector_random_roll(60) + 90);
                            return;
                        }
                    }
                }
            }
            if (action_13c == 705 || action_13c == 706) {
                if (facing_104 == 1 && x_ec > 1220.0f && velocity_x_f4 > 0.0f)
                    facing_104 = -1;
                if (facing_104 == -1 && x_ec < 60.0f && velocity_x_f4 > 0.0f)
                    facing_104 = 1;
                if (policy_counter_768 <= 0) {
                    policy_counter_76a = 1;
                    set_action(700);
                    return;
                }
            }
            return;

        case 4:
        case 5:
        case 6:
        case 7:
            if (policy_counter_76a == 0) {
                if (action_13c == 700 || action_13c == 0) {
                    set_action(770);
                    policy_counter_76a = 1;
                    return;
                }
            }
            if (policy_counter_76a == 1 &&
                (action_13c == 700 || action_13c == 0)) {
                set_action(720);
                policy_counter_76a = 2;
                face_opponent_and_flip_horizontal_velocity();
                return;
            }
            if (policy_counter_76a == 2 &&
                (action_13c == 700 || action_13c == 0)) {
                set_action(721);
                policy_x_780 = static_cast<float>(
                    static_cast<unsigned int>(selector_random_roll(6))) - 3.0f;
                policy_y_784 = static_cast<float>(
                    static_cast<unsigned int>(selector_random_roll(3))) + 12.0f;
                policy_scale_788 = 0.5f;
                policy_counter_76a = 3;
                face_opponent_and_flip_horizontal_velocity();
                return;
            }
            if (policy_counter_76a == 3 &&
                (action_13c == 700 || action_13c == 0)) {
                switch (g_match_identifier) {
                case 0: policy_counter_768 = 30; policy_counter_76a = 4; break;
                case 1: policy_counter_768 = 20; policy_counter_76a = 4; break;
                case 2: policy_counter_768 = 15; policy_counter_76a = 4; break;
                case 3: policy_counter_768 = 10; policy_counter_76a = 4; break;
                default: policy_counter_76a = 4; break;
                }
            }
            if (policy_counter_76a == 4 && policy_counter_768 <= 0 &&
                (action_13c == 700 || action_13c == 0)) {
                set_action(722);
                face_opponent_and_flip_horizontal_velocity();
                policy_counter_76a = 1;
            }
            return;

        case 8:
        case 9:
        case 10:
        case 11:
            if (policy_counter_76a == 0) {
                if (action_13c == 700 || action_13c == 0) {
                    set_action(770);
                    policy_counter_76a = 1;
                    return;
                }
            }
            if (policy_counter_76a == 1 &&
                (action_13c == 700 || action_13c == 0)) {
                set_action(730);
                policy_counter_76a = 2;
                face_opponent_and_flip_horizontal_velocity();
            } else if (policy_counter_76a == 2 &&
                       (action_13c == 700 || action_13c == 0)) {
                switch (g_match_identifier) {
                case 0: policy_counter_768 = 30; break;
                case 1: policy_counter_768 = 20; break;
                case 2: policy_counter_768 = 15; break;
                case 3: policy_counter_768 = 10; break;
                default: break;
                }
                policy_counter_76a = 3;
            }
            if (policy_counter_76a == 3 && policy_counter_768 <= 0 &&
                (action_13c == 700 || action_13c == 0)) {
                set_action(722);
                face_opponent_and_flip_horizontal_velocity();
                policy_counter_76a = 1;
            }
            return;

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
            return;

        case 12:
        case 13:
        case 14:
        case 15:
            if (policy_counter_76a == 0) {
                if (action_13c == 700 || action_13c == 0) {
                    set_action(770);
                    policy_counter_76a = 1;
                    return;
                }
                state_4a8 = 2;
                state_4ac = 2;
            }
            if (policy_counter_76a == 1 &&
                (action_13c == 700 || action_13c == 0)) {
                set_action(740);
                policy_counter_76a = 2;
                face_opponent_and_flip_horizontal_velocity();
            } else if (policy_counter_76a == 2 &&
                       (action_13c == 700 || action_13c == 0)) {
                switch (g_match_identifier) {
                case 0: policy_counter_768 = 30; break;
                case 1: policy_counter_768 = 20; break;
                case 2: policy_counter_768 = 15; break;
                case 3: policy_counter_768 = 10; break;
                default: break;
                }
                policy_counter_76a = 3;
            }
            if (policy_counter_76a == 3 && policy_counter_768 <= 0 &&
                (action_13c == 700 || action_13c == 0)) {
                set_action(722);
                face_opponent_and_flip_horizontal_velocity();
                policy_counter_76a = 1;
            }
            return;
        }
    }
}

} // namespace th105
