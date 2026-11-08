#include "battle/EventEffectStateData.hpp"
#include "EffectManager.hpp"
#include "EffectSprite.hpp"
#include "EventEffectState.hpp"
#include "ui/Title.hpp"

#include <deque>
#include <map>
#include <vector>

namespace th105 {

extern int g_event_runtime_state;
extern int g_event_runtime_zero;

void EventEffectStateData::publish_stage_state_469d50(signed char state)
{
    signed char next =
        stage_rows_3c.find(state)->second[current_event_id_00];
    if (next != current_stage_04) {
        current_stage_04 = next;
        BackgroundRenderEntry entry;
        entry.alpha = 0xff;
        if (next >= 0)
            entry.sprite = &sprites_18[static_cast<unsigned>(next)];
        else
            entry.sprite = 0;
        background_entries_28.push_back(entry);
    }
}

void EventEffectStateData::prepare_shutdown_469ec0()
{
    stage_rows_3c.clear();
    for (unsigned i = 0; i < resources_08.size(); ++i)
        g_title_resource_manager.release_title_resource_handle(resources_08[i]);
    reinterpret_cast<EffectEmitterSubobject *>(&emitter_48)->slot_08();
}

void EventEffectStateData::reset_runtime_state_469f40()
{
    emitter_48.release_all_tracked_objects();
    current_stage_04 = -2;
    current_event_id_00 = 16;
    g_event_runtime_state = 16;
    g_event_runtime_zero = 0;
    background_entries_28.clear();
    publish_stage_state_469d50(g_battle_transition_mode);
    runtime_x_dc = 0.0f;
    runtime_y_e0 = 0.0f;
    runtime_z_e4 = 0.0f;
}

} // namespace th105
