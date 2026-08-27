#include "battle/BattleObjectManagerRuntime.hpp"
#include "EventEffectState.hpp"

namespace th105 {

struct BattleAudioSetupView {
    void set_stage_music_433860(int stage, int value);
};

void BattleAudioSetupView::set_stage_music_433860(int stage, int value)
{
    g_battle_object_manager->publish_stage(stage, value, true);
    g_event_effect_state->publish_stage_state(stage);
}

} // namespace th105
