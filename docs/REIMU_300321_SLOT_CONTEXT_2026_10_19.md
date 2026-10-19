# Reimu300/320/321 suffix and scalar-slot constraints

## Scope and unchanged source

This work remains inside the authored Reimu slot28 root478FA0, callable
`[478FA0,48CE2E)`,81550 bytes, SHA256
`dbf6f375a809fea91cbbccf0f8cff2196f40cba11458c98e475a290b623053e6`.
Only original Japanese1.06a executable SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`
is used. The root remains unclassified/declaration-only, with no exact credit.

A fresh focused ordinary build reproduces generated source SHA256
`c9107448d21588ecd59f4b528b14ec7a82fb7d77a4f8c13d6b7c9f6f5c562481`
and complete82824-byte canonical payload SHA256
`6527316db79ea2e1e3dd600c057f6376b472fcf43f7f6d9f2f861dac716481a8`.
Prefix81452/frame570h and all2473 relocation fields qualify. Whole-root
comparison still first differs at+541/4791BD. The genuine cache is unchanged;
the prior full ordinary/genuine correspondence is not claimed as a fresh link.
No game source, ABI, profile, binding or accepted unit input changes here.

## Observed shared suffix and actual argument predecessors

Target300 and320 have separate95-byte/26-instruction prefixes at47CBBD and
47D96A. Each calls473DD0,478EE0 and4351C0, then has its own slot8 CALL. The
current source has one physical copy. Its first26 instructions agree with
both target prefix shapes after expressing relative destinations as explicit
roles, but source entry aliasing and lost call multiplicity remain wrong.
One instruction-shape observation cannot count as two recovered copies.

**Observed:** the shared event CALL47CC4B and RET47CC5E belong to
**300/320/321**, not just300/320.300/320 check timer0/frame3 and push27 at47CC47.
321 checks timer0/frame2, pushes28 at47DA66, then JMP47DA68 enters47CC49,
after the other paths' PUSH27. The receiver publication, CALL4359F0,
byte47E clear and RET are shared. A label before300's complete frame predicate
does not express321's different predicate and argument predecessor.

Direct read-only Ghidra independently checks executable/imported identity,
base/entry, x86/windows analysis target, full mapped text and callable hash,
then decodes these exact prefixes and321's28/47CC49 edge. Both successful
runs preserve all nine primary DB hashes and remove their project aliases.
Raw PE bytes and CFG remain the durable basis; no IDA semantics is used, and
the target file and primary database bytes remain unchanged.

## Full-CFG stack observations

The existing stack auditor qualifies all11 switches, direct/virtual call
cleanup and consistent ESP at every reachable merge. Its recording subclass
retains the unchanged analysis objects; no original check is bypassed. Relative
to the aligned post-AND stack base, the target300/320 scratch cell is-55Ch:
depth-580h plus displacement24h. This physical cell has98 target and88 current
source memory touches. It has several different scalar roles in disjoint paths;
physical reuse does not prove one original C++ variable or aggregate.

The current merged300/320 prefix already uses ESP+24. The unselected named
float320 control instead introduces ESP+14 and jumps back into300 before
completing the independent prefix. Adding a local does not solve the copying.

The same analysis exposes720's four mode-loop roles:

| Source form | Base angle | Float index | Qualified observation |
| --- | --- | --- | --- |
|Target, every mode|ESP+24|ESP+20|uint draw conversion rounds into a separate float cell|
|Current source|ESP+18|ESP+20|base reuses the integer conversion scratch cell|
|Two active array/struct members|ESP+2C|ESP+28|both forms yield the same36 changed operand bytes|
|Two common mutable scalars|ESP+20|ESP+24|mode/root scope and reversed declarations yield the same payload|

The common mutable-scalar form changes87 instruction bytes, including accesses
outside720. It is not a local improvement. Moving index initialization before
the draw emits a different instruction order; initializing once before the mode
switch removes six instructions. A double base produces QWORD storage at+28
and fails the existing float32 draw-conversion contract. These remain rejected.
Offsets are compared with actual ESP depth: an access after PUSH360 cannot be
interpreted as though the argument had already been popped.

## Source experiments and preserved constraints

All controls start from the pinnedc9107448 baseline and use the frozen ordinary
compiler command/header receipt. Twenty-five natural source controls were built
serially, independently of the intentional wrong-event control:

| Family | Complete qualified outcome |
| --- | --- |
|Named320 float; reference-parameter friction inline|Same82888-byte1A5B9B3B payload; direct partition differences5->3; all1214 prior equal checks survive, but advance/slot8 still merge and scratch is wrong|
|Pointer friction inline; float-return friction/random inline; named raw uint draw; declaration-only index change|Full original6527316D payload unchanged|
|Both named floats; clamp/writeback reorder|82824 bytes; no ownership improvement; wrong scalar homes/order|
|Shared event label, shared clear/RET, common event parameter, or float/event combinations|Lose the two previously equal300/320/321 CALL/RET membership checks; unselected|
|Float-rounded double friction in300 or320|Direct partition differences3 and all1214 checks retained, but local instruction preparation remains wrong|
|Double friction plus common event parameter|82936-byte object exceeds the unchanged diagnostic envelope; both public auditors reject it|
|720 array/struct, common scalar scopes/declarations, index-first forms, double base|New scalar layouts or instruction orders; no selected source change|

`summary.json` retains every object/canonical pin, complete membership result,
frame/count report and rejection. In particular, preserving1214 physical
membership/multiplicity checks is necessary but does not establish argument
values, instruction equality or source semantics. None of these experiments
proves the original TU/profile or a standalone-object/LTCG impossibility.

## Execution evidence and reproduction

The current source passes **0/989** selected existing public300/320/321 inputs,
including actual landing/gate/advance/setter paths, event27 and the321 event28
join. All cases require their advertised target prefixes; the aggregate requires
both300/320 completions and47DA68. Native RET ABI, real helper execution, state
and arguments retain the public void-root auditor's checks. The supplied fixture
does not prove arbitrary stacks, returning-world/resource graphs or unmasked
floating exceptions.

A real wrong-source321 event28->27 control qualifies under both public object
auditors and still preserves all1214 prior equal membership checks. It yields
**10/989** actual argument/trace mismatches and exits1 after completing the
matrix. Its canonical payload is
`c73ab7e1fdfa7be2dd457320b094fb648466ef3cc4db4eac8efc692be3b07994`.
This detects the argument predecessor error even with zero event handles; it
is not a patched shared machine instruction or a fabricated callback result.

The cohorts are motion340, friction192, frames160, nodes170, directional120,
required branches4 and terminal3. Input SHA256 is
`cf8b769e3bcd17cc6c72ebcfb23c7166a65717e02be079bf1c65ba4d2f7e1fde`.

```bash
python3 scripts/audit-reimu-call-sharing.py build/reimu-300320-slots-20261019/fresh-baseline/candidate.obj
python3 scripts/audit-reimu-root-relocations.py build/reimu-300320-slots-20261019/fresh-baseline/candidate.obj
taskset -c 0 nice -n 10 python3 -B .analysis/reimu-300320-slots-20261019/native-three.py build/reimu-300320-slots-20261019/fresh-baseline/candidate.obj
```

Private recipes are under `.analysis/reimu-300320-slots-20261019/`; reports,
slot/loop facts, frozen source/header/compiler baseline and DB pins are under
the corresponding build directory. Keep the baseline and current genuine cache;
unselected generated source/object copies are regenerable. CPU0/nice10 and one
128MiB-heap Ghidra process bound the work. No aggregate cold replay is claimed.
