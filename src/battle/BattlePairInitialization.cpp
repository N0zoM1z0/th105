#include "BattleController.hpp"
#include "Collision.hpp"

#include <cstring>

namespace th105 {

typedef void (__thiscall *FighterVslot44)(Fighter *fighter);

struct FighterPhaseContextPairView {
    Fighter *get_slot_character_463270(unsigned slot);
    void finish_slot_464240(int slot);
};

struct GlobalBattlePairStateView {
    void initialize_pair_metadata_426440(
        float *first_a,
        float *first_b,
        float *second_a,
        float *second_b);
};

struct PairPostResetView {
    void reset_pair_state_4694e0();
};

struct PairInputStateView {
    void reset_pair_input_427150();
};

struct PairEmbeddedModeView {
    void select_pair_mode_434780(int mode, unsigned char publish);
};

struct PairRendererView;
typedef void (__thiscall *PairRendererCallback)(PairRendererView *renderer);

struct PairRendererView {
    PairRendererCallback *vtable_00;
};

extern int g_pair_state;
extern float g_stage_surface_heights[1280];

__forceinline FighterPhaseContextPairView *fighter_phase_context_for_pair()
{
    return *reinterpret_cast<FighterPhaseContextPairView **>(0x006fbc9c);
}

void BattleController::initialize_battle_fighter_pair_46a490()
{
    int zero = 0;

    fighter_0c =
        fighter_phase_context_for_pair()->get_slot_character_463270(zero);
    fighter_10 =
        fighter_phase_context_for_pair()->get_slot_character_463270(1);

    fighter_0c->reset_for_roster_45e040(fighter_10);
    fighter_10->reset_for_roster_45e040(fighter_0c);

    reinterpret_cast<FighterVslot44>(
        (*reinterpret_cast<void ***>(fighter_0c))[17])(fighter_0c);
    reinterpret_cast<FighterVslot44>(
        (*reinterpret_cast<void ***>(fighter_10))[17])(fighter_10);

    fighter_phase_context_for_pair()->finish_slot_464240(zero);
    fighter_phase_context_for_pair()->finish_slot_464240(1);

    reinterpret_cast<GlobalBattlePairStateView *>(0x006fbcc0)
        ->initialize_pair_metadata_426440(
            &fighter_0c->x_ec,
            &fighter_0c->y_f0,
            &fighter_10->x_ec,
            &fighter_10->y_f0);

    (*reinterpret_cast<EffectSink **>(0x006fbcb0))->unknown_10();
    reinterpret_cast<CollisionContext *>(this)->reset_collision_extents();

    result_84 = zero;
    g_pair_state = zero;
    frame_counter_04 = zero;
    *reinterpret_cast<int *>(unknown_08) = zero;
    std::memset(
        g_stage_surface_heights,
        zero,
        sizeof(g_stage_surface_heights));

    PairRendererView *renderer =
        *reinterpret_cast<PairRendererView **>(0x006fbca8);
    renderer->vtable_00[3](renderer);

    (*reinterpret_cast<PairPostResetView **>(0x006fbcac))
        ->reset_pair_state_4694e0();

    *reinterpret_cast<unsigned short *>(0x006fa88c) =
        static_cast<unsigned short>(zero);
    reinterpret_cast<PairEmbeddedModeView *>(&frame_counter_04)
        ->select_pair_mode_434780(16, 1);

    (*reinterpret_cast<PairInputStateView **>(0x006fa888))
        ->reset_pair_input_427150();

    result_84 = zero;
    dispatch_round_phase_34(zero);
}

} // namespace th105
