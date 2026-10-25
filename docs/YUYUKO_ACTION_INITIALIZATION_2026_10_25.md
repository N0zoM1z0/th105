# Yuyuko action initialization: 2026-10-25

`Yuyuko_initialize_action_entry @ 0x0056C840` is canonical exact: 2083 callable
bytes and the complete 2650-byte emitted payload. Formal and independent cold
ordinary VC8 builds reproduce SHA256
`5f8072d1c88ffed7b1afca8f6f1b59c5e5f81cf990bc2108d2c99afb95906344`.
All 103 section relocations are replayed without masking code or metadata.

## Observed target, boundary and ABI

The executable is Japanese 1.06a, SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
IDA preflight rejects the GUI's different executable. No IDA analysis read/write,
Ghidra process or decompiler is used. All 495 main instructions were read from
the hash-attested PE and every direct/switch CFG edge was reconciled.

Main `[56C840,56D063)` has SHA256
`6e09b27e7269ed20d4b45ebce471934598114bec658f0b59b3250a7d294130c4`.
Raw CFG reaches all 2083 main bytes and closes 39 RET0s. There are 19 direct
zero-motion45AF40 calls, three45AF40 tails, one45C030 wave call and the477830
default tail. The root saves EBX/ESI, moves its ECX receiver into ESI and has no
local, EH or GS frame. The pointer-only virtual receiver must never be
instantiated or embedded as a recovered full Fighter.

Existing RTTI-backed roster evidence and raw cell6C5688 bind primary slot+3C
of Yuyuko vtable6C564C to56C840. Authored ownership is unchanged. Action13C is
read with MOVSX word. Byte/short/dword publications remain distinct. The high
switch indexes through ECX, so ordinary member calls restore the receiver.

Complete `[56C840,56D29A)` owns the following metadata:

| Destination table | DWORDs | Input range | Remap start / bytes |
| --- | ---: | --- | --- |
| 56D064 |19|300..418|56D0B0 /119|
| 56D128 |35|502..731|56D1B4 /230|

All 54 destination words/216 bytes and 349 remap bytes participate. Two separate
alignment NOPs at56D063 and56D127 participate without extra callable credit.
Six INT3 bytes after the final remap separate it from the independently accepted
handle-manager destructor56D2A0. Actions4/5/214,500/501 and797/798 use direct
branches. No adjacent function bytes are included.

The actual45AF40 provider writes float zeros atF4/F8/FC/100 and returns RET0.
The actual45C030 provider reads a dword argument atESP+4, checks it unsigned
against63, indexes receiver164 and forwards the resulting handle to401D50;
its out-of-range path is RET4. The declaration-only member view preserves that
argument/cleanup contract. No new callee implementation credit is claimed.

## Independently reviewed behavior

The source keeps numeric actions, typed offsets and real opaque calls. Target
instructions, field widths, edges and publication epochs are observations;
nominal source names and full class/TU identity remain unknown.

- 4/5 set horizontal speed+/-4.214 clears736 and both velocities, sets
  gravity0.6,108=0,10C=95,73C=9 and74C=0, with no scratch-reset call.
- 300/301/303/322 conditionally zero motion when47E is zero, then clear180
  and set184=1.302 adds750=1 but preserves47E.304 clears47E and sets184=1/
  180=0 before zero-motion, then sets750.305 sets vertical speed0, horizontal
  speed12,47E/180/gravity0 and184=1.306 clears730/180 and sets184=1.
- 307/309 set184=1,180=0,750=1 without zero-motion.308 uses184=4 instead.
  310 clears horizontal/vertical speed,730 and180, sets184=99/gravity0.5.
  320 clears47E, calls zero-motion unconditionally and uses the300 suffix;
  321 calls zero-motion and publishes184=1 before clearing180.
- 400/401/411 clear180 before zero-motion, clear730/732/736 and set750.
  402/410/412 instead clear730/732/734.404/406 enter at56CE00, clearing736
  but preserving17C and734.415 clears734 and enters at56CE09, preserving736
  and17C.562 first sets17C=3 then enters56CE00. Their shared suffix clears
  732/gravity/730/180, sets750 and scales both velocities by float0.2.
- 408 sets horizontal speed14.5, clears47E/730/180/vertical speed and sets
  184=1.409 uses gravity0.35.414/416 retain an independent complete body:
  clear gravity/180, scale horizontal speed across730/732/734 publications,
  set750 then scale vertical speed.418 sets horizontal speed15/184=1/180=0.
- 500/501 set17C=0, zero motion, clear47E/730 and set180=1.502/503 scale
  velocities by float0.2 and clear gravity before that suffix without a zero
  call.505/506 and507/508 correspond to these two forms with17C=4.
- 510/511 use17C=8, zero motion and clear740 before47E/730/180=1.512/513
  instead use independently scheduled products and scalar writes, ending with
  gravity/740=0. No184 or750 write is added to these500-family paths.
- 520/521 and525/526 use17C=1/5, zero motion and clear180/47E.522/523 use
  scaled velocities with17C=1/180=0/47E=0/gravity=0 and no zero-motion call.
- 540/541 use17C=2, clear180 before zero-motion, then clear730/732/736/738
  and750.545/546 use17C=6 and set750=1 instead.547 has no zero call: it sets
  17C=2/184=1 and clears180/750, without touching those four shorts.
- 560/561 and565/566/567 use17C=3/7, set184=1/180=0 before zero-motion,
  then set750=1. They preserve the shorts cleared by other family paths.
- 599 sets180=1 before zero-motion and clears four shorts.600/602/605/606
  enter56CE9F and therefore only set180=1 and zero motion.601/604/608/610/611
  additionally clear730/732 first.704/707 enter56CEA9 and therefore only zero
  motion.603 additionally clears740, retaining its independent helper tail.
- 651 clears gravity/730/732, sets180=1 and performs the vertical product
  before the horizontal product, without a zero-motion call. Its physical body
  lies before603, rather than at its numerical switch position.
- 607/657 set180=1 before zero-motion then clear730/732.612/615 additionally
  clear736/738 and set750=1.613 enters56C9B7 after the307-family184 store,
  so it only clears180 and sets750.700 is a no-op.701/702/703 conditionally
  zero motion when47E is zero.705/706 set horizontal speed+/-6.
- 708 clears horizontal speed before the709 entry56CF9C;709 only clears730.
  710 clears180 before zero-motion and clears four shorts without writing750.
  720/730 clear180 before zero-motion then clear730/73C.725/726 publish
  horizontal speed+/-4 and clear730, retaining independent speed-load entries.
  731 clears180 before zero-motion, clears73C/730, copies currentY atF0 into
  740 and clears744.797/798 clear730 and dispatch wave argument50. Other
  actions delegate to the common initializer.

Products use the compiler-emitted qword representation of the float0.2 value,
not decimal double0.2. Every floating operand has a target-observed width/bit
binding. Full canonical comparison includes these operands and both remaps.
No behavior matrix is required to settle any remaining ambiguity in this unit.
No standalone-object/LTCG impossibility or broader runtime contract is claimed.

## Whole-function experiments and negative controls

Private inputs are retained in `.analysis/exact-first-yuyuko-action-entry-20261025/`;
reports/objects are under `build/exact-first-yuyuko-action-entry-20261025/`.
Every row compares the entire emitted symbol with complete relocation replay.

| Complete source/control | Full bytes | SHA256 prefix | Whole result |
| --- | ---: | --- | --- |
| First complete source |2618|584e3d5a|37/39 RETs;4 shares725 speed tail;510 folded|
| 725 speed publication before730 |2630|669f389e|38 RETs;independent4/725 entries restored|
| Independent797/798 source arms |2630|7fc4bc1d|restores direct comparison geometry|
| 510 clears47E before740 |2630|7fc4bc1d|whole-payload neutral; retained once|
| 510 counter publication before clears |2650|98b8aee0|39 RETs; independent native body restored|
| 651 body before603 |2650|27e6d0ea|all but6 bytes agree;547 zero-store order differs|
| Reverse547 zero-store source order |2650|27e6d0ea|whole-payload neutral|
| 547 early184 publication |2650|14d52fd4|four bytes differ;constant-store order reversed|
| 54717C before184 publication |2650|5f8072d1|exact;zero unmasked differences|

Each subsequent trial addresses a new observed publication/owner discrepancy.
There is no flag grid, assembly, target-byte arrays, padding, inert locals or
fabricated ABI. The two neutral controls concern different bounded questions;
neither is repeated after its recorded result.

The public full auditor rejects the retained old547 publication object at+1395,
with six differences and SHA256
`27e6d0ea862c98a036530847e9846130e4274cb00acb60fc4127cf9eab517c84`.
A second negative changes only the final generated-object remap byte56D299
from valid index33 to valid index0. Parsing still succeeds, but full comparison
rejects exactly+2649 with one differing byte, SHA256
`b2e70518f69be2e636aa6c736877ea52a413fbf157d1d335632331d6c18b2e79`.
Neither the canonical PE nor the accepted object is modified. Five public
synthetic fixtures cover both EAX/ECX tables, invalid final indices, metadata
destinations, truncated remaps and an unreviewed external CFG tail.

## Reproduction and next scope

Use locked repository Python and serial CPU0/nice10 jobs:

```sh
taskset -c 0 nice -n 10 scripts/repo-python scripts/build.py --unit exact-first-yuyuko-action-initialization --compare --json
taskset -c 0 nice -n 10 scripts/repo-python scripts/audit-yuyuko-action-initialization.py
TH105_ENABLE_GS=0 TH105_FP_MODE=default TH105_INLINE_MODE=default \
  taskset -c 0 nice -n 10 scripts/compile-unit.sh src/characters/YuyukoActionInitialization.cpp build/yuyuko-entry-cold.obj
taskset -c 0 nice -n 10 scripts/repo-python scripts/audit-yuyuko-action-initialization.py --object build/yuyuko-entry-cold.obj
```

Only new local source/interface/unit and13 exclusive literal aliases are added.
Prior accepted sources, shared headers, compiler settings and bindings remain
unchanged. Formal and independent cold callable/full results agree. Complete
serial cold replay passes all521 accepted units/1409 functions. Receipt:
`build/exact-first-yuyuko-action-entry-20261025/cold-all.log`. The full2650-byte
audit also passes on the object rebuilt during that replay. The exact ledger
records375415 callable authored bytes; metadata/alignment receive no extra
callable credit. Source-present1553, mapped1572 and592 configured units are
independently ledger-validated.

Next independently review Aya primary slot+3C617000, candidate2049 bytes and
cell6C6310, currently authored and source-missing. Re-attest its boundary/ABI
and each changed action before reuse. Parked roots remain separate; do not
reopen neutral controls without new independent evidence.
