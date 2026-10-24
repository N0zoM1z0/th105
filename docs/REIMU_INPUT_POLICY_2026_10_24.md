# Reimu input policy: complete exact family peer

## Accepted result

Reimu Fighter primary slot `+0x50 @ 0x00494810` accepts **6,952 callable bytes**
and the complete **7,008-byte emitted payload**, including the nine-entry
destination table and twenty-byte index remap. The first complete source
matches immediately. Formal and independent cold builds replay all **142
relocations** with zero differences. Metadata earns no authored-byte credit.

```sh
taskset -c 0 nice -n 10 python3 scripts/build.py \
  --unit exact-first-reimu-input-policy --compare --json
python3 scripts/audit-reimu-input-policy.py
```

Run both commands. The full audit requires exact section-tail length and every
payload byte under strict COFF ownership, relocation and literal checks. The
first formal object/provenance is retained; only this unit's active object and
sidecar were removed before an independent cold compile and both comparisons.
The pinned VC8 SP1 `/O2` profile remains unchanged.

Callable SHA256:
`f58599ad975db6bb650f4226e783acc20a962b093283134b276e86505f51e11d`.
Complete canonical SHA256:
`ab3651e356c3b26be806d10352bd9c5af0ea8c8c8101e4addfba7c262926125a`.

The ordinary complete body in `src/characters/ReimuInputPolicy.cpp` uses
declaration-only pointer views. Never construct or embed them. Original names,
complete owner layout and original ignored-return declarations remain unknown.
Declaration-only callees earn no new implementation or exact credit. No
assembly, target array, artificial padding, inert local, fake return, ABI/register
forcing, compiler search or source-shape experiment is introduced.

## Observed target facts and reviewed differences

Only original Japanese 1.06a SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`
is used. The existing roster RTTI anchor owns this primary slot+50 root. An
independent aligned pointer scan reads cell `0x006C417C` pointing to it.
Authored ownership remains unchanged; only this accepted row's origin evidence
becomes the generated `canonical-exact-authored` baseline.

Raw traversal closes all **1,992 instructions**, **42 RETs**, **seven external
tails**, every internal direct edge and all nine destination-table entries.
Callable end is exclusive `0x496338` after an internal JMP, with no alignment
bytes before metadata. The destination table occupies `0x496338..0x49635B`;
the remap occupies `0x49635C..0x49636F`. Native unsigned CMP EAX,19 admits the
twenty selectors200..219 before MOVZX through the remap. All twenty remapped
edges are independently read; missing selector cases go to the actual default
destination. The frame reserves eight bytes and saves EBX/EBP/ESI/EDI.

There are160 physical calls:123 direct and37 virtual slot+08 action calls.
Direct calls comprise five stage predicates, six deque subscripts, two front
calls, eleven finalizers,58 window queries,32 input initializations and nine
other gates. External tails go once to45DDA0, once to464200 and five times to
4633A0. The object owns130 REL32 and12 DIR32 fields: one numeric reference,
two table bases and nine destination entries. Existing double120.0 at
`0x006C3E70` is independently checked and used by FCOMP qword at `0x495C57`.
Used float captures retain native rounding before the double comparison.
No shared header or global relocation mapping changes.

Accepted family source supplies a hypothesis. Raw instructions, edges, arguments
and widths independently check the changed paths; an attested Ghidra call-view
corroborates interpretation and is not pasted as source. Both common air gate
minima are independently confirmed as2.

| Surface | Reimu behavior retained from native instructions |
| --- | --- |
| Ground records |After real front/window/range/eligibility checks, input initialization precedes the third deque read and sparse switch.200/201/206/208/209/210/214/219 finalize600/601/606/608/609/610/614/619. The initialization also occurs for default selector values. |
| Air records |200/201/208 finalize650/651/658 after the actual bounds and eligibility checks. Other values fall onward. |
| Ground masks4000/2000 |+60E550 for both, +60A546/545, then541/540 through flag+756. |
| Ground masks400/200 |+60B566/565, then561/560 through flag+757. |
| Ground masks40/20 |+60D531/530, +609526/525, then521/520 through flag+755. |
| Ground masks4/2 |+60C511/510, +608506/505, then query500 for both but execute501/500 through flag+754. |
| Air masks4000/2000 |+60A546/545, then541/540 only when both+60A/+60E equal zero. |
| Air masks40/20 |523/522 require both+609/+60D equal zero through flag+755. |
| Air masks4/2 |+60C513/512, +608508/507, then query502 for both but execute503/502 only when both+608/+60C equal zero. |
| First normal group |UP303 has no state303 fallback. State321/320/300 shortcuts retain their actual state>299 outer guard. Distance compares against double120.0. Air has one UP308 query. |
| Group+6F8 |Ground state200 path queries408. The repeated402, forward401 and fallback400 window calls precede resource checks. Air406 and404 queries also precede resource checks. No resource-failure skip is transplanted from peers. |
| Group+6FC |Ground state200 path queries418 before the common resource gate. Resource>=200 precedes eligibility and two independent412 attempts, then forward410 and repeated410 fallback. Air requires resource first, then UP416 or414 fallback; no415 path. |

Query/action differences, repeated calls, side effects on default paths and
post-call field reads remain explicit. No +12C clear, +730 reset or extra
sequence-selection call is added. Full equality also checks unchanged paths.

## Validation and retained evidence

IDA preflight rejects the other executable open there; no semantics or writes
from that session are used. One read-only Ghidra process independently attests
file/program identity, Windows x86 language/compiler, image base, entry
`0x68B9D2`, every raw-backed section and root hash. Root min/max/count matches
the raw extent. Temporary metadata is read back and rolled back; pinned primary
DB hashes remain unchanged. Analysis uses CPU0/nice10 and384 MiB heap; builds
run serially on CPU0/nice10.

Private recipes and first complete source remain under
`.analysis/exact-first-reimu-slot50-20261024/`. The corresponding `build/`
directory retains raw facts/disassembly, CFG closure, nine destinations and all
twenty remapped selector edges, attested views/logs/DB hashes, first full probe,
formal/cold comparisons, first formal object/provenance, relocation counts,
original origin row and input hashes. Generated-object negatives independently
damage the first destination and first remap byte. The full audit rejects both
at `+0x1B28 / 0x496338`, target67/source68, and `+0x1B4C / 0x49635C`,
target00/source01. The target stays untouched. Earlier input source/header pairs
remain unchanged. No broad runtime matrix or aggregate cold replay is claimed.
Continue remaining complete peers; Marisa stays parked at its recorded residual.
