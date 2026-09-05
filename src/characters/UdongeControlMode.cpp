#include <stddef.h>
#include "battle/Collision.hpp"
#include "battle/SpellRuntime.hpp"

namespace th105 {

int __cdecl selector_random_roll(int limit);
float __cdecl lookup_orientation_sine_quantized_abs(float phase);
float __cdecl lookup_orientation_cosine_quantized_abs(float phase);

struct UdongeControlPeerView {
    unsigned char unknown_000[0xec];
    float x_ec;
    float y_f0;
    unsigned char unknown_f4[0x80];
    short value_174;
};

class UdongeControlModeView {
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
    int spawn_owned_object_via_manager(
        int object_id, float x, float y, int direction, unsigned char arg5,
        int arg6, int arg7);
    void dispatch_character_wave_handle(unsigned index);

    unsigned char unknown_004[0xe8];
    float x_ec;
    float y_f0;
    float velocity_x_f4;
    float velocity_y_f8;
    float acceleration_x_fc;
    float acceleration_y_100;
    unsigned char facing_104;
    unsigned char unknown_105[0x37];
    short action_13c;
    short sequence_13e;
    unsigned char unknown_140[0x30];
    UdongeControlPeerView *other_fighter_170;
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
    unsigned char unknown_76e[0x0a];
    float motion_x_778;
    float motion_y_77c;
    float policy_x_780;
    float policy_y_784;
    float policy_scale_788;
};

typedef char UdongeControl_action_offset[
    offsetof(UdongeControlModeView, action_13c) == 0x13c ? 1 : -1];
typedef char UdongeControl_sequence_offset[
    offsetof(UdongeControlModeView, sequence_controller_55c) == 0x55c ? 1 : -1];
typedef char UdongeControl_policy_offset[
    offsetof(UdongeControlModeView, policy_counter_764) == 0x764 ? 1 : -1];
typedef char UdongeControl_motion_offset[
    offsetof(UdongeControlModeView, motion_x_778) == 0x778 ? 1 : -1];

void UdongeControlModeView::update_control_mode()
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
        int record_id = sequence_controller_55c.entry_at_checked(0)->record_id_00;
        if (record_id <= 11) {
            if (record_id < 8) {
                switch (record_id) {
                case 0:
                case 1:
                case 2:
                case 3:
                    if (policy_counter_76a == 0 &&
                        (action_13c == 700 || action_13c == 0)) {
                        set_action(770);
                        policy_counter_76a = 1;
                        return;
                    }
                    if (policy_counter_76a == 1) {
                        if (other_fighter_170->value_174 > 0) {
                            if (action_13c == 700 || action_13c == 0) {
                                face_opponent_and_flip_horizontal_velocity();
                                set_action(710);
                                policy_counter_76a = 2;
                                return;
                            }
                        } else {
                            policy_counter_76a = 1;
                        }
                    }
                    if (policy_counter_76a == 2 && other_fighter_170->value_174 > 0 &&
                        (action_13c == 700 || action_13c == 0)) {
                        face_opponent_and_flip_horizontal_velocity();
                        policy_x_780 = static_cast<float>(
                            static_cast<unsigned int>(selector_random_roll(15)));
                        policy_y_784 = static_cast<float>(
                            static_cast<float>(static_cast<unsigned int>(selector_random_roll(4))) + 8.0);
                        policy_scale_788 = 0.30000001192092896f;
                        set_action(701);
                        policy_counter_76a = 1;
                    }
                    return;

                case 4:
                case 5:
                case 6:
                case 7: {
                    if (policy_counter_76a == 0) {
                        if (action_13c == 700 || action_13c == 0) {
                            set_action(770);
                            policy_counter_76a = 1;
                            policy_counter_76c = 0;
                            return;
                        }
                    }

                    if (policy_counter_76a >= 1 && action_13c != 770) {
                        ++policy_counter_76c;
                        if ((policy_counter_76c % 3) == 0) {
                            const float phase = static_cast<float>(
                                static_cast<unsigned int>(selector_random_roll(360)));
                            const float radius = static_cast<float>(
                                static_cast<float>(static_cast<unsigned int>(selector_random_roll(200))) + 100.0);
                            float params[3];
                            params[0] = static_cast<float>(
                                static_cast<unsigned int>(selector_random_roll(360)));
                            params[1] = static_cast<float>(
                                static_cast<float>(static_cast<unsigned int>(selector_random_roll(8))) + 5.0);
                            params[2] = 4.0f;
                            spawn_owned_object_via_manager(
                                910,
                                static_cast<float>(
                                    lookup_orientation_cosine_quantized_abs(phase) * radius +
                                    other_fighter_170->x_ec),
                                static_cast<float>(
                                    lookup_orientation_sine_quantized_abs(phase) * radius +
                                    other_fighter_170->y_f0 + 100.0f),
                                static_cast<unsigned char>(facing_104), 1,
                                reinterpret_cast<int>(params), 3);
                            dispatch_character_wave_handle(2);
                        }
                    }

                    if (policy_counter_76a == 1) {
                        if (action_13c == 700 || action_13c == 0) {
                            if (static_cast<unsigned int>(selector_random_roll(100)) < 50u) {
                                face_opponent_and_flip_horizontal_velocity();
                                policy_x_780 = static_cast<float>(
                                    static_cast<float>(static_cast<unsigned int>(selector_random_roll(5))) + 5.0);
                                policy_y_784 = static_cast<float>(
                                    static_cast<float>(static_cast<unsigned int>(selector_random_roll(4))) + 12.0);
                                policy_scale_788 = 0.30000001192092896f;
                                set_action(701);
                                policy_counter_76a = 3;
                                return;
                            }
                            if (facing_104 == 1) {
                                if (x_ec < 180.0f) {
                                    set_action(705);
                                    motion_x_778 = 6.0f;
                                    policy_counter_768 = static_cast<short>(selector_random_roll(30) + 60);
                                    return;
                                }
                                if (static_cast<unsigned int>(selector_random_roll(100)) > 50u) {
                                    set_action(705);
                                    motion_x_778 = 5.0f;
                                    policy_counter_768 = static_cast<short>(selector_random_roll(30) + 60);
                                    return;
                                }
                                set_action(706);
                                motion_y_77c = -5.0f;
                                policy_counter_768 = static_cast<short>(selector_random_roll(30) + 60);
                                return;
                            }
                            if (x_ec > 1100.0f) {
                                set_action(705);
                                motion_x_778 = 5.0f;
                                policy_counter_768 = static_cast<short>(selector_random_roll(30) + 60);
                                return;
                            }
                            if (static_cast<unsigned int>(selector_random_roll(100)) <= 50u) {
                                set_action(706);
                                motion_y_77c = -6.0f;
                            } else {
                                set_action(705);
                                motion_x_778 = 6.0f;
                            }
                            policy_counter_768 = static_cast<short>(selector_random_roll(30) + 60);
                            return;
                        }
                        if ((action_13c == 705 || action_13c == 706) &&
                            policy_counter_768 <= 0) {
                            set_action(700);
                            policy_counter_76a = 3;
                            return;
                        }
                    }

                    if (policy_counter_76a == 3) {
                        if (other_fighter_170->value_174 <= 0) {
                            policy_counter_76a = 1;
                            return;
                        }
                        if (action_13c == 700 || action_13c == 0) {
                            face_opponent_and_flip_horizontal_velocity();
                            if (static_cast<unsigned int>(selector_random_roll(100)) <= 60u)
                                set_action(725);
                            else
                                set_action(726);
                            policy_counter_76a = 1;
                        }
                    }
                    return;
                }

                default:
                    return;
                }
            } else {
                    if (policy_counter_76a == 0 &&
                        (action_13c == 700 || action_13c == 0)) {
                        set_action(770);
                        policy_counter_76a = 1;
                        return;
                    }
                    if (policy_counter_76a == 1) {
                        if (other_fighter_170->value_174 > 0) {
                            if (action_13c == 700 || action_13c == 0) {
                                face_opponent_and_flip_horizontal_velocity();
                                set_action(730);
                                policy_counter_76a = 2;
                                return;
                            }
                        } else {
                            policy_counter_76a = 1;
                        }
                    }
                    if (policy_counter_76a == 2 && other_fighter_170->value_174 > 0 &&
                        policy_counter_768 <= 0 &&
                        (action_13c == 700 || action_13c == 0)) {
                        face_opponent_and_flip_horizontal_velocity();
                        policy_x_780 = static_cast<float>(
                            static_cast<float>(static_cast<unsigned int>(selector_random_roll(5))) + 10.0);
                        policy_y_784 = static_cast<float>(
                            static_cast<float>(static_cast<unsigned int>(selector_random_roll(4))) + 8.0);
                        policy_scale_788 = 0.5f;
                        set_action(702);
                        policy_counter_76a = 1;
                    }
                    return;
            }
        } else {
                record_id -= 248;
                if (static_cast<unsigned int>(record_id) <= 7u) {
                    if (action_13c == 700)
                        set_action(0);
                    update_cpu_action_policy();
                }
                return;
        }
    }
}

} // namespace th105
