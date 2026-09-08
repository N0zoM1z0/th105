#include "RenderModeManager.hpp"

namespace th105 {

struct BgmBootstrapServiceView {
    void initialize_403460();
};

struct WaveBootstrapServiceView {
    void initialize_401990();
};

extern BgmBootstrapServiceView g_bgm_bootstrap_service;
extern WaveBootstrapServiceView g_wave_bootstrap_service;

void __cdecl initialize_scene_resources_43e2e0();
unsigned char __cdecl start_async_engine_scene_load(int scene);

struct CSceneManager {
    virtual void initialize();
};

void CSceneManager::initialize()
{
    g_render_mode_manager.set_mode(1);
    g_render_mode_manager.set_state_22(1);
    g_render_mode_manager.set_gate_states(0, 0);
    g_render_mode_manager.set_pair_state(1, 1);
    g_render_mode_manager.set_blend_mode(1);
    g_render_mode_manager.set_sampler_state(0, 1, 1);
    g_render_mode_manager.set_sampler_state(0, 2, 1);
    g_render_mode_manager.set_sampler_state(1, 1, 1);
    g_render_mode_manager.set_sampler_state(1, 2, 1);

    g_bgm_bootstrap_service.initialize_403460();
    g_wave_bootstrap_service.initialize_401990();
    initialize_scene_resources_43e2e0();
    start_async_engine_scene_load(1);
}

} // namespace th105
