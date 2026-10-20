# ReimuObject ordered stores and902 owner-member recovery

Work continues on complete canonical equality for `0x00496540`. This is a
source-recovery checkpoint, **not an exact result**. The original Japanese
TH10.5 v1.06a executable remains SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
The preceding selected source was the
[fade-order checkpoint](REIMU_OBJECT_FADE_ORDER_2026_10_20.md).

## Fresh target observations

The hash-attested PE, decoded on complete instruction boundaries, establishes
fifteen additional X-before-Y store pairs and855's368-before366 pair:

| Action | First store addresses | Fields, in target order |
| --- | --- | --- |
|800|496624|scale11C,120|
|801|496989;496B16;496B44|scale11C,120; velocityF4,F8 twice|
|810|497446;497698;497706|scale11C,120; velocityF4,F8 twice|
|812|497EF5|scale11C,120|
|817|49906C;499298;49935E|scale11C,120 three times|
|821|49997B|scale11C,120|
|822|49A179|scale11C,120|
|855|49B7A5;49B7B1|scale11C,120; state368,366|
|860|49BF13|scale11C,120|

The retained chained assignments write those fields in the opposite order.
Separate assignments now preserve target order and evaluate random/lookup
expressions once. The two817 channel111/channel112 chains are deliberately
retained: their right-to-left order agrees with the target.

A seventeenth group occurs at822's499F14/499F16: parameter word0 is written
before heading12C, followed by the copied packet's first word. The old
`parameters[0] = heading = value` writes heading first. Separate stores recover
the observed order. This path follows opaque wave/setup operations; ordinary
entry-stop fixtures do not establish execution through that prefix.

For902, the target sequence0/1 entries are separate at49D7ED/49D978. Each
has its own owner-health gate, pulse calculation and rectangle publication.
Both reach the real fade block at49D913. The old source instead entered one
combined block and tested the sequence again inside it.

Each rectangle publication first rounds into an actual float stack slot,
loads that rounded value, and writes one owner member. Subsequent publications
reload owner348. These eight stores are:

| Sequence | Owner fields | Target store PCs |
| --- | --- | --- |
|0|7A8,7B0,7B8,7C0|49D8A7,49D8C9,49D8EB,49D90D|
|1|7AC,7B4,7BC,7C4|49DA2E,49DA50,49DA72,49DA94|

The local `ReimuOwnerBoundaryView` describes those eight float members with
compile-time offset checks. Its preceding byte range represents unmodeled
owner state, not a recovered original base-class declaration. No storage is
added to the runtime object or function frame.

## Source and compiler experiments

Splitting902's two calculations and retaining their shared fade block is a
source-shape hypothesis supported by the target edges. The original C++
spelling remains unknown. Under the unchanged selected compiler profile,
typed float-member writes naturally restore all eight spill/load/store
sequences and owner reloads. No volatile qualifier, assembly, forced stack
slot, fake helper return or compiler-flag change is selected.

| Private control | Code prefix | Canonical payload SHA prefix | Observation |
| --- | ---: | --- | --- |
|Old selected source|44908|343089b7|Wrong sixteen store pairs;902 calculations combined|
|Sixteen ordered pairs only|44908|ff008138|Write order restored;902 still combined|
|902 separate calculations|45116|2a54ec77|Owner writes still lack eight spill/reloads|
|Separate calculations, shared fade|45036|afddcee6|Retains the target fade join|
|Float-value setter inlined|45116|2a54ec77|Identical to direct raw-pointer stores|
|Byte-storage copy|45148|4a053255|Float spills, but integer copies replace target x87 stores|
|Typed owner members, shared fade|45144|a792ff5f|Eight target-style float publications|
|Typed members, independent fade bodies|45228|e047c126|Duplicates the target-shared fade body|
|Typed members plus numeric action order|45164|a26352ef|Still nonexact; no basis for selecting this ordering|
|Selected, including822 parameter/heading order|45144|88bd9c9b|Same complete direct/indirect call membership partitions|

Moving retirement and animation labels, expanding all local exits, splitting
951's guards, and matching source case order to physical target order also
remain unsuccessful controls. Some alter target call-site partitions. These
results do not establish standalone-object or LTCG impossibility, and they
do not prove that retained labels reflect the original source.

Additional caller/callee context controls keep real implementations:
4963F0 release remains43/43 and496420 replacement remains274/274 when each
is visible beside the selected root, but the root payload remains88bd9c9b.
Enabling `/GS` also leaves this root/helper pair unchanged; the absence of a
cookie in this function therefore does not prove a GS-off original TU.
The current RTM build is nonexact+31, code45152/payload46020/hash1c7470e7,
with the counter still66/66 and equal call memberships. No such profile or
source partition change is selected.

A separate control restores the fourteen real World arrays to their narrowest
valid block scopes and emits their calls within those lifetimes. The901 pair
remains alive through its genuine shared local consumer. That control is
nonexact+31, code45356/hashaae2de30, and changes call memberships; it is not
selected. The experiment does not prove that local lifetimes are impossible
in another honest context.

The selected code has65 RETs against target68; membership distance25 is only
a diagnostic. Physical-owner instruction/edge identity is0/43. That diagnostic
is not an acceptance metric:902's member recovery can improve specific
instruction protocols while changing unrelated tail placement.

## Execution checks and limits

An initial25411-input experiment over the nine affected actions found zero
final-output differences for both the old and ordered-pair sources. The old
source had3756 ordered-write differences; the ordered source had none.
All sixteen first-store sites executed. This demonstrates why final-state
equality alone was insufficient. A subsequent12163-input deterministic
cross-action sample also found no object-field event or output differences
for the ordered source; that sample did not include parameter-region events.

The public `scripts/audit-reimu-object-typed-stores.py` strengthens the check:
it compares actual object, owner and parameter write events, retains all
original prefix-result comparisons, checks all eight float publication
patterns, and separately checks822's post-opaque store pair statically.
It records coverage explicitly. A zero execution count for499F14 is not
counted as dynamic evidence for that path.

The full133192-input replay passes with zero output differences and zero
object/owner/parameter event differences. Its input SHA256 remains
`f46a849ff57f64bb16e77fd0e28f7f51eee7238501c04049add99e7f77fc3b8b`.
All sixteen prefix store groups execute, and each902 owner publication executes
144 times. The822 post-opaque pair executes zero times and retains only its
separate static evidence.

Two compiled negative controls distinguish the checks: the predecessor's3024
855-transition inputs have zero output differences but378 write-event
differences; the ordered-pair/raw-owner control's2592 upper-state inputs have
zero output/event differences but lack all eight float-publication patterns.
Those restricted matrices also report incomplete overall site coverage; their
nonzero exit alone is not the sensitivity claim.

All19 serial commands in `selected-checks.json` finish with expected exits.
Preserved checks include the300 fade witnesses and all72/12-byte windows,
999's792 witnesses,869/901's128 lookup consumers,3360 animation inputs and
actual801/852 selector calls,812/World/900/901/804/selector-family checks,
808/812 caller checks, orientation400, alpha1170 and terrain288. The terrain
hardware qualifications remain unchanged. The source closure has10457
reachable instructions,404 direct plus29 indirect calls and65 RETs.
All25 direct-callee partitions and all indirect memberships still agree.
Source/header/object/support pins agree before and after the serial run.
Receipts are under `build/reimu-object-exact-20261020/`.

Opaque World/setup/wave/event/CRT continuations, arbitrary aliases/resources/
vtables, nonnull rendering, unmasked exceptions and hardware qualification of
nonfinite terrain contexts remain outside this finite execution contract.
Stack-packet write order is not covered by the new object/owner/parameter
event stream. Existing packet audits retain their own scopes.

## Current canonical result and reproduction

| Selected artifact | SHA256 |
| --- | --- |
|CPP|`555da0705db3e800f92c756449b88560d60d0a8d91a40f13d7c6c5feb354bfe2`|
|Header, unchanged|`6f469e6886959fd41ee6976b3c784c3df0c2e753ad4729a536764a3c8cd28b4b`|
|Formal COFF|`da35fa3833d68129cf26608f6d3064ba1fbc7971d0260aa2716da0c66c4ec504`|
|Canonical46012-byte payload|`88bd9c9bc88d9fc7643a2a162de2aa1cee026fb7d744bb8feb559bb86d54474e`|

The full46138-byte owned-extent comparison still first differs at49655F/+31.
The candidate's46012-byte section tail includes868 metadata bytes; it must
not be described as only126 callable bytes short. Its metadata starts at
offset45144, whereas the target tables start at46140. No root exact row,
remote-exact flag, partial authored-byte credit or aggregate percentage is
added. The actual same-TU4963A0 helper remains **66/66 canonical exact**.

No shared header, accepted ownership boundary, relocation key or selected
compiler flag changes. IDA remains attached to the wrong executable and was
not used. No Ghidra process, target patch or analysis-database write was used.

```bash
taskset -c 0 nice -n 10 python3 scripts/build.py --unit gpt-web-reimu-object-action-state --compare --json
# Expected exit1:496540 mismatch+31;4963A0 exact66/66.
taskset -c 0 nice -n 10 python3 scripts/audit-reimu-object-typed-stores.py build/match-units/GptWeb_ReimuObjectActionState.obj --output build/reimu-object-exact-20261020/typed-stores-replay.json
taskset -c 0 nice -n 10 python3 scripts/audit-reimu-object-fade-order.py build/match-units/GptWeb_ReimuObjectActionState.obj --output build/reimu-object-exact-20261020/fade-replay.json
python3 scripts/check-match-literals.py --require-target
python3 scripts/validate-tracking.py --require-target
python3 scripts/ci.py
git diff --check
```
