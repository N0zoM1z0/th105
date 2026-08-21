#pragma once

namespace th105 {

// Narrow shared battle/event state controller contract. Current target-backed
// callers establish the current event id at +0 and the two transition methods.
struct EventEffectStateView {
    int current_event_id;

    int publish_stage_state(int state);
    int set_event_id(int event_id);
};

extern EventEffectStateView *g_event_effect_state;
extern unsigned char g_battle_transition_mode;

} // namespace th105
