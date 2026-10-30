#include "engine/CriticalSectionWrapper.hpp"
#include <list>
#include <stddef.h>

extern "C" __declspec(dllimport) unsigned long __stdcall WaitForSingleObject(
    void *, unsigned long);

namespace th105 {
struct BgmStreamLoadingView {
    bool start();
};
struct BgmLoadingManagerView {
    unsigned char observed_storage_00[0x50];
    BgmStreamLoadingView *lookup(unsigned handle);
    void release(unsigned handle);
};
// Only the worker's observed global fields; no invented service lifetime.
struct BgmLoadingServiceView {
    unsigned char workers_00[0x10];
    void *events_10[2];
    bool running_18;
    unsigned char unknown_19[7];
    Win32CriticalSection24 lock_20;
    BgmLoadingManagerView manager_38;
    std::list<unsigned> active_88;
    std::list<unsigned> pending_94;
    std::list<unsigned> retired_a0;
};
extern BgmLoadingServiceView g_bgm_service;

void run_bgm_loading_worker()
{
    while (g_bgm_service.running_18) {
        WaitForSingleObject(g_bgm_service.events_10[1], 0xffffffffUL);
        while (!g_bgm_service.pending_94.empty()) {
            WaitForSingleObject(g_bgm_service.events_10[1], 1);
            BgmStreamLoadingView *stream = g_bgm_service.manager_38.lookup(
                g_bgm_service.pending_94.front());
            if (stream) {
                if (stream->start()) {
                    EnterCriticalSection(&g_bgm_service.lock_20);
                    g_bgm_service.active_88.push_back(
                        g_bgm_service.pending_94.front());
                    LeaveCriticalSection(&g_bgm_service.lock_20);
                } else {
                    g_bgm_service.retired_a0.push_back(
                        g_bgm_service.pending_94.front());
                }
            }
            g_bgm_service.pending_94.pop_front();
        }
        while (!g_bgm_service.retired_a0.empty()) {
            WaitForSingleObject(g_bgm_service.events_10[1], 1);
            g_bgm_service.manager_38.release(g_bgm_service.retired_a0.front());
            g_bgm_service.retired_a0.pop_front();
        }
    }
}

typedef char BgmWorkerLockOffset[
    offsetof(BgmLoadingServiceView, lock_20) == 0x20 ? 1 : -1];
typedef char BgmWorkerManagerOffset[
    offsetof(BgmLoadingServiceView, manager_38) == 0x38 ? 1 : -1];
typedef char BgmWorkerPendingOffset[
    offsetof(BgmLoadingServiceView, pending_94) == 0x94 ? 1 : -1];
typedef char BgmWorkerRetiredOffset[
    offsetof(BgmLoadingServiceView, retired_a0) == 0xa0 ? 1 : -1];
}
