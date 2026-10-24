# Patchouli input policy: complete exact family peer

## Accepted result

Patchouli Fighter primary slot `+0x50 @ 0x0051EF60` accepts **6,351 callable
bytes** and the complete **6,396-byte emitted payload**, including alignment
and all eleven switch entries. The first complete source matches immediately.
Formal and independent cold builds replay all **128 relocations** with zero
differences. Metadata earns no authored-byte credit.

```sh
taskset -c 0 nice -n 10 python3 scripts/build.py \
  --unit exact-first-patchouli-input-policy --compare --json
python3 scripts/audit-patchouli-input-policy.py
```

Run both commands. The full audit requires exact section-tail length and every
payload byte under strict COFF ownership, relocation and literal checks. The
first formal object/provenance is retained; only this unit's active object and
sidecar were removed before an independent cold compile and both comparisons.
The pinned VC8 SP1 `/O2` profile remains unchanged.

Callable SHA256:
`771b5434af8b13f42491842582152f7ccbdfe88a54a505188fc440d6932a0369`.
Complete canonical SHA256:
`9f517cea7b41772006c05e97ef82af42ef960a44bcc54a27c7ee250160b07e6a`.

The ordinary complete body in `src/characters/PatchouliInputPolicy.cpp` uses
declaration-only pointer views. Never construct or embed them. Original names,
complete owner layout and original ignored-return declarations remain unknown.
Declaration-only callees earn no new implementation or exact credit. No assembly,
target array, artificial padding, inert local, fake return, ABI/register forcing,
compiler search or source-shape experiment is introduced.

## Observed target facts and reviewed differences

Only original Japanese 1.06a SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`
is used. The existing roster RTTI anchor owns this primary slot+50 root. An
independent aligned pointer scan reads cell `0x006C4EFC` pointing to it.
Authored ownership remains unchanged; only this accepted row's origin evidence
becomes the generated `canonical-exact-authored` baseline.

Raw traversal closes all **1,810 instructions**, **35 RETs**, **six external
tails**, every internal direct edge and all eleven table entries. Callable end
is exclusive `0x52082F` after an internal JMP. Natural one-byte NOP alignment
at `0x52082F` precedes the table at `0x520830..0x52085B`. The native unsigned
guard admits indices0..10; selector208/209 entries go to the actual default
path. The frame reserves eight bytes and saves EBX/EBP/ESI/EDI.

There are139 physical calls:109 direct and30 virtual slot+08 action calls.
Direct calls comprise five stage predicates, six deque subscripts, two front
calls, ten finalizers,52 window queries,25 input initializations and nine other
gates. External tails go once to45DDA0, once to464200 and four times to4633A0.
The object owns115 REL32 and13 DIR32 fields: one numeric reference, one table
base and eleven destinations. Existing double120.0 at `0x006C3E70` is
independently checked and used by FCOMP qword at `0x52002B`. Used float captures
preserve native rounding before comparison. No shared header or relocation
mapping changes.

Accepted family source supplies a hypothesis. Raw instructions, edges, arguments
and widths independently check the changed paths; an attested Ghidra call-view
corroborates interpretation and is not pasted as source. Both common air gate
minima are independently confirmed as2.

| Surface | Patchouli behavior retained from native instructions |
| --- | --- |
| Ground records |200..207 and210 finalize600..607 and610.208/209 follow the default path. |
| Air records |Only201 finalizes651, after actual front/window/range/eligibility checks. Other values fall onward. |
| Ground masks400/200 |+60B546/545, then541/540 through flag+756. |
| Ground masks4000/2000 |+60D585 for both, then581/580 through the actual fifth flag+758. |
| Ground masks4/2 |+609506/505, then501/500 through flag+754. |
| Ground masks40/20 |Signed byte+611 selects571/570, +60C566/565, then561/560 through flag+757. |
| Ground high-bit masks |+60A526/525, then521/520 through flag+755. |
| Air masks4/2 |Both+609/+60E must equal zero, then503/502 through flag+754. |
| Air masks40/20 |+60C>=1 selects568/567 through flag+757; no fallback. |
| First normal group |UP303 has no state303 fallback. Retains320-to321 and300-to320; no321-to322 shortcut. Distance compares against double120.0. Air retains two independent308 attempts. |
| Group+6F8 ground |Two402 attempts precede a nested neutral-vertical block. Backward407 checks resource before its query; the following forward401 rechecks vertical input after the possible query and retains its resource-failure skip.400 remains the fallback. |
| Group+6F8 air |UP406 uses its actual resource guard. Neutral-vertical backward409 retains its resource-failure skip;404 remains the fallback. |
| Group+6FC |Ground state200 action418 has no window query; two separate412 attempts precede411/410. Air retains the<=0 forward415 path, rechecks vertical input after its query, then416 or414 fallback. |

Backward tests compare the signed facing products against zero independently
for+6B4 and+6D4. The second vertical read and repeated eligibility checks remain
explicit because intervening window calls can affect state. No +12C clear,
+730 reset or extra sequence/spawn call is added. Full equality also checks
unchanged paths and post-call reads.

## Validation and retained evidence

IDA preflight rejects the other executable open there; no semantics or writes
from that session are used. One read-only Ghidra process independently attests
file/program identity, Windows x86 language/compiler, image base, entry
`0x68B9D2`, every raw-backed section and root hash. Root min/max/count matches
the raw extent. Temporary metadata is read back and rolled back; pinned primary
DB hashes remain unchanged. Analysis uses CPU0/nice10 and384 MiB heap; builds
run serially on CPU0/nice10.

Private recipes and first complete source remain under
`.analysis/exact-first-patchouli-slot50-20261024/`. The corresponding `build/`
directory retains raw facts/disassembly, full CFG/table closure, attested views/
logs/DB hashes, first complete probe, formal/cold comparisons, first formal
object/provenance, relocation counts, original origin row and input hashes. A
generated-object table negative fails at `+0x18D0 / 0x520830`, targetA9/sourceAA;
the target stays untouched. Earlier input source/header pairs remain unchanged.
No broad runtime matrix or aggregate cold replay is claimed. The roster's
fifteen complete slot50 policies now have source: fourteen exact peers and
Marisa's separately recorded nonexact placement residual. Continue another
complete representative without repeating Marisa's neutral controls unchanged.
