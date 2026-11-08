#pragma once

namespace th105 {
// Pointer-only view of the input snapshot shared by Fighter-derived objects.
struct FighterInputSnapshotResetRuntimeView {
    unsigned char unknown_000[0x6d4];
    int saved_horizontal_6d4;
    int saved_vertical_6d8;
    int saved_buttons_6dc[6];
    unsigned char unknown_6f4[0x18];
    unsigned char timer_70c;
    int reset_input_snapshot_4633a0();
};
}
