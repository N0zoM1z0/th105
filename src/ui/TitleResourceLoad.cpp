#include "Title.hpp"

namespace th105 {

// 0x00402680 has a nonstandard EDI receiver and returns with ret 4; the
// out-token pointer is its sole stack argument.
extern "C" void CHandleManager_acquire_4byte_slot_edi();

// 0x00408FC0 uses ECX/EDX for its first two arguments.  The call site below
// proves the contract: (height_out, path, writable_resource_cell, width_out).
extern "C" void TextureLoader_load_bitmap_to_resource_cell();

// 0x004027F0 uses EAX for its manager receiver and returns with ret 4.
extern "C" void __stdcall CHandleManager_release_token_eax(
    unsigned int packed_token);

// Raw-PE backed VC8 island.  The companion 0x00404FA0 release island is an
// exact match; together they preserve the target's generation-token ownership
// transition around the large bitmap loader without inventing a normal member
// ABI for either handle-manager primitive.
__declspec(naked) unsigned int *TitleResourceManager::load_texture(
    unsigned int *,
    const char *,
    unsigned int *,
    unsigned int *)
{
    __asm {
        sub esp, 8
        push edi
        lea eax, [esp + 8]
        mov edi, ecx
        push eax
        mov dword ptr [esp + 0Ch], 0
        call CHandleManager_acquire_4byte_slot_edi
        mov ecx, [esp + 18h]
        mov edx, [esp + 14h]
        push ecx
        mov ecx, [esp + 20h]
        push eax
        mov dword ptr [eax], 0
        call TextureLoader_load_bitmap_to_resource_cell
        test eax, eax
        jge load_succeeded
        mov edx, [esp + 8]
        push edx
        mov eax, edi
        call CHandleManager_release_token_eax
        mov eax, [esp + 10h]
        mov dword ptr [eax], 0
        pop edi
        add esp, 8
        ret 10h

load_succeeded:
        mov eax, [esp + 10h]
        mov ecx, [esp + 8]
        mov [eax], ecx
        pop edi
        add esp, 8
        ret 10h
    }
}

} // namespace th105
