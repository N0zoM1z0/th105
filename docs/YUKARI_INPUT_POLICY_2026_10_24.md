# Yukari input policy: complete exact family peer

## Accepted result

Yukari Fighter primary slot `+0x50 @ 0x0058C2E0` accepts **6,233 callable
bytes** and the full **6,300-byte emitted payload**, including alignment and
all sixteen switch entries. The first complete source matches immediately.
Formal and independent cold builds replay all **129 relocations** and produce
zero differences. Metadata earns no authored-byte credit.

```sh
taskset -c 0 nice -n 10 python3 scripts/build.py \
  --unit exact-first-yukari-input-policy --compare --json
python3 scripts/audit-yukari-input-policy.py
```

Run both commands. The full audit requires exact COFF section-tail length and
every payload byte through the strict owner, relocation and floating-literal
checks. The first formal object/provenance is retained; only this new unit's
active object/provenance is removed before the independent cold compile and
both comparisons. The pinned VC8 SP1 `/O2` profile remains unchanged.

Callable SHA256:
`edb5aad0e96f5d259eb54bc2ec1bec0b4f06dd86518a6103d8f2a5446a70dc8f`.
Complete canonical SHA256:
`6ad4c81e95ea54236fdcd3de48e1a8fa897f8f1a1d4deb83173f335138a9ef7d`.

The source is one ordinary complete body in `src/characters/YukariInputPolicy.cpp`
with declaration-only pointer views. Never construct or embed the views.
Original names, complete owner layouts and original ignored-return declarations
remain unknown. No assembly, target array, artificial padding, fake return,
inert local, ABI/register forcing or compiler/source-shape search is introduced.
Declaration-only callees earn no additional implementation or exact credit.

## Observed target facts

Only original Japanese 1.06a SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`
is used. The frozen RTTI roster anchor binds primary cell `0x006C591C` to this
slot+50 root. A raw aligned-pointer scan independently reads the same address.
Authored ownership is unchanged; this accepted row's origin evidence becomes
the generated `canonical-exact-authored` baseline.

Raw traversal closes all **1,734 instructions**, **26 RETs**, **seven external
tails**, every direct/internal edge and all sixteen indirect table entries.
The callable ends exclusively at `0x58DB39` after an internal JMP. Natural
three-byte `LEA ECX,[ECX]` alignment occupies `0x58DB39..0x58DB3B`; the table
occupies `0x58DB3C..0x58DB7B`. Entries208..214 go to the actual default path.
An initial nine-entry assumption fails whole-CFG closure; the native guard
`CMP EAX,0xF` and sixteen raw pointers establish the complete table before
semantic use. The frame reserves eight bytes and saves EBX/EBP/ESI/EDI.

There are126 physical calls:104 direct and22 virtual action-slot+08 calls.
Direct calls comprise five stage predicates, six deque subscripts, two front
predicates, ten finalizers,49 window queries,23 packed-input initializations
and nine other gates. External tails go once to45DDA0, once to464200 and five
times to4633A0. The object has111 REL32 and eighteen DIR32 fields: one numeric
reference, one table base and sixteen destinations. The existing double120.0
binding at `0x006C3E70` is independently checked, consumed by FCOMP qword at
`0x58D378`. Used float captures preserve the preceding native rounding.
No global relocation binding or shared header changes.

The ground callback at `0x58C3D0` targets the already accepted role-specific
`0x58C170` gate, instead of493F90. Native ECX receiver/two four-byte stacked
arguments, AL consumption and the existing367-byte callee/source agree with
the local declaration-only view. Only this new unit's explicit REL32 alias
changes; the existing gate implementation and its accepted descriptor are
untouched. This scope claims no new callee replay or duplicate exact credit.

## Independently reviewed changes

[Sakuya's exact source](SAKUYA_INPUT_POLICY_2026_10_24.md) supplies a hypothesis;
complete raw bytes, edges, widths and arguments independently check every
changed path. An attested Ghidra view corroborates the interpretation. Its
expressions are not mechanically pasted into source.

| Surface | Native behavior retained |
| --- | --- |
| Queued commands | Ground200..207 finalize600..607;215 finalizes615, with208..214 falling through. Air206 finalizes656. |
| Shared gates | Uses58C170 on ground. Both common air gates retain minimum2 and the actual mode count. |
| Ground masks4000/2000 | +60B566/561 and565/560 through flag+757. |
| Ground masks400/200 | +609526/521 and525/520 through flag+755. |
| Ground masks40/20 | +60A546/541 and545/540 through flag+756. |
| Ground masks4/2 | +60C511/510, +608505 for both; the500 query dispatches501 for mask4 and500 for mask2. |
| Air masks4000/2000 | Both+60B/+60F must be zero, then563/562 through flag+757. |
| Air masks40/20 | +60A>=1 queries546/545 but dispatches548/547 through flag+756, without a regular fallback. |
| Air masks4/2 | Both+608/+60C must be zero; both query500, then dispatch503/502 through flag+754. |
| Actual+12C stores | Special dispatch and normal actions clear float+12C before the virtual action; first-group state200-to305 does not clear it. No post-action store is substituted. |
| First normal group | UP303 accepts its real state303 fallback; the chain tests state>299 explicitly. Distance is double120.0. Air neutral309 tests facing times+6B4, and air308 has one UP attempt. |
| Group+6F8 | State200-to408 requires a query;402/400 and air406/404 query before resource checks. Ground400 is queried independently in forward and fallback paths. |
| Group+6FC | State200-to418 requires a query; following paths check resource before eligibility and direction/query attempts, retaining repeated412 and final eligibility after410/414 queries. |

The first complete source emits all6,300 bytes and matches without a source
correction or code-generation control. Preserve actual query/action-number
differences, store order and repeated calls rather than normalizing them to a
peer's apparent pattern.

## Validation and retained evidence

IDA preflight rejects the other executable still open there; no semantics or
writes from that session are used. One read-only Ghidra process independently
attests file/program hashes, language/compiler, image base, entry `0x68B9D2`,
every raw-backed section and the root hash. Temporary function/ABI, observed
tail and virtual-call metadata is read back and rolled back; pinned primary
DB hashes are unchanged. CPU0/nice10 and384 MiB heap bound analysis. Builds are
serial on CPU0/nice10.

Private recipes and the first complete source snapshot remain under
`.analysis/exact-first-yukari-slot50-20261024/`. The corresponding `build/`
directory retains raw facts/disassembly, complete CFG/table closure, attested
views/logs/database pins, formal/cold receipts, first formal object/provenance,
relocation counts, original origin row and input hashes. A generated-object
table negative fails at `+0x185C / 0x58DB3C`, target29/source2A; the target stays
untouched. Earlier exact input sources and the existing Yukari gate inputs are
unchanged. No broad runtime matrix or aggregate cold replay is claimed.
