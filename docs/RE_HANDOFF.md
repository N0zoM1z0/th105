# Current reconstruction handoff

## Phase

Two canonical 1.06a authored-exact waves are established. The active phase is
expanding authored classification and exact source recovery beyond raw-identity
seeds using current-target-backed structural remapping where appropriate.

## Verified state

- Canonical SHA-256:
  `56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
- `resources/th105.exe` is byte-identical to the executable extracted from the
  official `th105_update_106a.exe` payload.
- IDA metadata, entry `0x0068B9D2`, five separated mapped-byte samples, required
  read tools, and a function query pass `scripts/check-ida-mcp.py`.
- The fresh IDA auto-analysis inventory remains 4,001 candidates. The corrected tracked ledger has 4,004: current-target boundary evidence recovered `CFileReader_dtor @ 0x0040CEB0` plus source-level fighter phase entries `0x00464630` and `0x00464780`, all of which IDA had attached as tail chunks instead of standalone entries. Current reviewed state is 310 authored functions, 696 classified exclusions, and 2,998 still awaiting origin/boundary review.
- All 310 confirmed authored functions are source-present and canonical exact:
  51,571 exact authored bytes across 155 configured VC8 units.
- The newest retained-source/lifecycle migration wave added 209 functions / 38,037 bytes
  beyond the prior 100-function checkpoint. Structural instruction shape and
  relocation-masked bytes are used only for candidate ranking; every accepted
  function still requires current 1.06a semantic/relocation evidence and a fresh
  canonical zero-difference comparison.
- The lifetime/template origin lane now excludes twenty-three compiler-generated functions through SHA-pinned VC8 replay. The newest singleton is raw-exact `std::map<int, String28>::find @ 0x006A4D60`, freshly emitted from tracked `ScenarioEventNameResolver.cpp` and inventory-unique at 105 bytes. The preceding pair are 72-byte `std::list<void*>::_Tidy` clones at `0x004023E0/0x00435EB0`: a fresh pinned-VC8 COMDAT is canonical 72/72 at `0x00435EB0`, and masking only its two operator-delete REL32 fields yields a complete current-inventory hit set equal to exactly those two addresses. The preceding six `SpellRecordView` `std::_Tree` COMDATs remain replayed by `config/vc8-generated-spell-tree-origin-anchors.toml`; all generated clone groups stay fail-closed and must match their declared complete hit set.
- `Alice_handle_event_bridge @ 0x0050ED00` is now 1075/1075 exact from a narrow natural C++ lifecycle view. Current 1.06a proves the byte return ABI, real virtual action/sequence slots, 22-event semantics, 19-destination jump table, and 121-byte sparse index table; the compiler-owned switch tables trail the accepted ledger body in the same COMDAT.
- `PatRecord88_construct @ 0x00460F90` and `PatRecord88_destroy @ 0x0045FFD0` are 300/300 and 515/515 exact with the current FrameData base and three checked nested vectors; the same pinned VC8 model now classifies current `vector<PatRaw16>::erase @ 0x0045FBD0` as compiler-generated.
- `test_aabb_against_descriptor_shape @ 0x0046B7B0` is 248/248 exact after expressing the already-proved signed broad-phase rejection as an equivalent bit-31 test; this preserves the target AND/TEST/JS schedule without assembly or register forcing.
- `load_indexed_character_wave_resources @ 0x0045F680` is 132/132 exact without source surgery. Current target reads `record_key_330`, resolves the character name at `0x0043BF80`, formats `data/se/%s/%03d.wav`, calls wave service `0x00702288` through `0x00401AF0`, and stores 64 returned handles through Fighter `+0x164`; all non-relocation bytes already matched before current relocation reconciliation.
- The current lifecycle/PAT wave adds exact `Alice::handle_event_bridge` (1,075 bytes) plus full `PatRecord88` construction/destruction (300/515 bytes). The recovered PAT layout now has a 0x1C `FrameData` base, checked `vector<PatRaw16>` members at +0x58/+0x68 and checked `vector<PatRaw16*>` at +0x78; the unique 88-byte value-vector `erase` helper is independently excluded as generated VC8 template code.
- Refined PAT layout evidence also removes `vector<PatRaw16>::operator= @ 0x00460AD0` and the implicit `PatRecord88` copy constructor `0x00460C90` from the authored denominator through SHA-pinned VC8 generated-COMDAT replay. The latter only matches after treating +0x3A/+0x4A as natural alignment gaps and the `FrameData` copy constructor as an out-of-line base lifetime; explicit padding-array members or an inlined implicit base copy do not reproduce the target.
- `load_spell_csv_via_325b0 @ 0x00434300` and `load_spell_csv_via_32e20 @ 0x00434A10` are 148/148 and 161/161 exact after correcting the parser ABI: current wrappers and independent caller `0x00434AC0` all restore `ECX = SpellDataOwner*` immediately before the parser call. Modeling the parser bodies as unused-`this` member functions naturally restores the two missing `mov ecx, esi` instructions and preserves the owner register in the alternate branch.
- Fourteen current character event bridges are now canonical exact from narrow current-target views: Alice plus Reimu, Marisa, Sakuya, Patchouli, Youmu, Remilia, Yuyuko, Suika, Udonge, Komachi, Aya, Iku, and Tenshi. Iku `0x0063CCB0` is 1553/1553 exact: two genuinely distinct `float[3]` spawn temporaries explain the target 0x18 stack frame, and all eight current callers of `0x00434E10` preserve an event-subobject receiver at `+0x130`, proving an unused-`this` member ABI that naturally recreates the target EDI lifetime. Tenshi `0x00659420` is 1412/1412 exact with one unused-`this` member view of `0x004359D0`; case 133 reaches it while ECX still holds `this`, whereas case 134 reloads ECX after shared-state calls clobber the receiver. Yukari remains outside the exact event-bridge set because standalone VC8 removes a target-only redundant `cmp ax,ax; jne` tail in case 156; do not reintroduce that dead test with tautological source or assembly.
- `try_dispatch_flagged_gate_actions_220_224 @ 0x00493B40` is 258/258 exact. Current IDA shows calls from all fifteen roster fighter dispatchers and the established phase/counter callees. The target has three truthful success tails: action 222 keeps its own consume-and-return path, action 220 owns a second counter/return path, and actions 223/224 jump into the latter. Preserving that already-observed CFG in ordinary C++ makes VC8 reproduce all internal branch displacements exactly; no assembly, dead code, padding, or register forcing is used.
- The shared event-helper wave adds five authored exact functions / 127 bytes without changing any of the fourteen exact roster event bridges. `SharedEventState` setters `0x004272B0/0x004272D0` are 17/17 each, `synchronize_targets @ 0x004272F0` is 33/33, `EventSubobject130::set_global_pair @ 0x00434E10` is 34/34, and the unused-receiver `set_shared_second_target @ 0x00476AD0` is 26/26. Fourteen exact callers establish the common state ABI, while the forwarder must remain in a separate TU: making the target setter body visible lets VC8 inline it, unlike the linked 1.06a call body.
- `EventSubobject130::trigger_global_effect @ 0x00434E90` is 74/74 exact and is reached by all fourteen exact roster bridges. Current target fixes event-id publication `0x006FA890`, lookup `0x0043C150`, exact-backed info-manager emitter receiver `0x006FBCA8`, constants `320.0f/42.0f`, and shared state controller `0x006FBCAC`. Keeping the lookup nested as the first emitter argument reproduces the target argument-preparation order naturally; extracting it to a local changes VC8 scheduling.
- `BattleAudioSetupView::set_stage_music_433860 @ 0x00434DE0` is 40/40 exact. Its semantic name comes from exact battle setup `0x00470880`; current body forwards stage/value/notify=1 to battle object manager `0x006FBCA0 -> 0x00467850` and mirrors stage to the already attested event-effect state `0x006FBCAC -> 0x00469D50`. No new relocation anchors were required.
- `EventEffectStateView::set_event_id @ 0x00469DF0` is 29/29 exact. Changed ids update controller `+0` then ordinary `return publish_stage_state(g_battle_transition_mode)` naturally reuses the incoming stack slot and tail-jumps to `0x00469D50`; unchanged ids return directly. A shared `EventEffectState.hpp` now keeps the three recovered event/stage TUs on one ODR-consistent narrow contract.
- `PostSequenceTransitionView::publish_transition_effect_46e040 @ 0x0046EA10` is 47/47 exact. Nine current battle callers converge on the same helper, including the canonical-exact round-transition dispatcher. The body forwards through a polymorphic emitter subobject at `this+4`, vslot `+0x0C`, with `(effect_id, 320.0f, 240.0f, 1, 0, 0)`. Both float literals were already exact-backed elsewhere; a shared narrow facade now replaces duplicated local declarations without changing the exact round-transition caller.
- `InfoEffectEmitterView::emit_effect @ 0x0046E9D0` is 49/49 exact. Exact `trigger_global_effect @ 0x00434E90` establishes the caller identity; current IDA shows the facade takes its polymorphic emitter subobject at `this+4`, calls vslot `+0x0C`, forwards the five caller arguments, and appends a real trailing zero argument. Moving the narrow emitter contract into `InfoEffectEmitter.hpp` leaves the existing 34/34 and 74/74 `EventSubobject130` helpers exact.
- `EventSubobject130::trigger_secondary_event_effect @ 0x00434E40` is 67/67 exact. Fifteen current dispatch cases all pass `ECX = Fighter+0x130` and immediately return after the call, proving an unused-receiver `void` member rather than the decompiler's incidental-EAX `int` guess. The helper ignores id 16, publishes `0x006FA884`, then emits `lookup(id)+4` at 320/32.
- `PairEmbeddedModeView::select_pair_mode_434780 @ 0x00435CE0` is 119/119 exact. Exact battle-pair initialization already owns the member edge; current body optionally publishes the primary effect, emits `lookup(mode)+2`, synchronizes mode globals `0x006FA884/0x006FA880`, and uses exact `selector_random_roll(14)` for mode 14. Extracting the view into `PairEmbeddedMode.hpp` leaves the original 279/279 caller exact.
- `Fighter::advance_secondary_event_effect_cycle @ 0x00473F90` is 244/244 exact. Cross-roster current callers pass Fighter `this`; the fourteen exact event bridges already agree that `EventSubobject130` occupies Fighter `+0x130`, so the shared `Fighter` layout now names that subobject instead of leaving those 12 bytes unknown. While pair mode is 16, a dense 0..14 switch rotates the secondary event-effect id and dispatches the exact 67-byte member. VC8 places a 60-byte jump table after the accepted 244-byte body in the same COMDAT.
- The CBattleManager shared-vtable wave adds nine authored exact functions / 603 bytes. Current constructors `0x00438CC0` and `0x00438D80` publish `CBattleManager` vtable `0x006C1504` and `CBattleManagerArcade` vtable `0x006C154C`; both tables share the recovered slots at `0x00471630`, `0x00471920`, `0x00472490`, `0x004724B0`, `0x00472D80`, `0x00472DC0`, `0x00472E10`, `0x00472EA0`, and `0x00472F10`. Natural VC8 preserves unsigned `frame_counter_04`, Fighter `+0x4EC/+0x4E9/+0x72C`, `this+0x8C` phase-object dispatch, and caller-backed unused-this views of linked phase helpers. The neighboring `0x00472A70` timer method remains review-pending: semantics/data are closed, but standalone VC8 does not reproduce the target 16-bit timer value scheduling without disallowed coercion.
- The scene/audio transition + Arcade wave adds eight authored exact functions / 470 bytes. Screen-fade state helpers are `get_async_scene_load_request @ 0x0043AB90` (6), `start_scene_fade_out @ 0x0043B240` (58), `start_scene_fade_in @ 0x0043B280` (58), and `is_scene_fade_in_progress @ 0x0043B2C0` (24). Current BGM loaders `0x0043CF00/0x0043CF80` prove that `0x006FCF7C`/`0x007026E0` are BGM handle/service, supporting exact `stop_bgm @ 0x0043B120` (17), `fade_bgm @ 0x0043B140` (40), and `set_bgm_volume @ 0x0043B170` (47). With those facades, `CBattleManagerArcade::run_info_phase_pipeline @ 0x00473870` is 220/220 exact using current derived state `+0x5BC/+0x5C4` and the shared base pipeline. `0x00472F80` remains review-pending because one final branch differs only in target vptr/vslot load scheduling; manual vtable evaluation was rejected.
- `CBattleManagerArcade::prepare_arcade_transition @ 0x00473050` is 189/189 exact in the same `/GS` TU as the 220-byte Arcade override. Current exact setup services establish MatchSetup stage/BGM bytes, object-manager reset, `this+4` stage/music facade, fighter-phase begin/configure, and pair initialization. The derived container at `+0x5B4` is a VC8 checked-list view with sentinel pointer `+4` and size `+8`; natural `erase(begin())` generates the target 8-byte iterator-by-value argument plus hidden 8-byte return storage. The 260-byte `data/bgm/st%02d.ogg` path buffer and security cookie reproduce without assembly or stack forcing.
- The UI-selection state wave adds two authored exact helpers / 112 bytes. `has_ui_selection_state_changed @ 0x0043B6E0` is 24/24 exact from the current unsigned dword-state minus byte-snapshot predicate. `set_ui_selection_state_tracking @ 0x0043FFB0` is 88/88 exact and establishes `g_ui_selection_state @ 0x006FD290`, snapshot/fade bytes `0x006FD046/0x006FD047`, and checked `std::list<UiSelectionMenu*> @ 0x006FD288`; disabled nonzero state walks `back()` through the sentinel at base+4 and tail-calls the selected menu vslot +4. These globals are loader-zero virtual-tail storage, so relocation provenance must preserve that fact and the list's +4 addend.
- `Menu::render_cursor @ 0x0043F9D0` is 55/55 exact from a narrow shared cursor-sprite view. Current IDA has twelve callers, proves receiver base `0x006E6958`, scale fields `+0x88/+0x8C`, direct render `0x00406BE0`, and the double `1/512` literal at `0x006C1860`. The match unit preserves one aggregate symbol and validates the two interior DIR32 references through symbol+addend mappings instead of inventing field globals.
- The global input-state facade adds `is_menu_initial_press @ 0x0043ABD0` (31/31) and `set_menu_input_state @ 0x0043ABF0` (21/21). Both load receiver `0x006FC618` and forward unchanged byte/bool stack slots to already exact members `0x0040A660/0x0040A6B0`. Canonical PE mapping proves the receiver is loader-zero virtual-tail storage even though IDA presents a nonzero-looking inferred value; relocation provenance follows the PE mapping.
- `character_key_to_name @ 0x0043BF80` is 78/78 exact from the same tracked `std::map<int,String28>` contract already backing exact `resolve_scenario_event_name @ 0x0043BFD0`. Current resource/spell callers independently use the forward key-to-name direction; fresh VC8 checked iterators and `String28` SSO/heap `c_str()` selection reproduce the full target body. The emitted `std::map<int,String28>::find` COMDAT is itself raw-exact and inventory-unique at current `0x006A4D60`, so it is separately excluded as compiler-generated.
- `config/claims.csv` remains header-only. IDA Pro remains the sole semantic
  backend.

## Cross-version seed decision

The former repository targeted 1.06 (`3,039,232` bytes), not 1.06a, so its
addresses, classifications, and exact claims remain invalid for the current
target. A raw-byte uniqueness survey may be used only to prioritize retained
source hypotheses.

The first migration wave intersected old authored/exact hypotheses with unique
raw-identical 1.06a candidates, then rebuilt every retained source with the
pinned VC8 toolchain and required a fresh canonical zero-difference compare.
That procedure promoted 47 functions; raw identity by itself promoted none.
REL32 destinations were checked against the current target. In particular, the
second loader called by `load_spell_data` is `0x00434300` in 1.06a; a guessed
cross-version delta produced a mismatch and was rejected before IDA confirmed
the current call target.

## Next bounded work

Continue origin/boundary review so the authored denominator becomes meaningful,
then expand exact recovery from the 309 accepted functions. Use
`scripts/rank_retained_exact.py --only-unconfigured` to prioritize historical
exact source that never had an old match unit. Same-size zero non-relocation
mismatch candidates are especially productive, but ambiguous template/clone
families must be disambiguated with
current xrefs/vtables/RTTI/relocations. Treat every old 1.06 address, callee,
name, and implementation as a hypothesis until independently reconciled
against 1.06a.

The 95% authored-function and authored-byte goals cannot be reported yet: 2,998
provisional candidates still need authored/excluded classification, so the
global authored denominator is not established. Do not use the current 310/310
exact subset as a substitute denominator.

## Routine checkpoint

```bash
python3 scripts/verify-target.py
python3 scripts/check-ida-mcp.py
python3 scripts/validate-tracking.py --require-target
python3 scripts/build.py --check
python3 scripts/progress.py --check
python3 scripts/verify-exact-units.py --all
python3 scripts/ci.py
git diff --check
```
