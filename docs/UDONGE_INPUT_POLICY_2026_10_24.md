# Udonge input policy: complete exact family peer

## Accepted result

Udonge Fighter primary slot `+0x50 @ 0x005D2C70` accepts **6,684 callable bytes**
and the complete **6,724-byte emitted payload**, including all ten switch
entries. The first complete source matches immediately. Formal and independent
cold builds replay all **135 relocations** with zero differences. Metadata
earns no authored-byte credit.

```sh
taskset -c 0 nice -n 10 python3 scripts/build.py \
  --unit exact-first-udonge-input-policy --compare --json
python3 scripts/audit-udonge-input-policy.py
```

Run both commands. The full audit requires exact section-tail length and every
payload byte under strict COFF ownership, relocation and literal checks. The
first formal object/provenance is retained; only this unit's active object and
sidecar were removed before an independent cold compile and both comparisons.
The pinned VC8 SP1 `/O2` profile remains unchanged.

Callable SHA256:
`386b1e900824a871194c05d78b77c8eded86aae488d35d21b6675c72721d6823`.
Complete canonical SHA256:
`20fb17b9a6f95c25aff1e7810bbd682c60f140bef07ba14f5d5df1e66eb9d31d`.

The ordinary complete body in `src/characters/UdongeInputPolicy.cpp` uses
declaration-only pointer views. Never construct or embed them. Original names,
complete owner layout and original ignored-return declarations remain unknown.
Declaration-only callees earn no new implementation or exact credit. No
assembly, target array, artificial padding, inert local, fake return, ABI/register
forcing, compiler search or source-shape experiment is introduced. The two
three-float arrays are actual live spawn parameters, not shaping storage.

## Observed target facts and reviewed differences

Only original Japanese 1.06a SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`
is used. The existing roster RTTI anchor owns this primary slot+50 root. An
independent aligned pointer scan reads cell `0x006C5E7C` pointing to it.
Authored ownership remains unchanged; only this accepted row's origin evidence
becomes the generated `canonical-exact-authored` baseline.

Raw traversal closes all **1,919 instructions**, **40 RETs**, **six external
tails**, every internal direct edge and all ten destination-table entries.
Callable end is exclusive `0x5D468C` after an internal JMP, with no alignment
before metadata. The destination table occupies `0x5D468C..0x5D46B3`. The
native unsigned guard admits indices0..9; selector201/204 entries go to the
actual default path. The frame reserves20 bytes and saves EBX/EBP/ESI/EDI.

There are150 physical calls:116 direct and34 virtual slot+08 action calls.
Direct calls comprise five stage predicates, six deque subscripts, two front
calls, eleven finalizers,52 window queries,28 input initializations, nine other
gates, two object spawns and one input reset. External tails go once to45DDA0,
once to464200 and four times to4633A0. The object owns122 REL32 and13 DIR32
fields: two numeric references, one table base and ten destinations. Existing
float90.0 at `0x006C3D8C` and float2.0 at `0x006C13F0` are independently
checked. Used float captures preserve native rounding. No shared header or
global relocation mapping changes.

Accepted family source supplies a hypothesis. Raw instructions, edges, arguments
and widths independently check the changed paths; an attested Ghidra call-view
corroborates interpretation and is not pasted as source. Both common air gate
minima are independently confirmed as2.

| Surface | Udonge behavior retained from native instructions |
| --- | --- |
| Ground records |200/202/203/205/206/207/208/209 finalize600/602/603/605/606/607/608/609.201/204 follow the default path. |
| Air records |200/202/205 finalize650/652/655 after the actual front, window, range and eligibility checks. Other values fall onward. |
| Ground masks400/200 |+60E551/550, +60A546/545, then541/540 through flag+756. |
| Ground masks4/2 |+60C511/510, +608506/505, then501/500 through flag+754. |
| Ground masks40/20 |+60D531/530, +609526/525, then521/520 through flag+755. |
| Ground high-bit masks |+60F571/570, +60B566/565, then561/560 through flag+757. |
| Air masks40/20 |+609>=1 selects528/527 through flag+755; no fallback. |
| Air high-bit masks |+60B>=1 selects568/567 through flag+757; no fallback. |
| First normal group |Ground UP303 retains state303 fallback. State321/320 spawns object848 before322/321, resets input and then clears signed word+7A6. State300-to320 remains ordinary. Distance is float90.0. Air retains two independent308 attempts. |
| Group+6F8 |Ground forward401 precedes400 fallback. Air UP406 retains resource-failure skip, then404 fallback; no405 attempt. |
| Group+6FC |Ground state200 action418 has no window query; two separate412 attempts precede411/410. Air retains the<=0 forward415 path, rechecks vertical input after its window call, then416 or414 fallback. |

Query order, side effects, signed storage widths, repeated calls and post-call
field reads remain explicit. No +12C clear, +730 reset or extra sequence call
is added. Full equality also checks unchanged paths.

## Object-spawn ABI and payload evidence

The two calls at `0x5D3E6C` and `0x5D3EEA` target the already accepted66-byte
`Fighter_spawn_owned_object_via_manager @ 0x465190`. Fresh raw inspection confirms
ECX receiver, seven four-byte stack slots, float x/y, manager slot+04 forwarding,
EAX return forwarding and RET28. Its implementation remains unchanged. Original
nominal direction/variant widths remain ambiguous; this root passes the facing
byte zero-extended, unlike the signed-facing multiplication used in movement.

Native requests pass object848, current x/y, zero-extended byte+104, variant1,
address of three used floats, count3. The packets are
`{0.0f, float(signed word+140), 2.0f}` for321 and the same with1.0f for320.
Source uses real local float arrays and the existing conservative integer-word
forwarding view for their addresses. Both requests precede virtual action
selection. The shared reset call precedes the actual word+7A6 clear. No callee
implementation or original complete object layout is inferred from these calls.

## Validation and retained evidence

IDA preflight rejects the other executable open there; no semantics or writes
from that session are used. One read-only Ghidra process independently attests
file/program identity, Windows x86 language/compiler, image base, entry
`0x68B9D2`, every raw-backed section and root hash. Root min/max/count matches
the raw extent. Temporary metadata is read back and rolled back; pinned primary
DB hashes remain unchanged. Analysis uses CPU0/nice10 and384 MiB heap; builds
run serially on CPU0/nice10.

Private recipes and first complete source remain under
`.analysis/exact-first-udonge-slot50-20261024/`. The corresponding `build/`
directory retains raw facts/disassembly, full CFG/table closure, spawn-callee
bytes/hash/ABI evidence, attested views/logs/DB hashes, first complete probe,
formal/cold comparisons, first formal object/provenance, relocation counts,
original origin row and input hashes. A generated-object table negative fails
at `+0x1A1C / 0x5D468C`, targetB9/sourceBA; the target stays untouched. Earlier
input source/header pairs and the accepted spawn source remain unchanged.
No broad runtime matrix or aggregate cold replay is claimed. Continue the
remaining complete peer; Marisa stays parked at its recorded placement residual.
