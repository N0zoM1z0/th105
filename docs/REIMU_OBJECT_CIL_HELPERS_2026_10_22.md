# ReimuObject real helper visibility and coordinate controls

This continues the [resolved real-provider context](REIMU_OBJECT_REAL_PROVIDER_CONTEXT_2026_10_22.md)
for `496540`. All target observations use Japanese 1.06a, SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Fresh IDA preflight rejects the open image; it supplies no semantics. Public
source, types, profiles, bindings, ownership and exact rows remain unchanged.
No new exact credit or aggregate cold replay is claimed.

## Fixed root and one real helper at a time

One fresh O2/GL root object is reused across four links. The baseline uses the
20 genuine native-provider inputs of the preceding context, replacing only its
root object. Each other link partitions the real `CharacterObjectRuntime.cpp`
into one selected CIL method and a native complement containing the other two
methods. No method body, declaration or callback type changes. Native
complements compare exact before linking. All ordinary root, counter and
Runtime helper interfaces remain exported, so actual calls and complete
helpers can be inspected independently. Replacing one Runtime object with
the two partitions gives21 code objects in those three variants.

All four links resolve with the same pinned static CRT/SDK libraries, four
data-only ABS bindings and eight source-view aliases. Every input object hash
is checked. There are no executable ABS providers. The complete oriented,
advance and phase helpers compare respectively **57/57, 62/62 and 73/73** in
every image; `4963A0` remains **66/66**. Helper comparison independently closes
each body, including advance's real indirect virtual tail jump. Only the two
named orientation lookup E8 operands need replay. Arbitrary virtual AL means
advance's return contract cannot be replaced with bool merely for codegen.

| CIL helper visibility | Root prefix | Source normal CFG | Call / RET membership distance |
| --- | --- | --- | --- |
| None; fixed root itself CIL | Different at +0 | 22 switches, 10,485 reachable instructions | 15 / 27 |
| Oriented components `435160` | Different at +0 | Same counts | 15 / 27 |
| Advance `4351C0` | Different at +0 | Same counts | 15 / 27 |
| Phase counter `64CD00` | Different at +0 | Same counts | 15 / 27 |

Each root starts with an aligned EBP frame rather than target's native
`sub esp,438h` entry. Its available symbol span is45,600 bytes and first switch
metadata offset44,720. These are source diagnostic surfaces, not accepted
target boundaries. Complete guarded normal-CFG inspection retains432 physical
calls (405 direct,27 indirect),63 RETs, and actual calls to all helpers:
oriented47, advance19, phase5 and same-TU counter27. Target has433 calls
(404 direct,29 indirect),68 RETs, and respectively47/22/5/27 calls to those
helpers. These counts do not imply that the CIL root is closer to exact.

The source's four extra direct calls belong to the private `fabs(float)`
overload in action817. Its actual26-byte body is separately bounded and pinned;
it is **not** assigned the game's different-ABI `fabs(double)` destination.
Call/RET memberships use one label per action800..999 plus the out-of-range
default, rather than assuming source and target group actions identically.

After replaying only named E8 operands for a source-to-source comparison, the
complete baseline/oriented/advance spans agree, SHA256
`eb93530707245a03c7b0698d1acee10bfd0e77311b3ff29c60e63052989956e7`.
Phase visibility changes that span to
`d6c246085007c5a48f7a288b902bf8b5367e3a01cf786a305dabe2bf10cf9361`.
This is neither canonical equality to the game nor a general LTCG conclusion.

## Observed floating lifetimes discriminate the controls

At target's action816 phase calls `498846` and `498B2C`, the next instruction
is `FLDZ`. The native-provider baseline also reloads zero at both calls.
Making the genuine phase body CIL-visible removes those two reloads, carrying
floating state through the calls. That tested visibility change does not
recover these observed target lifetimes even though the helper itself remains
73/73. This independently rechecks the older visibility concern in the newly
resolved provider context; earlier hosted conclusions are not used as proof.

A separate control explicitly promotes each already-rounded float input to
`fabs(double)` in the two action817 predicates. It preserves float coordinate
subtraction and input rounding, without force-inline or helper facades. The
CIL root loses all four private float-overload calls, closes all22 switches
with10,451 reachable instructions, and has428 calls /63 RETs, membership
distances11/27. It still has the incompatible aligned EBP entry at+0. Removing
those four calls alone therefore does not fix that entry in this context.

The ordinary native version also changes:45,668 section bytes versus selected
45,700, still nonexact+31, counter66/66 retained. Raw target inspection explains
why it is not selected. Every target FABS at `498D26`, `498D55`, `49958D` and
`4995BC` immediately stores to a float temporary then reloads it before the
comparison. Selected native source retains that exact local instruction
sequence; explicit double overload removes it at all four sites. Equal
absolute values would not justify discarding these observed write/reload
lifetimes. No new execution claim is made for this rejected control.

## Coordinate record hypothesis stops at genuine wrappers

The target wrappers forward seven32-bit words, so two scalar floats versus an
eight-byte coordinate record were initially separate source hypotheses. A
private `SpawnPosition` uses real x/y fields, a normal two-float constructor,
and checked size8/offsets0,4. Both declarations, genuine wrapper definitions
and the manager callback typedef consistently use the record by value.

Native comparison of the complete real providers produces69/77 at `4FCA60`
and70/78 at `64CCB0`, both different at+0. Target starts by loading a scalar
float; this record view begins integer forwarding. The probe stops there:
the106-site root rewrite is not compiled or qualified, and no alternate type
is selected. This rejects the tested native record view, not every possible
original coordinate representation or compiler context.

## Reproduction, current selection and remaining work

Private recipes are under `.analysis/reimu-object-helper-cil-20261022/`:
`probe.py`, `graphs.py`, `census.py`, `phase_lifetimes.py`,
`double_fabs_probe.py`, `fabs_roundtrips.py` and `native_replay.py`.
Receipts are below the matching `build/` directory: `results.json`,
`graph-results.json`, `owner-results.json`, `phase-lifetimes.json`,
`double-fabs-link.json`, `graph-results-double-fabs.json`,
`owner-results-double-fabs.json`, `fabs-roundtrips.json` and
`native-replay.json`. The coordinate recipe and provider comparison are in
the matching `reimu-object-position-value-20261022` private/build directories.
All builds run serially at CPU0/nice10. Neither linked image is executed.

Fresh native replay rebuilds the selected public root and genuine public
spawn providers. Root source SHA256 remains
`3b9e4896c3645bb1228db3b432a832154870c5639a80df6c02cb67ce2dba12cc`;
complete45,700-byte canonical source remains
`d0ff3d3259c823cc56e322c5e0ec238456d8b490c78b4a5336a249b45a405a58`,
nonexact at `49655F/+31`. Counter66 and parented77/unparented78 remain exact.

These controls leave native constant lifetimes, physical call/RET sharing,
908's post-wave x87 order and original compilation ownership unresolved.
Preserve the target-backed float round trips, phase-call reloads and existing
original-RNG argument-order evidence. Further root context work needs an
independent lifetime or ownership lead; repeating these three visibility
controls or substituting the shorter double/record forms supplies none.
