#include "ui/ProfileMenu.hpp"
#include "ui/Title.hpp"
#include "ui/ProfileMenuControllerRuntime.hpp"

namespace th105 {

signed char ProfileEditor168::update_selection()
{
    if (g_profile_menu_controller.mode_a0f) {
        ++state_160;
        if (g_profile_menu_controller.consume_reset()) {
            if (texture_secondary_004) {
                g_title_resource_manager.release_title_resource_handle(texture_secondary_004);
                texture_secondary_004 = 0;
            }
            if (texture_primary_000) {
                g_title_resource_manager.release_title_resource_handle(texture_primary_000);
                texture_primary_000 = 0;
            }
            state_160 = 0;
            g_profile_menu_controller.set_mode(0);
            return 1;
        }
        char *primary = g_profile_menu_controller.take_primary_text();
        if (primary) {
            g_title_resource_manager.release_title_resource_handle(texture_primary_000);
            texture_primary_000 = g_title_resource_manager.create_text_texture(
                primary, source_008, 512, 32, 0, 0).value;
            primary_tile_00c.set_texture(
                texture_primary_000, x_158, y_15c, width_154 / 2, width_154);
        }
        char *secondary = g_profile_menu_controller.take_secondary_text();
        if (secondary) {
            g_title_resource_manager.release_title_resource_handle(texture_secondary_004);
            texture_secondary_004 = g_title_resource_manager.create_text_texture(
                secondary, source_008, 512, 32, 0, 0).value;
            secondary_tile_0b0.set_texture(
                texture_secondary_004, x_158, y_15c, width_154 / 2, width_154);
        }
        return 0;
    }
    return -1;
}

} // namespace th105
