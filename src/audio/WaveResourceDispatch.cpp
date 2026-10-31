// Real reader/package/CRC source context; original translation unit unknown.
#include "assets/CsvFileLoading.cpp"
#include "audio/WaveDataRuntime.cpp"
#include <cstring>
namespace th105 {
extern "C" bool __fastcall dispatch_wave_resource(WaveData *output, const char *path)
{
    if (g_bootstrap_mode) {
        unsigned length = std::strlen(path);
        char filename[260];
        strcpy_s(filename, sizeof(filename), path);
        std::memcpy(filename + length - 4, ".cv3", 4);
        return load_cv3_wave_data(output, filename);
    }
    return load_wave_data(output, path);
}
}
