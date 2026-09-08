#define TH105_FILE_READER_OWNER_DTOR_VISIBLE
#include "FileReader.hpp"

#include <stdlib.h>

namespace th105 {

#pragma pack(push, 2)
struct BitmapFileHeader14 {
    unsigned short type_00;
    unsigned int size_02;
    unsigned short reserved1_06;
    unsigned short reserved2_08;
    unsigned int bits_offset_0a;
};
#pragma pack(pop)

struct BitmapInfoHeader40 {
    unsigned int header_size_00;
    int width_04;
    int height_08;
    unsigned short planes_0c;
    unsigned short bit_count_0e;
    unsigned int compression_10;
    unsigned int image_size_14;
    int x_pels_18;
    int y_pels_1c;
    unsigned int colors_used_20;
    unsigned int colors_important_24;
};

struct PaletteSourceColor {
    unsigned char blue;
    unsigned char green;
    unsigned char red;
    unsigned char reserved;
};

class PaletteDataView {
public:
    bool load_bmp_palette(const char *path, unsigned char output_format);
    bool load_raw_palette(const char *path);

private:
    unsigned char format_00;
    unsigned char reserved_01[3];
    void *data_04;
};

bool PaletteDataView::load_bmp_palette(
    const char *path,
    unsigned char output_format)
{
    if (output_format != 16 && output_format != 24 && output_format != 32)
        return false;

    FileReaderOwner file;
    if (!file.open(path))
        return false;

    CFileReader *reader = file.reader;
    BitmapFileHeader14 file_header;
    reader->read(&file_header, sizeof(file_header));
    if (file_header.type_00 != 0x4D42)
        return false;

    BitmapInfoHeader40 info;
    reader->read(&info, sizeof(info));
    if (info.bit_count_0e != 8)
        return false;

    PaletteSourceColor source[256];
    reader->read(source, sizeof(source));

    if (data_04 != 0) {
        free(data_04);
        data_04 = 0;
    }
    format_00 = output_format;

    if (output_format == 16) {
        data_04 = new unsigned short[256];
        for (int index = 0; index < 256; index += 4) {
            reinterpret_cast<unsigned short *>(data_04)[index + 0] = static_cast<unsigned short>((source[index + 0].red & 0xF8) << 7);
            reinterpret_cast<unsigned short *>(data_04)[index + 0] |= static_cast<unsigned short>((source[index + 0].green & 0xF8) << 2);
            reinterpret_cast<unsigned short *>(data_04)[index + 0] |= static_cast<unsigned short>(source[index + 0].blue >> 3);
            reinterpret_cast<unsigned short *>(data_04)[index + 0] |= 0x8000;
            reinterpret_cast<unsigned short *>(data_04)[index + 1] = static_cast<unsigned short>((source[index + 1].red & 0xF8) << 7);
            reinterpret_cast<unsigned short *>(data_04)[index + 1] |= static_cast<unsigned short>((source[index + 1].green & 0xF8) << 2);
            reinterpret_cast<unsigned short *>(data_04)[index + 1] |= static_cast<unsigned short>(source[index + 1].blue >> 3);
            reinterpret_cast<unsigned short *>(data_04)[index + 1] |= 0x8000;
            reinterpret_cast<unsigned short *>(data_04)[index + 2] = static_cast<unsigned short>((source[index + 2].red & 0xF8) << 7);
            reinterpret_cast<unsigned short *>(data_04)[index + 2] |= static_cast<unsigned short>((source[index + 2].green & 0xF8) << 2);
            reinterpret_cast<unsigned short *>(data_04)[index + 2] |= static_cast<unsigned short>(source[index + 2].blue >> 3);
            reinterpret_cast<unsigned short *>(data_04)[index + 2] |= 0x8000;
            reinterpret_cast<unsigned short *>(data_04)[index + 3] = static_cast<unsigned short>((source[index + 3].red & 0xF8) << 7);
            reinterpret_cast<unsigned short *>(data_04)[index + 3] |= static_cast<unsigned short>((source[index + 3].green & 0xF8) << 2);
            reinterpret_cast<unsigned short *>(data_04)[index + 3] |= static_cast<unsigned short>(source[index + 3].blue >> 3);
            reinterpret_cast<unsigned short *>(data_04)[index + 3] |= 0x8000;
        }
        reinterpret_cast<unsigned short *>(data_04)[0] &= 0x7FFF;
    } else {
        data_04 = new unsigned int[256];
        for (int index = 0; index < 256; index += 4) {
            reinterpret_cast<unsigned int *>(data_04)[index + 0] = source[index + 0].red;
            reinterpret_cast<unsigned int *>(data_04)[index + 0] |= static_cast<unsigned int>(source[index + 0].green) << 8;
            reinterpret_cast<unsigned int *>(data_04)[index + 0] |= static_cast<unsigned int>(source[index + 0].blue) << 16;
            reinterpret_cast<unsigned int *>(data_04)[index + 0] |= 0xFF000000u;
            reinterpret_cast<unsigned int *>(data_04)[index + 1] = source[index + 1].red;
            reinterpret_cast<unsigned int *>(data_04)[index + 1] |= static_cast<unsigned int>(source[index + 1].green) << 8;
            reinterpret_cast<unsigned int *>(data_04)[index + 1] |= static_cast<unsigned int>(source[index + 1].blue) << 16;
            reinterpret_cast<unsigned int *>(data_04)[index + 1] |= 0xFF000000u;
            reinterpret_cast<unsigned int *>(data_04)[index + 2] = source[index + 2].red;
            reinterpret_cast<unsigned int *>(data_04)[index + 2] |= static_cast<unsigned int>(source[index + 2].green) << 8;
            reinterpret_cast<unsigned int *>(data_04)[index + 2] |= static_cast<unsigned int>(source[index + 2].blue) << 16;
            reinterpret_cast<unsigned int *>(data_04)[index + 2] |= 0xFF000000u;
            reinterpret_cast<unsigned int *>(data_04)[index + 3] = source[index + 3].red;
            reinterpret_cast<unsigned int *>(data_04)[index + 3] |= static_cast<unsigned int>(source[index + 3].green) << 8;
            reinterpret_cast<unsigned int *>(data_04)[index + 3] |= static_cast<unsigned int>(source[index + 3].blue) << 16;
            reinterpret_cast<unsigned int *>(data_04)[index + 3] |= 0xFF000000u;
        }
        reinterpret_cast<unsigned char *>(data_04)[3] = 0;
    }
    return true;
}

bool PaletteDataView::load_raw_palette(const char *path)
{
    FileReaderOwner file;
    if (!file.open(path))
        return false;

    if (data_04 != 0)
        free(data_04);

    CFileReader *reader = file.reader;
    reader->read(&format_00, 1);

    unsigned int byte_count = 0;
    if (format_00 == 16)
        byte_count = 0x200;
    else if (format_00 == 24 || format_00 == 32)
        byte_count = 0x400;

    if (byte_count != 0) {
        data_04 = new unsigned char[byte_count];
        reader->read(data_04, byte_count);
    }
    return true;
}

typedef char PaletteDataViewSize[sizeof(PaletteDataView) == 8 ? 1 : -1];
typedef char BitmapFileHeader14Size[sizeof(BitmapFileHeader14) == 14 ? 1 : -1];
typedef char BitmapInfoHeader40Size[sizeof(BitmapInfoHeader40) == 40 ? 1 : -1];

} // namespace th105
