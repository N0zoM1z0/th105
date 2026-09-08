#pragma once

namespace th105 {

struct PngStruct;

struct PngInfo125 {
    unsigned long width_00;
    unsigned long height_04;
    unsigned long valid_08;
    unsigned long rowbytes_0c;
    void *palette_10;
    unsigned short num_palette_14;
    unsigned short num_trans_16;
    unsigned char bit_depth_18;
    unsigned char color_type_19;
    unsigned char compression_type_1a;
    unsigned char filter_type_1b;
    unsigned char interlace_type_1c;
    unsigned char channels_1d;
    unsigned char pixel_depth_1e;
    unsigned char spare_1f;
};

typedef void (__cdecl *PngReadFn)(
    PngStruct *png_ptr,
    unsigned char *destination,
    unsigned long size);

extern "C" void *__cdecl png_get_io_ptr(PngStruct *png_ptr);
extern "C" int __cdecl png_sig_cmp(
    const unsigned char *signature,
    unsigned long start,
    unsigned long count);
extern "C" PngStruct *__cdecl png_create_read_struct(
    const char *version,
    void *error_ptr,
    void *error_fn,
    void *warning_fn);
extern "C" PngInfo125 *__cdecl png_create_info_struct(PngStruct *png_ptr);
extern "C" void __cdecl png_destroy_read_struct(
    PngStruct **png_ptr,
    PngInfo125 **info_ptr,
    PngInfo125 **end_info_ptr);
extern "C" void __cdecl png_set_read_fn(
    PngStruct *png_ptr,
    void *io_ptr,
    PngReadFn read_fn);
extern "C" void __cdecl png_set_sig_bytes(PngStruct *png_ptr, int count);
extern "C" void __cdecl png_read_info(PngStruct *png_ptr, PngInfo125 *info_ptr);
extern "C" void __cdecl png_set_bgr(PngStruct *png_ptr);
extern "C" void __cdecl png_read_row(
    PngStruct *png_ptr,
    unsigned char *row,
    unsigned char *display_row);
extern "C" void __cdecl png_read_end(PngStruct *png_ptr, PngInfo125 *info_ptr);

typedef char PngInfo125PrefixSize[
    sizeof(PngInfo125) == 0x20 ? 1 : -1];

} // namespace th105
