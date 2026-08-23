#include "FighterPhaseContextRuntime.hpp"

#include <windows.h>

namespace th105 {

void FighterPhaseContextRuntimeView::begin_slot_4641f0(unsigned slot)
{
    if (slot > 2)
        return;

    int *handle = reinterpret_cast<int *>(
        reinterpret_cast<unsigned char *>(this) + 0x28) + slot;
    if (*handle == 0)
        return;

    *(reinterpret_cast<unsigned char *>(this) + 0x34 + slot) = 0;
    reset_slot_state_465040();
    reinterpret_cast<IntListView *>(
        reinterpret_cast<unsigned char *>(this) + 0x48)->push_back(*handle);
    *handle = 0;
    SetEvent(*reinterpret_cast<HANDLE *>(
        reinterpret_cast<unsigned char *>(this) + 0x24));
}

} // namespace th105
