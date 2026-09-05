#pragma once

namespace th105 {

// Roster ownership/ABI declarations. Exact-target manifests prove the receiver
// ABI, numeric action selector, and void return topology for every +0x28 root.
// Youmu now has a complete semantic source scaffold in YoumuActionState.cpp;
// the remaining roster roots are still declaration-only until their action CFGs
// are recovered.
struct Alice;
struct Aya;
struct Iku;
struct Komachi;
struct Marisa;
struct Patchouli;
struct Reimu;
struct Remilia;
struct Sakuya;
struct Suika;
struct Tenshi;
struct Udonge;
struct Youmu;
struct Yuyuko;
struct Yukari;

void __thiscall Alice_dispatch_action_state_vslot28(Alice *self);
void __thiscall Aya_dispatch_action_state_vslot28(Aya *self);
void __thiscall Iku_dispatch_action_state_vslot28(Iku *self);
void __thiscall Komachi_dispatch_action_state_vslot28(Komachi *self);
void __thiscall Marisa_dispatch_action_state_vslot28(Marisa *self);
void __thiscall Patchouli_dispatch_action_state_vslot28(Patchouli *self);
void __thiscall Reimu_dispatch_action_state_vslot28(Reimu *self);
void __thiscall Remilia_dispatch_action_state_vslot28(Remilia *self);
void __thiscall Sakuya_dispatch_action_state_vslot28(Sakuya *self);
void __thiscall Suika_dispatch_action_state_vslot28(Suika *self);
void __thiscall Tenshi_dispatch_action_state_vslot28(Tenshi *self);
void __thiscall Udonge_dispatch_action_state_vslot28(Udonge *self);
void __thiscall Youmu_dispatch_action_state_vslot28(Youmu *self);
void __thiscall Yuyuko_dispatch_action_state_vslot28(Yuyuko *self);
void __thiscall Yukari_dispatch_action_state_vslot28(Yukari *self);

} // namespace th105
