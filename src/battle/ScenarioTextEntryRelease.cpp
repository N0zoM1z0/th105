#include "ScenarioData.hpp"
#include "ui/Title.hpp"

namespace th105 {

ScenarioTextEntryDC::~ScenarioTextEntryDC()
{
    g_title_resource_manager.release_title_resource_handle(resource_handle_000);
}

} // namespace th105
