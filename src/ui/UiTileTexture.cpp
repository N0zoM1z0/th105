#include "UiPrimitives.hpp"

namespace th105 {

struct UiTileTextureRuntime {
    void set_texture_options(
        unsigned int handle,
        int x,
        int y,
        unsigned int width,
        unsigned int height,
        int option,
        int flags);
};

void UiTileA4::set_texture(
    unsigned int handle,
    int x,
    int y,
    unsigned int width,
    unsigned int height)
{
    reinterpret_cast<UiTileTextureRuntime *>(this)->set_texture_options(
        handle, x, y, width, height, 0, 0);
}

} // namespace th105
