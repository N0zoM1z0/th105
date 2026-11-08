#include "battle/FighterInputSnapshotResetRuntime.hpp"
#include <stddef.h>
namespace th105 {
typedef char snap_d4[offsetof(FighterInputSnapshotResetRuntimeView,saved_horizontal_6d4)==0x6d4?1:-1];
typedef char snap_timer[offsetof(FighterInputSnapshotResetRuntimeView,timer_70c)==0x70c?1:-1];
int FighterInputSnapshotResetRuntimeView::reset_input_snapshot_4633a0()
{
    saved_horizontal_6d4 = 0;
    saved_vertical_6d8 = 0;
    saved_buttons_6dc[0] = 0;
    saved_buttons_6dc[1] = 0;
    saved_buttons_6dc[2] = 0;
    saved_buttons_6dc[3] = 0;
    saved_buttons_6dc[4] = 0;
    saved_buttons_6dc[5] = 0;
    timer_70c = 0;
    return 0;
}
}
