#pragma once

namespace th105 {

// Source-facing declarations for the remaining character-command roots.  The
// classes stay incomplete here: the IDA breadth inventory proves the receiver
// ABI and control-flow families, but it does not yet prove full derived layouts.
struct Alice;
struct Patchouli;
struct Youmu;
struct Remilia;
struct Yuyuko;
struct Yukari;
struct Suika;
struct Udonge;
struct Komachi;
struct Aya;
struct Iku;
struct Tenshi;

Alice *__thiscall Alice_construct(Alice *self, int init_arg);

void __thiscall Patchouli_update_sequence_lifecycle(Patchouli *self);
bool __thiscall Patchouli_handle_event_bridge(Patchouli *self, int event_code);
void __thiscall Youmu_update_sequence_lifecycle(Youmu *self);
bool __thiscall Youmu_handle_event_bridge(Youmu *self, int event_code);
void __thiscall Remilia_update_sequence_lifecycle(Remilia *self);
bool __thiscall Remilia_handle_event_bridge(Remilia *self, int event_code);
void __thiscall Yuyuko_update_sequence_lifecycle(Yuyuko *self);
bool __thiscall Yuyuko_handle_event_bridge(Yuyuko *self, int event_code);
void __thiscall Yukari_update_sequence_lifecycle(Yukari *self);
void __thiscall Suika_update_sequence_lifecycle(Suika *self);
bool __thiscall Suika_handle_event_bridge(Suika *self, int event_code);
void __thiscall Udonge_update_sequence_lifecycle(Udonge *self);
bool __thiscall Udonge_handle_event_bridge(Udonge *self, int event_code);
void __thiscall Komachi_update_sequence_lifecycle(Komachi *self);
bool __thiscall Komachi_handle_event_bridge(Komachi *self, int event_code);
void __thiscall Aya_update_sequence_lifecycle(Aya *self);
bool __thiscall Aya_handle_event_bridge(Aya *self, int event_code);
void __thiscall Iku_update_sequence_lifecycle(Iku *self);
bool __thiscall Iku_handle_event_bridge(Iku *self, int event_code);
void __thiscall Tenshi_update_sequence_lifecycle(Tenshi *self);
bool __thiscall Tenshi_handle_event_bridge(Tenshi *self, int event_code);

} // namespace th105
