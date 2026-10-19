# Collision-frame preparation45C500: exact recovery and ABI

The 2026-10-20 continuation closes the complete function at2156/2156 under
the ordinary pinned VC8 SP1 profile. The earlier source checkpoint and its
failed controls remain useful phase evidence, not current blockers.

## Exact target and boundary

Only original Japanese TH10.5 v1.06a is used, executable SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
The reviewed candidate is `[45C500,45CD6C)`,2156 bytes, SHA256
`79b6295ec257dabdb090b1e3ae8943ccbfd2468fc9d438785215c75ddfec4dff`.
Raw CFG traversal closes all645 decoded instructions/all2156 bytes. The only
exits are RET0 at45CD59 and45CD6B and the noreturn checked-vector error jump
45C9E8->40C350. That separate123-byte error routine is not added to the authored
extent. No indirect exits, remote source chunks or switch metadata are found.

**Observed callers:**46E0C2,46E218 and46E310 lie inside the reviewed46DFF0
collision phase. Each loads the actor into ECX, calls45C500 and subsequently
overwrites EAX without consuming a result. The selected one-pointer fastcall
wrapper matches this physical ECX/no-stack-arguments/RET0 contract. Original
C++ member versus wrapper spelling is not uniquely recovered.

The previous bounded origin rule pinned the full body hash, all three inbound
E8 sites and all eleven calls to the three exact geometry providers. The
frame/actor collision policy established authored ownership before exactness.
The accepted function now uses the canonical-exact authored origin baseline;
the superseded nonexact rule is removed, not retained as a second claim.

**Observed behavior:** the entry copies state174, phase180/184, action13C,
facing104, sequence15C and frame158 into the collision snapshot. On a changed
frame it updates the two signed-byte counts and descriptor-pointer arrays.
It then prepares groupA/groupB boxes and shapes, optionally appends the194
extension to either family, and prepares or clears the primary32C pointer.
Group names describe the observed families, not a newly asserted gameplay
classification. Array stride16 and the pointer/box spans support five slots;
the execution fixture uses at most four frame boxes plus one extension.

The frame has native checked vector headers at58/68/78 (their first data
pointers are at5C/6C/7C), flags4C and a primary rectangle pointer54. Source
layout assertions fix these offsets, frame88h and actor-prefix330h. These
runtime views do not claim recovery of the original complete class hierarchy.

## Corrected helper contracts

The old ledger called all three providers single-argument fastcall functions.
That contradicted their selected C++ and target call/cleanup instructions.

| Provider | Observed/selected physical interface | Fresh result |
| --- | --- | --- |
|45B760 | ECX actor; record and output pointers in two stack slots; RET8 |335/335 exact |
|45B8B0 | Same receiver/two-pointer slots; flipped-Y path; RET8 |445/445 exact |
|45BA70 | ECX actor prepared at all three45C500 call sites; six stack slots for record, three low-word values and two outputs; RET18h |1386/1386 exact |

The oriented builder's receiver is unused in its body. A genuine member
source definition preserves every callee byte while reproducing the observed
caller receiver preparations. The original declaring class remains unknown;
this is not an invented custom calling convention. The two translation
providers read the actor's position/facing and have mandatory receiver input.

The three established matches stay in `cross-v106a-collision-preparation`.
The complete larger caller has its own accepted probe
`gpt-web-collision-geometry-preparation`. Both focused units succeed; only
45C500 is newly added to `matches.csv`, for2156 additional exact authored bytes.

## Source selection and compiler controls

The retained complete function was a hypothesis. It is now reviewed against
the complete target and selected in the mapping/source ledgers. The actual
state-tuple assignments precede the action/frame snapshot, restoring the
prologue's access schedule and MOVZX carriers. Actual member dispatch restores
the three missing ECX preparations. Runtime field names now identify vector
header offsets, and compile-time assertions verify their layout.

The earlier selected ordinary VC8 SP1 `/O2 /GS- /GR /EHsc /MT` root emitted2164
bytes, canonical4b5d4d88, with a34h frame versus target3Ch and first mismatch+2.
Those source-present and compatible-execution results did not establish exact
bytes. The following earlier controls were measured in that source context:

| Control | Whole-root observation |
| --- | --- |
| Original retained free-builder/state-order source |2162 bytes, first+2 |
| Member builder plus actual tuple order |2164 bytes, first+2; all three provider bodies remain exact |
| Make outer entry a member too |2164 bytes; no frame recovery |
| Const frame/record input views | Complete root payload unchanged |
| External provider declarations with all three genuine definitions separately compiled | All providers exact; root remains2164 bytes |
| Direct groupA array indexing or box-cursor/index form |3Ch frame and target prologue, but2207 bytes and first+6C |
| Shape-cursor/index form |2162 bytes; still wrong frame |
| GS and RTM variants of the new source context | Root payload unchanged in each corresponding context |

These are phase-scoped source/visibility/profile observations. In particular,
the failed2207-byte indexed control did not prove that direct indexing was
wrong, nor did any control establish an LTCG requirement.

### Complete ordinary-VC8 recovery

Target positive-facing paths take one destination pointer and copy the complete
16-byte descriptor; negative-facing paths reload the destination between the
reflected field stores. Genuine aggregate assignment explains the former;
four source assignments needlessly introduced reloads and different lifetimes.
Direct groupA indexing then restores the target's independent scalar and
16-byte induction values, output cursors and3Ch frame.

The extension path gives a separate lifetime observation: at45CBF7..45CBFF,
BL receives the narrow frame count plus one. That value stays live across the
geometry calls and is stored to the groupB count at45CCF7. It is not reloaded
from the potentially aliased object count. A signed-char local used by both
publications, with direct array indexing inside each branch, naturally
recovers the target EBP descriptor slot and EDI box address.

| New control | Complete root result |
| --- | --- |
| Aggregate positive copies with old explicit cursors |2120 bytes, first+2 |
| Aggregate copies plus direct groupA indexing |2163 bytes,3Ch frame |
| Narrow extension count retained across calls and branch-local indexing |2155 bytes; only cache-B register allocation and two commuted SIB forms differ structurally |
| Explicit cache-B `if/else` instead of ternary |2156 bytes, exactly two differing SIB bytes; first+2F8 |
| Direct checked-descriptor expressions instead of the temporary |2156/2156 canonical exact |
| Independent natural member-entry spelling with descriptor temporary |2156/2156 in private diagnostics; original C++ spelling is not unique |

The selected source retains the established one-pointer fastcall entry and
uses direct descriptor expressions. All645 instructions/2156 bytes, internal edges,
both RET0 exits,39 E8 fields and the separate Xran E9 field compare exactly.
The canonical body SHA256 is the target
`79b6295ec257dabdb090b1e3ae8943ccbfd2468fc9d438785215c75ddfec4dff`.
No comparator relaxation, manual SIB edit, register constraint, padding, dummy
local, fake return, copied code or target patch is involved. The fresh formal
producer records source/compiler/object/input hashes; the native audit below
retains its separate existing-object provenance limitation.

## Independent native execution and negative control

`scripts/audit-collision-geometry-preparation.py` places the source root at a
separate address and calls the original target providers. All geometry,
orientation lookup, conversion and SSE2-ceil instructions execute unmodified.
Target code and resource memory are read-only during execution; writes fail
closed outside the reviewed actor/stack regions. No helper result is supplied
by Python and no target instruction is patched.

The fixture supplies bounded native-vector headers, boxes and shape pointers,
a finite cosine resource table and an SSE2 CPU feature flag. The latter data
are environment inputs, not a claim to reproduce original game startup.
There are1344 distinct finite input records: zero, mixed and four-box groups;
eight combinations of400000/800000/1000000 flags; direct, absent and mixed
source descriptors; four initial facings; absent/plain/oriented extensions;
and two x87 precision settings. Each record executes cold and warm cache paths
on both sides, with changed positions/state/facing on the warm pass.

Both the earlier nonexact root and the selected exact root pass all1344
records with zero mismatches,2688 actual invocations per side. The final exact
run visits621 instructions on each side. The audit compares all330h object
bytes, actual geometry argument/data traces, native
RET/ESP and nonvolatile registers, x87 TOP/control word and MXCSR. Stack-local
scratch pointers are compared by role/content, not by an assumed matching
stack-frame address. Target/source helper counts agree:6848 ordinary box
transforms,8960 flipped-Y transforms and5504 oriented constructions per side.
Both actual lookup providers execute5504 times; conversion/ceil helpers execute
143104/63232 times per side.

All621 normal-path target instructions execute. The24 absent instructions are
exactly the22 invalid-parameter calls, the post-failure EDX restore at45C5F1
and the vector error jump45C9E8. The auditor enforces that coverage set rather
than describing645-instruction static closure as complete runtime coverage.
Invalid containers, throw execution, legacy x87 ceil, arbitrary NaNs/overflow,
unbounded metadata and original table initialization remain outside this proof.

A source-level1000000->2000000 extension-copy control, rerun from the selected
exact source, fails16/96 smoke inputs
on both cold/warm snapshots. It changes groupB count, box bytes and descriptor
pointers even though geometry call traces remain equal. This demonstrates
why counts/trace membership alone are insufficient. The single-session
negative source is compiled at the original source path to retain anonymous
namespace identities, then restored in a `finally` block before auditing.
The selected source hash is read back after restoration; no wrong source is
retained or selected. The complete recipe is private beside the trial sources.

## Vector exception edge and analysis limits

40C350 constructs and throws std::out_of_range using the exact target string
`invalid vector<T> subscript` at6D694C. Its ThrowInfo6E3BA4 resolves the
out_of_range, logic_error and exception type descriptors. This supports the
source vector-at error-edge binding. The pinned VC8 header implements that
same `_Xran` operation. However, native generated bodies are106 bytes with
GS off or118 with GS on, while target is123 with an aligned GS/EH prologue.
RTM/SP1 controls do not resolve it. Its exact compiler/EH context therefore
remains unknown and the candidate stays in origin review: no compiler
exclusion, upstream-release exactness or authored credit is inferred.

Required IDA preflight again rejects the wrong open image; no IDA semantics
or factory adapter is used. Direct read-only Ghidra independently attests the
file/imported hash, image base, entry, mapped text, selected root and three
caller E8 fields. It decodes the complete body, sets all four physical
signatures in disposable memory and reads their parameter storage back.
Decompiler text remains a hypothesis. All nine primary database hashes remain
unchanged and the temporary alias is removed.

## Reproduction

```bash
python3 scripts/build.py --unit cross-v106a-collision-preparation --compare --json
python3 scripts/build.py --unit gpt-web-collision-geometry-preparation --compare --json
python3 scripts/audit-collision-geometry-preparation.py \
  build/match-units/GptWeb_CollisionGeometryPreparation.obj
python3 scripts/validate-tracking.py --require-target
python3 scripts/check-match-literals.py --require-target
```

The established provider unit returns0/exact for all three members. The
caller unit now returns0/exact2156/2156. The native audit returns0; `--smoke` uses96
records/192 invocations per side. Existing-object execution reports build
provenance as unverified; the preceding formal producer is the separate
provenance evidence. Final reports are
`build/animation-state-20261019/formal-exact-root.json`,
`provider-exact-replay.json` and `native-exact.json` in the same directory.
Private controls/recipes are below `.analysis/animation-state-20261019/`.
This checkpoint adds one2156-byte exact function. No cold aggregate replay or
fresh aggregate exact-byte verification is claimed.
