#include "ScenarioData.hpp"

namespace th105 {

struct ScenarioScriptLoadGate {
    int load(const char *path, int option);
};

int CScenarioData::load_story_page_4583e0(const char *path)
{
    text_entries_32c.clear();
    reset_runtime_state();
    result_resources_390.hide_and_reset();
    return reinterpret_cast<ScenarioScriptLoadGate *>(&script_35c)->load(path, 0);
}

} // namespace th105
