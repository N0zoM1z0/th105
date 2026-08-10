#include "OggDataSource.hpp"
#include "../assets/FileReader.hpp"

#include <cstdlib>
#include <cstring>

namespace th105 {

void load_sfl_loop_metadata(
    const char *audio_path,
    OggDataSource *source)
{
    char metadata_path[260];
    strcpy_s(metadata_path, sizeof(metadata_path), audio_path);

    unsigned long path_length = std::strlen(audio_path);
    metadata_path[path_length - 3] = 's';
    metadata_path[path_length - 2] = 'f';
    metadata_path[path_length - 1] = 'l';

    FileReaderOwner file;
    if (!file.open(metadata_path) || file.reader->size() == 0)
        return;

    unsigned long size = file.reader->size();
    unsigned char *data = static_cast<unsigned char *>(std::malloc(size));
    file.reader->read(data, size);

    unsigned long cue_position = 0;
    unsigned long adtl_length = 0;
    for (int index = 0; index < static_cast<int>(size - 3); index++) {
        if (data[index] == 'c' &&
            data[index + 1] == 'u' &&
            data[index + 2] == 'e') {
            cue_position = *reinterpret_cast<unsigned long *>(
                data + index + 0x10);
        } else if (data[index] == 'a' &&
                   data[index + 1] == 'd' &&
                   data[index + 2] == 't' &&
                   data[index + 3] == 'l') {
            adtl_length = *reinterpret_cast<unsigned long *>(
                data + index + 0x10);
        }
    }

    if (cue_position != 0 && adtl_length != 0) {
        unsigned long sample_rate = source->wave_format.samples_per_second;
        source->loop_start =
            static_cast<double>(cue_position) / static_cast<double>(sample_rate);
        source->loop_end = static_cast<double>(cue_position + adtl_length) /
                           static_cast<double>(sample_rate);
    }

    std::free(data);
}

} // namespace th105
