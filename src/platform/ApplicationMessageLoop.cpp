#include "engine/D3DBackend.hpp"

namespace th105 {
struct ApplicationMessage28 {
    void *window_00;
    unsigned message_04;
    unsigned wparam_08;
    long lparam_0c;
    unsigned time_10;
    long point_x_14, point_y_18;
};
extern "C" __declspec(dllimport) void *__stdcall CreateEventA(void *, int, int, const char *);
extern "C" __declspec(dllimport) int __stdcall CloseHandle(void *);
extern "C" __declspec(dllimport) unsigned long __stdcall WaitForSingleObject(void *, unsigned long);
extern "C" __declspec(dllimport) int __stdcall PeekMessageA(ApplicationMessage28 *, void *, unsigned, unsigned, unsigned);
extern "C" __declspec(dllimport) int __stdcall GetMessageA(ApplicationMessage28 *, void *, unsigned, unsigned);
extern "C" __declspec(dllimport) int __stdcall TranslateMessage(const ApplicationMessage28 *);
extern "C" __declspec(dllimport) long __stdcall DispatchMessageA(const ApplicationMessage28 *);
bool __cdecl reset_application_d3d_device();
struct ApplicationMessageLoopView {
    unsigned char unreviewed_000[0x4c];
    bool running_04c;
    void run();
};
void ApplicationMessageLoopView::run()
{
    ApplicationMessage28 message;
    void *event = CreateEventA(0, 0, 0, 0);
    while (running_04c) {
        if (PeekMessageA(&message, 0, 0, 0, 0)) {
            if (!GetMessageA(&message, 0, 0, 0))
                break;
            TranslateMessage(&message);
            DispatchMessageA(&message);
        } else {
            if (g_d3d_backend.device_020)
                g_d3d_backend.cooperative_result_1a4 =
                    g_d3d_backend.device_020->TestCooperativeLevel();
            if (g_d3d_backend.cooperative_result_1a4 == static_cast<long>(0x88760869u))
                reset_application_d3d_device();
            WaitForSingleObject(event, 4);
        }
    }
    CloseHandle(event);
}
typedef char ApplicationMessageSize[sizeof(ApplicationMessage28) == 28 ? 1 : -1];
typedef char ApplicationRunningOffset[offsetof(ApplicationMessageLoopView, running_04c) == 0x4c ? 1 : -1];
} // namespace th105
