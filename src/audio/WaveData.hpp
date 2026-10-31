#pragma once

#include <new>
namespace th105 {

struct WaveFormatExStorage20 {
    unsigned short format_tag_00;
    unsigned short channels_02;
    unsigned int samples_per_second_04;
    unsigned int average_bytes_per_second_08;
    unsigned short block_align_0c;
    unsigned short bits_per_sample_0e;
    unsigned short extra_size_10;
    unsigned short padding_12;
};

struct WaveData {
    WaveFormatExStorage20 format_00;
    unsigned char *data_14;
    unsigned int data_size_18;
    WaveData() : data_14(0), data_size_18(0) {}
    ~WaveData() { if (data_14 != 0) delete[] data_14; }
};

} // namespace th105
