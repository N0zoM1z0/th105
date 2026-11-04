#include "battle/ScenarioData.hpp"
#include <utility>
namespace th105 {
typedef std::map<std::string, ScenarioTextEntryDC> ScenarioMap;
typedef std::pair<const std::string, ScenarioTextEntryDC> ScenarioPair;
void probe_scenario_map_insert(ScenarioMap &map, const ScenarioPair &entry)
{
    map.insert(entry);
}
}
