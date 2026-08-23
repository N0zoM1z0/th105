#pragma once

#include "Collision.hpp"

#include <stddef.h>

namespace th105 {

struct StoryInfoPhaseCounterView {
    unsigned char reserved_000[0x494];
    int counter_494;
};

// Current RTTI identifies the vtable at 0x006C1374 as CBattleManagerStory.
// Only the target-backed prefix used by the recovered Story phase virtuals is
// exposed here; the remaining derived extent stays deliberately unnamed.
struct CBattleManagerStory {
    virtual void slot_00();
    virtual void slot_04();
    virtual void slot_08();
    virtual void slot_0c();
    virtual void slot_10();
    virtual void slot_14();
    virtual void slot_18();
    virtual int run_threshold_pipeline_471670();
    virtual int run_180_300_pipeline_471740();
    virtual int run_story_pipeline_4717e0();
    virtual void slot_28();
    virtual void slot_2c();
    virtual void slot_30();
    virtual void transition_slot_34(int phase);
    virtual void slot_38();
    virtual void slot_3c();
    virtual void pre_reset_slot_40();

    unsigned frame_counter_04;
    int pending_08;
    Fighter *fighter_0c;
    Fighter *fighter_10;
    unsigned char reserved_14[0x78];
    StoryInfoPhaseCounterView *info_8c;
    signed char mode_90;

    // Caller-backed member views of independently recovered target bodies.
    void reset_fighter_fields_6b4_728_view();
    void prepare_match_roster_470060();
    void run_global_action_owned_phase_view();
    void run_intermediate_phase_46dff0();
    void run_collision_phase_46cca0();
    void run_global_position_status_timer_phase_view();
    void run_post_update_callbacks_view();
};

typedef char CBattleManagerStory_fighter_offset_must_be_0x0c[
    offsetof(CBattleManagerStory, fighter_0c) == 0x0c ? 1 : -1];
typedef char CBattleManagerStory_info_offset_must_be_0x8c[
    offsetof(CBattleManagerStory, info_8c) == 0x8c ? 1 : -1];
typedef char CBattleManagerStory_mode_offset_must_be_0x90[
    offsetof(CBattleManagerStory, mode_90) == 0x90 ? 1 : -1];

} // namespace th105
