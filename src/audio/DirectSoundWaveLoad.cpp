#include "audio/DirectSound.hpp"
#include <stdlib.h>
#include <string.h>

namespace th105 {
struct OwnedWaveFormat {
    unsigned short format_tag, channels;
    unsigned samples_per_second, average_bytes_per_second;
    unsigned short block_align, bits_per_sample, extra_size;
};
struct OwnedWaveData {
    OwnedWaveFormat format;
    unsigned char *data;
    unsigned size;
    OwnedWaveData() : data(0), size(0) {}
    ~OwnedWaveData() { if (data != 0) free(data); }
};
typedef char OwnedWaveData_size[sizeof(OwnedWaveData)==0x1c?1:-1];
// Current dispatcher takes output in ECX, path in EDX and no stack args.
extern "C" bool __fastcall dispatch_wave_resource(OwnedWaveData *, const char *);
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
    OwnedWaveData wave;
    if (!dispatch_wave_resource(&wave, path))
        return false;
    size_08 = wave.size;
    if (!initialize(&wave.format, wave.size))
        return false;
    void *audio1, *audio2;
    ULong bytes1, bytes2;
    if (buffer_04->lock(0, size_08, &audio1, &bytes1, &audio2, &bytes2, 2) < 0) {
        MessageBoxA(0, direct_sound_lock_error, sound_error_title, 0);
        return false;
    }
    memcpy(audio1, wave.data, size_08);
    buffer_04->unlock(audio1, bytes1, audio2, bytes2);
    return true;
}
}
