#include "RenderModeManager.hpp"

#include "ui/Title.hpp"

namespace th105 {

bool present_d3d_frame()
{
    if (!g_render_mode_manager.reset_flag_2a)
        return false;

    if (TryEnterCriticalSection(
            &g_d3d_backend.critical_section_000.critical_section_04) <= 0)
        return false;

    if (g_d3d_backend.swap_chain_024->Present(0, 0, 0, 0, 1) != 0) {
        LeaveCriticalSection(
            &g_d3d_backend.critical_section_000.critical_section_04);
        return false;
    }

    g_render_mode_manager.reset_flag_2a = 0;
    LeaveCriticalSection(
        &g_d3d_backend.critical_section_000.critical_section_04);
    return true;
}

D3DHResult RenderModeManager::submit_primitive(
    unsigned primitive_type,
    unsigned primitive_count,
    const void *vertices,
    unsigned stride,
    unsigned fvf)
{
    device_04->SetFVF(fvf);
    return device_04->DrawPrimitiveUP(
        primitive_type, primitive_count, vertices, stride);
}

D3DHResult RenderModeManager::submit_textured_primitive(
    unsigned texture_handle,
    unsigned primitive_type,
    unsigned primitive_count,
    const void *vertices,
    unsigned stride,
    unsigned fvf)
{
    g_title_resource_manager.bind_texture(texture_handle, 0);
    device_04->SetFVF(fvf);
    return device_04->DrawPrimitiveUP(
        primitive_type, primitive_count, vertices, stride);
}

int RenderModeManager::draw_rect_int(
    const int *rect,
    unsigned color,
    unsigned char filled)
{
    return draw_rect(
        static_cast<float>(rect[0]),
        static_cast<float>(rect[1]),
        static_cast<float>(rect[2]),
        static_cast<float>(rect[3]),
        color,
        filled);
}

void RenderModeManager::set_mode(int mode)
{
    if (state_0c.sampler_mode_04 == mode)
        return;

    switch (mode) {
    case 1:
        device_04->SetSamplerState(0, 5, 1);
        device_04->SetSamplerState(0, 6, 1);
        device_04->SetSamplerState(0, 7, 1);
        break;
    case 2:
        device_04->SetSamplerState(0, 5, 2);
        device_04->SetSamplerState(0, 6, 2);
        device_04->SetSamplerState(0, 7, 2);
        break;
    }

    state_0c.sampler_mode_04 = mode;
}

} // namespace th105
