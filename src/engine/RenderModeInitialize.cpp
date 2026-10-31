#include "engine/RenderModeManager.hpp"
#include "engine/D3DBackendListenerRuntime.cpp"
#include "engine/CriticalSectionWrapper.cpp"
#include "battle/BattleBaseEffectInitialize.cpp"
namespace th105 {
bool initialize_render_mode_manager()
{
    g_render_mode_manager.device_04 = g_d3d_backend.device_020;
    d3d_backend_listener_runtime()->register_reset_listener(&g_render_mode_manager);
    g_render_mode_manager.clear_color_30 = 0;
    g_render_mode_manager.reset_flag_2a = 0;
    g_render_mode_manager.state_2c = 0;
    g_d3d_backend.device_020->Clear(0, 0, 3, 0, 1.0f, 0);
    g_render_mode_manager.device_04->SetRenderState(58, 255);
    g_render_mode_manager.device_04->Clear(0, 0, 4, 0, 1.0f, 0);
    return true;
}
}
