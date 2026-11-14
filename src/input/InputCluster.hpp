#pragma once

#include "InputManager.hpp"

#include <deque>
#include <vector>

class CInputManagerCluster : public CInputManager {
public:
    std::deque<CInputManager *> sources;
    signed char active_source;

    signed char get_active_source() const;
    virtual void update_player_input_counters_from_raw();
};

typedef char CInputManagerCluster_size_must_be_0x78[
    sizeof(CInputManagerCluster) == 0x78 ? 1 : -1];

namespace th105 {

using ::CInputManagerCluster;

struct InputStateTableStorage {
    int key_counters[256];
    std::vector<unsigned char> tracked_keys;
    unsigned char modifier_states[3];

    InputStateTableStorage();
    void reset_input_state_table();
    void update_input_state_table();
    void add_tracked_key(unsigned char key);
    bool is_initial_press(
        unsigned char key,
        bool require_modifier_0,
        bool require_modifier_1,
        bool require_modifier_2) const;
};

} // namespace th105
