#include "DirectSound.hpp"

namespace th105 {

struct SoundHandleRecord {
    unsigned unknown_00;
    DirectSoundBuffer8 *buffer_04;
};

struct SoundHandleLookupResult {
    SoundHandleRecord *record_00;
};

struct SoundHandleManagerView {
    SoundHandleLookupResult *lookup(unsigned handle);
};

struct SoundVolumeService {
    unsigned char reserved_000[0x64];
    SoundHandleManagerView handles_064;

    void dispatch_wave_handle(unsigned handle);
};

void SoundVolumeService::dispatch_wave_handle(unsigned handle)
{
    if (handle == 0)
        return;

    SoundHandleRecord *record = handles_064.lookup(handle)->record_00;
    if (record->buffer_04 == 0)
        return;

    ULong status;
    record->buffer_04->get_status(&status);
    if ((status & 1) != 0)
        record->buffer_04->stop();
    if (record->buffer_04 == 0)
        return;
    record->buffer_04->set_current_position(0);
    if (record->buffer_04 == 0)
        return;
    record->buffer_04->play(0, 0, 0);
}

} // namespace th105
