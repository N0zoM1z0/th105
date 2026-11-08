#pragma once

#include <deque>

class CSpriteEx;

namespace th105 {

// Entry in the event state background-render deque.
struct BackgroundRenderEntry {
    unsigned char alpha;
    unsigned char reserved_01[3];
    CSpriteEx *sprite;
};
typedef char BackgroundRenderEntry_size_must_be_8[sizeof(BackgroundRenderEntry) == 8 ? 1 : -1];

struct EventEffectStateData;
extern EventEffectStateData *g_event_effect_state;
extern unsigned char g_battle_transition_mode;

} // namespace th105
