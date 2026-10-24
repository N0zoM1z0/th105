# RemiliaObject complete initializer: exact-first checkpoint

## Result and reproducible scope

`0x0055BE70` now has one complete natural source body in
`src/characters/RemiliaObjectActionEntry.cpp` and a pointer-only declaration
view in the adjacent header. The selected unit is
`exact-first-remilia-object-entry`. It is **nonexact**, not a new match:

```sh
taskset -c 0 nice -n 10 python3 scripts/build.py \
  --unit exact-first-remilia-object-entry --compare --json
```

The focused build succeeds and the strict comparison returns 1, first differing
at `+0x80 / 0x0055BEF0`: target `F9`, source `FA`, in the out-of-range JA
operand. It compares all 4,997 callable bytes. The complete emitted section
is 5,384 bytes, equal in length to the complete target payload, but not in
bytes. No `matches.csv` row, matching state, original source spelling, complete
owner layout, or LTCG impossibility is claimed.

## Observed target facts

All observations use only the original Japanese 1.06a image, SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
The existing candidate is independently classified authored by the frozen RTTI
primary-vtable anchor: RemiliaObject slot `+0x3C`, pointer cell `0x006C5378`.
That ownership evidence is unchanged.

Raw decoding covers 1,339 instructions from `0x0055BE70` through RET at
`0x0055D1F4`, exclusive end `0x0055D1F5`. Callable SHA256 is
`e16fb4cf071d8c2668bba00831808d4ff7dba869bd4708430e80535606cb1eac`.
The next three bytes are alignment `8D 49 00`, not callable credit.

| Physical region | Extent / size |
| --- | --- |
| Main destination table | `0x55D1F8..0x55D263`, 27 DWORDs / 108 bytes |
| Selector remap | `0x55D264..0x55D32A`, 199 bytes, selectors 800..998 |
| Table alignment | `0x55D32B`, one zero byte |
| State 826 sequence table | `0x55D32C..0x55D34B`, 8 DWORDs / 32 bytes |
| State 901 sequence table | `0x55D34C..0x55D377`, 11 DWORDs / 44 bytes |

All table destinations enter decoded instructions in the callable. The 26
explicit remap indices include shared 811/820 and terminal 998; the remaining
172 selector values use default index 26. Index 25 (998) and default index 26
both point at the same `0x55D1E3` cleanup. Retaining an explicit empty 998 case
is a source hypothesis supported by this distinct remap index, not a fake
behavior or a claim about original switch spelling.

There are 32 physical RETs and one external branch, the 980 tail to `0x596370`.
Direct calls comprise 21 ordinary float-to-integer conversions at `0x68A1A0`,
42 RNG calls at `0x4067D0`, seven oriented-component calls at `0x435160`, two
parented spawns at `0x4FCA60`, one secondary replacement at `0x496420`, and
one auxiliary replacement at `0x45CD70`. All 21 indirect calls use primary
vtable slot `+0x0C`, with the converted word in an ordinary four-byte argument
slot. The short selector contract is independently established by the existing
sequence-selector unit. Source casts express the conversions; no ordinary
prototype is fabricated for the implicit x87 runtime entry.

The 16-byte local frame includes a used three-float spawn payload. Both spawns
pass all seven ordinary stack slots and return with 28-byte cleanup. The motion
receiver is exactly `this+4`; the two replacement receivers are `this`.
The selected code retains unsigned RNG-to-float conversions, the integer
addition before the unsigned conversion in the range-plus-50 paths, actual
signed-byte facing reads, ordered auxiliary writes, independent sequence tests
and the two nested switch surfaces. Gameplay meanings remain provisional.

Two new readonly literal bindings are observed directly in this root:
`__real@3e19999a` at `0x6C5498`, four bytes `9A 99 19 3E` (0.15f), and
`__real@42aa0000` at `0x6C4004`, four bytes `00 00 AA 42` (85.0f).
These previously unresolvable symbols have no prior accepted consumer; existing
relocation rows and accepted source/header inputs are unchanged.

## Analysis database attestation

The required IDA preflight again rejects the other open executable hash; that
session was not used. The existing private IkuTarget Ghidra database was opened
read-only, analysis disabled, in a single CPU0/nice10 process with a 384 MiB
configured heap. Its imported executable SHA256, x86 Windows language/compiler,
image base, external entry point `0x68B9D2`, and every raw-backed section were
independently checked against the canonical PE before decompilation.

No function object existed at this address. A temporary 4,997-byte body was
created and read back, then removed and read back within a rolled-back
transaction. All pinned primary database files have identical before/after
hashes. The exported pseudocode is a hypothesis: in particular it expands the
980 tail into the separate callee and loses float types/rounding. The retained
source was written from the instruction/control-flow review, not copied from
that output.

Receipts: `build/exact-first-remilia-entry-20261024/ghidra-receipt.json`,
`primary-db-before.json`, `primary-db-after.json`, `ghidra.log`, `target.asm`,
`raw-facts.json`, and `constants.json`. Private analysis/recipes stay under
`.analysis/exact-first-remilia-entry-20261024/`.

## Whole-function experiment receipts

The 00..09 source trials were serial, pinned to CPU0 at nice10, with the existing
VC8 SP1 `/O2` profile. No accepted unit or shared header was edited. A later
optional full-origin check was cancelled after it was found to launch library
compiler witnesses; it is not a passed validation. The selected canonical unit
was then cold-built again serially before the final local CI gate.

| Revision | Complete section bytes | Observation |
| --- | ---: | --- |
| 00 | 5220 | Complete first draft; missing explicit terminal selector and excessive conversion-tail sharing; 19 physical conversions/calls instead of 21. |
| 01 | 5240 | Empty 998 return retains native selector limit; no new behavior. |
| 02 | 5240 | Chained scale assignment reversed to preserve native +11C then +120 store order. |
| 03 | 5336 | Natural per-case selector expressions restore all 21 physical conversion/virtual calls; remove the shared source goto. |
| 04 | 5384 | Explicit used float casts retain the native product-rounding steps before later additions. Metadata now begins at offset 5000. |
| 05/06 | 5364 | Moving empty terminal/default exits folds away selector 998; rejected. These two contexts are byte-identical and will not be repeated unchanged. |
| 07 | 5372 | Alternate 901 case grouping plus a float angle snapshot changes block scheduling and adds a rounding spill; unselected. |
| 08 | 5384 | Real named prefix fields instead of offset lvalues are completely byte-identical to 04; the additional layout view is unselected. |
| 09, selected | 5384 | A used double holds 851's exact input float across its byte write, preserving the observed heading-read epoch without an extra float spill. |

The selected canonical complete-payload SHA256 is
`d114fd28eaefcbc4fb8f1c8ebe1ceb7512661cdabb05624179ec85bab5be2aac`.
The full section contains 235 physical relocations. Private `diagnose.py`
reuses the public comparator's complete COFF relocation/literal validation and
normalizes the whole section; it does not mask registers or accept a match.
Reports and immutable source snapshots are retained alongside every revision.
The configured fresh build receipt is `selected-build-compare.json`.

## Remaining differences and next decision

Selected source still differs in selector-call register scheduling for 850/851,
902/903 heading/vptr registers, physical placement of 901's shared heading
store/return, and the 980 CALL+RET versus native tail JMP. The last discrepancy
also makes the callable one byte too long, consuming two alignment bytes
before the same metadata offset; a same-sized section is not an exact callable.

The control-flow diagnostic only aligns instructions to locate these regions.
It is not semantic equivalence proof and earns no partial exact credit. No
large runtime matrix was run: this checkpoint retains raw target observations,
a complete source hypothesis and ordinary canonical comparison separately.

Preserve this selected body and all negative controls. Do not repeat the
neutral named-field or terminal/default controls without new independent
instruction/compiler evidence. Switch to another bounded roster initializer
when the next hypothesis would merely repeat these scheduler experiments.
