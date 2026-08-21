#include "BattleManagerVirtuals.hpp"

namespace th105 {

extern "C" void __cdecl play_bgm(const char *path);
void __fastcall reset_fighter_fields_6bc_728(void *context);
void __fastcall reset_fighter_fields_6b4_728(void *context);
void __fastcall run_post_update_callbacks_and_global_state(void *context);
unsigned __cdecl get_session_setup_option();
extern InfoManager *g_info_manager;

namespace {

struct InfoManagerPhaseCounter494View {
    unsigned char reserved_000[0x494];
    int counter_494;
};

} // namespace

int CBattleManager::constant_one_471920()
{
    return 1;
}

void CBattleManager::mark_terminal_pending_if_state_not_3_472490(Fighter *fighter)
{
    if (fighter->state_72c != 3)
        fighter->terminal_pending_4e9 = 1;
}

void CBattleManager::update_phase_object_if_needed_4724b0()
{
    run_shared_pre_phase_46bf00();
    if (phase_88 == 5 || phase_88 == 6)
        phase_object_8c.run_phase_tail_0c();
}

int CBattleManager::run_pipeline_and_transition_472d80()
{
    run_global_action_owned_phase_view();
    run_collision_phase_46cca0();
    run_global_position_status_timer_phase_view();
    run_post_update_callbacks_and_global_state(this);
    if (frame_counter_04 > 60) {
        play_bgm(0);
        transition_slot_34(1);
    }
    return 0;
}

int CBattleManager::run_reset_pipeline_472dc0()
{
    pre_reset_slot_40();
    reset_fighter_fields_6bc_728(this);
    run_global_action_owned_phase_view();
    run_collision_phase_46cca0();
    run_global_position_status_timer_phase_view();
    run_post_update_callbacks_and_global_state(this);
    if (pending_08 != 0)
        transition_slot_34(2);
    return 0;
}

int CBattleManager::run_full_pipeline_471630()
{
    pre_reset_slot_40();
    run_global_action_owned_phase_view();
    run_intermediate_phase_46dff0();
    run_collision_phase_46cca0();
    run_global_position_status_timer_phase_view();
    run_post_update_callbacks_and_global_state(this);
    post_pipeline_slot_30();
    return 0;
}

int CBattleManager::run_120_frame_pipeline_472e10()
{
    unsigned frame = frame_counter_04;
    if (frame > 120 || (static_cast<unsigned char>(frame) & 3) == 0) {
        pre_reset_slot_40();
        if (frame_counter_04 > 120)
            reset_fighter_fields_6bc_728(this);
        run_global_action_owned_phase_view();
        if (fighter_0c->unknown_4ec == 0 || fighter_10->unknown_4ec == 0)
            run_intermediate_phase_46dff0();
        run_collision_phase_46cca0();
        run_global_position_status_timer_phase_view();
    }
    run_post_update_callbacks_and_global_state(this);
    if (fighter_0c->unknown_4ec != 0 && fighter_10->unknown_4ec != 0)
        transition_slot_34(1);
    return 0;
}

int CBattleManager::run_180_frame_pipeline_472ea0()
{
    unsigned frame = frame_counter_04;
    if (frame > 180 || (static_cast<unsigned char>(frame) & 3) == 0) {
        pre_reset_slot_40();
        if (frame_counter_04 >= 180)
            reset_fighter_fields_6b4_728(this);
        run_global_action_owned_phase_view();
        run_intermediate_phase_46dff0();
        run_collision_phase_46cca0();
        run_global_position_status_timer_phase_view();
    }
    run_post_update_callbacks_and_global_state(this);
    if (frame_counter_04 > 300) {
        unsigned option = get_session_setup_option();
        if (option == 2)
            return option;
        transition_slot_34(5);
    }
    return 0;
}

int CBattleManager::run_info_phase_pipeline_472f10()
{
    pre_reset_slot_40();
    reset_fighter_fields_6b4_728(this);
    if (reinterpret_cast<InfoManagerPhaseCounter494View *>(g_info_manager)
            ->counter_494 < 30) {
        reinterpret_cast<InfoManagerPhaseCounter494View *>(g_info_manager)
            ->counter_494 += 1;
    }
    if (phase_object_8c.status_08() <= 0)
        transition_slot_34(6);
    run_global_action_owned_phase_view();
    run_collision_phase_46cca0();
    run_global_position_status_timer_phase_view();
    run_post_update_callbacks_and_global_state(this);
    return 0;
}

} // namespace th105
