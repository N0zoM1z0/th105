# Reimu:520..531 middle families

## Target observations and source hypothesis

Target is original Japanese TH10.5 v1.06a, SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Parent `Reimu_dispatch_action_state_vslot28 @478FA0` remains81550 bytes,
ending48CE2E, SHA256
`dbf6f375a809fea91cbbccf0f8cff2196f40cba11458c98e475a290b623053e6`.
Candidate/origin/name/source selection were rechecked: authored,
unclassified/declaration-only. No implementation or exact entry is added.

Eight physical bodies occupy `[484F96,486487)`:5361 bytes/1277 instructions,
SHA256 `4534b9569839deafb2eafa0ff77be31e4aed51406f942a88df890f323140c955`.
Canonical table destinations and every body hash are checked.

|Action|Entry|Next physical entry|
|---|---|---|
|520|484F96|485307|
|521|485307|485621|
|522|485621|4859F1|
|523|4859F1|485DD1|
|525|485DD1|48602D|
|526|48602D|48626E|
|530|48626E|486383|
|531|486383|486487|

`ReimuActionStateMid520Cases.hpp` joins the same monolithic entry/low/middle
method, now through531. Gaps still call real4740C0; larger actions remain
pending. Its bool remains a staging interface, not the full void-root ABI.

520..523 publish BYTE+17C=1, consume200/floor120, publish state1 and add
scaled50 before object815 requests. The fire gate is sequence3/DWORD
counter0 before animation advancement, independent of timer/frame. Ground
positions are x+signed-facing114,y+96; aerial positions are
x+signed-facing43,y+107. Initial smoke exposed an incorrect aerial50; all
five original sites in each aerial body use IMUL2B. This is corrected.

The first payload is `[0,12,0]`, or `[0,25,0]` for521/523. Four subsequent
trajectories use real atan2 and sqrt helpers; near/far speeds are separately
rounded and cached after division by double15. The second payload sets
third float2; subsequent requests leave it live and restore cached speeds.
Every request re-reads coordinates/facing, and wave21 follows all five.
Aerial sequence4 applies0.6f gravity; crossing before sequence5 reuses
47FFA2 zero/height/set5/RET. Sequence5 node entry sets9:522 reuses48748C,
whereas523 has its own485DBE path. Both are required by the audit.

525/526 publish17C=5. Sequence1 counter>10 or sequence2 counter>50 advances
the block and returns before animation advancement. Sequence0/timer0/frame7
after advancement consumes200/floor120, adds scaled50, then publishes state1.
Object816's zero pair uses peer x minus/plus signed-facing50,peer y+125;
the second direction negates only the unsigned low byte. Its vertical pair
uses `[90,30,4]` at peer y+50, then changes only angle to-90 at peer y+150.
525 sends the zero pair first, then the vertical pair if signed BYTE+609>=4;
526 reverses the groups. The live test follows the preceding requests.
Wave5 follows all requests. The offset-proved signed byte is exposed in
the private staging view without changing its size or existing offsets.

530/531 publish17C=9 and advance/return at sequence1 counter>=18 before
animation advancement. Completion sets action0 for530 and2 for531. Their
sequence1 node entry consumes200/floor120, adds scaled50, then publishes1.
Object817 receives argument5=-1 and three floats:530 `[0,0,0]` at
x+signed-facing10,y-10;531 `[0,20,9]` at x+signed-facing50,y-10. Wave15
follows the request. Raw unsigned facing remains distinct from signed
coordinate multiplication.

## Focused build and execution

```bash
scripts/compile-unit.sh src/characters/ReimuActionStateDispatch.cpp build/reimu-mid-late/ReimuActionStateDispatch.obj
python3 scripts/audit-reimu-mid-520-actions.py build/reimu-mid-late/ReimuActionStateDispatch.obj
```

A fresh pre-edit object passes the previous510 smoke0/36. Pinned VC8 SP1
`/O2 /GS- /GR /EHsc /MT`, default FP/no injected compiler environment,
produces26279 staged text bytes, object SHA256
`58eb45ead04f36384709a030d04ad7f3f9890d2694e35b440a54927871b07d2a`.
Compiler/source/header/object hashes and the separate previous-commit
baseline are in `build/reimu-mid-late/build-receipt.json`. The oracle pins
its own inputs and does not itself attest compilation provenance.

**0/3362 differences**, `build/reimu-mid-late/native.json`, input SHA256
`1a292eaf5403c5128e388624335d7ea7172950006f26b520db2fcb5b83286785`:

|Cohort|Cases|
|---|---:|
|Sequence/landing/completion/NaN motion|672|
|First requests, facing extremes and scaled phases|1320|
|Pre/post-advance counter boundaries|60|
|Sequence/counter/timer/frame gates|864|
|12 required original sites at both x87 precisions|24|
|Earlier510/500/shot/projectile/middle/low/entry/common paths|409|
|Middle gaps/defaults|6|
|Later source handoffs|7|

1922 cases reach genuine RET;1399 stop at real object465190,18 at effect
435240,12 at common4740C0 and1 at set669. Another10 compare original pending
state with a genuine source false return.5693 original-root and3220 staged
instruction addresses are sampled. The inherited engine compares4096 actor
bytes, ordered helper/receiver/argument traces, conversion inputs, world
scalar, MT state and control word. Returns require stack delta4, preserved
callee-saved registers and x87 TOP=0. First815/816/817 requests require their
actual ID,17C flag, aligned live stack pointer, count3 and all12 pointed bytes.

Only the first actual world request is reached. Subsequent815 trajectory
math, later816 pairs, the signed609 gate and post-request waves have raw
instruction evidence, not dynamic returning-call proof. The existing
`sqrt_float_value @478DD0` symbol is bound to its18 target bytes but never
executed here; neither its CRT continuation nor later math is claimed as
verified by these cases. No callback return is fabricated. The supplied
read-only animation, flat surface, zero wave/texture/event handles, inactive
secondary-event cycle and masked PC53/PC64 constrain the proof. Complete
world contexts, floating exceptions and whole-game behavior remain unknown.

Compiled wrong-source controls each fail2/64 smoke cases: aerial y107->108,
fast first speed25->12, and pre-advance >=18->>18. Reports and pinned private
build receipts are in the same directory. These use ordinary modified C++
and VC8, without target-byte or helper-result patches. Rejected sources and
objects are removed after inspection.

## Preservation, analysis and next work

All six prior adapters rebuild with identical non-debug code/data and
relocation offset/type/symbol/value/section identities, sizes530,771,1562,
4017,4409,11271; `preserved-stages.json`. Focused smokes pass0/9,0/88,0/64,
0/99,0/150,0/59. The409 integration cases include previous510 and500 smokes.
Full historical matrices are not repeated. No accepted unit depends on this
private header; accepted source/profile/relocation ledgers and exact totals
are unchanged. No aggregate cold replay or canonical-exact result is claimed.

One direct Ghidra read-only clone independently attests executable SHA,
entry68B9D2, base400000, Windows x86, mapped.text/full-root bytes and all
instruction starts, then reads back current and adjacent entries/shared
exits. `REIMU_MID_LATE_READBACK_PASSED` is retained in `ghidra.log`. All9
primary DB hashes are unchanged; clone removed. Wrong-target IDA contributes
no semantics. Only the eight bodies above are implemented in this batch.

Adjacent boundary evidence:550 and551 share48749F. Their1132-byte body ends
48790B, followed by364 bytes for direct560, then30 selector bytes before
high561 at487A95. Do not assign the entire former provisional span to550.
Next continue540/541/545/546/550/551/direct560 and high actions. Returning
world contexts, faithful complete void ABI, full CFG/relocations, VC8/LTCG/TU
provenance and all81550 canonical bytes remain root acceptance requirements.
