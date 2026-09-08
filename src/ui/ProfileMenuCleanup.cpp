#include "ProfileMenu.hpp"

namespace th105 {

void ProfileMenuBaseData::cleanup()
{
    unsigned int &texture_000 =
        *reinterpret_cast<unsigned int *>(this);
    if (texture_000 != 0) {
        g_title_resource_manager.release_title_resource_handle(texture_000);
        texture_000 = 0;
    }
}

} // namespace th105
