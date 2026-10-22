# AyaObject801 fade snapshots and source controls

## Observed target and selected source

Original Japanese1.06a PE SHA256:
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Target/tracking startup checks pass; wrong-image IDA remains rejected. Raw PE
and complete VC8 objects provide this evidence, not retained decompiler output.
Root61A290 remains the19522-byte candidate callable.

In801 sequence1, target61A585 loads the float scale field11C,
61A58B reads alpha BYTE113, and61A591 compares alpha with5. The two scale
updates follow;61A5AF branches on the earlier comparison. The previous source
read alpha only after both scale stores. The selected C++ snapshots alpha
before those updates and uses that actual value for the threshold/subtraction.
There is no ABI/header/helper/profile change, fake return or inert shaping local.
The generated alpha-read epoch now agrees, although CMP remains scheduled late.

Target61A579 also loads WORD13E once into CX for both fading sequence tests.
The selected source still reloads this field. That discrepancy remains explicit;
recovering an alpha snapshot is not whole801 acceptance.

## Original-code execution

`scripts/audit-aya-object-801-fade.py` uses the guarded804/903/901 original-code
fixture, including actual gate, trigonometric, frame/sequence and render setup
helpers. It compares complete actor/parameter state, ordered writes, helper
calls, alpha-read live x87 snapshots and final x87 status/tag. Sequence WORD13E
read epochs are separately retained in the result.

The3840-case matrix exercises sequences0..3, phases0/1/5/6, owner actions
49/50/149/150, counter thresholds3/4 and signed wrap32767, time0/1, alpha
0/4/5/19/20/255, timers0/2, eight x87 precision/rounding settings, and scale bits
covering zero, adjacent finite values, denormal, largest finite, infinity and
quiet/signalling NaN inputs. Exceptions are masked. Results:

- 3732 actual root returns, with stack/saved-register checks.
- 36 paths stopped at original64CCB0 spawn entry; outgoing seven words,
  receiver and pointed-to three-word payload are compared.
- 72 paths stopped at original435240 effect entry; outgoing five words and
  receiver are compared. Neither stopped helper is given a fabricated return.
- Selected final effects and alpha snapshots: zero differences.
- Previous alpha-read snapshot differences:1680; these disappear.
- Sequence-read differences:3012 in both previous and selected code, unresolved.

The default audit requires all observations to agree and therefore rejects the
selected object's remaining sequence reads. The explicit
`--allow-sequence-read-differences` option checks effects and alpha snapshots
while reporting that unresolved field; it never permits alpha/final-effect
mismatches. No arbitrary-resource, full spawn/effect, callback, unmasked-exception
or whole-root proof is claimed. There is no gameplay defect claim based solely
on the previous alpha-read epoch.

## Explored controls and limits

Four target-motivated source forms were compiled serially:

| Form | Complete canonical bytes | SHA256 prefix | Result |
| --- | ---: | --- | --- |
| Previous checkpoint | 20048 | edd3903d | Late alpha read; repeated sequence read |
| Alpha plus explicit sequence snapshot | 20096 | b45c3790 | Changes other actions' x87 scheduling; not selected |
| Alpha snapshot only | 20136 | a2fafaa2 | Selected; other-action strict graph preserved |
| Alpha via actual color member's byte3 | 20136 | a2fafaa2 | Entire payload identical to alpha-only |
| Alpha plus early Boolean threshold value | 20136 | a2fafaa2 | Entire payload identical to alpha-only |

The sequence-snapshot form passes all3840 scoped801 cases, including both
alpha and sequence reads, but this does not close its changes to other actions.
It merges the alpha stores from the two mutually
exclusive branches; target keeps them separate. Its outside801 strict graph
fails. Further diagnostic inspection found operand-order swaps in other actions,
branch-polarity/tail merging and an x87 FILD/FMUL versus FLD/FILD/FMULP change.
These are not automatically errors: one changed861 addition now has target
61C2DF's FLD370/FADD11C order. They do require separate target/execution evidence
before selection. A private relaxed diagnostic only located these differences;
it is not an accepted equivalence checker. No generic floating commutation or
branch wildcard was added to the strict checker.

The alpha-only source preserves4491 strict instruction-labelled normal-return
graph nodes outside801 with no carrier allowances. The full payload grows88
bytes through compiler tail sharing/placement changes; this is a real unresolved
byte-matching cost, not hidden by owner statistics.801 remains520 bytes/128
instructions versus target503/117. Physical layout and sequence caching remain
open; the additional Boolean/member-alias controls do not resolve either.

## Canonical result and reproduction

Selected full20136-byte SHA256:
`a2fafaa2de959366066d6d2a0f2ab794c4f5b2260c294312d2ed03d3cf6b3d9d`.
Metadata starts19668. The19522-byte comparison SHA256 is
`5a25bb2689509d62bf0d93a39f858f5c54e3915527d117b6873d021d7d5d7ea1`.
Canonical mismatch remains at hex offset22, target0F/sourceA1. No exact credit.
The three prior low-byte predicate consumers also pass on the selected object.

```sh
taskset -c 0 nice -n 10 python3 scripts/build.py --unit gpt-web-aya-object-vslot28-full-root --compare --json
taskset -c 0 nice -n 10 python3 scripts/audit-aya-object-801-fade.py --previous-object build/aya-801-fade-20261022/previous.obj --allow-sequence-read-differences --output build/aya-801-fade-20261022/selected-native.json
python3 scripts/audit-aya-object-normal-flow.py build/aya-801-fade-20261022/previous.obj build/match-units/GptWeb_AyaObjectActionState.obj --exclude-action 801 --output build/aya-801-fade-20261022/selected-outside801.json
python3 scripts/audit-aya-object-predicate-widths.py
python3 scripts/validate-tracking.py --require-target
taskset -c 0 nice -n 10 python3 scripts/ci.py
git diff --check
```

The configured root comparison is expected to report nonexact. `previous.obj`
is the saved8466c73 object. Omit that argument when replaying selected code only.
Frozen controls and reports remain under `build/aya-801-fade-20261022/`; private
expanded diagnostics are in `.analysis/aya-801-fade-20261022/`.

Three completed control objects were SHA256-verified through a tar.gz round trip
and archived: 120637 to36068 bytes. Frozen sources, reports,
previous/selected objects and active target/compiler inputs remain available.
`retention.json` records member hashes and verifies the target, public source
and active object before/after deletion. Restore members from the repository root
with `tar -xzf build/aya-801-fade-20261022/completed-controls.tar.gz`.
