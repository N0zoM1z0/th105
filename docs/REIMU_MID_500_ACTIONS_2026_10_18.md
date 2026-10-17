# Reimu: first500 middle family

## Target observations and source

Target remains original Japanese TH10.5 v1.06a, executable SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Parent `Reimu_dispatch_action_state_vslot28 @478FA0` is81550 bytes ending
48CE2E, SHA256
`dbf6f375a809fea91cbbccf0f8cff2196f40cba11458c98e475a290b623053e6`.
Candidate/origin/name/source ledgers were rechecked. The root stays authored,
unclassified/declaration-only, without a new implementation or exact entry.

Eight observed bodies occupy `[4802EA,483375)`:12427 bytes/2910 instructions,
SHA256 `b374e8ccea91eccefea6fe2a49c9384f2b1501dab222427f1a58a62df27a9528`.
Each canonical primary-table index/destination and body hash is verified.

|Action|Entry|Next physical entry|
|---|---|---|
|500|4802EA|4807CF|
|501|4807CF|480C5E|
|502|480C5E|481180|
|503|481180|481680|
|505|481680|481DC8|
|506|481DC8|482485|
|507|482485|482C0E|
|508|482C0E|483375|

`ReimuActionStateMid500Cases.hpp` is directly included in the existing staged
monolithic method. It retains entry/low/earlier-middle source, routes newly
admitted gaps to real common4740C0 and returns pending for>508. Its bool is
not the original complete void-root ABI or a standalone target boundary.

The shared source follows these canonical instruction facts:

- Ground500/501/505/506 call landing unconditionally; aerial502/503/507/508
  call it only in sequence5. BYTE+17C is then written0 for500..503 or4 for
  505..508. Only this observed byte is exposed, with an offset assertion.
- Sequence<=1 clears BYTE+750 if the selected full DWORD input is zero:
  +6C0 for500/502/505/507, +6C4 for501/503/506/508. Signed sequence and full
  input widths are retained.
- Aerial sequence<5 checks crossing; sequence4 first publishes0.6f AY and
  subtracts its double representation. Landing calls zero motion, height,
  set-sequence5 and returns.503/508 reuse their paired explicit landing tails.
- Firing precedes animation advancement: sequence2/timer0 at frame2 on the
  ground or frame1 in the air. It consumes200/floor120, writes state1, adds
  scaled50, then calls wave4 before inspecting signed WORD+736.
- Object810 has speed15 and angle order(+20,-20), then(+20,+40,-20,-40),
  then(+20,+40,+60,-20,-40,-60) for levels0/1/2. The positive and negative
  loops have strict bounds. Each request reinitializes all three floats.
- Object811 has angle/speed pairs shown below, plus a third float0. Level
  checks remain separate live reads after preceding request groups; they
  are not an else-if selection captured before opaque calls.
- Ground coordinates are x+signed-facing114,y+96; aerial coordinates are
  x+signed-facing50,y+108. Every request re-reads position/facing; direction
  is the zero-extended raw facing byte.
- Advance completion calls set-action0 and continues. Aerial sequence5 node
  entry calls set-action9/RET. Sequence1 counter>20 at level0 writes level1
  and emits effect62, then separately checks counter>60 to write level2 and
  clear the held latch. A zero latch advances a block. Sequence3 advances
  only when its signed DWORD counter is>(signed WORD level+1)*10.

|811 level|Ordered angle/speed pairs|
|---|---|
|0|(10,23),(0,25),(-10,23)|
|1|(15,25),(5,27),(-5,27),(-15,25)|
|2|(20,26),(10,27),(0,29),(-10,27),(-20,26)|

Shared post-charge exits are48077D/4807A8 and481D78/481DA1; aerial completion
reuses48748C. These are source inferences from raw instructions and shared
edges, not original source spelling, callable boundaries or TU provenance.

## Focused build and native evidence

```bash
scripts/compile-unit.sh src/characters/ReimuActionStateDispatch.cpp build/reimu-mid-500/ReimuActionStateDispatch.obj
python3 scripts/audit-reimu-mid-500-actions.py build/reimu-mid-500/ReimuActionStateDispatch.obj
```

VC8 SP1 `/O2 /GS- /GR /EHsc /MT`, default FP/no injected compiler environment,
produces23300 staged text bytes. Object SHA256
`f93f762da95a4ff1c314b665f436c5113a676da582788dd618740593e36cea3b`;
manual compiler/source/header/object receipt:
`build/reimu-mid-500/build-receipt.json`. The oracle separately pins object
and support inputs and does not itself attest compilation provenance.

**0/4522 differences**, report `build/reimu-mid-500/native.json`, input SHA256
`61521d939694eb35ef475ccca52d07114cd82b693e9f332af6d8f605154c226c`:

|Cohort|Cases|
|---|---:|
|Sequences0..6, completion, landing and NaN velocity|672|
|First volley request/invalid levels, facing extremes and scaled phases|1200|
|20/60 charge boundaries, levels/latches and distinct full-width input pairs|1728|
|Signed level arithmetic and strict sequence3 cutoff|576|
|17 required target branch sites, both x87 precisions|34|
|Earlier shot/projectile/middle/low/entry paths and real common returns|301|
|New default transfers|4|
|Later source handoffs|7|

3306 cases reach native RET;755 stop at actual object465190 entry,440 at
actual effect435240 entry,10 at common4740C0 and1 at set669. Another10 compare
original pending state at47CC5F against the candidate's genuine false return.
5239 original-root and2881 staging instruction addresses are sampled.

The inherited engine executes real helpers, including1232 scaled-counter
and1223 wave calls; zero handles continue through the actual sound routine.
It compares4096 actor bytes, ordered helper/receiver/argument traces, physical
conversion inputs, world scalar and full MT state. Return cases require
stack delta4, callee-saved registers, x87 TOP=0 and the input control word.

At actual810/811 request entry the probe checks count3, aligned live stack
storage and all12 pointed bytes alongside remaining arguments. It requires
that each valid-level volley fixture really reaches the advertised object
request. Initial BYTE+17C is73 rather than its required0/4 output. Input
pairs distinguish+6C0 from+6C4 and include full DWORD65536.

Only the **first request per volley** executes to its actual entry. No return
is supplied. Later positive/negative loop iterations, later811 angle/speed
pairs, post-manager level changes and effect-returning continuations remain
unproved dynamically. Their source values/order have raw target evidence;
neither full volleys nor the complete root are claimed equivalent.

Compiled wrong-source controls are rejected:

- Swap the two input fields:640/1728 charge cases differ.
- Change811 level0's first speed23 to25:2/72 smoke cases differ.
- Change counter>60 to>=60:208/1728 charge cases differ.

Reports are `wrong-input.json`, `wrong-speed.json`, `wrong-cutoff.json` in
the same build directory. Controls use ordinary C++ and the pinned compiler
with a private include directory; their source/objects are deleted after
inspection. No helper result or target byte is patched.

## Preservation, analysis and remaining work

All six earlier adapters are rebuilt. Non-debug code/data and every relocation
offset/type/symbol/value/section identity remain identical; sizes stay530,
771,1562,4017,4409,11271. Receipt `build/reimu-mid-500/preserved-stages.json`.
Focused old replays pass0/9,0/88,0/64,0/99,0/150,0/59; the changed monolithic
method has the301-case integration cohort. Full historical matrices are not
repeated. No accepted unit uses this private header, no accepted source/
profile/relocation ledger changes, and no cold aggregate exact claim is made.

A direct Ghidra read-only clone independently attests executable identity,
entry68B9D2, base400000, Windows x86, complete mapped.text and full root hash.
It reads back all eight entries and shared exits;
`REIMU_MID_500_READBACK_PASSED` is in `build/reimu-mid-500/ghidra.log`.
All9 primary DB files remain hash-identical; the clone is deleted. The wrong
IDA image is rejected and supplies no semantics. Rejected/superseded objects
and Python caches are removed after final gates.

Supplied read-only animation, flat surface, zero wave/texture/event handles,
inactive secondary-event cycle and masked PC53/PC64 still bound the proof.
Real assets/world backends, both-zero atan2/domain-error behavior, other
runtime modes and full floating-exception equivalence remain unknown.
Next continue510..550 and high actions, then real returning world contexts.
Complete original void ABI, CFG/relocations, truthful VC8/LTCG/TU provenance
and all81550 canonical bytes remain the parent's exact acceptance criteria.
