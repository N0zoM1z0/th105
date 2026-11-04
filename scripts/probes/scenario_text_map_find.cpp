#include "battle/ScenarioData.hpp"
namespace th105 {
typedef std::map<std::string, ScenarioTextEntryDC> ScenarioTextMapProbe;
ScenarioTextMapProbe::iterator probe_scenario_text_find(
    ScenarioTextMapProbe &items, const std::string &key)
{
    return items.find(key);
}
}
