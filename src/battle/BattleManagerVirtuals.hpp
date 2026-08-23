#pragma once

#include "Collision.hpp"
#include <stddef.h>

namespace th105 {

struct BattleManagerPhaseObject {
    virtual void slot_00();
    virtual void slot_04();
    virtual signed char status_08();
    virtual void run_phase_tail_0c();
};

// Narrow current-target layout shared by CBattleManager and CBattleManagerArcade.
// Current constructors publish vtables 0x006C1504 and 0x006C154C; both tables
// share the nine methods implemented in BattleManagerVirtuals.cpp.
struct MatchSetup;

struct CBattleManager {
    virtual void slot_00();
    virtual void prepare_battle_setup_472110(MatchSetup *setup);
    virtual void slot_08();
    virtual int dispatch_battle_state_frame_472b20();
    virtual int run_pipeline_and_transition_472d80();
    virtual int run_reset_pipeline_472dc0();
    virtual int run_full_pipeline_471630();
    virtual int run_120_frame_pipeline_472e10();
    virtual int run_180_frame_pipeline_472ea0();
    virtual int run_info_phase_pipeline_472f10();
    virtual int constant_one_471920();
    virtual void mark_terminal_pending_if_state_not_3_472490(Fighter *fighter);
    virtual void post_pipeline_slot_30();
    virtual void transition_slot_34(int value);
    virtual void update_phase_object_if_needed_4724b0();
    virtual int update_event_effect_timer_472a70();
    virtual void pre_reset_slot_40();

    unsigned frame_counter_04;
    int pending_08;
    Fighter *fighter_0c;
    Fighter *fighter_10;
    unsigned char reserved_14[0x74];
    int phase_88;
    BattleManagerPhaseObject phase_object_8c;

    // Current call sites preserve ECX=this for these linked helpers even where
    // the helper body itself does not consume ECX. These are ABI views only;
    // they do not claim separate source ownership for the target callees.
    void run_global_action_owned_phase_view();
    void run_collision_phase_46cca0();
    void run_global_position_status_timer_phase_view();
    void run_intermediate_phase_46dff0();
    void run_shared_pre_phase_46bf00();
    void run_transition_phase_5_4724e0();

    __forceinline unsigned char &transition_state_5b0()
    {
        return *(reinterpret_cast<unsigned char *>(this) + 0x5b0);
    }
};

typedef char CBattleManager_phase_offset_must_be_0x88[
    offsetof(CBattleManager, phase_88) == 0x88 ? 1 : -1];
typedef char CBattleManager_phase_object_offset_must_be_0x8c[
    offsetof(CBattleManager, phase_object_8c) == 0x8c ? 1 : -1];

} // namespace th105
