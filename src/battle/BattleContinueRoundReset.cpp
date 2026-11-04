#include "ui/ContinueOwnerRuntime.hpp"
#include "battle/BattleController.hpp"
#include "battle/Collision.hpp"
#include "battle/ScenarioData.hpp"
#include "battle/ScenarioTransition.hpp"
#include "battle/SharedEventState.hpp"
#include "assets/String28.hpp"
#include <cstring>
#include <list>

namespace th105 {
struct RoundFighterVirtual {
    virtual void slot00();
    virtual void slot04();
    virtual void slot08();
    virtual void slot0c();
    virtual void slot10();
    virtual void slot14();
    virtual void slot18();
    virtual void slot1c();
    virtual void slot20();
    virtual void slot24();
    virtual void slot28();
    virtual void slot2c();
    virtual void slot30();
    virtual void slot34();
    virtual void slot38();
    virtual void slot3c();
    virtual void slot40();
    virtual void prepare44();
};
struct RoundPostVirtual {
    virtual void slot00();
    virtual void slot04();
    virtual void slot08();
    virtual void reset0c();
};
struct BattlePhaseBlockRoundView {
    unsigned char prefix[0x68];
    CScenarioData scenario_068;
    void *selected_input_58c;
    int selected_column_590;
    signed char page_index_594;
    signed char story_character_595;
    unsigned char reserved_596[2];
    std::list<int> source_598;
    std::list<int> destination_5a4;
};
typedef char RoundPhaseScenario_offset[offsetof(BattlePhaseBlockRoundView,scenario_068)==0x68?1:-1];
typedef char RoundPhaseLists_source[offsetof(BattlePhaseBlockRoundView,source_598)==0x598?1:-1];
typedef char RoundPhaseLists_dest[offsetof(BattlePhaseBlockRoundView,destination_5a4)==0x5a4?1:-1];
extern int g_pair_state;
extern unsigned char g_round_counter;
extern float g_stage_surface_heights[1280];
extern unsigned char g_global_battle_setup_state[];
void __fastcall update_global_battle_setup_state_second(void *);
void __cdecl set_session_setup_option(unsigned);
void ContinueOwnerRuntimeView::reset_battle_round_471180()
{
    set_session_setup_option(0);
    reinterpret_cast<RoundFighterVirtual *>(fighter_0c)->prepare44();
    reinterpret_cast<RoundFighterVirtual *>(fighter_10)->prepare44();
    update_global_battle_setup_state_second(g_global_battle_setup_state);
    g_shared_event_state.synchronize_targets();
    BattlePhaseBlockRoundView *phase =
        reinterpret_cast<BattlePhaseBlockRoundView *>(g_battle_phase_block);
    if (&phase->destination_5a4 != &phase->source_598)
        phase->destination_5a4.assign(
            phase->source_598.begin(), phase->source_598.end());
    phase->scenario_068.reset_runtime_state();
    g_effect_sink->unknown_10();
    reinterpret_cast<CollisionContext *>(this)->reset_collision_extents();
    end_pending_84 = 0;
    g_pair_state = 0;
    frame_04 = 0;
    field_08 = 0;
    g_round_counter = 0;
    std::memset(g_stage_surface_heights, 0, sizeof(g_stage_surface_heights));
    post_8c->reset0c();
    fighter_0c->terminal_delay_4e8 = 3;
    if (reinterpret_cast<ScenarioTransitionView *>(g_battle_phase_block)
            ->dispatch_owned_string_458e80(String28("Continue")))
        while (g_battle_phase_block->run_scenario_step()) {}
    dispatch34(1);
}

} // namespace th105
