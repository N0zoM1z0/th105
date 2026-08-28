#include "MenuConnectStateRuntime.hpp"
#include "../input/Input.hpp"

namespace th105 {

unsigned int CMenuConnectStateRuntimeView::reset_state_4422f0()
{
    show_profile_result(connect_address_result);
    unsigned char *input =
        reinterpret_cast<unsigned char *>(get_combined_menu_input());

    MenuCursorState &first = field<MenuCursorState>(0x3F8);
    if (input != 0)
        first.input_counter = reinterpret_cast<int *>(input + 0x38);
    else
        first.input_counter = 0;
    first.selection = 0;
    first.window_start = 0;
    first.item_count = 5;
    first.page_size = 0;

    MenuCursorState &second = field<MenuCursorState>(0x40C);
    if (input != 0)
        second.input_counter = reinterpret_cast<int *>(input + 0x3C);
    else
        second.input_counter = 0;
    second.selection = 0;
    second.window_start = 0;
    second.page_size = 0;
    second.item_count = 10;
    second.selection = 9 - field<unsigned int>(0x428) / 10000u % 10u;
    return static_cast<unsigned int>(second.selection);
}

int CMenuConnectStateRuntimeView::finalize_state_442530()
{
    clear_network_session();
    field<void *>(0x04) = create_connect_session_43ce00();

    unsigned char *slot =
        reinterpret_cast<unsigned char *>(get_player_slot_record(0));
    MenuString28 *profile_path =
        reinterpret_cast<MenuString28 *>(slot + 0xB4);
    reinterpret_cast<ConnectSessionRuntimeView *>(field<void *>(0x04))
        ->apply_profile_44d7d0(
            profile_path->c_str(), field<unsigned char>(0x3B9));

    ConnectKey16 temporary;
    ConnectKey16 key = *get_connect_key_43aba0(&temporary);
    int result =
        reinterpret_cast<ConnectSessionRuntimeView *>(field<void *>(0x04))
            ->status_3b4.configure_412e10(
                &key,
                static_cast<unsigned short>(field<unsigned int>(0x428)));
    *reinterpret_cast<int *>(
        reinterpret_cast<unsigned char *>(field<void *>(0x04)) + 0x4D0) = 1;
    return result;
}

} // namespace th105
