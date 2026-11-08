#pragma once

namespace th105 {
// The stored direction and button state captured for an input window.
struct FighterInputSnapshotValues {
    int horizontal;
    int vertical;
    int buttons[6];
};

// Pointer-only view of the input snapshot shared by Fighter-derived objects.
struct FighterInputSnapshotResetRuntimeView {
    unsigned char unknown_000[0x6d4];
    FighterInputSnapshotValues snapshot_6d4;
    unsigned char unknown_6f4[0x18];
    unsigned char timer_70c;
    int reset_input_snapshot_4633a0();
};
}
