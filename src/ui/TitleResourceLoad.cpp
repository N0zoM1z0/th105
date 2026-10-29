#include "Title.hpp"
#include "network/NetworkUdpPacketPool.hpp"

namespace th105 {
// Pointer-only acquisition view. Its native private EDI entry is not invented
// as a C++ calling convention; the ordinary member remains a nonexact boundary.
struct TitleResourceAcquireView {
    void **acquire(unsigned int *token);
};
extern "C" long __fastcall TextureLoader_load_bitmap_to_resource_cell(
    unsigned int *height, const char *path, void **cell, unsigned int *width);

unsigned int *TitleResourceManager::load_texture(
    unsigned int *result, const char *path,
    unsigned int *width, unsigned int *height)
{
    unsigned int token = 0;
    void **cell = reinterpret_cast<TitleResourceAcquireView *>(this)->acquire(&token);
    *cell = 0;
    if (TextureLoader_load_bitmap_to_resource_cell(height, path, cell, width) < 0) {
        // The matched release body only accesses the shared generation/list/lock
        // prefix, independently of the manager's payload specialization.
        reinterpret_cast<NetworkUdpPacketHandleManager64 *>(this)->release(token);
        *result = 0;
        return result;
    }
    *result = token;
    return result;
}
} // namespace th105
