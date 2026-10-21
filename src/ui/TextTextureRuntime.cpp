// Source hypothesis for JP1.06a text-texture wrapper404D00 and backend4097A0.
// Complete canonical comparisons remain nonexact; no private ABI is fabricated.
// See docs/TEXT_TEXTURE_RUNTIME_2026_10_21.md.
#include "ui/Title.hpp"
#include "assets/TextFontRuntime.hpp"
#include "engine/D3DBackend.hpp"
#include <deque>
#include <list>
#include <vector>
#include <string.h>

namespace th105 {

struct TextTextureLockedRect {
    int pitch;
    void *bits;
};

struct TextTexture9 : D3DUnknown {
#define TEXT_TEXTURE_SLOT(N) virtual void __stdcall slot_##N() = 0;
    TEXT_TEXTURE_SLOT(3) TEXT_TEXTURE_SLOT(4) TEXT_TEXTURE_SLOT(5)
    TEXT_TEXTURE_SLOT(6) TEXT_TEXTURE_SLOT(7) TEXT_TEXTURE_SLOT(8)
    TEXT_TEXTURE_SLOT(9) TEXT_TEXTURE_SLOT(10) TEXT_TEXTURE_SLOT(11)
    TEXT_TEXTURE_SLOT(12) TEXT_TEXTURE_SLOT(13) TEXT_TEXTURE_SLOT(14)
    TEXT_TEXTURE_SLOT(15) TEXT_TEXTURE_SLOT(16) TEXT_TEXTURE_SLOT(17)
    TEXT_TEXTURE_SLOT(18)
#undef TEXT_TEXTURE_SLOT
    virtual long __stdcall LockRect(unsigned, TextTextureLockedRect *, const void *, unsigned) = 0;
    virtual long __stdcall UnlockRect(unsigned) = 0;
};

extern "C" long __stdcall D3DXCreateTexture(
    D3DDevice9 *, unsigned, unsigned, unsigned, unsigned, unsigned, unsigned,
    TextTexture9 **);

static long __stdcall populate_text_texture(TextTexture9 **texture,
    const char *text, TextTextureFontView *font, unsigned width, unsigned height,
    unsigned *width_out, unsigned *height_out)
{
    // Target tests the backend caps byte at +0x64 before either lock.
    if (g_d3d_backend.caps_028.bytes_000[0x3c] & 0x20) {
        if (width < height)
            width = height;
        else
            height = width;
    }
    EnterCriticalSection(&g_d3d_backend.critical_section_000.critical_section_04);
    long status = D3DXCreateTexture(g_d3d_backend.device_020, width, height,
        1, 0, 21, 1, texture);
    LeaveCriticalSection(&g_d3d_backend.critical_section_000.critical_section_04);
    if (status >= 0) {
        EnterCriticalSection(&g_d3d_backend.critical_section_000.critical_section_04);
        TextTextureLockedRect locked;
        status = (*texture)->LockRect(0, &locked, 0, 0);
        if (status == 0) {
            memset(locked.bits, 0, 4 * height * width);
            font->surface_base_140 = font->surface_cursor_144 = locked.bits;
            font->surface_pitch_dwords_150 = locked.pitch / 4;
            font->surface_width_14c = width;
            font->surface_height_148 = height;
            font->render_text(text, width_out, height_out);
            (*texture)->UnlockRect(0);
        }
        LeaveCriticalSection(&g_d3d_backend.critical_section_000.critical_section_04);
    }
    return status;
}

struct TextTextureTokenManager {
    void **acquire(ResourceHandleToken &token);
    void release(unsigned packed_token);
    void *vptr_00;
    std::deque<void *> cells_04;
    std::vector<void **> slots_18;
    std::vector<unsigned> generations_28;
    std::list<unsigned> free_slots_38;
    unsigned generation_44;
    CriticalSectionWrapper lock_48;
};

class TextTextureTokenLock {
public:
    explicit TextTextureTokenLock(CriticalSectionWrapper *lock) : lock_(lock)
    { EnterCriticalSection(&lock_->critical_section_04); }
    ~TextTextureTokenLock() { LeaveCriticalSection(&lock_->critical_section_04); }
private:
    CriticalSectionWrapper *lock_;
};

void **TextTextureTokenManager::acquire(ResourceHandleToken &token)
{
    TextTextureTokenLock scope(&lock_48);
    unsigned slot;
    if (free_slots_38.empty()) {
        slot = cells_04.size();
        if (++generation_44 > 0xffff)
            generation_44 = 1;
        token.slot_00 = static_cast<unsigned short>(slot);
        token.generation_02 = static_cast<unsigned short>(generation_44);
        cells_04.push_back(0);
        slots_18.push_back(&cells_04.back());
        generations_28.push_back(token.generation_02);
    } else {
        slot = free_slots_38.back();
        if (++generation_44 > 0xffff)
            generation_44 = 1;
        token.slot_00 = static_cast<unsigned short>(slot);
        token.generation_02 = static_cast<unsigned short>(generation_44);
        free_slots_38.pop_back();
        generations_28[slot] = token.generation_02;
    }
    return slots_18.at(slot);
}

void TextTextureTokenManager::release(unsigned packed_token)
{
    const ResourceHandleToken &token = *reinterpret_cast<const ResourceHandleToken *>(&packed_token);
    EnterCriticalSection(&lock_48.critical_section_04);
    if (generations_28[token.slot_00] == token.generation_02) {
        generations_28[token.slot_00] = 0;
        free_slots_38.push_back(token.slot_00);
    }
    LeaveCriticalSection(&lock_48.critical_section_04);
}

TextureHandleResult TitleResourceManager::create_text_texture(const char *text,
    const void *config, unsigned width, unsigned height,
    unsigned *width_out, unsigned *height_out)
{
    union TokenValue { unsigned value; ResourceHandleToken token; } handle;
    handle.value = 0;
    TextTextureTokenManager &manager = *reinterpret_cast<TextTextureTokenManager *>(this);
    void **cell = manager.acquire(handle.token);
    *cell = 0;
    TextureHandleResult result;
    if (populate_text_texture(reinterpret_cast<TextTexture9 **>(cell), text,
            static_cast<TextTextureFontView *>(const_cast<void *>(config)), width, height,
            width_out, height_out) < 0) {
        manager.release(handle.value);
        result.value = 0;
    } else {
        result.value = handle.value;
    }
    return result;
}

typedef char TextManagerSize[sizeof(TextTextureTokenManager) == 0x64 ? 1 : -1];
typedef char TextManagerSlots[offsetof(TextTextureTokenManager, slots_18) == 0x18 ? 1 : -1];
typedef char TextManagerLock[offsetof(TextTextureTokenManager, lock_48) == 0x48 ? 1 : -1];
} // namespace th105
