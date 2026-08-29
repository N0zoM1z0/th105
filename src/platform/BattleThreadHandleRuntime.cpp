namespace th105 {

extern "C" __declspec(dllimport) void *__stdcall CreateThread(
    void *attributes, unsigned long stack_size,
    unsigned long (__stdcall *start)(void *), void *parameter,
    unsigned long creation_flags, unsigned long *thread_id);
extern "C" __declspec(dllimport) int __stdcall GetExitCodeThread(
    void *thread, unsigned long *exit_code);
extern "C" __declspec(dllimport) int __stdcall SetThreadPriority(
    void *thread, int priority);
extern "C" __declspec(dllimport) int __stdcall CloseHandle(void *handle);

class BattleThreadHandle {
public:
    BattleThreadHandle() : handle_(0), thread_id_(0) {}
    ~BattleThreadHandle();

    bool start(unsigned long (__stdcall *entry)(void *), void *parameter);
    void wait_for_exit();
    int set_priority(int priority);
    bool is_running();

private:
    void *handle_;
    unsigned long thread_id_;
};

BattleThreadHandle::~BattleThreadHandle()
{
    wait_for_exit();
}

bool BattleThreadHandle::start(
    unsigned long (__stdcall *entry)(void *), void *parameter)
{
    wait_for_exit();
    handle_ = CreateThread(0, 0, entry, parameter, 0, &thread_id_);
    return handle_ != 0;
}

void BattleThreadHandle::wait_for_exit()
{
    if (handle_ != 0) {
        SetThreadPriority(handle_, 15);
        unsigned long exit_code = 259;
        while (exit_code == 259)
            GetExitCodeThread(handle_, &exit_code);
        CloseHandle(handle_);
        handle_ = 0;
    }
}

int BattleThreadHandle::set_priority(int priority)
{
    return SetThreadPriority(handle_, priority);
}

bool BattleThreadHandle::is_running()
{
    if (handle_ != 0) {
        unsigned long exit_code;
        GetExitCodeThread(handle_, &exit_code);
        return exit_code == 259;
    }
    return false;
}

typedef char BattleThreadHandle_size_must_be_8[
    sizeof(BattleThreadHandle) == 8 ? 1 : -1];

} // namespace th105
