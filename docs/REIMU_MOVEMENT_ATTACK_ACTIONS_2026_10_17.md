# Reimu88/89/145 and197..204: movement/attack source phase

## Target observations and scope

Only the original Japanese1.06a target is used, SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
The parent remains the authored81550-byte `Reimu_dispatch_action_state_vslot28
@478FA0`, callable end48CE2E, SHA256
`dbf6f375a809fea91cbbccf0f8cff2196f40cba11458c98e475a290b623053e6`.
Its status/source selection stay unclassified/declaration-only. The new
`ReimuActionStateMovementAttack.cpp` is another staged phase, not an original
function boundary, a complete implementation, or a canonical exact unit.

These eleven physical blocks total4248 bytes/1111 decoded instructions.
Shared exits must also be followed; physical ends are exclusive.

|Action|Physical start/end|Instructions|
|---|---|---:|
|88|47A1CB..47A34E|97|
|89|47A34E..47A4C9|90|
|145|47A4C9..47A633|92|
|197|47A633..47A78F|90|
|198|47A78F..47A8C0|72|
|199|47A8C0..47A97B|50|
|200|47A97B..47ABCA|170|
|201|47ABCA..47AE2D|174|
|202|47AE2D..47B04E|139|
|203|47B04E..47B1FB|103|
|204|47B1FB..47B263|34|

Observed instructions establish the following behavior, independently of any
retained source hypothesis:

-88 resembles73's post-advance spawn/sequence selection and wrapping WORD
  friction, but its landing action is89. It captures truncated velocities
  into WORD products by100, clears motion, queries Y and publishes layout5
  before event22. It does not subtract gravity before crossing.
-89 updates angle by double40 and VY by AY only for signed sequence>0. Landing
  selects97 and then clears angle, publishes2, resets the sprite subobject
  and emits22. At the post-advance sequence1 zero-counter node it sets
  VX=WORD+730 times double(promoted FLOAT0.0025), VY=negated signed WORD+732
  times that same double, and AY=0.25. It writes WORD+7A0/+7A2=0/85 and their
  FLOAT conversions at+108/+10C. EDI=85 is established by the root entry and
  preserved at the observed calls; the target negates the sign-extended
  +732 value as a DWORD, including the -32768 case.
-145 preserves71's spawn-before-threshold behavior and conditional second
  gravity subtraction. The ordered sequence1/VY<2 exit is4852F6; its landing
  joins479CAB and then the existing97/layout2/event22 tail.
-197/198 call landing resolution for sequence0/frame<=2 or sequence2;199
  always calls it.197/198 subtract AY for signed sequence<2, then test crossing
  regardless of sequence. Crossing queries Y, clears motion and selects
  sequence2 through remote tails48A701/488FD5, without advancing animation.
-197..199 completion reads BYTE+72C: value2 selects700, then stores signed
  WORD+4A8/+4AC=3. Other values select0, re-read DWORD+6B8, and select1 only
  if it is positive. Re-read animation state after those callbacks. Facing
  updates at sequence2/frame4 for197/198, frame2 for199, use two independent
  ordered self/peer X comparisons; equal/NaN preserves the current facing.
  197/198 sequence0/frame3/timer0 sets VY=4.5,VX=12.5/-12.5,AY=0.35.
-200 resolves landing, sets BYTE+47E and reduces VX above8 by double0.5,
  clamping a strict undershoot back to8. It advances before reading sequence1
  and the signed counter%5 emission condition. Negative DWORD+6B8 selects
  212/211 according to the signed low32-bit facing-times-input product. Other
  values increment WORD+730 with wrap and select204 past the observed5/45
  thresholds. The explicit unsigned product in staging preserves IMUL's low
  DWORD without relying on signed C++ overflow.
-201 resolves landing only for sequence0/3; sequences1/2 subtract double0.5
  from VY and sequence3 adds double3 to VX, clamping strict positive overshoot.
  Its periodic effect precedes crossing/advance and requires !at_surface.
  Crossing with signed sequence<3 clears vertical motion only, queries Y and
  selects sequence3. Completed animation selects0 and clears VX; otherwise
  the post-advance sequence1 zero node sets VX=-14,VY=4 and emits125/126/31.
-202/203 subtract AY and test crossing before periodic effects and advance.
  Landing clears motion, queries Y and selects10.202's sequence0/frame3 node
  initializes WORD+730=0,VX=10,VY=4,AY=0.45 after advancement;203 initializes
  VX=-10,VY=4,AY=0.45 at the entry sequence0 zero-counter node. Both sequence2
  zero-counter nodes call the real face-and-flip primitive478E60.
-204 subtracts double0.75 after landing resolution, clearing VX and+47E only
  for a strict negative result. Animation completion selects0 and clears+47E.

Each periodic124 effect captures double(x+50) and byte direction before two
ordered calls to the real4066B0 generator: the first unsigned remainder%200
contributes to FLOAT Y, and the second%100 is subtracted from the captured
double base before FLOAT X storage.201/203 negate the raw facing BYTE before
zero-extension;200/202 preserve it.125/126 effects use observed80/110/120
height offsets, signed-facing X offsets where present, and event31 after the
two effect callbacks. The source keeps these callback/reload positions.

The staging prefix adds offset assertions for peer X, FLOAT+108/+10C,
WORD+4A8/+4AC, DWORD+6B4 and BYTE+72C. Numeric field names retain unknown
gameplay meanings. All four staged source files are the only consumers; no
accepted unit, compiler profile or shared relocation ledger changes.

## Focused build and comparison

```bash
scripts/compile-unit.sh src/characters/ReimuActionStateMovementAttack.cpp build/reimu-low-completion/ReimuActionStateMovementAttack.obj
python3 scripts/audit-reimu-movement-attack-actions.py build/reimu-low-completion/ReimuActionStateMovementAttack.obj
```

Fresh pinned VC8 SP1 uses `/O2 /GS- /GR /EHsc /MT`, default FP, with no injected
compiler environment. Staging text is4017 bytes. CRLF source SHA256 is
`c155f4db72015e2ceea6e7a71a6b99be0beec68f6b3177a0f0c10abfa0b8250b`,
header SHA256
`72f3cead53c3eb12095280618fe7fc6b9c2f0b5e81b87e0d4e808d0b3db50f0f`,
and object SHA256
`b33a5346ed3cc9490d625a98f5957f98fbb2af49dc60ada4e998815029bbf0c7`.
The manual compiler/input receipt is `build/reimu-low-completion/build-receipt.json`;
the native oracle separately attests the object it executes.

**0/4445 differences**, input SHA256
`e060aed69b228daa7c9c02609317718fe4300d46b6548ff7e3c9011c3fcb1f16`:

|Cohort|Cases|
|---|---:|
|Motion, signed sequences and surface heights|1980|
|Post-advance animation nodes/facing/latch/PC53/PC64|1100|
|Required real frame/block transitions|88|
|Required peer-facing comparisons|144|
|Required completion action setters|144|
|Input sign, low32-bit products and WORD thresholds|525|
|Seeded random emissions and counter gates|240|
|Coordinate precision/NaNs and surface gates|224|

There are3881 genuine RET cases,554 actual435240 request stops and10 actual
465190 request stops. The comparison samples1003 original-root and790 staging
instruction addresses. Each program enters real next-frame/next-block210/208
times, selects sequences100 times, invokes set-action/Reimu-finalize1072 times,
and CharacterEx-finalize1052 times. The real face-and-flip primitive runs40
times and832 MT draws are executed per program, excluding fixture preparation.
This is phase evidence only; no whole-root or exact credit.

The affected staged entry/low/recovery sources were rebuilt and replayed with
**0/10584**, **0/10700**, **0/4595** differences. Accepted units are unaffected;
no cold aggregate replay or new aggregate exact claim was made.

The oracle executes original helpers unchanged. Real406670 seeding through
native RET prepares MT state for0/5489/FFFFFFFF; each case resets that supplied
state and starts with index624. Real4066B0 performs twist/temper/index writes.
Both programs compare all2496 MT state bytes and its index, along with the
actor and callback observations. No random result is replaced. Writes to MT
storage are allowed only from these attested original routine extents.

The20-key read-only resource graph has four linked sequences and storage for
six frames per sequence. Five-frame inputs reach the197/198 frame4 nodes
without overlapping neighboring arrays. Nine structural tests cover11-key,
20-key and larger-frame trees, links and disjoint storage. Default older
fixture data remains unchanged. Flat original surface, inactive secondary
event cycle and zero texture/event handles remain scope restrictions.

An initial high-Y fixture made the actual landing helper switch200 to9 before
its input/random nodes. A swapped-random-source control consequently passed
the old smoke set. The retained matrix fixes200's initial surface context,
and also fixes the peer-facing/completion contexts. Target-side guards now
require actual input-gate/peer-comparison PCs, advertised completion setters,
two random draws and a real124 request where intended.201
negative-Y coordinates must instead take its native at-surface gate. The first completion profile also
used a non-advancing final sequence. Retained completion cases use actual
single-sequence terminal data (head/previous=NULL, next=NULL, mode0); separate
transition controls require real next-frame/next-block entry counts. These
discarded matrices are not evidence for the advertised branches. The oracle supports `--cohort NAME` for focused follow-up instead of full
replay. The final99-case smoke set
has zero differences and rejects both compiled controls1/99 each: exchanged
random consumption order in200, and signed sequence>0 replaced by!=0 in89.

Returning traces must restore the real RET ABI and zero x87 TOP; the
control word is compared between programs. Request traces stop at the actual465190/435240 wrapper entry with all
seven/five arguments and receiver, and do not fabricate callback results.
All4096 actor bytes, ordered helper traces and physical x87 conversion inputs
are compared. Object/support hashes must stay unchanged throughout each run.
This is sampled execution, not complete branch/numerical/exception coverage.

## Attestation and remaining work

IDA preflight still rejects the unrelated loaded executable; it supplied no
semantic evidence. One direct Ghidra clone independently attested executable
SHA256, entry68B9D2, base400000, Windows x86 language, mapped.text and full-root
bytes. It read back the root prototype/body, all eleven action starts and the
two remote crossing tails. The log retains
`REIMU_LOW_COMPLETION_READBACK_PASSED`. All nine primary database files remain
hash-identical; the disposable clone is deleted.

Object/effect callback-returning continuations remain outside the native
proof, including stores after700 and the second effect/event in paired
emissions. Their source is based on original instructions and must be exercised
with real returning world/manager contexts before whole-root claims. Default
action families still delegate to the unintegrated root; no whole-root canonical
comparison or authored exact increase is claimed. Next recover the remaining
low208..226 families, then mid/high toward complete81550-byte source.
