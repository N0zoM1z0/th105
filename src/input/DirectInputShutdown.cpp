#include "input/InputManager.hpp"
#include <stddef.h>
struct _GUID;
namespace th105 {
// Actual IDirectInputDevice8 COM prefix. Uncalled descriptor types stay
// opaque; real virtual dispatch evaluates a checked vector receiver once.
struct DirectInputCapabilities;
struct DirectInputObjectInstance;
struct DirectInputPropertyHeader;
struct DirectInputUnknownPrefix {
    virtual long __stdcall QueryInterface(const _GUID &, void **) = 0;
    virtual unsigned long __stdcall AddRef() = 0;
    virtual unsigned long __stdcall Release() = 0;
};
struct DirectInputShutdownDevice : DirectInputUnknownPrefix {
    virtual long __stdcall GetCapabilities(DirectInputCapabilities *) = 0;
    virtual long __stdcall EnumObjects(int (__stdcall *)(const DirectInputObjectInstance *, void *), void *, unsigned long) = 0;
    virtual long __stdcall GetProperty(const _GUID &, DirectInputPropertyHeader *) = 0;
    virtual long __stdcall SetProperty(const _GUID &, const DirectInputPropertyHeader *) = 0;
    virtual long __stdcall Acquire() = 0;
    virtual long __stdcall Unacquire() = 0;
};
void shutdown_direct_input()
{
    if (g_direct_input_backend.mouse_device) {
        static_cast<DirectInputShutdownDevice *>(g_direct_input_backend.mouse_device)->Unacquire();
        static_cast<DirectInputShutdownDevice *>(g_direct_input_backend.mouse_device)->Release();
        g_direct_input_backend.mouse_device = 0;
    }
    if (g_direct_input_backend.keyboard_device) {
        static_cast<DirectInputShutdownDevice *>(g_direct_input_backend.keyboard_device)->Unacquire();
        static_cast<DirectInputShutdownDevice *>(g_direct_input_backend.keyboard_device)->Release();
        g_direct_input_backend.keyboard_device = 0;
    }
    for (unsigned index = 0; index < g_direct_input_backend.gamepad_devices.size(); ++index) {
        if (g_direct_input_backend.gamepad_devices[index]) {
            static_cast<DirectInputShutdownDevice *>(g_direct_input_backend.gamepad_devices[index])->Unacquire();
            static_cast<DirectInputShutdownDevice *>(g_direct_input_backend.gamepad_devices[index])->Release();
            g_direct_input_backend.gamepad_devices[index] = 0;
        }
    }
    g_direct_input_backend.gamepad_devices.clear();
    g_direct_input_backend.gamepad_states.clear();
    g_direct_input_backend.gamepad_button_counts.clear();
    if (g_direct_input_backend.direct_input) {
        static_cast<DirectInputUnknownPrefix *>(g_direct_input_backend.direct_input)->Release();
        g_direct_input_backend.direct_input = 0;
    }
}
}

namespace th105 {
typedef char ShutdownDeviceVectorOffset[offsetof(DirectInputBackend,gamepad_devices)==0x10?1:-1];
typedef char ShutdownStateVectorOffset[offsetof(DirectInputBackend,gamepad_states)==0x124?1:-1];
typedef char ShutdownButtonVectorOffset[offsetof(DirectInputBackend,gamepad_button_counts)==0x134?1:-1];
}
