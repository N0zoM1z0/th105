#pragma once

#include <stddef.h>

namespace th105 {

// Win32 x86 RTL_CRITICAL_SECTION layout used by the target's imported
// EnterCriticalSection/LeaveCriticalSection calls.
struct Win32CriticalSection24 {
    void *debug_info_00;
    long lock_count_04;
    long recursion_count_08;
    void *owning_thread_0c;
    void *lock_semaphore_10;
    unsigned spin_count_14;
};

extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(
    Win32CriticalSection24 *critical_section);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(
    Win32CriticalSection24 *critical_section);

struct CriticalSectionWrapper {
    unsigned state_00;
    Win32CriticalSection24 critical_section_04;

    void enter();
    void leave();
};

typedef char CheckCriticalSectionWrapperSize[
    sizeof(CriticalSectionWrapper) == 0x1c ? 1 : -1];
typedef char CheckWin32CriticalSectionSize[
    sizeof(Win32CriticalSection24) == 0x18 ? 1 : -1];
typedef char CheckCriticalSectionWrapperMemberOffset[
    offsetof(CriticalSectionWrapper, critical_section_04) == 0x04 ? 1 : -1];

} // namespace th105
