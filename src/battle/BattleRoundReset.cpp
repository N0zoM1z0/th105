#include "battle/BattleController.hpp"
#include "battle/Collision.hpp"
#include "battle/ScenarioTransition.hpp"
#include "assets/String28.hpp"

#include <cstring>
#include <list>

namespace th105 {

void __cdecl set_session_setup_option(unsigned option);

typedef void (__thiscall *FighterVslot44)(Fighter *fighter);

struct GlobalBattleResetStateView {
    void update_second_425f10();
    void synchronize_426410();
};

struct BattlePhaseResetView {
    unsigned char unknown_000[0x68];
    struct HudState {
        void reset_456870();
    } hud_068;
};

struct BattlePhaseListsView {
    unsigned char unknown_000[0x598];
    std::list<void *> source_598;
    std::list<void *> destination_5a4;
};

struct EffectResetView {
    virtual void unknown_00();
    virtual void unknown_04();
    virtual void unknown_08();
    virtual void unknown_0c();
    virtual void reset_10();
};

struct PostSequenceResetView {
    virtual void unknown_00();
    virtual void unknown_04();
    virtual void unknown_08();
    virtual void reset_0c();
};

struct BattlePhaseRunView {
    bool run_458cc0();
};

static __forceinline GlobalBattleResetStateView *global_reset_state()
{
    return reinterpret_cast<GlobalBattleResetStateView *>(0x006e6260);
}

static __forceinline EffectResetView *effect_reset_sink()
{
    return *reinterpret_cast<EffectResetView **>(0x006e6250);
}

int BattleController::reset_battle_round_470780()
{
    set_session_setup_option(0);

    reinterpret_cast<FighterVslot44>(
        (*reinterpret_cast<void ***>(fighter_0c))[17])(fighter_0c);
    reinterpret_cast<FighterVslot44>(
        (*reinterpret_cast<void ***>(fighter_10))[17])(fighter_10);

    global_reset_state()->update_second_425f10();
    global_reset_state()->synchronize_426410();

    BattlePhaseListsView *block =
        reinterpret_cast<BattlePhaseListsView *>(g_battle_phase_block);
    if (&block->destination_5a4 != &block->source_598) {
        block->destination_5a4.assign(
            block->source_598.begin(), block->source_598.end());
    }

    reinterpret_cast<BattlePhaseResetView *>(block)->hud_068.reset_456870();
    effect_reset_sink()->reset_10();

    reinterpret_cast<CollisionContext *>(this)->reset_collision_extents();
    result_84 = 0;
    *reinterpret_cast<int *>(0x006e6238) = 0;
    frame_counter_04 = 0;
    *reinterpret_cast<int *>(unknown_08) = 0;
    *reinterpret_cast<unsigned char *>(0x006e4e2e) = 0;
    std::memset(reinterpret_cast<void *>(0x006e4e38), 0, 0x1400);

    reinterpret_cast<PostSequenceResetView *>(post_sequence_context_8c)
        ->reset_0c();
    fighter_0c->terminal_delay_4e8 = 3;

    if (reinterpret_cast<ScenarioTransitionView *>(g_battle_phase_block)
            ->dispatch_owned_string_458e80(String28("Continue"))) {
        while (reinterpret_cast<BattlePhaseRunView *>(g_battle_phase_block)
                   ->run_458cc0()) {
        }
    }
    typedef int (__thiscall *DispatchRoundPhase)(
        BattleController *controller,
        int phase);
    return reinterpret_cast<DispatchRoundPhase>(
        (*reinterpret_cast<void ***>(this))[13])(this, 1);
}

} // namespace th105
