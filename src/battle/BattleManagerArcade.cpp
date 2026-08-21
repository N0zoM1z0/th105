#include "BattleManagerArcade.hpp"
#include "../ui/SceneTransitionState.hpp"
#include "../audio/BgmTransition.hpp"

namespace th105 {

void __fastcall reset_fighter_fields_6b4_728(void *context);
void __fastcall run_post_update_callbacks_and_global_state(void *context);
extern InfoManager *g_info_manager;

namespace {

struct InfoManagerPhaseCounter494View {
    unsigned char reserved_000[0x494];
    int counter_494;
};

} // namespace

int CBattleManagerArcade::run_info_phase_pipeline_472f10()
{
    if (fade_transition_pending_5c4() != 0) {
        if (static_cast<unsigned char>(is_scene_fade_in_progress()) != 0)
            return 0;
        if (get_async_scene_load_request() != 0)
            return 0;

        prepare_arcade_transition_473050();
        start_scene_fade_out(0xff000000u, 60);
        fade_transition_pending_5c4() = 0;
        return 0;
    }

    pre_reset_slot_40();
    reset_fighter_fields_6b4_728(this);

    if (reinterpret_cast<InfoManagerPhaseCounter494View *>(g_info_manager)
            ->counter_494 < 30) {
        reinterpret_cast<InfoManagerPhaseCounter494View *>(g_info_manager)
            ->counter_494 += 1;
    }

    if (phase_object_8c.status_08() <= 0) {
        if (transition_resource_5bc() != 0 &&
            fighter_0c->terminal_finalize_4eb == 0) {
            fade_bgm(1000, 0);
            start_scene_fade_in(0xff000000u, 60);
            fade_transition_pending_5c4() = 1;
        } else {
            transition_slot_34(6);
        }
    }

    run_global_action_owned_phase_view();
    run_global_position_status_timer_phase_view();
    run_post_update_callbacks_and_global_state(this);
    return 0;
}

} // namespace th105
