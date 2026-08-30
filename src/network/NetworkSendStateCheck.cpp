#include <vector>
#include <stddef.h>

namespace th105 {

extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(void *critical);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(void *critical);

struct NetworkSendRecord20 {
    unsigned char reserved_00[0x10];
    int state_10;
    unsigned int age_14;
    unsigned char reserved_18[8];
};

struct RawCriticalSection18 {
    unsigned char storage_00[0x18];
};

struct NetworkSendStateView {
    unsigned char reserved_000[0x80];
    void *callback_080;
    unsigned char reserved_084[0x04];
    RawCriticalSection18 critical_088;
    unsigned char reserved_0a0[0x68];
    std::vector<NetworkSendRecord20> records_108;
    unsigned char reserved_118[0x0c];
    RawCriticalSection18 critical_124;

    void publish_callback(void *callback);
    bool check(int index);
};

void NetworkSendStateView::publish_callback(void *callback)
{
    EnterCriticalSection(&critical_088);
    callback_080 = callback;
    LeaveCriticalSection(&critical_088);
}

bool NetworkSendStateView::check(int index)
{
    EnterCriticalSection(&critical_124);
    if (records_108[index].state_10 == -1) {
        LeaveCriticalSection(&critical_124);
        return true;
    }

    bool result = records_108[index].age_14 > 10;
    LeaveCriticalSection(&critical_124);
    return result;
}

typedef char NetworkSendRecord20_size_must_be_0x20[
    sizeof(NetworkSendRecord20) == 0x20 ? 1 : -1];
typedef char NetworkSendState_callback_offset[
    offsetof(NetworkSendStateView, callback_080) == 0x080 ? 1 : -1];
typedef char NetworkSendState_critical_088_offset[
    offsetof(NetworkSendStateView, critical_088) == 0x088 ? 1 : -1];
typedef char NetworkSendState_records_offset[
    offsetof(NetworkSendStateView, records_108) == 0x108 ? 1 : -1];
typedef char NetworkSendState_critical_offset[
    offsetof(NetworkSendStateView, critical_124) == 0x124 ? 1 : -1];

} // namespace th105
