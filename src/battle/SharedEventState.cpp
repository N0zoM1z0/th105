#include "SharedEventState.hpp"

namespace th105 {

int __fastcall update_global_battle_setup_state_first(void *state);

char SharedEventState::set_target_20_enabled_2c(char enabled, float target)
{
    target_20 = target;
    enabled_2c = enabled;
    return enabled;
}

char SharedEventState::set_target_24_enabled_2d(char enabled, float target)
{
    target_24 = target;
    enabled_2d = enabled;
    return enabled;
}

char SharedEventState::set_target_28_enabled_2e(char enabled, float target)
{
    target_28 = target;
    enabled_2e = enabled;
    return enabled;
}

int SharedEventState::synchronize_targets()
{
    update_global_battle_setup_state_first(this);
    mirrored_18 = source_00;
    mirrored_1c = source_04;
    mirrored_14 = source_08;
    return update_global_battle_setup_state_first(this);
}

} // namespace th105
