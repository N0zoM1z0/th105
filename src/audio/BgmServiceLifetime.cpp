#include "platform/BattleThreadHandleRuntime.cpp"
#include "audio/BgmStreamAllocation.cpp"
// Native4032F0/4033C0 own the service at7026E0. This models its natural
// B4-byte member extent, not the following four-byte linker alignment gap.
// Gains are initialized by the separate service initialization routine.
namespace th105 {
struct BgmServiceLifetime {
    BattleThreadHandle playback_thread_00;
    BattleThreadHandle loading_thread_08;
    void *playback_event_10;
    void *loading_event_14;
    bool running_18;
    CriticalSectionWrapper critical_1c;
    BgmAllocationManager50 manager_38;
    // Queues contain allocated slot/generation tokens, unlike free index slots.
    std::list<BgmHandleResult> active_88;
    std::list<BgmHandleResult> pending_94;
    std::list<BgmHandleResult> retired_a0;
    float gain_ac;
    float gain_b0;
    BgmServiceLifetime();
    ~BgmServiceLifetime();
    void shutdown();
};
BgmServiceLifetime::BgmServiceLifetime()
{
    playback_event_10 = 0;
    loading_event_14 = 0;
    running_18 = false;
}
BgmServiceLifetime::~BgmServiceLifetime() {}
BgmServiceLifetime g_bgm_service_lifetime;
typedef char BgmServiceTokenSize[sizeof(BgmHandleResult)==4?1:-1];
typedef char BgmServiceSize[sizeof(BgmServiceLifetime)==0xb4?1:-1];
typedef char BgmServiceLock[offsetof(BgmServiceLifetime,critical_1c)==0x1c?1:-1];
typedef char BgmServiceManager[offsetof(BgmServiceLifetime,manager_38)==0x38?1:-1];
typedef char BgmServiceActive[offsetof(BgmServiceLifetime,active_88)==0x88?1:-1];
typedef char BgmServicePending[offsetof(BgmServiceLifetime,pending_94)==0x94?1:-1];
typedef char BgmServiceRetired[offsetof(BgmServiceLifetime,retired_a0)==0xa0?1:-1];
typedef char BgmServiceGain[offsetof(BgmServiceLifetime,gain_ac)==0xac?1:-1];
}

namespace th105 {
extern "C" __declspec(dllimport) int __stdcall SetEvent(void *);
void BgmServiceLifetime::shutdown()
{
    running_18 = false;
    if (loading_event_14) SetEvent(loading_event_14);
    playback_thread_00.wait_for_exit();
    loading_thread_08.wait_for_exit();
    if (playback_event_10) { CloseHandle(playback_event_10); playback_event_10 = 0; }
    if (loading_event_14) { CloseHandle(loading_event_14); loading_event_14 = 0; }
    for (std::list<BgmHandleResult>::iterator it = active_88.begin(); it != active_88.end(); ++it)
        manager_38.release(it->value);
    for (std::list<BgmHandleResult>::iterator it = pending_94.begin(); it != pending_94.end(); ++it)
        manager_38.release(it->value);
    for (std::list<BgmHandleResult>::iterator it = retired_a0.begin(); it != retired_a0.end(); ++it)
        manager_38.release(it->value);
    active_88.clear();
    pending_94.clear();
    retired_a0.clear();
}
}
