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

extern "C" __declspec(dllimport) void __stdcall InitializeCriticalSection(
    Win32CriticalSection24 *critical_section);
extern "C" __declspec(dllimport) void __stdcall DeleteCriticalSection(
    Win32CriticalSection24 *critical_section);
extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(
    Win32CriticalSection24 *critical_section);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(
    Win32CriticalSection24 *critical_section);

// Current RTTI/vtable ownership identifies the target type as CCriticalSection.
// The implicit polymorphic vptr is the observed +0 dword; the Win32 critical
// section begins at +4, so the total layout remains 0x1c.
struct CriticalSectionWrapper {
    CriticalSectionWrapper();
    virtual ~CriticalSectionWrapper();

    void enter();
    void leave();

    Win32CriticalSection24 critical_section_04;
};

typedef char CheckCriticalSectionWrapperSize[
    sizeof(CriticalSectionWrapper) == 0x1c ? 1 : -1];
typedef char CheckWin32CriticalSectionSize[
    sizeof(Win32CriticalSection24) == 0x18 ? 1 : -1];
typedef char CheckCriticalSectionWrapperMemberOffset[
    offsetof(CriticalSectionWrapper, critical_section_04) == 0x04 ? 1 : -1];

} // namespace th105
