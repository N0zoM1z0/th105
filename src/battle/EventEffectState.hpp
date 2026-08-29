#pragma once

#include "InfoEffectEmitter.hpp"

#include <deque>

class CSpriteEx;

namespace th105 {

// Narrow shared battle/event state controller contract. Current target-backed
// callers establish the current event id at +0 and the two transition methods.
struct BackgroundRenderEntry {
    unsigned char alpha;
    unsigned char reserved_01[3];
    CSpriteEx *sprite;
};

struct EventEffectStateView {
    int current_event_id;
    unsigned char reserved_04[0x24];
    std::deque<BackgroundRenderEntry> background_entries_28;
    unsigned char reserved_3c[0x0c];
    EffectEmitterSubobject emitter_48;

    int publish_stage_state(int state);
    int set_event_id(int event_id);
    int emit_effect(int effect_id, float x, float y, int flag_a, int flag_b);
    int dispatch_emitter_state(int state);
    void render_background_effects();
    void update_background_entries_469b70();

    __forceinline float &background_target_x_dc()
    { return *reinterpret_cast<float *>(reinterpret_cast<unsigned char *>(this) + 0xdc); }
    __forceinline float &background_target_y_e0()
    { return *reinterpret_cast<float *>(reinterpret_cast<unsigned char *>(this) + 0xe0); }
    __forceinline float &background_target_z_e4()
    { return *reinterpret_cast<float *>(reinterpret_cast<unsigned char *>(this) + 0xe4); }
};

typedef char BackgroundRenderEntry_size_must_be_8[
    sizeof(BackgroundRenderEntry) == 8 ? 1 : -1];

extern EventEffectStateView *g_event_effect_state;
extern unsigned char g_battle_transition_mode;

} // namespace th105
