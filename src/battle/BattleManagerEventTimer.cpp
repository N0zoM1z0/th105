#include "battle/BattleManagerVirtuals.hpp"
#include "battle/EventSubobject130.hpp"
#include "battle/PairEmbeddedMode.hpp"

namespace th105 {
extern int g_pair_mode_primary;
extern int g_secondary_event_effect_id;
extern short g_info_mode_value_6fa88c;
extern int g_pair_state;
int __cdecl selector_random_roll(int limit);

// The native tail accepts the same owner at ECX. This view names only the
// already recovered presentation operation; it does not claim a second object.
struct BattleTimerPresentationView {
    void update_presentation_46b160();
};
struct BattleManagerEventTimerView : CBattleManager {
    void update_event_timer();
};
void BattleManagerEventTimerView::update_event_timer()
{
    if (phase_88 == 2) {
        if (g_pair_mode_primary != 16) {
            g_info_mode_value_6fa88c -= (g_pair_state & 1);
            if (g_info_mode_value_6fa88c <= 0) {
                g_info_mode_value_6fa88c = 0;
                reinterpret_cast<PairEmbeddedModeView *>(&frame_counter_04)
                    ->select_pair_mode_434780(16, 1);
            }
        } else {
            ++g_info_mode_value_6fa88c;
            if (g_secondary_event_effect_id == 16 && g_info_mode_value_6fa88c >= 499) {
                reinterpret_cast<EventSubobject130 *>(&frame_counter_04)
                    ->trigger_secondary_event_effect(selector_random_roll(15));
            } else if (g_info_mode_value_6fa88c >= 999) {
                g_info_mode_value_6fa88c = 999;
                reinterpret_cast<PairEmbeddedModeView *>(&frame_counter_04)
                    ->select_pair_mode_434780(g_secondary_event_effect_id, 1);
            }
        }
    }
    reinterpret_cast<BattleTimerPresentationView *>(this)->update_presentation_46b160();
}
}
