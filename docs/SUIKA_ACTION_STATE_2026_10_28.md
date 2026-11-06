# Suika action-state 0x00598990

Complete-label, unselected, nonexact C++ candidate: 115 top-level action labels,
shared prelude and default path. Compilation and coverage do not establish
semantic correctness. No implemented.csv, matches.csv or exact-byte credit.

## Native evidence

The Japanese 1.06a target is hash-attested. Factory IDA metadata, entry,
inventory and mapped-byte samples independently matched the target. The direct
local MCP preflight lacked its Python dependency, and whole-root native
decompilation failed; neither was repeatedly retried or repaired by installing
software. Independently attested Ghidra action slices were navigation aids only.
Their temporary functions and caller-interface views are not original ABIs.
Transactions rolled back, with all nine primary database hashes unchanged.
Raw instructions decide selector arguments, floating widths and packet stores.

Callable 598990..5ABFDB exclusive is 79435 bytes, SHA-256
a1006a208fb62813cec2081c250f5825e88011ce834cff9e49e5d15d0164feb9.
There are 20324 decoded instructions and 20321 reachable instructions.
The nine unreachable bytes are three LEA ECX,[ECX] alignment instructions at
5A09FD, 5A5A5D and 5A97CD, not missing actions. All twenty indirect switches
resolve. Decoded direct calls: 1081 sites, 37 targets. A raw E8 byte scan counts
1083 sites, including non-instruction matches; it is not the decoded census.
Full metadata ends at 5AC680: 81136 bytes, SHA-256
11eb3a1f3f5eef32dee111878375b1b0270c7a38b1be49161220adb548a49e45.
Native aligned frame is 0x578. Sparse regions have 33/50/31 destinations,
with direct actions 300 and 560 outside those tables.

## Source observations and unresolved work

The pointer-only receiver inherits the established animation virtual-slot view.
Declaration-only helpers confer no callee implementation credit.
Slot0C selects a sequence; slot08 changes an action; slot20 advances a frame.
Direction arithmetic uses signed byte values, while spawn carriers preserve
unsigned low bytes, including layer255. Shared helper435160 receives root+4.

The source retains callback-sensitive surface/selector ordering, narrowed
velocity followed by QWORD predicted-Y captures for547/562/708, unsigned
button-edge predicates, and duplicate native gravity passes in740. Spell605
runs the secondary cycle before its sequence window, unlike the usual cast
helper. Grab608 preserves peer action changes, live receiver reloads and
caller-owned packet reuse through repeated requests. Negative spawn offsets
use integer subtraction as the native FISUB operands require.
540 and541 have distinct random-result narrowing/integer arithmetic.
505..508 initialize fragment type once before their loops;402 initializes it
per iteration. No defensive behavior, invented packet initialization or
cleanup of seemingly redundant native behavior is intended.

Remaining uncertainties include:
- Candidate low table merges208/220, though native physical entries differ.
- Giant605/730 surface-check bodies still merge at compilation despite explicit
  individual sequence cases. Each has five fewer static surface/zero-motion
  call sites and five fewer addition sites; this is not exact ownership.
- 608 has four more virtual sites. Grab608 also has five fewer
  additions and two more subtractions in the current per-action diagnostic.
  These differences need source/lifetime review, not padding or forced code.
- 740 has no established initialized turn/period fallback outside difficulty
  0..3. The draft does not invent a default. This remains an explicit semantic
  limitation, not a supported new behavior or accepted reconstruction.
- Packet extents, callback lifetimes, floating evaluation and TU/LTCG ownership
  remain under review. No complete payload-home equivalence is claimed.

Per-action call/arithmetic counts are omission diagnostics, not proof of
semantics. Integer x87 arithmetic and reversed/pop forms must be considered
when interpreting operation counts. No compiler-control assembly, copied
target bytes, fake ABI, inert locals or padding is used.

## Reproduction

    taskset -c 0 nice -n 10 scripts/repo-python scripts/build.py --unit exact-first-suika-action-state --compare --json
    scripts/repo-python scripts/audit-suika-action-state.py
    scripts/repo-python scripts/compare-giant-action-switches.py suika-vslot28 build/match-units/ExactFirst_SuikaActionState.obj --json

Current complete candidate: 78976 bytes versus native81136, frame0x578 matches
the native frame. First mismatch is +17 / 5989A1. Full unmasked comparison:
77122 differing bytes including length difference. This positional comparison
is not a semantic-completion percentage. Candidate SHA-256:
b2468219f5e5b824f0355c83bf4d4639e30e436b549e081dd0a890507c1944b6.
Sparse candidate cardinalities32/50/31; no target group is split. Twenty absent
native-backed literal bindings were added without changing existing bindings
or shared headers. Only this unit was compiled; accepted receipts elsewhere
remain unchanged.

Receipts: build/frontier-598990-20261028/formal-build.json, formal-full.json,
trial-giant-owners-map.json and trial-giant-owners-action-review.json.
Private raw boundaries, all115 diagnostic slices and IDA/Ghidra attestation
receipts remain in that bounded build directory. Continue source-level
ownership/lifetime refinement against this complete baseline.


## Separate action501 return owners

Native501 has distinct entry3 and entry4 action-reset calls. Keeping these as
separate source guards restores both virtual sites rather than combining them
with a logical OR. The candidate remains78976 bytes, first+17, with77122 full
unmasked differing bytes and frame578. Its new SHA-256 is
c950a4e409eb06b07a9463fca62141fe5e9d6442a05e7f5a4442ef3e8e91f741.
Receipts: trial501.full.json, trial501-map.json, trial501-action-review.json.
The prior baseline SHA above remains historical. Explicit inlining of the
giant surface-check helper was byte-identical and was not retained.


## Grab608 shared call tails

The sequence3/6 frame0/1 branches now prepare X and a narrowed Y before their
native common peer-action107 call. Sequence8 frames0/1/4/5 similarly select
peer action109/103 and converge on one Y-store/action tail; frame2 keeps its
independent impact path. This follows the native control-flow/data lifetimes,
rather than duplicating a callback in each pose helper. All608 direct and
virtual call-site counts now agree with the target. Remaining arithmetic
counts are target/candidate141/130 additions,13/15 subtractions,37/36
multiplications; these include integer and reversed/pop x87 forms. They remain
unresolved ownership/precision evidence, not grounds for exact acceptance.

Current full candidate78912/native81136; first+17,77137 unmasked differing
bytes. SHA-256:
d233df12e5ebf011944056b91df85c708c3fbb7b3a18d102d611046a37db7baa.
Receipts: formal608-build.json, formal608-full.json, trial608-y-map.json and
trial608-y-action-review.json under the same bounded build directory.


## Action ordering and packet-home evidence

A bounded stack trace, qualified for the root receiver and established
related_170 animation peer, resolves all112 native and candidate caller-owned
packet homes with no unknown spawn sites. Both frame578 offset sets are
identical. Initially thirteen actions nevertheless used different individual
homes: late-added562/605/608/730/740/751 source arms were out of native order.
Restoring their observed action/body order aligns the per-action home sets
without padding, dummy arrays, ABI edits or new storage. Include placement now
puts605 before606 and608 before650;730 is with the boss states and all relevant
high/special arms follow native order. Counts/widths and callbacks are unchanged.

After this refinement all per-action home sets agree. Action740's two middle
static spawn sites are emitted in reversed physical order (homes356 and1076);
this is still an open layout issue, not an absent/extra packet. Native/candidate
epilogue and indirect-call totals remain different. All crossed/on-surface
result consumers test AL. The receiver/stack diagnostic is not exact acceptance
and does not validate packet contents, callee readers or every semantic alias.

Full candidate78988/native81136; first+17,77319 unmasked differing bytes.
Candidate SHA-256:
9ae51885bae170b746946e50c7b74ce295133f28ed0f7ea3ecc43440b5e6c965.
Current605 additionally has one fewer virtual site; its surface/zero-motion
merges and608 arithmetic differences remain. Receipts: formal-order-build.json,
formal-order-full.json, trial-owner-order2-map.json, payload-order-review.log,
native-action-payload-review.json, candidate-action-payload-review.json and
payload-order-differences.json in the bounded build directory. Previous packet
diagnostics are retained under payload-before-owner-order/.


## Tracking740 phase order

The target at5AA6E3 falls through for counter<=600 and branches to the late
phase otherwise. Expressing that same early/late order restores740's physical
packet order. All115 incoming action partitions now agree on their ordered
packet-home lists, including all112 distinct homes and shared-tail unions.
This is stack-ownership evidence only. Full78988/native81136 remains nonexact,
first+17,77340 differing bytes, SHA-256
bd6498bffe09d36b25990faaf71802fb172a15de750f352ee42cc25d85ac2b7b.
Receipts: formal740-build.json, formal740-full.json, payload740-review.log,
payload740-differences.json (empty), and trial740-branch-action-review.json.

## Grab 608 vertical pose product order, 2026-11-05

At `0x5A6A83..0x5A6AA6` and `0x5A6F78..0x5A6F9B`, the native vertical-pose X calculation multiplies horizontal velocity by -30 before multiplying by signed facing and adding X. The source previously multiplied facing by velocity first. The source now follows the observed product grouping; focused VC8 compilation similarly multiplies velocity by 30 before facing, although it expresses the negative result as subtraction rather than the native negative multiply/add. No ordinary-input gameplay difference is asserted from the regrouping. The 79435-byte root remains non-exact (candidate section tail 78988, first mismatch +17); no exact credit is claimed.

## Action 740 cosine branch, 2026-11-05

Native `0x5AA7A3..0x5AA7E3` compares zero against the cosine result and takes the acceleration-increase branch for positive or unordered values; equality and ordered negative values take the decrease branch. The previous strict `> 0.0` also chose the decrease branch for unordered values. The source now expresses the target's unordered-inclusive condition; fresh VC8 output at `0x115B9..0x115DD` uses the reversed comparison with equivalent status/parity branching. This only establishes the branch behavior if the helper returns an unordered value, not that ordinary gameplay reaches such a result or that floating exceptions are equivalent. The 79435-byte root remains non-exact (candidate section tail 78988, first mismatch +17); no exact credit is claimed.

## Action 214 flight effect facing, 2026-11-05

Native `0x59A30A..0x59A37A` captures the unsigned effect-facing byte before the sine lookup, computes and rounds Y, then calls cosine and separately reloads signed facing for the X offset. The earlier candidate reused a signed facing captured before both lookups. Ordinary locals now preserve the two native read points; focused VC8 output captures the effect byte at `0x18F8` and reloads signed facing at `0x192F`, after cosine. This establishes read order, not that the actual lookup changes facing or that ordinary gameplay differs. The 79435-byte root remains non-exact (candidate section tail 78948, first mismatch +17); no exact credit is claimed.

### Grab 608 zero-height Y association (2026-11-05)

For zero-height poses, native `0x5A63C6..0x5A63E0` and `0x5A6C5F..0x5A6C79` load vertical velocity and directly add the actor's Y. The earlier shared source evaluated `(Y + 0.0) + velocity`, and its emitted code included the extra qword-zero add. The source now uses `velocity + Y` for the real zero-height pose and retains `(Y + height) + velocity` for nonzero heights. Both 70-offset and 83-offset candidate expansions now emit the direct target operand order.

This is an observable bounded floating-point distinction: with both Y and velocity equal to negative zero under round-to-nearest, the target direct sum is `0x80000000`, whereas the former extra positive-zero add yields `0x00000000`; the revised expression yields `0x80000000`. This example establishes the arithmetic distinction, not that the state occurs in ordinary play or whole-root exception equivalence.

The dispatcher remains nonexact: target callable 79,435 bytes, candidate section tail 78,932 bytes, first difference +17. No exact credit is added.

## Impact fragment layer argument, 2026-11-05

The second object-811 request in `impact_fragments811` passes a full DWORD
layer of `-1` in the native action 520/521/522/523 paths. The observed
`or edi, -1; push edi` preparations are at 59FAA0, 59FE77, 5A01B9 and
5A04F3. The source had passed integer 255 through its int layer argument;
it now passes `-1`, preserving the target's actual 32-bit call value. This
is one source correction expanded into four native action paths. It does not
establish the original nominal parameter type. The Suika manager consumes
only the low byte, so ordinary gameplay divergence is not claimed.

The focused VC8 build emits `push -1` in all four corresponding expansions.
The complete 79435-byte callable remains nonexact from +17; the candidate
section tail is 78980 bytes. No exact credit follows. The build receipt is
`build/frontier-55d850-20261027/suika-impact-layer-20261105.json`.

## Additional direct spawn layers, 2026-11-05

Twelve additional source requests also used integer 255 for a layer whose
native complete DWORD is -1. These are the two 816 requests at 5A0803 and
5A0B2A, object 852 at 5A34F1/5A3501, object 855 at 5A5305/5A530F, object
858 at 5A7B9B, objects 900 and 901 at 5A86C3 and 5A8800, object 920 at
5A9604/5A960E, and four object 940 requests using the -1 EBP established at
5AAF63 (argument pushes 5AB099, 5AB1CC, 5AB2FF and 5AB432). The 816 paths
establish EBX=-1 at 5A06CF and 5A09F4. These are actual layer slots, not the
separate dynamically selected byte-valued 0x730 layer.

The source now uses -1 at the twelve corresponding sites. The Suika manager
still consumes only the low byte; no ordinary gameplay difference is asserted.
Fresh focused compilation remains nonexact at +17 with a 78876-byte section
tail versus the 79435-byte native callable. No exact credit is added. Receipt:
`build/frontier-55d850-20261027/suika-other-layers-20261105.json`.

## Vertical grab X arithmetic, 2026-11-05

The native vertical-grab paths at `0x5A6A8A..0x5A6AAC` and
`0x5A6F7F..0x5A6FA1` multiply horizontal velocity by negative 30, multiply by
signed facing, then add actor X. The former natural single expression had
that source association, but VC8 emitted positive 30 and a final subtraction.
Naming the actually consumed double offset preserves the expression and lets
VC8 emit the negative-30 multiply, signed-facing multiply, and X addition at
both expanded sites, without a double spill. Other receiver and store
scheduling still differs; no normal-play numeric or exception-equivalence
claim is made.

The 79435-byte callable remains nonexact at +17; candidate section tail 78876.
This is not exact-function or exact-byte credit.

## Action 331 phase dispatch (2026-11-06)

Native `0x59C0FD..0x59C115` sign-extends the phase and dispatches phases 1, 2 and 3 using three subtractions and conditional branches. Expressing the existing source branches as an ordinary switch reproduces that local instruction and branch pattern in the focused VC8 candidate; handled and default phase behavior is unchanged. The complete candidate remains nonexact (78908-byte section tail, first mismatch +17); no exact credit is claimed.

### Integer gate thresholds

Five original integer gates at `0x59977E`, `0x5999C2`, `0x59C1E5`, `0x5AAA85`, and `0x5AB54C` use thresholds 16, 16, 25, 690, and 300. Equivalent source threshold forms restore their local signed comparisons and branches without changing integer behavior. The complete candidate remains non-exact, with a 78,908-byte section.

Two repeated 180-frame gates at `0x5A8629` and `0x5A8766` now use the equivalent native threshold form. Their local signed compare and branch families are recovered; the complete candidate remains non-exact.
