#include "battle/BattleBaseEffectLifetime.hpp"
#include "D3DBackendListenerRuntime.hpp"
#include <algorithm>
namespace th105 {
extern "C" void __stdcall remove_battle_base_effect(BattleBaseEffectLifetimeView *effect)
{
    D3DBackendListenerRuntimeView *backend = d3d_backend_listener_runtime();
    backend->critical_section_000.enter();
    DeviceResetListener *listener = reinterpret_cast<DeviceResetListener *>(effect);
    std::list<DeviceResetListener *>::iterator found =
        std::find(backend->reset_listeners_1ac.begin(), backend->reset_listeners_1ac.end(), listener);
    if (found != backend->reset_listeners_1ac.end())
        backend->reset_listeners_1ac.erase(found);
    backend->critical_section_000.leave();
}
}
