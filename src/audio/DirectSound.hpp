#pragma once

namespace th105 {

typedef long HResult;
typedef unsigned long ULong;

struct Guid {
    unsigned long data1;
    unsigned short data2;
    unsigned short data3;
    unsigned char data4[8];
};

struct UnknownInterface {
    virtual HResult __stdcall query_interface(const Guid *interface_id, void **object) = 0;
    virtual ULong __stdcall add_ref() = 0;
    virtual ULong __stdcall release() = 0;
};

struct DirectSoundBufferDescription;
struct OggDataSource;
struct DirectSoundBuffer : UnknownInterface {};
struct DirectSoundBuffer8 : UnknownInterface {};
struct DirectSound3DListener8 : UnknownInterface {};

struct DirectSound8 : UnknownInterface {
    virtual HResult __stdcall create_sound_buffer(
        const DirectSoundBufferDescription *description,
        DirectSoundBuffer **buffer,
        UnknownInterface *outer_unknown) = 0;
};

struct DirectSoundGlobals {
    DirectSoundBuffer8 *primary_sound_buffer;
    DirectSound8 *direct_sound;
    DirectSound3DListener8 *direct_sound_listener;
};

extern DirectSoundGlobals g_direct_sound_globals;

void shutdown_direct_sound();
HResult __stdcall create_secondary_buffer8(
    const DirectSoundBufferDescription *description,
    DirectSoundBuffer8 **buffer);
int __stdcall linear_gain_to_ds_volume(float gain);
int __cdecl close_ogg_data_source(void *data_source);
long __cdecl tell_ogg_data_source(void *data_source);
unsigned long __stdcall decode_ogg_pcm_block(
    OggDataSource *source,
    void *pcm_buffer);

} // namespace th105
