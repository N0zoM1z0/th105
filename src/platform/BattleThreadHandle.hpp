#pragma once

namespace th105 {

// Shared nonvirtual handle/id pair used by the native thread owners.
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

typedef char BattleThreadHandle_size_must_be_8[
    sizeof(BattleThreadHandle) == 8 ? 1 : -1];

} // namespace th105
