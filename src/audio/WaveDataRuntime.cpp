#include "audio/WaveData.hpp"
#define TH105_FILE_READER_OWNER_DTOR_VISIBLE
#include "assets/FileReader.hpp"

#include <new>
#include <stddef.h>
#include <stdlib.h>

namespace th105 {

bool __stdcall load_cv3_wave_data(WaveData *output, const char *path)
{
    FileReaderOwner file;
    if (!file.open(path))
        return false;

    CFileReader *reader = file.reader;
    reader->read(&output->format_00, 18);
    reader->read(&output->data_size_18, 4);
    if (output->data_size_18 != 0) {
        if (output->data_14 != 0) {
            delete[] output->data_14;
            output->data_14 = 0;
        }
        output->data_14 = new unsigned char[output->data_size_18];
        reader->read(output->data_14, output->data_size_18);
    }
    return true;
}

bool __stdcall load_wave_data(WaveData *output, const char *path)
{
    FileReaderOwner file;
    if (!file.open(path))
        return false;

    CFileReader *reader = file.reader;
    unsigned int chunk;
    reader->read(&chunk, 4);
    if (chunk != 0x46464952u)
        return false;

    unsigned int riff_size;
    reader->read(&riff_size, 4);
    reader->read(&chunk, 4);
    if (chunk != 0x45564157u)
        return false;

    reader->read(&chunk, 4);
    if (chunk != 0x20746D66u)
        return false;

    unsigned int format_size;
    reader->read(&format_size, 4);
    reader->read(&output->format_00, format_size);

    reader->read(&chunk, 4);
    if (chunk != 0x61746164u)
        return false;

    reader->read(&output->data_size_18, 4);
    if (output->data_size_18 == 0)
        return false;

    if (output->data_14 != 0)
        delete[] output->data_14;
    output->data_14 = new unsigned char[output->data_size_18];
    reader->read(output->data_14, output->data_size_18);
    return true;
}

typedef char WaveFormatExStorage20Size[sizeof(WaveFormatExStorage20) == 0x14 ? 1 : -1];
typedef char WaveDataSize[sizeof(WaveData) == 0x1c ? 1 : -1];
typedef char WaveDataPayloadOffset[offsetof(WaveData, data_14) == 0x14 ? 1 : -1];
typedef char WaveDataSizeOffset[offsetof(WaveData, data_size_18) == 0x18 ? 1 : -1];

} // namespace th105
