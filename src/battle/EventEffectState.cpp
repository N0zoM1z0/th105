#include "EventEffectState.hpp"

namespace th105 {

int EventEffectStateView::set_event_id(int event_id)
{
    if (current_event_id == event_id)
        return event_id;
    current_event_id = event_id;
    return publish_stage_state(g_battle_transition_mode);
}

} // namespace th105
