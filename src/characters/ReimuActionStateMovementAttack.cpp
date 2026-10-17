#include "ReimuActionStateStaging.hpp"

namespace th105 {

// Another phase of the81550-byte root; not an original callable boundary.
bool ReimuActionStatePreludeView::try_run_checked_movement_attack_action()
{
    const short selected_action = action_13c;
    switch (selected_action) {
#include "ReimuActionStateMovementAttackCases.hpp"
    default:
        return false;
    }
}

} // namespace th105
