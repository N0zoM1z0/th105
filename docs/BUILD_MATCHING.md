# VC8 build and exact matching

The target's linker/Rich metadata establishes the VC8 family and compiler build
50727; `config/tools.lock.toml` pins the current VC8 SP1 candidate environment.
The exact profile remains unproven for authored 1.06a code.

## Acceptance boundary

An exact function requires all of the following:

- an accepted target address/size in `config/functions.csv`;
- a durable authored mapping in `config/reccmp-functions.csv`;
- source selected in `config/implemented.csv`;
- a reproducible unit in `config/match-units.toml`;
- strict COFF symbol/extent validation and relocation replay;
- zero byte differences against canonical `resources/th105.exe`;
- a `matches.csv` row with command/report evidence and a simultaneous
  `matching`/`100.00` ledger update.

Build success, objdiff similarity, decompiler resemblance, and old 1.06
reports do not satisfy this boundary.

## Focused loop

```bash
python3 scripts/verify-target.py
python3 scripts/build.py --check
python3 scripts/build.py --unit UNIT --compare --json
```

Start with a small natural function. Recover calling convention, member
layout, narrow signedness, EH behavior, callees/globals, and likely object
ownership before register/branch shaping. Use the pinned compiler naturally;
never add assembly, machine-code arrays, fake behavior, padding, or ABI lies.

The existing unit format can group tightly coupled functions in one VC8 probe,
which is useful when COMDATs, templates, inline dependencies, or LTCG-shaped
ownership make TH08's one-function assumptions unsuitable.

## Relocations and boundaries

`compare-function.py` fails closed on unknown REL32/DIR32 targets, unexpected
addends, unsupported COFF ownership, and target identity changes. Add a
relocation mapping only after both target bytes and semantic ownership are
supported.

IDA extents do not define compiler boundaries. Tail chunks, jump tables,
EH funclets, thunks, and adjacent constants must be proven from control flow
and COFF records. If LTCG makes a truthful standalone object impossible,
record the blocker; do not weaken the comparator or invent a source boundary.

## Cross-version hypothesis migration

Retained 1.06 source and raw-byte identity can accelerate selection, but neither
is authority for 1.06a. The accepted first wave used this sequence:

1. intersect old authored/source hypotheses with unique raw-identical 1.06a
   candidate spans;
2. reconcile the current candidate and semantics;
3. compile the natural retained C/C++ with the pinned VC8 profile;
4. supply only current-target-backed relocation mappings; and
5. accept the function only after the canonical comparator reports zero
   differences and a cold unit replay succeeds.

Do not translate REL32 destinations by address delta alone. During the first
wave, a delta-derived target for the second `load_spell_data` loader produced a
real mismatch; current IDA disassembly identified `0x00434300`, which made the
source comparison exact. Treat that failure mode as a general rule for moved
callees.

### Structural-fingerprint migration

When raw identity no longer survives a patch, retained exact source can still
provide a safe *ranking* signal without weakening acceptance. Compile the
retained source with the pinned VC8 profile, disassemble both the COFF function
and current 1.06a candidates, and normalize only relocation/address-sensitive
operands (for example branch destinations and large absolute immediates). Rank
candidates by instruction/operand shape, then return to the normal bounded
function loop. A structural score is never a mapping or exact-match claim.

The first target-backed use of this method recovered seven additional authored
functions / 1,069 bytes: `0x00412A20`, `0x004284C0`, `0x0042B2F0`,
`0x0042B460`, `0x0045DBA0`, `0x00493D40`, and `0x0053CDF0`. For every one,
current-target call destinations were reconciled from the 1.06a instruction
stream and IDA call graph before the canonical comparator was run; all seven
then reached zero differences under fresh VC8 builds.

Normalized signatures are intentionally non-unique for template and clone
families. The roster object-manager spawn bodies and manager-base constructors,
for example, produce multiple equally strong structural candidates. Do not
break such ties by address order or old-version deltas. Use class-specific
xrefs, vtables/RTTI, neighboring recovered anchors, and current relocation
semantics to establish identity, then require the same canonical zero-difference
comparison.

A structural size difference can also expose a stale historical boundary rather
than changed authored logic. `BattleController::dispatch_battle_state_frame`
ranked as 529 old bytes versus a 535-byte current IDA body. Fresh VC8 output
matched all 535 current bytes exactly: the old ledger had stopped after the SEH
`pop ecx` and omitted `pop edi; pop esi; add esp, 0x10; ret`. Inspect the COFF
section tail and current control-flow terminator before editing source merely to
explain a size delta. Keep adjacent compiler-owned switch tables outside the
function body when current IDA/COFF evidence places them after the return.

Do not validate a BSS/global DIR32 destination by reading bytes beyond a PE
section's initialized raw data and treating file padding as the variable's
initial value. For globals, establish address identity from current semantics
and xrefs, and use a relocation validation mode appropriate to the target's
actual storage. If the existing comparator cannot represent that evidence
without pretending padding is data, leave the candidate blocked.

The comparator's `symbol_base` identifies a COFF symbol and need not equal the
durable semantic name in `reccmp-functions.csv`. This is useful when retained
source still carries an old address suffix or when a class-qualified compiled
symbol has a cleaner durable name.

## Shared changes

After any shared layout/header/flag/object-graph/relocation change, rebuild
every affected accepted unit. Aggregate totals require:

```bash
python3 scripts/verify-exact-units.py --all
```

The replay is cold and sequential by default so stale or concurrent build
products cannot support a published exact total.

For shared runtime globals whose PE storage is genuinely uninitialized or whose
file bytes are not meaningful evidence, use `validation=address` only after
current-target semantics establish the address identity independently. The
`BattleController::run_active_simulation_frame` recovery is the reference case:
IDA names `0x006FBCB4` as `Block`, numerous current battle-controller xrefs use
that address as the same `BattlePhaseBlock *`, and the 42-byte VC8 function then
compares exactly after resolving that DIR32 address. This validates an address;
it does not claim that file padding proves the global's initial contents.

A stale historical boundary can sometimes be disproved without source surgery by
triangulating all three lengths: old ledger, retained VC8 COMDAT tail, and
current IDA function boundary. `BattleController::initialize_round_state` is the
reference case: the old ledger claimed 299 bytes, while both the retained VC8
COMDAT tail and current 1.06a IDA body are 306 bytes. After current REL32 and
DIR32 identities were reconciled, all 306 bytes compared exactly. When the
object tail and current control-flow boundary agree, prefer correcting the stale
ledger span over editing already-matching C++ to reproduce an artificial cut.

Compiler-profile fidelity is part of semantic reconstruction, not a byte-forcing
knob. `configure_session_input_slots` is a reference case: compiling the natural
retained C++ with `/GS-` removed the current SEH prologue and produced a 223-byte
body, while the retained unit metadata required `/GS`; recompiling with the
correct `enable_gs = true` profile produced the current 238-byte body exactly.
Before reshaping C++, replay the historically supported profile and explain any
SEH/security-cookie structure from current IDA evidence.

When a retained function embeds several old-version absolute globals, reconcile
each use from the current instruction stream before editing the source.
`initialize_battle_fighter_pair` moved a coherent battle-global cluster; current
IDA established the fighter context, shared state, effect/renderer/reset/input
pointers, pair-state scalar, and 0x1400-byte stage-surface array independently.
Updating only those semantic global identities left the natural C++ unchanged
and fresh VC8 output matched all 279 bytes. Do not derive such clusters from a
single address delta.

`validation=address` still records canonical destination bytes in
`reccmp-relocations.csv`; the field is not an arbitrary placeholder. This caught
a bad provisional deque-destructor row while recovering
`configure_session_input_slots`. Use the actual current target bytes at the
validated destination even when semantic address identity, rather than literal
contents, is the reason the relocation is accepted.

Current PE virtual-tail bytes are modeled as Windows-loader zero-fill, not as
raw file padding. This matters for address-validated BSS globals such as
`g_battle_transition_mode` at `0x006FA88F`: current IDA semantics establish the
address identity, while `target_bytes()` verifies that the address lies in the
mapped section's virtual tail and therefore has the loader-defined zero initial
byte. Never substitute unrelated bytes beyond the section's initialized raw
extent.

A VC8 COMDAT can contain function-local jump-table data after the callable body.
`BattleController::dispatch_round_phase_34` compares exactly for its 602-byte
current IDA control-flow body even though the compiled `.text` section tail is
632 bytes. The extra tail belongs to local switch data resolved through same-COMDAT
DIR32 relocations; it is not permission to enlarge the function boundary.
Conversely, `ScenarioTransitionView::dispatch_owned_string_458e80` demonstrates
a genuinely stale old boundary: the historical ledger kept 127 bytes, while
current IDA control flow and fresh VC8 output both end at 130 bytes and all 130
bytes compare exactly. Use control-flow terminators plus COFF ownership to tell
these cases apart.

One C++ container object can legitimately generate several DIR32 references to
one global symbol with different addends. `resolve_scenario_event_name` is the
reference case: current IDA identifies the `std::map<int, String28>` object at
`0x006FCF70`, while generated code addresses both the object/sentinel at addend
0 and its head pointer at addend 4. Record one address-validated COFF symbol with
an explicit `0;4` addend allowlist rather than inventing separate globals for
individual fields. Fresh VC8 output then matches the full current 209-byte body;
the old 203-byte ledger boundary was stale.

A current-target global migration should be tested across every sibling function
that shares the affected inline accessors before the mapping is treated as
stable. `BattleControllerSetup.cpp` is the reference case: current IDA tied the
retained setup globals to the 1.06a fighter context, setup state, effect sink,
object manager, info manager, match identifier, round byte, and BGM format
string. Updating those semantic identities made both
`initialize_or_transition_46fe80` (479 bytes) and `prepare_match_roster_470060`
(337 bytes) compile exactly from one `/GS` object. The accepted addresses are
also mirrored into `config/known-globals.csv` so later agents need not rediscover
the same cluster from magic constants.

Normalized structural equality is insufficient to disambiguate clone families.
The roster object-manager spawn family contains fifteen current 237-byte bodies
with the same normalized instruction structure. Each identity was therefore
established by walking the current spawn's first allocator callee into its
object-pool allocator and observing the concrete vtable written after
`CharacterObject_ctor`:

| current spawn | allocator core | current class vtable |
| --- | --- | --- |
| `0x004938D0` | `0x00493340` | `ReimuObject` |
| `0x004B9DB0` | `0x004B9920` | `MarisaObject` |
| `0x004DF2C0` | `0x004DEE40` | `SakuyaObject` |
| `0x004FAAD0` | `0x004FA630` | `AliceObject` |
| `0x0051ED70` | `0x0051E8F0` | `PatchouliObject` |
| `0x0053B1C0` | `0x0053ACB0` | `YoumuObject` |
| `0x00555E80` | `0x00555A00` | `RemiliaObject` |
| `0x0056DCB0` | `0x0056D6E0` | `YuyukoObject` |
| `0x0058BF80` | `0x0058B990` | `YukariObject` |
| `0x005AEB10` | `0x005AE670` | `SuikaObject` |
| `0x005D2A80` | `0x005D25C0` | `UdongeObject` |
| `0x005F78C0` | `0x005F7440` | `KomachiObject` |
| `0x00618470` | `0x00617DF0` | `AyaObject` |
| `0x00631140` | `0x00630CA0` | `IkuObject` |
| `0x0064B580` | `0x0064B070` | `TenshiObject` |

That evidence safely fans the retained shared `RosterObjectSpawns.cpp` source
out to fourteen current functions, all of which fresh-compile to 237/237 exact.
Sakuya is deliberately excluded from that exact wave: its current identity is
proved by `??_7SakuyaObject@@6B@`, but the separate
`SakuyaObjectSpawn.cpp` fresh object still mismatches at function offset `0x0D`.
Identity, source presence, and exactness remain separate states even inside a
clone family.

Template-family filtering must happen before clone promotion. The current 103-byte
`TObjectManagerBase<..., ...>` constructor signature appears in twenty structural
clones, but current IDA vtable writes show that five instantiate effect/UI manager
types (`CSelectObject`, `WeatherEffectObject`, `EffectObject`,
`SystemEffectObject`, `InfoEffectObject`) rather than roster character managers.
The remaining fifteen explicitly write
`TObjectManagerBase<V<Class>Object,VCharacterObject>` vtables and each calls its
class-specific `CHandleManagerEx<ClassObject>` constructor. With `/GS` restored,
all fifteen roster specializations fresh-compile to 103/103 exact. Structural
shape alone would have over-promoted five unrelated template instantiations.

## Whole-corpus retained-source ranking

The retained 1.06 tree contains more useful source hypotheses than the old
match-unit graph recorded. `scripts/rank_retained_exact.py` turns that corpus
into a repeatable 1.06a work queue without weakening exact acceptance. It
attests the canonical target, selects historical `matching` `.cpp` rows,
compiles each retained source with the pinned VC8 probe under both `/GS-` and
`/GS`, extracts the requested COFF symbol, ranks current non-excluded candidates
by normalized GNU-objdump instruction shape, and for same-size candidates also
reports raw byte mismatches with COFF relocation fields masked. Generated
objects and reports stay under `.analysis/`.

A focused replay looks like:

```bash
python3 scripts/rank_retained_exact.py \
  --only-unconfigured \
  --name build_oriented_box_and_descriptor \
  --reuse-cache
```

The pre-1.06a historical checkpoint used by default contains 152 old exact
`.cpp` hypotheses that were absent from its match-unit graph; the migration
survey could uniquely extract 147 of those COFF symbols. The first tracked
migration wave raised the accepted 1.06a set from 100 functions / 13,487 bytes
to 205 functions / 28,219 bytes. This is still a candidate queue only. Every promotion still requires a current boundary/semantic audit,
current-target relocation reconciliation, a tracked match unit, and canonical
zero-difference replay.

Relocation-masked equality is deliberately *not* identity proof. The retained
`CFileReader::read` body ranked a current 35-byte forwarding clone with zero
non-relocation differences, but IDA showed that candidate called `WriteFile`.
Walking current `ReadFile` IAT xrefs identified `0x0040CED0` instead, which then
compiled 35/35 exact after the `ReadFile` IAT was allowlisted. Use this as the
reference failure mode whenever tiny wrappers or template/clone families tie.

The same survey exposed useful linker addends. In the stage-geometry helpers,
the retained `stage_surface_heights` symbol appears with addend `0x13FC`.
Current IDA resolves that address to `0x006FBC94`, exactly `0x006FA898 +
0x13FC`, or element `0x4FF` of the already-verified 0x500-float array. Record
such addends on one semantic relocation symbol instead of inventing a second
global.


Caller-side width is part of reconstruction. `is_y_at_or_below_stage_surface`
remains an independently exact `int`-returning helper, but the current
`update_common_fighter_state_window` tests only `AL`. Expressing the narrowing
at that call site and replacing its stale 1.06 input-gate absolute with the
verified current `g_battle_input_gate` made the full 339-byte caller exact.
Changing the shared callee's return type would have been an ABI guess, not a
valid code-generation fix.

Address validation can also express one polymorphic object through multiple
source-level narrow views. Current exact UI code uses `0x006FA21C` as a
`RenderModeManager`, while exact shared battle-phase code uses the same object
as a phase service. Both identities are supported by independent current xrefs;
there is no need to invent separate globals merely because the source views
differ.

Data-layout failures should be corrected at the semantic base, not hidden with
relocation addends. The DirectSound create-buffer recovery initially modeled
`0x0070385C` as `DirectSoundGlobals` and failed canonical comparison: that
address is the `direct_sound` field. Current initialization xrefs establish the
object at `0x00703858`, with fields at `+0/+4/+8`. Re-basing the semantic object
and allowing the real `+4` field relocation made `create_secondary_buffer8`
110/110 exact. Its Japanese error text is source-owned data, so it was restored
to the canonical Shift-JIS bytes and literal-validated rather than masked by
address validation.

A normalized structural tie can be accepted only after an independent identity
chain closes it. The 367-byte Yukari mirrored-command gate ties other clone
shapes, but its sole current fighter dispatcher, nearby exact Yukari manager/
spawn anchors, and five resolved calls to already-established gate/phase/stage
helpers identify `0x0058C170`; fresh VC8 then matches 367/367.

Standalone VC8 differences that survive semantic/layout correction remain
valid LTCG blockers. Examples from this wave include the shared tail chunk
entered by `0x0045E500`, two-byte EAX/EDX allocation differences in the roster
release helper, and the remaining CEffectSprite constructor store scheduling.
Do not respond to these with register coercion, inline assembly, raw bytes, or
padding; move to another candidate until natural C++ or stronger TU/LTCG
evidence explains them.

Authored ownership is a separate acceptance dimension from code-byte identity.
The retained `create_collision_list_node` implementation structurally ranks
`0x00421F30` with zero non-relocation mismatches, but that current helper has
dozen-scale cross-subsystem container callers and no class-specific ownership
chain yet. It therefore remains origin-review pending. The neighboring
`create_collision_list_sentinel` is different: exact `initialize_collision_list`
stores the result from `0x00435E50` as its list sentinel, and accepted roster
manager units independently reference the same helper. That current identity
chain plus a fresh 26/26 compare is sufficient for authored promotion. Never
turn a comparator success into an authored-origin claim without independent
ownership evidence.

A target-proved aggregate global may legitimately accumulate additional field
addends as sibling authored functions are recovered. The DirectSound base at
`0x00703858` was first established by create-buffer code using the `+4` device
field. `shutdown_direct_sound` then independently releases and zeros listener
`+8`, primary buffer `+0`, and device `+4`, and fresh VC8 matches all 82 bytes.
Extend one semantic relocation symbol to `0;4;8`; do not split fields into fake
globals merely to satisfy DIR32 comparison.

RDATA adjacency is not type identity. The accepted `ResultList` vtable starts at
`0x006C2058`, but `CMenuResult::update` is referenced from a separate table at
`0x006C2070`. Current `CMenuResult` destruction explicitly writes the latter
vtable, whose `+8` slot is `0x00447560`; only after that class chain was closed
was the zero-difference 43-byte update wrapper promoted.
Input accessor clusters are a productive case for semantic global migration.
The retained `InputSelection.cpp` and `Input.cpp` bodies already had the correct
VC8 instruction shapes, but their 1.06 magic absolutes pointed at stale storage.
Current 1.06a disassembly and accepted callers establish player records
`0x006FBF20` (stride `0x33C`), source/pointer tables `0x006FBD38/0x006FBD3C`,
session option `0x006FBD44`, network pointer `0x006FBD5C`, player2 storage
`0x006FBDD0`, and combined menu input `0x006FCF80`. Express these as extern
semantic globals in C++; the compiler emits ordinary DIR32 relocations and all
ten accessors compare exact. The counter getter relocates the combined-input
symbol with addend `0x38`, preserving one object identity instead of inventing a
field global. This is preferable to carrying target-specific integer addresses
inside source bodies.
Normalized wrapper ties can be solved by the destination body rather than the
wrapper bytes. `0x0046AF90` and `0x0046AFA0` are both eleven-byte `mov ecx,
[global]; jmp rel32` wrappers and therefore tie under relocation-normalized
ranking. Current 1.06a disassembly resolves them: the first jumps to LTCG entry
`0x00464630`, a five-pass fighter/owned-object callback body, while the second
jumps to `0x00464780`, a three-pass position/status/timer body. Mapping the
source-level callees to those observed internal entries and replacing the stale
phase-context absolute with `g_fighter_phase_context` produces 11/11 exact for
both. An internal LTCG entry is a truthful relocation destination; it need not
be promoted to a standalone IDA function to be used as evidence.

The neighboring 51-byte post-update wrapper demonstrates the same semantic
global migration at larger scale. Its control flow already matched; the only
real changes were current `g_info_manager`, current shared battle-setup-state
identity, and current helper destinations `0x00426BB0/0x00426DF0`. The natural
C++ source then compares 51/51 exact.
A tiny destructor is a good example of why normalized similarity still needs
class identity. Retained `CFileReader::~CFileReader` ranked a 21-byte
`CBitmapData` destructor at `0x00419FD0` surprisingly high. Instead of tuning
the scanner toward that false positive, extract the fresh VC8 destructor and
scan the canonical PE while masking only its two DIR32 fields (vtable and
CloseHandle IAT). Exactly two bodies match: the writer clone at `0x00407BF0` and
the reader clone at `0x0040CEB0`. Their vtables disambiguate them: the first
leads to WriteFile, the second to the already accepted CFileReader methods.

Boundary correction can require adding a candidate the initial IDA export
missed. `0x0040CEB0..0x0040CEC4` is surrounded on both sides by `INT3` padding
and followed by accepted `CFileReader::read @ 0x0040CED0`, while IDA incorrectly
attributes the address to a remote multi-chunk function. Add the observed
21-byte candidate to `functions.csv` first so the normal ledger gate remains in
force; only then run canonical comparison and promote it. This first correction changed the tracked inventory from 4,001 to 4,002
candidates. Later target-backed source-level phase entries at `0x00464630` and
`0x00464780` raise the current corrected inventory to 4,004.

Do not inherit historical function extents when source and current code agree on
a larger body. `mt19937_next_u32` was historically recorded as 271 bytes, but
fresh VC8 emits 279 bytes and current 1.06a contains the full standard MT19937
twist/temper implementation through byte 279. The accepted boundary is therefore
279 bytes, proven by current control flow and a 279/279 canonical compare.
Imported API identity is another clean way to break a normalized clone tie.
`CriticalSectionWrapper::enter` and `leave` compile to the same eleven-byte shape
when the DIR32 call slot is masked, but current target `0x0040AC30` calls
EnterCriticalSection and `0x0040AC40` calls LeaveCriticalSection after identical
`this+4` adjustment. Record the two IAT entries with canonical raw thunk bytes
and let the ordinary comparator prove each wrapper 11/11.

A field-layout migration should be corroborated by independent current use before
changing a retained struct. `copy_session_field_6c8_if_unset` decompiles at
`0x00426160` as a guarded `+0x6C0 <- +0x6D8` copy. Its caller first obtains the
object through the exact network-session getter and then repeats that same guarded
copy inline on another path. Moving the two retained fields by `+0x10` is therefore
a target-backed layout correction, not source shaping; fresh VC8 becomes 22/22
exact without any control-flow change.

When historical evidence says “exact” but its function size is shorter than the
fresh section tail, re-establish the current boundary. CMenuResult render and
destructor are both three bytes longer in 1.06a than their old ledger rows. Their
current semantic bodies and fresh VC8 tails agree at 270 and 256 bytes respectively,
and the canonical comparator matches those complete extents.

The same stale-boundary pattern extends beyond one UI class. `CSelectScenario::~CSelectScenario` was historically 271 bytes but its current `/GS` VC8 section tail and target body are both 277 bytes; `CMenuSelect::update_player_assignment` was historically 400 but current/fresh is 406. In both cases the retained source behavior already matches current IDA semantics and the added bytes merely complete the final epilogue/security-check sequence. When a high-gap structural candidate differs only in size, inspect the full COFF section tail before touching source.

An undefined COFF data symbol can still have a truthful address identity without weakening import checks. `MenuResult.cpp` and `SelectScenario.cpp` only declare the source-owned `_title_color_vtable_anchor`; the anchor itself is independently exact-backed at `0x006C0624`. Their probe objects therefore use a separate address-validated relocation view of that same symbol instead of pretending the undefined symbol is an import or copying bytes into the TU. Keep literal validation on the defining TU and use address validation only for independently established external views.
Relocation-free loops are useful boundary authorities because there is no target
address bookkeeping to hide a mismatch. The two fighter reset functions at
`0x0046AFF0` and `0x0046B080` compare 130/130 and 222/222 directly, while their
historical body-set rows were three bytes shorter. Current IDA field-offset
sequences and the exact two-fighter loop establish the complete extents.

When an old row already says a longer contiguous span was exact, treat that span
as a strong boundary hypothesis rather than reusing the shorter body-set size.
`consume_counter_484_steps` is 149 bytes rather than the old 138-byte body row,
and `advance_menu_item_wave` is 147 rather than 137. Fresh VC8 section tails,
current control flow, and canonical comparison all agree on those complete
lengths.

Historical row size can lag even its own earlier evidence. Both fighter reset rows recorded 127/219 bytes while their old evidence already cited exact 130/222-byte contiguous spans; `consume_counter_484_steps` similarly recorded 138 while citing 149, and `advance_menu_item_wave` recorded 137 while citing 147. Current IDA semantics plus fresh VC8 section tails reproduce 130/222/149/147 exactly. When migrating retained exact source, parse the evidence text and object tail as well as the CSV size column.

Identical-code folding does not make class ownership unknowable when a current vtable names the shared address. `CFileReader` vtable `0x006C0F34` directly points its seek slot at `0x00407C50` and its scalar-deleting-destructor slot at `0x0041B890`; the neighboring slots are already accepted reader methods. `0x00407C50` may also serve a writer through ICF, but one tracked binary function can truthfully be the shared implementation used by the reader. Current SetFilePointer/CloseHandle IAT semantics plus the vtable chain allow 25/25 and 45/45 exact promotion without pretending the bodies are class-unique.
Six-byte global getters are the opposite of a useful structural clone family.
Once the immediate address is masked, every `mov eax, imm32; ret` getter is
identical, so scanner score/gap cannot establish identity. Use current callers
and returned-object field semantics instead. In 1.06a this closes game mode
`0x0043AC40 -> [0x006FBD4C]`, MatchSetup `0x0043AC50 -> 0x006FCA48`, GameConfig
`0x0043AF10 -> 0x006FC598`, and ScoreData `0x0043AF20 -> 0x006FCC98`. Expressing
those addresses as semantic extern globals keeps the C++ natural and turns each
old literal into one ordinary DIR32 relocation; all four getters then compare
6/6 exact.

An IDA tail chunk can become a first-class source-level function without editing
the IDB. The exact wrappers at `0x0046AF90/0x0046AFA0` provide unique entry edges
to `0x00464630/0x00464780`; current body semantics give the five-pass
action/owned-object phase and three-pass position/status/timer phase; fresh VC8
section tails are exactly 323 and 187 bytes. Add those target-backed entries to
the corrected inventory, let the normal ledger gate run, and accept them only
after 323/323 and 187/187 canonical comparison. This preserves fail-closed
boundary discipline while recovering code that auto-analysis stores only as
remote chunks.

IDA tail-chunk ownership can hide a complete source-level function from candidate scanners. Exact wrappers `0x0046AF90` and `0x0046AFA0` load `g_fighter_phase_context` and tail-jump to `0x00464630` and `0x00464780`. IDA attaches each destination as a wrapper chunk, but the destinations are complete RET-terminated 323-byte and 187-byte bodies. Fresh `FighterPhases.cpp` emits sections of exactly those sizes with zero non-relocation mismatches, and canonical relocation replay is 323/323 and 187/187. Add such target-backed boundaries to `functions.csv`; do not mutate IDA merely to make its function list match the tracked ledger. Candidate-ranking tools that enumerate only standalone IDA functions will miss this class of exact source.

Vtable ownership is also the preferred way to resolve scalar-deleting-destructor clone ties. Current vtables identify `CMenuResult @ 0x00447890`, `CProfileMenu @ 0x0044D6E0`, and `CEffectSprite @ 0x0041F6F0`; fresh VC8 produces exact 30/30, 30/30, and 31/31 wrappers. A structurally similar candidate is not a substitute for the class vtable edge. The `CProfileMenu` 422-byte primary destructor remains deliberately non-exact: its member offsets agree, but standalone VC8 differs in SSO free-register allocation and one member-dtor schedule, so the exact scalar wrapper does not justify forcing the primary destructor.

Small retained absolute-address getters are best migrated as semantic globals, not rewritten constants. Current accepted callers establish `g_game_mode`, `g_match_setup`, `g_game_config`, and `g_score_data`; replacing the stale 1.06 absolutes with extern objects leaves ordinary DIR32 relocations and makes all four six-byte getters exact.

### Lifecycle roots and class-owned template families

A header-only declaration can still seed exact source if current target evidence first fixes the C++ lifetime and the touched layout. `Alice_construct @ 0x004FAC40` was reconstructed with a narrow `Alice : Character` view containing only the proven `+0x138` float and `+0x658` manager pointer. The source performs ordinary base construction, assigns `-6.0f`, and allocates `new AliceObjectManager(this)`. VC8 naturally emits the target `/GS`, EH unwind, derived-vptr publication, allocation cleanup, and 138-byte body. Use this pattern to open large lifecycle/event families; do not paste decompiler output or invent unused fields.

For template clone families, byte equality is not class identity. The fifteen `CharacterObjectManager<Fighter,FighterObject>` constructors are accepted because each current specialization writes its own target-backed primary/secondary vtables, calls its class-specific exact `TObjectManagerBase` ctor, stores the fighter owner at `+0x64`, and preallocates 256 objects. Each primary vtable's first slot also names the corresponding 30-byte scalar-deleting destructor. One natural template TU then compares all 30 functions exactly. Reuse vtable ownership to batch a family only after every specialization's current address is independently tied to its class.

### Generated VC8 COMDATs as origin evidence

Authored recovery can reveal compiler-owned template islands beside the authored function itself. `PatGroup` is the reference case: natural `/GS` source with a real checked `std::vector<PatRecord88>` makes the user constructor/destructor compare 106/106 and 128/128 exact, while the same compile emits `vector<PatRecord88>::erase` and `_Tidy` COMDATs whose non-relocation bytes uniquely match current `0x00461320` and `0x0045FC30`. Those current candidates must therefore leave the authored denominator rather than being renamed as game methods.

`config/vc8-generated-origin-anchors.toml` and `scripts/function-origins.py --check` make that conclusion replayable. The rule pins the target and compiler SHA-256, recompiles the tracked source with the declared `/GS` profile, normally requires the generated COMDAT section size to equal the candidate boundary, accepts only supported 4-byte COFF link relocations, enforces minimum exact non-relocation coverage, and requires the masked fingerprint to be unique across the full corrected inventory. A manifest may allow a strictly bounded alignment tail: the PAT vector copy constructor is the reference case, with exactly one trailing `0xCC`, no tail relocation, and target `0xCC` padding immediately after the 249-byte candidate. This exception is origin evidence only and never relaxes canonical function-byte comparison. Use this route for future checked-STL/template islands instead of explicit-address exclusions with prose-only evidence.


The same probe also proves the current 249-byte checked-vector copy constructor at `0x00461420` and 123-byte `std::_Construct<PatGroup>` at `0x00461940` are compiler-generated. The copy constructor's generated section is 250 bytes because VC8 emits one terminal `INT3` alignment byte; its first 249 relocation-masked bytes are exact, and the target is followed by `INT3` padding. `_Insert_n @ 0x00461640` and `_Assign_n @ 0x00461A30` are semantically the corresponding VC8 template machinery, but their generated bytes still depend on the incomplete nested `PatRecord88` model, so they remain review-pending rather than being excluded on prose alone.

The neighboring roster-manager destructor family illustrates a separate batch rule. Template identity comes from the current class vtable and class-specific member destructor edges, not from normalized clone order. Fourteen 100-byte `TObjectManagerBase<ClassObject,CharacterObject>` destructors compile exact after each current SEH handler and `CHandleManagerEx<ClassObject>` destructor destination is independently reconciled. Apparent fixed address offsets are not evidence: the comparator caught provisional handler/member-dtor mappings before promotion.

### Sparse switch bodies with trailing compiler tables

`Alice_handle_event_bridge @ 0x0050ED00` demonstrates that exact switch recovery is more than matching case bodies. VC8 emits a 1075-byte executable body followed in the same COMDAT by a 19-entry jump-pointer table at body `+0x434` and a 121-byte byte-index table at `+0x480`. The canonical comparator intentionally uses the accepted ledger boundary for function bytes and models same-section DIR32 references as `function_address + local_symbol_offset`; the trailing tables remain separate compiler metadata, but their offsets and index bytes should still be audited when recovering the source topology.

Current target evidence forced several natural C++ corrections before all 1075 body bytes matched: the return contract is a byte rather than the historical `bool` hypothesis; action/sequence dispatch must be represented as actual virtual slots `+0x08/+0x0C`; the identical case-1 and case-11 shared-state finalize statements should appear independently so VC8 itself folds case 11 into a backward jump; and case 2 is naturally written as a nested `counter <= 0` timer block. Most importantly, the source has no `default:` label: unknown events use a function-level `return 1` after the switch. That produces the target 19 destinations and exact 121-byte index table. A tempting explicit `case 10` variant made the first 1075 bytes look exact but emitted a twentieth jump-table slot and shifted the index table by four bytes; reject such near-matches rather than treating compiler metadata as irrelevant.

### Nested PAT value lifetimes

`PatRecord88_construct @ 0x00460F90` plus `PatRecord88_destroy @ 0x0045FFD0` are a useful bridge between authored lifetime code and generated checked-STL helpers. Current IDA proves the `FrameData` base plus nested `vector<PatRaw16>`/`vector<PatRaw16*>` ownership, and natural `/GS` C++ matches 300/300 for construction and 515/515 for destruction. The base constructor is not six independent assignments: target stores prove `memset(&raw_04, 0, 0x14)`, then the byte `tag_14 = 0`, then `optional_mode_payload_18 = 0`. A 0x18-byte memset is semantically tempting but moves the +0x18 write before the byte store and fails exact comparison. Destruction similarly needs the observed unsigned-index traversal and explicit null guards; an iterator loop or unconditional delete changes checked-STL scheduling. Recompile a minimal tracked nested-vector probe to classify adjacent template machinery: the 88-byte `vector<PatRaw16>::erase @ 0x0045FBD0` has an inventory-unique relocation-masked fingerprint under the SHA-pinned VC8 compiler and is excluded by the generated-origin rule. Keep authored lifetime exactness and compiler-helper origin as separate evidence paths.

### Semantic sign-bit predicates and VC8 AND/TEST folding

`test_aabb_against_descriptor_shape @ 0x0046B7B0` demonstrates a narrow acceptable code-generation correction. The target computes four signed separating-axis overlap terms, ANDs them together, then performs `test reg, reg; js`. A direct `overlap >= 0` spelling let standalone VC8 fold the last overlap expression into a different TEST operand even though the result was equivalent. Expressing the same real condition as `(static_cast<unsigned>(overlap) & 0x80000000u) == 0` preserves the stored 32-bit aggregate, causes the natural VC8 AND chain and `test/js`, and makes all 248 bytes exact. This is not license to test arbitrary bits for code shape: use it only when current semantics independently prove that the sign bit of the computed value is the branch predicate.

### Wider historical source hypothesis queues

After the historical exact-source pool is exhausted, `scripts/rank_retained_exact.py` accepts repeatable `--historical-status` filters such as `implemented` and `compiles`. This only widens the archaeology queue; it never upgrades evidence. Current candidate identity, boundary/ABI review, target-backed relocation reconciliation, and canonical zero-difference comparison remain mandatory before authored promotion.
### Zero-body-diff resource loaders

A retained function with zero non-relocation differences is still only a candidate until current service and data identities are reconciled. `load_indexed_character_wave_resources @ 0x0045F680` is the reference: current IDA proves `record_key_330 -> 0x0043BF80`, the NUL-terminated `data/se/%s/%03d.wav` literal at `0x006C2B20`, `wsprintfA`, wave-service object `0x00702288`, loader `0x00401AF0`, and Fighter handle array `+0x164`. The natural retained `/GS` C++ then compares 132/132 exact without source changes. Prefer this relocation-reconciliation path over source shaping whenever the non-relocation body is already identical.
