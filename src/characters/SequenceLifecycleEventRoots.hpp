#pragma once

namespace th105 {

// Source-facing declarations for the remaining character-command roots.  The
// classes stay incomplete here: the IDA breadth inventory proves the receiver
// ABI and control-flow families, but it does not yet prove full derived layouts.
struct Alice;
struct Marisa;
struct Patchouli;
struct Reimu;
struct Youmu;
struct Remilia;
struct Sakuya;
struct Yuyuko;
struct Yukari;
struct Suika;
struct Udonge;
struct Komachi;
struct Aya;
struct Iku;
struct Tenshi;

Alice *__thiscall Alice_construct(Alice *self, int init_arg);

int __thiscall Reimu_update_sequence_lifecycle(Reimu *self);
unsigned char __thiscall Reimu_handle_event_bridge(Reimu *self, int event_code);
int __thiscall Marisa_update_sequence_lifecycle(Marisa *self);
unsigned char __thiscall Marisa_handle_event_bridge(Marisa *self, int event_code);
void __thiscall Sakuya_update_sequence_lifecycle(Sakuya *self);
unsigned char __thiscall Sakuya_handle_event_bridge(Sakuya *self, int event_code);
int __thiscall Alice_update_sequence_lifecycle(Alice *self);
unsigned char __thiscall Alice_handle_event_bridge(Alice *self, int event_code);
void __thiscall Patchouli_update_sequence_lifecycle(Patchouli *self);
unsigned char __thiscall Patchouli_handle_event_bridge(Patchouli *self, int event_code);
void __thiscall Youmu_update_sequence_lifecycle(Youmu *self);
unsigned char __thiscall Youmu_handle_event_bridge(Youmu *self, int event_code);
void __thiscall Remilia_update_sequence_lifecycle(Remilia *self);
unsigned char __thiscall Remilia_handle_event_bridge(Remilia *self, int event_code);
void __thiscall Yuyuko_update_sequence_lifecycle(Yuyuko *self);
unsigned char __thiscall Yuyuko_handle_event_bridge(Yuyuko *self, int event_code);
void __thiscall Yukari_update_sequence_lifecycle(Yukari *self);
bool __thiscall Yukari_handle_event_bridge(Yukari *self, int event_code);
void __thiscall Suika_update_sequence_lifecycle(Suika *self);
unsigned char __thiscall Suika_handle_event_bridge(Suika *self, int event_code);
void __thiscall Udonge_update_sequence_lifecycle(Udonge *self);
unsigned char __thiscall Udonge_handle_event_bridge(Udonge *self, int event_code);
void __thiscall Komachi_update_sequence_lifecycle(Komachi *self);
unsigned char __thiscall Komachi_handle_event_bridge(Komachi *self, int event_code);
void __thiscall Aya_update_sequence_lifecycle(Aya *self);
unsigned char __thiscall Aya_handle_event_bridge(Aya *self, int event_code);
void __thiscall Iku_update_sequence_lifecycle(Iku *self);
unsigned char __thiscall Iku_handle_event_bridge(Iku *self, int event_code);
void __thiscall Tenshi_update_sequence_lifecycle(Tenshi *self);
unsigned char __thiscall Tenshi_handle_event_bridge(Tenshi *self, int event_code);

} // namespace th105
