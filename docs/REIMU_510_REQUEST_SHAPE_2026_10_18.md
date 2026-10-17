# Reimu510..513: explicit request sequences

## Target evidence and source change

Target remains original Japanese TH10.5 v1.06a, SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Parent `Reimu_dispatch_action_state_vslot28 @478FA0` remains81550 bytes,
root SHA256 `dbf6f375a809fea91cbbccf0f8cff2196f40cba11458c98e475a290b623053e6`.
Candidate/origin/name/source selection were rechecked: authored,
unclassified/declaration-only. No root source-present or exact credit.

Four bodies `[483375,484F96)` contain7201 bytes/1700 instructions, SHA256
`8aa87ea6f50a35365e2bae72a83c6806edd0fe30ed833f0285fe6a32e2d6f2d8`.
Current PE bytes and all retained instruction encodings were rechecked.
Each body has12 separate calls to465190, with ordered812 payloads:

|Live signed WORD736|Angles; speed15, final float0|
|---|---|
|0|30,0,-30|
|1|45,15,-15,-45|
|2|60,30,0,-30,-60|

The old wide branch in `ReimuActionStateMid500Cases.hpp` used three angle
loops. It now spells out each request. Each group has one real float[3];
all three elements are assigned again before every subsequent call. Each
request re-reads current x,y and facing. Separate level tests remain after
returning requests; changing them to else-if is not equivalent when an opaque
callee changes the actor. Ground offsets remain114/96 and aerial50/108.
Charge/landing/cutoff/helper order and non-wide500..508 bodies are unchanged.
Only the main dispatcher includes this changed fragment; the six earlier
adapters and accepted units do not depend on it. No ABI/header/profile or
relocation-ledger change was made.

This is ordinary C++ derived from target payload/store/control-flow facts.
Original source spelling versus compiler unrolling/LTCG expansion remains
unknown. Equal call counts or close spans are not exact evidence.

## Compiler and runtime checks

```bash
scripts/compile-unit.sh src/characters/ReimuActionStateDispatch.cpp build/reimu-510-shape/ReimuActionStateDispatch.obj
python3 scripts/probe-reimu-action-source-shape.py --output-dir build/reimu-510-shape/expanded
python3 scripts/audit-reimu-510-request-shape.py build/reimu-510-shape/ReimuActionStateDispatch.obj
python3 scripts/audit-reimu-510-request-shape.py build/reimu-510-shape/expanded/ReimuActionStateDispatch.obj
python3 scripts/audit-reimu-510-request-packets.py build/reimu-510-shape/expanded/ReimuActionStateDispatch.obj
```

A fresh74fd463 baseline expanded build passes0/36 smoke. VC8 SP1
`/O2 /GS- /GR /EHsc /MT`, default FP, produces current objects SHA256:

- Main compact staging: `5b211b8df5f6ac213390a284692de02561ab916d28741c98224b9c82172312a8`.
- Three-region source probe: `aa62d305fb39b53ff534a0f33b095b7d2e1aa39003eafc0c6bde0ded76c49d3e`.

Both pass **0/3061 native differences**, input SHA256
`a014e7d0447ceb2c0179231f24005a4a51e306ec64164ca432478aedcacb3f35`.
The matrix has336 motion,600 first-request,864 charge/input,288 tail,
24 required-site,948 earlier/current-root integration and1 default case.
Stops are2357 genuine RETs,447 real object entries,248 effects,7 common entries,
1 set669 and1 pending. Full actor bytes, ordered native calls/arguments,
pointed first payloads, actual manager/world/MT state and x87 control word are
compared; RET restores stack/registers/TOP. Earlier oracle classes are reused
without global mutation. No full historical matrix or aggregate cold replay.

The three-region probe keeps45/50/33 primary groups,126 unique destinations
and0 target-group splits under the unchanged mapper. Its text including
metadata grows75836->79980; prefix before the first table74560->78704.
Decoded E8 calls grow1095->1131; target has1188. RET count remains146 versus153.
The first diagnostic mismatch remains478FA8, frame570h versus5A8h. Prefixes
and mapper spans include alignment; they are not newly accepted boundaries.

|Action|Target span|Before|After|
|---|---:|---:|---:|
|510|1749|765|1805|
|511|1719|765|1805|
|512|1844|875|1855|
|513|1889|875|1855|

These four target spans total7201; candidate grows3280->7320. Changes elsewhere
in allocation/branching/alignment also contribute to the4144-byte prefix growth.
The remaining pre-table deficit is2846 bytes. No byte/edge equality is inferred.

## Static coverage beyond the first callback

Native execution still stops at the first real world request. The new
`audit-reimu-510-request-packets.py` separately checks **all48 target and48
candidate sites** without executing or returning a callback. It starts each
request's basic-block analysis with unknown registers, stack and x87 values,
apart from symbolic ESP and the attested ESI receiver. Only locally established
stack-pointer/count/payload definitions are accepted. Every site must supply
812/count3 and the expected12 payload bytes, with fresh actor EC/F0/104 reads.
Each group's level load must be reached after the preceding group's final
call, before another branch/call can bypass it; only direct transfers are
followed. Narrow/overlapping writes invalidate previous definitions. Unsupported
x87 operations fail closed. Reports pin the target/object, tool/mapper/manifest
hashes and Capstone version.

The current candidate passes all48 constraints and12 level-load checks. The
baseline has only3 request sites per action and is rejected. This proves local
request preparation/control properties, not callback effects or full-volley
execution. Coordinates' full floating expressions and whole function behavior
still need their broader native/canonical contracts.

Three compiled single-action510 negatives all pass the first-request0/36
native smoke, demonstrating that this smoke cannot detect their later changes:

|Source change|Static rejection|
|---|---|
|Second angle0->5|One payload differs|
|Omit second request's speed reset|One speed lacks a local definition|
|Second level test becomes else-if|Two packets rejected, including the missing post-group0 level reload|

The else-if compiler also moves some float definitions outside the local
blocks, so those values remain unproved rather than being reported as wrong
runtime values. Native and static evidence stay distinct. No target bytes,
helper outputs, callback returns or actor outputs are fabricated.

`build-analysis-receipt.json`, native/static reports and control-build receipt
are below `build/reimu-510-shape/`. The prior direct Ghidra510 receipt is reused
after rechecking target entries/instructions and all9 unchanged primary DB
hashes; no new process/clone or IDA semantics. Superseded source probes,
baseline/control objects and caches are removed; current two objects and
bounded evidence remain. Next attack710/711/720/730 mode/request lowering,
then reconcile740 undefined paths, full void/default ABI, returning world
contexts, full relocations and truthful VC8/LTCG/TU provenance before exact
acceptance of all81550 bytes.
