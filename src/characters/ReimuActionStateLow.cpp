#include "ReimuActionStateStaging.hpp"

namespace th105 {

// Verified actions0..10 of the Reimu root. This staging dispatcher is not
// an original function boundary and receives no implementation/exact credit.
bool ReimuActionStatePreludeView::try_run_checked_low_action()
{
    const short selected_action = action_13c;
    switch (selected_action) {
#include "ReimuActionStateLowCases.hpp"
    default:
        return false;
    }
}

} // namespace th105
