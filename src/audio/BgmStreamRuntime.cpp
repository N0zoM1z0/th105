// Complete BGM caller/provider reconstruction context; original class names/TUs unknown.
// OggStreamSource is a typed reader-prefix view. Its lifetime is not accepted here.
#include "assets/CsvFileLoading.cpp"
#include "audio/DirectSound.hpp"
#include "audio/OggDataSource.hpp"
namespace th105 {
struct OggStreamSource : FileReaderOwner {
    unsigned long stream_size;
    long position_adjustment;
    unsigned long unknown_0c;
    OggVorbisFile vorbis_file;
    VorbisInfo *vorbis_info;
    unsigned char unknown_2e4[0x1004];
    double loop_start;
    double loop_end;
    WaveFormat wave_format;

    OggStreamSource();
    ~OggStreamSource();
    bool open(const char *path);
    void load_sfl_metadata(const char *path);

};
}

// Shared DirectSound providers.
#include "audio/DirectSound.hpp"
#include <math.h>
#pragma function(log10)
namespace th105 {
static const Guid iid_direct_sound_buffer8 = {0x6825a449,0x7524,0x4d82,{0x92,0x0f,0x50,0xe3,0x6a,0xb3,0xab,0x1e}};
extern const float logarithmic_volume_scale, direct_sound_volume_units;
extern "C" const char create_sound_buffer_error[], direct_sound_error_title[];
extern "C" __declspec(dllimport) int __stdcall MessageBoxA(void *,const char *,const char *,unsigned);
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
    // The native result is rounded to float before scaling. Its unusual frame
    // and repeated stores do not justify invented aligned/volatile storage.
    float logarithmic_gain = static_cast<float>(log10(static_cast<double>(gain)));
    int volume = static_cast<int>(
        direct_sound_volume_units * logarithmic_volume_scale * logarithmic_gain);
    if (volume < -10000) {
        return -10000;
    }
    if (volume > 0) {
        return 0;
    }
    return volume;
}


}

// Observed DirectSound resource interface and initialization.
#include "audio/DirectSound.hpp"
#include <string.h>

namespace th105 {

struct DirectSound3DBuffer : UnknownInterface {
    virtual HResult __stdcall get_all_parameters(void *) = 0;
    virtual HResult __stdcall get_cone_angles(ULong *, ULong *) = 0;
    virtual HResult __stdcall get_cone_orientation(void *) = 0;
    virtual HResult __stdcall get_cone_outside_volume(long *) = 0;
    virtual HResult __stdcall get_max_distance(float *) = 0;
    virtual HResult __stdcall get_min_distance(float *) = 0;
    virtual HResult __stdcall get_mode(ULong *) = 0;
    virtual HResult __stdcall get_position(void *) = 0;
    virtual HResult __stdcall get_velocity(void *) = 0;
    virtual HResult __stdcall set_all_parameters(const void *, ULong) = 0;
    virtual HResult __stdcall set_cone_angles(ULong, ULong, ULong) = 0;
    virtual HResult __stdcall set_cone_orientation(float, float, float, ULong) = 0;
    virtual HResult __stdcall set_cone_outside_volume(long, ULong) = 0;
    virtual HResult __stdcall set_max_distance(float, ULong) = 0;
    virtual HResult __stdcall set_min_distance(float distance, ULong apply) = 0;
};

struct DirectSoundBufferDescription36 {
    ULong size;
    ULong flags;
    ULong buffer_bytes;
    ULong reserved;
    const void *format;
    Guid algorithm;
};

typedef char DirectSoundBufferDescription36_size[
    sizeof(DirectSoundBufferDescription36) == 36 ? 1 : -1];

extern "C" __declspec(dllimport) int __stdcall MessageBoxA(
    void *, const char *, const char *, unsigned);
extern "C" const char direct_sound_buffer8_acquire_error[];
extern "C" const char direct_sound_3d_buffer8_acquire_error[];
extern const Guid iid_direct_sound_3d_buffer;

class BgmBufferRuntime {
public:
    BgmBufferRuntime();
    virtual bool initialize(const void *source, unsigned size);
    virtual ~BgmBufferRuntime();

public:
    void clear();
    HResult stop_if_playing();
    void set_volume(long volume);
    bool load_raw(const void *source, unsigned bytes, const void *format);
    DirectSoundBuffer8 *resource_04;
    unsigned state_08;
};

class BgmSpatialBufferRuntime : public BgmBufferRuntime {
public:
    BgmSpatialBufferRuntime();
    virtual bool initialize(const void *source, unsigned size);
    virtual ~BgmSpatialBufferRuntime();

private:
    DirectSound3DBuffer *resource_0c;
};

bool BgmBufferRuntime::initialize(
    const void *format, unsigned buffer_bytes)
{
    DirectSoundBufferDescription36 description;
    memset(&description, 0, sizeof(description));
    description.size = sizeof(description);
    description.flags = 0x18088;
    description.buffer_bytes = buffer_bytes;
    description.format = format;
    if (create_secondary_buffer8(
            reinterpret_cast<const DirectSoundBufferDescription *>(&description),
            &resource_04) < 0) {
        MessageBoxA(0, direct_sound_buffer8_acquire_error,
                    "DSound-Error", 0);
        return false;
    }
    return true;
}

bool BgmSpatialBufferRuntime::initialize(
    const void *format, unsigned buffer_bytes)
{
    DirectSoundBufferDescription36 description;
    memset(&description, 0, sizeof(description));
    description.size = sizeof(description);
    description.flags = 0x58090;
    description.buffer_bytes = buffer_bytes;
    description.format = format;
    if (create_secondary_buffer8(
            reinterpret_cast<const DirectSoundBufferDescription *>(&description),
            &resource_04) < 0) {
        MessageBoxA(0, direct_sound_buffer8_acquire_error,
                    "DSound-Error", 0);
        return false;
    }
    if (resource_04->query_interface(
            &iid_direct_sound_3d_buffer,
            reinterpret_cast<void **>(&resource_0c)) < 0) {
        MessageBoxA(0, direct_sound_3d_buffer8_acquire_error,
                    "DSound-Error", 0);
        return false;
    }
    resource_0c->set_min_distance(3.0f, 1);
    return true;
}

BgmBufferRuntime::BgmBufferRuntime()
{
    resource_04 = 0;
    state_08 = 0;
}

BgmBufferRuntime::~BgmBufferRuntime()
{
    if (resource_04 != 0) {
        resource_04->release();
        resource_04 = 0;
    }
}

BgmSpatialBufferRuntime::BgmSpatialBufferRuntime()
{
    resource_04 = 0;
    resource_0c = 0;
}

BgmSpatialBufferRuntime::~BgmSpatialBufferRuntime()
{
    if (resource_0c != 0) {
        resource_0c->release();
        resource_0c = 0;
    }
    if (resource_04 != 0) {
        resource_04->release();
        resource_04 = 0;
    }
}

typedef char BgmBufferRuntime_size[
    sizeof(BgmBufferRuntime) == 0x0c ? 1 : -1];
typedef char BgmSpatialBufferRuntime_size[
    sizeof(BgmSpatialBufferRuntime) == 0x10 ? 1 : -1];

} // namespace th105

// Decoder callbacks and opening.
namespace th105 {
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

int __cdecl close_ogg_data_source(void *);
long __cdecl tell_ogg_data_source(void *);
OggCallbacks ogg_callbacks = {
    read_ogg_data_source,
    seek_ogg_data_source,
    close_ogg_data_source,
    tell_ogg_data_source
};

unsigned long __cdecl read_ogg_data_source(
    void *buffer,
    unsigned long item_size,
    unsigned long item_count,
    void *data_source)
{
    OggStreamSource *source = static_cast<OggStreamSource *>(data_source);
    source->reader->read(buffer, item_size * item_count);
    return source->reader->last_read_size();
}

int __cdecl seek_ogg_data_source(
    void *data_source,
    OggOffset offset,
    int origin)
{
    OggStreamSource *source = static_cast<OggStreamSource *>(data_source);
    long position;
    int reader_origin;

    switch (origin) {
    case 0:
        position = source->position_adjustment;
        reader_origin = 0;
        position += static_cast<long>(offset);
        break;
    case 1:
        position = static_cast<long>(offset);
        reader_origin = 1;
        break;
    case 2:
        position = source->position_adjustment + source->stream_size;
        reader_origin = 0;
        position += static_cast<long>(offset);
        break;
    default:
        return -1;
    }

    return source->reader->seek(position, reader_origin) == -1 ? -1 : 0;
}

int __cdecl close_ogg_data_source(void *data_source)
{
    OggStreamSource *source = static_cast<OggStreamSource *>(data_source);
    if (source->reader != 0) {
        delete source->reader;
    }
    source->reader = 0;
    return 0;
}

long __cdecl tell_ogg_data_source(void *data_source)
{
    OggStreamSource *source = static_cast<OggStreamSource *>(data_source);
    return source->reader->seek(0, 1) - source->position_adjustment;
}

bool OggStreamSource::open(const char *path)
{
    if (stream_size != 0) {
        if (reader != 0) {
            delete reader;
        }
        reader = 0;
        ov_clear(&vorbis_file);
        stream_size = 0;
    }

    if (!FileReaderOwner::open(path)) {
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
    load_sfl_metadata(path);
    return true;
}


}

// SFL loop metadata candidate.
#pragma float_control(precise,on,push)
#pragma fenv_access(on)
#pragma float_control(except,on)
#include "assets/FileReader.hpp"

#include <new>
#include <cstdlib>
#include <cstring>

namespace th105 {

void OggStreamSource::load_sfl_metadata(const char *audio_path)
{
    char metadata_path[260];
    strcpy_s(metadata_path, sizeof(metadata_path), audio_path);

    unsigned long path_length = std::strlen(audio_path);
    metadata_path[path_length - 3] = 's';
    metadata_path[path_length - 2] = 'f';
    metadata_path[path_length - 1] = 'l';

    FileReaderOwner file;
    if (file.open(metadata_path) && file.reader->size() != 0) {

    unsigned long size = file.reader->size();
    unsigned char *data = new unsigned char[size];
    file.reader->read(data, size);

    unsigned long cue_position = 0;
    unsigned long adtl_length = 0;
    for (int index = 0; index < static_cast<int>(size - 3); index++) {
        if (data[index] == 'c' &&
            data[index + 1] == 'u' &&
            data[index + 2] == 'e') {
            cue_position = *reinterpret_cast<unsigned long *>(
                data + index + 0x10);
        } else if (data[index] == 'a' &&
                   data[index + 1] == 'd' &&
                   data[index + 2] == 't' &&
                   data[index + 3] == 'l') {
            adtl_length = *reinterpret_cast<unsigned long *>(
                data + index + 0x10);
        }
    }

    if (cue_position > 0 && adtl_length > 0) {
        unsigned long sample_rate = wave_format.samples_per_second;
        loop_start =
            static_cast<double>(cue_position) / static_cast<double>(sample_rate);
        loop_end = static_cast<double>(cue_position + adtl_length) /
                           static_cast<double>(sample_rate);
    }

    std::free(data);
    }
}

} // namespace th105

#pragma fenv_access(off)
#pragma float_control(pop)

// PCM value-lifetime candidate.
#pragma float_control(precise,on,push)
#pragma fenv_access(on)
#include <string.h>
#include <stddef.h>

// Preserve the target's qword current_time materialization before either
// read-result path. Default FP keeps that value only in extended x87 state.
#pragma float_control(except, off, push)

namespace th105 {

extern "C" long __cdecl ov_read(
    OggVorbisFile *file,
    char *buffer,
    int length,
    int big_endian,
    int word_size,
    int signed_samples,
    int *bitstream);
extern "C" double __cdecl ov_time_tell(OggVorbisFile *file);
extern "C" int __cdecl ov_time_seek(OggVorbisFile *file, double position);

unsigned int __stdcall fill_ogg_pcm_block(
    OggStreamSource *source,
    void *destination)
{
    unsigned int total = 0;
    // ov_read owns this out-parameter; the target performs no initial store.
    int bitstream;
    char *output = static_cast<char *>(destination);

    for (;;) {
        // The target uses an unsigned JB when clamping the remaining count.
        unsigned int amount = 0x8000 - total;
        if (amount >= 0x1000)
            amount = 0x1000;
        int bytes_read = ov_read(
            &source->vorbis_file,
            output + total,
            amount,
            0,
            2,
            1,
            &bitstream);
        double current_time = ov_time_tell(&source->vorbis_file);
        if (bytes_read == 0) {
            if (source->loop_end == 0.0)
                break;
            ov_time_seek(&source->vorbis_file, 0.0);
        } else {
            if (source->loop_end > 0.0 && current_time > source->loop_end) {
                ov_time_seek(
                    &source->vorbis_file,
                    current_time - source->loop_end + source->loop_start);
            }
        }
        total += bytes_read;
        if (total >= 0x8000)
            return 0x8000;
    }

    memset(output + total, 0, 0x8000 - total);
    return total;
}

typedef char OggPcmFileOffset[
    offsetof(OggStreamSource, vorbis_file) == 0x10 ? 1 : -1];
typedef char OggPcmLoopStartOffset[
    offsetof(OggStreamSource, loop_start) == 0x12e8 ? 1 : -1];
typedef char OggPcmLoopEndOffset[
    offsetof(OggStreamSource, loop_end) == 0x12f0 ? 1 : -1];

} // namespace th105

#pragma float_control(pop)

#pragma fenv_access(off)
#pragma float_control(pop)

// Stream start, ring update and linked-stream handoff candidates.
#include "audio/DirectSound.hpp"
#include <string>
#include <cstring>
#include <stddef.h>
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime();
namespace th105 {
extern const float bgm_minimum_gain;
extern "C" const char wave_lock_error[], wave_error_title[];
extern "C" double __cdecl ov_time_tell(OggVorbisFile *);
extern "C" int __cdecl ov_time_seek(OggVorbisFile *, double);

void BgmBufferRuntime::clear()
{
    if (resource_04) {
        void *data;
        ULong bytes;
        resource_04->lock(0,0,&data,&bytes,0,0,2);
        memset(data,0,0);
        resource_04->unlock(data,bytes,0,0);
    }
}
HResult BgmBufferRuntime::stop_if_playing()
{
    if (resource_04) {
        ULong status;
        resource_04->get_status(&status);
        if (status & 1) return resource_04->stop();
    }
    return 0;
}
void BgmBufferRuntime::set_volume(long volume)
{
    if (resource_04) resource_04->set_volume(volume);
}
bool BgmBufferRuntime::load_raw(const void *source,unsigned bytes,const void *format)
{
    if(resource_04){resource_04->release();resource_04=0;}
    if(!initialize(format,bytes)){resource_04=0;return false;}
    if(source){
        void *first,*second; ULong first_size,second_size;
        if(resource_04->lock(0,bytes,&first,&first_size,&second,&second_size,2)<0) {
            MessageBoxA(0,wave_lock_error,wave_error_title,0);return false;
        }
        memcpy(first,source,first_size);
        memcpy(second,static_cast<const unsigned char *>(source)+first_size,second_size);
        resource_04->unlock(first,first_size,second,second_size);
    } else clear();
    state_08=bytes;
    return true;
}

struct BgmStreamRuntime {
    std::string name_00;
    int state_1c;
    bool active_20;
    BgmBufferRuntime buffer_24;
    OggStreamSource source_30;
    unsigned cursor_1340, previous_cursor_1344, eof_cursor_1348;
    unsigned scheduled_134c, transition_1350;
    int duration_1354;
    float gain_1358,start_135c,target_1360,master_1364;
    bool flag_1368;
    BgmStreamRuntime *next_136c,*previous_1370;
    unsigned unknown_1374;
    BgmStreamRuntime();
    ~BgmStreamRuntime();
    bool start();
    bool update();
    void handoff(BgmStreamRuntime *other);
};
typedef char StreamSize[sizeof(BgmStreamRuntime)==0x1378?1:-1];
typedef char StreamSource[offsetof(BgmStreamRuntime,source_30)==0x30?1:-1];
typedef char StreamCursor[offsetof(BgmStreamRuntime,cursor_1340)==0x1340?1:-1];
typedef char StreamGain[offsetof(BgmStreamRuntime,gain_1358)==0x1358?1:-1];

bool BgmStreamRuntime::start()
{
    if (!source_30.open(name_00.c_str())) return false;
    buffer_24.load_raw(0,0x100000,&source_30.wave_format);
    float effective=master_1364*gain_1358;
    long volume=effective<=bgm_minimum_gain?-10000:linear_gain_to_ds_volume(effective);
    buffer_24.set_volume(volume);
    if(buffer_24.resource_04) buffer_24.resource_04->set_current_position(0);
    previous_cursor_1344=0;
    cursor_1340=0;
    eof_cursor_1348=~0u;
    if(duration_1354) transition_1350=timeGetTime();
    active_20=true;
    if(state_1c==0) {
        if(scheduled_134c==0 || timeGetTime()>scheduled_134c) {
            scheduled_134c=0;
            if(next_136c) {handoff(next_136c);return true;}
            update();
            if(buffer_24.resource_04) buffer_24.resource_04->play(0,0,1);
        }
    } else update();
    return true;
}

bool BgmStreamRuntime::update()
{
    unsigned char samples[0x8000];
    if(!active_20) return false;
    ULong play,write;
    buffer_24.resource_04->get_current_position(&play,&write);
    if(eof_cursor_1348!=~0u) {
        if(play>eof_cursor_1348 &&
           play<cursor_1340+(static_cast<unsigned>(cursor_1340<previous_cursor_1344)<<20)) {
            buffer_24.stop_if_playing();
            return previous_1370==0;
        }
    } else {
        if(write>=previous_cursor_1344 &&
           write<cursor_1340+(static_cast<unsigned>(previous_cursor_1344>=cursor_1340)<<20)) {
            unsigned bytes=fill_ogg_pcm_block(&source_30,samples);
            if(bytes<0x8000) eof_cursor_1348=(bytes+previous_cursor_1344)&0xfffff;
            void *first,*second;
            ULong first_size,second_size;
            buffer_24.resource_04->lock(cursor_1340,0x8000,&first,&first_size,&second,&second_size,0);
            memcpy(first,samples,first_size);
            if(second) memcpy(second,samples+first_size,second_size);
            buffer_24.resource_04->unlock(first,first_size,second,second_size);
            previous_cursor_1344=cursor_1340;
            cursor_1340=(cursor_1340+0x8000)&0xfffff;
        }
    }
    if(scheduled_134c) {
        unsigned now=timeGetTime();
        if(now>scheduled_134c) {
            ULong status;
            buffer_24.resource_04->get_status(&status);
            if(!(status&1)) {
                if(buffer_24.resource_04) buffer_24.resource_04->play(0,0,1);
            }
            scheduled_134c=0;
            if(transition_1350<now) transition_1350=now;
        } else if(flag_1368 && previous_1370==0) {
            return true;
        }
        return false;
    }
    if(!duration_1354) return false;
    unsigned now=timeGetTime();
    if(now<=transition_1350) return false;
    float t=static_cast<float>(now-transition_1350)/duration_1354;
    if(t>=1.0f) {
        float level=target_1360;
        gain_1358=level;
        float effective=level*master_1364;
        buffer_24.set_volume(effective<=bgm_minimum_gain?-10000:linear_gain_to_ds_volume(effective));
        if(flag_1368) return previous_1370==0;
        duration_1354=0;
    } else if(t>0.0f) {
        float level=t*(target_1360-start_135c)+start_135c;
        gain_1358=level;
        float effective=level*master_1364;
        buffer_24.set_volume(effective<=bgm_minimum_gain?-10000:linear_gain_to_ds_volume(effective));
    }
    return false;
}

void BgmStreamRuntime::handoff(BgmStreamRuntime *other)
{
    unsigned char samples[0x8000];
    state_1c=0;
    if(!active_20) {
        next_136c=other;
        other->previous_1370=this;
        return;
    }
    buffer_24.stop_if_playing();
    buffer_24.clear();
    if(!other->active_20) return;
    ULong play=~0u,write=~0u;
    if(other->buffer_24.resource_04)
        other->buffer_24.resource_04->get_current_position(&play,&write);
    double time=ov_time_tell(&other->source_30.vorbis_file);
    previous_cursor_1344=other->previous_cursor_1344;
    cursor_1340=other->cursor_1340;
    eof_cursor_1348=other->eof_cursor_1348;
    int blocks=0;
    if(previous_cursor_1344<play) previous_cursor_1344+=0x100000;
    if(cursor_1340<play) cursor_1340+=0x100000;
    if(cursor_1340>play) {
        double step=32768.0/static_cast<double>(source_30.wave_format.average_bytes_per_second);
        do {
            previous_cursor_1344-=0x8000;
            cursor_1340-=0x8000;
            ++blocks;
            time-=step;
        } while(time>0.0 && cursor_1340>play);
    }
    if(previous_cursor_1344>0x100000) previous_cursor_1344+=0x100000;
    if(cursor_1340>0x100000) cursor_1340+=0x100000;
    ov_time_seek(&source_30.vorbis_file,time);
    while(blocks) {
        unsigned bytes=fill_ogg_pcm_block(&source_30,samples);
        if(bytes<0x8000) eof_cursor_1348=(bytes+previous_cursor_1344)&0xfffff;
        void *first,*second; ULong first_size,second_size;
        buffer_24.resource_04->lock(cursor_1340,0x8000,&first,&first_size,&second,&second_size,0);
        memcpy(first,samples,first_size);
        if(second) memcpy(second,samples+first_size,second_size);
        buffer_24.resource_04->unlock(first,first_size,second,second_size);
        previous_cursor_1344=cursor_1340;
        cursor_1340=(cursor_1340+0x8000)&0xfffff;
        --blocks;
    }
    if(buffer_24.resource_04) buffer_24.resource_04->play(0,0,1);
    ULong other_play=~0u,other_write=~0u;
    if(other->buffer_24.resource_04)
        other->buffer_24.resource_04->get_current_position(&other_play,&other_write);
    if(buffer_24.resource_04) buffer_24.resource_04->set_current_position(other_play);
    other->previous_1370=0;
}
}
