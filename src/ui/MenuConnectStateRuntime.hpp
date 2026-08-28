#pragma once

#include "GuideOverlay.hpp"
#include "Menu.hpp"
#include "MenuCursor.hpp"
#include "MenuSelect.hpp"
#include "../input/InputManager.hpp"
#include "../input/InputSelection.hpp"

namespace th105 {

extern "C" CInputManager *g_active_menu_input;
extern "C" int __cdecl update_profile_message();
extern "C" int __cdecl update_profile_confirmation();
extern "C" void __cdecl clear_network_session();
extern "C" void __cdecl dispatch_indexed_event(unsigned int index);
extern "C" bool __cdecl is_menu_initial_press(
    int primary, int modifier_a, int modifier_b, int modifier_c);
extern "C" void __cdecl close_config_menu();
extern "C" int g_next_scene_mode;

extern "C" const char connect_enable_prompt[];
extern "C" const char connect_waiting_message[];
extern "C" const char connect_address_result[];
extern "C" const char connect_config_file[];
extern "C" const char connect_config_section[];
extern "C" const char connect_config_key_port[];

struct ConnectKey16 {
    int values[4];
};

typedef char ConnectKey16_size_must_be_0x10[
    sizeof(ConnectKey16) == 0x10 ? 1 : -1];

struct ConnectPacket40 {
    unsigned char include_profile;
    unsigned char profile_length;
    char profile[38];
};

typedef char ConnectPacket40_size_must_be_0x28[
    sizeof(ConnectPacket40) == 0x28 ? 1 : -1];

struct ConnectConfigIniView {
    bool has_file_40f0b0(const char *path);
    unsigned int read_uint_40f100(const char *section, const char *key);
};

extern ConnectConfigIniView g_connect_config_ini;

struct ConnectStatusRuntimeView {
    int configure_412e10(const ConnectKey16 *key, int value);
    char send_415340(
        const char *endpoint,
        unsigned short port,
        const ConnectPacket40 *packet,
        unsigned short size);
};

struct ConnectSessionRuntimeView {
    void apply_profile_44d7d0(const char *source, unsigned char flag);
    unsigned char reserved_00[0x3B4];
    ConnectStatusRuntimeView status_3b4;
};

typedef char ConnectSessionRuntimeView_status_offset_must_be_0x3b4[
    offsetof(ConnectSessionRuntimeView, status_3b4) == 0x3B4 ? 1 : -1];

ConnectSessionRuntimeView *__cdecl create_connect_session_43ce00();
ConnectSessionRuntimeView *__cdecl create_connect_client_43ce80();
ConnectKey16 *__cdecl get_connect_key_43aba0(ConnectKey16 *output);

class CMenuConnectStateRuntimeView : public Menu {
public:
    template <typename T>
    T &field(unsigned int offset)
    {
        return *reinterpret_cast<T *>(
            reinterpret_cast<unsigned char *>(this) + offset);
    }

    bool update_state_one();
    unsigned int reset_state_4422f0();
    int finalize_state_442530();
    char finalize_message_4425d0();
    bool update_state_six();

private:
    int update_address_441bd0();
    void hide_profile_message_43f8d0();
};

} // namespace th105
