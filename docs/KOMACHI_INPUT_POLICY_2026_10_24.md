# Komachi input policy: complete exact family peer

## Accepted result

Komachi Fighter primary slot `+0x50 @ 0x005F7AB0` accepts **6,181 callable
bytes** and the full **6,232-byte emitted payload**, including alignment and
all twelve switch entries. The first complete source matches immediately.
Formal and independent cold builds replay all **124 relocations** with zero
differences. Metadata earns no authored-byte credit.

```sh
taskset -c 0 nice -n 10 python3 scripts/build.py \
  --unit exact-first-komachi-input-policy --compare --json
python3 scripts/audit-komachi-input-policy.py
```

Run both commands. The full audit requires exact section-tail length and every
payload byte through strict COFF owner, relocation and floating-literal checks.
The first formal object/provenance is retained; only this new unit's active
object/provenance is removed before the independent cold compile and both
comparisons. The pinned VC8 SP1 `/O2` profile remains unchanged.

Callable SHA256:
`bb4b8a436dfb53779f9dc38d4b4c949cd9c335af6f152aa426809357b70c71d0`.
Complete canonical SHA256:
`8d53e8dd92bdea44be96ed4ef0ded1fae0fb68e336f8e07edd721bc735c5c012`.

The source is one ordinary complete body in `src/characters/KomachiInputPolicy.cpp`
with declaration-only pointer views. Never construct or embed the views.
Original names, complete owner layouts and original ignored-return declarations
remain unknown. No assembly, target array, artificial padding, fake return,
inert local, ABI/register forcing or compiler/source-shape search is introduced.
Declaration-only callees receive no new implementation or exact credit.

## Observed target facts and reviewed differences

Only original Japanese 1.06a SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`
is used. The frozen roster RTTI anchor binds primary cell `0x006C60B4` to this
slot+50 root; a raw aligned-pointer scan independently reads the same address.
Authored ownership is unchanged; this accepted row's origin evidence becomes
the generated `canonical-exact-authored` baseline.

Raw traversal closes all **1,762 instructions**, **34 RETs**, **six external
tails**, every internal direct edge and all twelve indirect table entries.
The callable ends exclusively at `0x5F92D5` after an internal JMP. Natural
three-byte `LEA ECX,[ECX]` alignment occupies `0x5F92D5..0x5F92D7`; the table
occupies `0x5F92D8..0x5F9307`. Entries207..210 go to the actual default path.
The frame reserves eight bytes and saves EBX/EBP/ESI/EDI.

There are135 physical calls:104 direct and31 virtual action-slot+08 calls.
Direct calls comprise five stage predicates, three deque subscripts, two front
calls, eight finalizers,51 window queries,26 packed-input initializations and
nine other gates. External tails go once to45DDA0, once to464200 and four times
to4633A0. The object has110 REL32 and fourteen DIR32 fields: one numeric
reference, one table base and twelve destinations. Existing float140.0 at
`0x006C4C60` is independently checked and consumed by FCOMP dword at `0x5F8B25`.
Used float captures preserve preceding native rounding. No shared header or
global relocation mapping changes.

[Sakuya's exact source](SAKUYA_INPUT_POLICY_2026_10_24.md) supplies a hypothesis.
Complete raw bytes, edges, arguments and widths independently check all changed
paths; an attested Ghidra view corroborates interpretation and is not pasted
as source. Both common air gate minima are independently confirmed as2.

| Surface | Komachi behavior retained from native instructions |
| --- | --- |
| Ground records |200..206 finalize600..606;211 finalizes611.207..210 follow the actual default path. |
| Air front call |The normal input trigger still calls45D1B0 with0 and ignores its return. There is no air deque read, window bound, front-record selector or finalizer. The call itself must remain for its effects. |
| Ground masks400/200 |+60D531/530, +609526/525, then521/520 through flag+755. |
| Ground masks4/2 |+60C511/510, +608506/505, then501/500 through flag+754. |
| Ground masks40/20 |+60B566/561 and565/560 through flag+757. |
| Ground high-bit masks |+60E551/550, +60A546/545, then541/540 through flag+756. |
| Air masks4/2 |+608>=1 selects508/507 through flag+754 without a regular fallback. |
| Air high-bit masks |Both+60A/+60E must be zero, then543/542 through flag+756. |
| First normal group |UP303 has its real state303 fallback; distance is float140.0. Retains321-to322 and both independent air308 attempts. |
| Group+6F8 |Ground forward401 precedes400 fallback. Air attempts UP406, then neutral/forward405, then404 fallback, preserving actual resource checks and skip edges. |
| Group+6FC |Retains separate412 attempts and the real415/416/414 air paths; no Iku417 branch or Marisa mode replacement is added. |

No +12C clear, +730 reset or extra sequence selection from another character
is added. Signed field widths, independent repeated calls and post-call field
reads remain explicit. The first complete source emits all6,232 exact bytes;
no source correction or code-generation control is needed.

## Validation and retained evidence

IDA preflight rejects the other executable still open there; no semantics or
writes from that session are used. One read-only Ghidra process independently
attests file/program identity, Windows x86 language/compiler, image base,
entry `0x68B9D2`, every raw-backed section and root hash. The root body min/max/
count is checked against the raw accepted extent. Temporary metadata is read
back and rolled back; pinned primary database hashes remain unchanged. Analysis
uses CPU0/nice10 with384 MiB heap; builds run serially on CPU0/nice10.

Private recipes and the first complete source snapshot remain under
`.analysis/exact-first-komachi-slot50-20261024/`. The corresponding `build/`
directory retains raw facts/disassembly, full CFG/table closure, attested views/
logs/DB hashes, formal/cold receipts, first object/provenance, relocation counts,
original origin row and input hashes. A generated-object table negative fails
at `+0x1828 / 0x5F92D8`, targetF7/sourceF8; the target stays untouched. Earlier
accepted input sources remain unchanged. No broad runtime matrix or aggregate
cold replay is claimed. Continue remaining complete peers; Marisa stays parked.
