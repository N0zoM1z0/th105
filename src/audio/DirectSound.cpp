#include "DirectSound.hpp"
#include "OggDataSource.hpp"

#include <math.h>

#pragma function(log10)

extern "C" __declspec(dllimport) int __stdcall MessageBoxA(
    void *window,
    const char *text,
    const char *caption,
    unsigned type);

namespace th105 {

DirectSoundGlobals g_direct_sound_globals;

static const Guid iid_direct_sound_buffer8 = {
    0x6825a449,
    0x7524,
    0x4d82,
    {0x92, 0x0f, 0x50, 0xe3, 0x6a, 0xb3, 0xab, 0x1e}
};

static const char direct_sound_error_title[] = "DSound-Error";
static const char create_sound_buffer_error[] =
    "\x83\x65\x83\x93\x83\x7c\x83\x89\x83\x8a\x83\x6f\x83\x62\x83\x74"
    "\x83\x40\x82\xcc\x90\xb6\x90\xac\x82\xc9\x8e\xb8\x94\x73";

static volatile const float logarithmic_volume_scale = 33.220001220703125f;
static volatile const float direct_sound_volume_units = 100.0f;

typedef unsigned long (__cdecl *OggReadCallback)(
    void *buffer,
    unsigned long item_size,
    unsigned long item_count,
    void *data_source);
typedef int (__cdecl *OggSeekCallback)(
    void *data_source,
    OggOffset offset,
    int origin);

struct OggCallbacks {
    OggReadCallback read;
    OggSeekCallback seek;
    int (__cdecl *close)(void *data_source);
    long (__cdecl *tell)(void *data_source);
};

extern unsigned long __cdecl read_ogg_data_source(
    void *buffer,
    unsigned long item_size,
    unsigned long item_count,
    void *data_source);
extern int __cdecl seek_ogg_data_source(
    void *data_source,
    OggOffset offset,
    int origin);
extern "C" int __cdecl ov_clear(OggVorbisFile *file);
extern "C" int __cdecl ov_open_callbacks(
    void *data_source,
    OggVorbisFile *file,
    const char *initial_data,
    long initial_data_size,
    OggCallbacks callbacks);
extern "C" VorbisInfo *__cdecl ov_info(OggVorbisFile *file, int link);
extern void __cdecl initialize_ogg_audio(
    const char *path,
    OggDataSource *source);

static const OggCallbacks ogg_callbacks = {
    read_ogg_data_source,
    seek_ogg_data_source,
    close_ogg_data_source,
    tell_ogg_data_source
};

void shutdown_direct_sound()
{
    if (g_direct_sound_globals.direct_sound_listener != 0) {
        g_direct_sound_globals.direct_sound_listener->release();
        g_direct_sound_globals.direct_sound_listener = 0;
    }
    if (g_direct_sound_globals.primary_sound_buffer != 0) {
        g_direct_sound_globals.primary_sound_buffer->release();
        g_direct_sound_globals.primary_sound_buffer = 0;
    }
    if (g_direct_sound_globals.direct_sound != 0) {
        g_direct_sound_globals.direct_sound->release();
        g_direct_sound_globals.direct_sound = 0;
    }
}

HResult __stdcall create_secondary_buffer8(
    const DirectSoundBufferDescription *description,
    DirectSoundBuffer8 **buffer)
{
    DirectSoundBuffer *temporary_buffer = 0;
    HResult result = g_direct_sound_globals.direct_sound->create_sound_buffer(
        description,
        &temporary_buffer,
        0);
    if (result < 0) {
        MessageBoxA(0, create_sound_buffer_error, direct_sound_error_title, 0);
        return result;
    }

    result = temporary_buffer->query_interface(
        &iid_direct_sound_buffer8,
        reinterpret_cast<void **>(buffer));
    temporary_buffer->release();
    return result;
}

int __stdcall linear_gain_to_ds_volume(float gain)
{
    __declspec(align(64)) volatile unsigned char scratch[64];
    volatile float *logarithmic_gain =
        reinterpret_cast<volatile float *>(scratch + 60);
    *logarithmic_gain = static_cast<float>(log10(static_cast<double>(gain)));
    *logarithmic_gain = static_cast<float>(*logarithmic_gain);
    *logarithmic_gain = static_cast<float>(*logarithmic_gain);
    int volume = static_cast<int>(
        direct_sound_volume_units * logarithmic_volume_scale * *logarithmic_gain);
    if (volume < -10000) {
        return -10000;
    }
    if (volume > 0) {
        return 0;
    }
    return volume;
}

int __cdecl close_ogg_data_source(void *data_source)
{
    OggDataSource *source = static_cast<OggDataSource *>(data_source);
    if (source->reader != 0) {
        delete source->reader;
    }
    source->reader = 0;
    return 0;
}

long __cdecl tell_ogg_data_source(void *data_source)
{
    OggDataSource *source = static_cast<OggDataSource *>(data_source);
    return source->reader->seek(0, 1) - source->position_adjustment;
}

bool OggDataSource::open(const char *path)
{
    if (stream_size != 0) {
        if (reader != 0) {
            delete reader;
        }
        reader = 0;
        ov_clear(&vorbis_file);
        stream_size = 0;
    }

    if (!open_reader(path)) {
        return false;
    }

    stream_size = reader->size();
    position_adjustment = 0;
    if (ov_open_callbacks(this, &vorbis_file, 0, 0, ogg_callbacks) < 0) {
        if (reader != 0) {
            delete reader;
        }
        reader = 0;
        stream_size = 0;
        return false;
    }

    vorbis_info = ov_info(&vorbis_file, -1);
    wave_format.format_tag = 1;
    wave_format.channels = static_cast<unsigned short>(vorbis_info->channels);
    wave_format.samples_per_second = vorbis_info->sample_rate;
    loop_end = 0.0;
    loop_start = 0.0;
    wave_format.block_align = static_cast<unsigned short>(
        wave_format.channels * 16 / 8);
    wave_format.bits_per_sample = 16;
    wave_format.average_bytes_per_second =
        wave_format.block_align * wave_format.samples_per_second;
    wave_format.extra_size = 0;
    initialize_ogg_audio(path, this);
    return true;
}

} // namespace th105
