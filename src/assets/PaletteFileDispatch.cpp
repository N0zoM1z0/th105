#include "PaletteDataRuntime.cpp"
#include <cstring>

namespace th105 {
struct PaletteDecodeMode {
 bool encoded;
 bool load_palette(const char *path, PaletteDataView *palette, unsigned char format);
};
bool PaletteDecodeMode::load_palette(const char *path, PaletteDataView *palette, unsigned char format)
{
 if(encoded){
  char alternate[260];unsigned length=std::strlen(path);
  strcpy_s(alternate,260,path);std::memcpy(alternate+length-4,".pal",4);
  return palette->load_raw_palette(alternate);
 }
 return palette->load_bmp_palette(path,format);
}
}
