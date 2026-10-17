# Reimu208..226 and direct300: remaining low source phase

## Target observations and ownership

Target is original Japanese1.06a, SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Parent `Reimu_dispatch_action_state_vslot28 @478FA0` remains the81550-byte
authored callable ending48CE2E, SHA256
`dbf6f375a809fea91cbbccf0f8cff2196f40cba11458c98e475a290b623053e6`.
Root status/source selection remain unclassified/declaration-only. The staged
phase below is neither an original callable boundary nor a complete root;
no implemented/exact credit is added.

The remaining14 concrete low-table bodies plus direct300 occupy the contiguous
physical range47B263..47CC5F:6652 bytes/1764 decoded instructions. Ends below
are exclusive, and remote shared tails remain part of the behavior.

|Action|Physical start/end|Instructions|
|---|---|---:|
|208|47B263..47B46C|143|
|209|47B46C..47B56D|61|
|210|47B56D..47B66E|61|
|211|47B66E..47B811|101|
|212|47B811..47B92B|71|
|214|47B92B..47BF2F|445|
|215|47BF2F..47BFD2|55|
|220|47BFD2..47C0F7|76|
|221|47C0F7..47C229|81|
|222|47C229..47C3D1|106|
|223|47C3D1..47C5A7|127|
|224|47C5A7..47C7EA|149|
|225|47C7EA..47C9B3|118|
|226|47C9B3..47CBBD|122|
|300|47CBBD..47CC5F|48|

The mapper's provisional span-to-next-table-destination for226 is731 bytes.
That span also contains162 bytes for direct300 and47 bytes for the mid
selector47CC5F..47CC8E. These are not226-owned bytes. Observed4791DB compares
the sign-extended action with300;4791E0/JG enters the mid selector and4791E6/JE
enters47CBBD.226 ends with JMP47B039 at47CBB8;300 has RET47CC5E immediately
before the mid selector. This refines physical action attribution without
changing the reconciled parent boundary or the primary-table union counts.

## Recovered behavior

-208..212/220..222 resolve landing only for sequence0. Crossing is tested
  before gravity: set action10, query Y, then clear motion. At-surface or
  ordered positive VY publishes WORD+4AE=2. Signed sequence>0 subtracts AY
  and clamps a strict undershoot at FLOAT-20.208/211/220/221/222 emit123
  periodically before advancement. All except211/212 select sequence2 when
  live sequence1 has ordered VY<4. Their post-advance sequence1 zero node
  launches with target-specific VX/VY, AY=0.65, clears+47E and emits63.
-214 first advances; completion selects9 and returns. A zero-counter
  sequence1 node emits31, while a zero-counter sequence6 node selects9 and
  returns before steering. The signed low DWORD facing/input product and
  DWORD+6B8 select target angle WORD+732. Neutral input leaves+732 unchanged.
  Sequences5/6 apply gravity; signed sequences1..4 perform the flight update.
-Flight increments WORD+736 with wrap. WORD+734 is the wrapping difference
  between target angle and the truncated current FLOAT+740; only values>180
  subtract360 and only values<-180 add360. Positive/negative differences
  add/subtract double3 in mode+4B8=0, otherwise double1. Original quantized
  cosine/sine calls produce VX/VY from FLOAT+73C. Height>680 with VY>0 clears
  upward speed. The speed is then increased by double(promoted FLOAT0.3)
  and clamped strictly above10. Real46BF30 consumes5/10 resource units and
  applies floor1 to the associated counter.
-214 publishes angle=-phase or180-phase for negative VX. Four independent
  live comparisons select1↔3 and2↔4, with ordered VX>=0 on the positive side.
  Counter%5==1 emits125, preserving sine-before-cosine order and explicit
  `(sine*100 + Y) +100` association. Flight exits when the held/count gate or
  depleted WORD+482 requires it. The target repeats that unchanged gate twice
  without intervening writes/calls; staging uses one ordinary equivalent
  condition rather than inert duplicate code. Sprite reset precedes facing,
  VX flip and live sequence5/6 selection. The two sequence groups are re-read
  independently across callbacks.
-214 crossing after continued flight queries Y and clears VY. Signed
  sequence<5 resets the sprite before selecting215; otherwise it selects10
  before clearing all motion.215 independently damps positive and negative VX
  by double0.75 and selects0 on animation completion.
-223 advances before its periodic124 request, increments WORD+730 with wrap,
  uses12/45 thresholds, and selects204. Its sequence0/frame3 launch sets
  VX=7.5 and increments+730 again before125/126/event31.
-224 uses201-like landing/sequence behavior, but friction is double2 and
  crossing clears **VY only**, retaining AY. The sequence1 zero node is also
  guarded by WORD+730=0, then latches it to1 before launch/effects.
-225 applies gravity only for signed sequence>=1;226 always applies it.
  Both emit124 in sequence2, then advance and select9 on completion while
  continuing to re-read post-advance nodes.225 launches at sequence1 with
  VX=-10,VY=4,AY=0.45 and negative raw-byte direction.226 clears+730 and
  launches VX=10 with the observed110-height effect pair; its sequence3 zero
  node calls the original face-and-flip helper.
-Direct300 resolves landing, invokes the real directional gate478EE0 with
  option0 and returns on success. Otherwise it applies gated double0.5 VX
  friction, advances, optionally selects0, and re-reads timer/frame for
  event27 and+47E clearing. It is not a continuation of226.

Offsets for WORD+482/+4AE/+734/+736 and DWORD/FLOAT+4B8/+6C8/+73C/+740 are
compile-time asserted in the shared staging prefix. Gameplay field names,
original TU ownership and many callback world contexts remain unknown. The
sine/cosine bodies return an m32 table load in ST0; the pre-existing double
declarations are retained as an ABI-compatible view, without claiming the
unresolved original float-versus-double source spelling.

## Reproduction and native evidence

```bash
scripts/compile-unit.sh src/characters/ReimuActionStateLateLow.cpp build/reimu-late-low/ReimuActionStateLateLow.obj
python3 scripts/audit-reimu-late-low-actions.py build/reimu-late-low/ReimuActionStateLateLow.obj
```

Pinned VC8 SP1 `/O2 /GS- /GR /EHsc /MT`, default FP, no injected compiler
environment gives4409 staging text bytes. CRLF source SHA256 is
`70aa4459a84986dbcf1777e54f5072cf1332382435df6c7a222fbdf202870ac1`,
header SHA256
`b6edbe0548ccf2eeda987c5a0bc1329f339f4970469201d8e2f1a224254daa6a`,
and object SHA256
`3d4f11e1d528b1ecfc7e411334cb9468b7e32bf7977e310b4be5c4ea11d03ee3`.
Manual build receipt: `build/reimu-late-low/build-receipt.json`. The execution
oracle attests its object separately and does not itself attest compilation.

**0/3414 differences**, input SHA256
`da95a3f2424b34380b20d14bcddfe605c03d9faf958b0cb873e5ffdcb5485d3b`:

|Cohort|Cases|
|---|---:|
|Motion, signed sequences and surface heights|2160|
|Flight target angle/turning/mode/PC53/PC64|432|
|Resource/held/count/facing flight exits|288|
|Post-advance zero-counter nodes and BYTE facing|450|
|Required two-draw123/124 requests|36|
|Required direct300 directional-gate calls|48|

3294 cases reach native RET and120 stop at real435240 request entry, comparing
all five arguments and receiver.1597 original-root and962 staging instruction
addresses are sampled. Per program, sine/cosine/resource adjustment each run
786 times, directional gate222 times, MT draw108 times, set-action658 times
and sequence selection546 times. All4096 actor bytes, ordered helper calls,
physical x87 conversion inputs, MT state/index and control word are compared;
RET additionally requires stack delta4, preserved EBX/ESI/EDI/EBP, zero x87
TOP and staged AL=true. Target-side guards require the advertised steering,
resource, directional and periodic effect paths. This is sampled evidence,
not exhaustive branch/numerical/exception or full-gameplay coverage.

The21-key read-only fixture has seven linked sequences and room for six
frames per sequence. Twelve structural tests cover tree invariants, disjoint
frame/vector/node storage and real links across the old and new capacities.
No old fixture or oracle is changed for this extension.

The orientation table is not synthesized or substituted at a helper return.
`native_orientation_table` executes the original177-byte initializer4065B0,
including original cosine code, through genuine RET with reviewed global
write bounds and target-text execution bounds. Initializer SHA256 is
`2ca8263dd81760f21b6d23ec8912f5a12a0bea3a5823dfce24605bafbacd5d05`.
Both masked PC53/PC64, with the PE's zero startup math flags, yield the same
14400-byte table SHA256
`c134fa85e7988574c2db386dc8e14de2113d6e465c18f4503bd265219c5ca898`.
Its cardinal values are checked. Exact executed instruction bytes are retained
in the private report. This raw fixture dependency is not a promoted/matched
candidate or a new origin/implementation claim. Its MT initialization effects
are separate from each case's explicitly seeded MT context.

During the comparison, real406360/4063D0, finite fabs68BAAE and control-word
helper696387 run unchanged, along with existing animation/action helpers.
The orientation table is read-only to native comparison execution. Flat
surface, zero texture/event handles, inactive secondary-event cycle and
finite phase angles bound the context. Nonfinite-angle CRT error paths,
other startup math modes and real returning object/effect backends remain
outside this proof. Partial request stops do not prove their continuations.

Compiled source negatives are detected: clearing224's AY on landing fails1/150
smoke cases; changing214's `difference >180` to `>=180` fails24/432 steering
cases. Wrong objects are removed after retaining sources, hashes and receipts.

## Preservation, database and continuation

Fresh rebuilds of all four previous staging objects have byte-identical text,
non-debug code/data sections and every relocation's offset/type/symbol/value/
section identity. Debug/file/timestamp metadata is excluded from this
preservation check, not from any canonical target comparison. Current smoke
replays pass0/9 entry,0/88 low,0/64 recovery and0/99 movement/attack. Full old
matrices are not redundantly rerun, and no affected accepted unit exists:
the shared header is used only by these five unaccepted staged sources.
The receipt is `build/reimu-late-low/preserved-stages.json`.

IDA preflight rejects the unrelated loaded image; it supplies no semantics.
One direct Ghidra clone attested the executable SHA256, entry68B9D2,
base400000, Windows x86 language, mapped.text and full-root bytes, decoded
all bounded instruction starts (including direct300), and read back the root
prototype/body and relevant entries/shared tail. The log contains
`REIMU_LATE_LOW_READBACK_PASSED`. All nine primary DB files remain unchanged;
the clone is removed.

All44 concrete low-table bodies and direct300 now have staged source. The
selector/default call and phase integration, mid/high bodies, real returning
world contexts and canonical whole-root compilation remain pending. Keep the
full81550-byte root as the objective; these phase comparisons add no exact
authored bytes. Use `--cohort NAME` for focused follow-up and preserve the
corrected226/300/selector attribution in later owner analysis.
