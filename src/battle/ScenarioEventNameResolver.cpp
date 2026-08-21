#include "assets/String28.hpp"

#include <map>
#include <string.h>

namespace th105 {

typedef std::map<int, String28> ScenarioEventNameMap;

extern "C" ScenarioEventNameMap g_scenario_event_name_map;

const char *__cdecl character_key_to_name(int character_key)
{
    return g_scenario_event_name_map.find(character_key)->second.c_str();
}

int __cdecl resolve_scenario_event_name(String28 value)
{
    for (ScenarioEventNameMap::iterator it =
             g_scenario_event_name_map.begin();
         it != g_scenario_event_name_map.end();
         ++it) {
        if (_stricmp(it->second.c_str(), value.c_str()) == 0) {
            return it->first;
        }
    }
    return 0;
}

} // namespace th105
