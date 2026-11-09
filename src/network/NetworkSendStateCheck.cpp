#include "NetworkSendState.hpp"

namespace th105 {

extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(void *critical);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(void *critical);

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

} // namespace th105
