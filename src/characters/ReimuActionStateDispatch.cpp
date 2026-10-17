#include "ReimuActionStateStaging.hpp"

namespace th105 {

// One source path for the checked entry and all actions<=531. This staged
// bool's false means that the unreconstructed later middle/high path must continue.
// It is not the original void root and receives no implementation/exact credit.
bool ReimuActionStatePreludeView::run_checked_action_dispatch()
{
#include "ReimuActionStatePreludeBody.hpp"
    const short selected_action = action_13c;
    if (selected_action > 531)
        return false;
    switch (selected_action) {
#include "ReimuActionStateLowCases.hpp"
    case 71: case 72: case 73: case 74:
    case 75: case 76: case 77: case 78: {
#include "ReimuActionStateRecoveryBody.hpp"
    }
#include "ReimuActionStateMovementAttackCases.hpp"
#include "ReimuActionStateLateLowCases.hpp"
#include "ReimuActionStateMidNormalCases.hpp"
#include "ReimuActionStateMidProjectileCases.hpp"
#include "ReimuActionStateMidShotCases.hpp"
#include "ReimuActionStateMid500Cases.hpp"
#include "ReimuActionStateMid520Cases.hpp"
    default:
        update_common_action_state();
        return true;
    }
}

} // namespace th105
