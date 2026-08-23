#include "ProfileMenu.hpp"
#include "ProfileSubmenus.hpp"

extern "C" void __cdecl dispatch_indexed_event(unsigned index);

namespace th105 {

void __cdecl install_menu_object(void *object);

bool CProfileMenu::update_state_two()
{
    guides_5a4[4].visible = true;
    switch (select_profile(
        reinterpret_cast<MenuString28 *>(&string_518),
        reinterpret_cast<MenuString28 *>(&string_534))) {
    case 1: {
        const char *profile_path = string_518.c_str();
        PlayerSlotRecord *player =
            reinterpret_cast<PlayerSlotRecord *>(&base_data_004);
        if (player->load_profile(profile_path)) {
            player->set_profile_color(160, 160, 255);
            CProfileCharacterSelect *menu =
                new CProfileCharacterSelect(player);
            install_menu_object(menu);
        }
        return true;
    }
    case 2:
        state_340 = 0;
        return true;
    default:
        return true;
    }
}

bool CProfileMenu::update_state_three()
{
    guides_5a4[4].visible = true;
    switch (select_profile(
        reinterpret_cast<MenuString28 *>(&string_518),
        reinterpret_cast<MenuString28 *>(&string_534))) {
    case 1: {
        const char *profile_path = string_518.c_str();
        PlayerSlotRecord *player =
            reinterpret_cast<PlayerSlotRecord *>(&base_data_004);
        if (player->load_profile(profile_path)) {
            dispatch_indexed_event(0x28);
            player->set_profile_color(160, 160, 255);
            CProfileKeyConfig *menu = new CProfileKeyConfig(player, -1);
            install_menu_object(menu);
        }
        return true;
    }
    case 2:
        state_340 = 0;
        return true;
    default:
        return true;
    }
}

} // namespace th105
