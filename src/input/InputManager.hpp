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

struct CInputManager {
    virtual ~CInputManager();
    virtual void update_player_input_counters_from_raw();

    InputBindings bindings;
    union {
        HoldCounters hold;
        int counters[10];
    };

    void reset_counters();
};

struct CInputManagerEx : CInputManager {
    unsigned short injected_mask;
    unsigned short resolved_mask;
    bool use_injected_input;
    unsigned char reserved_65[3];

    virtual void build_player_logical_input_mask();
};

struct RawGamepadState {
    int x;
    int y;
    unsigned char reserved_08[0x28];
    unsigned char buttons[32];
};

struct DirectInputBackend {
    void *window_handle;
    void *direct_input;
    unsigned char unknown_08[0x18];
    unsigned char raw_keyboard_state[256];
    int gamepad_count;
    std::vector<RawGamepadState> gamepad_states;

    bool is_raw_key_down(unsigned char scan_code) const;
    RawGamepadState *get_gamepad_state(int index);
};

extern DirectInputBackend g_direct_input_backend;

} // namespace th105
