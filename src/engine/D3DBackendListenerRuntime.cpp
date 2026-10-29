#include "D3DBackendListenerRuntime.hpp"
#include <algorithm>
namespace th105 {
void D3DBackendListenerRuntimeView::register_reset_listener(DeviceResetListener *listener)
{
    critical_section_000.enter();
    std::list<DeviceResetListener *>::iterator found =
        std::find(reset_listeners_1ac.begin(), reset_listeners_1ac.end(), listener);
    if (found == reset_listeners_1ac.end())
        reset_listeners_1ac.push_back(listener);
    critical_section_000.leave();
}
}
