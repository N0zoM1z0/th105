#include "ReimuActionStateStaging.hpp"

namespace th105 {

// Actions71..78 of the original +0x28 root. This staged phase is not an
// original function boundary and receives no implementation/exact credit.
bool ReimuActionStatePreludeView::try_run_checked_recovery_action()
{
    const short selected_action = action_13c;
    if (selected_action < 71 || selected_action > 78)
        return false;

#include "ReimuActionStateRecoveryBody.hpp"

}

} // namespace th105
