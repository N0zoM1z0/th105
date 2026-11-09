#include "BattleController.hpp"
#include "BattleManagerStory.hpp"
#include "SharedBattlePhase.hpp"

namespace th105 {

void CBattleManagerStory::render()
{
    reinterpret_cast<SharedBattlePhaseController *>(this)
        ->run_battle_phase_and_info_callback();
    int phase = phase_88;
    if (phase == 0 || phase == 5 || phase == 6) {
        g_battle_phase_block->render_scenario();
    }
}

} // namespace th105
