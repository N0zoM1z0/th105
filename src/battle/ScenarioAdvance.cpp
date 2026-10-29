#include "ScenarioData.hpp"

namespace th105 {

signed char CScenarioData::advance_until_ready_454f10()
{
    signed char ready;
    do {
        ready = update();
    } while (!ready);
    return ready;
}

} // namespace th105
