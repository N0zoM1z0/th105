# Marisa action initialization: 2026-10-25

`Marisa_initialize_action_entry @ 0x004B89C0` is canonical exact: 2446 callable
bytes and the entire 3034-byte emitted payload. Formal and independent cold
ordinary VC8 builds reproduce SHA256
`fc233d82247c3c53ebd71b3675b9393ddb228b8494717a1bc7044b4cc6e3f690`.
All 115 section relocations are replayed, with no masked code or metadata.

## Observed target, boundary and ABI

The executable is Japanese 1.06a, SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
IDA preflight still rejects the GUI's different executable. No IDA analysis
read/write, Ghidra process or decompiler is used. All 589 main instructions
were read from the hash-attested PE and independently reconciled with the
switch edges before source selection.

Main `[4B89C0,4B934E)` is 2446 bytes, SHA256
`5e3c47e2ccc8a7c8af3a1ee8d766d10dfba9415df14abd77bffd6c0cbec95d19`.
Raw CFG reaches all 589 instructions/all 2446 bytes and closes 38 RET0s. There
are four zero-motion45AF40 tails, one face/velocity478E60 tail and one default
477830 tail. Direct calls are 25 zero-motion45AF40, two wave45C030, one scratch
reset435110, one landing predicate5F9310 and one spawn465190.

The prologue reserves 12 real temporary bytes and saves EBX/ESI. ECX is the
receiver, moved into ESI; no EH/GS frame is present. The 12-byte array in603 is
populated and passed to the actual spawn call. The declaration-only receiver
and scratch views are never instantiated or embedded as recovered full owners.
The int-return landing predicate preserves its independently accepted producer
ABI; this caller explicitly consumes its low byte, matching the actual TEST AL.
No bool-return declaration is substituted for the existing integer producer.

Existing RTTI-backed roster evidence and raw cell6C45C0 bind primary slot+3C
of Marisa vtable6C4584 to4B89C0. Authored ownership is unchanged. The target's
high remap indexes through ECX, so high-region call paths restore the receiver.
In particular, the shared 400 body starts4B8BDF for the low table; high560/565/
570 entries go through4B8BDD's real MOV ECX,ESI prefix. Ordinary member calls
reproduce both entries without an invented register convention.

Complete `[4B89C0,4B959A)` includes two remapped tables:

| Destination table | DWORDs | Input range | Remap start / bytes |
| --- | ---: | --- | --- |
| 4B9350 | 23 | 300..432 | 4B93AC /133 |
| 4B9434 | 32 | 504..733 | 4B94B4 /230 |

All 55 destination words/220 bytes and363 remap bytes participate. Adjacent
alignment is2 bytes `8BFF` after the main and3 bytes `8D4900` after the first
remap. These five payload bytes get no extra callable credit. Six INT3s follow
the last remap before the next separately tracked function4B95A0.
Low4/5/214,500 and797/798 have direct branches outside these tables.

## Independently reviewed behavior

The source retains numeric states, typed offsets and real opaque helper calls.
Same-family reuse preserves the following target-specific differences:

- 4/5 set horizontal speed6 and-5 respectively.214 first calls the actual
  this+4 scratch reset, then clears velocities/short736, sets gravity0.6,
  108=0,10C=95,73C=12 and74C=0. It does not copy73C into74C.
- 300/301/303/321/322 conditionally zero motion and preserve750.302 also clears
  47E and sets750;304 publishes47E/184/180 before zero-motion.305 writes
  horizontal speed17.5, vertical speed0 and gravity0.307/308 have no zero call;
  309 publishes the same184/180/750 fields before its real zero-motion tail.
  310 preserves velocity;320 clears47E/180 and publishes184 without zeroing.
- 400/401/402/411 clear736/732/730 after zero-motion and set750.560/561,565/566
  and570/571 publish17C=3/7/11 before that shared body.404/406/415 enter after
  the562/563 17C publication and therefore preserve17C.562/563,567/568 and
  572/573 use3/7/11 and share the actual zero-gravity/scaled-velocity body.
- 410 clears730/732/736/738 and sets750;412 omits the750 write.414 scales
  horizontal and vertical velocity across four short clears and a750 write.
  420/421 additionally clear7A8/7A4 instead of738;422 scales velocity with those
  five clear operations and does not write750.430/431 clear all six shorts;
  432 combines their clears with scaling, again without adding a750 write.
  416 clears180/738 and publishes184;418 sets speed17.5 before the300 path.
- 500 clears180 after zero-motion and uses gravity0.55.504 additionally sets
  both velocities10 and180=1;505/506 use17C=4.510/512 use17C=8 and clear73C/
  184/180/47E.520/521 publish184=99, while525/526 and530/531 publish184=0;
  606 enters the actual520 suffix after its17C publication and preserves17C.
- 540/541,545 and550/551 use17C=2/6/10, clear180 before zero-motion and clear
  four shorts/750 after it.542/547 publish17C=2/6 and184=1 and clear180/750
  without a zero-motion call. Those no-call entries retain their own store order.
- 599 writes180=1 before zero-motion, then clears four shorts.600/601/602/608/
  610/611/658 clear730/732 and set180=1 before a zero-motion tail.603 retains
  that prelude and calls the actual integer landing predicate, tests its low
  byte and only when zero spawns853 with a real `(0,0,10)` packet, current X/Y,
  unsigned-byte direction, variant-1 and count3. No provider result is supplied.
- 605 clears730/180 and publishes184=6 before zero-motion, then clears732/734.
  607 only zeros motion and clears47E/730.612/615 set180=1 before zero-motion,
  clear738/736/732/730 and set750;613 only clears180 and sets750.
- 619/730/732 clear730/732 before zero-motion.707/720/722 only zero motion;
  708 clears730 after the call.710/711 zero motion before the actual face/
  velocity helper tail.721 clears732/738/736 after zero-motion.731/733 clear
  730/73C/732 before their zero tail.797 clears730 and dispatches wave5;
  798 dispatches wave5, zeroes motion, sets horizontal speed15, short730=0,
  vertical speed0 and gravity0.5. All other actions reach the common default.

Field widths and call/publication epochs are target observations. Original
nominal field spelling, complete owner layout and original TU remain unknown.
There is no general standalone-object or LTCG impossibility claim.

## Whole-function experiments and negative

Private source controls are under
`.analysis/exact-first-marisa-action-entry-20261025/`; reports and objects are
under `build/exact-first-marisa-action-entry-20261025/`.

| Complete source/control | Full bytes | SHA256 prefix | Whole result |
| --- | ---: | --- | --- |
| First complete source |2818|c0556716|nonexact+15;35/38 RETs, extra shared FP tails|
| Common-body products before short clears |2974|d66ab0a0|restores special FP copies;36/38 RETs|
| Common scalar publications before both products |3034|fc45aff8|all entries/38 RETs restored;12 differing bytes|
| 542/547 publish184 before clearing180/750 |3034|e1e4844c|8 differences, only17C/184 store ordering|
| Both constant publications precede those clears |3034|fc233d82|exact, zero unmasked differences|

The first complete comparison immediately retains both table dimensions/all363
remap bytes and every physical direct-call/tail count. Its missing three RETs
come from shared floating-point suffixes at414/422/432. Changing the common
publication/product epoch retains their independent target copies; a further
common suffix join at410 disappears naturally as well. The final controls are
restricted to the two actual no-call scalar publication arms exposed by the
full byte difference. No compiler-profile grid, assembly, inert storage,
forced return, padding or runtime behavior matrix is used.

A generated-object negative changes only the final remap byte at4B9599 from
valid index30 to valid index0. Inventory still parses, but the full comparator
rejects precisely that byte at+3033; negative SHA256
`8c50db6a4c0c8394eeb359323384207278ce72687758f58622d889ce72281426`.
The canonical executable and accepted object are untouched. Five public
synthetic fixtures exercise both real EAX/ECX-indexed ranges, invalid final
indices, metadata destinations, truncated remaps and an unreviewed external tail.

## Reproduction and handoff

Use locked repository Python, serial CPU0/nice10 jobs:

```sh
taskset -c 0 nice -n 10 scripts/repo-python scripts/build.py --unit exact-first-marisa-action-initialization --compare --json
taskset -c 0 nice -n 10 scripts/repo-python scripts/audit-marisa-action-initialization.py
TH105_ENABLE_GS=0 TH105_FP_MODE=default TH105_INLINE_MODE=default \
  taskset -c 0 nice -n 10 scripts/compile-unit.sh src/characters/MarisaActionInitialization.cpp build/marisa-entry-cold.obj
taskset -c 0 nice -n 10 scripts/repo-python scripts/audit-marisa-action-initialization.py --object build/marisa-entry-cold.obj
```

Only new local source/interface/unit and12 exclusive literal aliases are added;
prior accepted sources, shared headers, compiler settings and bindings are
unchanged. Formal and independent cold callable/full results agree. Complete
serial cold replay passes all519 accepted units/1407 functions. Receipt:
`build/exact-first-marisa-action-entry-20261025/cold-all.log`. The current exact
ledger records371226 callable authored bytes; metadata/alignment receive no
extra callable credit. Source-present1551, mapped1570 and590 configured units
are independently ledger-validated.

Next independently review Sakuya primary slot+3C4DE060, candidate2106 bytes,
still authored and source-missing. Re-attest its boundary/ABI and every changed
action before reuse. Marisa's earlier nonexact CPU/input/control-mode roots
remain separate; do not reopen their neutral controls without new evidence.
