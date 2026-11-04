#include "battle/ScenarioData.hpp"
#include <utility>
namespace th105 {
typedef std::pair<std::string, ScenarioTextEntryDC> MutableScenarioPair;
typedef std::pair<const std::string, ScenarioTextEntryDC> ConstScenarioPair;
ConstScenarioPair probe_scenario_pair(const std::string &name, const ScenarioTextEntryDC &entry)
{
    MutableScenarioPair item(name, entry);
    return ConstScenarioPair(item);
}
}
