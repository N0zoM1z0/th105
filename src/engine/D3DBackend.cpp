#include "D3DBackend.hpp"

namespace th105 {

void shutdown_d3d_backend()
{
    if (g_d3d_backend.swap_chain_024 != 0) {
        g_d3d_backend.swap_chain_024->Release();
        g_d3d_backend.swap_chain_024 = 0;
    }
    if (g_d3d_backend.device_020 != 0) {
        g_d3d_backend.device_020->Release();
        g_d3d_backend.device_020 = 0;
    }
    if (g_d3d_backend.direct3d_01c != 0) {
        g_d3d_backend.direct3d_01c->Release();
        g_d3d_backend.direct3d_01c = 0;
    }
}

} // namespace th105
