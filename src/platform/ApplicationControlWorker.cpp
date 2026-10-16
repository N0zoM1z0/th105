// Complete singleton control loop; target/EH facts and residuals in
// docs/APPLICATION_CONTROL_WORKER_2026_10_16.md.
#include "platform/ApplicationStartupOptions.hpp"
#include "engine/RenderModeManager.hpp"
#include "engine/SceneBase.hpp"
#include "input/InputManager.hpp"
#include <float.h>
#include <string.h>

namespace th105 {
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime();
extern "C" __declspec(dllimport) int __cdecl wsprintfA(char *, const char *, ...);
extern "C" __declspec(dllimport) int __stdcall SetWindowTextA(void *, const char *);
extern "C" __declspec(dllimport) int __stdcall SetEvent(void *);
extern "C" __declspec(dllimport) void *__stdcall CreateThread(void *, unsigned long,
    unsigned long (__stdcall *)(void *), void *, unsigned long, unsigned long *);
extern "C" unsigned long __stdcall bootstrap_scene_creation_thread(void *);
extern "C" void __cdecl application_commit_pending_scene();
void *__cdecl create_audio_scheduler_listener_event();
int __stdcall wait_audio_scheduler_listener_event(void *);
int __stdcall remove_audio_scheduler_listener_event(void *);
extern const char control_fps_format[], control_fps_prefix[];

struct ControlInputDevice {
    virtual long __stdcall QueryInterface(const void *, void **) = 0;
    virtual unsigned long __stdcall AddRef() = 0;
    virtual unsigned long __stdcall Release() = 0;
    virtual long __stdcall GetCapabilities(void *) = 0;
    virtual long __stdcall EnumObjects(void *, void *, unsigned) = 0;
    virtual long __stdcall GetProperty(const void *, void *) = 0;
    virtual long __stdcall SetProperty(const void *, const void *) = 0;
    virtual long __stdcall Acquire() = 0;
    virtual long __stdcall Unacquire() = 0;
    virtual long __stdcall GetDeviceState(unsigned, void *) = 0;
};
struct ControlMouseState20 {
    long x, y, wheel;
    unsigned char buttons[8];
};
extern ControlMouseState20 g_control_mouse_state;
struct ControlThread8 {
    void *handle;
    unsigned long id;
    void wait_for_exit();
};
struct ControlSceneManager {
    virtual void initialize();
    virtual void shutdown();
    virtual void update();
    virtual unsigned char render();
    virtual IScene *create_scene(int);
};
struct ControlFade {
    virtual bool initialize();
    virtual void shutdown();
    virtual bool update();
    virtual bool is_ready();
    virtual bool render();
};
struct ApplicationControlView {
    void *window_00, *instance_04;
    ApplicationStartupOptions options_08;
    int control_fps_030, control_count_034;
    unsigned long timestamp_038;
    int render_fps_03c, present_fps_040, render_count_044, present_count_048;
    bool running_04c;
    unsigned char unknown_04d[3];
    ControlThread8 control_050, graphics_058;
    void *event_060;
    ControlThread8 scene_creation_064, scene_disposal_06c;
    ControlSceneManager *manager_074;
    ControlFade *fade_078;
    IScene *previous_scene_07c, *pending_scene_080;
    unsigned char unknown_084[0x10];
    CriticalSectionWrapper scene_lock_094;
    int requested_state_0b0, active_state_0b4;
};
extern ApplicationControlView g_application_control;

extern "C" void __cdecl application_control_worker()
{
    ApplicationControlView &self = g_application_control;
    char title[260];
    unsigned fp_state;
    void *listener = create_audio_scheduler_listener_event();
    _controlfp_s(&fp_state, 0, 0);
    _controlfp_s(&fp_state, _RC_UP, _MCW_RC);
    try {
        while (self.running_04c) {
            unsigned long previous_time = self.timestamp_038;
            if (timeGetTime() - previous_time >= 1000) {
                self.control_fps_030 = self.control_count_034;
                self.render_fps_03c = self.render_count_044;
                self.present_fps_040 = self.present_count_048;
                self.timestamp_038 = previous_time + 1000;
                self.control_count_034 = 0;
                self.render_count_044 = 0;
                self.present_count_048 = 0;
                if (self.options_08.flag_26) {
                    wsprintfA(title, control_fps_format, control_fps_prefix,
                        self.control_fps_030, self.render_fps_03c, self.present_fps_040);
                    SetWindowTextA(self.window_00, title);
                }
            }
            if (self.options_08.input_enabled_21) {
                poll_direct_input_gamepads();
                if (g_direct_input_backend.keyboard_device
                        && static_cast<ControlInputDevice *>(g_direct_input_backend.keyboard_device)->GetDeviceState(
                            sizeof(g_direct_input_backend.raw_keyboard_state), g_direct_input_backend.raw_keyboard_state) < 0) {
                    static_cast<ControlInputDevice *>(g_direct_input_backend.keyboard_device)->Acquire();
                    memset(g_direct_input_backend.raw_keyboard_state, 0, sizeof(g_direct_input_backend.raw_keyboard_state));
                }
                if (g_direct_input_backend.mouse_device
                        && static_cast<ControlInputDevice *>(g_direct_input_backend.mouse_device)->GetDeviceState(
                            sizeof(g_control_mouse_state), &g_control_mouse_state) < 0)
                    static_cast<ControlInputDevice *>(g_direct_input_backend.mouse_device)->Acquire();
            }
            self.manager_074->update();
            if (self.active_state_0b4 == self.requested_state_0b0) {
                if (self.fade_078)
                    self.fade_078->update();
                if (self.previous_scene_07c) {
                    self.requested_state_0b0 = self.previous_scene_07c->update();
                    if (self.requested_state_0b0 == -1) {
                        self.running_04c = false;
                        goto frame_pacing;
                    }
                    ++self.control_count_034;
                }
                if (self.requested_state_0b0 != self.active_state_0b4) {
                    self.scene_creation_064.wait_for_exit();
                    self.scene_creation_064.handle = CreateThread(0, 0,
                        bootstrap_scene_creation_thread, 0, 0, &self.scene_creation_064.id);
                }
            } else if (!self.fade_078 || self.fade_078->is_ready()) {
                application_commit_pending_scene();
            }
        frame_pacing:
            if (!self.options_08.graphics_flag_25) {
                if (!g_render_mode_manager.reset_flag_2a) {
                    EnterCriticalSection(&g_d3d_backend.critical_section_000.critical_section_04);
                    g_render_mode_manager.reset_flag_2a = 0;
                    LeaveCriticalSection(&g_d3d_backend.critical_section_000.critical_section_04);
                    unsigned char ready = 1;
                    if (self.previous_scene_07c)
                        ready &= static_cast<unsigned char>(self.previous_scene_07c->render());
                    else
                        ready = 0;
                    ready &= self.manager_074->render();
                    if (self.fade_078)
                        ready &= static_cast<unsigned char>(self.fade_078->render());
                    if (ready) {
                        EnterCriticalSection(&g_d3d_backend.critical_section_000.critical_section_04);
                        g_render_mode_manager.reset_flag_2a = 1;
                        LeaveCriticalSection(&g_d3d_backend.critical_section_000.critical_section_04);
                        if (present_d3d_frame()) {
                            ++self.render_count_044;
                            wait_audio_scheduler_listener_event(listener);
                            continue;
                        }
                        SetEvent(self.event_060);
                    }
                } else {
                    SetEvent(self.event_060);
                }
            }
            wait_audio_scheduler_listener_event(listener);
        }
    } catch (int) {
        self.running_04c = false;
    }
    _controlfp_s(&fp_state, _CW_DEFAULT, 0xffffffffu);
    remove_audio_scheduler_listener_event(listener);
}
typedef char ControlWorkerMouseSize[sizeof(ControlMouseState20) == 20 ? 1 : -1];
typedef char ControlWorkerTimestampOffset[offsetof(ApplicationControlView, timestamp_038) == 0x38 ? 1 : -1];
typedef char ControlWorkerRunningOffset[offsetof(ApplicationControlView, running_04c) == 0x4c ? 1 : -1];
typedef char ControlWorkerSceneThreadOffset[offsetof(ApplicationControlView, scene_creation_064) == 0x64 ? 1 : -1];
typedef char ControlWorkerManagerOffset[offsetof(ApplicationControlView, manager_074) == 0x74 ? 1 : -1];
typedef char ControlWorkerSceneOffset[offsetof(ApplicationControlView, previous_scene_07c) == 0x7c ? 1 : -1];
typedef char ControlWorkerStateOffset[offsetof(ApplicationControlView, requested_state_0b0) == 0xb0 ? 1 : -1];
} // namespace th105
