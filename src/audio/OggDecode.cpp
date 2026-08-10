#include "DirectSound.hpp"
#include "OggDataSource.hpp"

#include <cstring>

namespace th105 {

extern "C" long __cdecl ov_read(
    OggVorbisFile *file,
    char *buffer,
    int length,
    int big_endian,
    int word_size,
    int is_signed,
    int *bitstream);
extern "C" double __cdecl ov_time_tell(OggVorbisFile *file);
extern "C" int __cdecl ov_time_seek(OggVorbisFile *file, double time);

unsigned long __stdcall decode_ogg_pcm_block(
    OggDataSource *source,
    void *pcm_buffer)
{
    unsigned long written = 0;
    do {
        unsigned long request = 0x8000 - written;
        if (request >= 0x1000)
            request = 0x1000;

        int bitstream;
        long count = ov_read(
            &source->vorbis_file,
            static_cast<char *>(pcm_buffer) + written,
            request,
            0,
            2,
            1,
            &bitstream);
        volatile double current_time = ov_time_tell(&source->vorbis_file);

        if (count == 0) {
            if (source->loop_end == 0.0) {
                std::memset(
                    static_cast<char *>(pcm_buffer) + written,
                    0,
                    0x8000 - written);
                return written;
            }
            ov_time_seek(&source->vorbis_file, 0.0);
        } else if (source->loop_end > 0.0 && current_time > source->loop_end) {
            ov_time_seek(
                &source->vorbis_file,
                current_time - source->loop_end + source->loop_start);
        }

        written += count;
    } while (written < 0x8000);
    return 0x8000;
}

} // namespace th105
