#include "AudioSchedulerRuntime.hpp"
#include <stddef.h>
namespace th105 {
extern "C" __declspec(dllimport) void *__stdcall CreateEventA(void *,int,int,const char *);
extern "C" __declspec(dllimport) void *__stdcall CreateThread(void *,unsigned long,
    unsigned long (__stdcall *)(void *),void *,unsigned long,unsigned long *);
extern "C" __declspec(dllimport) int __stdcall SetThreadPriority(void *,int);
extern "C" unsigned long __stdcall bgm_thread_one(void *);
extern "C" unsigned long __stdcall bgm_thread_two(void *);

// These are the same observed thread methods as BattleThreadHandleRuntime.cpp.
// Keeping their bodies visible models the native inlined starts, not a new ABI.
bool BattleThreadHandle::start(unsigned long (__stdcall *entry)(void *),void *parameter)
{
    wait_for_exit();
    handle_ = CreateThread(0,0,entry,parameter,0,&thread_id_);
    return handle_ != 0;
}
int BattleThreadHandle::set_priority(int priority)
{
    return SetThreadPriority(handle_,priority);
}
struct BgmServiceInitializeView {
    BattleThreadHandle workers_00[2];
    void *events_10[2];
    bool running_18;
    unsigned char unknown_19[0x93];
    float gain_ac;
    float gain_b0;
    void initialize();
};
typedef char BgmInitializeGain[offsetof(BgmServiceInitializeView,gain_ac)==0xac?1:-1];
void BgmServiceInitializeView::initialize()
{
    running_18 = true;
    events_10[0] = CreateEventA(0,0,0,0);
    events_10[1] = CreateEventA(0,0,0,0);
    workers_00[0].start(bgm_thread_one,0);
    workers_00[0].set_priority(15);
    workers_00[1].start(bgm_thread_two,0);
    gain_ac = gain_b0 = 1.0f;
}
}
