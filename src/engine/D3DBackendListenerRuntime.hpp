#pragma once

#include "D3DBackend.hpp"

#include <list>
#include <stddef.h>

namespace th105 {

struct DeviceResetListener;

struct D3DBackendListenerRuntimeView {
    CriticalSectionWrapper critical_section_000;
    unsigned char reserved_01c[0x190];
    std::list<DeviceResetListener *> reset_listeners_1ac;

    void register_reset_listener(DeviceResetListener *listener);
};

typedef char D3DBackendListenerListOffset[
    offsetof(D3DBackendListenerRuntimeView, reset_listeners_1ac) == 0x1ac ? 1 : -1];

inline D3DBackendListenerRuntimeView *d3d_backend_listener_runtime()
{
    return reinterpret_cast<D3DBackendListenerRuntimeView *>(&g_d3d_backend);
}

} // namespace th105
