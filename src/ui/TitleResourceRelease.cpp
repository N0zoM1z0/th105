#include "Title.hpp"
#include "assets/ResourceHandleLookupRuntime.hpp"
#include "network/NetworkUdpPacketPool.hpp"
#include "engine/D3DBackend.hpp"
#include "audio/DirectSound.hpp"

namespace th105 {
extern void *g_title_texture_cache_host;

unsigned char TitleResourceManager::release_title_resource_handle(unsigned int handle)
{
    if (handle == 0)
        return 0;
    unsigned int *cached = cached_handles_64;
    for (int stage = 0; stage < 8; ++stage, ++cached) {
        if (*cached == handle) {
            static_cast<D3DDevice9 *>(g_title_texture_cache_host)->SetTexture(stage, 0);
            *cached = 0;
        }
    }
    void **cell = reinterpret_cast<CHandleManagerLookupView *>(this)
        ->lookup_token_417800(handle);
    if (*cell != 0) {
        static_cast<UnknownInterface *>(*cell)->release();
        *cell = 0;
    }
    reinterpret_cast<NetworkUdpPacketHandleManager64 *>(this)->release(handle);
    return 1;
}
} // namespace th105
