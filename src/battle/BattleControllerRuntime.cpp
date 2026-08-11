#include "BattleController.hpp"

namespace th105 {

int BattleController::run_active_simulation_frame_4704d0()
{
    int result = run_battle_phase_and_info_callback();
    int phase = phase_88;
    if (phase == 0 || phase == 5 || phase == 6) {
        return g_battle_phase_block->run_458cd0();
    }
    return result;
}

} // namespace th105
