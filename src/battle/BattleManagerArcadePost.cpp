#include "battle/BattleManagerVirtuals.hpp"

namespace th105 {
// The existing base layout and native Arcade vtable establish this override;
// the derived nominal layout beyond the observed state byte remains unknown.
struct BattleManagerArcadePostView : CBattleManager {
    virtual void post_pipeline_slot_30();
    unsigned char unknown_090[0x5b0 - 0x90];
    unsigned char terminal_state_5b0;
};
typedef char ArcadeTerminalStateOffset[
    offsetof(BattleManagerArcadePostView, terminal_state_5b0) == 0x5b0 ? 1 : -1];

void BattleManagerArcadePostView::post_pipeline_slot_30()
{
    if (fighter_0c->terminal_pending_4e9 != 0) {
        if (fighter_10->terminal_pending_4e9 != 0) {
            fighter_10->terminal_delay_4e8 = 1;
            fighter_0c->terminal_delay_4e8 = 1;
            terminal_state_5b0 = 2;
            transition_slot_34(3);
            return;
        }
        ++fighter_10->terminal_delay_4e8;
        if (fighter_10->terminal_delay_4e8 == 2) {
            fighter_0c->terminal_finalize_4eb = 1;
            terminal_state_5b0 = 2;
            transition_slot_34(4);
            return;
        }
        ++terminal_state_5b0;
        transition_slot_34(3);
        return;
    }
    if (fighter_10->terminal_pending_4e9 != 0) {
        ++fighter_0c->terminal_delay_4e8;
        if (fighter_0c->terminal_delay_4e8 == 2) {
            fighter_10->terminal_finalize_4eb = 1;
            terminal_state_5b0 = 2;
            transition_slot_34(4);
            return;
        }
        ++terminal_state_5b0;
        transition_slot_34(3);
    }
}
}
