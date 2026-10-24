# Alice input policy: complete exact family peer

## Accepted result

Alice Fighter primary slot `+0x50 @ 0x004FACD0` accepts **6,677 callable bytes**
and the full **6,720-byte emitted payload**, including alignment and all ten
switch entries. The first complete source matches immediately. Formal and
independent cold builds replay all **132 relocations** with zero differences.
Metadata earns no authored-byte credit.

```sh
taskset -c 0 nice -n 10 python3 scripts/build.py \
  --unit exact-first-alice-input-policy --compare --json
python3 scripts/audit-alice-input-policy.py
```

Run both commands. The full audit requires exact section-tail length and every
payload byte under strict COFF ownership, relocation and literal checks. The
first formal object/provenance is retained; only this new unit's active object
and sidecar were removed before an independent cold compile and both
comparisons. The pinned VC8 SP1 `/O2` profile remains unchanged.

Callable SHA256:
`9bcbd8182d30562238faa8230c47862293f36908edf76e9f499aab87377de261`.
Complete canonical SHA256:
`3b430021d2cc28d0ce1810de20a55331bcc62ffe584828375424624301cba764`.

The ordinary complete body in `src/characters/AliceInputPolicy.cpp` uses
declaration-only pointer views. Never construct or embed them. Original names,
complete owner layout and original ignored-return declarations remain unknown.
Declaration-only callees earn no new implementation or exact credit. No
assembly, copied target array, artificial padding, inert local, fake return,
ABI/register forcing, compiler search or source-shape experiment is introduced.

## Observed target facts and reviewed differences

Only original Japanese 1.06a SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`
is used. The existing roster RTTI anchor owns this primary slot+50 root. An
independent aligned pointer scan reads cell `0x006C4C2C` pointing to it.
Authored ownership is unchanged; only this accepted row's origin evidence
becomes the generated `canonical-exact-authored` baseline.

Raw traversal closes all **1,912 instructions**, **40 RETs**, **seven external
tails**, every internal direct edge and all ten table entries. Callable end is
exclusive `0x4FC6E5` after an internal JMP. Natural three-byte `LEA ECX,[ECX]`
alignment occupies `0x4FC6E5..0x4FC6E7`; the destination table occupies
`0x4FC6E8..0x4FC70F`. The native unsigned guard admits indices0..9. The frame
reserves eight bytes and saves EBX/EBP/ESI/EDI.

There are149 physical calls:113 direct and36 virtual slot+08 action calls.
Direct calls comprise five stage predicates, three deque subscripts, two front
calls, ten finalizers,53 window queries,31 input initializations and nine other
gates. External tails go once to45DDA0, once to464200 and five times to4633A0.
The object owns120 REL32 and12 DIR32 fields: one numeric reference, one table
base and ten destinations. Existing float140.0 at `0x006C4C60` is independently
checked and used by FCOMP dword at `0x4FBFB0`. Used float captures preserve
preceding native rounding. No shared header or global relocation map changes.

The accepted Sakuya/Komachi/Aya sources supply hypotheses. Raw instructions,
edges, arguments and widths independently check the changed paths; an attested
Ghidra call-view corroborates interpretation and is not pasted as source.
Both common air gate minima are confirmed as2.

| Surface | Alice behavior retained from native instructions |
| --- | --- |
| Ground records |200..209 finalize600..609 through the ten-entry table. |
| Air front call |The actual45D1B0 call remains, with its result ignored. No air deque/window/record/finalizer path is added. |
| Ground masks400/200 |+60D531/530, +609526/525, then521/520 through flag+755. |
| Ground masks4/2 |+608506/505, then501/500 through flag+754. |
| Ground masks40/20 |+60A546/545, then541/540 through flag+756. |
| Ground20000000 |Tries570 after signed word+7A6>=1 and signed byte+60F>=1. Then+60B query566 before checking word+7A4>=3, and query568 before checking+7A4<=2. Finally560 requires+7A6>=1. |
| Ground40000000 |An unconditional input initialization and conditional+491 bit write precede all tier checks. Tries570, then+60B565 requiring+7A4>=1 after its window query, then568 requiring+7A4==0, then560 requiring+7A6>=1. Every successful dispatch still performs its own real second initialization. |
| Air masks400/200 |Require signed byte+605>=2 and both+609/+60D equal zero; select523/522 through flag+755. |
| Air masks40/20 |+60A548/547; zero+60A/+60E fallback queries546/545 but executes543/542. These actual query/action differences remain. |
| Air masks4/2 |+608>=1 selects508/507 through flag+754. Order follows the native40/20 paths. |
| First normal group |Ground UP303 has no state303 fallback. Retains321/320/300 shortcuts and float140.0 distance. Air has one UP308 query. |
| Group+6F8 |The surface byte is compared specifically to1, not just zero. Ground forward401 precedes400 fallback. Air tries UP406 with resource-failure skip, then404 fallback. |
| Group+6FC |Ground state200 action418 has no window query. Retains two separate412 attempts; air has one UP416 attempt, then neutral/forward415 and414 fallback. |

Word+7A4/+7A6 accesses and their comparisons are signed. Their reads follow
the actual window calls rather than being cached or moved before them. The
eager40000000 input call remains even if no action succeeds. No +12C clear,
+730 reset or extra sequence-selection call is added. Full equality also
checks all unchanged paths, repeated eligibility tests and post-call reads.

## Validation and retained evidence

IDA preflight rejects the other executable open there; no semantics or writes
from that session are used. One read-only Ghidra process independently attests
file/program identity, Windows x86 language/compiler, image base, entry
`0x68B9D2`, every raw-backed section and root hash. Root min/max/count matches
the raw extent. Temporary metadata is read back and rolled back; pinned primary
DB hashes remain unchanged. Analysis uses CPU0/nice10 and384 MiB heap; builds
run serially on CPU0/nice10.

Private recipes and first complete source remain under
`.analysis/exact-first-alice-slot50-20261024/`. The corresponding `build/`
directory retains raw facts/disassembly, CFG/table closure, attested views/logs/
DB hashes, first complete probe, formal/cold comparisons, first formal object
and provenance, relocation counts, original origin row and input hashes. A
generated-object table negative fails at `+0x1A18 / 0x4FC6E8`, target17/source18;
the target stays untouched. Earlier input source/header pairs remain unchanged.
No broad runtime matrix or aggregate cold replay is claimed. Continue remaining
complete peers; Marisa stays parked at its recorded placement residual.
