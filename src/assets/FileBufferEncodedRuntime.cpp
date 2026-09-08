#define TH105_FILE_READER_OWNER_DTOR_VISIBLE
#include "FileReader.hpp"

#include <stdlib.h>

namespace th105 {

class FileBufferEncodedView {
public:
    bool load_encoded(const char *path);

private:
    unsigned char *data_00;
    unsigned int size_04;
};

bool FileBufferEncodedView::load_encoded(const char *path)
{
    FileReaderOwner file;
    if (!file.open(path))
        return false;

    CFileReader *reader = file.reader;
    size_04 = reader->size();
    if (size_04 != 0) {
        if (data_00 != 0)
            free(data_00);
        data_00 = new unsigned char[size_04 + 1];
        data_00[size_04] = 0;
        reader->read(data_00, size_04);

        unsigned char key = 0x8b;
        unsigned char delta = 0x71;
        for (unsigned int index = 0; index < size_04; ++index) {
            data_00[index] ^= key;
            key = static_cast<unsigned char>(key + delta);
            delta = static_cast<unsigned char>(delta - 107);
        }
    }
    return true;
}

typedef char FileBufferEncodedViewSize[
    sizeof(FileBufferEncodedView) == 8 ? 1 : -1];

} // namespace th105
