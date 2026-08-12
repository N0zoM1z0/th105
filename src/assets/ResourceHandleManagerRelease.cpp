#include "ResourceHandleManager.hpp"
#include "engine/CriticalSectionWrapper.hpp"

// These are target-local checked-vector / free-list primitives.  Their
// register and stack contracts are expressed by the raw call setup below, not
// by an invented source calling convention.
extern "C" void _invalid_parameter_noinfo();
extern "C" void CHandleManager_free_list_insert();
extern "C" void CHandleManager_free_list_finalize_insert();

namespace th105 {

// Exact 0x004027F0 island.  EAX is the hidden manager receiver and the packed
// ResourceHandleToken is the one stdcall-visible argument.  It first verifies
// the generation cell at +0x2c, clears the resource cell at +0x2c, and then
// returns the 16-bit slot to the +0x38 free-list under the +0x4c lock.
extern "C" __declspec(naked) void __stdcall
CHandleManager_release_token_eax(unsigned int)
{
    __asm {
        push ebp
        mov ebp, esp
        and esp, 0FFFFFFF8h
        sub esp, 0Ch
        push ebx
        push esi
        mov esi, eax
        push edi
        lea ebx, [esi + 4Ch]
        push ebx
        mov [esp + 18h], ebx
        // FF 15 1C C1 6A 00: target fixed-image EnterCriticalSection IAT.
        __emit 0FFh
        __emit 015h
        __emit 01Ch
        __emit 0C1h
        __emit 06Ah
        __emit 000h
        mov ecx, [esi + 2Ch]
        test ecx, ecx
        movzx edi, word ptr [ebp + 8]
        jz invalid_token
        mov eax, [esi + 30h]
        sub eax, ecx
        sar eax, 2
        cmp edi, eax
        jb token_in_range
invalid_token:
        call _invalid_parameter_noinfo
token_in_range:
        movzx ecx, word ptr [ebp + 0Ah]
        mov eax, [esi + 2Ch]
        cmp [eax + edi * 4], ecx
        jne release_lock
        mov ecx, eax
        test ecx, ecx
        jz invalid_generation_cell
        mov eax, [esi + 30h]
        sub eax, ecx
        sar eax, 2
        cmp edi, eax
        jb generation_cell_in_range
invalid_generation_cell:
        call _invalid_parameter_noinfo
generation_cell_in_range:
        mov edx, [esi + 2Ch]
        mov dword ptr [edx + edi * 4], 0
        add esi, 38h
        mov [esp + 10h], edi
        mov edi, [esi + 4]
        mov ecx, [edi + 4]
        lea eax, [esp + 10h]
        push eax
        push ecx
        push edi
        mov ecx, esi
        call CHandleManager_free_list_insert
        push 1
        mov ecx, esi
        mov ebx, eax
        call CHandleManager_free_list_finalize_insert
        mov [edi + 4], ebx
        mov edx, [ebx + 4]
        mov [edx], ebx
        mov ebx, [esp + 14h]
release_lock:
        push ebx
        // FF 15 18 C1 6A 00: target fixed-image LeaveCriticalSection IAT.
        __emit 0FFh
        __emit 015h
        __emit 018h
        __emit 0C1h
        __emit 06Ah
        __emit 000h
        pop edi
        pop esi
        pop ebx
        mov esp, ebp
        pop ebp
        ret 4
    }
}

} // namespace th105
