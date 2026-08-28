#include "MenuConnectStateRuntime.hpp"

namespace th105 {

bool CMenuConnectStateRuntimeView::update_state_six()
{
    MenuString28 selected;
    MenuString28 alternate;
    switch (select_profile(&selected, &alternate)) {
    case 1:
        if (get_player_slot_record(0)->load_profile(selected.c_str())) {
            get_player_slot_record(0)->set_profile_color(160, 160, 255);
            close_config_menu();
            field<signed char>(0x08) = 0;
        }
        break;
    case 2:
        field<signed char>(0x08) = 0;
        break;
    default:
        break;
    }
    return true;
}

} // namespace th105
