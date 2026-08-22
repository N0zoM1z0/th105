#include "ProfileDeckEdit.hpp"

namespace th105 {

CProfileDeckEdit::~CProfileDeckEdit()
{
    g_title_resource_manager.release_title_resource_handle(texture_94);
    g_title_resource_manager.release_title_resource_handle(texture_258);
    g_title_resource_manager.release_title_resource_handle(texture_300);
    design_10.virtual_cleanup();
    resources_398.clear_resources();

    ProfileDeckRefreshFacade refresh;
    refresh.clear_common_resources();
    refresh.reload_common_resources(255, 96, 96);
}

} // namespace th105
