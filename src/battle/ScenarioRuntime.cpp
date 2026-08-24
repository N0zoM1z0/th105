#include "ScenarioData.hpp"

namespace th105 {

void CScenarioData::clear_runtime()
{
    text_entries_32c.clear();
    system_effects_004.release_all_system_effects();
    script_35c.clear_commands();
}

} // namespace th105
