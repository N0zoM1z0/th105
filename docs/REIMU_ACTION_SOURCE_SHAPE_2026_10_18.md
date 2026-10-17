# Reimu action-root source-shape diagnosis

## Observations

Target remains original Japanese TH10.5 v1.06a, SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
`Reimu_dispatch_action_state_vslot28 @478FA0` has the separately reconciled
81550-byte callable ending48CE2E. Root SHA256 is
`dbf6f375a809fea91cbbccf0f8cff2196f40cba11458c98e475a290b623053e6`.
Its primary tables have45/50/33 entries and126 unique destinations including
the common default. Direct300/560 are outside those tables; all128 nondefault
source labels were reconciled in the preceding phase.

The compact staging source combines several physically separate target arms.
Its compiled primary tables have21/24/23 entries and66 unique destinations.
This is a concrete source-shape difference, not evidence that target ownership
or acceptance thresholds should change.

|Diagnostic|Compact staging|Independent cases, one switch|Independent cases, three regions|
|---|---:|---:|---:|
|COFF text including metadata|46640|76745|75836|
|Prefix before first table|45604|75552|74560|
|Decoded direct E8 call sites|656|1109|1095|
|Decoded RET opcodes|135|148|146|
|Aligned to target45/50/33 primary tables|No|No|Yes|

These prefix sizes include alignment up to the first table. They are not
accepted callable boundaries. Target has1188 decoded direct calls to32
addresses,153 RETs and11 proved switch dispatches. The raw manifest's1191/35
counts include three previously documented false-positive E8 bytes; do not
use those raw counts as decoded calls. The final expanded candidate retains
five indirect switch jumps, rather than all11 target dispatches.

Three explicit source regions, preserving the target's shared550/551 arm,
produce45/50/33 primary groups,126 unique destinations and zero target-group
splits with the unchanged official mapper. No candidate-count override or
manifest edit is used for this result. The original compact source and its
old adapters remain unchanged. All generated C++/headers/objects stay in
`build/`.

## Reproducible probe

```bash
python3 scripts/probe-reimu-action-source-shape.py
python3 scripts/audit-reimu-high-final-actions.py build/reimu-action-source-shape/ReimuActionStateDispatch.obj --cohort integration --cohort branches --cohort unresolved740
```

The probe verifies the exact executable, loads canonical target groups,
flattens only known source fragments, parses outer labels without confusing
nested sequence switches, and requires the complete target key set. It copies
each ordinary C++ case body, substitutes its fixed selected action, and emits
separate low/mid/high switches. Keys sharing a target owner retain one source
body; different input bodies for a shared owner fail closed. No assembly,
byte arrays, inert locals, guessed callback results or relocation edits are
introduced. The generated method deliberately keeps its existing bool staging
interface, >798 handoff and740 unknown-path returns. This is a compiler probe,
not a selected complete root implementation.

`--emit-only` produces the same generated source/header without compilation.
Output paths must resolve below `build/`. `receipt.json` pins source/fragment/
header/object hashes, default compiler, compiler environment and compile script;
`mapping.json` contains the unmodified mapper result. Normal AGENTS preflight
and final CI gates still apply when using the findings to change repository
state.

VC8 SP1 `/O2 /GS- /GR /EHsc /MT`, default FP, produced the75836-byte object
SHA256 `b1d4cf3f1b5ed6197c33a90ab833cc9186f51db0a2d0a8f3b564815cc1d92c2f`.
The generated source was built from0cfab49. **0/894 native differences**,
input SHA256 `f101415b752b8cd5facf0149380ad753c0bfefdbb89f4fcf3224c7e250cf48bf`,
cover852 earlier-path cases,34 required-site cases and8 unresolved740 boundary
cases. Stops are773 actual RETs,75 objects,30 effects,6 common entries,1 set669
and9 pending. Both preceding private expansion forms also pass this focused
894-case matrix. Old source, headers, compiler profiles and accepted objects
are untouched; no full historical matrix or aggregate cold replay is needed.

## Remaining differences

The standard full comparator correctly blocks the staging symbol until a
complete call/data relocation contract exists: first its wrapper names, then
unmapped `__real@40900000`. This is not an exact comparison result. A separate
read-only diagnostic uses the same target-checked literal/call bindings as the
native oracle and the canonical COFF resolver. Its first unequal byte is+8
at478FA8: target SUB ESP,570h, candidate SUB ESP,5A8h. It also differs in live
register choices, bool returns, code sharing, call count and mode lowering.
No stack padding or dead locals should be added to imitate the target frame.

The existing owner instruction/edge comparator, paired by the unchanged
primary maps, finds **0/127 identical owners including entry**. This grants no
partial exact credit. Largest physical span deficits are:

|Action|Target span|Candidate span|Deficit|
|---|---:|---:|---:|
|513|1889|875|1014|
|510|1749|765|984|
|512|1844|875|969|
|511|1719|765|954|
|711|1524|770|754|
|710|1573|844|729|
|720|1451|966|485|
|730|1320|862|458|

These are mapper spans to the next primary destination, not new compiler
boundaries. Eight arms explain6347 bytes of the6990-byte pre-table deficit
before other positive/negative span changes. Their compact loops/mode
expressions, target-expanded requests and cross-call reload order are the
next source-shape questions. Explicit source repetition versus compiler/LTCG
expansion remains an inference to test, not established provenance.

740's undefined-stack paths, returning world/backend contexts, original void
ABI, later defaults, full relocation contract and all81550 canonical bytes
remain root acceptance requirements. Candidate/origin/name/source selection
stay authored/unclassified/declaration-only. No ledger, source-present count,
match unit or exact total changes. Wrong-target IDA supplied no semantics;
analysis uses the canonical PE and prior independently attested evidence.
Rejected expansion source/objects and caches are cleaned after recording
receipts; the current reproducible probe is retained.
