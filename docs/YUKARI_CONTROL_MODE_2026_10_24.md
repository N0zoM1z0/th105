# Yukari control mode: complete source and parked physical-layout residuals

## Result and reproduction

Yukari Fighter primary slot `+0x5C @0x005893C0` now has complete source in
`src/characters/YukariControlMode.cpp/.hpp`. The target owns **3934 callable
bytes /4260 complete emitted bytes**. Selected source emits4244 complete bytes
and remains **nonexact** at `+0xAE /0x0058946E`: an early return displacement
changes because of downstream physical layout. No matches row or new exact
credit is added.

```sh
taskset -c 0 nice -n 10 python3 scripts/build.py \
  --unit exact-first-yukari-control-mode --compare --json
python3 scripts/audit-yukari-control-mode.py
```

Both commands correctly return1. The formal build reproduces the selected
private source; the full audit checks exact section-tail length and every byte,
including all tables and alignment. It replays all150 function relocations
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

Only original Japanese1.06a SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`
is inspected. Existing RTTI evidence classifies the root as authored. Raw
primary slot5C cell6C5928 points to5893C0. Slot08/0C bind45BFE0/45C390; slot58
binds the shared5F1F80 policy. No additional callee credit is assigned.

Complete raw traversal closes **1045 instructions**, **16 RET0s**, **63 calls**,
all internal direct edges and all18 destination entries. Direct calls comprise
4399C0 once,478E60 eight times,4067D0 twenty-seven times,465190 six times and
45C030 twice. Nineteen calls are virtual: eighteen action callbacks and one
CPU slot58 CALL followed by the normal epilogue. There is no register tail,
unresolved indirect exit, remote chunk or EH path in this bounded body.

Prologue aligns ESP to eight bytes, reserves40h and saves EBX/EBP/ESI/EDI;
EBP has a real-1 lifetime used by decrements and the negative spawn variant.
Callable end is exclusive58A31E. Two-byte MOV EDI,EDI alignment precedes tables
at58A320(3 entries),58A338(4),58A348(4),58A358(3),58A454(4). Byte-index maps
at58A32C and58A364 contain12 and240 entries. Complete payload ends exclusively
58A464, followed by twelve INT3 bytes. Metadata adds no authored-byte credit.

The low-health coefficient at6C57C0 is **double(float0.33)**, exactly
`0.33000001311302185`, bytes`00000060b81ed53f`; it is not the decimal double0.33.
Native589B35/589DC7 multiply signed WORD176 by that qword before comparing
signed WORD174. Source expresses the observed width explicitly. One new named
literal allowlist key is referenced only by this unit's explicit
`__real@3fd51eb860000000` override. Existing default mappings and accepted-unit
bindings remain unchanged; the ordinary literal audit checks source encoding
and hash-attested target bytes.

## Independently reviewed behavior

| Surface | Native behavior retained in complete source |
| --- | --- |
| Prefix |Decrement WORD768 and clear commands/action-conditioned word lanes; signed55A gate precedes checked deque selection. |
| Records0..3 |Ready0 selects770 then1. State1 with positive peer170/174 faces, selects710 and returns to1; a nonpositive peer also writes1. |
| Records4..7 |Ready0 selects770/1, ready1 faces/selects720/2, ready2 faces/selects721/1. |
| Records8..11 preemption |For signed state>=1 decrement7C0; expiry plus action700/705/706, action701..703 with positive sequence, or action704 faces/selects730 and returns. |
| Counted920 spawns |When7BE>0, peer**168**/174<=0 writes7BE=0 but continues. Identifier3/2/1/0 selects signed divisors6/8/9/10. A zero remainder still generates one three-zero-float920 packet, with x=self x+(100-RNG300)*signed facing and y=self y+300-RNG400, byte direction and variant-1. Then decrement7BE, including after the zeroing path. |
| Mobility state1 |Positive peer**170**/174 and ready action trigger facing. Facing+1 with ordered x<180 or other facing with ordered x>1100 chooses705/horizontal5. Otherwise unsigned RNG100>50 chooses705/horizontal4, else706/vertical-4. All routes use one RNG30+30 delay endpoint. Nonready/nonpositive-peer action705/706 with expired timer publishes state2 before700. |
| Motion state2 |Face, store the low-word RNG3 choice. Mode0 uses backward motion when ordered x>=640/facing+1 or ordered x<=640/facingFF; otherwise forward. Backward uses-RNG3-double6 then RNG4+double8/action703; forward stores vertical/scale before RNG3+6/action702. Mode1 is forward; mode2 sets facing by ordered x<=640 and retains two physical RNG paths. Scale is.2f; mode2 also publishes state1 before the callback and all modes restore1 afterward. |
| Low-health930 timer |At health<=max*double(float0.33), reset expired7C2 to60/65/70 for identifiers3/2/0-or1, spawn three zeros at peer170 x/y+100, then decrement7C2. A positive timer also decrements; the high-health path leaves it alone. |
| Vertical930 bursts |Positive7C4 modulo10 dispatches22 and uses a separate packet0f/40f/1f. Counter7C6=0 spawns at x=(facingFF)*double1280,y=self y+100; other values generate both y+100+n*double75 and y+100-n*75. Increment7C6 after generation; decrement7C4 after each active tick. Source retains independent callback/field reads. |
| Records12..15 states |Initial770/1. Ready1 faces; low health increments signed76E and publishes2 before741. Otherwise signed76E%2 chooses740/741, with2 published before the callback. Ready2 uses the same motion family with scale.3f. Mode2 retains its before/after state1 writes. |
| Records16..19 |Action750/sequence2 gates signed7C8%300. Identifier3/2/0-or1 chooses float count10/8/6; capture unsigned RNG360 phase. Each float iteration emits940 with angle=n*(double360/count)+phase, float step360/count and1f. A final940 retains the last angle/step and sets parameter2=5f, then dispatches53. Increment7C8 after the gated action tick. Ready state0 chooses771 then1. |
| Records248..255 |Conditional action0, then the actual virtual CPU CALL and epilogue. |

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
|00|First complete body emits4284 bytes. All six spawn/nineteen virtual sites are present, but28 physical selectors versus27 native; float temporary spills and shared-exit layout differ. |
|01 rejected|Keep mode2 vertical RNG as an unsigned scalar until the field conversion. This merges two physical selector copies; full4196 and26 selectors do not match. |
|02|Write the native single final float field directly in each branch, removing the extra float captures. Full4268,28 selectors; the remaining state-write scheduling is explicit in the diagnostic. |
|03 selected|Express the actual single delay endpoint after the mobility choice. All63 physical calls now agree; full4244 remains nonexact. Keep this simpler structured body. |
|04 unselected|Actual shared-exit labels change layout to4236 but retain wrong placement of the other-facing condition. No exact acceptance. |
|05 unselected|Order that condition's explicit branch label after the random branch. Full4236 changes again without recovering native layout. This is not a byte-neutral result or a proof about original source labels. |
|06 negative|Commute the positive burst Y addition to test its native operand/CSE ownership. It reproduces03's entire candidate byte-for-byte. |
|07 negative|Use a double rather than a float capture for the mode2 vertical result, reflecting the native double addition/single final store. It also reproduces03 byte-for-byte. |

Stop after the two identical-output controls and select another complete peer.
Remaining differences are the mobility branch/shared-return placement, a
state1-store schedule, hoisted/repeated Y+100 loads, and count/index/step stack
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
stack/edge interpretation and is not pasted as source. Own Ghidra heap384MiB /
one CPU; compilation remains serial CPU0/nice10, with memory monitored.

Private recipes/probes remain under
`.analysis/exact-first-yukari-slot5c-20261024/`; the matching `build/` directory
retains full raw CFG/tables/literals, attestation/DB pins, all full probes and
diffs, formal comparisons and object/provenance. Existing accepted sources,
headers, flags and relocation bindings are unchanged. Exact ledger totals
remain1397 functions/327058 bytes, without an aggregate cold replay claim.
Continue another complete peer; retain this nonexact checkpoint and its neutral
controls instead of repeating them unchanged.
