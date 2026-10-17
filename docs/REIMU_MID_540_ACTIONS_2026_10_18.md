# Reimu:540/541/545/546 middle families

## Target observations and source hypothesis

Original Japanese TH10.5 v1.06a SHA256 is
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
`Reimu_dispatch_action_state_vslot28 @478FA0` remains81550 bytes through
48CE2E, SHA256 `dbf6f375a809fea91cbbccf0f8cff2196f40cba11458c98e475a290b623053e6`.
Candidate/origin/name/source selection were rechecked: authored,
unclassified/declaration-only. No implementation or exact entry is added.

Four physical bodies occupy `[486487,48749F)`:4120 bytes/949 instructions,
SHA256 `312add7d42d167574fc464e60be1e38bcb3a42c1930bae54c934559e1d3aa4a6`.
Current PE table indices44..47 and destinations are independently rechecked;
every instruction is decoded again and compared with the pinned packet.

|Action|Entry|Next physical entry|
|---|---|---|
|540|486487|486714|
|541|486714|486A13|
|545|486A13|486F50|
|546|486F50|48749F|

`ReimuActionStateMid540Cases.hpp` joins the existing monolithic entry/low/
middle source. It now handles through546, routes gaps to real4740C0 and
leaves later actions pending. Its bool remains a staging interface, not the
complete void-root ABI. Shared C++ branches/loops are a source hypothesis;
target request sites and visual sequences are physically expanded. Original
source spelling, compiler sharing and complete TU provenance remain unknown.

All four initialize at sequence0/frame4/timer0, before advancing animation:
fields108/10C become0/100, scales11C/120 become1, bytes113..110 becomeFF,
then wave6 dispatches. Sequence0/frame>3 shrinks scale11C only while >0,
grows120 and subtracts25 from unsigned byte113 only while >25. Scale2
restoration adds/subtracts the same double literals and adds25 with byte
wrap; otherwise both scales clamp1 and alpha becomesFF. NaN scale takes
the clamp branch during restoration. The shrink/grow literals are doubles
holding widened0.1f/0.2f, preserved explicitly in source. Private fields are
offset-asserted; existing member offsets and prefix size remain unchanged.

540 lands only in sequence4 and publishes17C=2. Sequence2 restores visual
state while frame<5 and subtracts widened0.7f gravity while frame<7.
Sequence3 crossing does height, zero motion, next block, RET before advancing.
After advancement, sequence2 node entry consumes200/floor120, relocates to
**peer x-facing180**,y200, sets velocities6/8 and dispatches wave6. Its
frame7/timer0 sets velocities7.5/-24 and adds scaled50.

541 lands in sequences3/4/5 and publishes17C=2. Sequence2 subtracts double1,
restores visual state, and crossing resets scales/alpha, sets surface height,
zeroes only vertical velocity, sets sequence3 and continues. In sequence3,
nonzero state increments signed WORD734 with wrap and clears state/counter
only after >5; counter144>15 advances the block and sets BYTE184=1. A
subsequent sequence4 test can increment again in the same update. Sequence>3
subtracts widened0.8f horizontal speed and clamps only negative results0.
After advancement, sequence1 node entry consumes200/floor120, moves
**self x+facing100**,y50, sets velocities15/6, dispatches wave6 and adds
scaled50. It does not read peer x for this displacement.

545/546 land only in sequence6 and publish17C=6. Sequences2..5 subtract
current accelerationY; crossing does height, zero motion, set6 and RET.
Sequence3 counter>=8 advances/returns before animation advancement. Node2
consumes200/floor120, adds100 to y and caps it at350, then sets velocities
5/15 and accelerationY0.5.546 additionally subtracts facing320 from self x
and uses horizontal-5. Wave6 precedes object821 `[0,0,3]`, argument5=-1,
at current x,y+100. Node3 dispatches wave14 and adds scaled50, then loops
i=0..5: a live signed BYTE60A>=4 adds an extra ray for i<=4 before each
regular ray.545 extra/regular angles are i*9+34.5 / i*9+30;546 uses
35.5-i*9 /40-i*9. Speeds are22/25, third float0. Each request recomputes
negative-angle sine then cosine, coordinates and unsigned direction. A final
`[0,0,4]` object precedes state1. Node5 sets9 through47EDAB for545 and48748C
for546. All these later-request details have raw instruction evidence.

## Focused build and execution

```bash
scripts/compile-unit.sh src/characters/ReimuActionStateDispatch.cpp build/reimu-mid-540/ReimuActionStateDispatch.obj
python3 scripts/audit-reimu-mid-540-actions.py build/reimu-mid-540/ReimuActionStateDispatch.obj
```

Fresh pre-edit520 smoke passes0/64. VC8 SP1 `/O2 /GS- /GR /EHsc /MT`,
default FP/no injected compiler environment, produces28646 staged text
bytes, object SHA256
`b9df3026b4a951d6cf488532f4f1e14d8ec874c76e13f1e70032baefe9d0e467`.
`build/reimu-mid-540/build-receipt.json` pins compiler/source/header/object
hashes and the separately identified previous-commit baseline. The oracle
pins its own inputs, without claiming compilation provenance itself.

**0/5807 differences**, `build/reimu-mid-540/native.json`, input SHA256
`c3a46d1d479a189490f7e3a33740432ef1c2082a8f45645c37d79f18740080ef`:

|Cohort|Cases|
|---|---:|
|Sequence/landing/completion/NaN motion|432|
|Scale/NaN/infinity/alpha thresholds and byte wrap|3584|
|Counter/timer/frame/node gates|504|
|Launch coordinates, facing extremes and height cap|200|
|Signed skill thresholds, first fan requests and phases|360|
|541 state, WORD wrap and block transitions|216|
|13 required original sites at both x87 precisions|26|
|Earlier520/510/500/middle/low/entry/common paths|473|
|Gaps/defaults|5|
|Later source handoffs|7|

5256 genuine RET cases,511 real465190 request-entry stops,18 effects,
11 common entries,1 set669 entry and10 pending handoffs are compared.
6575 original-root and3773 staged instruction addresses are sampled.
366 sine/366 cosine,251 resource-consumption,462 scaled-counter and1051
wave calls execute actual native helpers, with no fabricated return values.
4096 actor bytes, ordered calls/receivers/arguments, conversion inputs,
world scalar, MT state and control word are checked. Returns require stack
delta4, preserved callee-saved registers and x87 TOP=0.821 requests check
ID,17C=6, aligned live stack pointer,count3 and all12 pointed bytes.

The360 fan cases reach the actual first optional/regular ray according to
signed skill60A; launch cases reach the node2 request. Later loop iterations,
remaining objects, state1 after returning manager calls and other opaque
continuations remain dynamically unproved. Read-only animation, flat surface,
zero wave/texture/event handles, inactive secondary-event cycle and masked
PC53/PC64 constrain this proof. Complete world contexts, floating exceptions
and whole-game behavior remain unknown; no full-root/canonical-exact claim.

Compiled wrong-source controls fail: alpha decrement25->24 gives8/40;
541 self x->peer x gives50/200 launch cases;545 first regular angle30->40
gives1/40. Reports and private build receipts are retained in the same
directory; rejected sources/objects are deleted after inspection.

## Preservation and remaining work

Six older adapters rebuild with identical non-debug code/data and relocation
offset/type/symbol/value/section identities, sizes530,771,1562,4017,4409,11271.
Focused smokes pass0/9,0/88,0/64,0/99,0/150,0/59. The473-case integration
cohort includes previous520/510/500 smokes; full historical matrices are not
repeated. No accepted unit depends on this private header. No accepted
source/profile/relocation ledger or exact total changes; no aggregate cold
replay is claimed.

Prior direct Ghidra readback explicitly covers all four entries. It is reused
after checking the canonical executable/root/body bytes, table destinations,
every instruction and all9 unchanged primary DB file hashes. Receipt
`analysis-reuse.json` pins the prior successful log/script. No new process
or clone is created. Wrong-target IDA contributes no semantics. Cleanup
removes superseded objects, private controls, the temporary baseline and caches.

Next recover550/551/direct560 and the high actions, then real returning
world contexts. Complete void ABI, full CFG/relocations, truthful VC8/LTCG/TU
provenance and all81550 canonical bytes remain root acceptance requirements.
