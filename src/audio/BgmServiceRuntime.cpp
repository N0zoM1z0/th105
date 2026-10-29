#include "audio/DirectSound.hpp"
#include "engine/CriticalSectionWrapper.hpp"
#include <vector>
#include <list>
#include <math.h>
#pragma function(log10)


#include <stddef.h>

extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime(void);

namespace th105 {

struct BgmStreamView {
    unsigned char reserved_00[0x1c];
    int state_1c;
    unsigned char active_20;
    unsigned char reserved_21[0x07];
    DirectSoundBuffer8 *buffer_28;
    unsigned char reserved_2c[0x1320];
    unsigned int scheduled_time_134c;
    unsigned int transition_time_1350;
    int transition_duration_1354;
    float gain_1358;
    float start_gain_135c;
    float target_gain_1360;
    float master_gain_1364;
    unsigned char transition_flag_1368;

    void transition(int value_a, float level, int value_b, int duration);
};

struct BgmHandleManagerView {
    unsigned char prefix_00[4];
    std::vector<BgmStreamView *> slots_04;
    std::vector<unsigned> generations_14;
    std::list<unsigned> free_slots_24;
    unsigned generation_30;
    CriticalSectionWrapper lock_34;
    BgmStreamView *lookup(int handle);
};
typedef char BgmManagerSize[sizeof(BgmHandleManagerView)==0x50?1:-1];
struct BgmLookupLock {
    CriticalSectionWrapper *lock;
    BgmLookupLock(CriticalSectionWrapper *p):lock(p) {EnterCriticalSection(&lock->critical_section_04);}
    ~BgmLookupLock() {LeaveCriticalSection(&lock->critical_section_04);}
};
BgmStreamView *BgmHandleManagerView::lookup(int handle) {
    BgmLookupLock guard(&lock_34);
    unsigned short slot=static_cast<unsigned short>(handle);
    if(generations_14.size()<=slot || generations_14[slot]!=(static_cast<unsigned>(handle)>>16))return 0;
    return slots_04.at(slot);
}
extern const float bgm_minimum_gain;
extern const float bgm_logarithmic_scale;
extern const float bgm_volume_units;
// Genuine natural gain provider for this isolated context; not a new exact claim.
// The native418990 gain provider remains independently nonexact.
int __stdcall bgm_transition_gain(float gain) {
    gain=static_cast<float>(log10(static_cast<double>(gain)));
    int volume=static_cast<int>(bgm_volume_units*bgm_logarithmic_scale*gain);
    if(volume < -10000)return -10000;
    if(volume > 0)return 0;
    return volume;
}
void BgmStreamView::transition(int delay, float level, int flag, int duration) {
    if(duration<=0) {
        gain_1358=level;
        float effective=level*master_gain_1364;
        int volume;
        // Native FCOMP tests only CF: unordered values take the gain-provider path.
        if(effective <= bgm_minimum_gain)volume=-10000;
        else volume=bgm_transition_gain(effective);
        if(buffer_28)buffer_28->set_volume(volume);
    } else {
        transition_time_1350=timeGetTime()+delay;
        start_gain_135c=gain_1358;
        transition_duration_1354=duration;
        target_gain_1360=level;
        transition_flag_1368=static_cast<unsigned char>(flag);
    }
}

struct BgmServiceView {
    unsigned char reserved_00[0x20];
    Win32CriticalSection24 lock_20;
    BgmHandleManagerView handles_38;

    void schedule_or_start(int handle, int delay);
    void stop(int handle);
    void fade(int handle, int duration, int target, int enabled);
    void set_level(int handle, int first, int unused, float value);
};

void BgmServiceView::schedule_or_start(int handle, int delay)
{
    EnterCriticalSection(&lock_20);
    BgmStreamView *stream = handles_38.lookup(handle);
    if (stream != 0) {
        stream->state_1c = 0;
        if (delay != 0) {
            stream->scheduled_time_134c = timeGetTime() + delay;
            LeaveCriticalSection(&lock_20);
            return;
        }
        if (stream->active_20 != 0) {
            stream->scheduled_time_134c = 0;
            if (stream->buffer_28 != 0)
                stream->buffer_28->play(0, 0, 1);
        } else {
            stream->scheduled_time_134c = timeGetTime();
        }
    }
    LeaveCriticalSection(&lock_20);
}

void BgmServiceView::stop(int handle)
{
    EnterCriticalSection(&lock_20);
    BgmStreamView *stream = handles_38.lookup(handle);
    if (stream != 0) {
        stream->state_1c = 3;
        if (stream->active_20 != 0 && stream->buffer_28 != 0) {
            ULong status;
            stream->buffer_28->get_status(&status);
            if ((status & 1) != 0)
                stream->buffer_28->stop();
        }
    }
    LeaveCriticalSection(&lock_20);
}

void BgmServiceView::fade(
    int handle,
    int duration,
    int target,
    int enabled)
{
    EnterCriticalSection(&lock_20);
    BgmStreamView *stream = handles_38.lookup(handle);
    if (stream != 0)
        stream->transition(target, 0.0f, enabled, duration);
    LeaveCriticalSection(&lock_20);
}

void BgmServiceView::set_level(
    int handle,
    int first,
    int unused,
    float value)
{
    EnterCriticalSection(&lock_20);
    BgmStreamView *stream = handles_38.lookup(handle);
    if (stream != 0)
        stream->transition(unused, value, 0, first);
    LeaveCriticalSection(&lock_20);
}

typedef char BgmServiceLockOffset[
    offsetof(BgmServiceView, lock_20) == 0x20 ? 1 : -1];
typedef char BgmServiceHandlesOffset[
    offsetof(BgmServiceView, handles_38) == 0x38 ? 1 : -1];
typedef char BgmStreamStateOffset[
    offsetof(BgmStreamView, state_1c) == 0x1c ? 1 : -1];
typedef char BgmStreamBufferOffset[
    offsetof(BgmStreamView, buffer_28) == 0x28 ? 1 : -1];
typedef char BgmStreamScheduledTimeOffset[
    offsetof(BgmStreamView, scheduled_time_134c) == 0x134c ? 1 : -1];

} // namespace th105
