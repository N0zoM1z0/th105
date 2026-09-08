#include "AudioSchedulerRuntime.hpp"

namespace th105 {

extern "C" __declspec(dllimport) void *__stdcall CreateEventA(
    void *attributes,
    int manual_reset,
    int initial_state,
    const char *name);
extern "C" __declspec(dllimport) int __stdcall SetEvent(void *event_handle);
extern "C" __declspec(dllimport) int __stdcall CloseHandle(void *handle);
extern "C" __declspec(dllimport) int __stdcall TryEnterCriticalSection(
    Win32CriticalSection24 *critical_section);
extern "C" __declspec(dllimport) unsigned long __stdcall WaitForSingleObject(
    void *handle,
    unsigned long milliseconds);

void *__cdecl create_audio_scheduler_listener_event()
{
    void *empty_handle = 0;
    EnterCriticalSection(&g_audio_scheduler_state.critical_section_00.critical_section_04);
    g_audio_scheduler_state.listeners_2c.push_back(empty_handle);
    g_audio_scheduler_state.listeners_2c.back() = CreateEventA(0, 0, 0, 0);
    LeaveCriticalSection(&g_audio_scheduler_state.critical_section_00.critical_section_04);
    return g_audio_scheduler_state.listeners_2c.back();
}

int __stdcall remove_audio_scheduler_listener_event(void *handle)
{
    int result = 0;
    EnterCriticalSection(&g_audio_scheduler_state.critical_section_00.critical_section_04);
    for (std::list<void *>::iterator it = g_audio_scheduler_state.listeners_2c.begin();
         it != g_audio_scheduler_state.listeners_2c.end();
         ++it) {
        if (*it == handle) {
            SetEvent(*it);
            result = CloseHandle(*it);
            g_audio_scheduler_state.listeners_2c.erase(it);
            break;
        }
    }
    LeaveCriticalSection(&g_audio_scheduler_state.critical_section_00.critical_section_04);
    return result;
}

int __stdcall wait_audio_scheduler_listener_event(void *handle)
{
    if (TryEnterCriticalSection(
            &g_audio_scheduler_state.critical_section_00.critical_section_04) > 0) {
        std::list<void *>::iterator it = g_audio_scheduler_state.listeners_2c.begin();
        std::list<void *>::iterator end = g_audio_scheduler_state.listeners_2c.end();
        for (; it != end; ++it) {
            if (*it == handle)
                break;
        }
        LeaveCriticalSection(&g_audio_scheduler_state.critical_section_00.critical_section_04);
        if (it != end)
            WaitForSingleObject(*it, 0xFFFFFFFFu);
    }
    return 0;
}

} // namespace th105
