#include "FighterPhaseContextRuntime.hpp"

#include <windows.h>

namespace th105 {

void FighterPhaseContextRuntimeView::initialize_slot_464270(
    unsigned slot,
    MatchSetup::Side *side,
    bool asynchronous)
{
    if (slot > 2)
        return;

    begin_slot_4641f0(slot);
    if (asynchronous) {
        FighterPhaseInitRequest request = {slot, side};
        queue_init_request_466db0(&request);
        SetEvent(*reinterpret_cast<HANDLE *>(
            reinterpret_cast<unsigned char *>(this) + 0x20));
        return;
    }

    initialize_slot_sync_4642f0(slot, side);
}

} // namespace th105
