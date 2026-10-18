# Reimu: complete returning fans, rings and radial volleys

The `478FA0` root now passes **1244 native comparisons through complete
821/822/869 requests and their returning continuations**. This includes the
33-object ring/grid, signed negative timers, real frame wrap/block changes
and both texture-publication branches. Earlier wrapper-entry comparisons
could not establish these later requests. The selected game source and exact
ledgers remain unchanged.

## Target and real execution

The target remains original Japanese TH10.5 v1.06a, SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
The root is `[478FA0,48CE2E)`,81550 bytes, callable SHA-256
`dbf6f375a809fea91cbbccf0f8cff2196f40cba11458c98e475a290b623053e6`.
The mandatory IDA preflight still rejects the other attached executable.
Evidence here comes from hash-attested PE instructions and native execution;
no analysis database or target instruction is changed.

The auditor reuses [the real owned-object backend](REIMU_OWNED_RETURNS_2026_10_18.md):
actual493750 construction,256 preallocated/released objects,465190/4938D0
requests, real pool/parameter allocation and ReimuObject callbacks, root RET,
then actual4939C0 destruction. Original code stays at400000, the qualified
source-derived root at4000000. All original `.text` and candidate bytes remain
protected and checked unchanged after each case. The105 real kernel32 imports,
65 blocked imports, real CRT setup and PC53/64 initialization are unchanged.

The native observer now records actual tracked-object counts, heap parameter
extents and logical child deques rather than assuming the811 family shape.
It checks pool ownership, unique slots, generation correspondence and reciprocal
parent/child links. Family-specific expectations are checked on target results
in Python. The existing811 contract retains its exact action, active-state,
descending-slot/generation and alternating parent/companion checks. Candidate
snapshots are compared as observed, without masking or correcting bytes.

## Texture context and animation boundaries

Action669 calls real `Fighter_publish_texture_state @45F560` before its
counter paths. Its170 canonical bytes show two branches:

- When both Fighters' `+6A0` durations are zero, checked deque index6 is
  published to both `manager+D8` and `manager+DC`.
- Otherwise the same checked entry is published to
  `manager+D8+4*signed(actor+334)`. These fixtures use index0, so DC remains
  unchanged. Both branches set actor+6A2 to6 and actor+6A0 to2.

The fixture supplies a valid eight-entry VC8 deque at actor+68C with read-only
texture IDs `A1000000..A1000007`. Global6FBCA0 points to a zeroed writable
publication block; D8/DC start with distinct sentinels. The actual42D1B0
checked accessor and45F560 execute without replacement. Each snapshot includes
the fullE0-byte publication prefix. This is a narrow data context, not a full
BattleObjectManager constructor or rendering/GPU claim.

Three coherent read-only animation graphs supply duration32, duration3 with
looping mode1, and duration4 with550/551 sequence1 mode0. Each has nine
sequences, fourteen-frame capacity and one active frame. Target4351C0's62
bytes and45C1A0's67 bytes independently establish that duration expiry calls
the real frame virtual; only wrap with mode0 requests the next block.
Mode1 wraps the timer while retaining sequence and incremented counter.
Mode0 advances to sequence2, clears its counter and runs the root's airborne
continuation: VX=-200,VY=2,Y+=100,alpha=0,AY=0.5. No cached-duration or
instruction substitution is used to obtain a transition. Timer3/duration4
covers ordinary expiry after eight real requests; timer3/9 at duration3 and
timer9 at duration4 deliberately exercise already overdue timer states.

An early check incorrectly expected every frame wrap to advance a block and
the busy texture branch to update DC. Complete target/source streams already
agreed; the canonical helper instructions above resolved these checker errors.
The corrected checks also require the distinct mode0 continuation explicitly.

## Complete cohorts and comparison

| Root actions | Contexts | Inputs | Tracked objects per process |
| --- | --- | ---: | ---: |
|545/546|sequence2 launch; sequence3 low/high signed skill fans|240|1600|
|550/551|timers-3,0,3,9,12; duration32/3/4; loop and block advance|400|4880|
|669|counters0/2/8/10/180/181/240; phase/height and texture-duration paths|604|4800|

The full inputs cross raw facings-128,-1,0,1,127, PC53/64 and MT seeds0/5489;
669's four late-counter boundary inputs use facing1/seed5489. Fan skills
include3,4,-128,127. Radial geometry includes phase359.75 and Y=33554432.
All random draws, orientation calculations and callback effects execute real
target helpers; no parallel RNG/trigonometry oracle supplies results.

Target checks require every copied parameter array in order: seven/twelve
821 fan objects or one launch object; eight822 random-ring objects plus the
25-object five-sector/five-layer grid at timer0; and869's three/four-ray
groups followed by cadence-dependent modes4/5. Counter180 still emits;
181 does not, and240 takes the real next-block/AY=0.2 early return. All
requests return before the root's next array update and final state work.

The comparison includes all4096 actor bytes, all904 bytes of every active
object, parameter allocation addresses/extents/full bytes, logical children,
MT index/state, pool counters, FP control and texture-publication prefix.
No pointer, padding or compared byte is masked. Allocator metadata, inactive
objects, unused container capacity and other globals remain outside scope.

All1244 candidate comparisons pass, and an independent target process repeats
exactly. Each full stream contains **19,036,468 bytes**, SHA-256
`d1f0be128ea7fa4c81d57b7de5bcd8bdfb259954fc21fe58827fed9ed0b82f08`.
Each process creates **11,280 real tracked objects** across these inputs.

A compiled negative changes only regular821 fan spacing9 to10, preserving
the i=0 requests and request count. All four unoptimized540/541/545/546 arms
contain the expression; only545/546 survive constant folding. The object
retains the strict callable/metadata envelope and every static stack/request
contract. It fails **160/240** focused fan inputs. Actor, MT, pool and texture
prefixes agree in all240. In80 differing low-skill cases the first complete
object record is equal; in80 high-skill cases the first three are equal.
Thus later fan errors are detected after correct initial requests. The
private control never changes selected source.

## Reproduction and limits

Run serially on CPU0 at nice10:

```bash
nice -n 10 taskset -c 0 python3 -B scripts/audit-reimu-circular-returns.py
nice -n 10 taskset -c 0 python3 -B scripts/audit-reimu-owned-returns.py --smoke
```

Use `--cohort fan821`, `--cohort ring822` or `--cohort rays869` for a focused
recheck; `--smoke` selects five inputs/99 objects. For the private negative,
copy the base producer's expanded source/header under `build/`, require four
occurrences of `40.0 - i * 9.0 : i * 9.0 + 30.0`, and change just those two
step constants to10. Reuse the ordinary compile receipt's command, changing
only source and `/Fo` paths. Pass the result using `--object`, `--cohort fan821`
and a separate output directory; the audit returns1 for160 differences.

Receipts are under `build/reimu-circular-returns/` and
`build/reimu-circular-control/native/`; bounded helper bytes/readback are under
`build/reimu-circular-native/`. Large streams, temporary native executables and
negative build products are cleaned after verification. The changed shared
owned observer also passes the14-input/50-object legacy smoke, including811
companions and three/four-word arrays:139244 identical bytes per stream, SHA
`03ab7121bdcac6dc7e9d3353429080dba808c92e39d2127662dea2e692f01c9c`.
The effect observer/common native header are unchanged; no old full matrix or
aggregate replay is claimed. All9 primary database files hash unchanged by
streamed reads; no Ghidra process or clone was used. Child peak RSS is301MiB.

Selected object SHA remains
`41bf3b15ff2dbf6cf7c25e0c0191ab18d963782e0e7fab5d3b9af82c0ab245fd`,
canonical payload SHA remains
`826889ee7ec055e44def5cc1602de2fae75f58403e2332194ec3b20cd55dc0d3`.
Prefix81544/text82916/frame570h and strict first+17/478FB1 persist. Native
equality is not canonical byte equality: the root remains unclassified and
declaration-only, with no new source-present or exact credit. Remaining
effect/projectile families, arbitrary resources/heaps/world states, exceptions,
full application startup and physical sharing/source-context gaps remain open.
