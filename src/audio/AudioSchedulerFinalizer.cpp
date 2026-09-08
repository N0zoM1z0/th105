#include "AudioSchedulerRuntime.hpp"

namespace th105 {

extern "C" __declspec(dllimport) int __stdcall SetEvent(void *event_handle);
extern "C" __declspec(dllimport) int __stdcall CloseHandle(void *handle);

void __cdecl finalize_audio_scheduler_state()
{
    g_audio_scheduler_state.running_38 = 0;
    g_audio_scheduler_state.thread_1c.wait_for_exit();
    EnterCriticalSection(
        &g_audio_scheduler_state.critical_section_00.critical_section_04);

    for (std::list<void *>::iterator it = g_audio_scheduler_state.listeners_2c.begin();
         it != g_audio_scheduler_state.listeners_2c.end();
         ++it) {
        SetEvent(*it);
        CloseHandle(*it);
    }
    g_audio_scheduler_state.listeners_2c.clear();

    LeaveCriticalSection(
        &g_audio_scheduler_state.critical_section_00.critical_section_04);
    g_audio_scheduler_state.listeners_2c.~list();
    g_audio_scheduler_state.thread_1c.wait_for_exit();
    g_audio_scheduler_state.critical_section_00.~CriticalSectionWrapper();
}

} // namespace th105
