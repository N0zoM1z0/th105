#include "D3DBackend.hpp"

namespace th105 {

D3DBackend::D3DBackend()
{
    direct3d_01c = 0;
    device_020 = 0;
    swap_chain_024 = 0;
    unknown_1a8 = 0;
}

D3DBackend::~D3DBackend()
{
    shutdown_d3d_backend();
}

D3DBackend g_d3d_backend;

typedef char D3DBackendLifetimeSize[sizeof(D3DBackend) == 0x1b8 ? 1 : -1];

} // namespace th105
