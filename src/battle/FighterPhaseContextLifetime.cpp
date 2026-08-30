#include "FighterPhaseContextRuntime.hpp"
#include "FighterPhaseContext.hpp"

#include <list>
#include <vector>
#include <windows.h>
#include <stddef.h>
#include <string.h>

namespace th105 {

struct FighterPhaseObjectView;
typedef unsigned (__stdcall *FighterPhaseThreadEntry)(void *);

struct FighterPhaseThreadOwner {
    HANDLE handle_00;
    DWORD thread_id_04;

    FighterPhaseThreadOwner();
    ~FighterPhaseThreadOwner();
    bool start(FighterPhaseThreadEntry procedure, void *argument);
    HANDLE stop();
    int set_priority(int priority);
};

struct FighterPhaseOwnedHandle {
    virtual ~FighterPhaseOwnedHandle();
};

struct FighterPhaseContextLifetime {
    std::list<FighterPhaseInitRequest> pending_00;
    unsigned char running_0c;
    unsigned char reserved_0d[3];
    FighterPhaseThreadOwner worker0_10;
    FighterPhaseThreadOwner worker1_18;
    HANDLE wake_20;
    HANDLE done_24;
    int owned_28[3];
    unsigned char active_34[3];
    unsigned char reserved_37;
    std::vector<FighterPhaseObjectView *> fighters_38;
    std::list<int> released_48;

    FighterPhaseContextLifetime();
    ~FighterPhaseContextLifetime();
    void pending_worker_loop_464d40();
    void released_worker_loop_464dd0();
    void release_slots_and_signal_464f90();
    void reset_slot_state_465040();
    void initialize_slot_sync(unsigned slot, MatchSetup::Side *side);
    void swap_slots_4642b0(unsigned first, unsigned second);
};

typedef char FighterPhaseContextLifetime_worker0_offset_must_be_0x10[
    offsetof(FighterPhaseContextLifetime, worker0_10) == 0x10 ? 1 : -1];
typedef char FighterPhaseContextLifetime_fighters_offset_must_be_0x38[
    offsetof(FighterPhaseContextLifetime, fighters_38) == 0x38 ? 1 : -1];
typedef char FighterPhaseContextLifetime_released_offset_must_be_0x48[
    offsetof(FighterPhaseContextLifetime, released_48) == 0x48 ? 1 : -1];
typedef char FighterPhaseContextLifetime_size_must_be_0x54[
    sizeof(FighterPhaseContextLifetime) == 0x54 ? 1 : -1];

unsigned __stdcall pending_worker_entry(void *context);
unsigned __stdcall released_worker_entry(void *context);

FighterPhaseContextLifetime::FighterPhaseContextLifetime()
{
    FighterPhaseThreadOwner *pending_worker = &worker0_10;
    FighterPhaseThreadOwner *released_worker = &worker1_18;
    g_fighter_phase_context =
        reinterpret_cast<FighterPhaseContext *>(this);
    running_0c = 1;
    wake_20 = CreateEventA(0, FALSE, FALSE, 0);
    done_24 = CreateEventA(0, FALSE, FALSE, 0);
    pending_worker->start(pending_worker_entry, this);
    released_worker->start(released_worker_entry, this);
    released_worker->set_priority(THREAD_PRIORITY_IDLE);
    memset(owned_28, 0, sizeof(owned_28));
    memset(active_34, 0, sizeof(active_34));
}

FighterPhaseContextLifetime::~FighterPhaseContextLifetime()
{
    running_0c = 0;
    SetEvent(wake_20);
    SetEvent(done_24);
    worker0_10.stop();
    worker1_18.stop();
    CloseHandle(wake_20);
    CloseHandle(done_24);

    while (released_48.size() != 0) {
        int handle = released_48.front();
        if (handle != 0)
            delete reinterpret_cast<FighterPhaseOwnedHandle *>(handle);
        released_48.pop_front();
    }

    for (int i = 0; i < 3; ++i) {
        if (owned_28[i] != 0) {
            delete reinterpret_cast<FighterPhaseOwnedHandle *>(owned_28[i]);
            owned_28[i] = 0;
        }
    }
}


void FighterPhaseContextLifetime::pending_worker_loop_464d40()
{
    while (running_0c) {
        WaitForSingleObject(wake_20, INFINITE);
        while (pending_00.size() != 0) {
            initialize_slot_sync(
                pending_00.front().slot,
                pending_00.front().side);
            pending_00.pop_front();
        }
    }
}

void FighterPhaseContextLifetime::release_slots_and_signal_464f90()
{
    for (int i = 0; i < 3; ++i) {
        active_34[i] = 0;
        released_48.push_back(owned_28[i]);
        owned_28[i] = 0;
    }
    fighters_38.clear();
    SetEvent(done_24);
}

void FighterPhaseContextLifetime::swap_slots_4642b0(
    unsigned first,
    unsigned second)
{
    int pointer = owned_28[first];
    owned_28[first] = owned_28[second];
    owned_28[second] = pointer;
    unsigned char a = active_34[second];
    unsigned char b = active_34[first];
    active_34[first] = a;
    active_34[second] = b;
}

unsigned __stdcall pending_worker_entry(void *context)
{
    if (CoInitialize(0) >= 0) {
        static_cast<FighterPhaseContextLifetime *>(context)->pending_worker_loop_464d40();
        CoUninitialize();
    }
    return 0;
}

unsigned __stdcall released_worker_entry(void *context)
{
    if (CoInitialize(0) >= 0) {
        static_cast<FighterPhaseContextLifetime *>(context)->released_worker_loop_464dd0();
        CoUninitialize();
    }
    return 0;
}

void FighterPhaseContextLifetime::released_worker_loop_464dd0()
{
    while (running_0c) {
        WaitForSingleObject(done_24, INFINITE);
        while (released_48.size() != 0) {
            int handle = released_48.front();
            if (handle != 0)
                delete reinterpret_cast<FighterPhaseOwnedHandle *>(handle);
            released_48.pop_front();
        }
    }
}

void FighterPhaseContextLifetime::reset_slot_state_465040()
{
    fighters_38.clear();
    for (int i = 0; i < 3; ++i) {
        FighterPhaseObjectView *&owned =
            *reinterpret_cast<FighterPhaseObjectView **>(&owned_28[i]);
        if (owned != 0 && active_34[i] != 0)
            fighters_38.push_back(owned);
    }
}

} // namespace th105
