#include "ProfileSubmenus.hpp"

namespace th105 {

CProfileCharacterSelect::~CProfileCharacterSelect()
{
    g_title_resource_manager.release_title_resource_handle(texture_04);
    design_13c.virtual_cleanup();
}

CProfileKeyConfig::~CProfileKeyConfig()
{
    g_title_resource_manager.release_title_resource_handle(texture_3c);
    g_title_resource_manager.release_title_resource_handle(texture_e4);
    design_08.virtual_cleanup();
}

} // namespace th105
