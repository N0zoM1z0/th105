#include "RenderModeManager.hpp"

#include "ui/Title.hpp"

#include <string.h>

namespace th105 {

bool RenderModeManager::begin_frame()
{
    if (TryEnterCriticalSection(
            &g_d3d_backend.critical_section_000.critical_section_04) > 0) {
        if (g_d3d_backend.device_020->BeginScene() == 0)
            return true;
        LeaveCriticalSection(
            &g_d3d_backend.critical_section_000.critical_section_04);
    }
    return false;
}

void RenderModeManager::finish_frame()
{
    device_04->EndScene();
    LeaveCriticalSection(
        &g_d3d_backend.critical_section_000.critical_section_04);
}

void RenderModeManager::prepare_frame()
{
    g_d3d_backend.device_020->Clear(
        0, 0, 3, clear_color_30, 1.0f, 0);
}

void RenderModeManager::set_state_22(int mode)
{
    if (state_0c.state_22_08 == mode)
        return;
    switch (mode) {
    case 1:
        g_d3d_backend.device_020->SetRenderState(22, 1);
        break;
    case 2:
        g_d3d_backend.device_020->SetRenderState(22, 2);
        break;
    case 3:
        g_d3d_backend.device_020->SetRenderState(22, 3);
        break;
    }
    state_0c.state_22_08 = mode;
}

int RenderModeManager::apply_render_mode(int mode, unsigned char flag)
{
    int result = mode - 1;
    switch (mode) {
    case 4:
        result = g_d3d_backend.device_020->Clear(
            0, 0, 4, 0, 1.0f, flag);
        break;

    case 1:
        if (flag) {
            g_d3d_backend.device_020->SetRenderState(52, 1);
            g_d3d_backend.device_020->SetRenderState(7, 1);
            g_d3d_backend.device_020->SetRenderState(14, 0);
            result = g_d3d_backend.device_020->SetRenderState(23, 1);
        } else {
            if (!state_0c.gate_7_10)
                g_d3d_backend.device_020->SetRenderState(7, 0);
            if (state_0c.gate_14_11)
                g_d3d_backend.device_020->SetRenderState(14, 1);
            g_d3d_backend.device_020->SetRenderState(
                23, state_0c.state_23_14);
            result = g_d3d_backend.device_020->SetRenderState(52, 0);
        }
        break;

    case 2:
        g_d3d_backend.device_020->SetRenderState(56, 8);
        g_d3d_backend.device_020->SetRenderState(57, flag);
        result = g_d3d_backend.device_020->SetRenderState(54, 3);
        break;

    case 3:
        if (!state_0c.gate_7_10)
            g_d3d_backend.device_020->SetRenderState(7, 0);
        if (state_0c.gate_14_11)
            g_d3d_backend.device_020->SetRenderState(14, 1);
        g_d3d_backend.device_020->SetRenderState(
            23, state_0c.state_23_14);
        g_d3d_backend.device_020->SetRenderState(56, 5);
        result = g_d3d_backend.device_020->SetRenderState(57, flag);
        break;

    default:
        break;
    }

    state_0c.current_mode_0c = mode;
    state_0c.mode_flag_1a = flag;
    return result;
}

void RenderModeManager::on_device_reset()
{
    for (int i = 0; i < 8; ++i) {
        g_d3d_backend.device_020->SetTexture(i, 0);
        g_title_resource_manager.cached_handles_64[i] = 0;
    }

    RenderModeState28 saved = state_0c;
    memset(&state_0c, 0, sizeof(state_0c));
    reset_flag_2a = 0;

    set_pair_state(saved.pair_first_18, saved.pair_second_19);
    device_04->SetRenderState(7, saved.gate_7_10);
    device_04->SetRenderState(14, saved.gate_14_11);
    state_0c.gate_7_10 = saved.gate_7_10;
    state_0c.gate_14_11 = saved.gate_14_11;
    device_04->SetRenderState(23, saved.state_23_14);
    state_0c.state_23_14 = saved.state_23_14;

    set_mode(saved.sampler_mode_04);
    set_blend_mode(saved.blend_mode_00);

    if (state_0c.state_22_08 != saved.state_22_08) {
        switch (saved.state_22_08) {
        case 1:
            g_d3d_backend.device_020->SetRenderState(22, 1);
            break;
        case 2:
            g_d3d_backend.device_020->SetRenderState(22, 2);
            break;
        case 3:
            g_d3d_backend.device_020->SetRenderState(22, 3);
            break;
        }
        state_0c.state_22_08 = saved.state_22_08;
    }

    device_04->SetRenderState(58, 255);
    device_04->Clear(0, 0, 4, 0, 1.0f, 0);
}

} // namespace th105
