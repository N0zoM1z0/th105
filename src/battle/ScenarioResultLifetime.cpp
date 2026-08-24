#include "ScenarioData.hpp"
#include "ui/Title.hpp"

namespace th105 {

ScenarioResultResource::~ScenarioResultResource()
{
    g_title_resource_manager.release_title_resource_handle(texture_058);
    reinterpret_cast<TitleDesignResource *>(&design_008)->virtual_cleanup();
}

} // namespace th105
