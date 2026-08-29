#include "ProfileMenu.hpp"
#include "Title.hpp"

#include <cstring>

namespace th105 {

struct ProfileMenuControllerReadNameView {
    char *take_primary_text();
};
extern "C" ProfileMenuControllerReadNameView g_profile_menu_controller;

struct ProfileReadStringAssignView {
    void assign_bytes(const char *source, unsigned int size);
};

void ProfileEditor168::read_profile_name(MenuString28 *output)
{
    char *text = g_profile_menu_controller.take_primary_text();
    reinterpret_cast<ProfileReadStringAssignView *>(output)->assign_bytes(
        text, static_cast<unsigned int>(std::strlen(text)));
}

void ProfileEditor168::shutdown()
{
    g_title_resource_manager.release_title_resource_handle(texture_primary_000);
    g_title_resource_manager.release_title_resource_handle(texture_secondary_004);
}

} // namespace th105

namespace th105 {

ProfileEditor168::~ProfileEditor168()
{
}

} // namespace th105
