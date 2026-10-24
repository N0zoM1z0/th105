# Iku input policy: complete exact family peer

## Accepted result

Iku Fighter primary slot `+0x50 @ 0x00631340` accepts **6,302 callable bytes**
and the full **6,348-byte emitted payload**, including alignment and all eleven
switch entries. The first complete source matches immediately. Formal and
independent cold builds replay all **131 relocations** with zero differences.
Metadata earns no authored-byte credit.

```sh
taskset -c 0 nice -n 10 python3 scripts/build.py \
  --unit exact-first-iku-input-policy --compare --json
python3 scripts/audit-iku-input-policy.py
```

Run both commands. The full audit requires exact section-tail length and every
payload byte through strict COFF owner, relocation and floating-literal checks.
The first formal object/provenance is retained; only this new unit's active
object/provenance is removed before the independent cold compile and both
comparisons. The pinned VC8 SP1 `/O2` profile is unchanged.

Callable SHA256:
`9d6484a53f7c990fba703935d961759a3f1771e240d8d575af1a251429aa3319`.
Complete canonical SHA256:
`5628641c925c65b24ce8feae7a7be22d6e680d8ffa83ee05de4dc5029931f7a3`.

The source is one ordinary complete body in `src/characters/IkuInputPolicy.cpp`
with declaration-only pointer views. Never construct or embed the views.
Original names, full owner layouts and original ignored-return declarations
remain unknown. No assembly, target array, artificial padding, inert local,
fake return, ABI/register forcing or compiler/source-shape search is introduced.
Declaration-only callees receive no new implementation or exact credit.

## Observed target facts and reviewed differences

Only original Japanese 1.06a SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`
is used. The frozen roster RTTI anchor binds primary cell `0x006C657C` to this
slot+50 root; a raw aligned-pointer scan independently reads the same address.
Authored ownership is unchanged; this accepted row's origin evidence becomes
the generated `canonical-exact-authored` baseline.

Raw traversal closes all **1,813 instructions**, **36 RETs**, **nine external
tails**, all internal direct edges and all eleven table entries. The callable
ends exclusively at `0x632BDE` after a tail JMP. Natural two-byte `MOV EDI,EDI`
alignment occupies `0x632BDE..0x632BDF`; the table occupies
`0x632BE0..0x632C0B`. Record204 points to the actual default path. The frame
reserves eight bytes and preserves EBX/EBP/ESI/EDI.

There are141 physical calls:109 direct and32 virtual action-slot+08 calls.
Direct calls comprise five stage predicates, six deque subscripts, two front
predicates, twelve finalizers,51 window queries,24 packed-input initializations
and nine other gates. External tails go once to45DDA0, once to464200 and seven
times to4633A0. The object has118 REL32 and thirteen DIR32 fields: one numeric
reference, one table base and eleven destinations. Existing double120.0 at
`0x006C3E70` is independently checked and consumed by FCOMP qword at `0x63240E`.
Used float captures preserve preceding subtraction/absolute-value rounding.
No shared header or global relocation mapping changes.

[Sakuya's exact body](SAKUYA_INPUT_POLICY_2026_10_24.md) supplies a hypothesis.
Complete raw byte, edge, argument and width review checks all changed paths;
attested Ghidra expressions corroborate interpretation and are not pasted as
source. Both common air gate minima are independently confirmed as2.

| Surface | Iku behavior retained from native instructions |
| --- | --- |
| Ground records |200..203 and205..210 finalize600..603 and605..610.204 follows the default path. |
| Air records |200-to650 or210-to660. After all front/window/eligibility checks succeed, any other record returns immediately; it does not continue to later special or normal paths. |
| Ground masks400/200 |+609526/521 and525/520 through flag+755. |
| Ground masks4/2 |+60C510 for both, then+608506/505 and501/500 through flag+754. |
| Ground masks40/20 |+60F571/570, +60B566/565, then561/560 through flag+757. |
| Ground high-bit masks |Mask40000000 queries545 but dispatches546, then queries541 but dispatches540. Mask20000000 uses545-to545 and540-to540 through flag+756. |
| Air masks40/20 |+60F573/572, then+60B queries573 for either mask but dispatches568/567.563/562 fallback requires both+60B and+60F to equal zero. |
| First normal group |State300 and320 both transition321;321 transitions322. Distance is double120.0. Retains both independent air308 queries and actual309 neutral gate. |
| Group+6F8 |Ground forward path queries401 before400 fallback. Air omits the peer's neutral/forward404 pre-attempt; UP406 preserves its resource-failure skip to group+6FC. |
| Group+6FC air |After the actual415 attempt and fresh direction reads, a negative facing-times+6B4 product selects417; the other upper path selects416.414 fallback retains its repeated eligibility. |

No +12C clear, +730 reset or mode replacement from another character is added.
Signed field widths, independent queries and post-call reads remain explicit.
The first complete source emits the complete6,348-byte exact payload; no source
correction or code-generation control is needed.

## Validation and retained evidence

IDA preflight rejects the other executable open there; no semantics or writes
from that session are used. One read-only Ghidra process independently attests
file/program identity, Windows x86 language/compiler, image base, entry
`0x68B9D2`, every raw-backed section and the root hash. The decompiled root's
min/max/count are checked against the raw accepted extent. Temporary metadata
is read back and rolled back; pinned primary database hashes remain unchanged.
Analysis uses CPU0/nice10 with384 MiB heap; builds run serially on CPU0/nice10.

Private recipes and the first complete source snapshot remain under
`.analysis/exact-first-iku-slot50-20261024/`. The corresponding `build/` directory
retains raw facts/disassembly, whole CFG/table closure, attested views/logs/DB
hashes, formal/cold receipts, first object/provenance, relocation counts,
original origin row and input hashes. A generated-object table negative fails
at `+0x18A0 / 0x632BE0`, target89/source8A; the target stays untouched. Previous
accepted input sources remain unchanged. No broad runtime matrix or aggregate
cold replay is claimed. Continue remaining complete peers; Marisa stays parked.
