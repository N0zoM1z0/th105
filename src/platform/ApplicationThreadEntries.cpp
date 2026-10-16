// Native application thread callbacks; docs/APPLICATION_THREAD_ENTRIES_2026_10_16.md.
extern "C" __declspec(dllimport) long __stdcall CoInitialize(void *);
extern "C" __declspec(dllimport) void __stdcall CoUninitialize();

namespace th105 {
extern "C" void __cdecl application_control_worker();
extern "C" void __cdecl application_graphics_worker();

extern "C" unsigned long __stdcall bootstrap_control_thread(void *)
{
    if (CoInitialize(0) >= 0) {
        application_control_worker();
        CoUninitialize();
    }
    return 0;
}

extern "C" unsigned long __stdcall bootstrap_graphics_thread(void *)
{
    if (CoInitialize(0) >= 0) {
        application_graphics_worker();
        CoUninitialize();
    }
    return 0;
}
} // namespace th105
