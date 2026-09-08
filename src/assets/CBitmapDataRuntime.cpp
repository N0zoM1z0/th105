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

    bool load_png(const char *path);
    bool load_from_file(const char *path);
    void copy_from(const CBitmapSourceView *source);

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
