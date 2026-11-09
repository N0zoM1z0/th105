// The real global owner gives VC8 its constant-receiver lifecycle context.
#include "audio/AudioSchedulerInitialization.cpp"
#include "platform/BattleThreadHandleRuntime.cpp"
#include "engine/CriticalSectionWrapper.cpp"


namespace th105 {

extern "C" __declspec(dllimport) int __stdcall SetEvent(void *event_handle);
extern "C" __declspec(dllimport) int __stdcall CloseHandle(void *handle);

AudioSchedulerState::~AudioSchedulerState()
{
    running_38 = 0;
    thread_1c.wait_for_exit();
    EnterCriticalSection(
        &critical_section_00.critical_section_04);

    for (std::list<void *>::iterator it = listeners_2c.begin(),
         end = listeners_2c.end();
         it != end;
         ++it) {
        SetEvent(*it);
        CloseHandle(*it);
    }
    listeners_2c.clear();

    LeaveCriticalSection(
        &critical_section_00.critical_section_04);
}

} // namespace th105

namespace th105 {
AudioSchedulerState g_audio_scheduler_state;
}
