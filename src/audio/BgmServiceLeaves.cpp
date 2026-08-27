#include "engine/CriticalSectionWrapper.hpp"

extern "C" __declspec(dllimport) long __stdcall CoInitialize(void *);
extern "C" __declspec(dllimport) void __stdcall CoUninitialize();

namespace th105 {

struct BgmStreamLinkView {
    unsigned char reserved_0000[0x1c];
    int state_001c;
    unsigned char active_0020;
    unsigned char reserved_0021[0x132b];
    void link_with(BgmStreamLinkView *other);
};

struct BgmHandleManagerLinkView {
    unsigned char storage[0x50];
    BgmStreamLinkView *lookup(unsigned handle);
};

struct BgmServiceLinkView {
    unsigned char reserved_0000[0x20];
    Win32CriticalSection24 lock_0020;
    BgmHandleManagerLinkView handles_0038;

    void link_handles(unsigned first, unsigned second);
};

void BgmServiceLinkView::link_handles(unsigned first, unsigned second)
{
    EnterCriticalSection(&lock_0020);
    BgmStreamLinkView *first_stream = handles_0038.lookup(first);
    BgmStreamLinkView *second_stream = handles_0038.lookup(second);
    if (first_stream != 0 && second_stream != 0)
        first_stream->link_with(second_stream);
    LeaveCriticalSection(&lock_0020);
}

extern "C" void __cdecl bgm_worker_one();
extern "C" void __cdecl bgm_worker_two();

extern "C" unsigned long __stdcall bgm_thread_one(void *)
{
    if (CoInitialize(0) >= 0) {
        bgm_worker_one();
        CoUninitialize();
    }
    return 0;
}

extern "C" unsigned long __stdcall bgm_thread_two(void *)
{
    if (CoInitialize(0) >= 0) {
        bgm_worker_two();
        CoUninitialize();
    }
    return 0;
}

} // namespace th105
