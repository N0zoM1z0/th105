#include "BattleManagerArcade.hpp"
#include "../ui/SceneTransitionState.hpp"
#include "../audio/BgmTransition.hpp"
#include "BattleController.hpp"
#include "GameMode.hpp"

namespace th105 {

void __fastcall reset_fighter_fields_6b4_728(void *context);
void __fastcall run_post_update_callbacks_and_global_state(void *context);
extern InfoManager *g_info_manager;


struct FighterPhaseContextArcadeSetupView {
    void begin_slot_4641f0(int slot);
    void configure_slot_463290(int slot, int value);
};

struct BattleObjectArcadeSetupManagerView {
    void reset_battle_render_state_and_signal_465f70();
};

struct BattleAudioArcadeSetupView {
    void set_stage_music_433860(int stage, int value);
};

struct ArcadeTransitionListView;
struct ArcadeTransitionListNode {
    ArcadeTransitionListNode *next;
    ArcadeTransitionListNode *prev;
};

struct ArcadeTransitionIterator {
    ArcadeTransitionListView *owner;
    ArcadeTransitionListNode *current;
};

struct ArcadeTransitionListView {
    unsigned allocator_state_00;
    ArcadeTransitionListNode *sentinel_04;
    unsigned size_08;

    ArcadeTransitionIterator erase(ArcadeTransitionIterator where);
};

extern BattleObjectArcadeSetupManagerView *g_battle_object_manager;
extern FighterPhaseContextArcadeSetupView *g_fighter_phase_context;
extern "C" const char arcade_bgm_path_format[];
extern "C" void __cdecl load_bgm_source(const char *path);
extern "C" __declspec(dllimport) int __cdecl wsprintfA(
    char *buffer, const char *format, ...);

namespace {

struct InfoManagerPhaseCounter494View {
    unsigned char reserved_000[0x494];
    int counter_494;
};

} // namespace


void CBattleManagerArcade::prepare_arcade_transition_473050()
{
    char path[260];
    MatchSetup *setup = get_match_setup();

    g_battle_object_manager->reset_battle_render_state_and_signal_465f70();
    reinterpret_cast<BattleAudioArcadeSetupView *>(&frame_counter_04)
        ->set_stage_music_433860(setup->stage_04, 0);
    wsprintfA(path, arcade_bgm_path_format, setup->bgm_id_05);
    load_bgm_source(path);

    g_fighter_phase_context->begin_slot_4641f0(1);
    g_fighter_phase_context->configure_slot_463290(1, 2);
    *reinterpret_cast<unsigned char *>(
        reinterpret_cast<unsigned char *>(this) + 0x5b0) = 0;
    reinterpret_cast<BattleController *>(this)
        ->initialize_battle_fighter_pair_46a490();
    ++*reinterpret_cast<unsigned *>(
        reinterpret_cast<unsigned char *>(this) + 0x5c0);

    ArcadeTransitionListView &list =
        *reinterpret_cast<ArcadeTransitionListView *>(
            reinterpret_cast<unsigned char *>(this) + 0x5b4);
    ArcadeTransitionIterator first = {&list, list.sentinel_04->next};
    list.erase(first);
}

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
