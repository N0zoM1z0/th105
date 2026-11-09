#include "BattleController.hpp"

namespace th105 {

struct ScenarioStepRuntime {
    virtual void unknown_00();
    virtual void unknown_04();
    virtual signed char run_scenario_step();
    virtual void render_scenario();
};

signed char BattlePhaseBlock::run_scenario_step()
{
    return reinterpret_cast<ScenarioStepRuntime *>(
        reinterpret_cast<unsigned char *>(this) + 0x68)
        ->run_scenario_step();
}

void BattlePhaseBlock::render_scenario()
{
    reinterpret_cast<ScenarioStepRuntime *>(
        reinterpret_cast<unsigned char *>(this) + 0x68)
        ->render_scenario();
}

} // namespace th105
