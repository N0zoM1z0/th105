namespace th105 {

struct BattleObjectManagerStageView {
    int publish_stage(int stage, int value, bool notify);
};
struct EventEffectStateView {
    int publish_stage_state(int stage);
};
struct BattleAudioSetupView {
    void set_stage_music_433860(int stage, int value);
};
extern BattleObjectManagerStageView *g_battle_object_manager_stage;
extern EventEffectStateView *g_event_effect_state;

void BattleAudioSetupView::set_stage_music_433860(int stage, int value)
{
    g_battle_object_manager_stage->publish_stage(stage, value, true);
    g_event_effect_state->publish_stage_state(stage);
}

}
