# Reimu710/711: independent aimed mode loops

## Target facts and source shape

Target remains original Japanese TH10.5 v1.06a, SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Parent `Reimu_dispatch_action_state_vslot28 @478FA0` is81550 callable bytes,
SHA256 `dbf6f375a809fea91cbbccf0f8cff2196f40cba11458c98e475a290b623053e6`.
Candidate/origin/name/source ledgers were rechecked: authored,
unclassified/declaration-only. No source-present or exact credit is added.

The two primary owners `[48B034,48BC4D)` contain3097 bytes/791 instructions,
SHA256 `21e61620a04245a0ff822d7fc94397d3f0adc7a9f920f1742bc50d5ad29ec202`.
Every retained instruction encoding and body byte was checked against the PE.
Both actions have independent four-way mode switches, laid out3,2,1,0:

|Action|Mode|Count|Spacing|Aim offset|
|---|---:|---:|---:|---:|
|710|0|3|120|0|
|710|1|4|90|0|
|710|2|6|60|0|
|710|3|8|45|0|
|711|0|3|60|60|
|711|1|4|60|90|
|711|2|5|45|90|
|711|3|6|36|90|

`ReimuActionStateHighLateCases.hpp` now expresses these eight loops instead
of selecting constants inside one shared loop. Each action shares one mutable
float[3] across its four mutually exclusive modes. Every iteration resets all
three parameters and re-reads peer/self coordinates and signed facing.
The first parameter is float32 of `i*spacing + (-atan2_result-offset)`;
the other two are4 and positive zero. The float32 atan2 arguments and spawn
coordinates are inline call arguments. This source order lets VC8 compute
atan2 before the counter product and evaluate direction/y/x as in the target,
without the earlier temporary-coordinate spills. Motion, snapshot restoration,
gravity, landing/completion and common frame3 tails are unchanged. Modes above3
still skip the volley. No accepted header/layout/profile/relocation changes.

This is a source-shape hypothesis supported by original instructions. It does
not identify the original spelling, an LTCG partition or an exact compiler
boundary. The bool staging entry still leaves740's undefined paths and the
original void/default ABI unresolved.

## Compiler and native checks

```bash
scripts/compile-unit.sh src/characters/ReimuActionStateDispatch.cpp build/reimu-mode-shape/ReimuActionStateDispatch.obj
python3 scripts/probe-reimu-action-source-shape.py --output-dir build/reimu-mode-shape/expanded
python3 scripts/audit-reimu-aimed-mode-shape.py build/reimu-mode-shape/ReimuActionStateDispatch.obj
python3 scripts/audit-reimu-aimed-mode-shape.py build/reimu-mode-shape/expanded/ReimuActionStateDispatch.obj
python3 scripts/audit-reimu-aimed-mode-loops.py build/reimu-mode-shape/expanded/ReimuActionStateDispatch.obj
```

A fresh33e4e3d baseline expanded build passes0/26 smoke. VC8 SP1
`/O2 /GS- /GR /EHsc /MT`, default FP, produces these current objects:

- Main compact: `8cbe855875fe4f48345e72856987b3a6233add5968be962fe416fd1b9c229ebb`.
- Three-region probe: `26554921bfa3139ba20a30caea230bf8e0b3e441e8ebb7b29fae0d5390a53e26`.

Both pass **0/2372 native differences**, input SHA256
`fab8e2692f3ca05c9a31ee058dd0105a4a03fd969fea1285a911c6297949edfe`.
The matrix covers216 motion,576 nodes,600 patterns,12 snapshots,20 branch
boundaries and948 integration cases. Stops are1855 genuine RETs,479 object
entries,30 effects,6 common entries,1 set669 and1 pending. Actual helpers,
actor/world state, ordered calls/arguments, first pointed payload and x87 state
are compared; RET checks stack, saved registers and TOP. World execution stops
at the first real request. No returning callback or whole-volley claim.

Old current-object checks still pass0/96 final-action smoke,0/36 510 smoke
and all48 510 static packets/12 level reloads. No old full matrix or aggregate
cold replay was run.

The three-region mapper still finds45/50/33 primary groups,126 destinations
and0 target-group splits. Text including switch data grows79980->81652;
the prefix before its first table grows78704->80344. Decoded E8s grow1131->1158
versus target1188; RETs remain146 versus153. There are7 indirect switches
versus target11. First diagnostic mismatch remains478FA8: frame570h versus5A8h.

|Action|Target layout span|Before|After|
|---|---:|---:|---:|
|710|1573|844|1576|
|711|1524|770|1570|

The two candidate spans total3146 versus target3097. The pre-table deficit
is now1206 bytes. These spans include alignment and are diagnostic quantities,
not equality evidence or accepted function boundaries.

## Static loop contracts and limits

`audit-reimu-aimed-mode-loops.py` separately checks all eight target and eight
candidate loops. It requires one four-way table and one natural backedge per
mode, a positive-zero counter, counter+1, the ordered finite upper-bound
predicate, one atan2/sine/cosine/spawn sequence,900/count3/argument5=1, an aligned
local parameter array, all three payload definitions, and fresh coordinate/
facing loads within each iteration. The counter cannot overlap the payload.
All16 rows satisfy the constraints. Neither final target nor candidate carries
the counter across the loop in x87. Target/source710 arrays both useESP+3C;
711 usesESP+30 versusESP+48, an outstanding layout difference.

The checker carries an unvalued float32 atan2 result and unknown sine/cosine
and object results; it executes no callback and supplies no concrete result.
It applies the observed RET1C and volatile-register ABI, invalidates exposed
parameter storage, and checks the loop state invariant. Symbolic algebra is
limited to finite angles under nearest rounding at PC53/PC64. It retains
addition grouping and literal positive/negative zero; only bounded integer
counter increments/products drop redundant stores. Sign symmetry and
commutative operations normalize the observed source/target expressions.
NaNs, exceptions, arbitrary precision modes, full coordinate expressions and
callback effects are outside this contract. Native first-request evidence
and static subsequent-iteration constraints remain separate.

Two compiled single-mode710/3 controls demonstrate the native stopping limit:

|Mutation|First-request native patterns|Static result|
|---|---|---|
|Spacing45->36|0/600 differences|Reject source710 mode3|
|Count8->6|0/600 differences|Reject source710 mode3|

Both mutations leave the first iteration unchanged. No helper return or
target bytes were altered to manufacture later execution.

The expanded object's81652 text bytes include102 bytes beyond the old
81550 fixture ceiling. Only the new contract opts into reviewed switch data:
the unchanged official mapper validates the target tables, candidate primary
groups and first-table offset. Executable prefix80344 must stay within81550;
total mapped text must stay within the original reviewed metadata end48D38C
(82924 bytes from entry). Execution into extended data is rejected. The real
helper overlap check remains unconditional. Older contracts still reject this
large object. This fixture accommodation changes no canonical comparator,
ledger or accepted compiler boundary. Seven extent tests exercise opt-in and
overflow rejection; three symbolic tests cover signed zero, rounding and
addition grouping.

Reports, target packet, control/build receipts and reused analysis identity
are below `build/reimu-mode-shape/`. The earlier direct Ghidra receipt was
reused after PE checks and all9 unchanged primary DB hashes; no new Ghidra
process/clone or IDA semantics. Superseded baseline/control/experimental objects,
temporary source copies and caches are removed; current objects and bounded
evidence remain. Next prioritize720/730 mode/request lowering, then740's
undefined paths, original void/default ABI, returning world contexts and full
relocation/VC8/LTCG evidence before canonical acceptance of all81550 bytes.
