#include "FileReader.hpp"

#include <stdlib.h>

namespace th105 {

class FileBufferView {
public:
    bool load_plain(const char *path);

private:
    unsigned char *data_00;
    unsigned int size_04;
};

bool FileBufferView::load_plain(const char *path)
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
    }
    return true;
}

typedef char FileBufferViewSize[sizeof(FileBufferView) == 8 ? 1 : -1];

} // namespace th105
