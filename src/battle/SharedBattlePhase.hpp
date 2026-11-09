#pragma once

namespace th105 {

// Shared member-call view. These methods do not access receiver fields.
struct SharedBattlePhaseController {
    void run_shared_battle_phase_sequence();
    void run_battle_phase_and_info_callback();
};

} // namespace th105
