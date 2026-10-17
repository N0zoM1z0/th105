# Reimu root: request-buffer lifetimes and stack control flow

## Target observations

Target is original Japanese TH10.5 v1.06a, SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
`Reimu_dispatch_action_state_vslot28 @478FA0` remains81550 bytes, body SHA256
`dbf6f375a809fea91cbbccf0f8cff2196f40cba11458c98e475a290b623053e6`.
The root remains authored, unclassified and declaration-only. No root
implementation/exact credit or accepted-unit changes.

Raw target control flow and ESP-relative LEAs distinguish buffer identity
independently of the pointed values. For example,400's two request paths use
frame-relative slots756 and676.545's initial request uses1020, while all three
later fan request sites use328.669's first two loops both use476; the other
two requests use1080 and1104. These offsets are measured from ESP after the
aligned frame allocation and four saved-register pushes, not from the caller.

The reviewed action-entry CFGs yield the following partitions. Equal numbers
mean the same stack buffer; numbering starts afresh for each action. Calls
are listed in physical instruction order, not runtime order or iteration count.
526 includes its request in525's shared tail, outside526's physical interval.

| Action | Target | Earlier source | Current source |
| --- | --- | --- | --- |
|400/401/404/406|0,1|0,0|0,1|
|525|0,0,0,0|0,0,1,1|0,0,0,0|
|526|0,0,0,0|0,1,1,0|0,0,0,0|
|545/546|0,1,1,1|0,1,2,3|0,1,1,1|
|669|0,0,1,2|0,1,2,3|0,0,1,2|

## Source inference and focused compilation

Four fragments change, all included only by `ReimuActionStateDispatch.cpp`:

- `ReimuActionStateMidProjectileCases.hpp` gives the ordinary and random
  paths their own initialized arrays.400's counter helper remains after
  initialization in both branches, as in the target; random iterations reuse
  their branch's array without resetting the third element between calls.
- `ReimuActionStateMid520Cases.hpp` reuses one buffer across525/526's request
  groups, with explicit stores of all three values at each group reset.
- `ReimuActionStateMid540Cases.hpp` reuses one buffer across both fan requests
  and the final request in545/546; the earlier sequence2 request stays separate.
- `ReimuActionStateHighLateCases.hpp` reuses one buffer across669's two loops,
  resetting all three parameters on each iteration. Its other requests retain
  independent buffers.

These are source-lifetime hypotheses supported by actual pointer identities;
the original spelling remains unknown. Every local participates in real
requests. No padding, register forcing, new helper facade or compiler flag.

VC8's source/assembly listing records112 arrays larger than8 bytes in the
earlier expanded source:102 three-float and10 four-float arrays,1384 bytes.
Current source has99 three-float and10 four-float arrays,1348 bytes. The frame
changes **598h->578h**, compared with target570h. Three fewer12-byte arrays
explain the main allocation discrepancy; compiler allocation/alignment does
not turn this into a36-byte frame reduction. The remaining8 bytes are unknown.
Listing output leaves the raw text and all relocation records unchanged;
COFF container hashes differ with the source pathname.

Two earlier private controls changed only case ordering or replaced the three
source regions with one outer switch. Both retain126 primary destinations,
all11 switches and0/26 native smoke differences, but both keep frame598h.
Their prefixes are81100 and81108 versus earlier81128. Neither is adopted;
this is scoped negative evidence, not an original compiler/TU identification.

## Reproducible stack and pointer audit

```bash
python3 scripts/probe-reimu-action-source-shape.py --void-root --output-dir build/reimu-root-layout/current
python3 scripts/audit-reimu-root-stack.py build/reimu-root-layout/current/ReimuActionStateDispatch.obj --require-partitions --native
```

The new audit first requires the existing complete relocation qualification
and canonical replay. It closes all eleven target/source switches, propagates
ESP through every reachable root edge and rejects disagreement at merges.
Calls use observed RET cleanup in pinned tracked callee spans; indirect targets
require reaching full-width vtable-slot loads with agreeing cleanup. Slots8
and12 may share a call because both pop4; slot14h pops0.

For each request, backward traversal finds **all** reaching writes of its
sixth stack argument, then all reaching pointer-register definitions. It
keeps unknown paths, partial writes and caller-saved call barriers significant.
Math calls crossed while finding a pushed pointer have explicit preservation
assumptions. The packet records these ABI assumptions separately from bytes.
It does not prove every callee's complete semantic ownership or side effects.

Global request contexts can contain multiple buffers at one physical CALL.
For example, the merged530/531 tail must retain both incoming argument pushes;
a nearest-physical-push scan loses one. Action-entry traversal restricts the
predecessors before comparing buffer partitions, and includes shared tails
outside each physical owner interval. All nine changed action partitions pass.

Target ESP propagation reaches20243 instructions. The current candidate
reaches20262; all243 target and242 source requests have the expected28-byte
argument depth. Each root has112 distinct non-null request-buffer addresses,
and12 null requests. These are static address/context counts, not runtime
object counts or byte equality.

Current source's last reachable instruction ends48CD85, before three bytes of
alignment and the first table48CD88. The preceding candidate ended48CC85.
The last physical RET is earlier than these active shared-tail instructions;
it is not the callable end. Internal alignment remains significant, and this
diagnostic closure does not create an accepted compiler/match-unit boundary.

Seven target-independent regression tests cover ESP disagreement, compatible
versus incompatible virtual cleanup, volatile/partial pointer definitions,
both predecessors of a shared request, and an unwritten argument path that
must not be discarded merely because another path is initialized.
The pinned earlier object passes its existing1544 native samples but fails
`--require-partitions` with all9 changed buffer relations. This is a detected
source-structure control, not evidence that native sampling proves lifetimes.

## Verification and limits

The affected native matrix reuses four earlier family generators and their
original target-branch assertions, filling later fixture fields from the
current void oracle's base input. It contains6722 inputs across the nine
actions, with5102 real RETs,1604 actual object-request entries and16 actual
effect-request entries. It passes **0/6722**, input SHA256
`afc219920d9471bfc7080ff5a6f8089e3b1cffc39d64a9406a33957bf4caedbe`.
No callback results are fabricated. This compares first world requests;
returning requests and complete runtime loops remain unproved.

The fresh current void object also passes0/1544 integration/default/common/
indeterminate-boundary samples with unchanged input SHA256
`c61982a9ccc694e3b6667371b5a4882e896da92d11320dd4aa3784f464787b80`.
Fresh compact bool passes0/12 smoke and0/8 unresolved740 boundaries.
The710/711/720 static loop contracts and all48 510 packets/12 reloads pass.
Only the affected families and current root samples were replayed.

The whole candidate remains nonexact at478FA8: frame578h versus570h. Its
prefix/text are81384/82756, with1168 direct calls versus target1188. All2454
relocations classify/replay, but that is not canonical equality. All11
switches and126 primary destinations remain. No aggregate cold replay.
Current object SHA256 is
`9fe46459022a5ff625033aee50527b43cc7f0565b343f4e655166be3ec02e75f`.

Bounded reports and source/compiler/object receipts are below
build/reimu-root-layout/. Raw PE supplies this unit's new facts; no IDA
semantics, Ghidra process or clone. All9 primary database hashes stay unchanged.
Obsolete private sources, listings, control objects and caches are cleaned;
current objects and compact evidence remain. Next recover the remaining
scalar spill/alignment and call sharing, while retaining the returning-world,
indeterminate740 and compiler/TU/LTCG proof obligations.

The follow-up [550 request/frame checkpoint](REIMU_550_REQUEST_FRAME_2026_10_18.md)
corrects source auxiliary-table traversal at adjacent metadata owners and x87
stack-store access flags. Both the earlier and current nine buffer partitions
pass the corrected audit; the measured source/listing/native facts above stay
historical. The follow-up recovers frame570h and supersedes the8-byte blocker.
