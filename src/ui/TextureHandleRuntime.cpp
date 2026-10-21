// Genuine C++ texture-handle provider hypothesis; not selected for exact credit.
// Public release remains119/115; see docs/DESIGN_OBJECT_EMPTY_VIRTUALS_2026_10_21.md.
#include "ui/Title.hpp"
#include "engine/D3DBackend.hpp"
#include <deque>
#include <list>
#include <vector>

namespace th105 {
extern void *g_title_texture_cache_host;

struct TextureTokenManager {
    void release(unsigned int packed_token);
    void *vtable_00;
    std::deque<void *> cells_04;
    std::vector<void **> slots_18;
    std::vector<unsigned int> generations_28;
    std::list<unsigned int> free_slots_38;
    unsigned int generation_44;
    CriticalSectionWrapper lock_48;
};

void TextureTokenManager::release(unsigned int packed_token)
{
    const ResourceHandleToken &token =
        *reinterpret_cast<const ResourceHandleToken *>(&packed_token);
    EnterCriticalSection(&lock_48.critical_section_04);
    if (generations_28[token.slot_00] == token.generation_02) {
        generations_28[token.slot_00] = 0;
        free_slots_38.push_back(token.slot_00);
    }
    LeaveCriticalSection(&lock_48.critical_section_04);
}

unsigned char TitleResourceManager::release_title_resource_handle(unsigned int handle)
{
    if (handle == 0)
        return 0;
    for (int stage = 0; stage < 8; ++stage) {
        if (cached_handles_64[stage] == handle) {
            static_cast<D3DDevice9 *>(g_title_texture_cache_host)->SetTexture(stage, 0);
            cached_handles_64[stage] = 0;
        }
    }
    void **texture = lookup_token(handle);
    if (*texture != 0) {
        static_cast<D3DUnknown *>(*texture)->Release();
        *texture = 0;
    }
    reinterpret_cast<TextureTokenManager *>(this)->release(handle);
    return 1;
}

typedef char TextureTokenManagerSize[sizeof(TextureTokenManager) == 0x64 ? 1 : -1];
typedef char TextureTokenManagerSlots[offsetof(TextureTokenManager, slots_18) == 0x18 ? 1 : -1];
typedef char TextureTokenManagerGenerations[offsetof(TextureTokenManager, generations_28) == 0x28 ? 1 : -1];
typedef char TextureTokenManagerFreeSlots[offsetof(TextureTokenManager, free_slots_38) == 0x38 ? 1 : -1];
typedef char TextureTokenManagerLock[offsetof(TextureTokenManager, lock_48) == 0x48 ? 1 : -1];
} // namespace th105

namespace th105 {
class ScopedTextureTokenLock {
public:
    explicit ScopedTextureTokenLock(CriticalSectionWrapper *lock) : lock_(lock)
    { EnterCriticalSection(&lock_->critical_section_04); }
    ~ScopedTextureTokenLock()
    { LeaveCriticalSection(&lock_->critical_section_04); }
private:
    CriticalSectionWrapper *lock_;
};

void **CHandleManager4::lookup_token(unsigned int packed_token)
{
    TextureTokenManager &manager = *reinterpret_cast<TextureTokenManager *>(this);
    ScopedTextureTokenLock scope(&manager.lock_48);
    const ResourceHandleToken &token =
        *reinterpret_cast<const ResourceHandleToken *>(&packed_token);
    if (manager.generations_28.size() <= token.slot_00
        || manager.generations_28[token.slot_00] != token.generation_02)
        return 0;
    return manager.slots_18.at(token.slot_00);
}
} // namespace th105
