# Reimu616 effect lifetime and compiler revision controls

## Scope and target observations

This continues the complete `Reimu_dispatch_action_state_vslot28 @478FA0`
root, callable81550 bytes, rather than treating616 as a function. Original
Japanese v1.06a executable SHA256 is
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`;
callable SHA256 is
`dbf6f375a809fea91cbbccf0f8cff2196f40cba11458c98e475a290b623053e6`.
All eighteen controls here remain unselected. No reconstruction source,
compiler profile, binding, implemented/matches row or exact credit changes.

**Observed:**after event23 CALL489FD2,616's effect115 preparation is22
instructions at489FD7..48A025, followed by CALL435240. It loads Y with FLD,
zero-extends facing byte104 into EAX, adds double144, pushes1 and EAX, then
sign-extends AL into EAX. Its rounded Y home is `[esp+20h]` after those pushes.
The signed X offset is calculated entirely in EAX: LEA three times the value,
three doublings to24 times, then integer-to-float conversion and addition of X.
The integer/rounded X home is `[esp+28h]`. No extra memory read of facing is
needed to supply its different unsigned-argument and signed-X roles.

The selected source's corresponding preparation is23 instructions. It reads
AL, zero-extends it into EDX for the argument, sign-extends AL into EAX for X,
and stores/reloads Y at `[esp+18h]` before pushing the integer arguments.
A wide unsigned direction local instead reproduces22 instructions and the
target's initial pushes/Y home, but calculates the integer offset in **EDX**.
Five operand encodings still differ. Equal instruction totals are insufficient.

The two650/651 threshold paths also have distinct target tails:
48A282->4852F6 loads the slot14 setter into EDX and calls4852FD;
48A485->47D7BE loads it into EAX and calls47D7C5. The651 descent branch
48A601->48A2B0 joins650's shared height/reset/set_sequence4/RET block:
CALL435D60 at48A2B2, CALL45AF40 at48A2BF, virtual slotC at48A2CD and RET48A2D6.
These observations independently justify testing explicit source joins.

## Fresh baseline and fifteen SP1 source controls

Fresh generation/build repeats source
`7650c8d3b96683b69ef596d6eac0793ed8350ae24a7840c608a629e9929d43cf`,
header `5212c424d02e266659335e78b728b336b30fe6c1d6557ac8268bf31bdb2610fd`
and complete canonical payload
`fbc0293d5e7ab9b39aca3d83c4d044ce7603d2e28d7961d2ff7736ef3f360177`.
This is still nonexact at+541/4791BD. The fresh baseline has1236 equal positive
membership/multiplicity checks and4897 equal physical/per-action count checks.
The original153 RET partitions remain equal.

All builds are serial at CPU0/nice10, using the existing VC8 options. Every
candidate qualifies under both complete object auditors; no ABI or relocation
checks are relaxed. Every frame remains570h.

| SP1 source controls | Count | Payload SHA prefix | Payload / code prefix | Instructions | Lost groups / counts |
| --- | --- | --- | --- | --- | --- |
|Unsigned-byte carrier with named Y; used inline helper with byte carrier|2|`fbc0293d`|82808 /81436|20245|0 /0|
|Wide carrier; named X/Y/integer offset; commuted X sum; mutable signed-X/unsigned-argument locals; inline helper with wide local or int argument|8|`aba67d99`|82840 /81468|20261|19 /4|
|Signed int carrier with byte conversion for the argument|1|`764424eb`|82808 /81436|20245|0 /0|
|Explicit650/651 landing join; that join plus both threshold-tail joins|2|`8cf65d0f`|82808 /81436|20245|0 /0|
|Wide616 plus explicit650/651 landing join|1|`515b5dc4`|82808 /81436|20244|12 /0|
|Wide616 plus landing and both threshold-tail joins|1|`0be53cb5`|82808 /81436|20244|12 /0|

The inline controls contain the actual effect expression and existing typed
member call. No helper return or behavior is fabricated; complete qualification
confirms there is no new external helper identity. These source contexts do
not change the resulting wide/byte payloads.

**Inference from controls:**the earlier negative wide-carrier result was
partly sensitive to source context. Explicitly joining the independently
proved650/651 landing prevents its extra physical height/reset/setter/RET
copies. Those four count regressions disappear, yet twelve correct memberships
still regress across slot8/slot14, RET and all-indirect domains. In particular,
616 completion ownership is disturbed even though its source goto remains.
The effect preparation still uses EDX for multiplication. This combined
candidate cannot be selected as a correction.

The fresh public `--baseline-object` comparison for `wide-join-all` exits1
with twelve lost groups and zero lost counts. This complements the preceding
[300/320 counterexample](REIMU_300320_IDENTITY_CONTROLS_2026_10_20.md), where
groups improved but one per-action count regressed. Both constraint families
are necessary, and neither substitutes for instruction comparison.

The byte-carrier controls are payload-neutral. The signed carrier retains the
positive physical checks but begins with MOVSX instead of the target's MOVZX
and does not recover the target preparation. The explicit landing join moves
the common source block from650 into651's physical span:823 payload bytes
differ despite unchanged total instruction/site counts. Correct membership
alone does not establish correct placement.

## Three compiler revision controls

The target Rich/linker data establishes the VC8 family/build50727, not an
exact patch revision. The installed compiler/front-end/backend files are
individually hashed and have version14.0.50727.762 for SP1 versus
14.0.50727.42 for RTM. RTM is a private diagnostic environment, not a newly
accepted toolchain/profile. All three RTM candidates use the same source and
options as their corresponding SP1 controls.

| RTM control | Payload SHA prefix | Payload / code prefix | Instructions | Lost groups / counts |
| --- | --- | --- | --- | --- |
|Unchanged current source|`73ff146f`|82852 /81480|20247|0 /0|
|Wide616|`f4c00f55`|82884 /81512|20262|19 /4|
|Wide616 plus all three joins|`1ae37d59`|82836 /81464|20244|12 /0|

RTM's unchanged-source code prefix is only8 bytes shorter than target, versus
52 for SP1. Nevertheless, fresh reuse of the public owner-relative instruction
comparator gives53/127 identical physical spans for SP1 and6/127 for RTM.
Both reports use the same target owner names, aliases, starts and extents.
RTM loses48 previously identical spans and gains one (`high:798`); five are
retained. This diagnostic preserves operand encodings and internal edges by
physical owner/offset. It awards no function or partial-byte credit.

All nine distinct payloads in this batch are examined with that comparator:
SP1 baseline/signed give53, wide/landing/wide+landing give51, wide+all joins
gives50, and all three RTM candidates give6. None recovers616's full preparation.
RTM's wide controls still use EDX for the integer X offset. A nearer size is
therefore insufficient evidence to switch compiler versions. This batch does
not prove the original compiler revision or rule out another source/TU context.

## Field storage and case specialization follow-up

Seven subsequent controls distinguish the physical byte declaration from its
signed consumers and from constant action specialization. A fresh baseline
again reproduces7650c8d3/fbc0293d. Reachable target instructions contain385
direct ESI+104 accesses, all one byte:315 MOVZX,51 MOVSX, seven plain MOV reads
and twelve MOV writes. Direct read-only Ghidra independently decodes all385
addresses after target/mapped-byte attestation. Missing listing instructions
are disassembled only in the unsaved read-only working state; all nine primary
database hashes remain unchanged. These extension operations establish use
roles, not the original C++ field declaration.

The expanded source has1214 rvalue uses and18 writes of `facing_104`, including
constant action branches. One private view changes its declaration to unsigned
char while preserving signed interpretation at every rvalue use and retaining
the writes' byte representation. Known unsigned consumers use the original
unsigned bits. A signed-declaration control adds the same explicit signed
casts, separating declaration effects from redundant source casts. Local
unsigned-char alias-reference controls preserve the public signed declaration.

| Follow-up controls | Count | Payload SHA prefix | Payload / code prefix | Instructions | Lost groups / counts |
| --- | --- | --- | --- | --- | --- |
|Explicit signed reads; local byte alias; specialized650/651 source|3|`fbc0293d`|82808 /81436|20245|0 /0|
|Wide copy of local byte alias; specialized650/651 plus wide616|2|`aba67d99`|82840 /81468|20261|19 /4|
|Unsigned field with signed consumers preserved|1|`72271db6`|82968 /81596|20244|41 /4|
|Unsigned field plus wide616|1|`52859286`|83000 /81628|20260|57 /5|

The unsigned-field variants exceed the callable by46/78 bytes and metadata
envelope by44/76. Default qualification rejects the first; both are then
inspected through the existing explicit **read-only oversize diagnostic**.
They are never executed. The whole-root regressions and differing preparation
prevent selection; they do not prove the original field was signed.
Neither local alias form recovers616's target preparation.

Specializing650/651 removes sixteen known constant comparisons, selects the
existing correctly typed ternary branches and removes only inactive blocks
without labels/else. Remaining scopes and runtime evaluation stay intact.
Both ordinary and wide616 controls reproduce their complete preceding payloads.
This source cleanup therefore does not resolve the observed register/ownership
differences in the tested context. No generator change is selected.

Recipes and all eight build receipts are under
`.analysis/reimu-facing-storage-20261020/` and
`build/reimu-facing-storage-20261020/`. `probe.py` covers the five type/view
controls, `prune.py` the two specialization controls, `facts.py` the reachable
field packet, and `ghidra.py` the independent readback. `summary.json` retains
artifact hashes/results before redundant generated files are removed. The
public source/header, binding and current genuine closure remain unchanged.

## Reproduction, safety and remaining questions

Direct Ghidra runs read-only with128MiB heap and one CPU. Before decoding it
re-attests raw/imported SHA, base/entry, x86/windows target, mapped text, full
callable hash and vtable6C4154->478FA0. It verifies616's completion edge and
the three650/651 edges above. All nine primary database hashes remain unchanged;
the temporary project alias is removed. IDA's wrong-target preflight prevents
its use; no IDA semantics, factory adapter or target patch is used.

Private recipes are in `.analysis/reimu-616-effect-lifetime-20261020/` and
reports in `build/reimu-616-effect-lifetime-20261020/`:

```bash
taskset -c 0 nice -n 10 python3 -B .analysis/reimu-616-effect-lifetime-20261020/probe.py wide byte-y signed join-landing wide-join-landing wide-join-all inline-wide inline-byte rtm-baseline rtm-wide rtm-wide-join-all
taskset -c 0 nice -n 10 python3 -B .analysis/reimu-616-effect-lifetime-20261020/profiles.py baseline wide signed join-landing wide-join-landing wide-join-all rtm-baseline rtm-wide rtm-wide-join-all
taskset -c 0 nice -n 10 python3 -B .analysis/reimu-616-effect-lifetime-20261020/ghidra.py
```

`summary.json` retains hashes, complete constraints and preparation observations
for all19 builds, including the baseline. Compiler hashes, target instruction
packet, owner reports and database pins remain private. Redundant generated
source/objects are removed after recording them; representative inputs remain.
No new native execution or genuine-linked comparison is claimed for these
unselected candidates. The selected source and its existing genuinefbc0293d
closure remain unchanged.616's local width/lifetime context,300/320's copies,
720's float homes and full-root/world semantics remain unknown. There is no
standalone-object or LTCG impossibility conclusion and no aggregate cold replay.
