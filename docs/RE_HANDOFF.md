# Current reconstruction handoff

The tracking ledgers and fresh target comparisons override prose. Historical
session notes are preserved in [the dated rolling log](RE_HANDOFF_HISTORY_2026_09_26.md)
and the focused evidence files; their old "current", "paused", and "next"
instructions are not the active queue.

## Target and current phase

- Target: original Japanese TH10.5 v1.06a, SHA-256
  `56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
- User-directed cleanup and origin/boundary review work is paused after this
  checkpoint. The initial census was
  **4,023 candidates, 1,476 authored, 1,308 excluded, 1,239 in review**.
  Thirty-four evidence-linked origin/boundary batches are recorded in
  [the focused review](ORIGIN_BOUNDARY_REVIEW_2026_09_26.md). The current
  census is **1,502 authored / 1,414 excluded / 1,107 review**. Source-present
  is now 1,390 after the body-collision source audit; the exact ledger now records 1,317 functions / 223,051 bytes after focused body-collision replay.
  Recompute from `scripts/report-reconstruction-status.py --summary` after
  every promotion. Resume the remaining 1,107 reviews on user request.
- The local target file passes hash verification. The attached IDA session
  currently exposes a different executable (SHA-256 beginning `10350095`),
  so do not use that session's output. Raw target PE disassembly is available.
  Direct Ghidra imports for the rotation, common Fighter and Youmu roots have
  passed independent target identity, entry point and full mapped `.text` checks.
  Attest any new project before relying on it. Do not launch multiple
  Ghidra processes or use the factory MCP adapter for this work.

## Active matching checkpoint: AyaObject action-state root

`AyaObject_update_action_state_vslot28 @ 0x0061A290` now restores852's
pending spawn arguments/direct coordinate evaluation, including selector
limit-cell reuse forY and640-before128 call order. A local byte-argument
view removes three extra MOVZX operations. Target64CCB0 forwards DWORD
slots, but RTTI-linked Aya manager vtable6C62A4 slot+4=618470 consumes facing/
field33C asBYTE at618512/618516. The local view preserves four-byte argument
slots and28-byte wrapper purge; a unit-local alias binds the existing body.
Original wrapper C++ types are unproven; shared declarations/bodies remain
unchanged. See [the argument/byte-contract evidence](AYA_OBJECT_SPAWN_ARGUMENTS_AND_BYTE_CONTRACT_2026_10_02.md).
A450-case decoded emission-prefix model agrees in meaningful arguments and
RNG order with mocked calls, optional callback field changes and nearest-even
FSTP32. First-two446-byte/126-instruction pattern agrees after47-byte placement
translation, not canonical bytes. The earlier194-byte/43-instruction pattern
persists42 bytes earlier; its former same-address byte equality does not
carry forward.852 candidate1206/312 instructions versus target1201/310;
facing conversion accounts for five extra bytes, with other load/home
mismatches still present. Int-facing FIMUL control remains rejected.
Fresh configured19522 comparison is nonexact at+22 target0F/candidate56.
Metadata19340 versus target19524 shrinks gap220->184; section tail19808 and
comparisonwindow19522 include182 metadata bytes, so its hash is not a body
hash. Rawdiagnostics3/34 entry/800/980;800375-byte/107-instruction owner gains
are diagnostic only.855321->337 versus target332,861358->427 versus target358,
9001737->1729 versus target1773; there is no uniform improvement. Default802
postRET alignment remains.33 destinations/zero splits; no exact credit.
Full raw target traversal closes4630 instructions/all19522 bytes through
seven switches; guards124/124 retain853 twelve-role pairing and902 path lead.
Prior two641-value unsignedY proofs,853 select7 return/owner reload, alpha,
quarterY and unordered observations remain. No shared ABI/header/helper/
compiler/object partition or accepted-unit relocation contract change.
Remaining facing conversion/FILD placement, scratch homes/X rounding carrier,
movement/decrement register ownership,855/861 physical sharing, other action
values/lifetimes and original TU/LTCG context are open. Full numerical/
exception closure remains unknown. ImplicitX cast and routing the other18
calls through the byte view are neutral controls; do not repeat them as a
search strategy. Continue from independent target dataflow/type evidence.

## Preceding matching checkpoint: YoumuObject action-entry root

Freshly rebuilt`YoumuObject_initialize_action_entry @ 0x00543670` remains
nonexact over5159 bytes at`+0x80` target9D/candidate97; metadata5156 versus
target5160,29 distinct destinations/zero splits,6/30 instruction-edge diagnostics.
Raw traversal reaches1294 instructions/all5159 bytes including both switches.
A target851 state-write-before-value-load source control merges distinct851/854
owners (29->28), so it is not retained. A real converted-int argument carrier
in800 is caller-byte-neutral and also not retained. Full-root source and
exact ledgers stay unchanged. Target/candidate spans are82012/26 and85057/37;
original tail placement, selector-call lowering, value/register lifetimes and
compiler/TU/LTCG context remain unknown. See
[the load-timing checkpoint](YOUMU_OBJECT_ENTRY_LOAD_TIMING_2026_10_02.md).
Continue with independently supported ABI/compiler-context or value-lifetime
evidence; do not repeat these two source spellings or earlier negative join
permutations as a search strategy.

## Preceding matching checkpoint: Youmu giant root

Current bounded return/width controls leave the retained source unchanged:
canonical first mismatch remains`+0xCA` target64/candidate38, metadata`+0x9310`
versus target`+0x933C`, and31/98 diagnostic owners with zero new exact credit.
Raw target has13 incoming jumps to low3's action-zero tail; baseline has9.
696-only sharing recovers two edges but displaces four correct ones; explicit
sharing across all seven incoming owners moves the common call into high797
and overmerges other tails. Shared decrement controls place the body in696,
whereas target places it in311. A caller-only float-return probe is byte-neutral;
float-table return origin does not uniquely prove the helper prototype.
710 branch-call/direction-snapshot controls also regress owners. None is retained.
TH08's FSINCOS/FRNDINT reference does not establish assembly necessity for this
root or its two decoded lookup helpers, which contain neither instruction.
Original lifetime/compiler/TU context remains open. See
[the shared-return and x87 controls](YOUMU_SHARED_ZERO_RETURN_AND_CONTROLS_2026_10_02.md).
Next bounded matching work: freshly attest/build the source-present
`YoumuObject_initialize_action_entry @ 0x00543670` (5,159 bytes), then inspect its
residual owners. Do not resume source permutations on this root without new
independent evidence.

The following paragraphs record preceding checkpoints.

The spawn view now uses an opaque copied-input pointer, supported by raw
forwarder465190/consumer53B1C0 and manager ctor/table observations. All56
original integer-address casts are removed byte-neutrally. Action601 now
rounds X in each branch call argument and retains one real unsigned direction
snapshot for signed multiplication/full direction passing. Four unused scalar
hypotheses are removed. Fresh canonical comparison remains nonexact at`+0xCA`,
target64/candidate38; metadata`+0x9310` versus target`+0x933C` (44 bytes short).
Diagnostics improve27->31/98, gaining mid500/501/505/506 without losses or
exact credit;97 destinations/33 low entries remain distinct. All138 guards
and49 physical spawn payloads remain covered/resolved. Payload-address leads
decrease6->2, leaving605/710; arithmetic349/349 has two multiset leads696/710.
710-only and combined601/710 probes regress owners despite near-target size
and remain private. Only this unit's spawn REL32 spelling changes, with the
same465190 destination; shared ABI/helpers/flags/global maps stay unchanged.
Original types, narrow-control upper bits, register/temporary homes, physical
tails, compiler/TU context and numerical/exception closure remain open. See
[the copied-input and601 evidence](YOUMU_COPIED_INPUT_AND_ACTION601_2026_10_02.md).

The following paragraphs record preceding checkpoints.

Action214 now uses mirrored nested facing decisions. Natural VC8 recovers
all11 physical sequence-call sites in this owner, versus9 previously and11
in the target; unordered positions retain facing and select the original
default5/6. One unused byte snapshot is removed byte-neutrally. Fresh whole-
root comparison remains nonexact at`+0xCA`, target64/candidate3C; metadata
`+0x9314` versus target`+0x933C` (40 bytes short). All27/98 diagnostic owners
remain, without gains/losses or exact credit;97 destinations/33 low entries
remain distinct. The340-byte/120-instruction facing region has two register
rows different after internal-edge/root-return normalization, not regional
byte acceptance. All138 guard and49 payload packets remain covered/resolved.
Shared landing controls recover source joins but place physical tails in
wrong owners: even an8-byte-short combination remains nonexact and private.
An isolated selector int-to-short control is byte-neutral and establishes no
unique prototype. Existing zero/effect/numerical/typed-call recoveries remain.
Original register lifetimes, types, physical tails, compiler/TU context and
numerical/exception closure remain open. See
[the facing and return-path evidence](YOUMU_FACING_AND_RETURN_PATHS_2026_10_02.md).

The following paragraphs record preceding checkpoints.

Action214 now uses natural velocity-on-left literal-zero predicates. VC8
keeps zero live through the five target memory comparisons and discards/reloads
it around conditional virtual calls; three extra velocity FLDs disappear.
Effect125 coordinates now occur in call arguments, restoring trailing-prefix,
sine-Y and cosine-X order while preserving its original addition association.
Four unused floating local hypotheses are removed. Fresh canonical comparison
remains nonexact at`+0xCA`, target64/candidate0C; metadata`+0x92E4` versus
target`+0x933C`. All27/98 prior diagnostic owners remain, with no gains/losses
or exact credit, and all97 destinations/33 low entries remain distinct.
All138 guard and49 payload packets remain covered; load/store leads decrease
13->12. The prior effect-only negative is superseded under the recovered zero
lifetime. Random-X606 and strict-frame-window probes remain private: the
local Y carry is restored but low11/mid304 regress. Original source types,
remaining argument schedules, physical tails and numerical/exception closure
remain open. See [the zero and effect lifetime evidence](YOUMU_ZERO_AND_EFFECT_LIFETIMES_2026_10_02.md).

The following paragraphs record preceding checkpoints.

Three cached action214 sequence calls, nine peer action calls and two self
frame calls now use the existing typed virtual methods. Raw target RTTI and
all15 roster primary tables corroborate the unchanged animation prefix.
Fresh whole-root comparison remains nonexact at `+0xCA`, target64/candidate2C;
metadata is `+0x9304` versus target`+0x933C` (56 bytes short). Diagnostics
reach27/98, gaining low215 with no losses from the preceding26/98, while all97
physical destinations/33 low entries remain distinct. All138 guard and49
payload packets remain covered; load/store leads decrease14->13. This adds
zero exact credit. Zero-carrier variants are byte-neutral; nested-first-facing
and combined effect-argument probes lose low11 and are not retained.
Action214 still has three extra velocity loads; original zero lifetime, actual
argument schedules, physical tails and numerical closure remain unknown. See
[the typed virtual call evidence](YOUMU_TYPED_VIRTUAL_CALLS_2026_10_02.md).

The following metrics describe preceding checkpoints.

Action603 now computes both offset object853 spawn coordinates inside the
actual call arguments. Fresh VC8 prepares the trailing arguments before the
remaining sine-Y/cosine-X helpers, matching the observed target order, and
removes two extra dword copies. Ten unused scalar hypotheses are removed.
Whole-root comparison remains nonexact at `+0xCA`, target64/candidateCC;
metadata is `+0x92A4`, with26/98 diagnostic owners and no gains/losses.
The retained49 physical payload sites remain resolved. Direct/late action545
Y reads instead merge its spawn with546 (49->48); those probes and double-Y,
label-placement, zero-carrier and declaration-order variants are not retained.
Snapshot timing/type and physical tail placement remain unknown. See
[the spawn argument schedule evidence](YOUMU_SPAWN_ARGUMENT_SCHEDULE_2026_10_02.md).

The preceding bounded floating-value audit recovers action603's
`sineScale + (peerY + 100)` grouping, action696's dword rounding before
its sign comparison, and action526's three natural integer FISUB operands.
Fresh whole-root comparison remains nonexact at `+0xCA`, target64/candidateCC;
metadata is `+0x92A4` and diagnostics remain 26/98 with no gains/losses.
All138 target floating comparisons are covered by the guard scan, but operand,
precision and exception closure remain open. Arithmetic multiset leads reduce
from five owners to three; the remaining hoisting/sharing differences do not
prove an assembly requirement. Explicit shared-decrement and signed-byte
parameter probes are not retained. See
[the floating value order evidence](YOUMU_FPU_VALUE_ORDER_2026_10_02.md).

Action 602 now preserves the two observed unsigned-to-float conversions,
uses one rounded float loop index, and joins the existing sequence-advance
return path. Its target loop-test template is recovered. The candidate's
physical slot14 sites decrease from 14 to 13, versus target 12; the action740
shared return and actual tail placement remain unresolved. Full comparison
still fails at `+0xCA`, target64/candidateCC, with metadata `+0x92A4` and
26/98 diagnostic owners. No exact credit is added. Static site counts do not
prove missing runtime calls. See
[the action-602 and call-path evidence](YOUMU_ACTION602_CALLS_2026_10_02.md).

Actions 601 and 710 retain float X-argument carriers supported by target
branch-local dword stores/reloads. Fresh whole-root comparison remains
nonexact at `+0xCA`, target64/candidateCC; metadata is `+0x92A4` and strict
owner diagnostics previously improved from 24/98 to **26/98**, gaining low11/high798
without losing previous identical owners. This adds no exact-byte credit.
The extended x87 scan covers 138 target/candidate guards with zero
unordered-only leads; two CL masks are independently proved as divisor5.
It does not close full numerical or exception behavior. RTM compiler,
array-scope and named-prefix probes do not improve this retained result.
See [the float carriers and TH08 reference](YOUMU_FLOAT_CARRIERS_2026_10_02.md).

Action 603 retains one contiguous three-float object-853 payload and its
third-element values 2/1/3. A raw stack/def-use packet still resolves all
49 physical spawn payloads; six owners retain different address sequences.
The actual manager consumes its control parameter's low byte. See
[the preceding payload extent checkpoint](YOUMU_PAYLOAD_EXTENT_2026_10_02.md).

The preceding bounded numerical audit corrects actions 601/602/604 to send
unordered angles outside the inclusive 0..180 interval, and preserves
`roll + (index*45 + 22.5)` in actions 601/604. Fresh natural VC8 code reproduces
the target comparison masks/branches and addition order. Full comparison
still fails at `+0xCA`; 26/98 diagnostic owners and metadata `+0x92A4` now apply.
The TH08 reference contains real FSINCOS/FRNDINT assembly islands, but neither
instruction occurs in this Youmu callable. This does not establish a rule for
its callees or other roots. See [the angle audit and TH08 reference](YOUMU_ANGLE_RANGE_2026_10_02.md).

The current bounded root is `Youmu_dispatch_action_state_vslot28 @ 0x00530200`,
37,692 callable bytes. Source now restores the observed ordinary-jump and
209/210 shared effect paths using real field stores and control-flow joins.
Correct ECX virtual calls and the accepted animation/sequence prefix remain.
Candidate again has **97 physical destinations / 33 low entries**, with no
merges of target-distinct owners. Fresh strict owner auditing runs and reports
**26/98** diagnostic identical owners. This is not exact-byte credit.

Fresh focused comparison remains nonexact at `+0xCA`, target `64`, candidate
`CC`. Candidate metadata starts at `+0x92A4`, versus target `+0x933C`.
Raw traversal still reaches **37,692 bytes / 9,912 instructions**, with no
unresolved indirect jumps, including the auxiliary table at `0x539990`.
See [the shared-tail evidence](YOUMU_SHARED_EFFECT_TAILS_2026_10_02.md).

Action 214 now also preserves the target's unordered facing guard: only
ordered-greater opponent X reverses facing/velocity and selects sequence 5;
less/equal/unordered select 6. That earlier correction changed one branch opcode in the whole COFF text.
Direct Ghidra independently passes imported identity, entry point and full
mapped-text checks for this root. Corrected helper metadata is read back;
stack tracking warnings and flattened floating expressions remain limitations.
See [the ordered guard and Ghidra audit](YOUMU_GHIDRA_NUMERICAL_2026_10_02.md).

Local floating-environment and numerical carry-join probes are not retained:
they introduce different literal widths, extra destinations or float spills.
Field-store joins avoid those new carry-value spills but place shared stores
and tails in later physical owners than the target. Continue ordered
comparison/rounding audits from raw instructions alongside
actual tail placement, effect argument schedules and real floating-value
lifetimes. Sharing actions0/2 step variables, ordinary nested clamp spelling
and swapping 209/210 predecessor order are closed negative probes. Distinct
shared paths are
observed; original labels, TU visibility and compiler context remain unknown.
Do not infer an assembly or LTCG requirement from these discrepancies.

The preceding [virtual ABI correction](YOUMU_VIRTUAL_ABI_2026_10_02.md) remains:
wrong stdcall declarations cannot be used to obtain a topology score. Its
95-destination metrics are historical. The [action-720 recovery](YOUMU_ACTION720_2026_10_02.md)
and [action-606/710 numerical corrections](YOUMU_NUMERICAL_CONTRACTS_2026_10_02.md)
also remain. No shared header, compiler profile or relocation target changed;
only this unit was rebuilt. Exact totals remain unchanged.

## Previous diagnostic checkpoint: common Fighter giant root

The previous bounded root is `Fighter_update_common_action_state @ 0x004740C0`.
Fresh focused build and complete owner audit reproduce **53/66** diagnostic
owners, metadata `+0x2838`, and canonical failure at `+0x14`; the 10,219-byte
function remains nonexact. Direct Ghidra identity/mapped-byte checks passed.
Helper ABI metadata was read back before using the second decompilation;
its guessed return type and flattened floating expressions remain hypotheses.
See [the diagnostic refresh and TH08 x87 reference](COMMON_FIGHTER_X87_AND_GHIDRA_2026_10_02.md).

New shared-rounding-lifetime, short-selector and local floating-environment
probes add no exact credit. The late shared float is byte-neutral; the wider
lifetime probe loses owners 50/799, and narrowing the cached action loses 42
previously identical owners. Local `fenv_access` produces an incompatible
aligned EBP frame and is blocked by an unmapped literal in formal comparison.
No probe was retained. The remaining dispatcher encoding, action-50/162 tail
ownership and action-73/75/88 sequence ownership are not evidence that inline
assembly or LTCG is required. Continue with target-supported source structure
and helper/TU visibility; preserve actual per-operation float rounding.

The subsequent actual-helper visibility check is also negative: making the
complete landing helper visible is byte-neutral, while exposing the boundary
classifier removes a target receiver reload and folds target-distinct bodies. Its
root section drops to 9,145 bytes; it is not retained. See the follow-up
section in the same focused note. Common-root source and exact ledgers remain
unchanged. Do not repeat these two helper bodies as a generic TU remedy.

## Previous exact checkpoint: fighter body collision

User-directed byte reconstruction is active; the separate origin-only cleanup
queue remains parked. `CollisionContext_resolve_fighter_body_collision @
0x0046CCA0` is now canonical **1862/1862 exact** in
`cross-v106a-body-collision`. Fresh raw target comparison corrected the retained
source's inverted vertical center tie and missing float-rounded directional
velocities. Structured edge-owner chains replace every retained goto, and one
real average-motion lifetime shared across the two ordinary resolution paths
closes the final two stack-slot bytes. See
[the focused evidence](FIGHTER_BODY_COLLISION_2026_10_02.md) for the complete
CFG/ABI, numerical contract, scratch lifetime caveat, hashes and command.

The exact ledger gains one function / 1862 bytes and source count gains one.
These are ledger totals after focused replay, not a new aggregate cold replay.
Original class/TU spelling and explicit-union versus compiler slot-coalescing
provenance remain unknown. The accepted source reads only the scratch member
written in its active phase. No shared header, compiler profile or relocation
ledger changed. Archived origin evidence retains its body hash, nine incoming
and ten outgoing call witnesses, replayed by the existing public workflow test.

The previous `CSpriteEx_rotate_xyz @ 0x00407680` checkpoint remains canonical
1095/1095 in its eleven-function unit. See
[the rotation evidence](SPRITE_PIVOT_ROTATION_2026_10_02.md); its function-local
floating environment control is not a general x87 cure.

The common Fighter giant switch root `0x004740C0` has now been re-attested as
described above. Do not accept old semantic-closure/TU assumptions without
ordered target arithmetic and control-flow evidence. The two numerical
corrections here demonstrate why residual stack differences should not be
classified as LTCG until full ordered arithmetic has been audited.

Direct Ghidra 12.1 import and full mapped `.text` attestation succeeded for
the rotation. Use an isolated script directory to avoid recursive scanning
of old `.analysis` worktree paths. No factory adapter or IDA analysis was used.
The body-collision unit used hash-attested raw PE disassembly directly.

## Origin and boundary review discipline

Review one evidence-linked batch at a time. `functions.csv` candidate spans are
provisional; establish a complete reachable body, RET/tail behavior, padding,
call and pointer edges, and any remote chunks before accepting a boundary.
Separate target observations from source hypotheses. An exact authored caller
alone does not prove that its callee is game-authored: STL, CRT, third-party,
and generated helpers are also called from exact game code. Use game-specific
behavior, RTTI/vtable ownership, or positive library/compiler provenance to
classify. Leave unresolved rows in review rather than assigning an origin to
make the count look complete.

`config/function-origin-rules.toml` generates the census. During the cleanup
pass, three stale rules were found to overlap functions already promoted to
canonical exact (`0x004064D0`, `0x004309F0`, `0x00496420`). Those rows belong to
the exact baseline; the stale nonexact rule text has been removed or narrowed.
Active origin-rule and anchor comments now refer to the full current inventory
instead of the historical 4,010-row snapshot. The 4,010 and 1,002 figures in
`docs/KNOWLEDGE_BASE.md` are labeled as dated checkpoints, not live totals.
Run `scripts/function-origins.py --check` after origin edits as well as the
normal tracking validator. Any new rule needs a fixed candidate count/byte sum
and target-backed provenance. Record reviewed boundary evidence in
`functions.csv` and a focused note; do not treat name mappings or source
presence as exact credit. `config/claims.csv` remains header-only.

The first [origin/boundary evidence batch](ORIGIN_BOUNDARY_REVIEW_2026_09_26.md)
reviews `0x00407AD0`, `0x004099F0`, `0x00420B90`, and `0x00462AB0` using
complete raw CFG spans, RET/padding, game-specific behavior, and replayed E8/E9
edges from exact callers. The new boundary auditor triaged all 1,239 initial
review rows: 935 had full provisional-span reachability with no visible exit;
159 had unreached bytes, 62 indirect jumps, and 137 outgoing direct edges
(overlapping groups). These are leads, not automatic origin promotions.
The same note also records ten five-byte tail aliases whose signed E9 target
and excluded destination origin are replayed in `function-origins.py`, plus
the 15-byte `0x00689D25` function matched against SHA-pinned VC8 SP1
`secchk.obj` with both COFF relocation targets resolved. Eighteen ten-byte
global destructor adapters are tied to actual `_atexit` registration sites;
eight larger checked-container/string cleanup bodies are pinned by full hashes,
free-call edges, and the same registration mechanism. Ten smaller callback
bodies have direct `_atexit` registration and complete main spans. Three
simple aliases without that witness stay in review. The bounded proximity
screen's two other hits `0x0043BF50/60` feed the VC8 array constructor
before the nearby `_atexit` call; both now have separate generated lifetime
callback reviews. The KERNEL32
`0x006B55C0/0x006B5ECA` thunks have exact six-byte boundaries and IAT
name/slot witnesses. The 400-byte `__free_lc_time @ 0x0069CCD9` and 31-byte
`__allshl @ 0x006B6D00` have complete VC8 archive extents and full-inventory
fingerprints; all 43 `__free_lc_time` relocations resolve to CRT `_free`.
The 286-byte match-mode setup has complete raw CFG, game state writes and two
replayed E8 sites in exact `CTitle::update`; the nine observed E8 calls all
belong to that one exact caller. The 111-byte text-texture wrapper has complete
raw CFG, handle lifetime/error cleanup, and independent exact UI/network
callers; its retained class label remains a hypothesis. The 298-byte profile
message update has five complete return paths, game UI state writes, and direct
calls from seven separate exact menu functions; its retained source probe is
still nonexact. Twelve eight-byte Boost exception vtable entries subtract the
offset in their adjacent VC8 RTTI locator from ECX and tail-jump to a separate
candidate. Eight primary virtual deleting destructors in the same Boost RTTI
families have complete 30/57-byte bodies and a conditional call to the
excluded free alias. Four `clone_impl` virtuals end in the pinned VC8
`__CxxThrowException` call after copying an exception temporary. Their
underlying destructor/copy-helper origins remain open. Four clone/allocate
virtuals have complete 120-byte main spans; their common VC8 FuncInfo names
a single unwind action that frees the allocated object on copy failure. The
464-byte network sender `0x00416990` has complete raw CFG, type-0x0E packet
construction, Win32 queue/event behavior and nine distinct exact callers.
The old `ReimuObject*` deque fingerprint also matches code used by this
network sender, so its subsystem is now neutral runtime rather than characters.
The 334-byte profile-slot default initializer has a complete main span,
fixed game key codes, twenty deck slots and exact profile UI callers; the
called deck CSV loader `0x00431E80` now has a reviewed 463-byte main span
and six-state VC8 EH cleanup chain. Its class/ABI identity remains unknown.
The 784-byte profile writer `0x004317A0` has a normal RET 4 and a separate
terminal throw path, plus a three-state EH cleanup map; its retained
ProfileMenuBaseData class label remains a source hypothesis.
Nine 30-byte primary-vtable scalar deleting destructors now have pinned
RTTI owners, class destructor E8 sites and conditional free calls; most
underlying destructors still need separate origin review.
Five further 31/38-byte inline scalar deleting wrappers have complete
boundaries, RTTI vtable/type links, observed vptr restoration and optional
free calls. Boost `clone_base` uses the third virtual slot after two
`__purecall` entries; its COL is not directly adjacent to the wrapper slot.
Four 10-byte VC8 CRT global setters match named functions in the SHA-pinned
SP1 archive after one DIR32 replay each, and their globals are read by
independently pinned runtime consumers. The adjacent `0x0069BC05` setter
remains unresolved despite identical instruction shape.
Four 147/153/147/154-byte Boost exception injector copy helpers now have
complete main spans, two reviewed clone callers each, primary/secondary
Boost RTTI vptr links and three pinned one-state VC8 EH cleanup chains.
Their source TU boundaries and the underlying `0x004017A0` base-copy origin
remain separate questions.
Two eight-byte subobject destructor adjustors are pinned by exact
constructor/destructor callback pushes into VC8 vector lifetime iterators;
an 11-byte `std::invalid_argument` EH cleanup thunk is pinned by RTTI and
the Boost injector unwind action. Unreferenced lookalikes stay in review.
Two 17-byte array-record default constructors have complete target bodies,
exact parent callback paths, and paired checked-container destructor
adjustors; one also reproduces natural VC8 implicit constructor code.
The 1,862-byte fighter body-collision phase `0x0046CCA0` has complete
main-span reachability, five RET paths, ten calls to exact game collision
helpers and nine distinct exact BattleManager/Story callers. The later
source audit now closes canonical exact codegen as described above; original
class/TU spelling remains unknown.
The 148-byte line renderer `0x00401180`, 395-byte outline/filled rectangle
renderer `0x004012A0`, and 107-byte texture-slot binder `0x00404DF0` have
complete main spans and replayed call edges. The rectangle draws four
untextured lines or one untextured triangle strip. The binder also has an
independent canonical-exact textured-primitive caller; its resource lookup
callee is source-present. Their original class/TU boundaries and source
implementations remain unselected.
The 138/210/439-byte visual effect owner constructor/destructor/configure
spans at `0x00411430/0x004114C0/0x004115A0` are complete and tied to ten
E8 sites in six exact profile, network, and scenario callers. Configuration
copies 0x128 bytes and creates a packed color or gradient table. The
retained per-subsystem `0x194` class models are hypotheses; nearby runtime
allocator/list helper origins remain separate pending work.
The 548-byte Server send path `0x00416B60` has a complete RET 0x14 span,
type-0x0D queue item, timestamp/critical-section/event sequence and six
replayed E8 sites in five exact Server callers. Its queue/acquire/release
callees remain separate origin work; no source or exact credit was added.
The 1,095-byte three-axis sprite pivot rotation `0x00407680` has complete
reachability, two RET 0x18 paths, six target trig-helper calls and six E8s
from five exact renderers. Its neighboring sprite transform functions are
canonical exact; the retained `rotate_xyz` source is still unselected and
was not recompiled in this origin-only review.
The 4,247-byte `CSelect` base constructor main span `0x004231A0` is now
reviewed. Its only unreachable six bytes are a branch-skipped alignment
`lea`; two primary RTTI vptr writes, three exact derived/factory calls,
and a 19-state VC8 EH cleanup chain are replayed. The 19 remote unwind
actions are separately pinned; original TU ownership and source/exact
codegen remain unresolved.
The 1,452-byte intermediate battle collision phase `0x0046DFF0` has
1,434 reachable bytes plus three branch-skipped alignment ranges of
3/8/7 bytes, five exact BattleManager/Story callers and four calls to
exact collision/counter helpers. Adjacent family and list helpers remain
separate origin work; source and exact credit are unchanged.
The 686-byte family-1 checked-list traversal `0x0046DD40` and its
542-byte pair resolver `0x0046CA80` both have complete target spans.
The reviewed intermediate phase calls the traversal; it calls the pair
resolver twice, which has eight terminal calls to exact collision-extents
reset. The pair predicate is reviewed below; original source/TU and exact
results stay open.

The 398-byte collision descriptor-pair test `0x0046BCA0` and its 252-byte
nested shape test `0x0046BA10` have complete main spans. Their caller
chain runs from the reviewed object-pair resolver, and nine outgoing
calls land in exact game geometry helpers. Source/TU and exact status
remain unresolved.

```bash
python3 scripts/verify-target.py
python3 scripts/check-ida-mcp.py
python3 scripts/report-reconstruction-status.py --summary
python3 scripts/validate-tracking.py --require-target
python3 scripts/function-origins.py --check
```

The September YoumuObject action-entry checkpoint below is historical; the
fresh October load-timing checkpoint above is current.
Its target control flow reaches all
5,159/5,159 callable bytes, but the standalone candidate remains nonexact at
`+0x80` with 6/30 instruction-and-edge-identical diagnostic owners. The
820/850 tail-owner inversion and other physical differences are documented in
[the focused Youmu evidence](YOUMU_OBJECT_ENTRY_SWITCH_CLOSURE_2026_09_26.md).
The common Fighter `0x004740C0` root remains nonexact at `+0x14`; see
[its focused handoff](COMMON_FIGHTER_HANDOFF_2026_09_12.md).

## Commit gate

Run `python3 scripts/ci.py` and `git diff --check` in the finished local
worktree before every commit, then rerun after any further edit. Keep VC8 builds
single-process and pinned to one CPU. Shared accepted header/layout/compiler
changes require affected exact-unit replay; aggregate exact totals require a
cold `python3 scripts/verify-exact-units.py --all` run. Keep private reports in
`build/` or `.analysis/` and out of Git.
