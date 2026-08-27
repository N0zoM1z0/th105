namespace th105 {

extern "C" __declspec(dllimport) int __cdecl wsprintfA(
    char *destination,
    const char *format,
    ...);

struct OpaqueWaveHandleService {
    unsigned char opaque_00[0x68];

    unsigned *__thiscall load_wave_handle(
        unsigned *out_handle,
        const char *path);
};

extern OpaqueWaveHandleService g_wave_handle_service;
extern unsigned g_indexed_event_handles[128];
int __cdecl initialize_info_effect_lookup_map();

int __cdecl load_indexed_event_wave_resources()
{
    unsigned loaded_handle;
    char path[260];

    for (int index = 0; index < 128; ++index) {
        wsprintfA(path, "data/se/%03d.wav", index);
        g_indexed_event_handles[index] =
            *g_wave_handle_service.load_wave_handle(&loaded_handle, path);
    }

    return initialize_info_effect_lookup_map();
}

} // namespace th105
