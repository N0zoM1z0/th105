// Complete graphics singleton worker, including the target-pinned catch(int).
// Nonexact frame-state/register residuals: docs/APPLICATION_GRAPHICS_WORKER_2026_10_16.md.
#include "platform/ApplicationStartupOptions.hpp"
#include "engine/RenderModeManager.hpp"
#include "engine/SceneBase.hpp"

namespace th105 {
extern "C" __declspec(dllimport) void *__stdcall CreateEventA(void *, int, int, const char *);
extern "C" __declspec(dllimport) int __stdcall CloseHandle(void *);
extern "C" __declspec(dllimport) unsigned long __stdcall WaitForSingleObject(void *, unsigned long);

struct GraphicsWorkerFade {
    virtual bool initialize();
    virtual void shutdown();
    virtual bool update();
    virtual bool is_ready();
    virtual bool render();
};
struct ApplicationGraphicsView {
    void *window_00, *instance_04;
    ApplicationStartupOptions options_08;
    unsigned char unknown_030[0x14];
    unsigned rendered_044, presented_048;
    bool running_04c;
    unsigned char unknown_04d[0x13];
    void *event_060;
    unsigned char unknown_064[0x14];
    GraphicsWorkerFade *fade_078;
    IScene *previous_scene_07c;
    unsigned char unknown_080[0x14];
    CriticalSectionWrapper scene_lock_094;
};
extern ApplicationGraphicsView g_application_graphics;

extern "C" void __cdecl application_graphics_worker()
{
    ApplicationGraphicsView &self = g_application_graphics;
    self.event_060 = CreateEventA(0, 0, 0, 0);
    try {
        if (self.options_08.graphics_flag_25) {
            bool wait = false;
            while (self.running_04c) {
                if (TryEnterCriticalSection(&self.scene_lock_094.critical_section_04) > 0) {
                    bool rendered = false;
                    if (self.previous_scene_07c) {
                        rendered = self.previous_scene_07c->render();
                        if (rendered && self.fade_078)
                            rendered = self.fade_078->render();
                    }
                    if (rendered) {
                        present_d3d_frame();
                        ++self.rendered_044;
                    } else {
                        wait = true;
                    }
                    LeaveCriticalSection(&self.scene_lock_094.critical_section_04);
                    if (!wait)
                        continue;
                }
                WaitForSingleObject(self.event_060, 1);
                wait = false;
            }
        } else {
            void *pause_event = CreateEventA(0, 0, 0, 0);
            WaitForSingleObject(self.event_060, 0xffffffffu);
            while (self.running_04c) {
                for (int attempt = 0; attempt < 16; ++attempt) {
                    if (g_render_mode_manager.reset_flag_2a
                            && TryEnterCriticalSection(&g_d3d_backend.critical_section_000.critical_section_04) > 0) {
                        if (g_d3d_backend.swap_chain_024->Present(0, 0, 0, 0, 1) != 0) {
                            LeaveCriticalSection(&g_d3d_backend.critical_section_000.critical_section_04);
                        } else {
                            g_render_mode_manager.reset_flag_2a = 0;
                            LeaveCriticalSection(&g_d3d_backend.critical_section_000.critical_section_04);
                            ++self.presented_048;
                            break;
                        }
                    }
                    WaitForSingleObject(pause_event, 1);
                }
                WaitForSingleObject(self.event_060, 0xffffffffu);
            }
            CloseHandle(pause_event);
        }
    } catch (int) {
        self.running_04c = false;
    }
    CloseHandle(self.event_060);
}
typedef char GraphicsWorkerOptionsOffset[offsetof(ApplicationGraphicsView, options_08) == 8 ? 1 : -1];
typedef char GraphicsWorkerRenderCountOffset[offsetof(ApplicationGraphicsView, rendered_044) == 0x44 ? 1 : -1];
typedef char GraphicsWorkerRunOffset[offsetof(ApplicationGraphicsView, running_04c) == 0x4c ? 1 : -1];
typedef char GraphicsWorkerEventOffset[offsetof(ApplicationGraphicsView, event_060) == 0x60 ? 1 : -1];
typedef char GraphicsWorkerSceneOffset[offsetof(ApplicationGraphicsView, previous_scene_07c) == 0x7c ? 1 : -1];
typedef char GraphicsWorkerLockOffset[offsetof(ApplicationGraphicsView, scene_lock_094) == 0x94 ? 1 : -1];
} // namespace th105
