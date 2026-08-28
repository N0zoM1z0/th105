#include "MenuConnectStateRuntime.hpp"

#include <cstring>

namespace th105 {

char CMenuConnectStateRuntimeView::finalize_message_4425d0()
{
    clear_network_session();
    field<void *>(0x04) = create_connect_client_43ce80();

    unsigned int port = 0;
    if (g_connect_config_ini.has_file_40f0b0(connect_config_file))
        port = static_cast<unsigned short>(
            g_connect_config_ini.read_uint_40f100(
                connect_config_section, connect_config_key_port));

    ConnectKey16 temporary;
    ConnectKey16 key = *get_connect_key_43aba0(&temporary);
    reinterpret_cast<ConnectSessionRuntimeView *>(field<void *>(0x04))
        ->status_3b4.configure_412e10(&key, port);
    *reinterpret_cast<int *>(
        reinterpret_cast<unsigned char *>(field<void *>(0x04)) + 0x4D0) = 1;

    ConnectPacket40 packet;
    if (field<unsigned char>(0x3B8)) {
        packet.include_profile = 1;
        MenuString28 *profile = reinterpret_cast<MenuString28 *>(
            reinterpret_cast<unsigned char *>(get_player_slot_record(0)) +
            0xB4);
        strcpy_s(packet.profile, 0x20, profile->c_str());
        packet.profile_length =
            static_cast<unsigned char>(strlen(packet.profile));
    } else {
        packet.include_profile = 0;
        packet.profile_length = 0;
    }

    MenuString28 &endpoint = field<MenuString28>(0x42C);
    return reinterpret_cast<ConnectSessionRuntimeView *>(field<void *>(0x04))
        ->status_3b4.send_415340(
            endpoint.c_str(),
            static_cast<unsigned short>(field<unsigned int>(0x428)),
            &packet,
            sizeof(packet));
}

} // namespace th105
