# Reimu: shared550/551 and direct560

## Target observations and source hypothesis

Target is original Japanese TH10.5 v1.06a, SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Parent `Reimu_dispatch_action_state_vslot28 @478FA0` remains81550 bytes
through48CE2E, SHA256
`dbf6f375a809fea91cbbccf0f8cff2196f40cba11458c98e475a290b623053e6`.
Candidate/origin/name/source selection were rechecked: authored,
unclassified/declaration-only. No implementation or exact entry is added.

Shared550/551 is `[48749F,48790B)`,1132 bytes; direct560 is
`[48790B,487A77)`,364 bytes. Together:1496 bytes/378 instructions, SHA256
`215a13617e9b7d8e1fe95ecb937377e5566936580c34917c7b0f863d5553a562`.
The30-byte high selector begins487A77; first high body561 begins487A95.
These are separate control-flow regions, not a1526-byte550 body. Canonical
550/551 table entries and all bounded instructions are rechecked.

`ReimuActionStateMid550Cases.hpp` joins the same monolithic entry/low/middle
method. All50 non-default middle keys now have source labels for49 physical
bodies; direct560 is also covered. `middle-coverage.json` checks these keys
against the canonical table. Gaps call real4740C0; >560 stays pending. This
is source-branch coverage, not complete semantic acceptance or exact credit.
The bool interface remains a staging aid rather than the complete void ABI.

550/551 publish17C=10. A pre-advance sequence2 node sets horizontal-2.
Sequence0 calls landing; state==3 clears state, advances the block, dispatches
wave18 and returns before animation advancement. Sequence1 uses signed WORD
timer `%3==0` before advancing. Timer<=9 includes negative multiples of3.
Eight ring requests use a float loop index and a real random roll45, with
parameters `[float(unsigned-roll + index*45),0,4,0]`. Only the first float
is rewritten per iteration; the remaining three remain live across requests.
Radius is signed timer*20, with sine then cosine calls; coordinates are
y+sin(angle)*radius+100 and x+cos(angle)*radius*signed-facing. Direction is
the original unsigned facing byte. The existing accepted
`selector_random_roll(int) @4067D0` interface is reused, with an explicit
unsigned conversion at this call site as required by the target instructions.
It is division-based, not a substituted modulo operation.

If the live timer is0 after those eight returning requests, a5x5 grid follows.
Sector/layer are float counters0..4. The trajectory angle is sector*72-90+162,
while the geometry angle is90-sector*72. Each request writes trajectory,
layer*18+8 and layer+30 into floats0/1/3, leaving float2 live after one initial
zero store. Coordinates use geometry sine/cosine at radius250,y+100.
All requests are822/count4/argument5=1. These later-loop lifetimes/order have
raw instruction evidence; no returning manager result is supplied by the oracle.
Instruction tracking shows temporary x87 operands are popped before request
calls. The shared oracle's TOP=0 rule is unchanged.

Sequences2/3 subtract accelerationY. Crossing sets action10 before surface
height, zero motion and alphaFF, then RET. Otherwise alpha adds10 while <245,
and clampsFF at>=245. After normal animation advancement, sequence1 node
sets0/RET; sequence2 node sets horizontal-200,y+100,vertical2,alpha0,AY0.5.
Sequence0/frame3/timer0 consumes200/floor120 and adds scaled50.

560 calls landing only in sequences0/3, publishes17C=3, and subtracts AY in
sequences1/2. It calls crossing detection unconditionally; crossing with
signed sequence<3 does zero motion, height, set3 and RET through47FA23.
After advancement, sequence0/frame3/timer0 sends825 `[0,12,0]`,count3,
argument5=1; wave7 follows the returning request. Sequence1 node consumes
200/floor120, adds scaled50, then sets velocities4.5/14 and AY0.75.
Compact C++ loops and shared branches remain source-shape hypotheses; original
TU spelling, compiler expansion/sharing and complete provenance are unproved.

## Focused build and execution

```bash
scripts/compile-unit.sh src/characters/ReimuActionStateDispatch.cpp build/reimu-mid-550/ReimuActionStateDispatch.obj
python3 scripts/audit-reimu-mid-550-actions.py build/reimu-mid-550/ReimuActionStateDispatch.obj
```

Fresh pre-edit540 smoke passes0/40. Pinned VC8 SP1 `/O2 /GS- /GR /EHsc /MT`,
default FP/no injected compiler environment, produces30180 staged text bytes.
Final object SHA256
`69ce2d497ff7dc170b46447ca26eb6c5cf40250aebec2db2bb98e53314841f2f`;
compiler/source/header/object hashes and the separate previous-commit baseline
are recorded in `build/reimu-mid-550/build-receipt.json`. The oracle pins its
own inputs but does not itself attest compilation provenance.

**0/2665 differences**, `build/reimu-mid-550/native.json`, input SHA256
`4ff70fd2660f2120fd28bc8c156e806827a4672800c3fb785575729e7aad694e`:

|Cohort|Cases|
|---|---:|
|Sequence/landing/completion/NaN motion|324|
|Signed ring timers, facing extremes, three seeds and both precisions|480|
|Timer/frame/counter gates|648|
|Alpha thresholds, crossing and both precisions|144|
|State/node/resource gates|432|
|825 payload/direction/counter/phase profiles|90|
|11 required original sites at both x87 precisions|22|
|Earlier540/520/510/500/middle/low/entry/common paths|513|
|Gaps/defaults|5|
|High handoffs|7|

1875 cases reach genuine RET;751 stop at actual465190,18 at effect435240,
11 at common4740C0,1 at set669 and9 at the high-source handoff.6698 target
and3942 staged instruction addresses are sampled.624 random-roll/MT calls,
618 sine/cosine pairs,91 resource/scaled-counter and56 wave calls execute
actual native helpers. The engine compares4096 actor bytes, ordered calls/receivers/arguments, conversion
inputs, world scalar, all2496 MT bytes/index and control word. Genuine RETs
require stack delta4, saved registers and x87 TOP=0.822/825 requests require
the advertised ID, aligned live stack pointer, count4/3 and all16/12 payload
bytes. Only each first world request is reached. Later ring iterations, the
25 grid requests and returning-manager continuations remain dynamically
unproved. Read-only animation, flat surface, zero wave/texture/event handles,
inactive secondary-event cycle and masked PC53/PC64 bound this proof; complete
runtime contexts and floating-exception behavior remain unknown.

Compiled wrong-source controls fail2/36 for rejecting negative ring timers,
16/144 for alpha threshold245->235, and1/36 for825 speed12->15. Reports and
private build receipts are retained in the same directory. Controls use real
VC8 C++, without target-byte/helper-result patches. Rejected sources and
objects are removed after inspection.

## Preservation and remaining work

All six older adapters rebuild with identical non-debug code/data and
relocation offset/type/symbol/value/section identities, sizes530,771,1562,
4017,4409,11271. Focused smokes pass0/9,0/88,0/64,0/99,0/150,0/59. The513
integration cases include prior540/520/510/500 smokes. Full historical matrices
are not repeated; accepted units do not depend on this private header. No
accepted source/profile/relocation ledger or exact total changes, and no
aggregate cold replay is claimed.

Prior direct Ghidra readback explicitly covers48749F/48790B. It is reused
after checking target/root/body/table/instruction bytes and all9 unchanged
primary DB file hashes; `analysis-reuse.json` pins its log/script. No new
Ghidra process/clone is created. Wrong-target IDA contributes no semantics.
Superseded objects, private controls, the temporary baseline and caches are
cleaned. Next recover high561..798, then actual returning world contexts.
Complete void ABI, full CFG/relocations, truthful VC8/LTCG/TU provenance and
all81550 canonical bytes remain parent acceptance requirements.
