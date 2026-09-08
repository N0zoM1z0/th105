#include "DirectSound.hpp"

#include <windows.h>
#include <stddef.h>

namespace th105 {

struct BgmStreamView {
    unsigned char reserved_00[0x1c];
    int state_1c;
    unsigned char active_20;
    unsigned char reserved_21[0x07];
    DirectSoundBuffer8 *buffer_28;
    unsigned char reserved_2c[0x1320];
    unsigned int scheduled_time_134c;

    void transition(int value_a, float level, int value_b, int duration);
};

struct BgmHandleManagerView {
    BgmStreamView *lookup(int handle);
};

struct BgmServiceView {
    unsigned char reserved_00[0x20];
    CRITICAL_SECTION lock_20;
    BgmHandleManagerView handles_38;

    void schedule_or_start(int handle, int delay);
    void stop(int handle);
    void fade(int handle, int duration, int target, bool enabled);
    void set_level(int handle, int first, int unused, float value);
};

void BgmServiceView::schedule_or_start(int handle, int delay)
{
    EnterCriticalSection(&lock_20);
    BgmStreamView *stream = handles_38.lookup(handle);
    if (stream != 0) {
        stream->state_1c = 0;
        if (delay != 0) {
            stream->scheduled_time_134c = GetTickCount() + delay;
            LeaveCriticalSection(&lock_20);
            return;
        }
        if (stream->active_20 != 0) {
            stream->scheduled_time_134c = 0;
            if (stream->buffer_28 != 0)
                stream->buffer_28->play(0, 0, 1);
        } else {
            stream->scheduled_time_134c = GetTickCount();
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
    bool enabled)
{
    EnterCriticalSection(&lock_20);
    BgmStreamView *stream = handles_38.lookup(handle);
    if (stream != 0)
        stream->transition(target, 0.0f, enabled ? 1 : 0, duration);
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
