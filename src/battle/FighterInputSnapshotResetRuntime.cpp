#include "battle/FighterInputSnapshotResetRuntime.hpp"
#include <stddef.h>
namespace th105 {
typedef char snap_d4[offsetof(FighterInputSnapshotResetRuntimeView,snapshot_6d4)==0x6d4?1:-1];
typedef char snap_timer[offsetof(FighterInputSnapshotResetRuntimeView,timer_70c)==0x70c?1:-1];
int FighterInputSnapshotResetRuntimeView::reset_input_snapshot_4633a0()
{
    snapshot_6d4.horizontal = 0;
    snapshot_6d4.vertical = 0;
    snapshot_6d4.buttons[0] = 0;
    snapshot_6d4.buttons[1] = 0;
    snapshot_6d4.buttons[2] = 0;
    snapshot_6d4.buttons[3] = 0;
    snapshot_6d4.buttons[4] = 0;
    snapshot_6d4.buttons[5] = 0;
    timer_70c = 0;
    return 0;
}
}
