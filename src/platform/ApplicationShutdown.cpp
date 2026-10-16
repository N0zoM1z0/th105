#include "platform/ApplicationStartupOptions.hpp"
#include "engine/RenderModeManager.hpp"
#include "engine/SceneBase.hpp"

struct HWND__;
namespace th105 {
extern "C" __declspec(dllimport) int __stdcall SetEvent(void *handle);
extern "C" __declspec(dllimport) void __stdcall CoUninitialize();
extern "C" int __stdcall ImmReleaseContext(HWND__ *window, void *context);
extern HWND__ *g_main_window;
struct ApplicationImePrefix { void *context_00; };
extern "C" ApplicationImePrefix g_application_ime_prefix;
void __cdecl shutdown_direct_sound();
void __cdecl shutdown_direct_input();
extern "C" void __stdcall remove_application_reset_listener(DeviceResetListener *listener);

struct ApplicationThread8 {
    void *handle_00;
    unsigned thread_id_04;
    void wait_for_exit();
};
// Observed callback teardown calls slot one, then releases storage with
// no destructor dispatch. The primary RTTI owner is CSceneManager and the
// secondary is CFade. These unconstructed prefix views emit no vtable.
struct ApplicationCallbackView {
    virtual void initialize();
    virtual void shutdown();
};
struct ApplicationShutdownView {
    void *window_00;
    void *instance_04;
    ApplicationStartupOptions options_08;
    unsigned char unknown_030[0x1c];
    bool running_04c;
    unsigned char unknown_04d[3];
    ApplicationThread8 control_thread_050;
    ApplicationThread8 graphics_thread_058;
    void *event_060;
    ApplicationThread8 worker_thread_064;
    ApplicationThread8 scene_thread_06c;
    ApplicationCallbackView *scene_manager_074;
    ApplicationCallbackView *fade_078;
    IScene *previous_scene_07c;
    IScene *current_scene_080;
    unsigned char unknown_084[0x0c];
    void *event_090;
    CriticalSectionWrapper scene_lock_094;

    void shutdown();
};
void ApplicationShutdownView::shutdown()
{
    running_04c = false;
    worker_thread_064.wait_for_exit();
    SetEvent(event_090);
    scene_thread_06c.wait_for_exit();
    SetEvent(event_060);
    graphics_thread_058.wait_for_exit();
    control_thread_050.wait_for_exit();
    EnterCriticalSection(&scene_lock_094.critical_section_04);
    if (previous_scene_07c) {
        delete previous_scene_07c;
        previous_scene_07c = 0;
    }
    if (current_scene_080) {
        delete current_scene_080;
        current_scene_080 = 0;
    }
    LeaveCriticalSection(&scene_lock_094.critical_section_04);
    scene_manager_074->shutdown();
    if (scene_manager_074) {
        delete scene_manager_074;
        scene_manager_074 = 0;
    }
    if (fade_078) {
        fade_078->shutdown();
        if (fade_078) {
            delete fade_078;
            fade_078 = 0;
        }
    }
    if (options_08.ime_enabled_23)
        ImmReleaseContext(g_main_window, g_application_ime_prefix.context_00);
    shutdown_direct_sound();
    shutdown_direct_input();
    remove_application_reset_listener(&g_render_mode_manager);
    shutdown_d3d_backend();
    CoUninitialize();
}
typedef char ApplicationShutdownOptionsOffset[offsetof(ApplicationShutdownView, options_08) == 8 ? 1 : -1];
typedef char ApplicationShutdownRunningOffset[offsetof(ApplicationShutdownView, running_04c) == 0x4c ? 1 : -1];
typedef char ApplicationShutdownThreadsOffset[offsetof(ApplicationShutdownView, worker_thread_064) == 0x64 ? 1 : -1];
typedef char ApplicationShutdownLockOffset[offsetof(ApplicationShutdownView, scene_lock_094) == 0x94 ? 1 : -1];
} // namespace th105
