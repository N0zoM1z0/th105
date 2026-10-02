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
  Direct Ghidra imports for the rotation and common Fighter root have passed
  independent target identity, entry point, and full mapped `.text` checks.
  Attest any new project before relying on it. Do not launch multiple
  Ghidra processes or use the factory MCP adapter for this work.

## Active matching checkpoint: common Fighter giant root

The current bounded root is `Fighter_update_common_action_state @ 0x004740C0`.
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

The previous bounded YoumuObject action-entry root at `0x00543670` is parked.
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
