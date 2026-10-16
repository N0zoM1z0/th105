// Scene handoff and retirement use a real native checked list.
// Reproduce with cross-v106a-application-scene-lifecycle (VC8 LTCG).
#include "engine/SceneBase.hpp"
#include "engine/CriticalSectionWrapper.hpp"
#include <list>

namespace th105 {
extern "C" __declspec(dllimport) int __stdcall SetEvent(void *);
extern "C" __declspec(dllimport) long __stdcall CoInitialize(void *);
extern "C" __declspec(dllimport) void __stdcall CoUninitialize();
extern "C" __declspec(dllimport) void *__stdcall CreateEventA(void *, int, int, const char *);
extern "C" __declspec(dllimport) unsigned long __stdcall WaitForSingleObject(void *, unsigned long);
extern "C" __declspec(dllimport) int __stdcall CloseHandle(void *);
struct ApplicationSceneCommitView {
    unsigned char unreviewed_000[0x4c];
    bool running_04c;
    unsigned char unreviewed_04d[0x2f];
    IScene *previous_scene_07c;
    IScene *pending_scene_080;
    std::list<IScene *> retired_scenes_084;
    void *retired_event_090;
    CriticalSectionWrapper scene_lock_094;
    int requested_state_0b0, active_state_0b4;
};
extern ApplicationSceneCommitView g_application_scene_commit;

extern "C" void __cdecl application_commit_pending_scene()
{
    ApplicationSceneCommitView &self = g_application_scene_commit;
    if (!self.pending_scene_080)
        return;
    EnterCriticalSection(&self.scene_lock_094.critical_section_04);
    IScene *old_scene = self.previous_scene_07c;
    self.previous_scene_07c = self.pending_scene_080;
    self.pending_scene_080 = 0;
    LeaveCriticalSection(&self.scene_lock_094.critical_section_04);
    if (old_scene) {
        old_scene->on_scene_exit(self.requested_state_0b0);
        self.retired_scenes_084.push_back(old_scene);
        SetEvent(self.retired_event_090);
    }
    if (self.previous_scene_07c)
        self.previous_scene_07c->on_scene_enter(self.active_state_0b4);
    self.active_state_0b4 = self.requested_state_0b0;
}
extern "C" unsigned long __stdcall bootstrap_scene_thread(void *)
{
    ApplicationSceneCommitView &self = g_application_scene_commit;
    if (CoInitialize(0) >= 0) {
        self.retired_event_090 = CreateEventA(0, 0, 0, 0);
        while (self.running_04c) {
            WaitForSingleObject(self.retired_event_090, 0xffffffffu);
            while (!self.retired_scenes_084.empty()) {
                if (self.retired_scenes_084.front()) {
                    delete self.retired_scenes_084.front();
                    self.retired_scenes_084.front() = 0;
                }
                self.retired_scenes_084.pop_front();
            }
        }
        CoUninitialize();
        CloseHandle(self.retired_event_090);
    }
    return 0;
}
typedef char SceneCommitListSize[sizeof(std::list<IScene *>) == 12 ? 1 : -1];
typedef char SceneCommitPreviousOffset[offsetof(ApplicationSceneCommitView, previous_scene_07c) == 0x7c ? 1 : -1];
typedef char SceneCommitPendingOffset[offsetof(ApplicationSceneCommitView, pending_scene_080) == 0x80 ? 1 : -1];
typedef char SceneCommitQueueOffset[offsetof(ApplicationSceneCommitView, retired_scenes_084) == 0x84 ? 1 : -1];
typedef char SceneCommitEventOffset[offsetof(ApplicationSceneCommitView, retired_event_090) == 0x90 ? 1 : -1];
typedef char SceneCommitLockOffset[offsetof(ApplicationSceneCommitView, scene_lock_094) == 0x94 ? 1 : -1];
typedef char SceneCommitStateOffset[offsetof(ApplicationSceneCommitView, requested_state_0b0) == 0xb0 ? 1 : -1];
} // namespace th105
