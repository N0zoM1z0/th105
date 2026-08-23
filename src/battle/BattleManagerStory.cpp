#include "BattleManagerStory.hpp"
#include "BattleController.hpp"
#include "GameMode.hpp"
#include "../ui/SceneTransitionState.hpp"

namespace th105 {

extern "C" __declspec(dllimport) void *__stdcall CreateEventA(
    void *, int, int, const char *);
extern "C" __declspec(dllimport) unsigned __stdcall WaitForSingleObject(
    void *, unsigned);
extern "C" __declspec(dllimport) int __stdcall CloseHandle(void *);

struct StoryEventWait {
    void *handle;
    unsigned wait_ms;

    StoryEventWait() : handle(CreateEventA(0, 0, 0, 0)), wait_ms(0x10) {}
    ~StoryEventWait() { CloseHandle(handle); }
    void wait() { WaitForSingleObject(handle, wait_ms); }
};

struct BattlePhaseStoryView {
    signed char status_45a290();

    signed char current_594() const
    {
        return *reinterpret_cast<const signed char *>(
            reinterpret_cast<const unsigned char *>(this) + 0x594);
    }

    signed char limit_595() const
    {
        return *reinterpret_cast<const signed char *>(
            reinterpret_cast<const unsigned char *>(this) + 0x595);
    }
};

int CBattleManagerStory::run_threshold_pipeline_471670()
{
    unsigned threshold;
    switch (mode_90) {
    case 0:
        threshold = 0;
        break;
    case 1:
        threshold = 120;
        break;
    case 2:
        threshold = 180;
        break;
    }

    unsigned frame = frame_counter_04;
    if (frame >= threshold || (static_cast<unsigned char>(frame) & 3) == 0) {
        pre_reset_slot_40();
        if (mode_90 == 2 && frame_counter_04 > threshold)
            reset_fighter_fields_6b4_728_view();

        unsigned char was_pending = fighter_0c->terminal_pending_4e9;
        run_global_action_owned_phase_view();
        if (was_pending != 0 && fighter_0c->terminal_pending_4e9 == 0)
            fighter_0c->value_174 = fighter_0c->maximum_176;

        run_intermediate_phase_46dff0();
        run_collision_phase_46cca0();
        run_global_position_status_timer_phase_view();
    }

    run_post_update_callbacks_view();
    if ((fighter_10->unknown_4ec & fighter_0c->unknown_4ec) != 0)
        transition_slot_34(2);
    return 0;
}

int CBattleManagerStory::run_180_300_pipeline_471740()
{
    unsigned frame = frame_counter_04;
    if (frame > 180 || (static_cast<unsigned char>(frame) & 3) == 0) {
        pre_reset_slot_40();
        if (frame_counter_04 >= 180)
            reset_fighter_fields_6b4_728_view();
        run_global_action_owned_phase_view();
        run_intermediate_phase_46dff0();
        run_collision_phase_46cca0();
        run_global_position_status_timer_phase_view();
    }

    run_post_update_callbacks_view();
    if (frame_counter_04 > 300) {
        if (get_session_setup_option() == 2) {
            if (fighter_0c->terminal_finalize_4eb == 0) {
                BattlePhaseStoryView *phase =
                    reinterpret_cast<BattlePhaseStoryView *>(g_battle_phase_block);
                if (phase->current_594() < phase->limit_595()) {
                    // Both Story terminal gates are still open.
                } else {
                    return 2;
                }
            } else {
                return 2;
            }
        }
        if (static_cast<int>(get_game_mode()) == 7)
            return 2;
        transition_slot_34(5);
    }
    return 0;
}

int CBattleManagerStory::run_story_pipeline_4717e0()
{
    reset_fighter_fields_6b4_728_view();

    if (info_8c->counter_494 < 30)
        ++info_8c->counter_494;

    if (reinterpret_cast<BattlePhaseStoryView *>(g_battle_phase_block)
            ->status_45a290() <= 0) {
        if (fighter_0c->terminal_finalize_4eb != 0) {
            transition_slot_34(6);
            return 0;
        }
        if (reinterpret_cast<BattlePhaseStoryView *>(g_battle_phase_block)
                ->current_594() >=
            reinterpret_cast<BattlePhaseStoryView *>(g_battle_phase_block)
                ->limit_595())
            return 3;

        StoryEventWait event;
        while (get_async_scene_load_request() != 0)
            event.wait();
        prepare_match_roster_470060();
    }

    run_global_action_owned_phase_view();
    run_collision_phase_46cca0();
    run_global_position_status_timer_phase_view();
    run_post_update_callbacks_view();
    return 0;
}

} // namespace th105
