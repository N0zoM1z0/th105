#include "D3DBackendListenerRuntime.hpp"

namespace th105 {

void D3DBackendListenerRuntimeView::register_reset_listener(
    DeviceResetListener *listener)
{
    critical_section_000.enter();
    for (std::list<DeviceResetListener *>::iterator it = reset_listeners_1ac.begin();
         it != reset_listeners_1ac.end(); ++it) {
        if (*it == listener) {
            critical_section_000.leave();
            return;
        }
    }
    reset_listeners_1ac.push_back(listener);
    critical_section_000.leave();
}

} // namespace th105
