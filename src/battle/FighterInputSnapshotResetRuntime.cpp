#include <stddef.h>
namespace th105 {
struct FighterInputSnapshotResetRuntimeView {
    unsigned char unknown_000[0x6d4];
    int field_6d4;
    int field_6d8;
    int field_6dc;
    int field_6e0;
    int field_6e4;
    int field_6e8;
    int field_6ec;
    int field_6f0;
    unsigned char unknown_6f4[0x18];
    unsigned char timer_70c;
    int reset_input_snapshot_4633a0();
};
typedef char snap_d4[offsetof(FighterInputSnapshotResetRuntimeView,field_6d4)==0x6d4?1:-1];
typedef char snap_timer[offsetof(FighterInputSnapshotResetRuntimeView,timer_70c)==0x70c?1:-1];
int FighterInputSnapshotResetRuntimeView::reset_input_snapshot_4633a0()
{
    field_6d4 = 0;
    field_6d8 = 0;
    field_6dc = 0;
    field_6e0 = 0;
    field_6e4 = 0;
    field_6e8 = 0;
    field_6ec = 0;
    field_6f0 = 0;
    timer_70c = 0;
    return 0;
}
}
