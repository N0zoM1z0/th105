#pragma once

namespace th105 {

struct InputStateTable {
    unsigned entries[256];

    void set_input_state_table_entry(unsigned char index, bool state);
};

struct CInputManager {
    virtual ~CInputManager();

    unsigned char unknown_04[0x1c];
    unsigned char raw_keyboard_state[256];

    bool is_raw_key_down(unsigned char scan_code) const;
};

} // namespace th105
