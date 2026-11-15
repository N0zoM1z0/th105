# Yukari control mode: complete source and parked physical-layout residuals

## Result and reproduction

Yukari Fighter primary slot `+0x5C @0x005893C0` now has complete source in
`src/characters/YukariControlMode.cpp/.hpp`. The target owns **3934 callable
bytes /4260 complete emitted bytes**. Selected source emits 4244 complete bytes
and remains **nonexact** at `+0xAE /0x0058946E`: an early return displacement
changes because of downstream physical layout. No matches row or new exact
credit is added.

```sh
taskset -c 0 nice -n 10 python3 scripts/build.py \
  --unit exact-first-yukari-control-mode --compare --json
```

Both commands correctly return 1. The formal build reproduces the selected
private source; the full audit checks exact section-tail length and every byte,
including all tables and alignment. It replays all 150 function relocations
(44 REL32 /106 DIR32), rather than clipping relocation replay to the callable
boundary. The pinned VC8 SP1 `/O2` profile remains unchanged.

Target callable SHA256:
`63acb68ca5994f8d160ad270e67814de74150413b3586cda9ac387787eedcad7`.
Target full SHA256:
`1dda21d7728f57101ceb8fe19caf2bcab9f9f3ac4616444b61036688c36cf285`.
Selected full canonical SHA256:
`be2a46e3e11ae1500dd25b54d5634fb0d4d6ec631cedf52e5d9c5d8387badf04`.

The receiver is a pointer-only call view; never construct or embed it. Original
complete layout, unused virtual signatures and source/TU identity remain
unknown. Declaration-only callees gain no implementation or exact credit.
There is no assembly, copied byte array, inert storage, artificial padding,
fake return, ABI/register forcing or compiler-profile search.

## Observed target facts

Only original Japanese 1.06a SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`
is inspected. Existing RTTI evidence classifies the root as authored. Raw
primary slot 5C cell 6C5928 points to 5893C0. Slot 08/0C bind 45BFE0/45C390; slot 58
binds the shared 5F1F80 policy. No additional callee credit is assigned.

Complete raw traversal closes **1045 instructions**, **16 RET 0s**, **63 calls**,
all internal direct edges and all 18 destination entries. Direct calls comprise
4399C0 once,478E60 eight times,4067D0 twenty-seven times,465190 six times and
45C030 twice. Nineteen calls are virtual: eighteen action callbacks and one
CPU slot 58 CALL followed by the normal epilogue. There is no register tail,
unresolved indirect exit, remote chunk or EH path in this bounded body.

Prologue aligns ESP to eight bytes, reserves 40h and saves EBX/EBP/ESI/EDI;
EBP has a real-1 lifetime used by decrements and the negative spawn variant.
Callable end is exclusive 58A31E. Two-byte MOV EDI,EDI alignment precedes tables
at 58A320(3 entries),58A338(4),58A348(4),58A358(3),58A454(4). Byte-index maps
at 58A32C and 58A364 contain 12 and 240 entries. Complete payload ends exclusively
58A464, followed by twelve INT3 bytes. Metadata adds no authored-byte credit.

The low-health coefficient at 6C57C0 is **double(float 0.33)**, exactly
`0.33000001311302185`, bytes`00000060b81ed53f`; it is not the decimal double 0.33.
Native 589B35/589DC7 multiply signed WORD176 by that qword before comparing
signed WORD174. Source expresses the observed width explicitly. One new named
literal allowlist key is referenced only by this unit's explicit
`__real@3fd51eb860000000` override. Existing default mappings and accepted-unit
bindings remain unchanged; the ordinary literal audit checks source encoding
and hash-attested target bytes.

## Independently reviewed behavior

| Surface | Native behavior retained in complete source |
| --- | --- |
| Prefix |Decrement WORD768 and clear commands/action-conditioned word lanes; signed 55A gate precedes checked deque selection. |
| Records 0..3 |Ready 0 selects 770 then 1. State 1 with positive peer 170/174 faces, selects 710 and returns to 1; a nonpositive peer also writes 1. |
| Records 4..7 |Ready 0 selects 770/1, ready 1 faces/selects720/2, ready 2 faces/selects721/1. |
| Records 8..11 preemption |For signed state>=1 decrement 7C0; expiry plus action 700/705/706, action 701..703 with positive sequence, or action 704 faces/selects730 and returns. |
| Counted 920 spawns |When 7BE>0, peer**168**/174<=0 writes 7BE=0 but continues. Identifier 3/2/1/0 selects signed divisors6/8/9/10. A zero remainder still generates one three-zero-float920 packet, with x=self x+(100-RNG300)*signed facing and y=self y+300-RNG400, byte direction and variant-1. Then decrement 7BE, including after the zeroing path. |
| Mobility state 1 |Positive peer**170**/174 and ready action trigger facing. Facing+1 with ordered x<180 or other facing with ordered x>1100 chooses 705/horizontal5. Otherwise unsigned RNG 100>50 chooses 705/horizontal4, else 706/vertical-4. All routes use one RNG 30+30 delay endpoint. Nonready/nonpositive-peer action 705/706 with expired timer publishes state 2 before 700. |
| Motion state 2 |Face, store the low-word RNG 3 choice. Mode 0 uses backward motion when ordered x>=640/facing+1 or ordered x<=640/facingFF; otherwise forward. Backward uses-RNG3-double6 then RNG 4+double 8/action703; forward stores vertical/scale before RNG 3+6/action702. Mode 1 is forward; mode 2 sets facing by ordered x<=640 and retains two physical RNG paths. Scale is.2f; mode 2 also publishes state 1 before the callback and all modes restore 1 afterward. |
| Low-health930 timer |At health<=max*double(float 0.33), reset expired 7C2 to 60/65/70 for identifiers 3/2/0-or1, spawn three zeros at peer170 x/y+100, then decrement 7C2. A positive timer also decrements; the high-health path leaves it alone. |
| Vertical 930 bursts |Positive 7C4 modulo 10 dispatches 22 and uses a separate packet 0f/40f/1f. Counter 7C6=0 spawns at x=(facingFF)*double 1280,y=self y+100; other values generate both y+100+n*double 75 and y+100-n*75. Increment 7C6 after generation; decrement 7C4 after each active tick. Source retains independent callback/field reads. |
| Records 12..15 states |Initial 770/1. Ready 1 faces; low health increments signed 76E and publishes 2 before 741. Otherwise signed 76E%2 chooses 740/741, with 2 published before the callback. Ready 2 uses the same motion family with scale.3f. Mode 2 retains its before/after state 1 writes. |
| Records 16..19 |Action 750/sequence2 gates signed 7C8%300. Identifier 3/2/0-or1 chooses float count 10/8/6; capture unsigned RNG 360 phase. Each float iteration emits 940 with angle=n*(double 360/count)+phase, float step 360/count and 1f. A final 940 retains the last angle/step and sets parameter 2=5f, then dispatches 53. Increment 7C8 after the gated action tick. Ready state 0 chooses 771 then 1. |
| Records 248..255 |Conditional action0, then the actual virtual CPU CALL and epilogue. |

All three spawn packet words are genuinely consumed. The final ring's float
count defaults and the signed divisor switch have no invented initialization
for invalid identifiers. The final packet retains its last two words; no fake
fallback is supplied for an invalid/zero-iteration path. Valid-domain assumptions
and original invalid-input behavior remain unknown. Both peer pointer offsets,
unsigned RNG consumption, signed word counters/remainders, double expression
widths and callback-side state ownership follow raw instructions. Ordered
predicates retain NaN fallthrough rather than copying a peer's conditions.

## Early whole comparison and finite experiments

| Probe | Evidence-backed change / complete result |
| --- | --- |
|00|First complete body emits 4284 bytes. All six spawn/nineteen virtual sites are present, but 28 physical selectors versus 27 native; float temporary spills and shared-exit layout differ. |
|01 rejected|Keep mode 2 vertical RNG as an unsigned scalar until the field conversion. This merges two physical selector copies; full 4196 and 26 selectors do not match. |
|02|Write the native single final float field directly in each branch, removing the extra float captures. Full 4268,28 selectors; the remaining state-write scheduling is explicit in the diagnostic. |
|03 selected|Express the actual single delay endpoint after the mobility choice. All 63 physical calls now agree; full 4244 remains nonexact. Keep this simpler structured body. |
|04 unselected|Actual shared-exit labels change layout to 4236 but retain wrong placement of the other-facing condition. No exact acceptance. |
|05 unselected|Order that condition's explicit branch label after the random branch. Full 4236 changes again without recovering native layout. This is not a byte-neutral result or a proof about original source labels. |
|06 negative|Commute the positive burst Y addition to test its native operand/CSE ownership. It reproduces 03's entire candidate byte-for-byte. |
|07 negative|Use a double rather than a float capture for the mode 2 vertical result, reflecting the native double addition/single final store. It also reproduces 03 byte-for-byte. |

Stop after the two identical-output controls and select another complete peer.
Remaining differences are the mobility branch/shared-return placement, a
state 1-store schedule, hoisted/repeated Y+100 loads, and count/index/step stack
slots in the final radial loop. A nearer payload size or matching call count
is diagnostic only. New independent source/lifetime/TU evidence is needed to
reopen those controls; no claim that LTCG is required is made. No broad runtime
matrix was needed for a concrete ambiguity in this scope.

## Validation and retained evidence

IDA preflight rejects the different executable open there; no semantics or
writes from that session are used. The single-process guard initially refuses
a new Ghidra launch while another repository's analysis is live. After that
process is confirmed absent, one read-only run attests target SHA/base/entry
68B9D2, Windows x86 language/compiler and every raw-backed section against the
PE. Temporary bounded entry and callee views are read back and rolled back;
all nine primary DB pins are unchanged. Decompiled output corroborates raw
stack/edge interpretation and is not pasted as source. Own Ghidra heap 384MiB /
one CPU; compilation remains serial CPU 0/nice10, with memory monitored.

Existing accepted sources, headers, flags and relocation bindings are unchanged.
Exact ledger totals remain 1397 functions/327058 bytes, without an aggregate cold
replay claim. Continue another complete peer; retain this nonexact checkpoint and
its neutral controls instead of repeating them unchanged.
