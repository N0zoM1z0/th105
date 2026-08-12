# Workflow evolution decision

## Decision

The reconstruction will evolve in this order:

```text
ledger schema gate
→ structured strict comparator
→ match-unit object graph
→ lazy IDA-first work packets
→ known roster clone-family manifest/fan-out
→ one audited synthetic COFF island + objdiff
→ generic clone mining / WIP scheduler / dashboard
→ partial link → runtime validation → full executable
```

This sequence was accepted on 2026-08-11 after reviewing the current TH105
repository and the TH06-style build proposal in `/tmp/vc_sth.txt`. It keeps
exact function bytes as the acceptance criterion while separating facts about
the shipped executable from useful, but weaker, source/build hypotheses.

The 2026-08-11 roster pass also fixed the operating priority inside those
gates: breadth-first reconstruction precedes per-function compiler tuning.
IDA evidence, RTTI, exact clone manifests, and truthful compilable source first
move central gameplay roots to `decompiled` or `implemented` across the whole
roster. Canonical strict comparisons remain mandatory regression gates, but a
known LTCG/register-scheduling tail must not monopolize the lane while dozens
of character functions remain unclassified. Once a family has source and a
reproducible mismatch packet, parallel evidence workers may tune its members
individually; only their strict 100% results become `matching`.

## Why this order

The function ledger previously admitted malformed CSV rows because comma-bearing
signatures were not quoted and the validator did not check physical row width.
That makes every downstream metric suspect, so schema correctness is the first
gate. A comparator must then report exact, mismatch, blocked, and error states
as structured data; a scheduler cannot safely infer those states from prose or
exit codes alone.

Focused VC8 probes already reproduce target functions, but they are not proof
of original translation-unit boundaries. `config/match-units.toml` therefore
models an explicit probe/object/function graph and records compiler inputs and
provenance without pretending that a probe is an original object. Work packets
join this local evidence with a fresh, exact-target IDA query. They remain
advisory because neither IDA MCP nor Ghidra MCP exposes a stable database
revision identity.

The fifteen-character object lifecycle is a known family supported by exact
target bytes. Eight audited families now cover 120 functions: handle-pool
construction/acquire, manager-base construction/destruction, acquire/link,
preallocation, outer-manager construction, and spawn. It is safer and more
valuable to encode these families before attempting generic similarity mining.
Clone membership alone does not change function status; it supports a
controlled semantic fan-out only after one canonical member is fully recovered.

Objdiff is useful before an original COFF is recovered, but the evidence class
must remain explicit. An audited PE-derived synthetic island can normalize
linked relocations back into ordinary COFF relocations and provide a visual
diagnostic. It is not original object, translation-unit, or LTCG-boundary
evidence, and it cannot grant ledger status. Object/function comparison remains
the acceptance loop until a linked reconstruction exists; executable comparison
remains final authority, especially for the PE's LTCG code.

## Invariants

- `config/functions.csv` remains the authoritative function/status ledger.
- A physical CSV row must have exactly the canonical fifteen columns.
- `matching` requires a reproducible 100% strict comparison; clone hashes,
  decompiler similarity, and IDA names are not acceptance evidence.
- An IDA or Ghidra function boundary is advisory until reconciled with target
  instructions and the ledger.
- IDA packets require exact SHA-256 metadata before and after collection.
- Every Ghidra fallback call supplies `program="th105.exe"` and runs headless.
- Match units state whether they are probes, synthetic islands, or linked
  candidates. None silently claims an original translation unit.
- The comparator independently verifies the exact target SHA-256. Unknown
  relocations fail closed, and failures have stable categories.
- The coordinator owns semantic-database writes, shared ledgers, claims, and
  Git; parallel evidence workers use non-overlapping address ranges.
- The original executable, analysis databases, generated packets, compiler,
  and reports remain uncommitted.

## Implemented foundation

- `scripts/validate-tracking.py` enforces the canonical ledger header and row
  width, booleans, evidence, and source-file invariants.
- `scripts/compare-function.py --json` emits stable exact/mismatch/blocked/error
  records with the first differing byte and relocation failure category.
- `config/match-units.toml` and `scripts/build.py` build canonical VC8 probes,
  hash their inputs, save provenance, and run strict comparisons.
- `scripts/work-packet.py ADDRESS --refresh` performs a lazy IDA-first capture,
  preserves raw backend payloads, diagnoses boundary disagreement, and embeds
  only fresh canonical comparison results. `--backend ghidra` is the explicit
  headless fallback; `--cached` is visibly advisory.
- `config/clone-families.toml` and `scripts/clone-families.py --check` attest
  the 120 known roster lifecycle members against exact target bytes and explicit
  normalization fields.
- `config/synthetic-islands.toml` and
  `scripts/generate-synthetic-coff.py` define one audited PE-derived diagnostic
  island. The generator verifies the exact target hash and ledger boundary,
  replays both REL32 equations, emits ordinary unlinked COFF operands, and
  proves that linking them reproduces the 175 target bytes.
- The pinned objdiff 3.8.0 unit `synthetic-youmu-owner-record` compares the
  synthetic island with the rebuilt `YoumuObjectRecords.obj`; its `.text` and
  `apply_owner_record` symbol report 100.0%. This closes the diagnostic objdiff
  gate without claiming recovery of an original COFF object.

The first match-unit audit covers `0x0053CA40` and `0x0053CAA0`; both rebuild
and compare exactly. They prove the focused-probe pipeline, not an extracted
original COFF boundary. Generic mining, scheduling, and dashboard work is the
next workflow gate, but it should now consume the structured comparator,
match-unit graph, lazy packets, known-family manifest, and the audited objdiff
diagnostic rather than inventing a second source of truth.

Applying these gates to the high-value shared object chain produced four new
exact implementations: `IColor::~IColor` at `0x0041EAA0`, the CEffectSprite
scalar deleting destructor at `0x0041EB30`, `AttackObject::AttackObject` at
`0x0045E3A0`, and `CharacterObject::CharacterObject` at `0x004927D0`.
`CEffectSprite::CEffectSprite` at `0x00421310` is source-complete but remains
`implemented`: the standalone VC8 object reverses the target's final derived
vptr/EH-state store order, a linked-LTCG island question rather than a semantic
gap.

The next canonical packet, Reimu pool acquire `0x00492BA0`, also validates the
workflow.  Exact decorated REL32 names are now preferred over legacy short
aliases, so distinct VC8 template specializations such as the pointer-vector
and unsigned-vector `push_back` calls remain fail-closed and unambiguous.  The
resulting probe matches all relocated target bytes through the complete fresh
allocation path.  Modeling the object tail as a second non-polymorphic base
was the decisive structural correction: VC8 then emits base construction,
tail initialization, and the derived vptr store in target order.  The only
remaining delta is a five-byte checked-list iterator spill/register schedule
in the reuse path, suitable for the linked-LTCG island rather than fake source
code.  The verified roster clone manifest then safely fans this implementation
out to all fourteen non-Sakuya object pools.

The same canonical-first rule then advanced the 237-byte roster spawn family.
The clone audit corrected an important trait assumption: only acquire-and-link
is character-specific; deque append, array allocation, and `memcpy` are shared
targets whose raw REL32 operands differ only by caller address.  Giving the
owner `+0x160` field a direct typed assignment and using the real virtual
action method moved the first mismatch from `+0x0D` to the parent block at
`+0x3E`; the target and object are both 237 bytes and the complete tail from
`+0x57` is exact.  A tempting single-expression parent append introduced
C++03 evaluation-order ambiguity and was rejected.  The safe source keeps the
same parent/deque operations with only a standalone/LTCG scheduling delta, and
the audited manifest fans it out to fourteen non-Sakuya managers.

A later exact pass resolved that final spawn delta without unsafe expression
tricks. Keeping the incoming parent in a stable alias, publishing it to the
object, and passing the published lvalue to deque `push_back` gives VC8 the
target dataflow while preserving deterministic C++03 semantics. All fourteen
shared-source non-Sakuya spawn entries now compare exactly at 237/237 bytes;
Sakuya remains an independently compiled work unit.

The same object graph exposed the manager-base constructor boundary. RTTI and
offset evidence require a polymorphic `CHandleManagerEx<Object>` member at
`+0x04` and an inline-constructed tracked list at `+0x54`. Modeling those as
real members, including the constructor-local EH relocations and per-roster
vtables, makes all fifteen constructor instances exact at 103/103 bytes. One
truthful type recovery therefore retired fifteen functions and strengthened
every later manager, spell, and battle work packet.

The next breadth-first pass applied the same gates at subsystem scale instead
of waiting for individual exact matches. `scripts/core-lane-survey.py` now
collects SHA-attested IDA-first packets for a named core lane, records ledger
versus backend boundaries, and keeps per-function query failures explicit. The
spell-card survey expanded the core graph with parser-owned deques and trees,
short-key temporary-tree helpers, sprite copy/growth, and sequence storage. It
also corrected `0x00432E20` from a guessed member function to its proven free
four-argument `__stdcall` ABI.

The battle survey then promoted the entire previously unclassified controller
island `0x0046FE80..0x00470940` to decompiled structure and connected it to
input gating, scene transitions, shared phase calls, fighter updates, and spell
runtime. This is the intended breadth-first result: central functions acquire
truthful declarations, type/dependency contracts, boundary warnings, and
bounded exact-work packets before workers spend time on compiler scheduling.
No fake bodies were added to make the island compile.

Two exact checks demonstrate that breadth and exactness reinforce each other.
The recovered spell-tree layout makes the native VC8
`std::map<int, SpellRecordView>::find` specialization at `0x004316C0` exact
(105/105) and therefore `library`; it is not authored progress. The recovered
0x98-byte sequence-slot layout makes `0x0045C5A0` exact (114/114) through a
truthful grow/lazy-allocation/two-short/embedded-sprite-copy implementation.
The latter is now a canonical match unit and a regression gate for the harder
EH-bearing sequence preparation path.

This result makes the breadth/exact cycle the default for large gameplay
systems rather than a one-off experiment. The reusable procedure is recorded
in `.agents/skills/th105-re/references/breadth-first-system-waves.md`: survey a
lane, expand one direct-call layer, establish neutral contracts and boundary
gates, fan out non-overlapping strict packets, merge exact results centrally,
then repeat from the newly exposed graph. The second BattleController wave
validated the next iteration by promoting thirteen formerly unclassified
shared setup/input/scenario/fighter/manager dependencies without adding fake
bodies.

The first exact fan-out from the expanded controller graph then made the
42-byte active-simulation wrapper `0x004704D0` exact as a canonical match unit.
In parallel, the strengthened 0x98-byte spell-sequence contract revealed that
`0x0045C440` is an exact native VC8 `deque<FighterSequenceSlot>::_Growmap`, not
authored storage code, and RTTI turned `0x0045C690`'s vague byte payload into a
real global CSprite/LTCG special-member blocker. These outcomes are the desired
feedback loop: exact work both retires functions and corrects the next breadth
wave's type graph.

The next fan-out confirmed that this was repeatable rather than a one-function
success. The central seven-state dispatcher `0x00470940` now matches all 529
authoritative bytes (and its 564-byte diagnostic section tail), the packed
local-control collector `0x0042A560` matches 224/224, and the synchronized
availability leaf `0x00427680` matches 8/8 in a separate TU that preserves its
caller's EH frame. The same packets left auditable stop conditions for the
127/129 RAII caller, 258/240 synchronized publisher, and paired fixed-slot
transfers. Breadth therefore supplies stable types and packet boundaries;
strict fan-out supplies exact bytes and feeds corrections into the next wave.

The newly shared controller/input/scene contracts then made the 299-byte round
initializer `0x004701C0` exact on its first complete source pass except for one
final branch polarity. Complementing the phase-1 predicate fixed the cold-block
order without changing behavior, yielding a 306-byte matching section tail and
an exact authoritative ledger prefix. This is the intended economics of the
workflow: breadth absorbs the semantic and ABI cost once, leaving exact workers
with small compiler-shaping deltas instead of whole-function rediscovery.

The same map immediately paid off across both neighboring directions. The
setup/roster worker returned exact 479-byte and 337-byte bodies, establishing a
complete 0x4C-byte `MatchSetup`, scenario/story argument order, and the shared
fighter-slot initialization path. The resolution worker returned exact 90-byte
terminal publication and 358-byte spell-linked round resolution, promoting
formerly unclassified direct callees into bounded contracts. Five new central
functions and 1,563 exact bytes were integrated from one breadth map without
each worker rediscovering the controller layout.

The work-packet boundary gate also prevented a false partial comparison at
`0x004B9540`: its stored `size=112` disagreed with `span_end=0x004B95B9`.
Fresh IDA instructions prove a contiguous 122-byte body through the final
`retn`, with the next function at `0x004B95C0`. Correcting the boundary before
adding a match unit exposed the full result: the genuine checked-list release
and clear source emits 122 bytes and matches 120, differing only in the token
load/push register. A comparator run against the stale 112 bytes would have
silently omitted the node-freeing tail.

The following fan-out is the strongest evidence so far for breadth-first plus
exact workers. Shared Fighter/ScoreData/BattleController layouts made
`0x0045BB10` exact at 154/154 after one expression-order adjustment,
`0x0046A490` exact at 279/279 after preserving an otherwise unused embedded
thiscall receiver, and the EH-bearing virtual `0x00470500` exact at 602/602.
The neighboring `0x00470780` also reached complete source and an equal-size
290-byte object; its only remaining issue is a precisely recorded checked-list
ECX/EDI schedule at `+0x3D`. In the same wave, fifteen direct dependencies were
promoted from inventory into named core contracts. This is the desired split:
the coordinator expands and stabilizes the graph, parallel workers close
bounded byte deltas, and non-exact results return a reusable blocker instead of
inflated progress.

The next spell/battle wave confirms the split also works when exact closure is
not immediate. One worker turned the 1,885-byte `0x004325B0` parser survey into
complete compilable source and corrected its temporary container to
`ShortTree`; another moved `0x0045BC30` from a 282-byte partial body to an
exact-size 346-byte object whose first 204 bytes match. In parallel, the small
ABI-focused `0x00458E80` packet corrected a false free-function hypothesis and
closed all 127 ledger bytes exactly. The coordinator then registered each
object and strict relocation set centrally. This is now the default evidence
for breadth-first plus exact fan-out: complete subsystem behavior may land as
`implemented`, precise compiler deltas stay queued, and independent leaves can
still become `matching` without holding the breadth wave hostage.

The following mixed wave exposed a second, equally important payoff: exact
workers can correct breadth contracts, not merely close byte deltas. A native
VC8 `std::deque<short>::operator=` probe matched `0x0042A7B0` at 297/297 and
proved that all three 0x14-byte fixed-setup payloads are real deques, replacing
an opaque authored type. That corrected layout fed back into both setup
transfers. In parallel, resource-owner cleanup `0x00432500` became exact at
171/171 and fixed the `0x0042D240` member ABI, while breadth source completed
the 516-byte scenario-row parser `0x004591D0` and 198-byte spell advance
`0x0045BA40` with resolved relocation graphs. The practical rule is now clear:
fan out exact packets early enough to challenge inferred types, merge those
corrections centrally, and immediately spend the improved contracts on the
next breadth layer.

The immediate next iteration validated that rule quantitatively. Enabling the
target's `/GS` mode made the native deque copy constructor `0x0042A8E0` exact
at 236/236, and its corrected three-deque layout made the whole fixed-slot
envelope assignment `0x0042AA00` exact at 162/162. Independently, an event-name
worker replaced a false global-list model with the exact VC8
`std::map<int, String28>` contract and closed `0x0043AC30` at 203/203. The
sequence-advance worker then used the real CSprite destructor to move
`0x0045BA40` from 185/198 at `+0x0C` to an exact-size object with a 46-byte exact
prefix. These are not disconnected leaves: each result sharpens a shared type
or ownership boundary used by larger setup, scenario, or spell-runtime bodies.

Breadth then advanced immediately through that corrected type. The next four
previously unclassified functions were identified as full-envelope copy
construction plus forward, backward, and fill algorithms over 0x50-byte fixed
setup ranges (`0x0042ADD0` and `0x0042AE50/AEA0/AEF0`). Their edges terminate in
the already exact deque copy/tidy and envelope assignment gates. This is the
preferred expansion shape: one exact ownership island turns several anonymous
neighbors into typed compiler/container contracts before exact workers tune
their callers.

Exact shaping on the adjacent scenario parser also benefited from the stronger
contracts: target-like selected-value reuse and a remaining-row loop reduced
`0x004591D0` from 538 to 518 bytes against 516, while preserving every resolved
relocation. The sole leading delta remains the four-byte VC8 `/GS`/EH frame
allocation, so the packet is now a two-byte tail-size problem rather than a
twenty-two-byte structural gap.

The same retuning cycle moved the paired fixed-slot transfers from 288/305 and
292/332 to 302/305 and exact-size 332/332 while preserving exact selector
`0x004275E0`. Their first differences are now early empty-container branch
displacements (`+0x0C` and `+0x1F`), which isolates the remaining work to the
original container/TU register schedule rather than payload semantics.

The corrected ownership island then unlocked another six formerly anonymous
fixed-slot operations without requiring speculative bodies: single-envelope
and range destruction, EH-safe range copy construction, checked tail
relocation/publication, backward tail assignment, and counted fill
construction (`0x00429640`, `0x0042A330`, and `0x0042AF20..0x0042B070`). Their
edges all terminate in the already typed envelope copy/assignment/tidy layer.
This is a useful LeanToken-assisted breadth pattern: retrieve the shared
repository contracts once, confirm exact address semantics in IDA, commit a
complete ownership/dependency slice, then hand the newly bounded callers to
exact workers.

Following that graph one caller layer farther recovered the complete checked
vector contract: size and overflow-checked allocation leaves, clear,
uninitialized copy/fill wrappers, a 786-byte counted insertion engine, and
count assignment (`0x004275C0`, `0x00427620`,
`0x0042A9E0`, `0x0042B120..0x0042B4F0`). This wave also demonstrates why the
ledger schema gate stays first: `0x0042B1D0` still carried `size=711`, while
its recorded span, contiguous target instructions, final `retn 10h`, and IDA
all agree on 786 bytes. The size was corrected before any exact packet was
allowed to compare it. A parallel native-vector probe then closed the size,
clear, uninitialized-fill, and uninitialized-copy specializations exactly
(31, 57, 56, and 41 bytes) as compiler-library code. The exact results do not
inflate authored progress; they remove ABI uncertainty from the central insert
and its input-record callers.

The same vector probe exposed and closed a comparator-schema gap. The deque
destructor COFF symbol resolves directly to `0x0051D0D0` inside
`0x0042B1D0`, but to the verified `0x00445370` jump thunk inside
`0x0042B4F0`. Function-local `dir32_targets` now select between separately
byte-validated relocation rows while remaining fail-closed. This makes the
native VC8 `_Assign_n` specialization reproducibly exact at 218/218; the
native 786-byte `_Insert_n` is a clean mismatch at `+0x43`, not a relocation
blocker. Registering the separately verified `bad_alloc` ThrowInfo and vtable
anchors also closes native `std::_Allocate<FixedSlotEnvelope>` at 89/89.

The next iteration validated both halves of the breadth/exact loop at once.
LeanToken first retrieved the roster and field contracts, while IDA vtable
xrefs expanded one 16,032-byte Aya root into a five-body CPU action-policy
family covering roughly 80 KB: four character overrides plus one default body
shared by eleven fighters. The family now has one common 0x770-byte view, five
ledger signatures, 25 direct dependency edges, and explicit declarations,
without fake gameplay bodies. In parallel, three exact packets consumed the
fixed-slot ownership layer: the 365-byte envelope deserializer and 238-byte
session slot initializer are exact, while the complete 848-byte recording
loader is durably registered with its first genuine compiler-shaping mismatch.
This confirms the intended cadence: use repository retrieval plus IDA to close
a large semantic family, then let small strict packets retire exact leaves and
feed corrected relocation facts back into the next breadth wave.

The 2026-08-12 lifecycle/continuity wave is the first direct audit of the
combined breadth-plus-parallel-exact policy. One coordinator-owned IDA survey
classified 22 remaining character roots and persisted their complete cases and
callees, while three read-only evidence lanes handled independent shared
boundaries. The lanes did not touch IDA, ledgers, or Git. Central integration
then identified `0x00463120` as the exact VC8 `deque<short>::_Assign_n`
specialization, matched the separate `0x00459D30` tail helper exactly, emitted
complete `0x0045CF00` source, and recovered the nested PAT ownership contracts.
This is a productive workflow: wide structural coverage and narrow compiler
experiments compound instead of competing, provided the coordinator retains
all shared writes and strict comparison remains the only matching gate.

## Operational loop

```bash
python3 scripts/verify-target.py
python3 scripts/validate-tracking.py
python3 scripts/build.py --check
python3 scripts/clone-families.py --check
python3 scripts/generate-synthetic-coff.py --check
python3 scripts/core-worklist.py --ready

# Coordinator or single-agent fresh capture.
python3 scripts/work-packet.py 0x00421310 --refresh

# Rebuild and compare a canonical focused unit.
python3 scripts/build.py --unit youmu-object-records --compare --json

# Regenerate the audited diagnostic island and inspect it with pinned objdiff.
python3 scripts/generate-synthetic-coff.py --island youmu-owner-record
.tools/objdiff/objdiff-cli diff -p . -u synthetic-youmu-owner-record \
  -o build/objdiff/youmu-owner-record.json --format json-pretty

# Evidence workers consume an existing packet without touching IDA/Ghidra.
python3 scripts/work-packet.py 0x00421310 --cached
```

The current high-value path remains the shared character-owned-object chain:
`CEffectSprite` → `AttackObject` → `CharacterObject` → fifteen pool acquire
functions → acquire/link and spawn families → character dispatchers, skills,
and spell-card pilots. Work should follow this unlock graph instead of raising
the function count with unrelated trivial accessors.

### 2026-08-12 giant-dispatch backend result

The second primary-vtable `+0x28` wave tested the lazy IDA-first policy against
three 54–67 KiB roots. Patchouli produced a complete 6,380-line Hex-Rays view;
Marisa and Udonge passed target, vtable, boundary, caller, callee, ABI, and
return checks but Hex-Rays rejected the full function. Headless Ghidra remained
the no-GUI fallback and recovered Udonge control flow, but its jump-table
warnings did not recover selector cases.

The accepted recovery path is therefore backend-neutral but still fail-closed:
decode the exact PE byte-index map and target table, keep direct singleton
branches outside the table-label count, audit fields from target instructions,
and record the evidence form explicitly. The pilot schema now uses
`analysis_form` and `analysis_lines`; it no longer mislabels target disassembly
as pseudocode. Batch survey failures are isolated per root, so one failed giant
decompile does not discard successful siblings. This moved the family from
three to six structurally decompiled roots without emitting placeholder source
or weakening the exact-match gate.

The immediately following boundary/outlier wave moved the family from six to
nine roots. Reimu exercised the exact-table path after both decompilers failed;
Remilia and Tenshi produced complete Hex-Rays views. A hanging giant request
also exposed the need for a per-root time budget, so the survey now defaults to
a 60-second `--decompile-timeout`. Most importantly, Reimu and Tenshi showed
that the ledger's non-contiguous function-body byte count may legitimately be
smaller than the inclusive entry-to-terminal-ret span. The workflow preserves
both values and requires instruction proof before contiguous comparison rather
than rewriting the ledger size from an IDA extent.

The next three roots extended this to the severe Sakuya chunk conflict, Yukari's
four independent selector tables, and Suika's 79-KiB exact-table path. Twelve
of fifteen roots are now structurally gated. In particular, instruction-width
auditing is sufficient for a truthful `exact_target_tables` structural packet
when typed pseudocode is unavailable; the manifest records that evidence form
and still withholds implementation and exact-match status.
