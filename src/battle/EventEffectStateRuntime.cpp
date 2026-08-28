#include "EffectManager.hpp"
#include "EffectSprite.hpp"
#include "EventEffectState.hpp"
#include "ui/Title.hpp"

#include <deque>
#include <map>
#include <vector>

namespace th105 {

struct EventEffectStateRuntimeView {
    unsigned current_event_id_00;
    signed char current_stage_04;
    unsigned char reserved_05[3];
    std::vector<unsigned> resources_08;
    std::vector<CSpriteEx> sprites_18;
    std::deque<BackgroundRenderEntry> background_entries_28;
    std::map<signed char, std::vector<unsigned char> > stage_rows_3c;
    CEffectManager<WeatherEffectObject> emitter_48;
    float runtime_x_dc;
    float runtime_y_e0;
    float runtime_z_e4;

    void publish_stage_state_469d50(signed char state);
    void prepare_shutdown_469ec0();
    void reset_runtime_state_469f40();
};

typedef char EventEffectStateRuntimeView_size_must_be_0xe8[
    sizeof(EventEffectStateRuntimeView) == 0xe8 ? 1 : -1];

extern int g_event_runtime_state;
extern int g_event_runtime_zero;

void EventEffectStateRuntimeView::publish_stage_state_469d50(signed char state)
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

void EventEffectStateRuntimeView::prepare_shutdown_469ec0()
{
    stage_rows_3c.clear();
    for (unsigned i = 0; i < resources_08.size(); ++i)
        g_title_resource_manager.release_title_resource_handle(resources_08[i]);
    reinterpret_cast<EffectEmitterSubobject *>(&emitter_48)->slot_08();
}

void EventEffectStateRuntimeView::reset_runtime_state_469f40()
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
