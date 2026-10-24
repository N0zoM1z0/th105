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

The first candidate, retained at commit `d15e178`, is **nonexact**:

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

### Branch/argument checkpoint, b1c32b5

The following complete-source controls were serial builds and whole-payload
comparisons; no compiler flags, shared header or accepted binding changed.

| Control | Bytes | RETs | Result |
| --- | ---: | ---: | --- |
| First source | 17804 | 24 | baseline |
| Move common800 movement/advance/retirement labels before801 | 17664 | 22 | more merging; unselected |
| Replace global retirement jumps with real local decrement/return | 17864 | 33 | extra exits; unselected |
|820 switch plus target-local sequence1 fade exit | 17844 | 25 | restores both position sites; retained |
|826 direct unsigned-to-double argument expression | 17812 | 25 | removes spill but widens2^32 correction load; unselected |
|826 direct unsigned-to-float argument expression | 17812 | 25 | target DWORD correction/load epoch; retained |
| Move shared855 fade label before856 | 17812 | 25 | byte-neutral to preceding source |
|855/856 separate0/1 fade guards with real shared body | 17832 | 26 | retains distinct target-local RET; selected |
|852 explicit switch/independent guards | 17836 | 26 | merges the fade body with855; unselected |

At b1c32b5, the source naturally recovers820's signed-WORD dispatcher and its
separate local sequence1 fade RET. All19 position calls now agree. The two826
spawn arguments use the observed direct unsigned-to-float conversion instead
of a force-inlined float-return helper. This removes an extra consumed float
spill, pushes Y before RNG and retains the target's DWORD2^32 correction.
The double control instead loads the equal-valued QWORD at6D6ED0; equal numeric
results do not justify keeping the wrong observed load width. The two826 spawn
suffixes still merge into one site; no source/TU impossibility is established.
855/856 keep the observed separate sequence0/1 alpha guards and genuine shared
fade body. Label placement alone was neutral and is not a reusable recipe.

At b1c32b5, formal and independent object-deleting cold builds agree on the
**17832-byte** normalized payload, SHA256
`6866e295fb8ab78fb38a890755f4bffba73d499100f1bc7cec9818cbed9bf679`.
It remains nonexact at+22,556 bytes shorter than target. All15 other direct
callee counts and all six virtual calls agree; spawn remains28/29 and RETs26/28.
All12 destination-table lengths agree and the199 remap bytes are independently
equal. This does not assert equality of the relocated destination entries.
Selected raw CRLF source SHA256:
`4662b783091f104f0f88dc4f35c9218c07517c32697926b9ffce23f3e37676ef`;
unchanged header SHA256:
`485d18d864b74c9b1977405cd4ff382313f17bc5a96386f34ef2d128d7edd30b`.

The native diagnostic now also checks12 fade inputs:852/855/856, sequences0/1,
alpha9/10, with nonzero370/374 values. Six reach real RET0; six stop at the
first animation call after publishing the real fade results. All22 angle/guard/
fade inputs pass for formal and cold candidates. The unordered857 negative
control still fails exactly its NaN input. This remains a bounded diagnostic,
with the lookup-fixture limitations above.

Receipts include `controls.json`, each control's preview/inventory, plus
`formal-selected.json`, `formal-selected-payload.json`, `formal-selected-paths.json`,
`cold-selected.json`, `cold-selected-payload.json`, `cold-selected-paths.json` and
`guard-control-paths-22.json`. The controls retain complete source in `.analysis/`.
Do not repeat these label/retirement/dispatcher controls without new evidence.

### Natural branch bodies and compiler-owned joins

The next target-pinned opcode inventory isolated a concrete premature join:
801's bounds check had been folded into821's common tail in the source object,
while the target retained both physical copies. Its other differences were
mostly GP register choices. No extra gameplay branch was inferred from that
folding. The earlier post-spawn801 local-return spelling control is also
byte-neutral; retain `exit801-preview.json` and do not repeat it.

The follow-up restores independent source operations and allows VC8 to form
its own shared machine tails. Every trial below compares the complete payload;
flags, header, literal ledger and accepted units are unchanged.

| Incremental control | Bytes | RETs | Observation |
| --- | ---: | ---: | --- |
| Five independent movement bodies | 18048 | 25 |801's171-instruction block, including GP registers, agrees after branch-destination-only diagnostic normalization |
| Move early common frame/retirement labels after that change | 18132 | 25 | extra movement body in801; unselected |
| Independent816/857/900 fade bodies | 18056 | 25 | naturally restores EBP=4 and all three EBP argument pushes in816 |
| Inline each fade-counter exit | 18052 | 25 | moves the retained fade bodies out of816; unselected |
| Independent animation-call exits | 18108 | 24 | restores800's actual movement/frame-call block and its location |
| Independent real retirement exits | 18212 | 31 |800/801/810 instruction sequences agree; no explicit global retire join |
| Separate852/855/8560/1 branches and natural opposite-polarity guards | 18360 | 32 | restores all three complete physical fade blocks; selected |

The second/third branches in this table build on the five independent movement
bodies; the inline-fade control is not the parent of the animation-exit trial.
This is a changed CFG experiment, not a repetition of the first-source global
label control. The earlier globally shared move/frame/retire nodes constrained
register lifetimes before machine tail merging. Source-independent bodies
recover801 and promote the real constant4 without a forced register, inert
local, padding, assembly or made-up call. This is a bounded source hypothesis;
no general matching recipe is accepted until a whole unit reaches exactness.

The **current selected** full payload is18360 bytes, SHA256
`89e5bd2eb0955bb9f55cac1c2f423f9b93b9663417f0295145485cf8137536c5`.
Formal and independent object-deleting cold builds reproduce it. Source raw
CRLF SHA256 is
`b644e2ffbe1eb7ef89d7aab414e5c64354a0e65889c404ca8ffb247358de965d`;
the header remains unchanged. The complete comparison is **nonexact at+22**,
with15330 unequal byte positions over the full18388-byte target range. The
28-byte payload size gap is a separate measurement. All12 table lengths and
199 remap bytes agree; spawn remains28/29 and physical RETs32/28. Several
complete case instruction sequences now agree when only branch destinations
are normalized for diagnosis. Acceptance still uses every unmasked byte and
strict relocation replay, including all destination entries.

The native diagnostic has54 inputs: the preceding22,24 effect-fade inputs
(816/857/900, sequences3/4, timer3/4, alpha29/30 and live phase7), and eight
movement inputs across all five independently expanded paths. The movement
cases include801 at X=1379.5/1380.5/quiet NaN with a real +1.75 movement.
All54 pass in formal and cold objects;13 reach real RET0 and the rest stop at
first spawn/animation entries. A negative source control moves only801's bounds
check after movement and fails exactly the two finite boundary-order fixtures.
The production-lookup and whole-runtime-equivalence limits above still apply.

Receipts: `natural-controls.json`, each control's preview/inventory and opcode
packet, `natural-formal.json`, `natural-formal-payload.json`,
`natural-formal-paths.json`, `natural-cold.json`, `natural-cold-payload.json`,
`natural-cold-paths.json`, and `movement-order-control-paths.json`, all in the
same build scope. Private controls and the diagnostic case differ live in the
corresponding `.analysis/` directory. The differ ignores jump destinations
only to locate source-shape problems and never records a match score or waiver.

### Closed local lifetime controls after the natural-body checkpoint

The source remains the18360-byte `89e5bd2e...` candidate above. Three further
whole-function controls are unselected:

| Control | Bytes | Canonical SHA256 | Finding |
| --- | ---: | --- | --- |
|811 independent positive post-frame conditions | 18364 | `8684b06a03b1e6665c4a5188261c140c6854c9a9ae07874333c97e73bca27e2d` | restores repeated142 guards but caches144 and holds minus-one in ECX |
|811 real branch-defined decrement scalar, consumed by all three updates | 18364 | `1c8f2bd4ff015c91671075f7a60b7a5f470a50e89564801ba5ec389d0e1a97a2` | same811 instruction stream as the preceding control; four815 addition-operand bytes change |
| One function-scope four-float packet replacing20 source array declarations | 18360 | `89e5bd2eb0955bb9f55cac1c2f423f9b93b9663417f0295145485cf8137536c5` | complete byte equality to selected source;28 spawn sites remain |

The target811 sequence holds minus-one in EAX after the AL result test and
retains both memory144 tests. The first control instead saves144 in EAX and
keeps minus-one in ECX; the scalar control does not recover the target lifetime.
Only811 is instruction-neutral between those two controls; their complete
payloads differ at four815 bytes. Do not describe that pair as whole-byte
neutral or select the scalar just to change a neighboring floating addition.
The frame helper4351C0 delegates its nonzero exit through a virtual callback;
its current physical AL-byte view is retained, without a new bool-domain claim.

The shared packet control consumes all four elements in actual four-word spawn
paths and preserves the separate live854 ground packet. It introduces no inert
storage. Nevertheless, its canonical output is exactly unchanged, closing this
packet-storage-duration hypothesis for826's missing physical spawn copy.
No ABI, header, flags, relocation ledger, source selection or exact count changes
are made for these controls. Receipts are `positive811-preview.json`,
`positive811-opcode-diff.txt`, `delta811-preview.json`, `delta811-opcode-diff.txt`,
`815-natural-opcode-diff.txt`, `815-delta811-opcode-diff.txt`,
`shared-packet-preview.json` and `shared-packet-inventory.json` in the same scope.
The raw811/826 facts and selected complete comparison remain authoritative.

Run serially, CPU0/nice10, through the locked repository Python:

```sh
scripts/repo-python scripts/audit-remilia-object-update-target.py
scripts/repo-python scripts/build.py --unit exact-first-remilia-object-update --compare --json
scripts/repo-python scripts/audit-remilia-object-update.py
scripts/repo-python scripts/audit-remilia-object-update-paths.py
```

The build/comparison and full payload audit currently return1 for the recorded
mismatch; the target and54-prefix audits return0. Receipts are under
`build/exact-first-remilia-object-update-20261025/`: `first-preview.json`,
`first-inventory.json`, `formal-first.json`, `formal-first-payload.json`,
`formal-first-paths.json`, `guard-control-paths.json` and the Ghidra receipt.
Private source controls and recipes are in the corresponding `.analysis/`
directory. Readonly Ghidra was target-attested, temporary views rolled back
and all nine primary database pins unchanged; its decompilation remains a
hypothesis. IDA's open GUI still has the wrong target and was not used.

Next inspect826's actual receiver/argument preparation around its shared spawn
suffix. Packet storage duration and811 decrement spellings now have retained
negative results; reopen them only with independent evidence. The earlier
global label, local-return and852 controls remain recorded in their original
source context. No original TU/LTCG impossibility is established. Source-present
remains1543 and exact remains1403 functions/359740 authored code bytes.
