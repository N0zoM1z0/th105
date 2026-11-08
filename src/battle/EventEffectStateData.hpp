#pragma once

#include "battle/EffectManager.hpp"
#include "battle/EffectSprite.hpp"
#include "battle/EventEffectState.hpp"
#include <deque>
#include <map>
#include <vector>

namespace th105 {
// The resource-owning event/effect state. Construction leaves the coordinates
// untouched; the runtime reset initializes them after loading resources.
struct EventEffectStateData {
    unsigned current_event_id_00;
    signed char current_stage_04;
    unsigned char reserved_05[3];
    std::vector<unsigned> resources_08;
    std::vector<CEffectSprite> sprites_18;
    std::deque<BackgroundRenderEntry> background_entries_28;
    std::map<signed char, std::vector<unsigned char> > stage_rows_3c;
    CEffectManager<WeatherEffectObject> emitter_48;
    float runtime_x_dc;
    float runtime_y_e0;
    float runtime_z_e4;

    EventEffectStateData();
    ~EventEffectStateData();
    void set_event_id(int event_id);
    void initialize_effect_runtime();
    void publish_stage_state_469d50(signed char state);
    void prepare_shutdown_469ec0();
    void reset_runtime_state_469f40();
};
}
