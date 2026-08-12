#pragma once

namespace th105 {

// Declarations only. The exact-target manifests prove the receiver ABI,
// numeric action selector, and void return topology for these nine pilots.
// Complete derived layouts and per-action gameplay names remain unresolved;
// no placeholder implementation is emitted.
struct Alice;
struct Marisa;
struct Patchouli;
struct Reimu;
struct Remilia;
struct Tenshi;
struct Udonge;
struct Youmu;
struct Yuyuko;

void __thiscall Alice_dispatch_action_state_vslot28(Alice *self);
void __thiscall Marisa_dispatch_action_state_vslot28(Marisa *self);
void __thiscall Patchouli_dispatch_action_state_vslot28(Patchouli *self);
void __thiscall Reimu_dispatch_action_state_vslot28(Reimu *self);
void __thiscall Remilia_dispatch_action_state_vslot28(Remilia *self);
void __thiscall Tenshi_dispatch_action_state_vslot28(Tenshi *self);
void __thiscall Udonge_dispatch_action_state_vslot28(Udonge *self);
void __thiscall Youmu_dispatch_action_state_vslot28(Youmu *self);
void __thiscall Yuyuko_dispatch_action_state_vslot28(Yuyuko *self);

} // namespace th105
