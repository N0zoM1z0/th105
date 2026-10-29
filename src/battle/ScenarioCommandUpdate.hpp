#pragma once

namespace th105 {

// Pointer-only view of the vslot-08 entry at 00458440. The native exits set
// AL to 0, 1 or FF. The shared CScenarioData declaration and the actual
// advance-loop callers now use this signed-byte contract. Never construct
// or embed this view.
struct ScenarioCommandUpdateView {
    signed char update();
};

} // namespace th105
