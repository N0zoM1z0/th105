namespace th105 {

struct OpaqueWaveHandleService {
    unsigned char opaque_00[0x68];

    void dispatch_wave_handle(unsigned handle);
};

#pragma bss_seg(".bss$wave_manager")
OpaqueWaveHandleService g_wave_handle_service;
#pragma bss_seg(".bss$indexed_events")
unsigned g_indexed_event_handles[0x80];
#pragma bss_seg()

void dispatch_indexed_event(unsigned index)
{
    if (index <= 0x7f) {
        g_wave_handle_service.dispatch_wave_handle(
            g_indexed_event_handles[index]);
    }
}

} // namespace th105
