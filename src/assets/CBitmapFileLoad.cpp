#include "CBitmapData.hpp"
#include "FileReader.hpp"
#include <new>
#include <stdlib.h>

namespace th105 {

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

} // namespace th105
