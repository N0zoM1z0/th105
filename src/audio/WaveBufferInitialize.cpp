#include "audio/DirectSound.hpp"
#include <string.h>
#include <stddef.h>
namespace th105 {
#pragma pack(push,2)
struct WaveFormat18 {
    unsigned short format_tag, channels;
    unsigned samples_per_second, bytes_per_second;
    unsigned short block_align, bits_per_sample, extra_size;
};
#pragma pack(pop)
// Pointer-only resource prefix. Target4183B0/418610 have private EAX/EDI
// and ESI live-ins; these declarations retain ordinary C++ member contracts.
class WaveBufferView {
public:
    virtual bool initialize(const WaveFormat18 *, unsigned);
    virtual ~WaveBufferView();
    DirectSoundBuffer8 *resource_04;
    unsigned size_08;
    bool load_raw(const void *source,unsigned bytes,const WaveFormat18 *format);
    void clear();
};
class Wave3DBufferView : public WaveBufferView {
public:
    UnknownInterface *resource_0c;
};
struct WaveServiceInitializeView {
    unsigned char unknown_000[0xc8];
    WaveBufferView buffers_c8[32];
    Wave3DBufferView buffers_248[32];
    unsigned next_448,next_44c;
    float gain_450,gain_454;
    bool initialize();
};
extern "C" __declspec(dllimport) int __stdcall MessageBoxA(void *,const char *,const char *,unsigned);
extern const char wave_lock_error[];
extern const char wave_error_title[];
bool WaveServiceInitializeView::initialize()
{
    unsigned char silence[0x40000];
    memset(silence,0,sizeof(silence));
    WaveFormat18 format;
    format.extra_size=0;
    format.format_tag=1;
    format.samples_per_second=44100;
    format.bits_per_sample=16;
    format.channels=1;
    format.block_align=2;
    format.bytes_per_second=88200;
    WaveBufferView *buffer=buffers_c8;
    Wave3DBufferView *spatial=buffers_248;
    unsigned remaining=32;
    do {
        buffer->load_raw(silence,sizeof(silence),&format);
        spatial->load_raw(silence,sizeof(silence),&format);
        ++buffer;
        ++spatial;
    } while(--remaining);
    gain_450=gain_454=1.0f;
    next_448=next_44c=0;
    return true;
}
bool WaveBufferView::load_raw(const void *source,unsigned bytes,const WaveFormat18 *format)
{
    if(resource_04){resource_04->release();resource_04=0;}
    if(!initialize(format,bytes)){resource_04=0;return false;}
    if(source){
        void *first,*second;
        ULong first_size,second_size;
        if(resource_04->lock(0,bytes,&first,&first_size,&second,&second_size,2)<0){
            MessageBoxA(0,wave_lock_error,wave_error_title,0);return false;
        }
        memcpy(first,source,first_size);
        memcpy(second,static_cast<const unsigned char *>(source)+first_size,second_size);
        resource_04->unlock(first,first_size,second,second_size);
    }else clear();
    size_08=bytes;return true;
}
void WaveBufferView::clear()
{
    if(resource_04){
        void *data;ULong bytes;
        resource_04->lock(0,0,&data,&bytes,0,0,2);
        // The target forwards a zero fill length after Lock; preserve it.
        memset(data,0,0);
        resource_04->unlock(data,bytes,0,0);
    }
}
typedef char FormatSize[sizeof(WaveFormat18)==18?1:-1];
typedef char BaseSize[sizeof(WaveBufferView)==12?1:-1];
typedef char DerivedSize[sizeof(Wave3DBufferView)==16?1:-1];
typedef char ServiceSize[offsetof(WaveServiceInitializeView,gain_450)==0x450?1:-1];
}
