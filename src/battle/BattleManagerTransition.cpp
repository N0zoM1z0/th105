#include "BattleManagerVirtuals.hpp"
#include "PostSequenceTransition.hpp"

#include <new>

namespace th105 {

struct CMenuEndDispatchView {
    unsigned char observed_extent_00[0x44];
    explicit CMenuEndDispatchView(CBattleManager *owner);
};

void __cdecl install_menu_object(void *object);
void __fastcall reset_fighter_round_counters_45f610(Fighter *fighter);

void CBattleManager::transition_slot_34(int phase)
{
    phase_88 = phase;
    switch (phase) {
    case 1:
        reset_fighter_round_counters_45f610(fighter_0c);
        reset_fighter_round_counters_45f610(fighter_10);
        reinterpret_cast<PostSequenceTransitionView *>(g_info_manager)
            ->publish_transition_effect_46e040(
            static_cast<signed char>(transition_state_5b0()) + 10);
        if (transition_state_5b0() == 0)
            reinterpret_cast<PostSequenceTransitionView *>(g_info_manager)
                ->publish_transition_effect_at_46e130(400.0f);
        fighter_0c->value_174 = fighter_0c->maximum_176;
        fighter_10->value_174 = fighter_10->maximum_176;
        break;
    case 2:
        fighter_0c->unknown_4ec = 0;
        fighter_10->unknown_4ec = 0;
        break;
    case 3:
        fighter_0c->unknown_4ec = fighter_0c->terminal_pending_4e9 == 0;
        fighter_10->unknown_4ec = fighter_10->terminal_pending_4e9 == 0;
        reinterpret_cast<PostSequenceTransitionView *>(g_info_manager)
            ->publish_transition_effect_46e040(16);
        break;
    case 4:
        if (fighter_0c->terminal_delay_4e8 >= 2)
            fighter_0c->unknown_4ec = fighter_0c->terminal_pending_4e9 == 0;
        if (fighter_10->terminal_delay_4e8 >= 2)
            fighter_10->unknown_4ec = fighter_10->terminal_pending_4e9 == 0;
        reinterpret_cast<PostSequenceTransitionView *>(g_info_manager)
            ->publish_transition_effect_46e040(17);
        break;
    case 5:
        run_transition_phase_5_4724e0();
        break;
    case 6:
        install_menu_object(new CMenuEndDispatchView(this));
        break;
    }

    frame_counter_04 = 0;
}

} // namespace th105
