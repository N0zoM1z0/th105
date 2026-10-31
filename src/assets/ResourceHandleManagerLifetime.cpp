#include "assets/ResourceHandleManagerLifetime.hpp"
namespace th105 {
template struct ResourceHandleManagerLifetime64<WaveBufferResource *>;
template struct ResourceHandleManagerLifetime64<SoundBufferResource *>;
template struct ResourceHandleManagerLifetime64<TextureResource *>;
}
