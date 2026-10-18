#include "ReimuActionStateStaging.hpp"

namespace th105 {

// Remaining low-table actions and the direct300 edge of the original root.
// This source phase is not an original callable or a complete root.
bool ReimuActionStatePreludeView::try_run_checked_late_low_action()
{
    const short selected_action = action_13c;
    switch (selected_action) {
#include "ReimuActionStateLateLowCases.hpp"
    default:
        return false;
    }
#include "ReimuActionStateLandingAction10.hpp"
}

} // namespace th105
