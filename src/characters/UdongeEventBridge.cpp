#include <stddef.h>

// Narrow 1.06a source view for Udonge's event bridge. Only fields, access widths,
// virtual slots, and event payloads directly established by current target
// control flow are represented here.

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
};

class UdongeEventView {
public:
    virtual ~UdongeEventView();
    virtual void virtual_slot_04();
    virtual void set_action(int action_id);
    virtual void set_sequence(int sequence_id);

    unsigned char handle_event_bridge(int event_code);
    void zero_velocity_acceleration();
    int spawn_owned_object_via_manager(
        int object_id,
        float x,
        float y,
        int direction,
        int arg5,
        int arg6,
        int arg7);

public:
    unsigned char unknown_004[0xe8];
    float x_ec;
    float y_f0;
    float velocity_x_f4;
    float velocity_y_f8;
    float acceleration_x_fc;
    float acceleration_y_100;
    signed char facing_104;
    unsigned char unknown_105[0x2b];
    EventSubobject130 event_subobject_130;
    short state_13c;
    unsigned char unknown_13e[0x32];
    UdongeEventView *other_fighter_170;
    unsigned char unknown_174[0x5bc];
    short event_counter_730;
    short event_timer_732;
    unsigned char unknown_734[0x25];
    unsigned char event_flag_759;
    unsigned char unknown_75a[2];
    int event_value_75c;
    int event_value_760;
};

typedef char UdongeEventView_state_13c_offset[
    offsetof(UdongeEventView, state_13c) == 0x13c ? 1 : -1];
typedef char UdongeEventView_other_offset[
    offsetof(UdongeEventView, other_fighter_170) == 0x170 ? 1 : -1];
typedef char UdongeEventView_event_counter_offset[
    offsetof(UdongeEventView, event_counter_730) == 0x730 ? 1 : -1];
typedef char UdongeEventView_event_flag_offset[
    offsetof(UdongeEventView, event_flag_759) == 0x759 ? 1 : -1];

unsigned char UdongeEventView::handle_event_bridge(int event_code)
{
    switch (event_code) {
    case 1:
        x_ec = 100.0f;
        event_counter_730 = 640;
        event_timer_732 = 0;
    case 2:
    case 11:
        g_shared_event_state.set_target_20_enabled_2c(1, 640.0f);
        g_shared_event_state.set_target_24_enabled_2d(1, 0.0f);
        g_shared_event_state.set_target_28_enabled_2e(1, 1.0f);
        g_shared_event_state.synchronize_targets();
        return false;

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

    case 8: {
        set_action(139);
        float copied_words[3] = {0.0f, 0.0f, 0.0f};
        spawn_owned_object_via_manager(
            999, x_ec, y_f0, 1, 1,
            reinterpret_cast<int>(copied_words), 3);
        return false;
    }

    case 9:
        x_ec = 100.0f;
        y_f0 = 2.0f;
        facing_104 = 1;
        velocity_x_f4 = 6.0f;
        velocity_y_f8 = 15.0f;
        acceleration_y_100 = 0.5f;
        set_action(797);
        return false;

    case 50:
        x_ec = 280.0f;
        y_f0 = 0.0f;
        set_action(797);
        return false;

    case 101:
        x_ec = 1000.0f;
        y_f0 = 0.0f;
        set_action(798);
        return false;

    case 102:
    case 106:
    case 111:
    case 121:
        return state_13c != 700;

    case 103:
        event_subobject_130.trigger_global_effect(11);
        event_flag_759 = 1;
        event_value_75c = 0;
        event_value_760 = 180;
        return false;

    case 104:
        event_subobject_130.trigger_global_effect(0);
        return false;

    case 105: {
        UdongeEventView *const other = other_fighter_170;
        y_f0 = 960.0f;
        x_ec = other->x_ec + 250 * static_cast<signed char>(other->facing_104);
        facing_104 = static_cast<signed char>(-other->facing_104);
        set_action(795);
        return false;
    }

    case 110:
        goto action_796;

    case 113:
        event_subobject_130.trigger_global_effect(11);
        return false;

    case 120:
        facing_104 = 1;
        x_ec = 100.0f;
        y_f0 = 0.0f;
        velocity_x_f4 = 13.0f;
        velocity_y_f8 = 15.0f;
        acceleration_y_100 = 0.5f;
    action_796:
        set_action(796);
        return false;
    }
    return true;
}

} // namespace th105
