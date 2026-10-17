# Reimu actions71..78: staged recovery control flow

Target observations below use only the original Japanese1.06a PE, SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
The authored root remains `Reimu_dispatch_action_state_vslot28 @478FA0`,
81550 bytes, SHA256
`dbf6f375a809fea91cbbccf0f8cff2196f40cba11458c98e475a290b623053e6`.
`ReimuActionStateRecovery.cpp` is a staged source phase, **not** an original
function boundary or a complete root implementation. Neither implemented nor
exact credit is added. The root ledger stays unclassified/declaration-only.

## Observed target ownership and behavior

The primary action blocks occupy2619 bytes/677 decoded instructions, with
shared control flow outside these physical ranges. Ends are exclusive.

|Action|Physical start/end|Instructions|
|---|---|---:|
|71|479790..479963|125|
|72|479963..479A1B|48|
|73|479A1B..479B9E|97|
|74|479B9E..479CFB|100|
|75|479CFB..479E59|90|
|76|479E59..479FCC|91|
|77|479FCC..47A0DC|69|
|78|47A0DC..47A1CB|57|

Their branch/floating-point instructions establish these distinctions:

-71/74 may mark+7A4 and request owned object951 before the sequence check;
  77 does so before animation advancement. 73/75 do so after advancement.
  76/78 first advance, then at the zero-counter/sequence1 node flip the BYTE
  facing and initialize velocity before requesting951. Directions zero-extend
  the resulting raw facing byte, including wrapped -128.
-71/72/74 with sequence1 and ordered VY<2 call the real vslot+14 helper and
  return. The remote tails at47D7BE and4852F6 both do this. Other sequences
  continue; NaN does not take the threshold exit.
-71 subtracts AY and stores VY, then subtracts it a second time only if the
  stored VY is ordered positive. 72/74/76/77/78 subtract it once;73/75 do not.
-74 tests the boundary before its surface crossing;75 does so after crossing.
  Each calls435910 separately for VX<=-25→action76 and VX<=-15→action78.
  The comparisons are ordered and include equality. The helper calls cannot
  be cached across these two tests.
-Landing captures each velocity with the original integer conversion, then
  an AX-width product by100 into WORD+730/+732. Multiplying the float first
  changes the result. It clears motion, queries the surface and sets action97.
  Layout scalar is5 for73/75,4 for76 and2 otherwise. Actions76..78 emit event22
  before recording/clearing velocity;71..75 emit it after layout publication.
  Only76/77 explicitly clear angle+12C and reset the sprite subobject at+4.
-71 decrements+730 only while positive.73 decrements the WORD unconditionally,
  then clamps a signed negative result to0: -32768 wraps to32767. Boundary
  friction adds double1 for71/72 and double2.5 for73, stores FLOAT VX and
  clamps positive overshoot. If byte+490 is set,72 publishes VX to+6AC;
  71/73 publish signed WORD+730 times double-2.
-73/75 advance first and re-read the DWORD/WORD animation counters. At the
  sequence1 zero node, nonzero VY (including NaN) selects sequence3 when VX
  is zero, otherwise2, through shared tail479E35.73's friction follows only
  if this selection did not return;75 returns without friction.
-76 subtracts double30 from angle only for signed sequence>0;77 always does.
  Their post-advance launch values differ:76 uses VX=-3,VY=10;78 uses
  VX=-5,VY=3; both use AY=0.5. Sequence sign and callback ordering are retained.

The staging header adds offset-asserted FLOAT+12C/+6AC, BYTE+490,
WORD+730/+732/+7A4 and the observed virtual slots. It still describes a
partial prefix rather than a full Reimu class size. These new declarations
are used only by the three unaccepted staging files; accepted units are
unaffected. No compiler profile or shared relocation ledger changes.

## Reproduction and native evidence

```bash
scripts/compile-unit.sh src/characters/ReimuActionStateRecovery.cpp build/reimu-71/ReimuActionStateRecovery.obj
python3 scripts/audit-reimu-recovery-actions.py build/reimu-71/ReimuActionStateRecovery.obj
```

Fresh VC8 SP1 `/O2 /GS- /GR /EHsc /MT`, default FP, no injected compiler
environment, yields1562 staging text bytes. CRLF source SHA256 is
`d428caf56e157a19f5ca9a2b7b54065a52a5c19bb0f3e1256e7c6cc5889f2599`,
header SHA256
`d8e236e63dc2857ecc2037b31777e4b9dfb354193678d758d759afbb5047f5da`,
and object SHA256
`15f85b618851e84a1b64ee84f6242a77070000bd9187be1ec1b5a6b5c686e127`.
The manual build receipt is `build/reimu-71/build-receipt.json`; the oracle
attests its object input but does not itself attest compilation.

**0/4595 differences**, input SHA256
`f78eb11f656eb7224a986ec65319fc43257f35c92b038be9e0df4c2028c0ee7f`:

|Cohort|Cases|
|---|---:|
|Gravity, signed sequence and surface height|1920|
|Boundary thresholds, friction and WORD wrap|2100|
|Animation nodes, signed facing and effect latch|560|
|Initial object951 request|15|

Of these,4106 reach genuine native RET;414 stop at the actual global effect
wrapper435240 and75 at owned-object wrapper465190. At the latter two entries,
all five/seven DWORD arguments and the receiver are compared, with no fake
result or skipped callback body. Stops include both landing-action97 and
boundary-action76/78 finalization. Request-returning continuations remain
unproved. In particular, layout publication and the final explicit scratch
reset are instruction-derived source, not covered by these returning traces.

Every case compares all4096 supplied actor bytes, ordered helper/receiver/
argument traces, physical x87 conversion inputs, control word and the allowed
layout scalar. RET cases additionally require stack delta4, preserved
EBX/ESI/EDI/EBP, empty x87 stack and candidate AL=true. Both programs execute
the same unchanged target helper bodies; target/helper/object/tool/support
hashes are retained, and object/support inputs must remain unchanged during
the run.675 target-root and375 staging instruction addresses are sampled.
This is neither exhaustive branch/numerical coverage nor a canonical match.

The read-only20-key resource graph contains0..10,71..78 and97, four linked
sequences per action, and disjoint frame storage. Terminal cases begin in
sequence3; earlier sequences retain links needed by real set-sequence calls.
An initial disconnected terminal fixture caused a real45C390 read failure
when73 selected sequence2; the retained matrix fixes the data rather than
replacing the helper. Both11-key and20-key tree order/parents/red-black
heights, storage disjointness and sequence links pass six fixture tests.

The original flat stage and zero event handles are required, as is the
inactive secondary-event-cycle path. Textured/audio/world backends, active
secondary-event cycles, allocation and callback-returning object/effect
contexts are outside scope. Invalid/signaling floats are sampled with masked
PC53/PC64; exception behavior is not established.

Two compiled wrong-source controls are rejected: moving71's second gravity
subtraction to72 causes11/64 smoke differences; replacing73's wrapping
decrement/clamp with a wider pre-clamp causes84/4595 differences. Their
objects were discarded after retaining small receipts and reproduction patches.

The affected entry and0..10 phases were freshly rebuilt and replayed:
**0/10584** and **0/10700**, respectively. Their input matrices remain unchanged.
No accepted-unit aggregate or cold replay was needed or claimed.

## Database attestation and continuation

The mandatory IDA preflight still rejects the wrong loaded image; none of its
semantic output was used. Direct Ghidra on one disposable database clone
attested executable SHA256, entry68B9D2, base400000, Windows x86 language,
the full mapped.text and root bytes. It read back the root prototype/body,
all eight action starts, both remote next-block exits and shared sequence
tail. `REIMU_RECOVERY_READBACK_PASSED` is retained in the private build log.
All nine primary database files remained hash-identical; the clone was deleted.

Next recover the remaining Reimu action families toward complete root source.
The unproved object/effect callback continuations above must be resolved
before a whole-root behavioral or canonical result. Fields retain numeric
names where gameplay meaning and ownership remain uncertain.
