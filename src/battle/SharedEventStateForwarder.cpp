#include "SharedEventStateForwarder.hpp"
#include "SharedEventState.hpp"

namespace th105 {

char SharedEventStateForwarder::set_shared_first_target(
    char enabled,
    float target)
{
    return g_shared_event_state.set_target_20_enabled_2c(enabled, target);
}

char SharedEventStateForwarder::set_shared_second_target(
    char enabled,
    float target)
{
    return g_shared_event_state.set_target_24_enabled_2d(enabled, target);
}

char SharedEventStateForwarder::set_shared_third_target(
    char enabled,
    float target)
{
    return g_shared_event_state.set_target_28_enabled_2e(enabled, target);
}

} // namespace th105
