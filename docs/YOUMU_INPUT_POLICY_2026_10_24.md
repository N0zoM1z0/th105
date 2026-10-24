# Youmu input policy: complete exact family member

## Accepted result

Youmu Fighter primary slot `+0x50 @ 0x0053B410` accepts **6,017 callable
bytes** and the full **6,052-byte emitted payload**, including alignment and
all eight switch destinations. The first successfully compiled complete source
matches immediately. Formal and independent cold builds replay all **121
relocations** and produce zero differences. Only callable bytes earn authored
credit; the adjacent metadata does not.

```sh
taskset -c 0 nice -n 10 python3 scripts/build.py \
  --unit exact-first-youmu-input-policy --compare --json
python3 scripts/audit-youmu-input-policy.py
```

Run both commands. The full-payload audit requires exact COFF section-tail
length and compares every byte using strict owner, relocation and floating
literal validation. The first formal object/provenance is retained, then only
this new unit's active object/provenance is removed before an independent
compile and both comparisons. The pinned VC8 SP1 `/O2` profile is unchanged.

Callable SHA256:
`36ee7339ea87c4507577430e91dfb984733f3111e75200191c2451803c17916d`.
Complete canonical SHA256:
`050e801122ba3cee6da69fb3abdcca297922e24d08913ef938c1b4e42a962fa1`.

The source is one ordinary complete body in `src/characters/YoumuInputPolicy.cpp`
with declaration-only pointer views. Do not construct or embed the views.
Original names, complete layouts and original ignored-return declarations remain
unknown. There is no assembly, target array, padding, fake return, inert local,
ABI/register forcing or compiler/profile search. Declaration-only callees earn
no implementation or exact credit.

## Observed target facts

Only original Japanese 1.06a SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`
is used. The frozen roster RTTI anchor binds cell `0x006C5194` to Youmu primary
slot `+0x50`; an independent raw pointer scan reads the same destination.
Authored ownership remains unchanged. Only this accepted row's generated
origin evidence becomes `canonical-exact-authored`.

Raw CFG traversal closes all **1,714 instructions**, **28 RETs**, **nine external
tails**, every internal direct edge and all eight switch destinations.
The callable ends exclusively at `0x53CB91` after an internal JMP. Natural
three-byte `LEA ECX,[ECX]` alignment occupies `0x53CB91..0x53CB93`, followed by
the eight-entry table at `0x53CB94..0x53CBB3`. The frame reserves eight bytes
and saves EBX/EBP/ESI/EDI.

There are **134 physical calls**: 101 direct, 30 virtual action-slot `+0x08`
calls and three sequence-slot `+0x0C` calls. Direct calls comprise five stage
predicates, five deque subscripts, two front predicates, eight finalizers,
49 command-window queries, 23 packed-input initializations and nine other
gates. External tails go once to `0x45DDA0`, twice to `0x464200`, and six times
to `0x4633A0`. The object has110 REL32 and eleven DIR32 fields: two numeric
references, one table base and eight destinations.

The new sequence calls are independently located at `0x53B75D`, `0x53B7BB`
and `0x53C368`. Youmu's actual primary cell `0x006C5150` points to the already
accepted `0x45C390` selector. The pointer-only view uses the existing selector's
`int select_sequence(int)` ABI view: ECX receiver, one four-byte stack slot,
callee cleanup, ignored result. This does not establish the original nominal
parameter/return declarations. Action calls retain their distinct `+0x08` slot.

Two already registered constants are independently checked: the eight bytes at
`0x006CD190` are double100.0, consumed by FCOMP qword at `0x53C28C`; the four
bytes at `0x006C3D8C` are float90.0, consumed at `0x53C429`. Used float captures
preserve both subtraction and absolute-value rounding before comparison. No
shared relocation mapping or accepted header changes.

## Independently reviewed family differences

[Suika's exact body](SUIKA_INPUT_POLICY_2026_10_24.md) supplies a source hypothesis.
Every changed field, argument, edge and call order is reviewed against raw
instructions. Attested Ghidra expressions corroborate the interpretation; they
are not mechanically pasted into source. Structural alignment is diagnostic
only, never acceptance.

| Surface | Youmu behavior retained from native instructions |
| --- | --- |
| Queued commands | Ground records200..207 finalize600..607. Air records200..299 pack input and return without an additional record-equality test or finalizer. |
| Ground540 sequence | Under resource>=0/mask60/state540, sequence1/frame>=6 packs input, reselects540, selects2 and continues. A subsequent fresh sequence0/frame>=7 check selects6 or1 according to bit40 and signed byte+606>=2, then continues. |
| Ground masks400/200 | Retains+60D531/530, +609526/525, then521/520 through flag+755. |
| Ground masks40/20 | Adds+60E550, then+60A546/545, then540 through flag+756. Both550 successes share a physical block. |
| Ground masks4/2 | +608506/505 share the actual500 fallback through flag+754. |
| Ground high-bit masks | Adds+60F571/570 before+60B566/565 and561/560, through flag+757. |
| First ground normal group | Adds the UP/double100.0 distance311 branch,303 state fallback,305/sequence0 reselect with sequence1, and322-to323 chain. The later301 threshold remains float90.0. |
| Second normal group | State200 transitions408/418 require real window queries. In group+6F8,402/401/400 and air406/404 query before resource checks; no copied405 branch or resource-failure skip is added. |
| Final ground group | Checks resource once before eligibility and direction/query attempts412/411/410;410 retains its repeated eligibility after the query. |
| Final air group | Checks resource before eligibility, then attempts UP416, neutral/forward415 and414 fallback with its actual repeated eligibility. |

The first source-composition attempt accidentally cut at an inner `else` and
failed syntax checking; its source and compiler log are retained as probe00.
Fixing that private composition boundary produces probe01, the first complete
compiled body, which matches all6,052 bytes without code-generation tuning.

## Validation and retained evidence

The IDA preflight rejects the other open executable; no semantics or writes
from that session are used. A single read-only Ghidra process independently
attests file/program hashes, language/compiler, image base, entry `0x68B9D2`,
every raw-backed section and the root hash. Temporary function/ABI, observed
tails and virtual-call metadata are read back and rolled back. A second view
labels the three sequence sites separately; their ABI storage is unchanged.
Pinned primary database files remain byte-identical. An intervening prelaunch
check saw another Java/Ghidra process and refused to start; after that PID no
longer existed, the serial read-only pass ran successfully. No unknown process
was killed. Each analysis pass uses CPU0/nice10 and384 MiB heap; builds are serial.

Private recipes and complete/failed source snapshots are retained under
`.analysis/exact-first-youmu-slot50-20261024/`. The corresponding `build/`
directory retains raw facts/disassembly, whole CFG/table closure, family
comparison, attestation/logs/database hashes, formal/cold receipts, first formal
object/provenance, relocation counts and original origin-baseline row.

A generated-object table negative fails at `+0x1784 / 0x53CB94`, target57 /
source58. The target is never patched. Earlier Remilia/Tenshi/Sakuya/Suika
source/header inputs stay unchanged. No broad runtime matrix or fresh aggregate
cold replay is claimed. Continue complete independently reviewed slot+0x50 peers.
