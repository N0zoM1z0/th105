#include "assets/ResourceHandleManagerLifetime.hpp"
namespace th105 {
struct TextureServiceLifetime {
    ResourceHandleManagerLifetime64<TextureResource *> manager_00;
    unsigned cached_handles_64[8];
    TextureServiceLifetime()
    {
        for (unsigned i = 0; i < 8; ++i)
            cached_handles_64[i] = 0;
    }
};
TextureServiceLifetime g_texture_service_lifetime;
typedef char TextureServiceSize[sizeof(TextureServiceLifetime) == 0x84 ? 1 : -1];
typedef char TextureCacheOffset[offsetof(TextureServiceLifetime,cached_handles_64) == 0x64 ? 1 : -1];
}
