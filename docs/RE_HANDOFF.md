# TH10.5 reconstruction handoff

Current bounded checkpoint: DirectSound buffer clear418610 is canonical exact85
in genuine one-CIL context with its real ordinary load caller4183B0. The existing
private-caller witness closes native edge418495; VC8 naturally recovers ESI with
no ABI/register invention. Caller245/247 and silent initializer227/234 remain
nonexact. Public linked profile unchanged; no private cookie extension is used
for acceptance. See [WAVE_BUFFER_INITIALIZE_2026_10_28.md](WAVE_BUFFER_INITIALIZE_2026_10_28.md)
and build/frontier-401990-20261028/formal-linked-clear.json.

Preceding bounded checkpoint: six primary CNetworkServer/Client byte accessors
43CBA0/43CBB0/43CBC0 and43CD10/43CD20/43CD30 are canonical exact10/5/7 each,
adding44 authored bytes. Fresh primary RTTI/vtable ownership supersedes the
unreviewed label at43CBC0; EAX sign-extension and AL-only return widths remain
separate. See [NETWORK_PRIMARY_BYTE_ACCESSORS_2026_10_28.md](NETWORK_PRIMARY_BYTE_ACCESSORS_2026_10_28.md)
and build/frontier-43cba0-20261028/{formal-build,boundary}.json.

Preceding bounded checkpoint: CSceneManager update41E140/render41E150 and CFade
initialize41E240 are canonical exact5/5/11. Fresh RTTI vtable cells and complete
raw boundaries close all three. Both affected units replay13 functions exact,
including ten unchanged accepted siblings. See
[SCENE_MANAGER_VIRTUAL_LEAVES_2026_10_28.md](SCENE_MANAGER_VIRTUAL_LEAVES_2026_10_28.md)
and build/frontier-41e140-20261028/{manager-build,fade-build,boundary}.json.

Preceding bounded checkpoint: BattleBaseEffect device-reset callbacks418070/418090
are canonical exact21/21 each. The real COM OnLostDevice/OnResetDevice slots114/
118 and exact owner vtable6D6CD0 close both leaf bodies. Three accepted lifetime
siblings replay unchanged; initializer417FF0 retains its known private-ABI+17
residual. See [BATTLE_EFFECT_RESET_2026_10_28.md](BATTLE_EFFECT_RESET_2026_10_28.md)
and build/frontier-418070-20261028/{formal-build,boundary}.json.

Preceding bounded candidate: Sakuya Fighter4CADB0 has complete113-action/default
source and focused owned-extent/full76336 replay. Selected77064 remains nonexact
at+8, frame4A8/native4D8;95 request homes agree in count, declaration extents and
sharing remain unresolved. Native14/candidate13 tables and several call tails
differ. Raw CFG closes all ten remote chunks; ownership74937 excludes105 padding
bytes, all still included in strict full comparison. No exact credit. See
[SAKUYA_ACTION_STATE_2026_10_28.md](SAKUYA_ACTION_STATE_2026_10_28.md),
`scripts/audit-sakuya-action-state.py`, and
build/frontier-4cadb0-20261028/{formal-tail-build,formal-tail-audit,target-audit}.json.

Preceding bounded candidate: Aya Fighter602250 has complete114-action manual source
and canonical full65720/native66704 replay, nonexact+18. Raw two-word530/532
request homes restore native frame3E8; register allocation and tails still differ.
All114 reachable direct-call censuses agree, but low31/native33 owners and physical
tails differ. No exact credit. Independently attested Ghidra supplied navigation
after IDA failed; raw instructions corrected508 fan direction and FP/lifetime
errors. See [AYA_ACTION_STATE_2026_10_28.md](AYA_ACTION_STATE_2026_10_28.md),
`scripts/audit-aya-action-state.py`, and
build/frontier-602250-20261028/{formal-paired-build,formal-paired-audit}.json.

Preceding bounded candidate: audio scheduler thread419100 has complete source for
cadence correction, externally adjusted waits and checked listener notification.
Whole576/native591 remains nonexact+0; prologue, float lifetimes and iterator
checks differ. Raw CFG closes the full callable through41934F. No exact credit.
See [AUDIO_SCHEDULER_THREAD_2026_10_28.md](AUDIO_SCHEDULER_THREAD_2026_10_28.md)
and build/frontier-419100-20261028/{formal-build,boundary}.json.

Preceding bounded candidate: AliceObject update4FCAB0 has complete38-action manual
source and whole canonical replay. Full62960/native63248 remains nonexact+37.
Frame348, all28 direct-callee counts,18 table dimensions and260 remap bytes agree.
Shared817 impact continuation restores the direct-call census, but stack homes,
floating lifetimes and tail sharing remain different. No exact credit. See
[ALICE_OBJECT_UPDATE_2026_10_28.md](ALICE_OBJECT_UPDATE_2026_10_28.md),
`scripts/audit-alice-object-update.py` and
build/frontier-4fcab0-20261028/{formal-build,full-audit}.json.

Preceding bounded candidate: SuikaObject update5B0460 has complete31-action manual
source and whole canonical replay. Full53204/native53012 remains nonexact+17.
Frame4B0, all23 direct-callee counts,18 table dimensions and200 remap bytes agree;
initial owner scheduling and shared tails differ. No exact credit. See
[SUIKA_OBJECT_UPDATE_2026_10_28.md](SUIKA_OBJECT_UPDATE_2026_10_28.md),
`scripts/audit-suika-object-update.py` and
build/frontier-5b0460-20261028/{formal-build,full-audit}.json.

Preceding bounded candidate: PatchouliObject update520890 has complete30-action
manual source and whole canonical replay. Full51428/native51564 remains
nonexact+37. Actual shared packet lifetimes restore frame3E0; all28 direct-call
counts,24 virtual calls,21 table dimensions and219 remap bytes agree. No exact
credit. See [PATCHOULI_OBJECT_UPDATE_2026_10_28.md](PATCHOULI_OBJECT_UPDATE_2026_10_28.md),
`scripts/audit-patchouli-object-update.py` and
build/frontier-520890-20261028/{formal-build,full-audit}.json.

Preceding bounded candidate: UdongeObject update5D46C0 has complete31-action
manual source and an early whole canonical replay. Full43873/native43537
remains nonexact+37; the real812 widened count restores frame2F0. All22
direct-call counts,25 virtual calls,17 table dimensions and216remap bytes agree. No exact credit. See
[UDONGE_OBJECT_UPDATE_2026_10_28.md](UDONGE_OBJECT_UPDATE_2026_10_28.md),
`scripts/audit-udonge-object-update.py` and
build/frontier-5d46c0-20261028/{formal-build,full-audit}.json.

Preceding bounded candidate: MarisaObject update4BBE00 has complete manual
41-action source and a focused canonical replay. Full50156/native49744 remains
nonexact+37; native frame0x340 and all18 table dimensions are recovered, but
call/return sharing and later code remain different. No exact credit. See
[MARISA_OBJECT_UPDATE_2026_10_28.md](MARISA_OBJECT_UPDATE_2026_10_28.md),
`scripts/audit-marisa-object-update.py` and
build/frontier-4bbe00-20261028/{formal-build,full-audit}.json.

Preceding bounded checkpoint: BGM service initialize403460 is canonical exact133.
Actual paired thread owners and events plus existing visible start/priority
bodies recover the complete native initializer on its first focused build.
See [BGM_SERVICE_INITIALIZE_2026_10_28.md](BGM_SERVICE_INITIALIZE_2026_10_28.md)
and build/frontier-403460-20261028/{formal-build,boundary}.json.

Preceding bounded checkpoint: scenario BGM transition43D030 is canonical
exact208/208, with all three accepted BGM siblings unchanged. The interpreter
caller4594A2 pins path/duration/linked arguments and late global handle publish.
See [BGM_TRANSITION_POLICY_2026_10_28.md](BGM_TRANSITION_POLICY_2026_10_28.md)
and build/frontier-43d030-20261028/{formal-build,boundary,callers}.json.

Preceding bounded checkpoint: scene resource shutdown43D670 and its CSceneManager
owner41E120 are canonical exact264/25. Existing owner initialization41E070 stays
exact162. Actual socket/member lifetimes reuse the independently exact network
cleanup policy; all tails remain explicit. See
[SCENE_RESOURCE_SHUTDOWN_2026_10_28.md](SCENE_RESOURCE_SHUTDOWN_2026_10_28.md)
and build/frontier-43d670-20261028/{socket-owner-lifetime,scene-owner,boundary}.json.

Preceding bounded checkpoint: CFade timer policies41E250/41E270 are canonical
exact30/30 each; all six existing accepted scene-render peers remain exact.
Current RTTI slots08/0C and the exact renderer pin color04/timer08 semantics.
See [FADE_TIMER_POLICIES_2026_10_28.md](FADE_TIMER_POLICIES_2026_10_28.md)
and build/frontier-41e250-20261028/{formal-build,boundary}.json.

Preceding bounded checkpoint: Youmu constructor53B330 is canonical exact159/159.
The existing history override independently fixes the deque<YoumuObjectRecord>
at7D0, closing the previously unresolved member lifetime. Native boundary closes
46 instructions; only the authored constructor receives credit. See
[YOUMU_CONSTRUCTOR_2026_10_28.md](YOUMU_CONSTRUCTOR_2026_10_28.md)
and build/frontier-53b330-20261028/{mapped-build,boundary}.json.

Preceding bounded checkpoint: Ending entry41E790 and Connect reset442190
are canonical exact40/25. Current RTTI slots own both; all16 existing accepted
peers in the two affected TUs remain exact. See
[SCENE_MENU_ENTRY_LEAVES_2026_10_28.md](SCENE_MENU_ENTRY_LEAVES_2026_10_28.md)
and build/frontier-41e790-20261028/{formal-build,connect-reset}.json.

Preceding bounded candidate: sprite rectangle renderer4070C0 is complete
153/native153 under the independently available strict-FP context. Default
161 uses a different half-pixel pool; strict recovers x87 work but still moves
the texture-handle load before geometry stores. No credit. See
[SPRITE_RECTANGLE_RENDER_2026_10_28.md](SPRITE_RECTANGLE_RENDER_2026_10_28.md)
and build/frontier-4070c0-20261028/strict-fp.json.

Preceding bounded candidate: Fighter cutin resource destructor465420 now has
complete natural sprite/resource lifetime source. Candidate95/native96 remains
nonexact+40 on handle load versus EH-state publication; no credit. See
[FIGHTER_CUTIN_LIFETIME_2026_10_28.md](FIGHTER_CUTIN_LIFETIME_2026_10_28.md)
and build/frontier-465420-20261028/formal-build.json.

Preceding bounded checkpoint: wave buffer release401A80 is canonical exact97/97.
Native constructor independently pins the paired32-element base/spatial arrays;
ordinary source preserves three COM release guards per slot. See
[WAVE_BUFFER_RELEASE_2026_10_28.md](WAVE_BUFFER_RELEASE_2026_10_28.md)
and build/frontier-401a80-20261028/formal-build.json.

Preceding bounded checkpoint: scene-owned battle effect bootstrap6654A0/6654C0
is canonical exact21/10. Native scene callers, global owner and embedded
program extent are attested; no shader bytes or static-init thunk credit. See
[BATTLE_EFFECT_BOOTSTRAP_2026_10_28.md](BATTLE_EFFECT_BOOTSTRAP_2026_10_28.md)
and build/frontier-6654a0-20261028/formal-build.json.

Preceding bounded checkpoint: effect global forwarding6609C0/6609F0/665470
is canonical exact47/16/45. Distinct info/weather globals and scene state08
policy retain the target member-compatible versus cdecl boundaries. See
[EFFECT_GLOBAL_FORWARDERS_2026_10_28.md](EFFECT_GLOBAL_FORWARDERS_2026_10_28.md)
and build/frontier-6609c0-20261028/formal-build.json.

Preceding bounded checkpoint: InfoEffectObject transform660730 and action
initializer660780 are canonical exact80/266. Complete initializer576-byte
code/table payload also matches. Real float shift lifetime and native late
alpha-case family ordering close both; pending update65CB40 stays nonexact. See
[INFO_EFFECT_VISUAL_2026_10_28.md](INFO_EFFECT_VISUAL_2026_10_28.md)
and build/frontier-660730-20261028/late-alpha-group.json.

Preceding bounded checkpoint: endpoint-edit initializer442390 is canonical
exact165/165. One input receiver, native17/10 cursor counts and signed promoted
address arithmetic reproduce the whole body. History selector443030 is complete
153/native157 with retained-tail merging residual, no credit. See
[CONNECT_ENDPOINT_SELECTION_2026_10_28.md](CONNECT_ENDPOINT_SELECTION_2026_10_28.md)
and build/frontier-442390-20261028/final-build.json.

Preceding bounded candidate: connect endpoint digit editor441E10 now restores
complete IP/port decimal selection and replacement. Native cursor pair and
branch-owned powers recover a192-byte exact prefix; full888/native891 remains
nonexact at return scheduling. Port-only sibling441BD0 is now complete
568/native570, first+106 at the same epilogue scheduling boundary. No credit. See
[CONNECT_DIGIT_EDITOR_2026_10_28.md](CONNECT_DIGIT_EDITOR_2026_10_28.md)
and build/frontier-441e10-20261028/cursor-pair.json.

Preceding bounded candidate: result-menu character refresh447080 now has a
complete342/native342 focused replay. Real class-valued texture result and
branch-local input publication replace the retained hidden-result/zero-cast
source. Remaining mismatch+38 is early selected-character load scheduling;
no credit. See [RESULT_CHARACTER_REFRESH_2026_10_28.md](RESULT_CHARACTER_REFRESH_2026_10_28.md)
and build/frontier-447080-20261028/branch-input-binding.json.

Preceding bounded checkpoint: CProfileCharacterSelect render448420 is canonical
exact205/205. Direct branch-local item expressions recover native count reloads
and x87 rounding; cached item controls were shorter and are not retained.
RTTI slot0C and complete56-instruction/tail boundary verified. See
[PROFILE_CHARACTER_SELECT_RENDER_2026_10_28.md](PROFILE_CHARACTER_SELECT_RENDER_2026_10_28.md)
and build/frontier-448420-20261028/direct-item-expressions.json.

Preceding bounded checkpoint: DirectSound wave load4184B0 is canonical
exact304/304, and CDS3DBuffer constructor4180B0 is exact20/20 after
restoring derived ownership of both resource pointers. Six accepted lifetime
peers remain exact; normal destructor139 remains nonexact+47. Natural owned-wave lifetime and real COM lock/copy/unlock close
all114 native instructions. Source uses the observed ordinary fastcall
dispatcher408ED0 without fabricating its private decoder child ABI. See
[DIRECT_SOUND_WAVE_LOAD_2026_10_28.md](DIRECT_SOUND_WAVE_LOAD_2026_10_28.md)
and build/frontier-4184b0-20261028/formal-build.json.

Preceding bounded checkpoint: global replay storage constructor43F1B0 is
canonical exact161/161, now with shared injected-input ctor42C930 exact27/27.
RTTI corrects its inherited update override; profile192/205 and score defaults
remain exact on focused replays. Real two-input ownership plus vector/string/critical
section members reproduce the whole constructor naturally. Global thunk and
implicit cleanup remain uncredited. See
[REPLAY_STORAGE_CONSTRUCTOR_2026_10_28.md](REPLAY_STORAGE_CONSTRUCTOR_2026_10_28.md)
and build/frontier-43f1b0-20261028/formal-build.json.

Preceding bounded candidate: CSelect destructor424260 restores complete authored
release policy and natural member destruction. Direct token values recover
845/native845 and the first605 bytes; remaining mismatch is generated cleanup
scheduling at4244BD. A typed sprite member trial was worse and fully reverted.
No exact credit. See [SELECT_DESTRUCTOR_2026_10_28.md](SELECT_DESTRUCTOR_2026_10_28.md)
and build/frontier-424260-20261028/restored-final.json.

Preceding bounded candidate: Scenario label selection455490 now restores the
owned-string search and real12-byte checked script iterator. Candidate275/
native276 remains nonexact+36 on owner lifetime; named-script control251
eliminates a target-retained range check and is not retained. No credit.
See [SCENARIO_LABEL_SELECTION_2026_10_28.md](SCENARIO_LABEL_SELECTION_2026_10_28.md)
and build/frontier-455490-20261028/formal-build.json.


Preceding bounded checkpoint: CLoadingCL scene-state mapper426490 is canonical
exact26/26, with205/313/217 Select network peers still exact. Current RTTI
vtable6C0524 fixes the authored slot04 policy; no generated thunk credit.
See [SELECT_NETWORK_RUNTIME_2026_10_28.md](SELECT_NETWORK_RUNTIME_2026_10_28.md)
and build/frontier-4264b0-20261028/loading-client.json.


Preceding bounded candidate: CSelect frame update421430 now has complete
menu/input reassignment, cursor publications and native input-deque ownership.
Candidate685/native697 remains first+337 on cdecl cleanup/publication ordering;
no exact/source-selection credit. All231 native instructions are reachable.
See [SELECT_SCENE_UPDATE_2026_10_28.md](SELECT_SCENE_UPDATE_2026_10_28.md)
and build/frontier-421430-20261028/formal-build.json.


Preceding bounded checkpoint: CSelect portrait binding41FB80 is canonical
exact258/258. Ordinary scalar conversion of the real class-valued texture
result recovers native handle/buffer lifetime. Related object transform41FAD0
is complete154/154 but nonexact+25 on receiver/x87 scheduling, with no credit.
See [SELECT_CHARACTER_BINDING_2026_10_28.md](SELECT_CHARACTER_BINDING_2026_10_28.md)
and build/frontier-41fb80-20261028/scalar-handle-local.json.


Preceding bounded candidate: CSelect entry421120 now restores the complete
783-byte input/cursor/character/stage setup path. Candidate783/native783
remains first+225 after target-backed input-value, cursor and UI-receiver
lifetime recovery. Residual begins at zero-register scheduling; no exact credit.
See [SELECT_SCENE_ENTRY_2026_10_28.md](SELECT_SCENE_ENTRY_2026_10_28.md)
and build/frontier-421120-20261028/byte-ui-enabled.json.


Preceding bounded checkpoint: CSelectSV update4262A0 is canonical exact217/217;
same-unit205/313 peers remain exact. The neighboring CBattleSV/CL update
roots426180/426380 are now complete candidates252/247 and259/267, with only
the inspected return/tail-merge region left after switch dispatch recovery.
No credit for those two candidates.
See [SELECT_NETWORK_RUNTIME_2026_10_28.md](SELECT_NETWORK_RUNTIME_2026_10_28.md)
and [BATTLE_NETWORK_UPDATE_2026_10_28.md](BATTLE_NETWORK_UPDATE_2026_10_28.md).


Preceding bounded checkpoint: Select network entry4264B0 and client update426580
are canonical exact205/313, adding518 authored bytes. Current RTTI fixes
SV/CL ownership; natural event RAII and virtual session/input callbacks close
both complete bodies. No shared-header changes.
See [SELECT_NETWORK_RUNTIME_2026_10_28.md](SELECT_NETWORK_RUNTIME_2026_10_28.md)
and build/frontier-4264b0-20261028/formal-build.json.


Preceding bounded candidate: combo resource load46A8C0 was independently
rechecked using current typed CDesignBase/CNumber owners. Complete427/native413
remains first+2 on extra receiver/member-address lifetime. Outer-owner and
typed-output controls did not solve it; shared-type source is retained.
See [INFO_COMBO_LOAD_2026_10_28.md](INFO_COMBO_LOAD_2026_10_28.md).
No exact/source-selection credit or existing caller changes.


Preceding bounded checkpoint: local/practice battle controls428070 are canonical
exact482/482, including the internal loop-alignment gap and final return.
Repeated mode queries, signed modulo cycling and fresh scene/fighter reads
match naturally. Existing callers/contracts remain unchanged.
See [LOCAL_PRACTICE_BATTLE_CONTROLS_2026_10_28.md](LOCAL_PRACTICE_BATTLE_CONTROLS_2026_10_28.md)
and build/frontier-428070-20261028/formal-build.json.


Preceding bounded checkpoint: CBattleManager pre-reset virtual472230 is
canonical exact314/314. The existing fully described CMenuPractice0x288 layout
supersedes the historical allocation blocker; ordinary menu/input/EH source
now matches the complete body. No shared header or global profile changed.
See [BATTLE_MANAGER_PRE_RESET_2026_10_28.md](BATTLE_MANAGER_PRE_RESET_2026_10_28.md)
and build/frontier-472230-20261028/formal-build.json.


Preceding bounded candidate: spell preparation45DC90 now uses the real typed
sprite record and deque ownership. Its old GS-buffer blocker and stale
addresses/dataflow are corrected; current257/native259 remains nonexact.
Initial entry/size loads now agree; optional-resource load/reuse is residual.
Accepted front-ready118 remains exact; existing198/346 nonexact peers retain
their residuals. See [SEQUENCE_PREPARATION_2026_10_28.md](SEQUENCE_PREPARATION_2026_10_28.md).
No new exact credit from this candidate.


Preceding bounded candidate: input policy428260 now has complete Practice and
non-Practice restoration, guard, mode and player-input source. Raw CFG closes
the553-byte callable plus five-entry table; candidate callable554/full576
is nonexact at+9. No source-selection/exact credit. Pair-capture control was
byte-neutral; no register/liveness workaround is retained.
See [PRACTICE_BATTLE_POLICY_2026_10_28.md](PRACTICE_BATTLE_POLICY_2026_10_28.md).


Preceding bounded checkpoint: presentation phase46B160 and Story reset471580
are canonical exact105/14, adding119 authored bytes. All five previously
accepted Story core peers remain exact in the fresh caller-unit replay.
See [BATTLE_PRESENTATION_PHASE_2026_10_28.md](BATTLE_PRESENTATION_PHASE_2026_10_28.md)
and build/frontier-46b160-20261028/{formal-build,story-caller}.json.


Preceding bounded checkpoint: Story early phase pipelines471590/4715D0 are
canonical exact59/88. Existing203/157/309-byte Story peers remain exact.
RTTI-owned slots10/14, scenario callback/transition policy, signed countdown
and pending transition are raw-target backed. New authored increment147 bytes.
See [STORY_EARLY_PIPELINES_2026_10_28.md](STORY_EARLY_PIPELINES_2026_10_28.md)
and build/frontier-471590-20261028/formal-build.json.
The typed-owner trial for471930 was byte-neutral321/323 and is retained privately;
public source was restored, with no exact credit.


Preceding bounded checkpoint: story value binder471A80 is now canonical
exact351/351. A mode-specific typed owner recovers native integer health and
UI-receiver lifetimes; same-unit20/27/648 accepted peers remain exact.
The old352-byte normal-mode alias candidate is superseded, not silently
recredited. No shared header or compiler setting changed. New authored exact
increment across the recent four accepted helpers is755 bytes.
See [STORY_INFO_VALUE_BINDING_2026_10_28.md](STORY_INFO_VALUE_BINDING_2026_10_28.md)
and build/frontier-471a80-20261028/formal-typed-owner.json.

Preceding exact checkpoint: normal InfoManager initializer46EB90 is
canonical exact228/228. Typed embedded resources and the actual number-pointer
array remove the prior loop-cursor spill naturally. Same-unit119/171/30
lifetime peers remain exact; no shared header/global profile/data binding
changed. New authored exact increment across tangent406430, binder432550 and
this initializer is404 bytes, excluding generated sprite-copy code.
See [INFO_MANAGER_NORMAL_INITIALIZATION_2026_10_28.md](INFO_MANAGER_NORMAL_INITIALIZATION_2026_10_28.md)
and build/frontier-46eb90-20261028/formal-build.json.

Preceding checkpoint: story InfoManager update471930 now restores
health/secondary smoothing and timer/alpha callbacks. Complete321/native323
remains first+67 in the second signed smoothing stage; no exact credit.
Its first67 and shifted trailing201-byte windows agree, but full ownership
and positional bytes do not. Rejected clamp/scoping controls remain private.
See [STORY_INFO_UPDATE_2026_10_28.md](STORY_INFO_UPDATE_2026_10_28.md)
and build/frontier-471930-20261028/formal-build.json.

Preceding checkpoint: story value binder471A80 now restores both
integer gauges and both float-number adapters with native release/new and
span-capture ordering. Complete352/native351 remains first+16 on the initial
health-address/store schedule; no credit. Same-unit20/27/648 accepted peers
remain exact. No shared header or global compiler setting changed.
See [STORY_INFO_VALUE_BINDING_2026_10_28.md](STORY_INFO_VALUE_BINDING_2026_10_28.md)
and build/frontier-471a80-20261028/formal-build.json.

Preceding exact checkpoint: long InfoManager record binder432550 is canonical
exact107/107. Native byte-side consumption and coherent caller declarations
recover the actual output homes. All five functions in its two affected
accepted caller units remain exact. No global flags or data bindings changed.
See [INFO_LONG_RECORD_BINDING_2026_10_28.md](INFO_LONG_RECORD_BINDING_2026_10_28.md)
and build/frontier-432550-20261028/formal-*.json. Together with tangent406430,
the new authored exact increment is176 bytes; generated sprite copy455160
remains excluded and receives no authored credit.

Preceding checkpoint: Fighter sequence rotation45DDA0 now uses the real
VC8 deque and a nontrivial polymorphic card temporary. Main265/265 remains
12 unequal bytes at+123, confined to prefix-load/store scheduling. Generated
record destructor8 bytes, unwind/handler44 bytes and metadata44 bytes replay
exact independently; no authored credit is added for them or the main body.
See [FIGHTER_SEQUENCE_ROTATE_2026_10_28.md](FIGHTER_SEQUENCE_ROTATE_2026_10_28.md)
and build/frontier-45dda0-20261028/formal-{build,auxiliary}.json.

Preceding exact checkpoint: float-angle tangent406430 is canonical exact69/69.
The existing strict-FP profile plus balanced exception-scheduling-off pragma
reproduces every byte without changing global build defaults. This adds one
accepted function/69 bytes. Sine/cosine dependencies and Udonge remain nonexact.
See [ANGLE_TANGENT_2026_10_28.md](ANGLE_TANGENT_2026_10_28.md)
and build/frontier-406430-20261028/formal-build.json.

Preceding checkpoint: Udonge5BFD50 has a complete-label unselected
110-action candidate and shared prelude. Full replay67520/native67968,
first+8 at5BFD58; frame488/native480. All32/34/39 sparse groups resolve.
All110 per-action direct-call and FP-site counts agree;406 still merges
one native virtual owner. All92 packet homes resolve, but frame displacement
and ten per-action ownership differences remain. Cone tangent evaluation
retains native post-call peer reloads without an extra FST32. No exact credit.
See [UDONGE_ACTION_STATE_2026_10_28.md](UDONGE_ACTION_STATE_2026_10_28.md)
and build/frontier-5bfd50-20261028/formal-{build,full,switches}.json.

Preceding checkpoint: Suika598990 has a complete-label unselected
115-action candidate. Full replay78988 versus native81136, first+17, frame578
matches native. Sparse candidate groups32/50/31 versus native33/50/31;
208/220 merge. Giant605/730 static surface/zero-motion bodies also merge;
grab608 shared pose tails now restore its native direct/virtual call counts,
while arithmetic ownership remains under review. Separate501 return guards
also restore its virtual-site count. Native action ordering now aligns all112
packet-home offsets. The native740 early/late phase order now also aligns all115
ordered per-action packet-home lists. No exact credit.
See [SUIKA_ACTION_STATE_2026_10_28.md](SUIKA_ACTION_STATE_2026_10_28.md)
and build/frontier-598990-20261028/formal740-{build,full}.json.

Preceding checkpoint: Marisa4A3710 now has a complete unselected
130-action source candidate and shared prelude. Native-backed 565..568 scalar
captures now retain both request branches; action708 narrows velocity before
its QWORD predicted-Y capture. Current full compile68204 versus
native67936, first+14, frame4C8 versus4C0. All32/45/48 action-table groups and98
payload homes resolve; flight214 rate branches now match native arithmetic
ownership. Direct-call and arithmetic-site counts agree across all130 actions,
but virtual-call and lifetime differences remain. No exact credit.
See [MARISA_ACTION_STATE_2026_10_28.md](MARISA_ACTION_STATE_2026_10_28.md)
and build/frontier-4a3710-20261028/trial214-*.json.

Preceding checkpoint: Yuyuko720 now preserves the native QWORD Y
capture and unordered surface predicate: action700 only for ordered surface>=Y,
gravity otherwise. Complete unselected source59456/full59672 remains first+8.
See [YUYUKO_ACTION_STATE_2026_10_28.md](YUYUKO_ACTION_STATE_2026_10_28.md)
and build/frontier-55d850-20261027/formal-surface720*.json. No exact credit.

Preceding checkpoint: Tenshi raw-backed scalar captures reduce the
extra frame from16 to8 bytes; request and atan argument lifetimes are refined.
The complete unselected candidate is49032/full48968, first+8, frame328 versus320.
All35/36/37 action-table groups and64 payload homes resolve. See
[TENSHI_ACTION_STATE_2026_10_27.md](TENSHI_ACTION_STATE_2026_10_27.md)
and build/frontier-63d3e0-20261027/formal-lifetimes*.json. No exact credit.

Preceding checkpoint: Patchouli request-branch ownership, argument
lifetimes and flight214 physical placement now follow native evidence.
The complete unselected candidate is55026/full55610, first+8, frame468.
All109 actions have matching per-action call/FP-site counts and91 resolved
payload homes; these diagnostics do not establish exactness. See
[PATCHOULI_ACTION_STATE_2026_10_27.md](PATCHOULI_ACTION_STATE_2026_10_27.md)
and build/frontier-50f200-20261027/formal-ownerorder*.json. No exact credit.

Preceding checkpoint: Yuyuko captured-X width and eight aim-argument
lifetimes now follow raw native storage/evaluation evidence. The complete
candidate remains unselected/nonexact,59456/full59672, first+8, frame4F0.
All100 payload homes resolve. See
[YUYUKO_ACTION_STATE_2026_10_28.md](YUYUKO_ACTION_STATE_2026_10_28.md)
and build/frontier-55d850-20261027/formal-lifetimes*.json. No exact credit.

Preceding checkpoint: Yukari aim argument lifetimes now follow the native
DX-outgoing-before-DY sequence at seven atan sites. Their local 32-byte windows
match; the complete candidate remains 57792/full58248, first+8, frame4E8.
See [YUKARI_ACTION_STATE_2026_10_28.md](YUKARI_ACTION_STATE_2026_10_28.md)
and build/frontier-57b030-20261028/formal-aimargs*.json. No exact credit.

Preceding checkpoint: Remilia circular request preparation now recovers
the native 4F0 frame. Its complete unselected 107-action candidate emits
62912/full63316, first +18; all sixteen tables and 101 payload homes resolve.
[KOMACHI_ACTION_STATE_2026_10_28.md](KOMACHI_ACTION_STATE_2026_10_28.md)
and [REMILIA_ACTION_STATE_2026_10_28.md](REMILIA_ACTION_STATE_2026_10_28.md)
record the separate scalar-angle and call-preparation causes. No exact credit.
Latest Remilia receipts: build/frontier-545090-20261028/formal-frame*.json.

Preceding Komachi f1df72c2 remains complete but unselected/nonexact:
64884/full65176, first +42, native 490 frame; 108 actions, seven tables and
94 payload homes. Byte-direction view is supported by its actual manager.
Receipts: build/frontier-5e20e0-20261028/formal-frame*.json.

Preceding Yukari b491d153 remains complete but unselected/nonexact:
57792/full58248, first +8; 124 actions and 101 payload homes resolved. See
[YUKARI_ACTION_STATE_2026_10_28.md](YUKARI_ACTION_STATE_2026_10_28.md).

Preceding Yuyuko97a2575e remains complete but unselected/nonexact:
59428/full59672, first+8;116 actions and100 payload homes resolved. See
[YUYUKO_ACTION_STATE_2026_10_28.md](YUYUKO_ACTION_STATE_2026_10_28.md).

Preceding Patchouli203faa8b remains complete but unselected/nonexact:
54466/full55610, first+8;109 actions and91 payload homes resolved. See
[PATCHOULI_ACTION_STATE_2026_10_27.md](PATCHOULI_ACTION_STATE_2026_10_27.md).

Preceding Tenshi80a9f71d remains complete but unselected/nonexact:49096/full48968,
first+8, two low-owner pairs merged. Its47,784-byte native root and110 actions
are covered; RNG widths, coordinate types, live packets and shared500/501 tail
were refined. See
[TENSHI_ACTION_STATE_2026_10_27.md](TENSHI_ACTION_STATE_2026_10_27.md).

Preceding b14285d6 Fighter reset460200 remains1247/1247 with25 differences,
unselected/nonexact. Directly affected fighter-input-phase remains exact; see
[FIGHTER_BATTLE_RESET_2026_10_27.md](FIGHTER_BATTLE_RESET_2026_10_27.md).

The preceding94f0f3b7 checkpoint corrects general hit resolver46BF80 semantics;
its complete1581/1579 source remains nonexact. See
[GENERAL_HIT_RESOLVER_2026_10_27.md](GENERAL_HIT_RESOLVER_2026_10_27.md).

The prior CBattleManager phase5 transition4724E0 remains991/991 exact, including
its separately audited generated GS/EH code and metadata; cd976369 passed the
final local CI. Weather emission660B30 remains12198/full12348 exact and
WeatherEffectObject entry664E10 remains1383/full1630 exact. The complete
InfoEffectObject and WeatherEffectObject update peers remain nonexact.

The complete preceding handoff is preserved in
[October26 history](RE_HANDOFF_HISTORY_2026_10_26.md). Earlier chronology and
private artifact recovery remain linked from that archive and [ARTIFACTS.md](ARTIFACTS.md).
Live ledgers and fresh command output take precedence over historical counts.

## Start here

Workflow maintenance (2026-10-28): routine CI now checks exact-comparison tooling
and ledgers; analysis/probe suites are optional via `scripts/ci.py --all-tests`.
Removed 69 historical checkpoint/count/source snapshots. Allocation-failure,
null-pointer and broad runtime matrices are not reconstruction prerequisites.
CI checks progress without rewriting it. No source, target address, match ledger
or acceptance receipt changed; existing reconstruction blockers above remain.

1. Read `AGENTS.md`, this file and the relevant source; consult architecture and
   workflow notes as needed.
2. Inspect Git status and the source/evidence document for the intended scope.
3. Use `scripts/repo-python`; reconstruction/ledger work uses the preflights below.
   Run the IDA check only when using IDA. Maintenance needs no native preflight.
4. Keep one writable bounded scope, no subagents or concurrent VC8/Ghidra jobs.
   `config/claims.csv` remains header-only. Builds use CPU0/nice10 serially.
5. Compare the first complete medium/large source early. Test one supported
   question per trial; retain byte-neutral results and switch without a grid.
   Review family peers independently. Defer naming/abstraction until exactness.

```bash
git status --short
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/check-ida-mcp.py
scripts/repo-python scripts/report-reconstruction-status.py --summary
scripts/repo-python scripts/validate-tracking.py --require-target
```

## Immutable target and environment

Only original Japanese TH10.5v1.06a is valid: SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`,
image base400000, entry68B9D2. Do not substitute another patch/localization.
The direct IDA launcher currently lacks mcp1.26.0/uv. Factory native IDA was
freshly attested on October27 to this exact target, entry and mapped entry bytes;
its inventory, disassembly, decompilation and xref operations succeeded.
Any Ghidra use requires separate import/entry/mapped-byte attestation. Never
patch the target or infer ownership from disassembler auto-analysis.

The isolated environment pins Python3.11.14, Capstone4.0.2, pefile2024.8.26,
Unicorn1.0.2 and setuptools75.8.0. The repo launcher enforces it. Preserve the
active `.venv`, its external UV interpreter and installed VC8 SP1 toolchain.
Use the VC8 x86 ABI and exact target facts;42 LTCG Rich records do not establish
that a particular standalone mismatch requires LTCG.

## Current durable state

| Ledger state | Count |
| --- | ---: |
| Provisional / authored / excluded / review candidates |4024 /1625 /1419 /980 |
| Mapped / source-present |1614 /1586 |
| Exact functions / authored bytes |1431 /414554 |
| Configured units / functions |642 /1614 |
| Accepted units |539 |

The423a2cd checkpoint passed529 cold units/1417 functions and390476 bytes.
Subsequent focused comparisons add story refresh860, replay naming1322 and
pattern expansion1323, deck update1339, stage selection890, selection flow341
EffectObject entry2676; WeatherEffectObject entry1383 and weather emission12198 and battle phase5 transition991,
with unchanged prior receipts retained. Current totals are incremental, not a
new whole-corpus replay. Final CI is the current frontier's `local-ci.log`.

`implemented.csv` means selected source-present; `matches.csv` requires canonical
100% equality against this target. Complete unselected source already exists
for many nonexact roots. Do not infer that a function is unwritten merely from
its absence in implemented.csv. No helper inherits a caller's ownership/match.

## Latest score-family checkpoint

| Target | State | Source / evidence |
| --- | --- | --- |
|42D3F0 |1155/1155 exact |`src/config/ScorePersist.cpp`; [persistence](SCORE_PERSIST_2026_10_26.md) |
|42ED70 |2428/2428 exact |`src/config/ScoreDefaults.cpp`; [defaults](SCORE_DEFAULTS_2026_10_26.md) |
|42F6F0 |Complete1672-byte source;7 SIB-order differences; unselected |`src/config/ScoreLoad.cpp`; [loader](SCORE_LOAD_2026_10_26.md) |

Shared definitions: `src/config/ScoreDataDefaults.hpp`. Constructor43E1A0
independently proves20 map/vector slots. Defaults and persistence use only15
roster keys; source layout is a bounded view, not the complete original owner.

Persistence's first whole source was1155 bytes with80 differences, first42D661.
One real count shared by serialized roster size and loop bound closes all1155
bytes, SHA7c1f3777. All360 instructions/359 reached, RET0,3C-frame EH/cookie,
19 checked-container guards and full relocations are accounted for. Four native
and candidate cases pin332-byte serialization, duplicate records, values above
200, ignored open/encode/write failure results, source preservation and cleanup.
Actual I/O, compression providers and EH unwinding are not executed by fixtures.

The October27 native vector.clear recovery improves the loader to1672 bytes
with7 SIB-order differences (SHA6641fe76). A fresh genuine three-source TU
preserves both exact peers and leaves this new loader residual unchanged.
The four existing native/candidate observer cases agree; no new exact credit.
See the superseding loader note and `build/frontier-42f6f0-clear-20261027/`. Original nominal types/TU and loader stack/iterator scheduling remain
unknown; no LTCG-impossibility claim follows. The prior bootstrap return-type
repair retains its complete3722-byte/11-difference nonexact body.

Current scope receipts and raw decode:
`build/frontier-42d3f0-20261026/` (`formal-first.json`, `formal-second.json`,
`formal-audit-first.json`, `formal-audit-second.json`, `family-tu-summary.json`,
`origins-write.log`, `origins-check.log`, `cold-all.log`, `local-ci.log`).
Private first/count-control/family-TU sources and replay recipe:
`.analysis/frontier-42d3f0-20261026/`.
The new selected root adds1155 exact authored bytes; no provider receives credit.

## Parked work

Do not reopen these lanes without the independent evidence their dated notes
request. The full history records commands, source pins and unknowns.

- Spell resource CSV4343A0 is exact1646; filtered433B30 remains1987 bytes/two
  operand differences. The genuine family-TU lane is closed.
- Collision debug45E950 is exact3087. Rectangle4012A0 remains394 versus395,
  85 unequal positions; native Z0.5 and finite lifetime controls are retained.
- Scene bootstrap43E2E0 remains3722/11 stack-home differences; effect loader
  437EC0 remains2528/79 differences; Fighter PAT461B70 remains3898 versus3885.
- Profile deck render448F60 is2521/1622 differences. Native execution rejected
  a push-relative missing-count misread; correct zero counts agree in32 events.
- Complete giant sources/hypotheses for Tenshi64CD50, Alice4E9F50, Youmu53CEA0
  and Yuyuko56F700 remain saved in their documented selected/unselected states.
  Aya61F0B0's complete4859-byte payload still has two operand differences.

42E990 is now independently reviewed and exact. Small providers and constructors
remain independent unknowns unless positively classified and compared.

## Private recovery and cleanup

The current-scope portable bundle is
`build/handoff-cleanup-20261026/score-family-resume.tar.gz`; its member hashes and
verified archive SHA are in `score-family-members.json` and `bundle.json` in the
same directory. List the archive before restoring repository-relative members;
avoid overwriting newer work. This ignored local archive is not included by a
Git clone. It excludes target PE, compiler installs, databases and credentials;
those remain separate local inputs. Final CI/remote receipts remain loose in
the current build scope. See [artifact details](ARTIFACTS.md).

Source-backed bytecode cleanup and protected-file/worktree checks are recorded
in `build/handoff-cleanup-20261026/cache-cleanup.json`, `protected-before.json`
and `protected-after.json`. Unknown cache files are retained. Primary Ghidra
state remains under `.analysis/iku-vslot28-20261002/project/`, with the retained
snapshot at `.analysis/archive-loader-shape-20261019/primary-before/`.
Six older detached worktrees contain uncommitted work; preserve them and their
frozen inputs. Their presence does not authorize parallel reconstruction.

## Final gate and future commits

Run the focused affected comparisons first. Shared headers/types/flags/TU or
relocation changes require directly affected-unit replay. Preserve unchanged
acceptance receipts for incremental totals; do not rebuild the whole corpus
routinely. Full cold replay requires an explicit request or demonstrated
repository-wide invalidation that cannot be narrowed.
Every commit/push/PR requires the finished lightweight local gate; remote green
is additional. Analysis matrices and the complete optional test collection are
not part of the routine gate.

```bash
PYTHONDONTWRITEBYTECODE=1 taskset -c 0 nice -n 10 scripts/repo-python scripts/ci.py
git diff --check
git diff --cached --check
```

Any later source, ledger, script, test or generated-progress edit requires the
local gate again. Commit prefix: `gpt-6.1-sol: ...`. Keep executables, game data,
analysis databases, compiler installs, generated reports, credentials/private
keys and `.tools/mcp_for_gptweb/.env` out of Git.
