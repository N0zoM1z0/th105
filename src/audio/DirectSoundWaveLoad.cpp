#include "audio/WaveData.hpp"
#include "audio/DirectSound.hpp"
#include <stdlib.h>
#include <string.h>

namespace th105 {
// Current dispatcher takes output in ECX, path in EDX and no stack args.
extern "C" bool __fastcall dispatch_wave_resource(WaveData *, const char *);
extern "C" __declspec(dllimport) int __stdcall MessageBoxA(
    void *, const char *, const char *, unsigned);
extern "C" const char direct_sound_lock_error[];
extern const char sound_error_title[];
struct DirectSoundWaveResource {
    virtual bool initialize(const void *, unsigned);
    virtual ~DirectSoundWaveResource();
    DirectSoundBuffer8 *buffer_04;
    unsigned size_08;
    bool load(const char *path);
};

bool DirectSoundWaveResource::load(const char *path)
{
    if (buffer_04 != 0) {
        buffer_04->release();
        buffer_04 = 0;
    }
    WaveData wave;
    if (!dispatch_wave_resource(&wave, path))
        return false;
    size_08 = wave.data_size_18;
    if (!initialize(&wave.format_00, wave.data_size_18))
        return false;
    void *audio1, *audio2;
    ULong bytes1, bytes2;
    if (buffer_04->lock(0, size_08, &audio1, &bytes1, &audio2, &bytes2, 2) < 0) {
        MessageBoxA(0, direct_sound_lock_error, sound_error_title, 0);
        return false;
    }
    memcpy(audio1, wave.data_14, size_08);
    buffer_04->unlock(audio1, bytes1, audio2, bytes2);
    return true;
}
}
