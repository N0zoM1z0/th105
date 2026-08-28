#include <new>

namespace th105 {

struct EffectSinkTeardownView {
    virtual ~EffectSinkTeardownView();
    virtual void load_effect_resource(const char *, unsigned);
    virtual void shutdown();
};
struct EventEffectStateTeardownView {
    ~EventEffectStateTeardownView();
    void prepare_shutdown();
};
struct BattleObjectManagerTeardownView { ~BattleObjectManagerTeardownView(); };
struct FighterPhaseContextTeardownView { ~FighterPhaseContextTeardownView(); };

extern EffectSinkTeardownView *g_effect_sink_teardown;
extern EventEffectStateTeardownView *g_event_effect_state_teardown;
extern BattleObjectManagerTeardownView *g_battle_object_manager_teardown;
extern FighterPhaseContextTeardownView *g_fighter_phase_context_teardown;
extern void *g_battle_input_gate_teardown;

void __cdecl destroy_scene_managers();

void __cdecl destroy_shared_battle_runtime()
{
    destroy_scene_managers();
    g_event_effect_state_teardown->prepare_shutdown();
    g_effect_sink_teardown->shutdown();
    operator delete(g_battle_input_gate_teardown);
    delete g_effect_sink_teardown;
    delete g_event_effect_state_teardown;
    delete g_battle_object_manager_teardown;
    delete g_fighter_phase_context_teardown;
}

} // namespace th105
