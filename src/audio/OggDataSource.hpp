#pragma once

namespace th105 {

typedef long long OggOffset;

struct OggVorbisFile {
    unsigned char opaque[0x2d0];
};

struct VorbisInfo {
    long version;
    int channels;
    long sample_rate;
};

struct WaveFormat {
    unsigned short format_tag;
    unsigned short channels;
    unsigned long samples_per_second;
    unsigned long average_bytes_per_second;
    unsigned short block_align;
    unsigned short bits_per_sample;
    unsigned short extra_size;
};

struct OggDataSourceReader {
    virtual ~OggDataSourceReader() = 0;
    virtual long unknown_04() = 0;
    virtual long unknown_08() = 0;
    virtual long seek(long offset, int origin) = 0;
    virtual long size() = 0;
};

struct OggDataSource {
    OggDataSourceReader *reader;
    unsigned long stream_size;
    long position_adjustment;
    unsigned long unknown_0c;
    OggVorbisFile vorbis_file;
    VorbisInfo *vorbis_info;
    unsigned char unknown_2e4[0x1004];
    double loop_start;
    double loop_end;
    WaveFormat wave_format;

    bool open(const char *path);
    bool open_reader(const char *path);
};

void load_sfl_loop_metadata(
    const char *audio_path,
    OggDataSource *source);

} // namespace th105
