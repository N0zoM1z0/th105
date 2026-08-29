#include "BattleController.hpp"

namespace th105 {

struct ScenarioStepRuntime {
    virtual void unknown_00();
    virtual void unknown_04();
    virtual bool run_scenario_step();
    virtual int run_phase_step();
};

bool BattlePhaseBlock::run_scenario_step()
{
    return reinterpret_cast<ScenarioStepRuntime *>(
        reinterpret_cast<unsigned char *>(this) + 0x68)
        ->run_scenario_step();
}

int BattlePhaseBlock::run_458cd0()
{
    return reinterpret_cast<ScenarioStepRuntime *>(
        reinterpret_cast<unsigned char *>(this) + 0x68)
        ->run_phase_step();
}

} // namespace th105
