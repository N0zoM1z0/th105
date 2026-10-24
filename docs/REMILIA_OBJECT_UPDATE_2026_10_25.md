# RemiliaObject complete update, 0x557690

## Observed target

The canonical Japanese1.06a executable SHA256 is
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
RemiliaObject's primary vtable6C533C cell6C5364 binds slot28 to557690.
Raw control flow closes the complete17793-byte callable, ending at55BC10,
with4238 reachable instructions,28 RET0 sites and no external direct JMP.
The sole unreachable instruction is the three-byte alignment LEA at55777D.
This does not establish an original standalone compiler/TU boundary.

The full18388-byte payload ends exclusively at55BE64, followed by12 INT3
bytes and the separate initializer55BE70. It contains12 destination tables
(98 DWORDs), the199-byte800..998 remap and four alignment bytes after main.
Main SHA256 is
`b53af50d6bfdf124d8c16098abfa56c043f8cd1bca9606cc8d73b892610d4fe2`;
complete payload SHA256 is
`793c1954983d385b07ead1e850f95b4c521448100500074eaa0b371e2f3b0cd6`.
[The target audit](../scripts/audit-remilia-object-update-target.py) checks these
bytes, every table destination, physical calls and closed reachability.

There are168 direct physical calls to16 entries and six virtual calls:
slot20 at5585F6/55A4BC/55A974 and slot0C at559625/559A59/55B82F.
Thirteen direct callees already have exact records. Sine406360/cosine4063D0
remain nonexact; FTOL68A1A0 is tracked as compiler/runtime code. The call
declarations add no callee implementation or matching credit.

## Complete first source and comparison

[The source](../src/characters/RemiliaObjectActionState.cpp) covers all27
nondefault actions and the real default animation call. Its
[receiver](../src/characters/RemiliaObjectActionState.hpp) is a declaration-only
primary call view: never construct or embed it. Working `void` return views,
double lookup returns and the low-WORD secondary key express observed physical
use; original nominal types, full owner layout and TU identity remain unknown.
No assembly, copied code arrays, inert locals, padding or fabricated returns
are used.

The first complete source was compiled before tuning and compared over the
whole18388-byte target payload with the unchanged canonical COFF relocation
algorithm. Six newly observed literal keys were supplied after independently
checking their IEEE bytes in both COFF and the attested PE. The durable unit
then reproduced the same normalized payload. Existing literal bindings were
not changed. These six new keys are not consumed by an accepted unit.

The selected first candidate is **nonexact**:

| Measurement | Target | First candidate |
| --- | --- | --- |
| Complete payload bytes | 18388 | 17804 |
| First mismatch | — | +22, branch displacement |
| Direct spawn calls | 29 | 28 |
| Relative-position calls | 19 | 18 |
| Other14 direct-callee counts | observed | equal |
| Virtual calls | 6 | 6 |
| Physical RETs | 28 | 24 |

Candidate normalized SHA256 is
`12b93e93a54fa810556ec7c9662ac19c57894e97c54a658522bc51b600a3239c`.
All18388 target bytes participate; no differences or relocations are masked.
The common eight-byte-aligned32-byte stack frame and entry prefix already
agree. Shared-tail placement, source branch shapes and compiler merging remain
open. Specifically,820's two relative-position sites merge into one and826's
two burst sites merge into one. This physical inventory is diagnostic and is
not an exactness or full behavioral-equivalence claim.

Retain unsigned RNG-to-float conversion, signed byte phase predicates, explicit
consumed float rounding, genuine double Y captures before terrain calls and
post-call field rereads. Retirement decrements can continue through animation
and additional state checks; they must not all become immediate returns.
The common816/857/900 fade tails and855/856 fade body have target cross-edges.

## Bounded native angle/guard evidence

[The prefix diagnostic](../scripts/audit-remilia-object-update-paths.py) executes
real atan2, FTOL and sine/cosine instructions to the first spawn/advance entry.
Ten cases compare owner bytes, actual helper-entry trace, spawn arguments,
four-float payload and x87 top/control. Six test816/857/900 with179/-540 input
angles; four distinguish857 H3 below/equal/above45 and quiet NaN. All ten pass.
The mapped PE's lookup tables have their zero-initialized fixture contents;
this does not validate populated production trigonometric data, spawn execution,
later updates or complete runtime equivalence. No helper instruction, result,
return or control-flow transfer is injected.

A negative source control changes only `H[3] <= 45.0f` to
`!(H[3] > 45.0f)`. It fails the NaN case by taking the atan2/spawn path where
the original advances without spawning. Its normalized SHA256 is
`35395fee7b06aa95e6008d38fe0d249d3334865a93ca5533ddd0cd1c52e8272e`.
The target's557690-body instruction at55A1C4 tests the unordered status bit;
the ordered comparison is required. This diagnostic resolves that concrete
ambiguity and is not a large gameplay matrix.

## Reproduction and continuation

Run serially, CPU0/nice10, through the locked repository Python:

```sh
scripts/repo-python scripts/audit-remilia-object-update-target.py
scripts/repo-python scripts/build.py --unit exact-first-remilia-object-update --compare --json
scripts/repo-python scripts/audit-remilia-object-update.py
scripts/repo-python scripts/audit-remilia-object-update-paths.py
```

The build/comparison and full payload audit currently return1 for the recorded
mismatch; the target and ten-prefix audits return0. Receipts are under
`build/exact-first-remilia-object-update-20261025/`: `first-preview.json`,
`first-inventory.json`, `formal-first.json`, `formal-first-payload.json`,
`formal-first-paths.json`, `guard-control-paths.json` and the Ghidra receipt.
Private source controls and recipes are in the corresponding `.analysis/`
directory. Readonly Ghidra was target-attested, temporary views rolled back
and all nine primary database pins unchanged; its decompilation remains a
hypothesis. IDA's open GUI still has the wrong target and was not used.

Next test one source-tail-placement hypothesis against the whole function:
the physical common movement/advance/retirement blocks follow800, while the
first source puts their labels after the final switch case. Then inspect the
820/826 call-site merging with their target predecessor graph. Preserve a
receipt and switch hypotheses after repeated identical output. No original
TU/LTCG impossibility is established. Source-present increases by one;
exact remains1403 functions/359740 authored code bytes.
