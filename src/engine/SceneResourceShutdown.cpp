#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <string>
#include <stddef.h>
#include "ui/Title.hpp"

namespace th105 {
struct AsyncSceneThreadControl { int set_priority(int); void wait_for_exit(); };
extern AsyncSceneThreadControl g_async_scene_thread;
struct ScoreData { void persist(); };
extern ScoreData g_score_data;
struct ShutdownSocketView { void shutdown(); };
struct CNetworkBase {
    virtual ~CNetworkBase();
    unsigned char unknown_004[0x274];
    unsigned texture_278;
    unsigned char unknown_27c[0x138];
    ShutdownSocketView socket_3b4;
};
extern CNetworkBase *g_network_session;
void __cdecl destroy_shared_battle_runtime();
unsigned char __cdecl shutdown_profile_ui();
void __cdecl shutdown_battle_effect_program();
struct SceneBootstrapDeckRefresh { void clear_common_resources(); };
extern SceneBootstrapDeckRefresh g_bootstrap_deck_refresh;
struct ShutdownProfileView {
    unsigned char unknown_000[0x98];
    std::string config_name_098;
    unsigned char unknown_0b4[0x288];
    void cleanup();
};
extern ShutdownProfileView g_shutdown_profiles[2];
struct ShutdownConfigView {
    std::string profile_names[2];
    void save();
};
extern ShutdownConfigView g_shutdown_config;
struct ShutdownWaveView { void release_handle(unsigned); };
extern ShutdownWaveView g_shutdown_wave;
extern unsigned g_indexed_event_handles[128];
extern HWND g_main_window;
extern int g_config_window_mode_state;
extern bool g_bootstrap_send_enter;

typedef char ShutdownProfileSize[sizeof(ShutdownProfileView)==0x33c?1:-1];
typedef char ShutdownNetworkTexture[offsetof(CNetworkBase,texture_278)==0x278?1:-1];
typedef char ShutdownNetworkSocket[offsetof(CNetworkBase,socket_3b4)==0x3b4?1:-1];
void __cdecl shutdown_scene_resources()
{
    g_async_scene_thread.set_priority(0);
    g_async_scene_thread.wait_for_exit();
    g_score_data.persist();
    if (g_network_session) {
        ShutdownSocketView *socket = &g_network_session->socket_3b4;
        CNetworkBase *session = g_network_session;
        socket->shutdown();
        g_title_resource_manager.release_title_resource_handle(session->texture_278);
        if (g_network_session) {
            delete g_network_session;
            g_network_session = 0;
        }
    }
    destroy_shared_battle_runtime();
    shutdown_profile_ui();
    g_bootstrap_deck_refresh.clear_common_resources();
    shutdown_battle_effect_program();
    g_shutdown_profiles[0].cleanup();
    g_shutdown_profiles[1].cleanup();
    for (int i=0;i<128;++i)
        g_shutdown_wave.release_handle(g_indexed_event_handles[i]);
    g_bootstrap_send_enter = g_config_window_mode_state == 0;
    if (g_bootstrap_send_enter)
        SendMessageA(g_main_window, WM_SYSKEYDOWN, VK_RETURN, 0);
    g_shutdown_config.profile_names[0] = g_shutdown_profiles[0].config_name_098;
    g_shutdown_config.profile_names[1] = g_shutdown_profiles[1].config_name_098;
    g_shutdown_config.save();
}
}
