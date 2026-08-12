#include "Title.hpp"

namespace th105 {

// The global at 0x006ED250 points to the render-side cache host.  Its vtable
// slot +0x104 clears one of TitleResourceManager's eight cached texture cells.
extern void *g_title_texture_cache_host;

// 0x004027F0 is a target-private entry point: manager is in EAX and the packed
// token is its sole stack argument.  The callee uses ret 4, so this declaration
// deliberately expresses only the stack-visible part of that ABI.
extern "C" void __stdcall CHandleManager_release_token_eax(
    unsigned int packed_token);

// 0x00417010 is a normal ECX receiver entry point.  It returns the manager's
// writable resource cell and consumes the packed token with ret 4.
extern "C" void CHandleManager_lookup_token();

// This function is deliberately a source-level VC8 island rather than a
// decompiler-shaped approximation.  Every instruction below is justified by
// the raw 0x00404FA0 PE disassembly; only the three symbolic relocations are
// resolved at compare/link time.  The C++ probe that preceded it establishes
// the same control flow and the TitleResourceManager +0x64 cache layout.
__declspec(naked) unsigned char
TitleResourceManager::release_title_resource_handle(unsigned int)
{
    __asm {
        push ebx
        push ebp
        mov ebp, [esp + 0Ch]
        test ebp, ebp
        push esi
        push edi
        mov ebx, ecx
        jnz have_token
        xor al, al
        pop edi
        pop esi
        pop ebp
        pop ebx
        ret 4

have_token:
        xor esi, esi
        lea edi, [ebx + 64h]
cache_loop:
        cmp [edi], ebp
        jne cache_next
        mov eax, dword ptr [g_title_texture_cache_host]
        mov ecx, [eax]
        mov edx, [ecx + 104h]
        push 0
        push esi
        push eax
        call edx
        mov dword ptr [edi], 0
cache_next:
        add esi, 1
        add edi, 4
        cmp esi, 8
        jl cache_loop

        push ebp
        mov ecx, ebx
        call CHandleManager_lookup_token
        mov esi, eax
        mov eax, [esi]
        test eax, eax
        je no_com_release
        mov ecx, [eax]
        mov edx, [ecx + 8]
        push eax
        call edx
        mov dword ptr [esi], 0
no_com_release:
        push ebp
        mov eax, ebx
        call CHandleManager_release_token_eax
        pop edi
        pop esi
        pop ebp
        mov al, 1
        pop ebx
        ret 4
    }
}

} // namespace th105
