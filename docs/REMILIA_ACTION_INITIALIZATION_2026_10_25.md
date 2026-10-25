# Remilia action initialization: 2026-10-25

`Remilia_initialize_action_entry @ 0x00554D50` is canonical exact:1802 callable
bytes and the complete2344-byte emitted payload. Formal and independent cold
ordinary VC8 builds reproduce SHA256
`38cb9b4ada942934d9d3dd9fe3ee94a6d62d71a65db8c21c86e38b7f57283903`.
All92 section relocations are replayed without masking code or metadata.

## Observed target, boundary and ABI

The executable is Japanese1.06a, SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
IDA preflight rejects the GUI's different executable. No IDA analysis read/write,
Ghidra process or decompiler is used. All426 main instructions were read from
the hash-attested PE and their direct/switch control-flow edges reconciled.

Main `[554D50,55545A)` has1802 bytes and SHA256
`4c0eaa105dff592184522c787404bcec404d62aefa59c95693c8a67bb5cbc10f`.
Raw CFG reaches every main instruction/byte and closes33 RET0s. It contains21
direct zero-motion45AF40 calls, five45AF40 tails, the477830 default tail and
one indirect call555122 through virtual slot0C. There is no scratch-reset,
event, wave or spawn call. EBX/ESI are saved and ECX is retained in ESI; no
local, GS or EH frame is present. Action13C is read with MOVSX word. The high
switch uses ECX as index, requiring receiver restoration on its helper paths.

Existing RTTI-backed roster evidence and raw cell6C5400 bind primary slot+3C
of Remilia vtable6C53C4 to554D50. Authored ownership is unchanged. Complete
`[554D50,555678)` owns:

| Destination table | DWORDs | Input range | Remap start / bytes |
| --- | ---: | --- | --- |
| 55545C |20|300..418|5554AC /119|
| 555524 |26|505..740|55558C /236|

All46 destination words/184 bytes and355 remap bytes participate. Alignment is
two-byte MOV EDI,EDI after the main and one NOP after the low remap. These three
bytes receive no extra callable credit. Eight INT3 bytes separate the final
remap from the independently accepted handle-manager destructor555680. Direct
branches handle4/5/214,500/501 and797/798; no neighboring function is included.

The actual Remilia slot0C cell6C53D0 points to45C390. Its complete202-byte
provider reads a four-byte stack argument at45C3E8 but consumes the sequence
through AX: word tests,13E word stores and a decrement/word-test loop, ending
RET4. The source uses a pointer-only virtual call view with a `short` sequence
parameter. This expresses the observed low-word argument contract in a
four-byte stack slot; it does not recover the original nominal parameter type
or change the separately accepted provider's `int` declaration. The505/506
local is consumed by the virtual call and stays in registers. MOVZX730, the
early vptr/slot read, PUSH EAX, scalar stores and CALL EDX all agree. Never
instantiate/embed this partial receiver as a complete Fighter allocation.

## Independently reviewed behavior

Instructions, access widths, skipped writes and publication order are observed.
Numeric actions, typed offsets and opaque calls are retained. Original names,
complete nominal class layouts and original translation-unit ownership remain
unknown; canonical equality does not resolve those questions.

- 4/5 set horizontal speed+6.5/-6.5.214 clears736 and both velocities, sets
  gravity0.6,108=0,10C=75,73C=25 and74C=0, without a scratch-reset call.
  300/301/303/322 conditionally zero motion when47E is zero, clear180 and set
  184=1.302 also clears47E and sets750=1.304 publishes47E=0/184=1/180=0
  before zero-motion and sets750=1 afterward.320 only clears47E/180 and sets
  184=1.321 uses the conditional zero path but sets184=2.
- 305 clears vertical speed/gravity, sets horizontal speed17.5, clears47E/180
  and sets184=1.306/325 clear730/180 and set184=1.307 zeroes motion before
  setting184=1/180=0/750=1;308/309 enter after the call.613 skips the184
  publication too, clearing180 and setting750 only.310 clears horizontal
  speed/730/180, sets184=99, then enters the797/798 vertical-speed/gravity
  suffix with a live x87 zero.418 sets horizontal speed17.5 before the300
  family's conditional zero call and scalar suffix.
- 400/401/402/410/411 clear180 before zero-motion and set750=1, without
  short clears.404/406 clear180/gravity, set750=1 and scale both velocities
  by float0.2.408 sets horizontal speed17.5/vertical speed0, clears47E/730/
  180 and sets184=1.409 clears47E, sets gravity0.35, clears730/180 and sets
  184=1 while preserving velocities.
- 412 clears180 before zero-motion, then clears730/732/736/738, preserving
  750.414 independently clears gravity/180, scales horizontal speed across
  its730/732/736/738 publications, sets750=1 and scales vertical speed.
  415 enters after567's17C=7 store: clear180/730/732/736, then enter404 at
  554F63 after its180 clear. It preserves17C/738.416 only sets750=1/180=0.
- 500/501 use17C=0, zero motion, clear180/47E and set184=1.505/506 use17C=4,
  zero motion, read the730 word, clear180/47E, set184=1 and invoke slot0C
  with that sequence, preserving730/750.520/521 publish17C=1/750=1 before
  zero-motion, then set180=1/47E=0.525/526 use17C=5 and share that suffix.
  530/531 use17C=9, zero motion, then184=0/47E=0/180=1/750=1.
- 540/541 publish730=0/184=4/17C=2/180=0 before zero-motion, then750=1.
  542/547 have no zero call:180=0/750=0/17C=2/184=1.545/546 use17C=6/
  180=0 before zero-motion, then clear730/732/736/738/750.560/561 publish
  17C=3/184=1/180=0 before zero-motion, then clear730/732/736 and set750=1.
  565/566 publish17C=7/180=0 before zero-motion, then184=1/750=1 without
  short clears.567 sets17C=7 before415's actual body.
- 599 sets180=1 before zero-motion, then shares412's four-short clear suffix
  and preserves750.600 sets73C=240/180=1 and tail-calls zero-motion;601/604
  skip the73C store and707 skips180 as well.602/605 clear730/732/180, set
  184=20 and tail-call zero-motion.603 sets180=1/73C=320 then zeroes motion.
  606 clears730/732/180, sets184=1 and zeroes motion.607/710/711 set180=1,
  zero motion, then clear73C/744.608/610/611 clear730/732, set180=1 and
  tail-call zero-motion.612/615 set180=1 before zero-motion, then clear
  730/732/736/738 and set750=1.
- 708 clears horizontal speed then enters709's730 clear;709 only clears730.
  720/721 set180=0/184=1 before zero-motion, then clear730.730/731/740 use
  184=0 and clear730/732 afterward.797/798 independently zero motion, set
  horizontal speed12/vertical speed0/gravity0.5 and clear730. Neither has an
  event or wave helper. Other actions delegate to the common initializer.

Float0.2 products use the emitted qword extension of float0.2, not decimal
double0.2. Every operand has a target-observed width/bit binding. Each shared
suffix and skipped write was reviewed for this peer independently.

## Whole-function experiments and negative control

Private inputs are retained in `.analysis/exact-first-remilia-action-entry-20261025/`;
reports/objects are under `build/exact-first-remilia-action-entry-20261025/`.
Every row compares the complete emitted symbol with all relocations replayed.

| Complete source/control | Full bytes | SHA256 prefix | Whole result |
| --- | ---: | --- | --- |
| First complete source |2344|091fffb4|12 differing bytes; all metadata/call counts/33 RETs agree|
| 500/501 scalar publication order |2344|4db88a6e|6 differing bytes remain in542/547|
| 542/547 scalar publication order |2344|38cb9b4a|complete payload exact|

The first complete source already preserves the505/506 virtual sequence path.
Two targeted publication-order controls account for all12 residual bytes.
No compiler flag grid, assembly, copied target arrays, inert locals, fake
returns, ABI lies, padding, repeated neutral controls or runtime matrix is used.

A generated-COFF-only negative changes the final remap byte555677 from valid
index24 to valid index0. Parsing still succeeds, but complete comparison rejects
exactly+2343 with one differing byte; full SHA256
`a4c8e8746605a1738bd1684266a284719adbe88b8fa42cf5978159bdab8b01bd`.
Neither the canonical PE nor the accepted object is modified. Five synthetic
fixtures check both remapped tables, invalid final indices, metadata destinations,
truncated remaps and an unreviewed external CFG tail.

## Reproduction and next scope

Use locked repository Python and serial CPU0/nice10 jobs:

```sh
taskset -c 0 nice -n 10 scripts/repo-python scripts/build.py --unit exact-first-remilia-action-initialization --compare --json
taskset -c 0 nice -n 10 scripts/repo-python scripts/audit-remilia-action-initialization.py
TH105_ENABLE_GS=0 TH105_FP_MODE=default TH105_INLINE_MODE=default \
  taskset -c 0 nice -n 10 scripts/compile-unit.sh src/characters/RemiliaActionInitialization.cpp build/remilia-entry-cold.obj
taskset -c 0 nice -n 10 scripts/repo-python scripts/audit-remilia-action-initialization.py --object build/remilia-entry-cold.obj
```

Only local source/interface/unit and12 exclusive literal aliases are added.
Prior accepted sources, shared headers, compiler settings and bindings remain
unchanged. Formal and independent cold callable/full results agree. Complete
serial cold replay passes all524 accepted units/1412 functions. Receipt:
`build/exact-first-remilia-action-entry-20261025/cold-all.log`. The full2344-byte
audit also passes on the object rebuilt during that replay. The exact ledger
records381108 callable authored bytes; metadata/alignment receive no extra
callable credit. Source-present1557, mapped1576 and596 configured units are
independently ledger-validated. Provenance census/readback and1394 floating
target-reference checks pass.

Next independently review Youmu Fighter primary slot+3C53A1D0, candidate1424
bytes, after re-attesting its slot/boundary/ABI and every changed action. This is
a distinct owner from the parked YoumuObject initializer543670. Keep parked
Komachi/common/Reimu/Udonge residuals closed absent new independent evidence.
