#include "AudioSchedulerRuntime.hpp"

namespace th105 {

extern "C" __declspec(dllimport) unsigned __stdcall timeBeginPeriod(unsigned);
unsigned long __stdcall AudioScheduler_thread_main(void *);

AudioSchedulerState::AudioSchedulerState()
{
    tick_interval_24 = 16;
    wait_adjustment_28 = 0;
    running_38 = 1;
    timeBeginPeriod(1);
    listeners_2c.clear();
    thread_1c.start(AudioScheduler_thread_main, 0);
    thread_1c.set_priority(15);
}

} // namespace th105
