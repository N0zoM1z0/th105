#include "battle/ScenarioTransition.hpp"
#include "battle/ScenarioData.hpp"

namespace th105 {

unsigned char ScenarioTransitionView::dispatch_owned_string_458e80(
    String28 value)
{
    return reinterpret_cast<CScenarioData *>(
        reinterpret_cast<unsigned char *>(this) + 0x68)
        ->select_label(String28(value, 0, static_cast<unsigned int>(-1)));
}

} // namespace th105
