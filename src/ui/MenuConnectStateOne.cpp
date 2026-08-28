#include "MenuConnectStateRuntime.hpp"

namespace th105 {

bool CMenuConnectStateRuntimeView::update_state_one()
{
    switch (field<signed char>(0x09)) {
    case 0:
        field<GuideOverlay>(0xD9C).visible = true;
        switch (update_address_441bd0()) {
        case 1:
            field<signed char>(0x09) = 1;
            *reinterpret_cast<int *>(
                reinterpret_cast<unsigned char *>(field<void *>(0xC48)) +
                0x38) = field<int>(0x428);
            show_profile_message(connect_enable_prompt, true);
            break;
        case 2:
            field<signed char>(0x08) = 0;
            break;
        default:
            break;
        }
        break;

    case 1:
        field<GuideOverlay>(0xE44).visible = true;
        switch (update_profile_message()) {
        case 2:
            reset_state_4422f0();
            field<signed char>(0x09) = 0;
            break;
        case 3:
            field<unsigned char>(0x3B9) = 1;
            field<signed char>(0x09) = 2;
            show_profile_result(connect_waiting_message);
            finalize_state_442530();
            break;
        case 4:
            field<unsigned char>(0x3B9) = 0;
            field<signed char>(0x09) = 2;
            show_profile_result(connect_waiting_message);
            finalize_state_442530();
            break;
        default:
            break;
        }
        break;

    case 2:
        field<GuideOverlay>(0xEEC).visible = true;
        if (*reinterpret_cast<unsigned char *>(
                reinterpret_cast<unsigned char *>(field<void *>(0x04)) +
                0x3A4) != 0) {
            dispatch_indexed_event(0x39);
            g_scene_mode = 8;
            g_next_scene_mode = 4;
            field<signed char>(0x09) = -1;
            return true;
        }
        if (g_active_menu_input->hold.buttons[1] == 1 ||
            is_menu_initial_press(1, 0, 0, 0)) {
            dispatch_indexed_event(0x29);
            hide_profile_message_43f8d0();
            clear_network_session();
            field<void *>(0x04) = 0;
            field<signed char>(0x09) = 0;
            reset_state_4422f0();
        }
        break;

    default:
        break;
    }
    return true;
}

} // namespace th105
