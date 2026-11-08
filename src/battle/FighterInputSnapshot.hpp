#pragma once

namespace th105 {
// The stored direction and button state captured for an input window.
struct FighterInputSnapshotValues {
    int horizontal;
    int vertical;
    int buttons[6];
};

} // namespace th105
