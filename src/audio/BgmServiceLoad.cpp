// Actual stream providers and checked handle lookup used by service4036E0.
#include "audio/BgmStreamRuntime.cpp"
#include "audio/BgmHandleResult.hpp"
#include "engine/CriticalSectionWrapper.hpp"
#include <list>
namespace th105 {
extern "C" __declspec(dllimport) int __stdcall SetEvent(void *);
struct BgmLoadLookupLock {
    CriticalSectionWrapper *lock;
    BgmLoadLookupLock(CriticalSectionWrapper *p):lock(p) { EnterCriticalSection(&lock->critical_section_04); }
    ~BgmLoadLookupLock() { LeaveCriticalSection(&lock->critical_section_04); }
};
struct BgmLoadManagerView {
    unsigned unknown_00;
    std::vector<BgmStreamRuntime *> streams_04;
    std::vector<unsigned> generations_14;
    std::list<unsigned> free_24;
    unsigned generation_30;
    CriticalSectionWrapper lock_34;
    BgmStreamRuntime *lookup(unsigned handle);
};
BgmStreamRuntime *BgmLoadManagerView::lookup(unsigned handle)
{
    BgmLoadLookupLock guard(&lock_34);
    unsigned short slot = static_cast<unsigned short>(handle);
    if (generations_14.size() <= slot || generations_14[slot] != (handle >> 16)) return 0;
    return streams_04.at(slot);
}
struct BgmLoadServiceView {
    unsigned char threads_00[0x10];
    void *playback_event_10, *loading_event_14;
    bool running_18;
    CriticalSectionWrapper lock_1c;
    BgmLoadManagerView manager_38;
    std::list<BgmHandleResult> active_88, pending_94, retired_a0;
    float gain_ac, gain_b0;
    bool play(BgmHandleResult handle, const char *path, bool queued, float gain);
    void set_master_gain(float gain);
};
typedef char LoadManagerSize[sizeof(BgmLoadManagerView)==0x50?1:-1];
typedef char LoadServiceActive[offsetof(BgmLoadServiceView,active_88)==0x88?1:-1];
void BgmStreamRuntime::prepare(std::string path, float master, float gain)
{
    active_20 = false;
    name_00 = path;
    gain_1358 = gain;
    state_1c = 3;
    master_1364 = master;
    flag_1368 = false;
    transition_1350 = 0;
    target_1360 = gain;
    duration_1354 = 0;
    start_135c = gain;
    next_136c = 0;
}
bool BgmLoadServiceView::play(BgmHandleResult handle, const char *path, bool queued, float gain)
{
    BgmStreamRuntime *stream = manager_38.lookup(handle.value);
    if (stream) {
        stream->prepare(path, gain_ac * gain_b0, gain);
        if (queued) {
            pending_94.push_front(handle);
            SetEvent(loading_event_14);
            return true;
        }
        if (stream->start()) {
            EnterCriticalSection(&lock_1c.critical_section_04);
            active_88.push_back(handle);
            LeaveCriticalSection(&lock_1c.critical_section_04);
            return true;
        }
        retired_a0.push_back(handle);
        SetEvent(loading_event_14);
    }
    return true;
}
}

namespace th105 {
void BgmLoadServiceView::set_master_gain(float gain)
{
    if (gain < 0.0f) gain = 0.0f;
    else if (gain > 1.0f) gain = 1.0f;
    gain_ac = gain;
    EnterCriticalSection(&lock_1c.critical_section_04);
    for (std::list<BgmHandleResult>::iterator it = active_88.begin(); it != active_88.end(); ++it) {
        BgmStreamRuntime *stream = manager_38.lookup(it->value);
        if (stream) {
            float master = gain_ac * gain_b0;
            stream->master_1364 = master;
            if (stream->active_20) {
                float effective = master * stream->gain_1358;
                long volume = effective <= bgm_minimum_gain ? -10000 : linear_gain_to_ds_volume(effective);
                stream->buffer_24.set_volume(volume);
            }
        }
    }
    LeaveCriticalSection(&lock_1c.critical_section_04);
}
}
