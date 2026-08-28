#include "FighterPhaseContextRuntime.hpp"

#include <list>
#include <vector>
#include <windows.h>
#include <stddef.h>

namespace th105 {

struct FighterPhaseObjectView;

struct FighterPhaseThreadOwner {
    HANDLE handle_00;
    DWORD thread_id_04;

    FighterPhaseThreadOwner();
    ~FighterPhaseThreadOwner();
    HANDLE stop();
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
    unsigned short active_34_35;
    unsigned char active_36;
    unsigned char reserved_37;
    std::vector<FighterPhaseObjectView *> fighters_38;
    std::list<int> released_48;

    ~FighterPhaseContextLifetime();
    void released_worker_loop_464dd0();
    void reset_slot_state_465040();
};

typedef char FighterPhaseContextLifetime_worker0_offset_must_be_0x10[
    offsetof(FighterPhaseContextLifetime, worker0_10) == 0x10 ? 1 : -1];
typedef char FighterPhaseContextLifetime_fighters_offset_must_be_0x38[
    offsetof(FighterPhaseContextLifetime, fighters_38) == 0x38 ? 1 : -1];
typedef char FighterPhaseContextLifetime_released_offset_must_be_0x48[
    offsetof(FighterPhaseContextLifetime, released_48) == 0x48 ? 1 : -1];
typedef char FighterPhaseContextLifetime_size_must_be_0x54[
    sizeof(FighterPhaseContextLifetime) == 0x54 ? 1 : -1];

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
    unsigned char *active =
        reinterpret_cast<unsigned char *>(&active_34_35);
    for (int i = 0; i < 3; ++i) {
        FighterPhaseObjectView *&owned =
            *reinterpret_cast<FighterPhaseObjectView **>(&owned_28[i]);
        if (owned != 0 && active[i] != 0)
            fighters_38.push_back(owned);
    }
}

} // namespace th105
