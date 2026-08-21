#include "SharedEventStateForwarder.hpp"
#include "SharedEventState.hpp"

namespace th105 {

char SharedEventStateForwarder::set_shared_second_target(
    char enabled,
    float target)
{
    return g_shared_event_state.set_target_24_enabled_2d(enabled, target);
}

} // namespace th105
