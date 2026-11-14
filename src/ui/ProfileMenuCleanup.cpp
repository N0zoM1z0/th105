#include "ProfileMenu.hpp"

namespace th105 {

void ProfileMenuBaseData::cleanup()
{
    if (texture_000 != 0)
        g_title_resource_manager.release_texture(texture_000);
}

} // namespace th105
