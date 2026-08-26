#include "ProfileMenu.hpp"

namespace th105 {

bool PlayerSlotRecord::reload_profile()
{
    ProfileMenuBaseData *data =
        reinterpret_cast<ProfileMenuBaseData *>(this);
    std::string path(data->string_098);
    return load_profile(path.c_str());
}

} // namespace th105
