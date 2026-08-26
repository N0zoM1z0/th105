#include "BattleController.hpp"
#include "FighterPhaseContextRuntime.hpp"

namespace th105 {

struct StorySceneRendererView {
    virtual void slot_00();
    virtual int apply_match_setup(MatchSetup *setup);
    virtual void finalize_loading();
};

struct StoryBattleObjectManagerView {
    void reset_battle_render_state_and_signal_465f70();
};

struct StoryFighterPhaseContextView {
    void reset_all_slots_and_signal_464f90();
    void initialize_slot_464270(
        unsigned slot, MatchSetup::Side *side, bool asynchronous);
};

extern StorySceneRendererView *g_scene_renderer;
extern StoryBattleObjectManagerView *g_battle_object_manager;
extern StoryFighterPhaseContextView *g_fighter_phase_context;

int __cdecl apply_story_match_setup(MatchSetup *setup)
{
    return g_scene_renderer->apply_match_setup(setup);
}

void __cdecl initialize_story_slot_two()
{
    MatchSetup::Side *side = &get_match_setup()->sides_08[1];
    if (g_battle_phase_block != 0)
        g_battle_phase_block->parse_scenario_event_row_4591d0(side);
    g_fighter_phase_context->initialize_slot_464270(2, side, false);
}

void __cdecl reset_story_loading_runtime()
{
    g_battle_object_manager->reset_battle_render_state_and_signal_465f70();
    g_fighter_phase_context->reset_all_slots_and_signal_464f90();
    g_scene_renderer->finalize_loading();
}

// The target constructs the 0xA8 Story manager inline at its allocation site:
// the base constructor stays out of line and the implicit derived constructor
// publishes the Story vtable.  Keep this narrow lifetime view local so the
// larger battle-manager headers do not acquire speculative trailing layout.
struct BattleManagerBaseBootstrap {
    virtual int slot_00();
    unsigned char storage_004[0xA4];
    BattleManagerBaseBootstrap();
};

struct BattleManagerStoryBootstrap : BattleManagerBaseBootstrap {
    virtual int slot_00();
};

struct InfoManagerStoryBootstrap {
    unsigned char storage_000[0x610];
    InfoManagerStoryBootstrap();
};

extern BattleManagerStoryBootstrap *g_story_battle_manager;
extern InfoManagerStoryBootstrap *g_story_info_manager;

void __cdecl initialize_story_managers()
{
    g_story_battle_manager = new BattleManagerStoryBootstrap;
    g_story_info_manager = new InfoManagerStoryBootstrap;
}

} // namespace th105
