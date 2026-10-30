#include "platform/ApplicationStartupOptions.hpp"
#include "engine/D3DBackend.hpp"
#include "ui/ProfileImeRuntime.cpp"
namespace th105 {
extern "C" __declspec(dllimport) long __stdcall DefWindowProcA(void *,unsigned,unsigned,long);
extern "C" __declspec(dllimport) void __stdcall PostQuitMessage(int);
extern "C" __declspec(dllimport) int __stdcall ShowCursor(int);
void toggle_application_window_mode();
struct ApplicationWindowView {
    void *window_00, *instance_04;
    ApplicationStartupOptions options_08;
    unsigned char unreviewed_030[0x1c];
    bool running_04c;
    unsigned char unreviewed_04d[0x47];
    CriticalSectionWrapper scene_lock_094;
};
extern ApplicationWindowView g_application_window;
static bool __stdcall change_application_window_mode(ApplicationWindowView *owner,bool expected_fullscreen)
{
    bool was_fullscreen = !g_d3d_backend.presentation_158.windowed_20;
    if (!expected_fullscreen) {
        if (was_fullscreen) return false;
    } else if (!was_fullscreen) return false;
    EnterCriticalSection(&owner->scene_lock_094.critical_section_04);
    toggle_application_window_mode();
    LeaveCriticalSection(&owner->scene_lock_094.critical_section_04);
    if (owner->options_08.cursor_visible_24) {
        if (!was_fullscreen) {
            if (!g_d3d_backend.presentation_158.windowed_20) {
                ShowCursor(0); return false;
            }
        } else if (g_d3d_backend.presentation_158.windowed_20) {
            ShowCursor(1); return true;
        }
    }
    return !was_fullscreen;
}
long __stdcall dispatch_application_window_message(ApplicationWindowView *owner,
    void *window,unsigned message,unsigned wparam,long lparam)
{
    if (owner->options_08.ime_enabled_23 && process_ime_window_message(window,message,wparam,lparam))
        return 0;
    switch(message) {
    case 1: case 0x12: case 0x105: case 0x282: return 0;
    case 2:
        g_application_window.running_04c = false;
        PostQuitMessage(0);
        return 0;
    case 0x104:
        switch (wparam) {
        case 0x73:
            return DefWindowProcA(window,message,wparam,lparam);
        case 13:
            change_application_window_mode(owner,!g_d3d_backend.presentation_158.windowed_20);
            return 0;
        default:
            return 0;
        }
    case 0x112:
        if (wparam == 0xf140 || wparam == 0xf170) return 1;
        return DefWindowProcA(window,message,wparam,lparam);
    default:
        return DefWindowProcA(window,message,wparam,lparam);
    }
}
extern "C" long __stdcall application_window_proc(void *window,unsigned message,unsigned wparam,long lparam)
{
    return dispatch_application_window_message(&g_application_window,window,message,wparam,lparam);
}
typedef char WindowOptionsOffset[offsetof(ApplicationWindowView,options_08)==8?1:-1];
typedef char WindowRunningOffset[offsetof(ApplicationWindowView,running_04c)==0x4c?1:-1];
typedef char WindowSceneLockOffset[offsetof(ApplicationWindowView,scene_lock_094)==0x94?1:-1];
}
