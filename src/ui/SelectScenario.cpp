#include "SelectScenario.hpp"

namespace th105 {

CSelectScenario::~CSelectScenario()
{
    g_title_resource_manager.release_title_resource_handle(texture_218);
    g_title_resource_manager.release_title_resource_handle(texture_d8);
    g_title_resource_manager.release_title_resource_handle(texture_40);
    g_title_resource_manager.release_title_resource_handle(texture_170);
    design_2e4.virtual_cleanup();
}

} // namespace th105
