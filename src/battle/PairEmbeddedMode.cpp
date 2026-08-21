#include "PairEmbeddedMode.hpp"
#include "EventSubobject130.hpp"
#include "InfoEffectEmitter.hpp"

namespace th105 {

extern int g_secondary_event_effect_id;
extern int g_pair_mode_primary;
void __cdecl dispatch_indexed_event(unsigned index);
int __cdecl lookup_event_effect_record(int event_id);
int __cdecl selector_random_roll(int limit);

void PairEmbeddedModeView::select_pair_mode_434780(
    int mode, unsigned char publish)
{
    if (publish)
        reinterpret_cast<EventSubobject130 *>(this)->trigger_global_effect(mode);

    if (mode != 16) {
        dispatch_indexed_event(0x35);
        g_info_effect_emitter->emit_effect(
            lookup_event_effect_record(mode) + 2,
            320.0f,
            32.0f,
            1,
            1);
    }

    g_secondary_event_effect_id = mode;
    g_pair_mode_primary = mode;
    if (mode == 14)
        g_pair_mode_primary = selector_random_roll(14);
}

} // namespace th105
