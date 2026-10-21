#include "OggDataSource.hpp"
#include <string.h>
#include <stddef.h>

// Preserve the target's qword current_time materialization before either
// read-result path. Default FP keeps that value only in extended x87 state.
#pragma float_control(except, off, push)

namespace th105 {

extern "C" long __cdecl ov_read(
    OggVorbisFile *file,
    char *buffer,
    int length,
    int big_endian,
    int word_size,
    int signed_samples,
    int *bitstream);
extern "C" double __cdecl ov_time_tell(OggVorbisFile *file);
extern "C" int __cdecl ov_time_seek(OggVorbisFile *file, double position);

unsigned int __stdcall fill_ogg_pcm_block(
    OggDataSource *source,
    void *destination)
{
    unsigned int total = 0;
    // ov_read owns this out-parameter; the target performs no initial store.
    int bitstream;
    char *output = static_cast<char *>(destination);

    for (;;) {
        // The target uses an unsigned JB when clamping the remaining count.
        unsigned int amount = 0x8000 - total;
        if (amount >= 0x1000)
            amount = 0x1000;
        int bytes_read = ov_read(
            &source->vorbis_file,
            output + total,
            amount,
            0,
            2,
            1,
            &bitstream);
        double current_time = ov_time_tell(&source->vorbis_file);
        if (bytes_read == 0) {
            if (source->loop_end == 0.0)
                break;
            ov_time_seek(&source->vorbis_file, 0.0);
        } else {
            if (source->loop_end > 0.0 && current_time > source->loop_end) {
                ov_time_seek(
                    &source->vorbis_file,
                    current_time - source->loop_end + source->loop_start);
            }
        }
        total += bytes_read;
        if (total >= 0x8000)
            return 0x8000;
    }

    memset(output + total, 0, 0x8000 - total);
    return total;
}

typedef char OggPcmFileOffset[
    offsetof(OggDataSource, vorbis_file) == 0x10 ? 1 : -1];
typedef char OggPcmLoopStartOffset[
    offsetof(OggDataSource, loop_start) == 0x12e8 ? 1 : -1];
typedef char OggPcmLoopEndOffset[
    offsetof(OggDataSource, loop_end) == 0x12f0 ? 1 : -1];

} // namespace th105

#pragma float_control(pop)
