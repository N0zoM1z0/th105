# Iku action initialization: 2026-10-25

`Iku_initialize_action_entry @ 0x0062FFF0` is canonical exact:1842 callable
bytes and the complete2380-byte emitted payload. Formal and independent cold
ordinary VC8 builds reproduce SHA256
`ea5aebaff6315bea69cdd8d450ebae711e21029a181bc0d6ec4af31137c7f1e4`.
All92 section relocations are replayed without masking code or metadata.

## Observed target, boundary and ABI

The executable is Japanese1.06a, SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
IDA preflight rejects the GUI's different executable. No IDA analysis read/write,
Ghidra process or decompiler is used. All436 main instructions were read from
the hash-attested PE; every direct/switch CFG edge was reconciled.

Main `[62FFF0,630722)` has1842 bytes and SHA256
`d873d944e39c760cdd14f6d2b86adba56b9700519274fff9af74e759831cfcac`.
Raw CFG reaches every main instruction/byte and closes36 RET0s. There are21
direct zero-motion45AF40 calls, two45AF40 tails, one435110 scratch reset and
the477830 default tail. No event, wave, spawn or indirect call is present.
EBX/ESI are saved and ECX is retained in ESI. No local, GS or EH frame is
present. Pointer-only receiver/scratch views must never be instantiated or
embedded as recovered full owners.

Existing RTTI-backed roster evidence and raw cell6C6568 bind primary slot+3C
of Iku vtable6C652C to62FFF0. Authored ownership is unchanged. Action13C is read
with MOVSX word. The high switch indexes through ECX, requiring receiver
restoration on its helper paths. Direct780 enters after the restoration prefix;
603 enters after608's short clears;740 enters after599's180 store. Those
interior entries preserve the skipped fields.

Complete `[62FFF0,63093C)` owns:

| Destination table | DWORDs | Input range | Remap start / bytes |
| --- | ---: | --- | --- |
| 630724 |21|300..418|630778 /119|
| 6307F0 |23|501..740|63084C /240|

All44 destination words/176 bytes and359 remap bytes participate. Alignment is
two-byte MOV EDI,EDI after the main and one NOP after the low remap. These three
bytes receive no extra callable credit. Four INT3 bytes separate the final
remap from the independently accepted handle-manager destructor630940. Actions
4/5/214,500,780/781 and797/798 use direct branches. No neighboring function
bytes are included in the comparison.

The accepted435110 scratch reset consumes ECX=this+4 and returns RET0. Ordinary
declaration-only members retain the established helper cleanup and receiver ABI;
no substituted helpers or new callee acceptance credit are claimed.

## Independently reviewed behavior

Instructions, access widths, edges and physical publication epochs are target
observations. Source retains numeric states, typed offsets and opaque calls.
Original nominal source names, complete class layouts and original TU remain
unknown; a matching receiver view does not recover a complete allocation.

- 4/5 set horizontal speed+6/-5.214 calls the scratch reset onthis+4, clears
  both velocities and736, sets gravity0.6,108=0,10C=95,73C=10 and74C=0.
  300/301/303/321/322 conditionally zero motion when47E is zero, clear180
  and set184=1.302 additionally clears47E and sets750=1.304 publishes47E=0/
  184=1/180=0 before zero-motion, then sets750=1.320 only clears47E/180 and
  sets184=1, without a zero-motion call.
- 305 clears vertical speed/gravity, sets horizontal speed8.5, clears47E/180
  and sets184=1.306 clears180 before730 and sets184=1.307/308 set184=1,
  180=0 and750=1;309 uses184=4.613 enters after307's184 write, preserving184.
  310 clears horizontal speed/180/vertical speed/730, sets184=99/gravity0.5.
- 400/401/402 clear180 before zero-motion and set750=1 without short clears.
  404/406 clear180/gravity, set750=1 and scale both velocities by float0.2,
  without a zero-motion call.408 sets horizontal speed12.5/vertical speed0,
  clears47E/180/730 and sets184=1.409 sets gravity0.35 before408's actual
  scalar suffix, preserving velocities.
- 410 clears180 before zero-motion, then clears736/738/732/730 and sets750=1.
  411 preserves738.412 clears the same four shorts as410 but preserves750.
  414 independently clears gravity/180, scales horizontal speed across its
  736/738/732/730 publications, sets750=1 and scales vertical speed.
- 415 first clears736, clears gravity, performs float0.2 velocity products,
  clears180/732/730 and sets750=1.416/417 publish gravity0 before736, use
  float0.15 products and share415's multiply/publication suffix.567/568 set
  17C=7 and clear734, then enter415 at63035A *after* its736 clear. They must
  preserve736 while retaining the shared gravity/product/publication suffix.
  None of these paths may acquire414's738 clear.418 sets horizontal speed
  10.5/184=1/180=0 without zero-motion.
- 500/501 use17C=0, zero motion, clear180/47E/730 and set184=4/6 respectively.
  505/506 use17C=4, zero motion,184=0/47E=0/730=0/180=1/750=1.520/521
  use17C=1, zero motion,180=0/47E=0/730=0/184=1.525/526 use17C=5 and
  clear184/180/47E/730 after zero-motion.
- 540/541 publish17C=2/180=0 before zero-motion, then clear750.545/546 use
  17C=6/180=0 before the actual zero-motion tail and preserve750.547 has no
  zero call:180=0/750=0/17C=2/184=1.560/561/562/563 use17C=3/180=0 before
  zero-motion and set750=1;570/571/572/573 use17C=11.565/566 use17C=7,
  clear180 before zero-motion, then clear734/732/730 and set750=1.
- 599 sets180=1 before zero-motion and clears736/738/732/730.740 skips that
  180 store and enters599's actual call, preserving180.600/602/606/650/710/
  720 clear180 before zero-motion, with no short/flag writes.601 zeroes motion,
  clears180/47E/730 and sets184=99.603 only sets180=1 before zero-motion,
  skipping608's730/732 clears.605 clears730/180 and publishes184=6 before
  zero-motion, then clears732/734.607 zeroes motion and clears47E/730.
- 608/609/610/611/660 clear730/732, set180=1 and tail-call zero-motion.
  612/615 set180=1 before zero-motion, clear736/738/732/730 and set750=1.
  730 clears180 before zero-motion and clears734 afterward.780 directly enters
  the zero-motion tail, without545's17C/180 writes.781 sets73C=13, clears
  732/730 and sets740=200, with no helper call.
- 797/798 set horizontal speed10, vertical speed-5 and gravity float-0.12.
  They do not zero motion, clear730 or dispatch an event/wave. Other actions
  delegate to the common initializer.

Float0.2 and float0.15 products use their compiler-emitted qword extensions,
not decimal double0.2/0.15. Every operand has a target-observed width/bit binding.
Physical sharing and skipped writes are checked independently for this peer.
There is no new runtime matrix or standalone-object/LTCG impossibility claim.

## Whole-function experiments and negative control

Private inputs are retained in `.analysis/exact-first-iku-action-entry-20261025/`;
reports/objects are under `build/exact-first-iku-action-entry-20261025/`.
Every row compares the complete emitted symbol with all relocations replayed.

| Complete source/control | Full bytes | SHA256 prefix | Whole result |
| --- | ---: | --- | --- |
| First complete source |2276|a0c51253|34/36 RETs;414/415 overmerged;520 enters408's scalar suffix|
| Early750 phase in415/416/567 |2352|19f37fb9|independent414 restored;35 RETs;one scalar-copy discrepancy remains|
| Early184 phase in408/409 |2380|ea5aebaf|36 RETs;520 copy and47E/180 ordering restored;full exact|

No compiler flag grid, assembly, copied target arrays, inert locals, fake
returns, ABI lies or padding is used. The first complete body already preserves
both remaps, all direct-call/tail counts and all target-specific actions. Two
evidence-backed publication controls recover complete physical sharing. There
are no repeated neutral controls or behavior matrices.

A generated-COFF-only negative changes the final remap byte63093B from valid
index21 to valid index0. Parsing still succeeds, but complete comparison rejects
exactly+2379 with one differing byte; full SHA256
`5a725415589546057966b6a86b7a91d612051c2c3547c672947be637e590749c`.
Neither the canonical PE nor the accepted object is modified. Five synthetic
fixtures cover both EAX/ECX tables, invalid final indices, metadata destinations,
truncated remaps and an unreviewed external CFG tail.

## Reproduction and next scope

Use locked repository Python and serial CPU0/nice10 jobs:

```sh
taskset -c 0 nice -n 10 scripts/repo-python scripts/build.py --unit exact-first-iku-action-initialization --compare --json
taskset -c 0 nice -n 10 scripts/repo-python scripts/audit-iku-action-initialization.py
TH105_ENABLE_GS=0 TH105_FP_MODE=default TH105_INLINE_MODE=default \
  taskset -c 0 nice -n 10 scripts/compile-unit.sh src/characters/IkuActionInitialization.cpp build/iku-entry-cold.obj
taskset -c 0 nice -n 10 scripts/repo-python scripts/audit-iku-action-initialization.py --object build/iku-entry-cold.obj
```

Only new local source/interface/unit and15 exclusive literal aliases are added.
Prior accepted sources, shared headers, compiler settings and bindings remain
unchanged. Formal and independent cold callable/full results agree. Complete
serial cold replay passes all523 accepted units/1411 functions. Receipt:
`build/exact-first-iku-action-entry-20261025/cold-all.log`. The full2380-byte
audit also passes on the object rebuilt during that replay. The exact ledger
records379306 callable authored bytes; metadata/alignment receive no extra
callable credit. Source-present1556, mapped1575 and595 configured units are
independently ledger-validated.

Next independently review Remilia primary slot+3C554D50, candidate1802 bytes and
cell6C5400, currently authored and source-missing. Re-attest its boundary/ABI
and every changed action before reuse. Keep the parked Komachi/common/Reimu/
Udonge residuals closed absent new independent evidence.
