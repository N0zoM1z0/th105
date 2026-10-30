#include "assets/DdsTextureLoading.cpp"
#include "assets/CBitmapData.hpp"
#include <string.h>
namespace th105 {
extern int g_bitmap_texture_levels;
extern int g_bitmap_texture_base_level;
extern unsigned g_bitmap_texture_palette;
extern bool g_bitmap_texture_encoded;
extern "C" __declspec(dllimport) int __cdecl wsprintfA(char *,const char *,...);
struct TextureFileLoading {
    static void __fastcall upload(unsigned pitch,unsigned char format,CBitmapData *bitmap,void *bits);
    static long __fastcall load(unsigned *height_out,const char *path,DdsTexture9 **output,unsigned *width_out);
};
void __fastcall TextureFileLoading::upload(unsigned pitch,unsigned char format,CBitmapData *bitmap,void *bits)
{
    unsigned *destination=static_cast<unsigned *>(bits);
    if(bitmap->explicit_size_14) {
        switch(format) {
        case 8: {
            const unsigned char *source=bitmap->buffer_1c;
            unsigned run=source[0],count=0;
            int index=0;
            unsigned short color=reinterpret_cast<unsigned short *>(bitmap->field_18)[source[1]];
            unsigned short *row=reinterpret_cast<unsigned short *>(destination);
            unsigned stride=pitch/2;
            for(int y=0;y<bitmap->field_0c;++y) {
                for(int x=0;x<bitmap->field_08;++x) {
                    ++count;
                    row[x]=color;
                    if(count>=run) {
                        index+=2;
                        count=run<count;
                        if(x==bitmap->field_08-1 && y==bitmap->field_0c-1) break;
                        run=source[index];
                        color=reinterpret_cast<unsigned short *>(bitmap->field_18)[source[index+1]];
                    }
                }
                row+=stride;
            }
            break;
        }
        case 16: {
            const unsigned short *source=reinterpret_cast<const unsigned short *>(bitmap->buffer_1c);
            int run=source[0],count=0,index=0;
            unsigned short color=source[1];
            unsigned short *row=reinterpret_cast<unsigned short *>(destination);
            unsigned stride=pitch/2;
            for(int y=0;y<bitmap->field_0c;++y) {
                for(int x=0;x<bitmap->field_08;++x) {
                    ++count;
                    row[x]=color;
                    if(count>=run) {
                        index+=2;count=0;
                        if(x==bitmap->field_08-1 && y==bitmap->field_0c-1) break;
                        run=source[index];color=source[index+1];
                    }
                }
                row+=stride;
            }
            break;
        }
        case 24: case 32: {
            const int *source=reinterpret_cast<const int *>(bitmap->buffer_1c);
            int run=source[0],count=0,index=0;
            unsigned color=source[1];
            unsigned *row=destination;
            unsigned stride=pitch/4;
            for(int y=0;y<bitmap->field_0c;++y) {
                for(int x=0;x<bitmap->field_08;++x) {
                    ++count;row[x]=color;
                    if(count>=run) {
                        index+=2;count=0;
                        if(x==bitmap->field_08-1 && y==bitmap->field_0c-1) break;
                        run=source[index];color=source[index+1];
                    }
                }
                row+=stride;
            }
            break;
        }
        }
    } else {
        switch(format) {
        case 8: {
            const unsigned char *source=bitmap->buffer_1c;
            unsigned short *row=reinterpret_cast<unsigned short *>(destination);
            unsigned stride=pitch/2;
            for(int y=0;y<bitmap->field_0c;++y) {
                for(int x=0;x<bitmap->field_08;++x)
                    row[x]=reinterpret_cast<unsigned short *>(bitmap->field_18)[source[x]];
                row+=stride;source+=bitmap->field_10;
            }
            break;
        }
        case 16: {
            const unsigned *source=reinterpret_cast<const unsigned *>(bitmap->buffer_1c);
            unsigned *row=destination;
            unsigned stride=pitch/4;
            int width=bitmap->field_08>>1,source_stride=bitmap->field_10>>1;
            for(int y=0;y<bitmap->field_0c;++y) {
                for(int x=0;x<width;++x) row[x]=source[x];
                row+=stride;source+=source_stride;
            }
            break;
        }
        case 24: case 32: {
            const unsigned *source=reinterpret_cast<const unsigned *>(bitmap->buffer_1c);
            unsigned *row=destination;
            unsigned stride=pitch/4;
            for(int y=0;y<bitmap->field_0c;++y) {
                for(int x=0;x<bitmap->field_08;++x) row[x]=source[x];
                row+=stride;source+=bitmap->field_10;
            }
            break;
        }
        }
    }
}

long __fastcall TextureFileLoading::load(unsigned *height_out,const char *path,DdsTexture9 **output,unsigned *width_out)
{
    long status=load_dds_texture(output,path,width_out,height_out);
    if(status!=static_cast<long>(0x8876086c)) return status;
    CBitmapData bitmaps[3];
    char source[261];
    char encoded[261];
    char base[261];
    strcpy_s(base,260,path);
    base[strlen(path)-4]=0;
    int levels=1;
    if(g_bitmap_texture_palette)
        for(int i=0;i<3;++i) bitmaps[i].field_18=g_bitmap_texture_palette;
    CBitmapData *bitmap=bitmaps;
    int level=g_bitmap_texture_base_level;
    bitmap->format_04=0;
    for(;level>=0;--level) {
        if(level==0) strcpy_s(source,261,path);
        else wsprintfA(source,"%s_%d.bmp",base,level);
        bool loaded;
        if(g_bitmap_texture_encoded) {
            unsigned length=strlen(source);
            strcpy_s(encoded,260,source);
            memcpy(encoded+length-4,".cv2",4);
            loaded=bitmap->load_from_file(encoded);
        } else loaded=bitmap->load_bitmap(source);
        if(loaded) break;
        if(level==0) return 0x8876086c;
    }
    if(width_out) *width_out=bitmap->field_08;
    if(height_out) *height_out=bitmap->field_0c;
    if(level==g_bitmap_texture_base_level) {
        for(int i=1;i<g_bitmap_texture_levels;++i) {
            if(i>=3) break;
            wsprintfA(source,"%s_%d.bmp",base,i+g_bitmap_texture_base_level);
            bitmaps[i].format_04=0;
            bool loaded;
            if(g_bitmap_texture_encoded) {
                unsigned length=strlen(source);
                strcpy_s(encoded,260,source);
                memcpy(encoded+length-4,".cv2",4);
                loaded=bitmaps[i].load_from_file(encoded);
            } else loaded=bitmaps[i].load_bitmap(source);
            if(!loaded) break;
            ++levels;
        }
    }
    unsigned width=bitmap->field_08,height=bitmap->field_0c;
    if(g_d3d_backend.caps_028.bytes_000[0x3c]&0x20) {
        if(width<height) width=height;
        else height=width;
    }
    if(bitmap->format_04==32 || bitmap->format_04==24)
        status=create_file_texture(width,height,levels,21,output);
    else if(bitmap->format_04==8 || bitmap->format_04==16)
        status=create_file_texture(width,height,levels,25,output);
    else return status;
    if(status>=0) {
        for(int i=0;i<levels;++i) {
            DdsLockedRect locked;
            if((*output)->LockRect(i,&locked,0,0)==0) {
                if(bitmaps[i].format_04==8 && g_bitmap_texture_palette)
                    bitmaps[i].field_18=g_bitmap_texture_palette;
                upload(locked.pitch,bitmaps[i].format_04,&bitmaps[i],locked.bits);
                (*output)->UnlockRect(0);
            }
        }
    }
    return status;
}
}
