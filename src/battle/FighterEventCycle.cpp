#include "Collision.hpp"

namespace th105 {

extern int g_pair_mode_primary;
extern int g_secondary_event_effect_id;

void Fighter::advance_secondary_event_effect_cycle()
{
    if (g_pair_mode_primary != 16)
        return;

    switch (g_secondary_event_effect_id) {
    case 0: event_subobject_130.trigger_secondary_event_effect(1); return;
    case 1: event_subobject_130.trigger_secondary_event_effect(2); return;
    case 2: event_subobject_130.trigger_secondary_event_effect(3); return;
    case 3: event_subobject_130.trigger_secondary_event_effect(4); return;
    case 4: event_subobject_130.trigger_secondary_event_effect(5); return;
    case 5: event_subobject_130.trigger_secondary_event_effect(6); return;
    case 6: event_subobject_130.trigger_secondary_event_effect(7); return;
    case 7: event_subobject_130.trigger_secondary_event_effect(8); return;
    case 8: event_subobject_130.trigger_secondary_event_effect(9); return;
    case 9: event_subobject_130.trigger_secondary_event_effect(10); return;
    case 10: event_subobject_130.trigger_secondary_event_effect(11); return;
    case 11: event_subobject_130.trigger_secondary_event_effect(12); return;
    case 12: event_subobject_130.trigger_secondary_event_effect(13); return;
    case 13: event_subobject_130.trigger_secondary_event_effect(14); return;
    case 14: event_subobject_130.trigger_secondary_event_effect(0); return;
    default: return;
    }
}

} // namespace th105
