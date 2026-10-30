#include "engine/RenderModeManager.hpp"
namespace th105 {
extern "C" __declspec(dllimport) int __stdcall GetSystemMetrics(int index);
extern "C" __declspec(dllimport) int __stdcall SetWindowPos(void *,void *,int,int,int,int,unsigned);

bool reset_application_d3d_device()
{
    if (!g_d3d_backend.direct3d_01c || !g_d3d_backend.device_020
        || g_d3d_backend.cooperative_result_1a4 == static_cast<long>(0x88760868))
        return false;
    g_d3d_backend.presentation_158.back_buffer_format_08 =
        g_d3d_backend.presentation_158.windowed_20 ? g_d3d_backend.display_mode_190.format_0c : 22;
    EnterCriticalSection(&g_d3d_backend.critical_section_000.critical_section_04);
    for (std::list<DeviceResetListener *>::iterator it = g_d3d_backend.reset_listeners_1ac.begin();
         it != g_d3d_backend.reset_listeners_1ac.end(); ++it)
        (*it)->on_device_lost();
    if (g_d3d_backend.swap_chain_024) {
        g_d3d_backend.swap_chain_024->Release();
        g_d3d_backend.swap_chain_024 = 0;
    }
    if (g_d3d_backend.device_020->Reset(&g_d3d_backend.presentation_158) < 0) {
        LeaveCriticalSection(&g_d3d_backend.critical_section_000.critical_section_04);
        return false;
    }
    g_d3d_backend.device_020->GetSwapChain(0,reinterpret_cast<void **>(&g_d3d_backend.swap_chain_024));
    for (std::list<DeviceResetListener *>::iterator it = g_d3d_backend.reset_listeners_1ac.begin();
         it != g_d3d_backend.reset_listeners_1ac.end(); ++it)
        (*it)->on_device_reset();
    LeaveCriticalSection(&g_d3d_backend.critical_section_000.critical_section_04);
    return true;
}

void toggle_application_window_mode()
{
    g_d3d_backend.presentation_158.windowed_20 = !g_d3d_backend.presentation_158.windowed_20;
    if (!reset_application_d3d_device()) {
        g_d3d_backend.presentation_158.windowed_20 = !g_d3d_backend.presentation_158.windowed_20;
        return;
    }
    if (g_d3d_backend.presentation_158.windowed_20) {
        int width = static_cast<int>(g_d3d_backend.presentation_158.back_buffer_width_00)
            + GetSystemMetrics(5) + GetSystemMetrics(7) + GetSystemMetrics(45);
        int height = static_cast<int>(g_d3d_backend.presentation_158.back_buffer_height_04)
            + GetSystemMetrics(4) + GetSystemMetrics(6) + GetSystemMetrics(8) + GetSystemMetrics(46);
        int x = (GetSystemMetrics(0) - width) / 2;
        int y = (GetSystemMetrics(1) - height) / 2;
        SetWindowPos(g_d3d_backend.presentation_158.device_window_1c,
            reinterpret_cast<void *>(-2),x,y,width,height,0x20);
    } else {
        // The native fullscreen branch performs these seven API calls before
        // recomputing its offsets; their return values are discarded.
        GetSystemMetrics(45); GetSystemMetrics(7); GetSystemMetrics(5);
        GetSystemMetrics(46); GetSystemMetrics(8); GetSystemMetrics(6); GetSystemMetrics(4);
        int x = -(GetSystemMetrics(5) + GetSystemMetrics(7) + GetSystemMetrics(45)) / 2;
        int y = -(GetSystemMetrics(6) + GetSystemMetrics(8) + GetSystemMetrics(46)) / 2 - GetSystemMetrics(4);
        SetWindowPos(g_d3d_backend.presentation_158.device_window_1c,0,x,y,0,0,0x21);
    }
}
}
