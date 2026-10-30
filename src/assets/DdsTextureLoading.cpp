#define TH105_FILE_READER_OWNER_DTOR_VISIBLE
#include "assets/FileReader.hpp"
#include "engine/D3DTextureQuery.hpp"
#include <stdio.h>
namespace th105 {
struct DdsLockedRect { int pitch; void *bits; };
struct DdsTexture9 : D3DTexture9 {
    virtual long __stdcall LockRect(unsigned,DdsLockedRect *,const void *,unsigned)=0;
    virtual long __stdcall UnlockRect(unsigned)=0;
};
struct DdsPixelFormat { unsigned size,flags,fourcc,rgb_bits,red_mask,green_mask,blue_mask,alpha_mask; };
struct DdsHeader124 {
    unsigned size,flags,height,width,pitch_or_linear_size,depth,mipmap_count;
    unsigned reserved[11];
    DdsPixelFormat pixel_format;
    unsigned caps,caps2,caps3,caps4,reserved2;
};
typedef char DdsHeaderSize[sizeof(DdsHeader124)==124?1:-1];
extern "C" long __stdcall D3DXCreateTexture(D3DDevice9 *,unsigned,unsigned,unsigned,unsigned,unsigned,unsigned,DdsTexture9 **);
static long __stdcall create_file_texture(unsigned width,unsigned height,unsigned levels,unsigned format,DdsTexture9 **texture)
{
    if (g_d3d_backend.caps_028.bytes_000[0x3c]&0x20) {
        if (width<height) width=height;
        else height=width;
    }
    EnterCriticalSection(&g_d3d_backend.critical_section_000.critical_section_04);
    long status=D3DXCreateTexture(g_d3d_backend.device_020,width,height,levels,0,format,1,texture);
    LeaveCriticalSection(&g_d3d_backend.critical_section_000.critical_section_04);
    return status;
}
long __stdcall load_dds_texture(DdsTexture9 **output,const char *path,unsigned *width_out,unsigned *height_out)
{
    FileReaderOwner file;
    if (!file.open(path)) return 0x8876086c;
    CFileReader *reader=file.reader;
    unsigned signature;
    reader->read(&signature,4);
    if (signature!=0x20534444) return 0x8876086c;
    DdsHeader124 header;
    reader->read(&header,sizeof(header));
    if (header.caps2&0x200) return 0x8876086c;
    unsigned format;
    switch(header.pixel_format.fourcc) {
    case 0x31545844: format=0x31545844; break;
    case 0x32545844: format=0x32545844; break;
    case 0x33545844: format=0x33545844; break;
    case 0x34545844: format=0x34545844; break;
    case 0x35545844: format=0x35545844; break;
    default: return 0x8876086c;
    }
    unsigned width=header.width,height=header.height;
    unsigned levels=1;
    if(header.mipmap_count) levels=header.mipmap_count;
    DdsTexture9 *texture;
    long status=create_file_texture(width,height,levels,format,&texture);
    if(status<0) { printf("failed\n"); return status; }
    unsigned bytes;
    if(header.flags&8) {
        if(format==0x31545844) bytes=8*(width/4<1?1:width/4)*(height/4<1?1:height/4);
        else bytes=16*(width/4<1?1:width/4)*(height/4<1?1:height/4);
    } else bytes=(header.flags&0x80000)?header.pitch_or_linear_size:0;
    for(unsigned level=0;level<levels;++level) {
        DdsLockedRect locked;
        if(texture->LockRect(level,&locked,0,0)!=0) return 0x8876086c;
        reader->read(locked.bits,bytes);
        texture->UnlockRect(level);
        bytes=bytes/4<1?1:bytes/4;
    }
    if(width_out) *width_out=width;
    if(height_out) *height_out=height;
    *output=texture;
    return status;
}
}
