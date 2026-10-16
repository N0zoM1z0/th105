// Native application thread callbacks; docs/APPLICATION_THREAD_ENTRIES_2026_10_16.md.
#include <stddef.h>

extern "C" __declspec(dllimport) long __stdcall CoInitialize(void *);
extern "C" __declspec(dllimport) void __stdcall CoUninitialize();

namespace th105 {
extern "C" void __cdecl application_control_worker();
extern "C" void __cdecl application_graphics_worker();

extern "C" unsigned long __stdcall bootstrap_control_thread(void *)
{
    if (CoInitialize(0) >= 0) {
        application_control_worker();
        CoUninitialize();
    }
    return 0;
}

extern "C" unsigned long __stdcall bootstrap_graphics_thread(void *)
{
    if (CoInitialize(0) >= 0) {
        application_graphics_worker();
        CoUninitialize();
    }
    return 0;
}

class IScene;
struct ThreadSceneManagerView {
    virtual void initialize();
    virtual void shutdown();
    virtual void update();
    virtual unsigned char render();
    virtual IScene *create_scene(int);
};
struct ApplicationSceneCreationView {
    unsigned char unreviewed_000[0x74];
    ThreadSceneManagerView *manager_074;
    unsigned char unreviewed_078[8];
    IScene *pending_scene_080;
    unsigned char unreviewed_084[0x2c];
    int requested_state_0b0;
};
extern ApplicationSceneCreationView g_application_scene_creation;

extern "C" unsigned long __stdcall bootstrap_scene_creation_thread(void *)
{
    if (CoInitialize(0) >= 0) {
        g_application_scene_creation.pending_scene_080 =
            g_application_scene_creation.manager_074->create_scene(
                g_application_scene_creation.requested_state_0b0);
        CoUninitialize();
    }
    return 0;
}
typedef char SceneCreationManagerOffset[offsetof(ApplicationSceneCreationView, manager_074) == 0x74 ? 1 : -1];
typedef char SceneCreationPendingOffset[offsetof(ApplicationSceneCreationView, pending_scene_080) == 0x80 ? 1 : -1];
typedef char SceneCreationStateOffset[offsetof(ApplicationSceneCreationView, requested_state_0b0) == 0xb0 ? 1 : -1];
} // namespace th105
