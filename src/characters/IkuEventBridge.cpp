#include <stddef.h>

// Narrow 1.06a source view for Iku's event bridge. Current target access widths,
// two independent spawn temporaries, and unused-this helper ABIs define this view.

namespace th105 {
struct SharedEventState {
    char set_target_20_enabled_2c(char enabled, float target);
    char set_target_24_enabled_2d(char enabled, float target);
    char set_target_28_enabled_2e(char enabled, float target);
    int synchronize_targets();
};
extern SharedEventState g_shared_event_state;

struct EventSubobject130 {
    unsigned char storage_00[0x0c];
    int trigger_global_effect(int value);
    void *set_global_pair(float first, float second);
};

class IkuEventView {
public:
    virtual ~IkuEventView();
    virtual void virtual_slot_04();
    virtual void set_action(int action_id);
    virtual void set_sequence(int sequence_id);

    unsigned char handle_event_bridge(int event_code);
    char set_shared_second_target(char enabled, float target);
    void zero_velocity_acceleration();
    int spawn_owned_object_via_manager(
        int object_id, float x, float y, int direction,
        int arg5, int arg6, int arg7);

    unsigned char unknown_004[0xe8];
    float x_ec;
    float y_f0;
    float velocity_x_f4;
    float velocity_y_f8;
    float acceleration_x_fc;
    float acceleration_y_100;
    signed char facing_104;
    unsigned char unknown_105[0x0b];
    unsigned char byte_110;
    unsigned char byte_111;
    unsigned char byte_112;
    unsigned char unknown_113[0x1d];
    EventSubobject130 event_subobject_130;
    short state_13c;
    unsigned char unknown_13e[0x32];
    IkuEventView *other_fighter_170;
    unsigned char unknown_174[0x5bc];
    short event_counter_730;
    short event_timer_732;
    short word_734;
    short word_736;
    short word_738;
    unsigned char unknown_73a[2];
    float float_73c;
    float float_740;
    float float_744;
    float float_748;
    unsigned char unknown_74c[0x0d];
    unsigned char event_flag_759;
    unsigned char unknown_75a[2];
    int event_value_75c;
    int event_value_760;
    unsigned char unknown_764[0x0c];
    short word_770;
    unsigned char unknown_772[0x40];
    short word_7b2;
    float float_7b4;
};

typedef char Iku_state_offset[offsetof(IkuEventView, state_13c) == 0x13c ? 1 : -1];
typedef char Iku_counter_offset[offsetof(IkuEventView, event_counter_730) == 0x730 ? 1 : -1];
typedef char Iku_float_73c_offset[offsetof(IkuEventView, float_73c) == 0x73c ? 1 : -1];
typedef char Iku_word_770_offset[offsetof(IkuEventView, word_770) == 0x770 ? 1 : -1];
typedef char Iku_word_7b2_offset[offsetof(IkuEventView, word_7b2) == 0x7b2 ? 1 : -1];

unsigned char IkuEventView::handle_event_bridge(int event_code)
{
    float spawn_999_words[3];
    float spawn_995_words[3];
    switch (event_code) {
    case 1:
        x_ec = 100.0f;
        event_counter_730 = 640;
        event_timer_732 = 0;
        g_shared_event_state.set_target_20_enabled_2c(1, 640.0f);
        set_shared_second_target(1, static_cast<float>(event_counter_730));
        g_shared_event_state.set_target_28_enabled_2e(1, 1.0f);
        g_shared_event_state.synchronize_targets();
        return false;
    case 2:
        g_shared_event_state.set_target_20_enabled_2c(1, 640.0f);
        set_shared_second_target(1, static_cast<float>(event_counter_730));
        g_shared_event_state.set_target_28_enabled_2e(1, 1.0f);
        event_counter_730 -= 5;
        if (event_counter_730 <= 0) {
            ++event_timer_732;
            event_counter_730 = 0;
            if (event_timer_732 >= 60)
                return false;
        }
        return true;
    case 3:
        g_shared_event_state.set_target_20_enabled_2c(0, 640.0f);
        g_shared_event_state.set_target_24_enabled_2d(0, 0.0f);
        g_shared_event_state.set_target_28_enabled_2e(0, 1.0f);
        return false;
    case 4:
        g_shared_event_state.set_target_20_enabled_2c(1, 640.0f);
        g_shared_event_state.set_target_24_enabled_2d(1, 0.0f);
        g_shared_event_state.set_target_28_enabled_2e(1, 1.0f);
        return false;
    case 5:
        x_ec = 0.0f;
        y_f0 = 0.0f;
        zero_velocity_acceleration();
        set_action(0);
        return false;
    case 6:
        set_action(790);
        set_sequence(2);
        x_ec = 480.0f;
        y_f0 = 800.0f;
        velocity_x_f4 = 0.0f;
        velocity_y_f8 = 0.0f;
        acceleration_y_100 = 0.25f;
        return false;
    case 7:
    case 51:
        return state_13c != 0;
    case 8:
        set_action(139);
        spawn_999_words[0] = 0.0f;
        spawn_999_words[1] = 0.0f;
        spawn_999_words[2] = 0.0f;
        spawn_owned_object_via_manager(999, x_ec, y_f0, 1, 1,
            reinterpret_cast<int>(spawn_999_words), 3);
        return false;
    case 9:
        x_ec = 100.0f;
        y_f0 = 2.0f;
        facing_104 = 1;
        velocity_x_f4 = 6.0f;
        velocity_y_f8 = 15.0f;
        acceleration_y_100 = 0.5f;
        set_action(797);
        return false;
    case 11:
        g_shared_event_state.set_target_20_enabled_2c(1, 640.0f);
        g_shared_event_state.set_target_24_enabled_2d(1, 0.0f);
        g_shared_event_state.set_target_28_enabled_2e(1, 1.0f);
        g_shared_event_state.synchronize_targets();
        return false;
    case 50:
        x_ec = 70.0f;
        y_f0 = 160.0f;
        set_action(797);
        return false;
    case 101:
        x_ec = 1210.0f;
        y_f0 = 160.0f;
        set_action(798);
        return false;
    case 102:
    case 106:
    case 111:
        return state_13c != 700;
    case 103:
        event_subobject_130.trigger_global_effect(13);
        event_flag_759 = 1;
        event_value_75c = 0;
        event_value_760 = 180;
        return false;
    case 105: {
        IkuEventView *const other = other_fighter_170;
        y_f0 = 960.0f;
        x_ec = other->x_ec + 250 * static_cast<signed char>(other->facing_104);
        facing_104 = static_cast<signed char>(-other->facing_104);
        set_action(795);
        return false;
    }
    case 110:
        set_action(796);
        return false;
    case 113:
        event_subobject_130.trigger_global_effect(13);
        return false;
    case 130:
        x_ec = 800.0f;
        byte_112 = 32;
        byte_111 = 32;
        y_f0 = 640.0f;
        byte_110 = 32;
        float_740 = 100.0f;
        event_counter_730 = 0;
        set_action(780);
        return false;
    case 131:
        event_counter_730 = 1;
        return false;
    case 132:
        event_counter_730 = 3;
        return false;
    case 133:
        event_subobject_130.trigger_global_effect(16);
        return false;
    case 134:
        set_action(781);
        spawn_995_words[0] = 0.0f;
        spawn_995_words[1] = 0.0f;
        spawn_995_words[2] = 0.0f;
        word_7b2 = 32;
        spawn_owned_object_via_manager(995, 0.0f, 0.0f, 1, 1,
            reinterpret_cast<int>(spawn_995_words), 3);
        return false;
    case 135:
        set_action(781);
        set_sequence(1);
        return false;
    case 138:
        x_ec = 0.0f;
        set_action(0);
        float_73c = 0.0f;
        float_740 = 100.0f;
        float_744 = 800.0f;
        float_748 = 0.0f;
        word_736 = 0;
        word_734 = 0;
        event_timer_732 = 0;
        event_counter_730 = 0;
        word_738 = 700;
        word_770 = 255;
        event_subobject_130.trigger_global_effect(13);
        float_7b4 = 300.0f;
        event_subobject_130.set_global_pair(0.0f, 300.0f);
        return false;
    case 139:
        x_ec = 1280.0f;
        set_action(700);
        float_73c = 0.0f;
        float_740 = 100.0f;
        float_744 = 800.0f;
        word_736 = 0;
        word_734 = 0;
        event_timer_732 = 0;
        event_counter_730 = 0;
        word_738 = 700;
        word_770 = 255;
        event_subobject_130.trigger_global_effect(13);
        float_7b4 = 300.0f;
        event_subobject_130.set_global_pair(0.0f, 300.0f);
        return false;
    }
    return true;
}
}
