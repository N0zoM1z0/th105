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

Tracking CSV row width is part of the acceptance boundary. `scripts/validate-tracking.py` now rejects both extra and missing CSV fields instead of silently accepting `csv.DictReader`'s `None` overflow key. The concrete failure was an older `functions.csv` signature containing an unquoted comma: a standard DictWriter round-trip could then truncate the inventory after the malformed row. Keep signatures/notes CSV-quoted and run tracking validation before any generated origin write; never mass-rewrite a tracking ledger after a parse-width warning.

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

That evidence safely fans the retained shared `RosterObjectSpawns.cpp` source out to fourteen current functions, all of which fresh-compile to 237/237 exact. Sakuya is now the fifteenth exact member through its separate `SakuyaObjectSpawn.cpp`: the old source introduced `owner_field_160` and `child_refs` locals, which moved the parent-argument load ahead of fixing the newly acquired object in ESI and caused the first mismatch at function offset `0x0D`. Restoring direct `owner_field(owner,0x160)`, `original_parent->child_refs_350.push_back(parent)`, and the common related-object field order preserves the same game semantics while making ordinary VC8 reproduce all 237 bytes. Class identity still comes from the current Sakuya allocator/vtable chain; zero-difference clone shape by itself is not enough.

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

The same narrow-lifetime method closes a larger constructor family. Twelve standard roster fighters -- Reimu, Marisa, Sakuya, Patchouli, Remilia, Yuyuko, Yukari, Suika, Udonge, Komachi, Aya, and Tenshi -- each compile to the current 126-byte constructor from only `Character(init_arg)`, the derived class vptr, `new 0x68` class-specific ObjectManager construction, and publication at `+0x658`. Iku adds the current-backed `field_138 = -6.0f` assignment and is 138/138, matching the already-exact Alice pattern. The thirteen new constructors all push a linker-folded handler at `0x006BBCE3`, but acceptance maps every current RTTI-owned class vtable and every already-exact 123-byte ObjectManager ctor separately. Do not use the shared EH address as class identity. Youmu is not part of this simple family: current `0x0053B330` has a non-trivial member at `+0x7D0`, its EH cleanup reaches `0x00448DE0`, and `+0x7D4..+0x7E0` are explicitly zeroed; recover that member before attempting the 159-byte ctor.

A header-only declaration can still seed exact source if current target evidence first fixes the C++ lifetime and the touched layout. `Alice_construct @ 0x004FAC40` was reconstructed with a narrow `Alice : Character` view containing only the proven `+0x138` float and `+0x658` manager pointer. The source performs ordinary base construction, assigns `-6.0f`, and allocates `new AliceObjectManager(this)`. VC8 naturally emits the target `/GS`, EH unwind, derived-vptr publication, allocation cleanup, and 138-byte body. Use this pattern to open large lifecycle/event families; do not paste decompiler output or invent unused fields.

For template clone families, byte equality is not class identity. The fifteen `CharacterObjectManager<Fighter,FighterObject>` constructors are accepted because each current specialization writes its own target-backed primary/secondary vtables, calls its class-specific exact `TObjectManagerBase` ctor, stores the fighter owner at `+0x64`, and preallocates 256 objects. Each primary vtable's first slot also names the corresponding 30-byte scalar-deleting destructor. One natural template TU then compares all 30 functions exactly. Reuse vtable ownership to batch a family only after every specialization's current address is independently tied to its class.

A source-level scalar lifetime can be the missing evidence in a clone family even when the member itself is narrower. The fifteen roster `ObjectPool::acquire` bodies were all 519 bytes in the target while the direct source expression `generations[slot] = handle->generation` produced 514-byte fresh bodies. Current target flow first performs the checked free-list erase, then zero-extends the 16-bit generation into a 32-bit register, and only then enters checked-vector bounds. Expressing that real intermediate as `unsigned generation = handle->generation` reproduces 519/519 for all fifteen bodies. An `unsigned short` intermediate instead produces 522 bytes, so this is not a generic "add a local" trick: the width and lifetime are part of the recovered semantics. Prefer such target-backed typed lifetimes over `register`, `volatile`, dummy dependencies, inline assembly, or manual instruction shaping.

### Generated VC8 COMDATs as origin evidence

Authored recovery can reveal compiler-owned template islands beside the authored function itself. `PatGroup` is the reference case: natural `/GS` source with a real checked `std::vector<PatRecord88>` makes the user constructor/destructor compare 106/106 and 128/128 exact, while the same compile emits `vector<PatRecord88>::erase` and `_Tidy` COMDATs whose non-relocation bytes uniquely match current `0x00461320` and `0x0045FC30`. Those current candidates must therefore leave the authored denominator rather than being renamed as game methods.

`config/vc8-generated-origin-anchors.toml` and `scripts/function-origins.py --check` make that conclusion replayable. The rule pins the target and compiler SHA-256, recompiles the tracked source with the declared `/GS` profile, normally requires the generated COMDAT section size to equal the candidate boundary, accepts only supported 4-byte COFF link relocations, enforces minimum exact non-relocation coverage, and requires the masked fingerprint to be unique across the full corrected inventory. A manifest may allow a strictly bounded alignment tail: the PAT vector copy constructor is the reference case, with exactly one trailing `0xCC`, no tail relocation, and target `0xCC` padding immediately after the 249-byte candidate. This exception is origin evidence only and never relaxes canonical function-byte comparison. Use this route for future checked-STL/template islands instead of explicit-address exclusions with prose-only evidence.

#### Mine generated COMDATs from already-exact source TUs

Once many authored units are exact, their fresh COFF objects become a trustworthy **discovery corpus** for adjacent compiler-owned code. Scan emitted `std` COMDAT symbols, mask only supported 4-byte DIR32/REL32 fields, require useful non-relocation coverage, and compare each fingerprint against the complete corrected target inventory. The scan is only prioritization: do not write origin rows from cached objects. Convert every accepted source family into a tracked `vc8-generated-*-std-origin-anchors.toml` manifest whose `source`, `/GS` profile, target SHA and compiler SHA are pinned, then let `function-origins.py` recompile that source and recompute the whole hit set.

The current large census is the reference scale: 15 already-exact source TUs regenerate standard-library fingerprints covering 216 target candidates / 27,039 bytes. `FixedSlotEnvelope.cpp` contributes 63 candidates / 8,358 bytes, `EffectManagerLifetime.cpp` 36 / 5,217, `CFileList.cpp` 28 / 3,452, and `BattleInputSlotConfig.cpp` 38 / 4,614; smaller PAT/Profile/Replay/roster/input sources close the rest. Clone-identical helpers remain one equivalence group only when the regenerated fingerprint's **complete** 4,010-candidate hit set is exactly the manifest address set. A review-only scan is useful for discovery but is never promotion evidence: the same fingerprint must be replayed across the full inventory so already-classified spans cannot be silently omitted. An extra hit, missing hit, changed relocation form, insufficient coverage, unbounded section tail, source/compiler hash drift, or overlap with an authored match fails closed. This is how a retained application-looking name such as a 57-byte `SelectIntVector16::clear` is rejected when the same bytes are proven to be a checked-vector COMDAT clone.


A second generated-origin lane covers the current spell tree. Tracked `scripts/probes/spell_tree.cpp` emits six `SpellRecordView` `std::_Tree` COMDATs matching `_Lrotate @ 0x0042C9E0`, `_Max @ 0x0042CA30`, `_Rrotate @ 0x0042CA70`, `const_iterator::_Dec @ 0x004329B0`, `find @ 0x00432C40`, and `insert @ 0x00433890` (615 bytes total). `config/vc8-generated-spell-tree-origin-anchors.toml` applies the same SHA-pinned compiler, relocation-form, coverage, boundary, and full-inventory uniqueness checks. Their authored parser/lookup callers do not make the templates authored; compiler ownership is established by the regenerated COMDATs themselves.

The same probe also proves the current 249-byte checked-vector copy constructor at `0x00461420` and 123-byte `std::_Construct<PatGroup>` at `0x00461940` are compiler-generated. The copy constructor's generated section is 250 bytes because VC8 emits one terminal `INT3` alignment byte; its first 249 relocation-masked bytes are exact, and the target is followed by `INT3` padding. `_Insert_n @ 0x00461640` and `_Assign_n @ 0x00461A30` are semantically the corresponding VC8 template machinery, but their generated bytes still depend on the incomplete nested `PatRecord88` model, so they remain review-pending rather than being excluded on prose alone.

The neighboring roster-manager destructor family illustrates a separate batch rule. Template identity comes from the current class vtable and class-specific member destructor edges, not from normalized clone order. Fourteen 100-byte `TObjectManagerBase<ClassObject,CharacterObject>` destructors compile exact after each current SEH handler and `CHandleManagerEx<ClassObject>` destructor destination is independently reconciled. Apparent fixed address offsets are not evidence: the comparator caught provisional handler/member-dtor mappings before promotion.

The same rule now covers `CHandleManagerEx<T>` itself at larger scale. Sixteen current specializations are independently class-disambiguated, then one `/GS` template TU replays 48 special members exactly: ctor 130, dtor 263, scalar deleting wrapper 30 for every type. Current linker folding sends every ctor EH record to `0x006BC551` and every dtor EH record to `0x006BBB3C`; never use those shared handlers to infer specialization identity. Two ordinary source details control the exact body: clear `generation_counter_30` in the ctor body after the nontrivial critical-section member has constructed, and cache `slots_04[index]` in one local before null-check/delete so checked `operator[]` is evaluated once. Repeating the indexed expression emits a second bounds-check path and produces 294 bytes instead of 263.


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

### Implicit copy construction as compiler-origin evidence

`PatRecord88` demonstrates why explicit padding fields are dangerous during both matching and origin review. Current `0x00460C90` calls an out-of-line `FrameData` copy constructor, copies the real scalar members, then copy-constructs the three checked vectors. A pinned VC8 implicit derived copy constructor initially failed because the contract used raw byte-array members and inlined the base copy. Once current disassembly established the member widths, the two 2-byte holes at +0x3A/+0x4A were left as natural alignment gaps and `FrameData(FrameData const&)` was declared out-of-line. VC8 then generated a 311-byte copy constructor whose 283 non-relocation bytes match only `0x00460C90` in the corrected inventory. Classify it as `compiler_generated`; do not promote a historical “PatRecord copy helper” name to authored code.

The same rule applies to `vector<PatRaw16>::operator= @ 0x00460AD0`: a tracked nested-vector probe generates the exact 317-byte section, with 289 non-relocation bytes and a unique current fingerprint. Conversely, candidate template helpers that are semantically plausible but fail exact section/fingerprint/uniqueness checks remain review-pending. A generated-COMDAT rule is intentionally evidence-hungry; never exclude by STL-looking decompilation alone.

### Unused-this member ABI recovery

A decompiler may show a source-level member as a free/stdcall-like function when the body never reads ECX. Do not repair that prototype from a single caller or to obtain a desired `mov ecx`. The spell CSV parser lane provides a target-backed test: `load_spell_csv_via_325b0 @ 0x00434300` and `load_spell_csv_via_32e20 @ 0x00434A10` both restore the owning `SpellDataOwner*` into ECX immediately before their parser calls, and independent caller `0x00434AC0` does the same before `0x004343A0`. With the parser declarations and definitions modeled as real `SpellDataOwner` members, VC8 naturally emits the missing `mov ecx, esi`, preserves ESI across the null-owner branch, and both wrappers become 148/148 and 161/161 exact. Keep the parser bodies as ordinary members even if the optimizer never consumes `this`; call-site ABI plus canonical codegen is stronger evidence than an unused-register decompiler guess.

### Generated COMDAT clone equivalence groups

Compiler-origin fingerprints are normally required to be inventory-unique. Some tiny checked-container COMDATs are legitimately ICF/clone-identical, so uniqueness must not be weakened globally. `scripts/function-origins.py` supports manifest `equivalence_group` only for explicit generated anchors: all entries in one group must have the same symbol and size, and replay requires the fingerprint's complete current-inventory hit set to equal exactly the group's listed addresses. The two 42-byte `vector<PatRaw16>` destructor clones and two 90-byte `vector<PatRaw16*>` erase clones are the reference cases. An extra unlisted hit, a missing group member, mixed symbol/size, insufficient non-relocation coverage, or unsupported relocation fails the origin rule.

### Event-bridge tail merging

The recovered character event bridges use sparse VC8 switches whose compiler-owned jump/index tables trail the source-level body boundary. Alice, Reimu, Marisa, Sakuya, Patchouli, Youmu, Remilia, Yuyuko, Suika, Udonge, Komachi, Aya, Iku, and Tenshi now all reproduce from narrow class views containing only current-target-proven Fighter/derived fields and virtual slots. Historical same-size/event-label data is useful only to seed the current address; current character-specific case values, field widths, effect/action ids, and virtual dispatch must independently close identity. Before promotion, compare the full body canonically and use current character-specific semantics to reject structural clones; same-size location seeds are not identity proof.

The family has multiple truthful source shapes, so do not force one generic switch template. Reimu/Alice/Remilia/Komachi/Suika/Aya use the dynamic `+0x730/+0x732` countdown and current second-target member helper `0x00476AD0`; Sakuya/Patchouli/Youmu/Udonge use direct shared-state setters; Yuyuko compiles exact from a result-and-break spelling. Character-specific access widths can refine the narrow view: current Suika cases prove a signed short at `+0x13E`, a word at `+0x734`, and a float at `+0x740`, while Aya independently proves the signed-short `+0x13E` sequence gate. Preserve those typed facts locally rather than speculating a common full Fighter layout.

Do not translate decompiler cross-jumps directly into source gotos. Sakuya and Marisa cases 9/50 both perform the same motion suffix after selecting different action ids. Writing that suffix in both source cases causes VC8 `/O2` to merge the duplicate tail naturally, producing the target shape where one case contains the full suffix and the other pushes its action id then jumps backward into it. Writing an explicit `goto common_motion` instead gave a different block order and a nonzero compare. This is compiler-owned deduplication, not permission to duplicate unrelated work merely to force bytes.
### Target-proved shared-success CFG shaping

`try_dispatch_flagged_gate_actions_220_224 @ 0x00493B40` is a useful counterexample to blindly avoiding every source `goto`. The retained source already had the correct gates, actions, callees, and return values; canonical comparison differed only in four short-branch displacement bytes. Current 1.06a control flow proves that action 222 owns one consume-and-return path, action 220 owns a second counter/return path, and the 223/224 branches jump into the action-220 counter check. Expressing the already-proved positive success node explicitly in ordinary C++ preserves those three lifetimes, and VC8 emits the exact 258-byte target body.

This does not weaken the no-shaping rule. Do not add a cross-edge merely because it improves bytes, and do not use dead conditions, fabricated state, register tricks, or assembly. First prove the edge and the distinct return/counter behavior from current target control flow; then choose the smallest truthful C++ topology that preserves it. Contrast this with Sakuya/Marisa event-tail deduplication, where an explicit source `goto` was *not* supported by distinct source semantics and produced the wrong block order.

### Generated list-node clone groups

Raw or relocation-masked exactness does not establish authored ownership. `0x00421F30` was deliberately left review-pending even though a retained collision-list node helper reproduced its 51-byte shape, because current xrefs show broad container use. A tracked pinned-VC8 `std::list<void*>::_Buynode` probe now emits the same 51-byte body with only the `operator new` REL32 masked. Its complete 4,004-candidate fingerprint hit set is exactly `0x004129E0` and `0x00421F30`. Record such unavoidable generated clones as one manifest `equivalence_group`; the origin validator must reject the rule if any listed clone disappears or any unlisted clone appears. Do not promote a generic node helper merely because authored wrapper source can produce identical machine code.

The same rule applies to teardown helpers reached from authored destructors. Current `0x00435EB0` is called by fourteen exact roster-manager destructors, but a minimal pinned-VC8 probe that explicitly destroys `std::list<void*>` emits a separate 72-byte `_Tidy` COMDAT whose complete body is canonical exact at that address; the actual generated `~list` is only a five-byte jump to `_Tidy`. Masking only the two operator-delete REL32 fields gives exactly two 72-byte inventory hits, `0x004023E0` and `0x00435EB0`. The first is independently used as a member-container teardown inside `CHandleManager<CWaveBuffer*>`, so the tracked origin manifest declares this exact pair as one equivalence group. Caller authorship is identity context, not ownership proof for a callee.
Iku and Tenshi add two source-shaping lessons without any assembly. Iku's cases 8 and 134 each own a distinct three-float spawn argument array; declaring both before the switch preserves their real lifetime and naturally gives VC8 the target 0x18 stack frame. Iku also proves `0x00434E10` is an unused-`this` `EventSubobject130` member: all eight current call sites keep a `+0x130` receiver in ECX, and Iku reuses that receiver across the effect and pair-setting calls. Tenshi similarly uses one member view for `0x004359D0`; case 133 inherits ECX=`this` from switch entry while case 134 reloads ECX after prior calls clobber it. Both complete bodies are exact (1553/1553 and 1412/1412). Yukari case 156 remains blocked because the target contains a redundant self-compare branch that natural standalone VC8 deletes; do not add tautological source to force it.
### Exact-caller convergence and translation-unit visibility

When historical ranking reaches a cluster of standalone/LTCG scheduling blockers, invert the search: enumerate REL32 destinations already named by canonical-exact match units and rank review-pending targets by independent exact callers. This is identity evidence, not exactness evidence, but it can expose authored helpers whose retained-source row was missing. The shared event-state family is the reference: fourteen exact roster event bridges all call `0x004272B0`, `0x004272D0`, and `0x004272F0`, alongside the already exact `0x00427290`. Their common receiver and argument ABI plus current bodies establish one narrow `SharedEventState` layout; compiling that contract reproduces the four functions at 17/17, 17/17, 17/17, and 33/33. All fourteen callers must be replayed after consolidating the shared header.

`set_shared_second_target @ 0x00476AD0` demonstrates that source visibility can reveal an original TU boundary. The truthful wrapper only forwards `(char,float)` to `SharedEventState::set_target_24_enabled_2d`. If the setter definition is present in the same TU, VC8 `/O2` inlines it and the object contains direct global+addend relocations, unlike the target. Compiling the wrapper as a separate TU with only the setter declaration visible naturally emits the target 26-byte out-of-line call. Preserve such a boundary in the match graph; do not replace it with `__declspec(noinline)`, compiler-option changes, or assembly when normal C++ TU separation explains the linked body.

The same exact-caller lane closed `EventSubobject130::set_global_pair @ 0x00434E10`. Its receiver is independently proved at Fighter `+0x130`, yet the body intentionally leaves ECX unused. Capturing exact-backed battle object manager `0x006FBCA0` as the real return value, writing its `+0x10C` field, reloading the global for `+0x110`, and returning the captured pointer reproduces all 34 bytes. A semantically meaningful value lifetime is acceptable; a local introduced only to select a register is not.
### Loader-zero UI globals and checked-list addends

`has_ui_selection_state_changed @ 0x0043B6E0` and `set_ui_selection_state_tracking @ 0x0043FFB0` show how to recover exact helpers whose globals live in the PE virtual tail rather than initialized raw data. Current IDA establishes a dword state at `0x006FD290`, byte snapshot/fade values at `0x006FD046/0x006FD047`, and a checked `std::list<UiSelectionMenu*>` object at `0x006FD288`. The executable supplies zero initialization through loader-backed virtual `.bss`; do not reject these addresses merely because the file has no initialized payload bytes there. Canonical relocation entries should therefore identify the semantic symbols while recording loader-zero provenance.

Preserve the container base and relocation addend separately. The target tracking helper reads the list sentinel pointer at `g_ui_selection_menu_stack + 4` (`0x006FD28C`), performs the two VC8 checked-iterator invalid-parameter guards, loads the final menu pointer, and tail-jumps to vslot `+0x04`. The match unit records the list symbol with addend `4`; introducing a standalone `g_ui_selection_menu_sentinel` absolute would lose the recovered object layout. With those identities, ordinary C-linkage source gives 88/88 exact, and the companion unsigned `(state - snapshot) > 0` predicate gives 24/24. Replay exact callers after moving repeated declarations into the shared header.

### One container contract, two ownership outcomes

An exact-backed STL container may support both authored wrappers and compiler-generated specializations in the same TU. `g_scenario_event_name_map @ 0x006FCF70` is already established by exact `resolve_scenario_event_name @ 0x0043BFD0` as `std::map<int,String28>`. Adding the truthful forward lookup `find(character_key)->second.c_str()` to that tracked TU makes VC8 reproduce `character_key_to_name @ 0x0043BF80` all 78/78, including checked-iterator validation and the `String28` SSO/heap branch. The same compile emits the concrete `std::map<int,String28>::find` specialization as a 105-byte relocation-free COMDAT whose raw bytes have exactly one current-inventory hit, `0x006A4D60`. Promote the wrapper as authored and exclude the specialization as generated; a common source file or caller edge does not collapse those ownership layers.

### Preserve aggregate fields with symbol+addend DIR32 mappings

When one source object is referenced both by its base and by interior fields,
do not split those fields into fake globals to satisfy the comparator.
`Menu::render_cursor @ 0x0043F9D0` uses one cursor sprite at `0x006E6958`; VC8
emits DIR32 relocations for the base and for the same COFF symbol with addends
`0x88` and `0x8C`. `compare-function.py` supports function-local
`COFF_SYMBOL+0xADDEND=ALLOWLIST_KEY` overrides, so the match unit keeps the
aggregate identity while independently attesting the two field addresses. The
helper then compiles naturally to the target 55/55 bytes.

Use literal validation when the probe object supplies the initialized bytes
being selected. Use address validation for an independently established
aggregate-field identity when the source probe does not own a corresponding
initialized object payload. In both cases, keep the allowlist narrow to the
observed addends and verify the canonical target bytes/address before exact
acceptance. This mechanism is not permission to use arbitrary addends as byte
patches; the object layout and each interior reference must come from current
target semantics.

### Verify virtual-tail globals against the PE, not an inferred IDA value

A current IDA data display is semantic context, not proof of loader initialization.
For `g_global_input_state @ 0x006FC618`, IDA exposes a nonzero-looking inferred
value, but the canonical PE section mapping shows the address lies beyond the
raw-backed `.data` span while remaining inside the section's virtual size. The
correct initial bytes are therefore loader-zero. Recording `FF` from the IDA
display made the canonical comparator fail closed; recording the mapped zero bytes
with address provenance made both natural wrappers compare exact.

When an address falls in this virtual tail, compute RVA-to-section membership and
raw-size coverage from the pinned executable before adding a relocation key. This
is the same storage rule used by the UI-selection globals. Do not weaken target
byte validation or use a guessed initialized value just because a debugger or
disassembler renders one.

### Preserve nested argument dependencies before introducing temporaries

MSVC argument preparation can move independent literal loads ahead of a nested
call. For `EventSubobject130::trigger_global_effect @ 0x00434E90`, spelling the
effect lookup as a separate local causes standalone VC8 to call the lookup first;
the target instead prepares `42.0f`, flags, and `320.0f` before evaluating the
lookup used as the first emit argument. Writing the truthful nested expression
`emit(lookup(value), 320.0f, 42.0f, 1, 1)` reproduces the target 74-byte body
without volatile variables, register hints, assembly, or dead work.

Before creating a local merely for readability, compare whether that local gives
a call result a real lifetime that the target does not have. Prefer the smallest
source expression supported by current data/control dependencies. Conversely, do
not nest unrelated calls just because it improves bytes; the target callee graph
and argument values must already prove the dependency.

### Let ordinary return forwarding form verified member tail calls

A target `jmp` at the end of a member function does not require assembly or an
explicit tail-call extension. In `EventEffectStateView::set_event_id @ 0x00469DF0`,
ordinary `return publish_stage_state(g_battle_transition_mode);` gives VC8 exactly
the target sequence: zero-extend the byte, reuse `[esp+4]`, and jump to the sibling
member. Preserve the shared receiver and argument width in the source and let the
optimizer choose the tail call.
### Replay callers after extracting a polymorphic subobject contract

A local member declaration can be promoted into a shared narrow header when the
current target proves the receiver and virtual slot. `InfoEffectEmitterView` is
the reference: `emit_effect @ 0x0046E9D0` forwards through its `this+4` subobject
and vslot `+0x0C`, adding one trailing zero argument. Keep that as ordinary C++
virtual dispatch. After replacing the local declaration in `EventSubobject130.cpp`
with the shared header, rebuild both the new facade unit and the pre-existing
caller unit; exactness of the new function does not by itself prove that header
visibility/ODR changes left accepted callers unchanged.
### Use caller consumption to distinguish void from incidental EAX

A callee can leave useful-looking values in EAX without having a source-level
return value. Before declaring an `int` ABI, inspect current callers. For
`0x00434E40`, all fifteen switch callers set an `EventSubobject130` receiver,
call the helper, and return without reading EAX. The truthful `void` member
source compiles 67/67 exact; an `int` hypothesis makes VC8 materialize or preserve
a return and changes the branch/epilogue layout. This is an ABI correction from
current caller evidence, not permission to change return types merely to improve
bytes.
### Dense switch tables can trail the accepted body

`Fighter::advance_secondary_event_effect_cycle @ 0x00473F90` compiles to a
244-byte RET-terminated body followed by a 60-byte 15-entry jump table in the
same COMDAT. Compare the accepted current-target function boundary, not the
whole COFF section tail, while letting same-section DIR32 relocations resolve
case labels relative to the function entry. As with sparse switches, audit the
trailing table as compiler metadata; do not inflate authored-byte totals to
include it.

### Batch a polymorphic class only after vtable ownership closes identity

For stripped virtual methods, use constructor/vtable evidence before structural similarity. Current `CBattleManager` constructor `0x00438CC0` writes vtable `0x006C1504`; current `CBattleManagerArcade` constructor `0x00438D80` calls the base constructor and overwrites the vptr with `0x006C154C`. Their shared slots justify one `BattleManagerVirtuals.cpp` match unit containing nine methods, each still compared independently against its current address. Do not infer a class method merely because another candidate has the same small body.

A call-site can prove an unused-this member *view* even when the callee has another accepted standalone view. Several recovered manager pipelines preserve/reload `ECX=this` before `0x0046AF90/0x0046AFA0`; keeping those calls as member views naturally reproduces the target `mov ecx,esi` schedule while the existing 11-byte wrapper units remain unchanged. Record this as caller ABI evidence, not as a reason to mutate a globally accepted callee signature.

Use source types to explain condition-code differences. `frame_counter_04` is unsigned: target `0x00472D80` skips on `jbe` after compare with 60, and changing only the narrow field from signed to unsigned converts standalone VC8 from `jle` to the exact target without altering behavior. Conversely, if a semantically complete function still differs only by register/value scheduling after several natural formulations—as with `0x00472A70`—leave it review-pending rather than adding compiler hints or fake work.

### Reconcile subsystem ownership before freezing relocation names

A relocation address can be exact while its first semantic name is still wrong. `0x006FCF7C`/`0x007026E0` were first encountered from an Arcade scene-transition caller, but current BGM load/play bodies `0x0043CF00/0x0043CF80` are broader ownership evidence and identify them as BGM handle/service state. Rename the semantic contract before acceptance; do not let a locally convenient name become durable merely because the comparator can map it.

When one caller narrows a verified result, keep the unit boundary honest. `is_scene_fade_in_progress @ 0x0043B2C0` returns integer 0/1; `CBattleManagerArcade @ 0x00473870` tests AL. Express the narrowing at the caller rather than recompiling the helper under a false return ABI. Similarly, derived field offsets `+0x5BC/+0x5C4` can be exposed through narrow accessors when current code proves the offsets but not the intervening class layout; do not create a large synthetic padding array solely to land a field.

### Small class returns can expose hidden-sret ABI

`Menu::show_profile_result @ 0x0043F810` proves `TitleResourceManager::create_text_texture @ 0x00404D00` returns a four-byte class value. Declaring `TextureHandleResult { unsigned value; }` and returning it by value makes VC8 emit the hidden result pointer and naturally reuse a dead caller argument slot, giving 93/93. An explicit output local emits a two-byte-larger wrapper. Model the C++ value return; do not alias parameter slots or hand-manipulate the stack.

### Let VC8 generate hidden iterator returns; never synthesize the stack

A checked STL-like call can expose enough ABI to write truthful C++ even when the callee remains review-pending. At `0x00473050`, target code passes an iterator as two dwords `{owner,current}` and reserves a hidden 8-byte result pointer before calling `0x0043FC40`. Declaring an 8-byte iterator class/struct and a member `erase(iterator)` that returns the iterator by value makes pinned VC8 emit exactly that hidden-return convention. Use this source-level ABI reconstruction rather than inline assembly, manual stack manipulation, or copied call bytes.

For external target strings, distinguish address ownership from object-owned literal bytes. `data/bgm/st%02d.ogg @ 0x006C1590` is referenced through an undefined extern in the Arcade probe, so the comparator entry uses address validation and still verifies the canonical target bytes. Literal validation is appropriate only when the probe COFF section itself supplies the literal being selected.

### Share proved polymorphic subobject contracts across facades

`PostSequenceTransitionView::publish_transition_effect_46e040 @ 0x0046EA10` reuses the exact-backed `EffectEmitterSubobject` contract already used by `InfoEffectEmitterView`: the owner embeds it at `+0x04` and calls vslot `+0x0C`. With the already-attested 320.0f and 240.0f literals, ordinary VC8 source `emitter_04.emit(effect_id, 320.0f, 240.0f, 1, 0, 0)` is 47/47 exact. After replacing the round-transition TU's local ABI alias with the shared header, replay that caller; it remains exact. Prefer one narrow, target-backed subobject contract over multiple local vtable shapes whenever current ownership and slot evidence agree.

### Do not infer a container's mapped type from a key-only template helper

A raw-exact generated `std::_Tree::find` COMDAT can be stable across different mapped-value types when its machine code only compares keys and walks nodes. The pinned origin witness for current `0x0046EA60` uses `std::map<unsigned,void*>`, which is sufficient to prove compiler ownership of that helper. It is not sufficient to prove the live map schema. Current initializer `0x00438F50` writes path-hash/16-bit-id records, and exact authored `0x0046EB00` reads `iterator->second`, proving the actual object at `0x006FBD2C` is `std::map<unsigned,unsigned short>`. Treat generated template probes as code-shape/origin evidence unless the generated body actually touches the mapped value layout.

### Use translation-unit visibility before compiler attributes

`InfoManagerResourceView::initialize_story_info_resources_471e50 @ 0x00471E50` calls exact base loader `0x0046E960`. Putting both definitions in one probe TU lets VC8 inline the 33-byte loader and changes the target body. Moving only the truthful Story method to a separate TU, leaving the base declaration visible but not its definition, restores the target out-of-line call and gives 97/97 exact. This is positive source-partition evidence. Prefer a supported TU boundary over `noinline`, optimization changes, or dummy side effects.


### Distinguish implicit virtual destructors from user-defined empty bodies

`CharacterObjectManager<Fighter,FighterObject>` provides a repeatable VC8 lifetime test. A user-defined empty derived destructor publishes both derived vptrs and emits a 91-byte body, which is not the target. Leaving the derived destructor implicit while making the trivial primary-base `ICharacterObjectManager::~ICharacterObjectManager() {}` definition visible in the same TU emits the target 81-byte normal destructor. This visibility change does not alter any of the fifteen already-exact 123-byte constructors.

To discover an implicit destructor in a probe, a direct destructor call may be fully inlined and therefore produce no standalone symbol. Force ordinary vtable emission through a real object construction path, then inspect the compiler-emitted special member; do not add a fake destructor body merely to get a symbol. Linker-folded EH is only shape evidence: all fifteen current normal dtors share handler `0x006BBE48`, while each specialization is identified by its vtable-owned scalar wrapper and exact secondary-base destructor edge.

### A register permutation can mean the source abstraction is still too low

A same-size register permutation is a stop signal for *that source model*, not proof that the original compiler cannot be reached naturally. The roster/effect `TObjectManagerBase` family is the reference. Directly spelling the list-node operations reproduced all semantics and target lengths but kept the wrong callee-saved registers, so many bounded pointer/reference/loop variants were correctly rejected. The missing fact was ownership at a higher C++ level: acquire the object and publish its handle in a small TU-local helper, then append the resulting base pointer with the real checked `std::list<BaseObject *>::push_back`. Pinned VC8 `/O2` inlines the ordinary `static` helper on its own and emits the exact target lifetime. That one source correction closes nineteen 94-byte `acquire_and_link_object` bodies and nineteen 117-byte `preallocate_object_pool` bodies, 4,009 bytes total, with no `__forceinline`, volatile/register variables, fake dependencies, manual vtables, or assembly.

Use this as an abstraction diagnostic, not permission to grind source spellings indefinitely. Current `release_all_tracked_objects @ 0x0056DA90` still reaches 122/122 with only target-EAX versus fresh-EDX handle-token scheduling, and several unrelated InfoManager bodies such as `0x0046E5A0`, `0x0046EB90`, and `0x0046EF40` remain allocator/spill blockers after their semantic contracts are closed. If a stronger container, lifetime, TU-visibility, or type-ownership fact is absent, keep the residual pending rather than manufacturing liveness. Conversely, when many class-specialized bodies share the same permutation, first ask whether a standard-container operation or base-class ownership has been prematurely lowered into manual node/register-shaped code.

### Prefer qualified base calls for proven secondary-base receivers

In a multiple-inheritance member, assigning `SecondaryBase *base = this` is not always codegen-neutral. VC8 preserves C++ null-pointer conversion semantics and can emit a `test/jz` before applying the secondary-base adjustment. Current `CEffectManager<T>::spawn_effect` bodies instead go directly from the non-null member receiver to `lea ecx,[this+4]` before the linked `TObjectManagerBase<T,...>::acquire_and_link_object` call. A qualified base-member call expresses exactly that source relationship and reproduces all three 115-byte targets without register hints, volatile locals, or manual vtable arithmetic.

### Treat trivial base-destructor visibility as TU evidence

A semantically empty virtual base destructor can still change a derived destructor by several instructions depending on whether its definition is visible. The four `CEffectManager<T>` targets end by restoring the shared `IEffectManager` vptr. With only a declaration, pinned VC8 emits an out-of-line `IEffectManager::~IEffectManager()` call and the derived dtor is 203 bytes. Giving the TU the truthful empty definition lets VC8 inline that vptr restore and yields the target 194 bytes exactly. Prefer the TU visibility demonstrated by target code over `noinline`/`forceinline` attributes or synthetic cleanup calls.

### Recover MI layout from dual vptr writes and symmetric member lifetime

The `CEffectManager<T>` constructors and destructors independently write two derived vptrs: primary `IEffectManager` at `+0` and a specialization-specific `TObjectManagerBase<T,EffectObjectBase>` vptr at `+4`. Their construction/destruction symmetry then fixes a 16-byte checked vector at `+0x64`, a 20-byte owning deque at `+0x74`, and a 12-byte checked tree at `+0x88`. Model those as real bases/members so VC8 owns vptr and EH-state generation. Do not flatten the object into byte padding merely because individual methods can be matched from narrow offset views.

### Recover sprite layouts from copy spans before naming transform methods

Current copy construction can close a render layout more strongly than isolated offsets. `CSpriteBase` copy constructor `0x004396A0` copies its leading `IColor` state and then exactly `0x78` bytes from `+0x08`, proving size `0x80`; four color virtuals access a 0x1C stride, which is the standard `{x,y,z,rhw,color,u,v}` vertex record. `CSpriteEx` copy constructor `0x00450640` copies the full 0x80 base, then 0x30 bytes at `+0x80` and 0x38 at `+0xB0`, proving a 0xE8 object with two four-point xyz quads. Model those records first. The resulting C++ naturally reproduces the color/transform family and preserves the existing CEffectSprite offsets without a synthetic padding array.

### Let ordinary integer promotion explain VC8 divide-by-255 color code

For packed RGBA multiplication, `unsigned char` components promote to `int` before multiplication and division. Source `first * second / 255` therefore produces the target signed magic-multiply sequence using `0x80808081`. Adding explicit `unsigned int` casts changes the generated division and fails exactness. Prefer the language's proved promotion rules over casts introduced only because the packed storage is unsigned.

### Duplicate truthful switch cases when the target owns a merged tail

`SystemEffectObject::reset_state @ 0x00660B00` has three source cases with the same real reset semantics. Grouping `case 0: case 1: case 2:` lets VC8 replace the switch with a compact range check and emits 24 bytes. Spelling the three cases separately and repeating the same two stores lets VC8 perform its own tail merge, reproducing the target arithmetic three-case dispatch in 35 bytes. This is the same principle as duplicated event-case suffixes: duplicate real semantics and let the compiler choose the merge; do not add a goto solely to prescribe target control flow.

`SystemEffectObject::update_state @ 0x00660A00` also demonstrates byte-significant source case order. Cases 0 and 2 contain a genuinely identical `alpha += 3; return` tail. Source order 2,1,0 makes VC8 keep the target case-2 copy and backward-cross-jump from case0, yielding 248/248; order 0,1,2 keeps the other copy and yields 244 bytes. Case order is legitimate source structure when each case's behavior is independently target-proved; it is not permission to insert inert branches.

### Keep semantically closed stack/register/constant blockers pending

A correct type/layout model does not guarantee standalone allocation. System manager spawn `0x00458340` reaches the target 125-byte instruction budget with the exact texture out-token/returned-handle distinction but still uses a 12-byte fresh frame instead of the target 8-byte coalesced frame. System acquire/link `0x00457110` is target-length with a callee-saved receiver permutation, while pool acquire `0x00456B70` has broader allocation drift. `CSpriteEx::finalize_render @ 0x00407AD0` closes the resource/D3D9 semantics but fresh VC8 pools 0.5 as double where the target uses a single-precision dword resident on the x87 stack. Do not solve these with parameter-slot aliasing, volatile, fake locals, register variables, hand-evaluated vtables, or assembly; preserve the semantic recovery as a future TU/LTCG/codegen lead.

### Use aggregate copy/clear operations when the target shows aggregate lifetime

`RenderModeManager::on_device_reset @ 0x004014C0` copies exactly seven dwords of cached render state from `this+0x0C` and then clears that same 0x1C-byte state block. Seven handwritten member assignments are semantically equivalent but let VC8 interleave later call preparation, producing a 324-byte body. Modeling the recovered state as one `RenderModeState28` and writing `RenderModeState28 saved = state_0c; memset(&state_0c, 0, sizeof(state_0c));` naturally emits `rep movsd` followed by one zero register and seven dword stores, matching the target scheduling. Use aggregate operations when current layout and target instruction shape both prove aggregate ownership; do not add `volatile` to block scheduling.

### A common switch tail can explain parameter liveness across the whole function

The 482-byte `RenderModeManager::apply_render_mode @ 0x00404A90` initially grew to 528 bytes when each case separately wrote the cached mode/flag. The target loads the byte flag into BL at entry and keeps it live across all cases. Moving the already-common semantic work back to one source tail after the switch lets ordinary VC8 preserve that lifetime; placing source cases in the target-backed physical order `4, 1, 2, 3` then reproduces the exact body and trailing jump-table placement. This is not permission to reorder arbitrary switches for bytes: require current branch semantics and a common operation that all cases genuinely share.

### Correct ABI from caller consumption before tuning codegen

`toggle_d3d_window_mode @ 0x00414B30` is a negative/positive reference. Hex-Rays exposes the residual `SetWindowPos` return as a byte-like return value, but current caller `0x00408780` ignores EAX immediately and performs unlock cleanup. Declaring the source `void` removes fresh `test eax; setne al` and brings the natural body from 290 to 284 bytes; further ordinary arithmetic association can reach the target length 286, although register allocation still differs and the function remains pending. Fix caller-backed ABI first; never preserve incidental EAX merely because a decompiler assigned it a type.

### Preserve member reloads across COM calls when aliasing permits mutation

`RenderModeManager::submit_primitive @ 0x004010F0` and
`submit_textured_primitive @ 0x00401130` are useful Direct3D9 aliasing
references.  A source local such as `D3DDevice9 *device = device_04` lets VC8
hoist the member load and produces shorter 55/74-byte bodies.  The target calls
`SetFVF`, then reloads `this->device_04` before `DrawPrimitiveUP`; ordinary
source that accesses the member again after the COM call reproduces 60/60 and
77/77 exactly.  This is real C++ alias behavior: an external virtual call may
mutate object state.  Do not add dummy reloads or volatile fields merely to
force the instruction sequence.

The same wave closes `IDirect3DDevice9` slots 69/83/89 as
`SetSamplerState`/`DrawPrimitiveUP`/`SetFVF`.  `RenderModeManager::set_mode @
0x00404750` is 137/137 from the cached sampler mode plus three normal
`SetSamplerState` calls, and `draw_rect_int @ 0x00401260` is 51/51 from the
member overload that converts four integer corners to float before forwarding
to the still-pending float rectangle body.

### Distinguish explicit false tails from preserved byte results

Small frame renderers expose two legitimate source shapes.  `CLogo::render @
0x0041F6A0`, `Opening::render @ 0x0041F8A0`, and the shared scene delegate
`0x0041E040` explicitly construct false on failure, so source
`if (begin_frame()) { ...; return true; } return false;` keeps the target
failure tail at the end.  `Ending::render @ 0x0041E920` instead returns the
byte result of `begin_frame` directly on failure; spelling that early return
preserves AL and removes two otherwise generated bytes.  Use caller/vtable ABI
and target result construction to choose between them; do not normalize every
byte-like virtual to C++ `bool` by habit.

`CFade::render @ 0x0041E290` also shows that source branch order is byte
significant even when both branches implement the same triangular fade.  The
target keeps the `timer > 60` descending path as fallthrough.  Writing that
branch first gives 142/142; the semantically equivalent `timer <= 60` first
form has the same size but a different branch layout.

### Reuse an already-proved vtable-cache source pattern

Current RTTI identifies `CLoadingSV::render @ 0x0041F410`.  The target keeps
complete-object `this` in EDI, caches `sprite_08.vtable` in EBX for the color
call, and keeps `&sprite_08` in ESI while the later render call reloads its
vtable.  Reusing the already exact `UiSprite94` pattern from GuideOverlay—one
local `methods = sprite.vtable` for the color call, followed by the normal
sprite render wrapper—naturally reproduces all 217 bytes.  This is stronger
than inventing register variables because the vtable-cache lifetime is visible
in target dataflow and already exists in accepted source elsewhere.

Do not treat `/fp:fast` or `/fp:strict` as a generic fix for the neighboring
primitive renderer `0x00401180`.  Default `/O2` promotes its `0.5f` arithmetic
to a qword literal; fast/strict keep a dword but produce different x87 or
integer-store schedules for the same two vertices.  None reproduces the full
148-byte target.  Keep that body and the 395-byte float rectangle renderer
pending until truthful TU/floating-point evidence appears; do not mix profiles,
volatile constants, or synthetic temporaries to manufacture the target.

### Recover Win32 wait-object lifetime from EH and stack storage

`CBattleSV/CBattleCL::on_scene_enter @ 0x00426090` and
`CBattleWatch::on_scene_enter @ 0x00426770` independently prove the same local
RAII object. A raw HANDLE plus explicit `CloseHandle` emits only 116 bytes for
the SV/CL body; a one-dword RAII wrapper reaches 177. The target reserves two
dwords, stores the `CreateEventA` result in the first and the literal wait
interval 16 in the second, and owns normal VC8 EH cleanup. Truthful source
`{ HANDLE handle; DWORD wait_ms; }`, with destructor `CloseHandle(handle)` and a
`wait()` member, naturally keeps the 8-byte object store while constant-folding
the actual `WaitForSingleObject` argument to `push 0x10`. With `/GS`, the two
independent target bodies become 193/193 and 230/230 exact. Prefer a real RAII
lifetime that explains both EH and local storage; never synthesize SEH or add a
dummy stack word.

### Let translation-unit visibility keep tiny base constructors out of line

`CBattle::CBattle @ 0x0041DF60` is a natural 9-byte constructor that publishes
the current RTTI-owned vptr. Defining `CBattleSV/CL/Watch` constructors in the
same TU lets VC8 inline that tiny base constructor and emits 9-byte derived
constructors, unlike the target. Placing the three truthful empty derived ctor
definitions in another TU where `CBattle()` is declared but not defined makes
VC8 emit `call CBattle::CBattle` followed by the derived vptr store, exactly
18/18/18. Use source partition as evidence before reaching for `noinline` or
other compiler attributes.

### Preserve real shared tails in network scene state machines

`CBattleWatch::update @ 0x004266C0` demonstrates two byte-significant source
control-flow facts. Disconnect, menu-initial-press, and the combined-input
counter all share one `return 2` tail. After the watch pump, the ordinary
network path is the fallthrough (`transition_mode != 3`) and uses
`while (continue_transition())`; phase 1..2 returns 12 directly, while renderer
state 5 and transition mode 3 share the real `prepare_watch_transition` tail.
Writing separate early-return blocks or placing the special transition block
before the loop changes jump distances/alignment. Preserve target-backed common
semantics and let VC8 merge them; do not add inert branches or gotos solely for
bytes.

### Pre-C++17 member-call evaluation order can be exact-match evidence

`CLoadingWatch::update @ 0x004268F0` is 209/209 only when the source preserves
the target's call-expression structure. For
`session->accept_match_setup(get_match_setup())`, VC8 selects the virtual member
before evaluating the argument getter. For the player2-input configuration
calls, the target evaluates game-mode/match-setup arguments before resolving
`get_player2_input()` as the receiver. Naming receiver/argument locals changes
that order and grows the body. Likewise, the state-1 result must be an explicit
branch; a ternary lets VC8 strength-reduce it into non-target branchless
arithmetic. Treat observable call evaluation order as source evidence, not as a
license for comma-expression tricks or register forcing.

### Stop at closed semantics when receiver/cross-jump scheduling remains different

`CBattleSV::update @ 0x00426180` and `CBattleCL::update @ 0x00426380` now have
closed network/renderer semantics and a natural source formulation whose first
47 target bytes match exactly. Their later loop/common-tail receiver scheduling
still differs under standalone VC8: target reuses the same session receiver
across success/failure edges and places cross-jumps differently. Keep these two
review-pending. Do not introduce fake member calls, volatile state, manual
register variables, or synthetic control flow merely to make the final schedule
match.

### Profile-menu switch bodies: trust the RET boundary, not the COMDAT tail

`CProfileMenu::update_state_four @ 0x0044CC50` and `update_state_five @
0x0044CDE0` are each 371-byte authored functions even though pinned VC8 emits a
388-byte `.text` section for each.  The remaining 17 bytes are the switch jump
table placed after the accepted `ret` in the same section.  The virtual
`CProfileMenu::update @ 0x0044D240` shows the same pattern at larger fanout:
227 authored bytes followed by a 29-byte alignment/jump-table tail in its
256-byte section.  Canonical comparison must therefore use the reviewed ledger
function boundary; section-tail size is codegen evidence, not an automatic
function extent.

The state-four/state-five pair is a useful source-shape reference.  Ordinary
`switch (substate_344)` source, the existing exact profile string/confirmation/
message contracts, and real CProfileMenu members reproduce both bodies exactly.
The only semantic differences are the target-owned Shift-JIS prompt suffixes at
`0x006C2458/0x006C246C` and the state-specific bool commit members at
`0x0044C380/0x0044C710`.  Both functions use the same folded current EH handler
at `0x006B8A58`; the folded handler is codegen evidence, not class identity.

Keep adjacent near-matches pending rather than shaping registers or CFG.
`update_profile_message @ 0x0043F6E0` has closed UI/input semantics but fresh
ordinary C++ is 291 bytes versus target 298 because the target keeps integer one
in a different register lifetime across several absolute UI-pointer loads.
`CProfileMenu::update_primary @ 0x0044BCF0` has matching switch semantics but
fresh body is 246 bytes versus target 256 because VC8 folds one true-return
case into the default epilogue; natural case/default reorderings merely move the
folded tail.  Do not use register variables, volatile, fake branches, or cloned
returns to force either function.

### Profile-menu file commits: hidden returns and caller-TU destructor visibility

`CProfileMenu::commit_state_four @ 0x0044C380` (908), `commit_state_five @
0x0044C710` (324), and `commit_profile_change @ 0x0044C860` (529) form one
canonical-exact file/string island.  The important correction is type/lifetime
evidence, not hand-shaped cleanup.  Current helper `0x00429970` initializes its
hidden return with the exact `MenuString28` SSO state (`capacity=15`, `size=0`,
inline buffer NUL) before assignment.  Modeling that return as the older
`ProfileStringTemporary` view makes delete-commit 314 bytes; the real
`MenuString28` return naturally produces the target 324-byte body.

Current `0x00408C40` initializes the same 0x1C SSO layout.  Its callers still
prove a translation-unit visibility distinction: the file-commit TU inlines the
returned temporary's `MenuString28` teardown, while the already-exact state-six
TU intentionally keeps an out-of-line temporary-destructor view.  Preserve the
caller-backed view that target codegen proves; do not globally unify same-layout
views just because the callee address is shared.

Two ordinary source details are byte-significant.  Copy retry checks the length
of the complete destination path (including `.dat`) before appending another
underscore to the stem; checking the stem instead keeps the same high-level
intent but swaps temporary stack colors and fails comparison.  Rename validation
must call `string_56c.c_str()` independently for the `/` and `\` `_mbschr`
checks.  Caching the pointer removes the target's second SSO selection and makes
the function 507 rather than 529 bytes.  These are observable alias/lifetime
semantics, not permission to duplicate dead work.

### Profile UI globals, aggregate lifetimes, and render facades

The Profile UI helper island closes a real global `MenuCursorState` at `0x006FCFFC`: item_count, page_size, input_counter, selection, and window_start occupy +0/+4/+8/+0xC/+0x10. Do not split those field relocations into five invented globals. Source store order still matters: `Menu::initialize_profile_menu @ 0x0043FBF0` is 77/77 only when `ProfileNameList::item_count()` remains live while input_counter/selection/window_start are initialized and item_count is published afterward. Writing item_count immediately shortens the function to 75 bytes.

The same TU reproduces seven Profile render/state facades exactly: message hide 48, initialization 77, overlay 97, footer 83, profile list 215, shared player-slot render 103, and tile render 142. `render_menu_list` gives a useful conversion rule: target converts the unsigned row index to `float` before that value participates in double-precision 16.0 spacing math. Direct unsigned-to-double conversion selects the wrong qword `2^32` correction. Recover the conversion stage from target literal width/FPU flow rather than changing the whole TU floating-point profile.

`Menu::render_profile_player_slot @ 0x0043FAF0` is a caller-proven unused-this member: callers place their Menu-derived receiver in ECX, while the body uses the player argument and shared UI globals. Keep the member ABI even though the body ignores ECX. `Menu::render_profile_tiles @ 0x0043FB60` similarly reuses the already-established shared byte at `0x006FA88E`; do not manufacture a duplicate global simply because the older semantic name is battle-oriented.

`CProfileMenu::commit_state_one @ 0x0044C110` extends the exact ProfileMenu file-commit TU to 621 bytes. The target requires `/GS`, a real local `ProfileMenuBaseData` lifetime, initialization member `0x00432050`, save-to-profile member `0x004317A0`, and the same caller-TU `MenuString28` temporary-destructor visibility used by the other file commits. Do not flatten that local object into raw storage or hand-code EH cleanup.

### Profile UI lifecycle: typed stack records and checked-list `back()`

`initialize_profile_ui @ 0x0043FCA0` (666), `render_profile_ui_frame @
0x00440170` (359), and `shutdown_profile_ui @ 0x004402E0` (129) form one
canonical-exact Profile UI lifetime island.  The initializer's 0x128-byte local
is not opaque padding: current `0x004115A0` copies exactly 0x128 bytes and then
reads the six color bytes plus aligned dword fields.  Modeling it as a typed
configuration record and compiling `/GS` reproduces the target 0x138 stack frame
and all 666 function bytes.

Two lifetime details are observable source evidence.  The initializer publishes
the input argument to `g_active_menu_input` immediately, then later rereads that
global while initializing a second `MenuCursorState @ 0x006FD018`; keeping the
argument live across the whole function causes VC8 to save an extra register.
This cursor is distinct from the already-established profile-list cursor at
`0x006FCFFC`.  Preserve both aggregates rather than merging nearby UI globals.

The frame condition naturally emits the target `test al,al; ja` only when the
unsigned snapshot predicate is expressed as `snapshot <= 0` after the preceding
state comparison.  More importantly, the current selection-menu stack uses
`std::list<UiSelectionMenu *>::back()`, not `front()`.  VC8's checked `back()`
emits the target sentinel-prev traversal and both invalid-parameter checks; a
`front()` spelling is 14 bytes shorter.  This is semantic container evidence,
not a license to hand-code iterator validation.

### Menu overlay lifetimes: class-owned teardown, element references, and switch tails

The current RTTI/vtable islands for `CMenuBattle`, `CMenuConfig`, `CMenuPractice`, and `CMenuConnect` support an eight-function 1,066-byte exact wave without inventing complete layouts for every menu class. `CMenuBattle` is the strongest layout case: current ctor/vtable/call evidence closes exactly 0x78 bytes as `Menu` + state byte/alignment + `TitleDesignResource @ +0x08` + five `UiDesignObject*` entries + `MenuCursorState @ +0x50` + checked `std::vector<int> @ +0x64` + owner pointer `+0x74`. Natural `/GS` C++ makes the normal dtor 142/142, scalar wrapper 30/30, and render 82/82. The ctor is intentionally still pending at 799/800: moving the real UI-binding loop inside each of the three game-mode branches recovers about 199 previously missing bytes and matches the target branch ownership, but truthful `clear`/`erase` iterator spellings all leave the same final stack-color difference. Stop there; do not add a dummy local, alignment directive, or register coercion for one byte.

`CMenuConfig` demonstrates that member teardown order is better evidence than a hand-written cleanup list. Current ctor/render/dtor accesses establish `GuideOverlay @ +0x08`, texture handle `+0xB4`, `UiSprite94[2] @ +0xB8`, real dwords at `+0x1E0/+0x1E4`, and `TitleDesignResource @ +0x1E8`. The user destructor releases the title texture and calls the design resource's virtual cleanup; ordinary reverse C++ destruction then emits the target design destructor, the two-element VC8 array destructor, GuideOverlay destructor, and Menu base lifetime. The array helper receives the linker-folded exact `IColor::~IColor @ 0x0040AD50` implementation as a function pointer, so canonical comparison needs an address-validated DIR32 callback anchor rather than a REL32 call mapping. The resulting dtor/scalar/render are 179/30/197 exact.

`CMenuPractice::render @ 0x00445BA0` is a useful checked-vector lifetime case. The second checked `std::vector<UiDesignObject*>` at `+0x1BC` is accessed twice before one `CTile` render call. Loading both results immediately into pointer values changes the register lifetime; keeping the results as `UiDesignObject *&` element references lets VC8 preserve the first element-address reference across the second bounds check and yields 211/211 exact. Do not complete the Practice object layout just to obtain its destructor: no owned method currently explains the four bytes at `+0x15C`, so that gap remains deliberately unnamed.

`CMenuConnect::update @ 0x00444B90` shows two control-flow details that are source evidence rather than cosmetic rearrangement. The target physically spells the UI-color branch as `state != 6` (all-white pointer walk) with state 6 in the alternate block, and the selected-color loop advances both an integer index and a `UiDesignObject**` pointer. An indexed `item[index]` spelling removes the target `add item,4` and shifts two branch bytes. With the target-backed pointer walk, the callable body is 195/195 exact; VC8 places a 29-byte jump table after the RET in the same 224-byte section. As elsewhere, compare the reviewed function boundary and audit trailing compiler metadata separately.

### Profile submenu lifetimes and DeckEdit checked-container ownership

The Profile submenu wave closes six authored functions / 1,131 bytes without
inventing class padding. `CProfileDeckEdit::import_deck_counts @ 0x00449BE0`
(395) and `export_deck_counts @ 0x00449DF0` (159) compile exactly from the
native VC8 checked types `std::map<unsigned short, signed char>` at `+0x3C0`
and `std::deque<unsigned short>` at the API boundary. The same compile emits
tree/deque COMDATs matching current `find`, `insert`, iterator-increment and
push-back helpers. Treat those helpers as compiler-generated candidates; an
authored caller does not make the STL implementation authored.

`CProfileDeckEdit::~CProfileDeckEdit @ 0x0044A950` is 353/353 exact from a
natural 0x6B0 member layout. The late region is especially useful evidence: a
0x20 `DwordDeque4 + SpellTree` resource group at `+0x398`, the count map at
`+0x3C0`, `std::deque<map::iterator>` at `+0x3CC`, two `MenuCursorState`
objects at `+0x3E4/+0x3F8`, four real state bytes at `+0x40C`, and
`GuideOverlay[4] @ +0x410`, which ends exactly at 0x6B0. The UI subobjects use
implicit `CSpriteBase`-derived 0x94/0xA4 lifetime views. Current copy/lifetime
evidence proves five 32-bit extension values for the sprite and nine float
values for the tile; letting their implicit destructors run naturally fixes the
last target IColor-vptr scheduling difference. Do not replace this with manual
vptr stores.

Current vtables independently own `CProfileCharacterSelect` 0x288 and
`CProfileKeyConfig` 0x330 layouts. CharacterSelect normal/scalar destructors
are 164/164 and 30/30 exact; KeyConfig's scalar wrapper is 30/30 exact. The
same truthful KeyConfig TU emits a 188-byte normal destructor whose semantics,
length and member teardown are closed but one store/load scheduling swap
remains. Keep that normal destructor review-pending rather than forcing the
compiler merely because its scalar wrapper is exact.

### CDesignBase lifetime: owner width, implicit destruction, and alignment blockers

Current RTTI/vtable evidence identifies `CDesignBase @ 0x006C08AC` as the binary class behind the retained 0x34 `TitleDesignResource` facade. A natural `/GS` lifetime probe becomes canonical exact only with the target's actual member widths: an IColor-like 0x08 primary base, a 0x0C three-pointer handle owner, checked `list<UiDesignObject*>`, checked `map<unsigned,UiDesignObject*>`, and an 8-byte checked list iterator. The probe profile's checked `std::vector<unsigned>` is 0x10 and therefore cannot truthfully occupy the handle slot. Use a real three-pointer owner with real delete/reset semantics; do not hide the four-byte mismatch behind padding.

Special-member visibility is byte-significant here. A user-defined empty `CDesignBase` destructor republishes the derived vptr before member teardown, while current `0x00421890` starts directly with container/owner destruction and only restores the IColor vptr at the end. Leaving the virtual destructor implicit produces 154/154 exactly; its scalar wrapper is 30/30 and ctor is 153/153. This is the same compiler-lifetime principle seen in roster manager families: prefer the natural implicit special member when target vtable and teardown evidence support it.

The recovered layout also explains a useful stop condition. The three color-forwarding vtable members at `0x0040BFE0/0x0040C040/0x0040C0A0` semantically traverse `objects_14` and call UiDesignObject color vslots, but ordinary checked-list source emits 74-byte register-only functions. The target emits 81-byte bodies with an EBP frame and 8-byte stack alignment. Once semantics, iterator validation and virtual slots agree, this remaining frame-policy difference is not permission to add an aligned dummy, volatile local, compiler attribute, register coercion, or assembly. Keep the methods pending until a truthful TU/compiler cause is recovered.

`CMenuContinue`/`CMenuEnd` show how the exact base lifetime composes into derived UI objects. Their visible member prefix through 0x40 is natural: `Menu`, state byte, aligned `CDesignBase @ +8`, owner pointer `+0x3C`. Their six ctor/dtor/scalar bodies compile 160/114/30 and 157/120/30 exactly using ordinary virtual design load/cleanup, Menu base lifetime, target-owned paths and caller-backed unused-this member views. Do not treat that visible prefix as proof of the complete allocation extent: all current `CMenuEnd` new-sites allocate 0x44 before ctor `0x00445100`, so the trailing four bytes remain an unresolved layout question rather than padding to fabricate.


### CFileList/ProfileList/ReplayList: base extent, checked-byte flags, and import visibility

Current RTTI/vtables plus the `CMenuReplay` member boundary close `CFileList` at **0xB4**, not 0xB8. `ResultList` owns the extra `character_id` at derived +0xB4. Natural VC8 members are checked `deque<string> +0x04`, `deque<unsigned char> +0x18`, `deque<unsigned> +0x2C`, `deque<FileListTile> +0x40`, three 0x1C `std::string` values, then tail state through +0xB0. The base ctor/dtor remain 128/224 exact, while `CProfileList` and `CReplayList` are zero-size-derivative-layout classes at 0xB4.

Checked container APIs remain source evidence. `CFileList::shutdown @ 0x0043A0A0` is 166/166 only with `deque<unsigned>::operator[]`; `.at()` introduces `_Xran` and grows to 177. Replay navigation proves the +0x18 container is `deque<unsigned char>`: `row_is_directory @ 0x00439A60` returns the raw byte 28/28, and `enter_directory @ 0x00439A80` becomes 156/156 from the checked byte flag, checked row access, `"/" + row` temporary, and append. `find_row @ 0x00439750` (189) and nullable `row_at @ 0x004399A0` (26) use the same checked row deque.

The 233-byte base formatter is a useful relocation-semantics lesson. `std::string value = *current` reaches the copy/assign body at `0x004020D0`, but `output->append(value, 0, -1)` truthfully reaches the distinct append implementation at `0x00408B40`. Earlier treating both operations as assign created a fake “one COFF symbol, two target addresses” blocker. Fix the source operation, never the relocation mapping. Fresh source is canonical exact 233/233.

`CReplayList::format_item @ 0x0042A150` extends the same ABI to 501 bytes. A by-value 12-byte checked deque iterator supplies the row and index; directory rows get the green color tag, files build `directory/name`, call the replay-header service and compare against current code 0x6A, then incompatible files get the gray tag before the shared trim/append pipeline. One-byte size debugging exposed a general import rule: declaring `wsprintfA` as a plain extern emits `E8 rel32` (5 bytes), while the target uses `FF 15 [IAT]` (6 bytes). `__declspec(dllimport)` is the truthful visibility and makes the whole body 501/501 with zero non-relocation differences.

`CMenuReplay` lifetime closes naturally at 0x280 and its dtor/scalar/scene-mode virtual are 187/30/11 exact. Keep its 350-byte ctor pending. The only remaining difference is the scheduler position of `mov ecx,esi` before `refresh_file_list`: source VC8 hoists it across four independent `MenuCursorState` stores while target schedules it immediately before the final file-cursor store. Same size and semantics are not permission to manufacture a data dependency or force a register.

`CFileList::populate @ 0x0043A150` adds a strong C++ lifetime reference. The 1088-byte target is reproduced only when the directory-search `std::string pattern` is **default-constructed first and assigned later**; direct initialization lets VC8 construct the concatenation result in place and shortens the body. The string's scope also ends before the common `finalize()` virtual call. Moving that call into the directory-mode branch reverses destructor/call order. The rest is ordinary checked `deque<string>/deque<byte>` clear/push plus dllimport `FindFirstFileA/FindNextFileA/FindClose`. These are observable source lifetimes, not justification for artificial temporaries.

ReplayMenu gives two related branch/ABI references. `render @ 0x00446650` is 282/282 only with direct branch-local `render_cursor(...)` calls; outer x/y/scale locals change the stack/outgoing-argument shape. Its row loop repeats the Profile UI rule that an unsigned index must become `float` before double-precision 16.0 spacing math so VC8 selects the target single-precision `2^32` correction. `update_delete_state @ 0x00446A60` is 555/555 only after the substate is modeled as a signed byte and written as a switch, which gives the target `movsx; sub; je` topology. The input `hold.horizontal` pointer remains live across button reads (`axis[2]/axis[3]`), matching target alias/lifetime behavior.

`update_mode_state @ 0x00446590` is also a boundary-recovery example. Initial IDA attached it as a distant tail chunk of `CMenuReplay::update`, but the current dispatcher restores registers/ECX and tail-jumps into a chunk that immediately owns `push esi; push edi` and later four independent RET tails. Treat such a current control-flow/prologue/return closure as source-boundary evidence and add the candidate explicitly before comparing; do not merely compare an arbitrary interior address.

Stop conditions from the same island are useful. `go_parent_directory @ 0x004398B0` recovers the real expression `char slash='/'` plus `string::find_last_of(&slash,npos,1)` and reaches 91/91, but standalone VC8 places `slash` at stack-slot byte +3 while target uses byte +0. `refresh_file_list` is 231/229 on zero/EBX allocation, and the 511-byte browse helper remains 559 because target shares one `/GS` epilogue while standalone VC8 duplicates return epilogues. `finalize @ 0x0043A590` has a fully observed 0x194 text-render owner and correct high-level page pipeline, yet a natural probe remains 1080/1106 after truthful out-of-line string/handle visibility. Do not use arrays/unions as stack-color levers, goto-only tail shaping, opaque owner padding, or register coercion for these gaps.


### Profile-data and platform bootstrap: folded ownership, CFG source shape, and narrow COM views

A class can own a virtual slot without owning a distinct physical function body. Current `CFileWriter` RTTI/vtable `0x006C0F4C` identifies three new physical bodies: normal destructor `0x00407BF0`, `write @ 0x00407C10`, and scalar deleting destructor `0x00407C70`. Its last-write-size and seek slots point at `0x00407C40/0x00407C50`, the same addresses already established for `CFileReader`. Record the writer ownership in notes, but do not create duplicate candidates or count one folded address twice. The independent 21-byte writer destructor is also a boundary-recovery case: vtable xref plus a RET-terminated body bounded by `INT3` padding is stronger evidence than initial IDA function ownership.

Source branch topology can be recovered from target control flow without resorting to arbitrary gotos. `split_path_components @ 0x0040D0B0` compiles 164 bytes when written as an early `if (!filename) return ...`; the target has a far `je` around the filename-producing branch. Writing the truthful positive branch first, `if (filename) { _splitpath_s(...); return strcat_s(...); } return _splitpath_s(...);`, naturally emits all 168 target bytes. `ModulePathTextView::extra_bytes @ 0x0040D1D0` is an even smaller dataflow example: final `value != 0xFF` emits `setne`, while the equivalent ordered range predicate `value < 0xFF` emits the target `setb` and closes 34/34. Prefer a target-observed semantic predicate/branch organization over register or instruction forcing.

COM-heavy platform code does not require inline assembly or hand-written machine bytes. For `initialize_direct_input @ 0x0040D360` and `initialize_keyboard_device @ 0x0040D560`, define narrow structs containing only the current observed vtable slots as typed `__stdcall` function pointers. Ordinary member-pointer dereference then reproduces the target `CoCreateInstance`, `Initialize`, `CreateDevice`, `SetDataFormat`, `SetCooperativeLevel`, and `Acquire` calls exactly (138 and 188 bytes). Treat the vtable indices, current caller chain, and actual PE constants as independent evidence. Read GUIDs, format descriptors, IAT cells, and localized error strings from the canonical PE; an initially plausible remembered DirectInput constant was wrong until target bytes corrected it.

Stop when the remaining difference is not explained by a truthful source distinction. Module-directory init `0x0040D020` is 137/137 but differs only because standalone VC8 moves a real global context store across already-prepared GetModuleFileName arguments. DirectInput enumeration `0x0040D620` reaches the observed 80-byte temporary but calls helper `0x0040DE50` with an unresolved unused ECX plus EDX/stack arguments. Do not add volatile dependencies, fake locals, invented prototypes, inline assembly, or copied opcodes to close either gap.

### Separate authored DirectInput runtime from generated vector machinery

A recovered application aggregate can support both authored exact code and compiler-origin exclusions. `DirectInputBackend @ 0x00702A28` is the reference: natural `poll_direct_input_gamepads`, `get_gamepad_button_count`, and `get_gamepad_state` reproduce 312/71/88 target bytes while using checked vectors as ordinary members. Compile a second narrow probe that exercises those exact vector specializations and inventory-scan the emitted COMDATs. The current DirectInput probe excludes fifteen functions / 1,455 bytes only when each SHA-pinned relocation-masked fingerprint has the declared complete hit set. Do not classify `DCC0/DE30/...` as compiler code merely because IDA decompiles them like STL.

LTCG can rewrite a generated helper ABI without invalidating the authored caller semantics. Current gamepad initializer `0x0040D620` and fresh VC8 are both 176 bytes with the same EnumDevices/error/count/zero-state flow, but linked helper `0x0040DE50` consumes its value in EDX and vector/count on the stack instead of the standalone thiscall form. Current `vector<void*>::push_back` helper `0x00404400` likewise has a private ESI receiver. Treat these as linker/TU evidence. Do not encode EDX/ESI contracts into fake source prototypes or register variables just to copy the linked ABI.

### Use missed normal lifetimes to validate scalar wrappers

A vtable-owned scalar deleting wrapper can expose a normal destructor boundary that auto-analysis missed. `FrameData` vtable `0x006C0908` owns scalar wrapper `0x00421A90`; exact PatRecord88 destruction independently reaches its base lifetime. Fresh VC8 emits a 21-byte `FrameData::~FrameData`, and the target has exactly that RET-terminated body at `0x00421A70..0x00421A84` between INT3 pads even though the initial inventory omitted it. Add the source boundary first, compare 21/21, then accept the 47-byte scalar wrapper. Do not manufacture a normal destructor solely because a scalar wrapper exists; require target boundary evidence plus an independent owner edge.

### Keep durable relocation identities out of anonymous namespaces

A tracked match unit must survive a clean recompile, not only reuse of an old
object. `Fighter::finalize_sequence_entry_45bb10 @ 0x0045D110` exposed a stale
manifest mapping to an anonymous-namespace member whose decorated name contained
compiler hash `?A0x0fa9c17f`; a clean compile of unchanged semantics emitted a
different private hash and the comparator correctly failed closed before
comparing bytes. The callee is current
`FighterSequenceEffect_reset_and_set_color @ 0x004652B0`, independently visible
in target code. Moving the narrow ABI-only `FighterSequenceEffectView`
declaration into namespace `th105` produces a stable decorated symbol and keeps
the function 154/154 exact. Do not use anonymous-namespace hash fragments as
durable `rel32_targets` keys when the facade is meant to name an external target.

### Recover typed background render chains before forcing large callers

A medium render body can become straightforward once its small transform and layout callees are typed. Current `EventEffectStateView::render_background_effects @ 0x004696E0` is the reference case. The target receiver is independently fixed to `g_event_effect_state @ 0x006FBCAC`; checked-deque lowering proves a `std::deque<BackgroundRenderEntry>` at `+0x28`, with 8-byte entries `{unsigned char alpha; pad[3]; CSpriteEx *sprite;}`. The same object owns a polymorphic emitter at `+0x48`. Recovering the missing CSpriteEx origin-scale overloads first made the 511-byte caller readable rather than opaque.

The layout call inside that loop provides a second identity anchor: every current caller loads receiver `0x006FBCC0`, already known as global battle setup state. `BattleBackgroundLayout::place_sprite @ 0x00427200` then fixes `scale +0x14` and four viewport edges `+0x18/+0x1C/+0x30/+0x34`; ordinary 420/640/320 arithmetic followed by exact translate/X/Y origin-scale calls compares 128/128. With that helper exact, ordinary checked-deque iteration plus render-state setup, 3.0 X/Y/Z origin scaling, -100 Y translation, virtual color update, final sprite render, and the null-entry rectangle fallback reproduces the caller 511/511. Prefer this bottom-up typed-call-chain recovery over hand-transcribing a large decompiler listing.

Float expression and condition spelling can remain compiler-visible even after semantics close. The adjacent three-axis CSpriteEx rotation target is 1095 bytes, while natural source remains 1089: target uses `fld angle; fld st; fldz; fucompp` for each of three float truth tests, preserving the angle for the next cosine call. `if(angle)`, `angle != 0`, `0 != angle`, float-zero constants, and named zero locals all select other VC8 x87 topologies. Treat the remaining 6 bytes as a TU/compiler source-shape blocker. Likewise, an 11-byte +0x48 emitter state facade differs from its natural 10-byte source only in whether the vptr or adjusted ECX is formed first. Do not use inline assembly, volatile/dummy liveness, manual vtable arithmetic, or copied machine bytes to close such gaps.

Scalar-deleting destructors are safe batch progress only after class ownership is proved. This wave regenerated five 30-byte wrappers from the already-exact CSelectScenario, CTitle, CFileList, CMenuSelect, and PatRecord88 lifetime TUs. Each target wrapper is owned by the current class vtable and directly calls that class's already-exact normal destructor before conditional `operator delete`. The shared wrapper shape is not sufficient evidence by itself; keep normalized/raw clone matches unclassified until the vtable/lifetime edge establishes authored identity.

### Recover redundant target CFG as semantics, not source gotos

`decrement_fighter_timers_and_cleanup @ 0x0045E500` is a useful case where the retained source was semantically redundant rather than merely scheduled differently. The target tests `counter_558 >= 500`, enters the prepare/dispatch path only when `state_55a < 5 && state_72c != 2`, then performs the real counter update and returns; all other paths reach one later `state_55a >= 5` zeroing test before the common update tail. Writing the retained nested `if (counter >= 500) { if (state >= 5) ... else if (...) ... }` plus a second later `if (state >= 5)` preserves a redundant test that VC8 cannot fold into the target layout. Writing the single truthful compound success condition and real early update/return reproduces 470/470 naturally. Use target control flow to remove a logically redundant source condition when the resulting C++ says the same thing; do not encode target edges with artificial `goto` labels.

The same function reinforces the unused-this rule. Current Fighter callers load ECX with the Fighter receiver before `0x004359F0`; the callee body ignores ECX and tail-forwards only its stack event id to `dispatch_indexed_event`. Modeling the wrapper as a narrow Fighter member, not a free/stdcall helper, naturally emits the target receiver reload in the caller. Call-site ABI plus an exact caller is stronger evidence than a decompiler prototype that discarded an unused register.

### Missed interior boundaries can close caller/callee islands

`update_fighter_counter_thresholds @ 0x0045B300` was absent from the initial IDA inventory even though its machine-code boundary is unusually strong: the preceding function returns at `0x0045B2F2`, `INT3` padding fills through `0x0045B2FF`, the 284-byte helper owns a complete prologue/body/RET through `0x0045B41B`, and the next candidate starts at `0x0045B420` after another padding run. Fresh `FighterContinuity.cpp` emits exactly 284 bytes, and exact `0x0045E500` independently calls the helper twice. Add such a boundary to the corrected inventory before canonical comparison; never compare an arbitrary interior span and then back-fill a function claim.

This helper also shows why semantic-global ownership must be revisited. An earlier facade called its virtual notification receiver `g_battle_scene_renderer`, but canonical comparison stopped on one DIR32 byte: target loads `0x006FBCA8`, already established as `g_info_manager`, not scene renderer `0x006FBCA4`. Replacing the source owner with the current exact-backed identity makes all 284 bytes exact. Do not paper over a wrong semantic global with a relocation alias when the target address belongs to a different established aggregate.

### Correct lifetime semantics can still expose a zero-propagation blocker

`advance_fighter_sequence_55c @ 0x0045D040` demonstrates a useful stopping rule. The sequence slot contains a 0x94 sprite object; current teardown writes only the `IColor` vptr. Making the truthful trivial `CSprite` destructor visible and invoking the statically known destructor non-virtually reproduces that lifetime operation, but standalone VC8 then holds zero in ECX and reuses it for later head resets and a zero argument. The body shrinks from the target 198 bytes to 187 even though the destructor semantics improve. This is evidence about TU/LTCG constant propagation, not permission to clobber ECX with dummy work. Preserve the semantic discovery and leave the authored function pending.


### Battle-manager setup: caller-backed returns, TU boundaries, and list lifetime

Current vtable ownership should drive recovery of large state-machine methods before decompiler return guesses. `CBattleManager` vtable `0x006C1504` owns `prepare_battle_setup @ 0x00472110`; derived override `0x00473520` calls it and immediately continues without consuming EAX. Model the base slot as `void(MatchSetup*)`. A truthful `char path[260]` plus `/GS`, current session-input branches, MT seed, BattleObjectManager reset, BGM formatting/loading, two FighterPhaseContext slot initializations, pair initialization and round-byte randomization then compile 276/276. The neighboring vslot +0x30 terminal-state method is 277/277 from ordinary nested C++ and exact Fighter field layout.

Separate source definitions when current code proves an out-of-line TU boundary. `FighterPhaseContext::begin_slot @ 0x004650B0` and `initialize_slot @ 0x00465130` are 69/69 and 88/88 only when compiled from separate TUs. Putting both definitions in one source lets VC8 inline `begin_slot` into initialize; adding a noinline attribute would reproduce a compiler decision without source-partition evidence. The split also preserves a declaration-only `IntListView::push_back(const int&)` at +0x48 so the target's already-linked checked-list helper remains out of line instead of expanding `_Buynode` locally.

`BattleObjectManager::reset_battle_render_state_and_signal @ 0x00466DF0` is a strong condition-lifetime reference. The target compares pending-list size immediately after two -0.5f stores, performs roughly 180 bytes of independent x87/scalar reset work, then branches using the still-live flags. Writing `const bool transfer_pending = !pending.empty()` at that point naturally reproduces the schedule. Keep the active `std::list<int>&` reference scoped inside the transfer branch; hoisting it to function scope makes EBX live from the prologue and changes the body. The state byte at +0xF8 is unsigned `0xFF`, not signed `-1`: the signed spelling reuses AL rather than emitting the target immediate byte store. These are semantic lifetime/type facts, not register directives.

### Separate observed allocation extent from class member extent

`CBattleManager::dispatch_battle_state_frame @ 0x00472B20` and `transition_slot_34 @ 0x004728C0` show when an opaque allocation extent is legitimate evidence rather than fake padding. Current code passes literal sizes 0x288/0x78 to `operator new` before the external Practice/Battle menu ctors, and phase transition passes 0x44 before the independently identified `CMenuEnd` ctor. The callers never inspect the unnamed tail bytes. A narrow allocation-only facade of exactly the observed size therefore states only the current allocator contract; it does **not** claim a recovered member layout. Keep the known CMenuEnd member prefix at 0x40 until other methods identify the extra four bytes. This distinction lets ordinary `new Facade(this)` reproduce the target EH/new/ctor/install sequence without padding claims or manual allocation calls.

The dispatcher is also a function-boundary reference. Pinned VC8 emits a 600-byte `.text` COMDAT, but current control flow returns at byte 572 and the remaining 28 bytes are the local seven-entry switch table. The comparator resolves same-COMDAT DIR32 labels locally while comparing only the reviewed 572-byte function boundary. Do not extend a function merely because its COFF section continues into compiler-owned jump-table data.

`CBattleManager::transition_slot_34` adds an alias-lifetime and current-literal lesson. Caching `g_info_manager` in a long-lived local makes VC8 save EDI and grows/reorders the function; the target reloads `0x006FBCA8` independently at each effect call, so truthful repeated global access is the exact source shape. Also read target literal bytes before reusing an older semantic constant: current phase-1 uses 400.0f at `0x006C3A5C`, while a separate exact BattleController transition uses 480.0f. Equal-looking subsystem behavior is not evidence that literal identity survived the version/link layout.


### Narrow interface width can fix callers without changing the callee

`SpellDataOwner::load_spell_data @ 0x00432360` is the reference. Its retained declaration used an `int` story-mode parameter even though the body only forwards that value to loaders whose corresponding parameter is `signed char`. With `int`, `Fighter::initialize_fighter_spell_resources @ 0x00463070` must zero EAX before `sete al`; the current target performs `sete al` and pushes that byte-derived value directly. Narrowing the source interface to `signed char` leaves the already-exact selector body byte-for-byte 71/71 while making the 333-byte caller emit the target promotion naturally. Test both caller and callee before changing an ABI width; a `bool` spelling made the selector 75 bytes and was rejected.

### Start a subobject pointer lifetime where ownership actually begins

The Fighter face/cutin texture loaders show a useful evaluation-order pattern. The virtual configure call should remain a direct member expression so VC8 fetches the vslot from the member exactly as the target does. A real sprite pointer is needed only by the subsequent mirror-scale writes; declaring it **after** configure lets the compiler start the long-lived EDI lifetime at the same point as the target while still using the member expression for virtual dispatch. Declaring the pointer before configure hoists EDI too early and changes the vslot load. This is a source-lifetime distinction, not register forcing.

The same recovery removed a historical `volatile` store from `FighterCutinResource::load_for_character`. Ordinary `state_9c = -1` plus the correct sprite lifetime naturally schedules the store in the target epilogue and closes 199/199. Treat volatile/register/dummy-liveness constructs as suspect reconstruction debt: re-test them after neighboring ownership and ABI contracts improve rather than preserving them as matching mechanisms.

### Preserve destructor-only hierarchy visibility and checked-container lifetimes

Roster object destruction proves that a real class hierarchy can be visible in one original TU while a constructor TU behaves as though only a narrower layout is visible. Current RTTI owns `CharacterObjectEx<Fighter,FighterObject>` vtables and fifteen 406-byte relationship destructors, but exposing that polymorphic intermediate class to the already-exact ObjectPool source changes its 519-byte constructor lowering. Keep a target-backed destructor-only hierarchy view until constructor-side evidence closes the visibility gap; do not globally "improve" a header when cold replay disproves that visibility.

Checked-container spelling can encode real lifetimes rather than optimizer tricks. In the exact CharacterObjectEx destructor, the parent search recomputes `end()` in the loop condition and the child path has a real `empty()` guard before checked iteration. Saving `end()` adds one persistent iterator slot (410 vs 406); dropping `empty()` shortens the body to 393; `std::find` chooses a 440-byte checked-iterator topology. Use the target-observed lifetime/CFG form, and reject register/volatile/assembly workarounds.


### Shared vtables can expose both layout and source-partition boundaries

The current animation hierarchy provides a compact batch-recovery reference. RTTI-owned `AnimationObject`, `AttackObject`, `CharacterObject`, and fifteen `CharacterObjectEx` vtables agree on the same physical sequence slots. That repeated ownership is stronger than historical naming: it fixes base setters `0x00435200/0x00435220`, AttackObject sequence overrides `0x0045BFE0..0x0045C460`, and the four still-pending shared render slots. A narrow ABI view can therefore name only the observed `+0x13C..+0x170` state without exposing unrelated roster-object fields.

Source lifetime remains byte-significant inside that proven layout. `apply_sequence_frame @ 0x0045C110` computes a checked index into 0x88-byte records. Writing `frame_150 = frame_158 = begin + index` preserves one EAX frame pointer while EDI remains the index, matching the target stores and 16-bit duration load; two separate assignments let VC8 retain the frame in EDI and emit a different 107-byte body. Prefer the source expression that states the real simultaneous publication rather than adding a dummy dependency.

TU visibility is independently observable in the two setter/finalize overrides. When the base setters are defined in the same probe TU, VC8 changes the wrappers to 35/40-byte bodies. Compiling the overrides from a declaration-only TU naturally produces the target 26/33-byte out-of-line calls before virtual slot 15. Preserve this partition in the match graph. Do not substitute `__declspec(noinline)`, register variables, volatile state, inline assembly, or copied bytes for a boundary already demonstrated by target code.

### Shared render virtuals: container choice, branch layout, and post-RET tables

The AnimationObject render island is a positive reference for source-level choices that survive VC8 optimization without codegen coercion. `BattleObjectManager::dispatch_render_sprite @ 0x00466AB0` uses a real checked `std::list<RenderEntry*>` at manager +0x28. `back()` naturally emits the target sentinel `+4` traversal and two checked-iterator validations; `front()` emits a different shorter body. Prefer the container operation proved by target lowering over raw node access.

`AnimationObject::render_main @ 0x00435280` keeps render modes 0 and 1 as separate source cases even though they perform the same blend/color calls. VC8 preserves the target's two physical blocks only with separate cases. `AnimationObject::render_color_mode @ 0x00435540` similarly requires receiver lifetime to begin inside each case: precomputing `sprite = &sprite_004` moves the receiver before the switch and changes nearly the entire body. Direct case-local member expressions produce the exact first 479 bytes. The compiled section is 504 bytes because a 25-byte local switch table/alignment tail follows the RET; compare only the reviewed callable boundary while still resolving same-section DIR32 labels.

The nearby same-size transform pair `0x00435360/0x00435740` is a stopping reference. After correcting real float lifetimes, both fresh functions have the exact target size and all but one five-byte instruction scheduling window agree. Multiple truthful scalar/array/declaration-order forms do not move the target `fild` ahead of the EDI save. Treat that as TU/LTCG allocation evidence; do not introduce register variables, volatile state, dummy locals, padding, or assembly.

### Recover menu state machines from branch scope and member ABI

The exact `CMenuConfig::update @ 0x004411B0` wave shows how current RTTI ownership plus small typed callees can close a medium state machine. Primary-cursor success, secondary-cursor success, and accept/cancel are one `if / else if / else` chain; moving cancel handling after the chain changes pointer lifetime and callee-saved allocation. Percentage/grid fields are unsigned, and the four option colors are real `if/else` branches rather than a ternary. Preserve the reviewed RET boundary when VC8 appends a local switch table to the same COMDAT.

Literal type can be canonical evidence. The config volume helpers require `0.01f` promoted to double; spelling `0.01` generates the wrong qword even when code bytes otherwise line up. The SE helper also proves `g_indexed_event_handles + 0x200` is the end of the already-established 128-entry array, so encode that as a verified addend instead of inventing an end global.

Correct callee ABI before treating caller bytes as dead scheduling. Fighter initialization's former free/stdcall spell-mode declaration omitted the target receiver materialization. Current `0x00432520` proves a `SpellDataOwner` thiscall member; fixing that declaration restores the missing `lea ecx,[fighter+0x4F0]` and target loop alignment naturally. Keep the out-of-line TU boundary demonstrated by target code rather than using `noinline` or dummy liveness.

### Preserve C++ linkage across new-expression cleanup boundaries

Function linkage can affect VC8 `/EHsc` state even when the machine-level argument convention appears compatible. `CProfileMenu::update_state_two @ 0x0044BEF0` and `update_state_three @ 0x0044BFE0` allocate a submenu, run its constructor, then pass the result to `install_menu_object @ 0x0043B0F0`. The current target ends the new-expression cleanup state before entering that helper. Declaring the helper with false C linkage makes standalone VC8 keep the cleanup state live across the call and shortens each function by eight bytes; preserving its real decorated C++ linkage naturally emits the target `state = -1` transition and gives 236/236 plus 248/248. Do not normalize an external helper to `extern "C"` merely because the visible stack arguments are unchanged.

The same pair is an evaluation-order reference. Capture `string_518.c_str()` before converting `&base_data_004` to the exact-backed `PlayerSlotRecord` view. Writing the nested member call directly lets VC8 form the +4 receiver first, while the target completes the SSO pointer selection first. This is a real temporary/value lifetime distinction, not a register directive.

Physical storage type and helper ABI view can also differ truthfully. Five CProfileMenu 0x1C members are real `std::string`; exact helper calls may still reinterpret those objects through the layout-compatible `MenuString28` facade when that narrower external contract is independently established. Using the real physical type is what makes the 422-byte CProfileMenu normal destructor reproduce VC8's inline SSO teardown.

### Physical records can have phase-specific typed overlays

`BattleInfoRecordF8` is a current 1.06a example where one physical 0xF8 record has different truthful source views across initialization and runtime. Normal battle code treats +0x10/+0x14/+0x18/+0x1C as gauge/effect/Fighter-or-UI state, while Story attach/update reuses those exact bytes for progress, alpha, context and Fighter publication. Model the common physical extent once and use unions or narrowly scoped views for independently observed phase meanings; do not solve the conflict with duplicate absolute objects or a permanently opaque byte array. The shared layout now backs seven canonical-exact `BattleInfoRecordF8`/InfoManager consumers before the Story-manager virtuals are counted; the broader core island is documented below.

Also audit decompiler algebra before using it as source. In `BattleInfoRecord_initialize @ 0x0046FD20`, the target LEA chain computes `i + 10*mode + 205`; the decompiler rendered an apparently equivalent-looking `5*mode` expression. The factor is identity-bearing because it selects UI object ids, and correcting it removes the final body mismatch. Prefer target instruction dataflow when chained shift/add/LEA arithmetic disagrees with pseudocode.


### Promote container identity at a high-leverage consumer, not everywhere

`BattleInfoRecordF8::render_470710 @ 0x00470710` is the reference case for upgrading an opaque ring-like layout to the native checked container only where target lowering proves it. Fighter `+0x55C` has the 0x14-byte VC8 `std::deque<FighterSequenceSlot>` header, and the render loop's inlined checked element access naturally reproduces the target map/head/size validation. The branch-local scale lookup remains an out-of-line `entry_at_checked(index)` call; its argument lifetime keeps `height_ratio_08` live across the call on the `index>0` path, while the zero-index path materializes `1.0f` afterward.

Receiver lifetime identifies the final source shape. Caching the deque element as `FighterSequenceSlot*` or caching the sprite lets VC8 leave the element in ECX. The target instead transforms EBX from the checked deque index into the element pointer, then forms `ECX = element+4` for virtual render. Writing the direct expression `&deque[index].sprite_04` preserves that lifetime and gives 353/353 without register forcing. This container fact is not permission to rewrite every sequence access: substituting `deque[0]` for the separately reconstructed front-access path in `BattleInfoRecordF8::update @ 0x0046FF30` produces a materially shorter body and is rejected.

### Recover an RTTI-owned core virtual island as one source unit

Current RTTI identifies vtable `0x006C1374` as `CBattleManagerStory`; constructor sites call `CBattleManagerBase` construction at `0x0046B200` before publishing the Story vptr. A narrow prefix is enough for three central virtuals: unsigned frame counter `+0x04`, Fighters `+0x0C/+0x10`, InfoManager-like pointer `+0x8C`, and signed mode byte `+0x90`. Keeping this view separate from the later `CBattleManager` vtable avoids inventing one universal class layout.

The three methods are a batch source-shape reference. `run_threshold_pipeline @ 0x00471670` is 203/203 when the signed mode switch has only the target-observed cases 0/1/2 mapping to thresholds 0/120/180; assigning a fabricated default would change the unobserved invariant path. `run_180_300_pipeline @ 0x00471740` is 157/157 when Story terminal checks are written as a positive-success nest, naturally making both failures share the target return-2 node without a source `goto`. `run_story_pipeline @ 0x004717E0` is 309/309 under `/GS` with the real `{HANDLE handle; DWORD wait_ms}` event lifetime already proved by network scenes. Do not cache `g_battle_phase_block`: direct rereads free ESI for the event handle and reproduce the target exactly.

These exact methods all call the still-pending `resolve_fighter_body_collision @ 0x0046CCA0`, providing strong current Story-manager caller/TU evidence. They do not justify coercing that callee's remaining x87/stack-coloring mismatch. A real VC8 `/GL` + `/LTCG` link experiment on neighboring Story runtime `0x00471930` retained the same standalone EAX/EDX scheduling difference; treat LTCG as a hypothesis to test, not a blanket cure for allocator residuals.

### Let transition policy and container element type explain generated control flow

A compressed target jump table does not require source-level table construction. `RenderModeManager::set_blend_mode @ 0x004047E0` starts from a normal old/new transition key and a switch whose semantically shared tails are expressed as ordinary fallthrough. Once the source case order matches the target physical transition groups, pinned VC8 emits both the 256-byte callable and its compressed table/index payload exactly. Use target-observed source fallthrough and case order when they describe real state-policy reuse; never replace them with copied table bytes, computed-goto tricks, or inline assembly.

Generated-container identity is also caller-visible. `RenderTimelineEntry::render @ 0x00450EA0` calls the already-origin-proven 94-byte deque `operator[]` shape at `0x004399C0`. A `deque<CSpriteEx*>` produces an extra dereference because the helper returns a pointer-slot reference; the target instead uses EAX directly. The physical entry is `std::deque<CSpriteEx>`: CSpriteEx is large enough for a one-element deque block, so checked `operator[]` naturally returns the element address. Fingerprint identity proves compiler origin, but the authored caller still has to recover the correct semantic element type.

### Prefer real value-return and cross-call scalar lifetimes to stack shaping

The BGM loader pair demonstrates legitimate parameter-slot reuse. `allocate_handle` returns a four-byte class value, and ordinary VC8 hidden-return lowering reuses the dead source-path argument slot in `load_bgm_source`/`play_bgm`. That source contract closes 123/123 and 168/168 without naming stack offsets. Likewise, the render-timeline entry becomes 282/282 only when the real Y-scale value is captured before `scale_x` and used after the call; VC8 then creates exactly the target spill. When a stack slot has a value that is independently visible before and after a call, recover that value lifetime rather than adding a dummy local.

### Distinguish a checked-vector object base from its begin pointer

VC8 checked STL can make a target member look four bytes later than the source object itself. The FighterPhaseContext family is the reference: target code repeatedly reads vector begin/end at `this+0x3C/+0x40`, but a real checked `std::vector<Fighter*>` contains a four-byte proxy/allocator prefix. Placing the vector object at `+0x38` makes pinned VC8 emit those exact begin/end addresses and closes five phase bodies at once. Placing the vector at `+0x3C` moves fresh begin/end to `+0x40/+0x44` even though every loop is otherwise correct.

When several methods share the same four-byte displacement, first ask whether the observed target field is an internal STL pointer rather than the C++ member base. Recover the native container object and replay all callers before inventing a padding field or separate begin/end facade.

### Let chained value expressions recover EH temporary lifetime

String concatenation is a useful source-lifetime oracle under VC8 `/EHsc`. In `BattlePhaseBlock::initialize_character_story_script @ 0x0045A4E0`, the target calls generated `const char* + String28` followed by generated `String28 + const char*`. Writing two named locals (`prefix_path`, then `full_path`) keeps two user-visible String28 lifetimes and produces 316 bytes. Writing the real chained expression `String28 full_path = prefix + name + suffix;` leaves only the first result as an intermediate temporary and gives the exact 312-byte target, including unwind-state transitions.

Use hidden-return/cleanup order as evidence for expression structure. Do not imitate the resulting stack layout with parameter aliases, dummy locals, manual destructor calls, or source-only padding.

### Use special-member visibility and chained assignment as source evidence

Two current TH105 bodies provide reusable compiler archaeology without codegen
coercion. A trivial base constructor may need to be visible in the consuming TU
for an implicit derived/local construction to match. Fighter phase render state
`0x0045AA00` constructs a local `CSpriteEx`; making the truthful
`IColor() : value_04(0) {}` class-body definition visible reproduces the target
while the pre-existing IColor/CEffectSprite lifetime unit still cold-compares
exact. Prefer such demonstrated TU visibility to `forceinline`, duplicate
out-of-line bodies, fake locals, or register annotations.

C++ chained assignment also carries observable evaluation/store order. The
BackgroundBase ctor `0x00466020` zeroes six consecutive floats with a single
x87 zero value in reverse-address order. Ordinary
`a = b = c = d = e = f = 0.0f` is right-associative and naturally emits that
reverse `fst` chain; six initializer-list/member assignments emit forward order.
When the target shows one shared floating value feeding a reverse store chain,
test the semantic assignment expression before considering compiler flags or
stack/register shaping.

### A folded destructor helper does not erase constructor-proved container specialization

`BattleObjectManager` provides a useful checked-STL identity rule. Its request list stores an 8-byte `{unsigned,float}` value, so VC8 allocates a 0x10-byte list node through target `_Buynode @ 0x00464B20`; its renderer/owned-object lists store pointers and allocate 0x0C-byte nodes through the body folded at `0x00435E50`. All three element types are trivially destructible, however, so their `_Tidy` specializations fold to the same `0x00435EB0` target. Do not flatten the source type merely because a teardown REL32 is shared. Constructor allocation extent, checked consumer access, and exact caller ownership are stronger specialization evidence.

The same wave is a reminder to repair stale address-shaped method names before promotion. An older source called three methods `phase_465b00/70/d0`, but current exact caller `run_shared_battle_phase_sequence @ 0x0046BE30` physically reaches `0x00466980/0x004669F0/0x00466A50`; the `0x465Bxx` bodies are separate helpers. Rename the source to current-backed identities and replay the caller. Address history is a hypothesis, not a relocation contract.

Finally, worker-proc identity can close an asynchronous owner without promoting its downstream dispatcher. The exact manager ctor passes `0x00466CF0/0x004678D0` as stdcall thread entries; each exact entry performs COM init/uninit around an exact member loop. The render loop calls pending `0x00467380`, which establishes its ABI/ownership but does not make its 986 bytes exact. Preserve that evidence boundary instead of expanding a match claim through the call graph.

### Use a derived-to-base `push_back` temporary as static-type evidence

A standard-container member can have the correct physical layout and still expose the wrong **source static type** only when a richer caller is recovered. `BattleObjectManager +0x28` originally worked as `list<BattleObjectRenderEntry*>` for destruction, iteration, and `back()->render_sprite`; those paths do not distinguish that facade from the real `list<BackgroundBase*>`. The 986-byte typed factory does: `BGxx* -> BattleObjectRenderEntry*` must be materialized before passing a reference to `push_back`, and VC8 allocates one extra 4-byte local. Target has no local. Using `BackgroundBase*`, independently fixed by its RTTI/vtable and exact 0x64 lifetime, removes the C++ conversion temporary. Replay all prior consumers; if they remain exact and the richer root closes, the shared static type has stronger evidence than the earlier facade. Do not fake away the temporary with aliasing, casts to dead stack slots, or register/liveness tricks.

### Ordinary typed `new` can reproduce a large factory's entire EH surface

For `BattleObjectManager::dispatch_request @ 0x00467380`, do not lower eighteen cases into `operator new + placement new`. Narrow target-proved derived class extents plus declaration-only constructors are sufficient: normal `new BGCommon(...)`, `new BG02`, `new BG04`, and `new BG16` naturally emit all 17 target unwind states. The remaining byte evidence is semantic CFG shape: keep `!renderers.empty()` as hot fallthrough and write the nonzero float path as `value != 0.0f` so the target x87 parity branch and NaN behavior are retained. Case/allocation extent and source block order are evidence; copied jump tables, inline assembly, or explicit EH state manipulation are not.


### Use failure-form float guards when target NaN semantics require them

`BackgroundBase::render_base_sprites @ 0x004659E0` is a useful x87 source
oracle. A positive conjunction such as `x >= 0 && x <= 640 && ...` is
mathematically attractive but makes VC8 reject unordered/NaN through parity
branches that differ from the target. The shipped body instead behaves like
four independent failure guards: `x3 < 0`, `x0 > 640`, `y3 < 0`, `y0 > 480`.
Writing those ordinary C++ conditions reproduces the target `test ah` masks and
cleanup edges exactly. The outer counter must be signed `int` (`jl` at 30),
while passing it to checked vector `operator[]` still gives the target unsigned
bounds checks. Recover comparison semantics and source type; do not patch Jcc
opcodes or force x87 state.

### Linker-folded virtual overrides are one physical authored function

BG02/BG04/BG16/BGCommon provide a current ICF reference. Several classes have
identical ordinary overrides: three stateful backgrounds increment signed
`state_64`, three classes tail-forward to the same base renderer, and
BG02/BG04/BGCommon use the same 107-byte sprite transform. Source should retain
the class methods. The linked target may fold their identical COMDATs to one
address, so the authored-byte ledger counts that physical function once. Class
identity comes from each current RTTI vtable; do not multiply the numerator by
alias count, and do not hand-write a shared jump solely because the final PE has
one address.

### Let VC8 synthesize derived induction variables from source arithmetic

`BG16::slot_0c @ 0x00468780` demonstrates that a target register which advances
by a fixed amount need not correspond to a source counter.  An explicit
`angle_step += 90` source variable produced the right values but the wrong
EBX/EBP ownership and a three-byte-shorter `cmp i,4` latch.  Writing only the
semantic expression `i * 90 + state_64 * (i + 4)` inside the ordinary
`for (int i=0; i<4; ++i)` lets VC8 strength-reduce `i*90` into a second
induction register, yielding the target `add ebp,90; add ebx,1; cmp ebp,360`
loop.  Recover the source arithmetic and allow the optimizer to create the
machine counter; do not introduce a source counter merely because IDA names a
second induction register.

The same phase and BG04 `slot_08 @ 0x00468360` also show why one-use floating
locals should not be added for readability during byte matching.  Under x87,
a named POD float can reserve a full function-lifetime spill slot even when its
value has one consumer.  Keeping that computation directly in the call
expression allows VC8 to reuse the target spill area and can remove a complete
frame dword.  This is source-lifetime evidence, not a reason to use dummy
locals, volatile, register annotations, or stack padding.

### Treat unconsumed residual registers as unknown, not return values

Small leaf functions often leave a useful value in AX/EAX even when their
authored contract is `void`. `Fighter_copy_action_word_176_to_174 @ 0x0045B250`
loads word +0x176 into AX and stores it to +0x174; current callers discard AX.
Declaring the method as `short` based only on the residual register makes VC8
zero-extend the word and fails at byte zero. A void member assignment emits the
canonical 15-byte body. Recover return types from caller use and ABI evidence,
not from a decompiler's convenient expression result.

This rule also keeps compact virtual forwards simple. BattlePhaseBlock embeds
its scenario runtime at +0x68, and normal C++ calls to virtual slots 2 and 3
produce the two exact 11-byte tail wrappers. Prefer a typed embedded object over
manual vtable function pointers when current layout and callers establish the
relationship.

### Separate a physical container owner from a checked operation view

`CSelectScenario::CSelectScenario @ 0x00425350` is the reference case for a
shared member whose physical lifetime and consumer-facing operation surface are
both byte-significant. The target-backed integer-vector member is 0x10 bytes in
the constructor/destructor view. Two previously exact flow consumers still need
VC8's checked `std::vector<int>::operator[]` lowering, so those TUs use a narrow
operation view over the same independently proved storage. This is not license
to invent layouts: require exact constructor/destructor evidence for the owner,
exact checked consumers for the operation view, and replay every affected unit
after changing the shared header.

Local declaration points can carry the remaining optimizer evidence. In the
exact 862-byte constructor, `width` and `height` span all three texture loads,
but the one real texture `handle` ends before design loading. In the tree lookup,
the iterator is compared with the tree head before a node local is materialized.
Moving that declaration earlier emits a redundant two-byte register copy;
moving it after the end check removes the copy naturally. Treat lexical lifetime
as recoverable source structure, never as permission for dummy variables,
volatile/register forcing, alias barriers, padding, or inline assembly.

### Rank review callees from exact caller contracts, not stale handoff targets

A useful current-target discovery pass is to invert the accepted match-unit call graph.
Parse the `rel32_targets` of canonical-exact units, aggregate unresolved target
addresses by the number of distinct exact callers/units, and retain the semantic
aliases those callers already prove. Then remove CRT/import/generated candidates
and every address already documented as a bounded compiler/TU stop. This is more
reliable than an old “next target” list: several historical handoff targets had
already been promoted by later waves, while the inverted graph surfaced current
roots such as replay save, ProfileMenuBaseData lifetime, queue publication, and
the CNetworkServer/CNetworkClient construction/factory quartet.

An exact caller edge proves identity and a call-site ABI, **not callee exactness**.
The callee can also reveal a stronger local source fact without requiring every
caller facade to be rewritten. `BattleInputGate::queue_control_word @ 0x0042B270`
is the reference case: its own target body proves a 32-bit argument slot whose
low 16 bits are normalized in place before `deque<short>::push_back`, while an
already-exact caller remains byte-correct with a narrower `unsigned short`
declaration. Preserve both independently supported views and replay affected
callers before changing a shared header. Do not “standardize” signatures merely
for aesthetic consistency, and never use a caller alias as a substitute for the
callee's canonical zero-difference comparison.
### Keep same-size near-matches as negative source-lifetime evidence

`apply_current_frame @ 0x00436760` is a useful example of when to stop despite a seemingly close result. Exact character/effect callers prove one shared 0x1C frame prefix: pivot shorts +0x04/+0x06, texture index/rectangle +0x0A..+0x12, transform mode +0x14, and optional scale/rotation payload +0x18. Reading the rectangle into real scalar locals in the target order naturally recovers the target 8-byte frame and all **335 bytes**, with the first **120 bytes** exact. The remaining mode-2 difference is receiver lifetime across two transform calls: the shipped TU keeps one frame identity live for the later payload while reloading pivots; a branch-local frame pointer instead shortens the body and changes the earlier mode receiver. Record that as TU/alias scheduling evidence rather than adding fake dependencies or register directives.
