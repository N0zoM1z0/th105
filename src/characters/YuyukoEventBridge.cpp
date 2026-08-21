#include <stddef.h>

// Narrow 1.06a source view for Yuyuko's event bridge. Only fields, access widths,
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
class YuyukoEventView {
public:
    virtual ~YuyukoEventView();
    virtual void virtual_slot_04();
    virtual void set_action(int action_id);
    virtual void set_sequence(int sequence_id);
    unsigned char handle_event_bridge(int event_code);
    void zero_velocity_acceleration();
    int spawn_owned_object_via_manager(int object_id, float x, float y,
        int direction, int arg5, int arg6, int arg7);
public:
    unsigned char unknown_004[0xe8];
    float x_ec; float y_f0; float velocity_x_f4; float velocity_y_f8;
    float acceleration_x_fc; float acceleration_y_100;
    signed char facing_104;
    unsigned char unknown_105[0x2b];
    EventSubobject130 event_subobject_130;
    short state_13c;
    unsigned char unknown_13e[0x32];
    YuyukoEventView *other_fighter_170;
    unsigned char unknown_174[0x5bc];
    short event_counter_730;
    short event_timer_732;
    unsigned char unknown_734[0x25];
    unsigned char event_flag_759;
    unsigned char unknown_75a[2];
    int event_value_75c;
    int event_value_760;
};
typedef char Yuyuko_state_off[offsetof(YuyukoEventView,state_13c)==0x13c?1:-1];
typedef char Yuyuko_other_off[offsetof(YuyukoEventView,other_fighter_170)==0x170?1:-1];
typedef char Yuyuko_event_off[offsetof(YuyukoEventView,event_counter_730)==0x730?1:-1];

unsigned char YuyukoEventView::handle_event_bridge(int event_code)
{
    unsigned char result;
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
        result = 0;
        break;
    case 3:
        g_shared_event_state.set_target_20_enabled_2c(0, 640.0f);
        g_shared_event_state.set_target_24_enabled_2d(0, 0.0f);
        g_shared_event_state.set_target_28_enabled_2e(0, 1.0f);
        result = 0;
        break;
    case 4:
        g_shared_event_state.set_target_20_enabled_2c(1, 640.0f);
        g_shared_event_state.set_target_24_enabled_2d(1, 0.0f);
        g_shared_event_state.set_target_28_enabled_2e(1, 1.0f);
        result = 0;
        break;
    case 5:
        x_ec = 0.0f; y_f0 = 0.0f;
        zero_velocity_acceleration();
        set_action(0);
        result = 0;
        break;
    case 6:
        set_action(790); set_sequence(2);
        x_ec = 480.0f; y_f0 = 800.0f;
        velocity_x_f4 = 0.0f; velocity_y_f8 = 0.0f;
        acceleration_y_100 = 0.25f;
        result = 0;
        break;
    case 7:
    case 51:
        result = state_13c != 0;
        break;
    case 8: {
        set_action(139);
        float copied_words[3] = {0.0f,0.0f,0.0f};
        spawn_owned_object_via_manager(999,x_ec,y_f0,1,1,
            reinterpret_cast<int>(copied_words),3);
        result = 0;
        break;
    }
    case 9:
        set_action(795);
        x_ec = 70.0f; y_f0 = 240.0f;
        zero_velocity_acceleration();
        velocity_x_f4 = 15.0f; velocity_y_f8 = 0.0f;
        acceleration_y_100 = 0.5f;
        result = 0;
        break;
    case 50:
        x_ec = 480.0f; y_f0 = 960.0f;
        acceleration_y_100 = 0.1f;
        set_action(797);
        result = 0;
        break;
    case 101:
        x_ec = 800.0f; y_f0 = 960.0f;
        acceleration_y_100 = 0.1f;
        set_action(798);
        result = 0;
        break;
    case 102:
    case 106:
    case 111:
    case 121:
        result = state_13c != 700;
        break;
    case 103:
        event_subobject_130.trigger_global_effect(7);
        event_flag_759 = 1;
        event_value_75c = 0;
        event_value_760 = 180;
        result = 0;
        break;
    case 105: {
        YuyukoEventView *const other = other_fighter_170;
        y_f0 = 960.0f;
        x_ec = other->x_ec + 250 * static_cast<signed char>(other->facing_104);
        facing_104 = static_cast<signed char>(-other->facing_104);
        set_action(795);
        result = 0;
        break;
    }
    case 110:
        set_action(796);
        result = 0;
        break;
    case 113:
        event_subobject_130.trigger_global_effect(7);
        result = 0;
        break;
    case 120:
        set_action(796);
        x_ec = 100.0f;
        facing_104 = 1;
        y_f0 = 0.0f;
        velocity_x_f4 = 7.0f;
        velocity_y_f8 = 15.0f;
        acceleration_y_100 = 0.30000001f;
        result = 0;
        break;
    default:
        result = 1;
        break;
    }
    return result;
}
} // namespace th105
