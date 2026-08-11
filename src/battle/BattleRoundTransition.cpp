#include "assets/String28.hpp"
#include "battle/BattleController.hpp"
#include "battle/Collision.hpp"

#include <new>

namespace th105 {

struct FighterTransitionView {
    void reset_transition_counters_45e010();
};

struct PostSequenceTransitionView {
    int publish_transition_effect_46e040(int effect);
    void publish_transition_effect_at_46e130(float position);
};

struct ScenarioTransitionView {
    signed char consume_transition_code_458d90();
    unsigned char dispatch_owned_string_458e80(String28 value);
};

struct ContinueMenu {
    unsigned char storage_00[0x40];
    explicit ContinueMenu(BattleController *controller);
};

struct EndMenu {
    unsigned char storage_00[0x44];
    explicit EndMenu(BattleController *controller);
};

extern unsigned char g_battle_transition_mode;
unsigned char __cdecl start_async_engine_scene_load(int scene);
void __cdecl install_menu_object_thunk(void *object);

void BattleController::dispatch_round_phase_34(int phase)
{
    phase_88 = phase;
    switch (phase) {
    case 0:
        outcome_band_94 = 0;
        tally_second_98 = 0;
        tally_third_9c = 0;
        transition_flag_91 = 0;
        fighter_0c->accumulated_hit_quantity_178 = 0;
        break;
    case 1:
        reinterpret_cast<FighterTransitionView *>(fighter_0c)
            ->reset_transition_counters_45e010();
        reinterpret_cast<FighterTransitionView *>(fighter_10)
            ->reset_transition_counters_45e010();
        reinterpret_cast<PostSequenceTransitionView *>(post_sequence_context_8c)
            ->publish_transition_effect_46e040(13);
        reinterpret_cast<PostSequenceTransitionView *>(post_sequence_context_8c)
            ->publish_transition_effect_at_46e130(480.0f);
        break;
    case 2:
        fighter_0c->unknown_4ec = 0;
        fighter_10->unknown_4ec = 0;
        break;
    case 3:
        fighter_0c->unknown_4ec = fighter_0c->terminal_pending_4e9 == 0;
        fighter_10->unknown_4ec = fighter_10->terminal_pending_4e9 == 0;
        field_90 = 0;
        if (fighter_10->terminal_pending_4e9 != 0) {
            field_90 = reinterpret_cast<ScenarioTransitionView *>(
                g_battle_phase_block)->consume_transition_code_458d90();
            switch (static_cast<signed char>(field_90)) {
            case 0:
                reinterpret_cast<PostSequenceTransitionView *>(
                    post_sequence_context_8c)->publish_transition_effect_46e040(22);
                break;
            case 1:
                reinterpret_cast<PostSequenceTransitionView *>(
                    post_sequence_context_8c)->publish_transition_effect_46e040(18);
                break;
            case 2:
                reinterpret_cast<PostSequenceTransitionView *>(
                    post_sequence_context_8c)->publish_transition_effect_46e040(17);
                break;
            }
        } else if (fighter_0c->terminal_pending_4e9 != 0) {
            reinterpret_cast<PostSequenceTransitionView *>(post_sequence_context_8c)
                ->publish_transition_effect_46e040(22);
        }
        break;
    case 4:
        if (fighter_0c->terminal_finalize_4eb == 0 &&
            g_battle_phase_block != 0 &&
            *(reinterpret_cast<signed char *>(g_battle_phase_block) + 0x594) <
                *(reinterpret_cast<signed char *>(g_battle_phase_block) + 0x595)) {
            start_async_engine_scene_load(4);
        }
        reinterpret_cast<PostSequenceTransitionView *>(post_sequence_context_8c)
            ->publish_transition_effect_46e040(17);
        break;
    case 5:
        if (fighter_0c->terminal_finalize_4eb != 0) {
            if (g_battle_transition_mode == 6) {
                dispatch_round_phase_34(6);
                break;
            }
            reinterpret_cast<ScenarioTransitionView *>(g_battle_phase_block)
                ->dispatch_owned_string_458e80(String28("Lose"));
        } else {
            reinterpret_cast<ScenarioTransitionView *>(g_battle_phase_block)
                ->dispatch_owned_string_458e80(String28("Win"));
        }
        break;
    case 6:
        if (phase_a0 > 0) {
            install_menu_object_thunk(new ContinueMenu(this));
        } else {
            install_menu_object_thunk(new EndMenu(this));
        }
        break;
    }
    frame_counter_04 = 0;
}

} // namespace th105
