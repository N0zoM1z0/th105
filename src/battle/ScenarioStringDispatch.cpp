#include "battle/ScenarioTransition.hpp"

namespace th105 {

struct ScenarioStringDispatchTarget {
    unsigned char dispatch(String28 value);
};

unsigned char ScenarioTransitionView::dispatch_owned_string_458e80(
    String28 value)
{
    return reinterpret_cast<ScenarioStringDispatchTarget *>(
        reinterpret_cast<unsigned char *>(this) + 0x68)
        ->dispatch(String28(value, 0, static_cast<unsigned int>(-1)));
}

} // namespace th105
