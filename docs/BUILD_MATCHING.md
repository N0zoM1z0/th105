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
to 168 functions / 25,148 bytes. This is still a candidate queue only. Every promotion still requires a current boundary/semantic audit,
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
