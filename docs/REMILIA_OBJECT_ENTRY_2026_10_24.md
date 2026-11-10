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

## November1: request-local lifetimes recover the real 980 tail

The two actual parented requests belong only to800/sequence0 and854/sequence2.
The previous source unnecessarily kept one payload array alive for the entire
initializer. Each request now owns an ordinary three-float array in its actual
branch, with the existing three writes and pointer/count arguments unchanged.
No unused local, padding, forced inline boundary or ABI change is introduced.

The lifetime is supported by the complete synchronous consumer chain. Exact
4FCA60/77 obtains owner348, manager658 and calls manager vslot4, forwarding
pointer and count with RET28. Remilia manager constructor555DF0 installs vptr
6C5394, whose slot4 is555E80/237. In that complete manager the count controls
new unsigned[count], and555F08..555F12 copies count*4 bytes to the newly owned
object340 buffer. The original request pointer is not retained. The source
lifetime therefore need not extend through unrelated later action branches.
Fresh roster-manager comparisons from the immediately preceding scope include
Remilia237; the current effect-provider replay freshly matches4FCA60/77.
That mixed effect unit also reports its pre-existing5F9350 nonexact peer; it is
not reported as an aggregate pass. Shared980 provider596370/323 freshly passes.

Native spawn sites55BF9D and55C938 and their complete75/83-byte argument windows
are byte-identical in the newly compiled candidate. Both requests still use
three words and retain their original initialization and conversion order.
The compiler now emits the actual980 tail JMP at55D1DE naturally, replacing
the former CALL/RET. The native32RET count,1339 decoded/reachable instructions,
4997-byte callable and three-byte post-RET LEA are all recovered. A complete
entry/table traversal reaches all1339 instructions on each side, closes all
three switch tables, and permits only the independently exact596370 tail.
The199-byte selector remap and its zero alignment byte are unchanged/equal.

The whole5384-byte canonical result remains **nonexact** at+440/55C028.
Selected SHA256:
38fd7441435512a41e9d0ea886fa4bbc39fa2869b150cbc195753fe10b1cdd36.
There are426 callable and11 table-byte differences,437 over the full payload.
The target full-payload SHA256 is
6d40a4fe209f5cb0306cb213898728fb5d1e9b0421868fbad511d777d363cfc9.
The remaining locations are850/851 and902/903 virtual-call/heading-register
scheduling plus901's shared heading-store/return placement. Local equality and
recovered physical extents are diagnostics, not partial exact-byte credit.
No further old sequence-view or switch-placement spelling controls were run.

The public build reproduces the isolated lifetime control exactly. Only this source,
its tracking evidence and documentation change; shared headers/providers stay
intact.

## November1 follow-up:901's distinct source arms and full metadata

Native901's sequence table places2/9 at55CE02 but8 at55C3A8, a different
shared heading-store tail. The prior source grouped2/9 before3 and separately
spelled8. Keeping the three real heading assignments in their own ascending
sequence arms, rather than pre-grouping2/9, lets VC8 perform the observed tail
merging itself. This adds no operation, goto, scratch, branch condition or fake
liveness: only the existing case9 assignment is independently spelled after8.
The old07 experiment coupled grouping with a float snapshot; this control does
not repeat that snapshot or change any float epoch/type.

The complete selected5384-byte payload is now
b35e53a2e1d34d1622a7adbb3f2b120bde3f69acc35702f6a9b7059bcee27dea.
All387 suffix bytes (alignment plus three tables/map) match, and only10 callable
bytes differ, first+2036/55C664. They are confined to850/851's two virtual-call
preparations at55C664..55C66A and55C68E..55C694. All902/903 pointer registers
and901's physical tail/table destinations now agree without targeted register
edits. Whole1339-instruction reachability,32RET, actual55D1DE tail and4997-byte
callable remain closed. This is still **nonexact**, with no partial credit.

Finite controls, not selected:
- Grouping2/8/9 together produces83a141f6/full5384, nonexact+1318, and changes
  the earlier shared tail. The distinct native8 target rules out treating all
  three physical destinations as one recovered owner.
- The established normal int-return/int-argument selector view across the root
  givesa86f51a7/full5384, nonexact+169. It does not establish the original nominal
  declaration or improve the original source choice.
- On the selected separate901 source, direct short conversion at all23 source
  float-selector expressions and an int return with the existing short argument
  are each completely byte-neutral: fullb35e53a2/10 differences. Native primary
  vtable6C533C slot0C really selects45C390; its ordinary int facade and actual
  WORD consumption are independently known. No per-case ABI selection is made.

The public build reproduces the selected isolated source. Receipts in the same
scope: selected901.json,selected901-full.json,selected901-cfg.json and source
control COFF/canonical reports. Complete-CFG recipe is retained privately as
complete_cfg.py. Stop this selector/grouping lane absent new ownership or
compiler evidence; do not force the remaining two register/stack schedules.
