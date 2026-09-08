#pragma once

#include "../engine/CriticalSectionWrapper.hpp"

#include <list>

namespace th105 {

class BattleThreadHandle {
public:
    BattleThreadHandle();
    ~BattleThreadHandle();

    bool start(unsigned long (__stdcall *entry)(void *), void *parameter);
    void wait_for_exit();
    int set_priority(int priority);
    bool is_running();

private:
    void *handle_;
    unsigned long thread_id_;
};

struct AudioSchedulerState {
    CriticalSectionWrapper critical_section_00;
    BattleThreadHandle thread_1c;
    int tick_interval_24;
    int wait_adjustment_28;
    std::list<void *> listeners_2c;
    unsigned char running_38;
};

extern AudioSchedulerState g_audio_scheduler_state;

typedef char AudioSchedulerStateSize[
    sizeof(AudioSchedulerState) == 0x3C ? 1 : -1];

} // namespace th105
