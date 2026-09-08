#include "FileReader.hpp"
#include "Png125Runtime.hpp"

#include <stdlib.h>
#include <string.h>

namespace th105 {

struct CBitmapSourceView {
    int field_00;
    int field_04;
    int field_08;
    unsigned char format_0c;
    unsigned char reserved_0d[3];
    unsigned int explicit_size_10;
    const unsigned char *data_14;
};

class CBitmapData {
public:
    CBitmapData();
    virtual ~CBitmapData();

    virtual bool load_bitmap(const char *path);
    virtual bool load_png(const char *path);
    virtual bool load_from_file(const char *path);
    virtual void copy_from(const CBitmapSourceView *source);

private:
    unsigned char format_04;
    unsigned char reserved_05[3];
    int field_08;
    int field_0c;
    int field_10;
    unsigned int explicit_size_14;
    unsigned int field_18;
    unsigned char *buffer_1c;
};

void __cdecl CBitmapData_png_read(
    PngStruct *png_ptr,
    unsigned char *destination,
    unsigned long size)
{
    FileReaderOwner *file =
        static_cast<FileReaderOwner *>(png_get_io_ptr(png_ptr));
    file->reader->read(destination, size);
}

CBitmapData::CBitmapData()
{
    format_04 = 0;
    buffer_1c = 0;
    field_18 = 0;
    explicit_size_14 = 0;
}

CBitmapData::~CBitmapData()
{
    if (buffer_1c != 0)
        free(buffer_1c);
}

#pragma pack(push, 2)
struct BitmapFileHeader14 {
    unsigned short type_00;
    unsigned int file_size_02;
    unsigned short reserved_06;
    unsigned short reserved_08;
    unsigned int bits_offset_0a;
};
#pragma pack(pop)

struct BitmapInfoHeader40 {
    unsigned int size_00;
    int width_04;
    int height_08;
    unsigned short planes_0c;
    unsigned short bit_count_0e;
    unsigned int compression_10;
    unsigned int image_size_14;
    int x_pixels_per_meter_18;
    int y_pixels_per_meter_1c;
    unsigned int colors_used_20;
    unsigned int colors_important_24;
};

struct BitmapPaletteColor {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
    unsigned char alpha;
};

struct BitmapSourcePaletteColor {
    unsigned char blue;
    unsigned char green;
    unsigned char red;
    unsigned char alpha;
};

bool CBitmapData::load_bitmap(const char *path)
{
    FileReaderOwner file;
    if (!file.open(path))
        return false;

    CFileReader *reader = file.reader;

    unsigned short *palette16;
    unsigned int *palette32;
    unsigned short type;
    palette16 = 0;
    palette32 = 0;
    reader->read(&type, 2);
    if (type != 0x4D42)
        return load_png(path);

    reader->seek(0, 0);
    unsigned int file_size = reader->size();
    unsigned char *file_data = new unsigned char[file_size];
    reader->read(file_data, file_size);

    BitmapFileHeader14 *file_header =
        reinterpret_cast<BitmapFileHeader14 *>(file_data);
    BitmapInfoHeader40 *info = reinterpret_cast<BitmapInfoHeader40 *>(
        file_data + sizeof(BitmapFileHeader14));
    unsigned char *source = file_data + file_header->bits_offset_0a;
    unsigned char source_bpp = static_cast<unsigned char>(info->bit_count_0e);

    if (format_04 == 0) {
        format_04 = source_bpp;
        if (format_04 < 8)
            format_04 = 8;
    }
    if (format_04 == 32 && source_bpp <= 24)
        format_04 = 24;
    if (format_04 == 8 && field_18 == 0)
        format_04 = 16;

    field_08 = info->width_04;
    field_0c = info->height_08;
    field_10 = (field_08 + 3) & ~3;
    int source_stride = (field_08 * source_bpp / 8 + 3) & ~3;

    BitmapPaletteColor palette[256];
    if (source_bpp <= 8 && format_04 >= 16) {
        int color_count = 1 << source_bpp;
        BitmapSourcePaletteColor *source_palette =
            reinterpret_cast<BitmapSourcePaletteColor *>(file_data + 54);
        for (int index = 0; index < color_count; ++index) {
            palette[index].red = source_palette[index].red;
            palette[index].green = source_palette[index].green;
            palette[index].blue = source_palette[index].blue;
            palette[index].alpha = source_palette[index].alpha;
        }

        if (format_04 == 16) {
            palette16 = new unsigned short[256];
            for (int index = 0; index < 256; index += 4) {
                palette16[index + 0] = static_cast<unsigned short>(
                    0x8000 | ((palette[index + 0].red & 0xF8) << 7) |
                    ((palette[index + 0].green & 0xF8) << 2) |
                    (palette[index + 0].blue >> 3));
                palette16[index + 1] = static_cast<unsigned short>(
                    0x8000 | ((palette[index + 1].red & 0xF8) << 7) |
                    ((palette[index + 1].green & 0xF8) << 2) |
                    (palette[index + 1].blue >> 3));
                palette16[index + 2] = static_cast<unsigned short>(
                    0x8000 | ((palette[index + 2].red & 0xF8) << 7) |
                    ((palette[index + 2].green & 0xF8) << 2) |
                    (palette[index + 2].blue >> 3));
                palette16[index + 3] = static_cast<unsigned short>(
                    0x8000 | ((palette[index + 3].red & 0xF8) << 7) |
                    ((palette[index + 3].green & 0xF8) << 2) |
                    (palette[index + 3].blue >> 3));
            }
            palette16[0] &= 0x7FFF;
        } else if (format_04 == 24) {
            palette32 = new unsigned int[256];
            for (int index = 0; index < 256; index += 4) {
                palette32[index + 0] =
                    0xFF000000u | (palette[index + 0].red << 16) |
                    (palette[index + 0].green << 8) |
                    palette[index + 0].blue;
                palette32[index + 1] =
                    0xFF000000u | (palette[index + 1].red << 16) |
                    (palette[index + 1].green << 8) |
                    palette[index + 1].blue;
                palette32[index + 2] =
                    0xFF000000u | (palette[index + 2].red << 16) |
                    (palette[index + 2].green << 8) |
                    palette[index + 2].blue;
                palette32[index + 3] =
                    0xFF000000u | (palette[index + 3].red << 16) |
                    (palette[index + 3].green << 8) |
                    palette[index + 3].blue;
            }
            reinterpret_cast<unsigned char *>(palette32)[3] = 0;
        }
    }

    switch (format_04) {
    case 8: {
        unsigned char *destination =
            new unsigned char[field_10 * field_0c];
        buffer_1c = destination;
        for (int y = 0; y < field_0c; ++y) {
            for (int x = 0; x < field_08; ++x)
                destination[x + field_10 * (field_0c - y - 1)] = source[x];
            source += source_stride;
        }
        break;
    }
    case 16: {
        unsigned short *destination =
            new unsigned short[field_10 * field_0c];
        buffer_1c = reinterpret_cast<unsigned char *>(destination);
        if (source_bpp <= 8) {
            for (int y = 0; y < field_0c; ++y) {
                for (int x = 0; x < field_08; ++x) {
                    destination[x + field_10 * (field_0c - y - 1)] =
                        palette16[source[x]];
                }
                source += source_stride;
            }
        } else {
            for (int y = 0; y < field_0c; ++y) {
                unsigned char *pixel = source + 1;
                for (int x = 0; x < field_08; ++x) {
                    destination[x + field_10 * (field_0c - y - 1)] =
                        static_cast<unsigned short>(pixel[-1] >> 3);
                    destination[x + field_10 * (field_0c - y - 1)] |=
                        static_cast<unsigned short>((pixel[0] & 0xF8) << 2);
                    destination[x + field_10 * (field_0c - y - 1)] |=
                        static_cast<unsigned short>((pixel[1] & 0xF8) << 7);
                    if ((pixel[-1] | pixel[0] | pixel[1]) == 0)
                        destination[x + field_10 * (field_0c - y - 1)] &= 0x7FFF;
                    else
                        destination[x + field_10 * (field_0c - y - 1)] |= 0x8000;
                    pixel += 3;
                }
                source += source_stride;
            }
        }
        break;
    }
    case 24: {
        unsigned int *destination =
            new unsigned int[field_10 * field_0c];
        buffer_1c = reinterpret_cast<unsigned char *>(destination);
        if (source_bpp <= 8) {
            for (int y = 0; y < field_0c; ++y) {
                for (int x = 0; x < field_08; ++x) {
                    destination[x + field_10 * (field_0c - y - 1)] =
                        palette32[source[x]];
                }
                source += source_stride;
            }
        } else {
            for (int y = 0; y < field_0c; ++y) {
                unsigned char *pixel = source + 2;
                for (int x = 0; x < field_08; ++x) {
                    destination[x + field_10 * (field_0c - y - 1)] =
                        static_cast<unsigned int>(pixel[-2]);
                    destination[x + field_10 * (field_0c - y - 1)] |=
                        static_cast<unsigned int>(pixel[-1]) << 8;
                    destination[x + field_10 * (field_0c - y - 1)] |=
                        static_cast<unsigned int>(pixel[0]) << 16;
                    if (pixel[-2] == 0 && pixel[-1] == 0xFF && pixel[0] == 0)
                        destination[x + field_10 * (field_0c - y - 1)] = 0;
                    else
                        destination[x + field_10 * (field_0c - y - 1)] |=
                            0xFF000000u;
                    pixel += 3;
                }
                source += source_stride;
            }
        }
        break;
    }
    case 32: {
        unsigned int *destination =
            new unsigned int[field_10 * field_0c];
        buffer_1c = reinterpret_cast<unsigned char *>(destination);
        if (source_bpp <= 8) {
            for (int y = 0; y < field_0c; ++y) {
                for (int x = 0; x < field_08; ++x) {
                    destination[x + field_10 * (field_0c - y - 1)] =
                        palette32[source[x]];
                }
                source += source_stride;
            }
        } else {
            for (int y = 0; y < field_0c; ++y) {
                unsigned int *pixel = reinterpret_cast<unsigned int *>(source);
                for (int x = 0; x < field_08; ++x) {
                    destination[x + field_10 * (field_0c - y - 1)] = *pixel;
                    ++pixel;
                }
                source += source_stride;
            }
        }
        break;
    }
    default:
        break;
    }

    if (palette16 != 0)
        free(palette16);
    else if (palette32 != 0)
        free(palette32);
    free(file_data);
    return true;
}

bool CBitmapData::load_png(const char *path)
{
    FileReaderOwner file;
    if (!file.open(path))
        return false;

    unsigned char signature[4];
    file.reader->read(signature, 4);
    if (png_sig_cmp(signature, 0, 4) != 0)
        return false;

    PngStruct *png = png_create_read_struct("1.5.2", 0, 0, 0);
    if (png == 0)
        return false;

    PngInfo125 *info = png_create_info_struct(png);
    if (info == 0) {
        png_destroy_read_struct(&png, 0, 0);
        return false;
    }

    png_set_read_fn(png, &file, CBitmapData_png_read);
    png_set_sig_bytes(png, 4);
    png_read_info(png, info);
    png_set_bgr(png);

    field_10 = info->width_00;
    field_08 = info->width_00;
    field_0c = info->height_04;
    format_04 = info->pixel_depth_1e;
    unsigned char row_scale = 4 * (info->bit_depth_18 >> 3);

    if (info->interlace_type_1c != 0) {
        png_destroy_read_struct(&png, &info, 0);
        return false;
    }

    unsigned int row_index = 0;
    if (format_04 == 24) {
        unsigned char *row =
            new unsigned char[row_scale * field_08 * info->channels_1d];
        unsigned char *destination =
            new unsigned char[4 * field_0c * field_10];
        buffer_1c = destination;
        if (info->height_04 != 0) {
            do {
                png_read_row(png, row, 0);
                int x = 0;
                if (field_08 > 0) {
                    unsigned char *dst = destination + 2;
                    unsigned char *src = row + 2;
                    do {
                        dst[-2] = src[-2];
                        dst[-1] = src[-1];
                        dst[0] = src[0];
                        dst[1] = 0xFF;
                        ++x;
                        src += 3;
                        dst += 4;
                    } while (x < field_08);
                }
                destination += 4 * field_10;
                ++row_index;
            } while (row_index < info->height_04);
        }
    } else if (format_04 == 32) {
        unsigned char *pixels = new unsigned char[
            row_scale * field_0c * field_08 * info->channels_1d];
        unsigned int offset = 0;
        if (info->height_04 != 0) {
            do {
                png_read_row(png, pixels + offset, 0);
                offset += row_scale * field_08;
                ++row_index;
            } while (row_index < info->height_04);
        }
        buffer_1c = pixels;
    }

    png_read_end(png, 0);
    png_destroy_read_struct(&png, &info, 0);
    return true;
}

bool CBitmapData::load_from_file(const char *path)
{
    FileReaderOwner file;
    if (!file.open(path))
        return false;

    CFileReader *reader = file.reader;
    reader->read(&format_04, 1);
    reader->read(&field_08, 4);
    reader->read(&field_0c, 4);
    reader->read(&field_10, 4);
    reader->read(&explicit_size_14, 4);

    unsigned char *old_buffer = buffer_1c;
    int byte_count;
    if (explicit_size_14 > 0) {
        if (old_buffer != 0) {
            free(old_buffer);
            buffer_1c = 0;
        }
        buffer_1c = new unsigned char[explicit_size_14];
        byte_count = explicit_size_14;
        reader->read(buffer_1c, byte_count);
    } else if (format_04 >= 24) {
        if (old_buffer != 0) {
            free(old_buffer);
            buffer_1c = 0;
        }
        buffer_1c = new unsigned char[field_10 * field_0c * 4];
        byte_count = field_10 * field_0c * 4;
        reader->read(buffer_1c, byte_count);
    } else {
        if (old_buffer != 0) {
            free(old_buffer);
            buffer_1c = 0;
        }
        buffer_1c = new unsigned char[format_04 * field_10 * field_0c / 8];
        byte_count = format_04 * field_10 * field_0c / 8;
        reader->read(buffer_1c, byte_count);
    }

    return true;
}

void CBitmapData::copy_from(const CBitmapSourceView *source)
{
    field_08 = source->field_00;
    field_0c = source->field_04;
    field_10 = source->field_08;
    format_04 = source->format_0c;
    explicit_size_14 = source->explicit_size_10;

    if (explicit_size_14 > 0) {
        buffer_1c = new unsigned char[explicit_size_14];
        memcpy(buffer_1c, source->data_14, explicit_size_14);
        return;
    }

    if (format_04 >= 24) {
        buffer_1c = new unsigned char[field_10 * field_0c * 4];
        memcpy(buffer_1c, source->data_14, field_10 * field_0c * 4);
        return;
    }

    buffer_1c = new unsigned char[format_04 * field_10 * field_0c / 8];
    memcpy(buffer_1c, source->data_14, format_04 * field_10 * field_0c / 8);
}

typedef char CBitmapDataSize[sizeof(CBitmapData) == 0x20 ? 1 : -1];
typedef char CBitmapSourceViewSize[
    sizeof(CBitmapSourceView) == 0x18 ? 1 : -1];

} // namespace th105
