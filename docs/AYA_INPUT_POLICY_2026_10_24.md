# Aya input policy: complete exact family peer

## Accepted result

Aya Fighter primary slot `+0x50 @ 0x00618660` accepts **7,161 callable bytes**
and the full **7,216-byte emitted payload**, including alignment and all thirteen
switch entries. Formal and independent cold builds replay all **146 relocations**
with zero differences. Metadata earns no authored-byte credit.

```sh
taskset -c 0 nice -n 10 python3 scripts/build.py \
  --unit exact-first-aya-input-policy --compare --json
python3 scripts/audit-aya-input-policy.py
```

Run both commands. The full audit requires exact section-tail length and every
payload byte under strict COFF ownership, relocation and literal checks. The
first formal object/provenance is retained; only this unit's active object and
sidecar were removed before an independent cold compile and both comparisons.
The pinned VC8 SP1 `/O2` profile remains unchanged.

Callable SHA256:
`7a322264cec526c517097f5faaab431324c20222b276f57c2d813cf94ca0ef46`.
Complete canonical SHA256:
`27ca5b6b8e56b4099e251f654b0f53b24ba4100eb13fe96a79df110ba65377da`.

The ordinary complete body in `src/characters/AyaInputPolicy.cpp` uses
declaration-only pointer views. Never construct or embed them. Original names,
complete owner layout and original ignored-return declarations remain unknown.
No callee implementation or additional callee exact credit is claimed. No
assembly, copied target array, artificial padding, inert local, fake return,
ABI/register forcing or compiler-profile search is introduced.

## Observed target facts and reviewed differences

Only original Japanese 1.06a SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`
is used. The existing roster RTTI anchor owns Aya's primary vtable `0x006C62D4`;
an independent aligned pointer scan reads the slot+50 cell `0x006C6324` pointing
to this root. Authored ownership is unchanged. Only its accepted origin evidence
is updated to the generated `canonical-exact-authored` baseline.

Raw traversal closes all **2,021 instructions**, **39 RETs**, **seven external
tails**, every internal direct edge and all thirteen table entries. Callable
end is exclusive `0x61A259` after an internal JMP. Natural three-byte
`LEA ECX,[ECX]` alignment occupies `0x61A259..0x61A25B`; the destination table
occupies `0x61A25C..0x61A28F`. The native unsigned guard admits indices0..12.
Ground entries203/204/207..210 go to the actual default path. The frame reserves
eight bytes and saves EBX/EBP/ESI/EDI.

There are157 physical calls:122 direct and35 virtual slot+08 action calls.
Direct calls comprise five stage predicates, six deque subscripts, two front
calls, ten finalizers,61 window queries,29 input initializations and nine other
gates. External tails go once to45DDA0, once to464200 and five times to4633A0.
The object owns129 REL32 and17 DIR32 fields: three numeric references, one
table base and thirteen table destinations. Existing literal maps independently
match float90.0 at `0x006C3D8C` and double480.0 at `0x006C0EB0`. No shared
header or global relocation mapping changes.

The accepted Sakuya/Komachi sources supply hypotheses. Full raw instructions,
edges, arguments and widths independently check the changed paths; an attested
Ghidra call-view corroborates interpretation and is not pasted as source.
Both common air gate minima are confirmed as2.

| Surface | Aya behavior retained from native instructions |
| --- | --- |
| Ground records |200/201/202/205/206/211/212 finalize600/601/602/605/606/611/612. |
| Air records |203 finalizes603;211/212 finalize661/662. Other values fall onward. All real front, window, range and eligibility checks remain. |
| Ground masks4000/2000 |+60B query/action565 for both, then561/560 through flag+757. |
| Ground masks4/2 |+60C511/510, +608506/505, then500 for both through flag+754. |
| Ground masks40/20 |+60D530 for both, +609526/525, then521/520 through flag+755. |
| Ground high-bit masks |+60E>=1 selects551/550 through flag+756; no lower-tier fallback. |
| Air masks4000/2000 |+60B>=1 queries/selects567 for both. The2000 override checks flag+756, while success writes flag+757. This actual difference is preserved. |
| Air masks4/2 |+608508/507, then502 for both through flag+754. |
| Air masks40/20 |+60D532 for both, +609528/527, then523/522 only when both+609/+60D equal zero. |
| Air high-bit masks |+60E553/552, +60A546/545, then540 for both only at height<=480.0. |
| First normal group |Ground UP303 retains state303 fallback and the321/320/300 shortcuts. Distance is float90.0. Air has one UP308 query; no separate UP/FORWARD308 attempt. |
| Group+6F8 |Ground forward401 precedes400 fallback. Air tries UP406, with the real resource-failure skip, then404 fallback; no neutral/forward405 attempt. |
| Group+6FC |Ground state200 path queries418. Retains repeated UP/FORWARD then UP412 ground and416 air queries, followed by411/410 ground and415/414 air fallbacks. |

No +12C clear, +730 reset or extra sequence-selection call is added. Signed
field widths, independent repeated calls and post-call field reads remain
explicit. Full equality independently checks all unchanged paths as well.

## Evidence-backed correction and validation

The first complete source emits the exact target length, metadata and all but
two bytes. Its canonical SHA256 is
`dc72d9b49ffd9bc7c99dfd3ea7f4fdee2fe8cc54aeda5c018a5940eedcda3802`.
Only `TEST AH,05` versus native `TEST AH,41` at `0x61971F` and `0x61986E`
differs. Both follow FCOMP qword480.0 and precede JP. Native41 admits the less
and equal cases and rejects greater/unordered;05 rejects equal too. Correcting
the actual source condition from `<480.0` to `<=480.0` makes the entire7,216-byte
payload exact. This is a semantic correction, not a floating-environment or
instruction-spelling control. No other source correction is needed.

IDA preflight rejects the other executable open there; no semantics or writes
from that session are used. One read-only Ghidra process independently attests
file/program identity, Windows x86 language/compiler, image base, entry
`0x68B9D2`, every raw-backed section and root hash. The root min/max/count is
checked against the raw extent. Temporary metadata is read back and rolled
back; pinned primary DB hashes remain unchanged. Analysis uses CPU0/nice10 and
384 MiB heap; builds run serially on CPU0/nice10.

Private recipes and first complete source remain under
`.analysis/exact-first-aya-slot50-20261024/`. The corresponding `build/` directory
retains raw facts/disassembly, CFG/table closure, attested call-views/logs/DB
hashes, both source receipts, formal/cold comparisons, first formal object and
provenance, relocation counts, original origin row and input hashes. A
generated-object table negative fails at `+0x1BFC / 0x61A25C`, targetA9/sourceAA;
the target stays untouched. Earlier input source/header pairs remain unchanged.
No broad runtime matrix or aggregate cold replay is claimed. Continue remaining
complete peers; Marisa stays parked at its recorded placement residual.
