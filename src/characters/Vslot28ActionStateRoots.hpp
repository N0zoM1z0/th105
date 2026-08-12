#pragma once

namespace th105 {

// Declarations only. The exact-target manifests prove the receiver ABI,
// numeric action selector, and void return topology for these three pilots.
// Complete derived layouts and per-action gameplay names remain unresolved;
// no placeholder implementation is emitted.
struct Alice;
struct Youmu;
struct Yuyuko;

void __thiscall Alice_dispatch_action_state_vslot28(Alice *self);
void __thiscall Youmu_dispatch_action_state_vslot28(Youmu *self);
void __thiscall Yuyuko_dispatch_action_state_vslot28(Yuyuko *self);

} // namespace th105
