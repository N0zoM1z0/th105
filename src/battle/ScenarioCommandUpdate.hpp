#pragma once

namespace th105 {

// Pointer-only view of the vslot-08 entry at 00458440. The native exits set
// AL to 0, 1 or FF; the retained CScenarioData::update int declaration has
// not established the return width. Never construct or embed this view.
struct ScenarioCommandUpdateView {
    signed char update();
};

} // namespace th105
