# Sakuya action initialization: 2026-10-25

`Sakuya_initialize_action_entry @ 0x004DE060` is canonical exact: 2106 callable
bytes and the entire 2656-byte emitted payload. Formal and independent cold
ordinary VC8 builds reproduce SHA256
`9a6c54b1b3b06de9094a73416afc795c479e9ee2cf6da969244a00726378f870`.
All 99 section relocations are replayed without masking code or metadata.

## Observed target, boundary and ABI

The executable is Japanese 1.06a, SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
IDA preflight rejects the GUI's different executable. No IDA analysis read/write,
Ghidra process or decompiler is used. All 486 main instructions were read from
the hash-attested PE and all direct/switch CFG edges were reconciled. Initial
source remains a hypothesis until comparison: the first implementation's extra
562 short734 clear is specifically rejected below.

Main `[4DE060,4DE89A)` is 2106 bytes, SHA256
`67a0991a385a5c26e7bc8408bc1df8c60a07a59c047d20d1a40a975478c39aa0`.
Raw CFG reaches every main instruction/all2106 bytes and closes32 RET0s. There
are21 direct zero-motion45AF40 calls, two45AF40 tails and the477830 default
tail. No scratch reset, wave, spawn, face or landing-predicate call is present.
The root saves EBX/ESI, moves its ECX receiver into ESI and allocates no local
frame. No EH/GS frame is present. The pointer-only virtual receiver is never
instantiated or embedded as a recovered full Fighter.

Existing RTTI-backed roster evidence and raw cell6C4950 bind primary slot+3C
of Sakuya vtable6C4914 to4DE060. Authored ownership is unchanged. The high
switch indexes through ECX, so its helper paths restore the receiver. The
411 low-table entry skips the real MOV ECX,ESI prefix at4DE363, while high
560/565 entries use that prefix. Ordinary member calls retain both entries.

Complete `[4DE060,4DEAC0)` owns the following metadata:

| Destination table | DWORDs | Input range | Remap start / bytes |
| --- | ---: | --- | --- |
| 4DE89C |20|300..418|4DE8EC /119|
| 4DE964 |27|501..740|4DE9D0 /240|

All47 destination words/188 bytes and359 remap bytes participate. Alignment is
two bytes `8BFF` after the main and one `90` after the first remap. These three
bytes receive no extra callable credit. The final remap ends exactly at the
already independently accepted SakuyaObject handle-manager destructor4DEAC0;
there is no assumed padding gap.4/5/214,500 and797/798 use direct branches.

## Independently reviewed behavior

Complete source retains numeric states, typed offsets and real opaque calls.
Same-family reuse preserves these target-specific differences:

- 4/5 use +/-6.214 clears736 and both velocities, sets gravity0.6,108=0,
  10C=75,73C=10.5 and74C=0, without a scratch-reset call.
- 300/301/303/321/322 conditionally zero motion, clear180 and publish184=1,
  preserving750.302 zeroes unconditionally, clears47E and sets750;304 publishes
  184=2 before zero-motion.305 first clears vertical speed, applies the ordered
  lower clamp described below, clears gravity/47E/180 and publishes184=1.
- 307/309 publish184/180/750 without zero-motion.308 additionally scales both
  velocities by float0.2 and clears gravity before entering their suffix.310
  clears velocities/730/180, sets184=99 and gravity0.5.320 only clears47E/180
  and publishes184=1.418 applies the same lower clamp before the300-family path.
- 305/418 compare horizontal speed against *double*12.5 and only when strictly
  less store *float*12.5. The actual FCOMP qword/TEST AH,5/JP leaves unordered
  values unchanged. This is a lower clamp, not an upper bound. Distinct dword
  and qword literal bindings preserve both observed widths.
- 400/401/402 clear730/732/734 after zero-motion and set750.404/405/406 clear
  734 before the shared floating suffix, clear732/730/180, set750 and scale
  velocities with zero gravity.562 instead publishes17C=3, clears736 and enters
  that suffix *after* the734 write:734 must be preserved.411,560/561 and565/566
  use the separate736/732/730 zero-motion suffix, with17C=3/7 for the high arms.
- 408 uses horizontal speed12.5, vertical speed0 and184=3.409 uses gravity0.35.
  410 clears73C plus730/732/734 after zero-motion and sets750.412 clears four
  shorts and does not add a750 write.414 clears73C/180/gravity, scales velocity
  across730/732/734 publications and sets750.415/416 preserve73C but retain an
  independent complete floating body. Neither body may be folded into another
  clear-only tail for exact acceptance.
- 500/501 use17C=0, actual zero-motion,184=4/5 and clear180/47E/730.502/503
  perform double0.25 velocity scaling without zero-motion, then retain those
  respective184=4/5 suffixes.504 sets both velocities10, gravity0.55 and180=1.
  505/506 use17C=4, clear184/47E and set180=1 without adding730/750 writes.
- 520/521 and525/526 use17C=1/5, zero motion, clear73C/47E/730/732 and set
  180=1/750=1 while preserving184.540/541 and545/546 use17C=2/6, clear180
  before zero-motion, then clear730/732/736/738/750.542/543 perform zero-gravity
  scaling with those clears and17C=2 without a zero call.547/548 use17C=6 and
  their own publication/product epoch before entering the actual540 clear suffix.
- 599 sets180=1 before zero-motion and clears four shorts;600 only sets180=1
  and zeroes motion.601/602/605/607 clear730/732, set180=0 and zero motion.
  603/604/608/609/610/611/720 use180=1 instead.707 enters after those field
  publications and therefore only zeros motion.606/656/710/711 zero motion
  and clear47E, without adding other stores.
- 612/615 set180=1 before zero-motion, clear738 and enter the exact411 suffix
  at its736 write; the750/short publication phase must preserve this sharing.
  613 only clears180 and sets750.708 clears730/horizontal speed without calling
  zero-motion.721 clears740/730 before zero-motion, then clears47E.722/730
  clear180 before zero-motion and clear730/732/736 afterward.740 also clears73C.
  797 zeros motion then sets horizontal speed12,730=0, vertical speed0 and
  gravity0.5;798 only zeroes motion and clears730. Other actions use the default.

Widths, edges and physical call/publication epochs are target observations.
Original nominal names, complete owner layout and original TU remain unknown.
No standalone-object/LTCG impossibility or broader runtime contract is claimed.

## Whole-function experiments

Private inputs are retained in `.analysis/exact-first-sakuya-action-entry-20261025/`;
reports/objects are under `build/exact-first-sakuya-action-entry-20261025/`.
Every experiment compares the entire emitted symbol, not an isolated first diff.

| Complete source/control | Full bytes | SHA256 prefix | Whole result |
| --- | ---: | --- | --- |
| First complete source |2392|9cc69580|26/32 RETs; extra shared suffixes|
| 415/416 both products before short clears |2572|1dc30af6|28 RETs; restores414/542 bodies|
| 415/416 short publications before products |2424|cc991523|regresses first table20 to19; rejected|
| Common404/562 publications before products |2648|567ff0a5|wrong562 physical copy; rejected|
| Chained400 short stores, restored2572 baseline |2572|1dc30af6|whole-payload neutral|
| 400 publishes750 before its short clears |2636|9915c1f3|30 RETs, extra zero call22/21|
| Same early750 phase for411/560/565 |2616|247bdce6|restores21 zero calls/shared411 owner|
| Early750 publication in415/416 |2636|91a500a3|31 RETs;520 body restored|
| 415/416 vertical product after short clears |2664|99a23f0e|all32 RETs;612 has extra seven-byte clear|
| 612/615 uses the shared early750 phase |2656|174459b0|all dimensions/counts agree;46 differing bytes|
| Remove incorrect562 short734 clear |2656|9a6c54b1|exact; zero unmasked differences|

Rejected controls are retained rather than selected by byte length alone. The
neutral chain control is recorded once; later controls address new observed
owner/epoch differences. No flag grid, assembly, byte arrays, inert locals,
forced returns or padding is used. No behavior matrix is needed.

The last46 differences are particularly useful: all lie in404's instruction
schedule and562's jump displacement. The old source enters before the734 clear;
the target enters after it at4DE289. Removing the extra562 store simultaneously
restores that entry and the404 schedule. The ordinary final source replays both
callable and complete payloads exactly. The retained old-source object is still
rejected by the public full auditor at+546, SHA256
`174459b07348eb61d7cccdb6ba201ede7fef24a711c9cdf6098f45d598316c89`.
This is instruction evidence; no native execution or substituted helper output
is claimed.

A second negative changes only the final generated-object remap byte4DEABF
from valid index25 to valid index0. Parsing still succeeds, but full comparison
rejects exactly+2655; SHA256
`824f6fb52a6fe9be05505d2e2394d39c119675b33cba2afc54ca2ed447448981`.
The canonical executable and accepted object are untouched. Five public
synthetic fixtures exercise both EAX/ECX ranges, invalid last indices, metadata
destinations, remap truncation and an unreviewed external tail.

## Reproduction and next scope

Use locked repository Python and serial CPU0/nice10 jobs:

```sh
taskset -c 0 nice -n 10 scripts/repo-python scripts/build.py --unit exact-first-sakuya-action-initialization --compare --json
taskset -c 0 nice -n 10 scripts/repo-python scripts/audit-sakuya-action-initialization.py
TH105_ENABLE_GS=0 TH105_FP_MODE=default TH105_INLINE_MODE=default \
  taskset -c 0 nice -n 10 scripts/compile-unit.sh src/characters/SakuyaActionInitialization.cpp build/sakuya-entry-cold.obj
taskset -c 0 nice -n 10 scripts/repo-python scripts/audit-sakuya-action-initialization.py --object build/sakuya-entry-cold.obj
```

Only new local source/interface/unit and14 exclusive literal aliases are added.
Prior accepted sources, shared headers, compiler settings and bindings are
unchanged. Formal and independent cold callable/full results agree. Complete
serial cold replay passes all520 accepted units/1408 functions. Receipt:
`build/exact-first-sakuya-action-entry-20261025/cold-all.log`. The current exact
ledger records373332 callable authored bytes; metadata/alignment receive no
extra callable credit. Source-present1552, mapped1571 and591 configured units
are independently ledger-validated.

Next independently review Yuyuko primary slot+3C56C840, candidate2083 bytes,
still authored and source-missing. Re-attest its boundary/ABI and every changed
action before reuse. Parked roots remain separate; do not reopen their neutral
controls without new evidence.
