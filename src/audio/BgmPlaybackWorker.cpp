// JP1.06a403B90: active-stream polling and retirement policy.
// Ordinary source declarations retain, rather than fake, the unresolved
// native private EDI receiver used by BgmStreamRuntime::update.
#include "engine/CriticalSectionWrapper.hpp"
#include <list>
#include <stddef.h>
extern "C" __declspec(dllimport) unsigned long __stdcall WaitForSingleObject(void *,unsigned long);
extern "C" __declspec(dllimport) int __stdcall SetEvent(void *);
namespace th105 {
struct BgmPlaybackStreamView {
    bool update();
};
struct BgmPlaybackManagerView {
    unsigned char observed_storage_00[0x50];
    BgmPlaybackStreamView *lookup(unsigned handle);
};
// A pointer-only view of the independently observed global service fields.
// No construction, allocation extent or additional thread lifetime is claimed.
struct BgmPlaybackWorkerView {
    unsigned char workers_00[0x10];
    void *events_10[2];
    bool running_18;
    unsigned char unknown_19[7];
    Win32CriticalSection24 lock_20;
    BgmPlaybackManagerView manager_38;
    std::list<unsigned> active_88;
    std::list<unsigned> pending_94;
    std::list<unsigned> retired_a0;
};
extern BgmPlaybackWorkerView g_bgm_playback_worker_service;

void run_bgm_playback_worker()
{
    while (g_bgm_playback_worker_service.running_18) {
        WaitForSingleObject(g_bgm_playback_worker_service.events_10[0], 16);
        EnterCriticalSection(&g_bgm_playback_worker_service.lock_20);
        std::list<unsigned>::iterator current =
            g_bgm_playback_worker_service.active_88.begin();
        while (current != g_bgm_playback_worker_service.active_88.end()) {
            BgmPlaybackStreamView *stream =
                g_bgm_playback_worker_service.manager_38.lookup(*current);
            if (stream && stream->update()) {
                g_bgm_playback_worker_service.retired_a0.push_back(*current);
                current = g_bgm_playback_worker_service.active_88.erase(current);
                SetEvent(g_bgm_playback_worker_service.events_10[1]);
            } else {
                ++current;
            }
        }
        LeaveCriticalSection(&g_bgm_playback_worker_service.lock_20);
    }
}
typedef char BgmPlaybackEventOffset[offsetof(BgmPlaybackWorkerView,events_10)==0x10?1:-1];
typedef char BgmPlaybackRunningOffset[offsetof(BgmPlaybackWorkerView,running_18)==0x18?1:-1];
typedef char BgmPlaybackLockOffset[offsetof(BgmPlaybackWorkerView,lock_20)==0x20?1:-1];
typedef char BgmPlaybackManagerOffset[offsetof(BgmPlaybackWorkerView,manager_38)==0x38?1:-1];
typedef char BgmPlaybackActiveOffset[offsetof(BgmPlaybackWorkerView,active_88)==0x88?1:-1];
typedef char BgmPlaybackPendingOffset[offsetof(BgmPlaybackWorkerView,pending_94)==0x94?1:-1];
typedef char BgmPlaybackRetiredOffset[offsetof(BgmPlaybackWorkerView,retired_a0)==0xa0?1:-1];
}
