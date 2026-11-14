#pragma once

#include <vector>

namespace th105 {

struct InputStateTable {
    unsigned entries[256];

    void set_input_state_table_entry(unsigned char index, bool state);
};

struct InputBindings {
    signed char source_id;
    unsigned char reserved_01[3];
    int up;
    int down;
    int left;
    int right;
    int buttons[8];
};

struct HoldCounters {
    int horizontal;
    int vertical;
    int buttons[8];
};

} // namespace th105

// The executable RTTI identifies global classes, shared by every owner.
class CInputManager {
public:
    CInputManager();
    virtual ~CInputManager();
    virtual void update_player_input_counters_from_raw();

    th105::InputBindings bindings;
    union {
        th105::HoldCounters hold;
        int counters[10];
    };

    void reset_counters();
};

class CInputManagerEx : public CInputManager {
public:
    unsigned short injected_mask;
    unsigned short resolved_mask;
    bool use_injected_input;
    unsigned char reserved_65[3];

    // Native slot +4 overrides the base update; there is no third slot.
    virtual void update_player_input_counters_from_raw();
};

typedef char CInputManager_size_must_be_0x60[
    sizeof(CInputManager) == 0x60 ? 1 : -1];
typedef char CInputManagerEx_size_must_be_0x68[
    sizeof(CInputManagerEx) == 0x68 ? 1 : -1];

namespace th105 {

using ::CInputManager;
using ::CInputManagerEx;

struct RawGamepadState {
    int x;
    int y;
    unsigned char reserved_08[0x28];
    unsigned char buttons[32];
};

struct DirectInputBackend {
    void *window_handle;
    void *direct_input;
    void *keyboard_device;
    void *mouse_device;
    std::vector<void *> gamepad_devices;
    unsigned char raw_keyboard_state[256];
    int gamepad_count;
    std::vector<RawGamepadState> gamepad_states;
    std::vector<int> gamepad_button_counts;

    bool is_raw_key_down(unsigned char scan_code) const;
    RawGamepadState *get_gamepad_state(int index);
    int get_gamepad_button_count(int index);
};

extern DirectInputBackend g_direct_input_backend;
void poll_direct_input_gamepads();

} // namespace th105
