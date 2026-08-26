#include "BattleManagerArcade.hpp"
#include "PostSequenceTransition.hpp"

#include <new>

namespace th105 {

struct CMenuEndArcadeDispatchView {
    unsigned char observed_extent_00[0x44];
    explicit CMenuEndArcadeDispatchView(CBattleManager *owner);
};

void __cdecl install_menu_object(void *object);
extern unsigned char g_round_counter;

void CBattleManagerArcade::transition_slot_34(int phase)
{
    phase_88 = phase;

    switch (phase) {
    case 4:
        reinterpret_cast<PostSequenceTransitionView *>(g_info_manager)
            ->publish_transition_effect_46e040(17);
        if (fighter_10->terminal_finalize_4eb != 0) {
            finalize_arcade_round_473110();
            if (fighter_10->terminal_delay_4e8 != 0)
                g_round_counter += 1;
            else
                g_round_counter += 2;
        }
        break;
    case 6:
        install_menu_object(new CMenuEndArcadeDispatchView(this));
        break;
    default:
        CBattleManager::transition_slot_34(phase);
        break;
    }

    frame_counter_04 = 0;
}

} // namespace th105
