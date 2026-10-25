# Aya action initialization: 2026-10-25

`Aya_initialize_action_entry @ 0x00617000` is canonical exact: 2049 callable
bytes and the complete 2579-byte emitted payload. Formal and independent cold
ordinary VC8 builds reproduce SHA256
`66057eaf0ac9f68aaf0e5f776e9cbc7b48197511501cbd4ce7f782ab81079623`.
All 92 section relocations are replayed without masking code or metadata.

## Observed target, boundary and ABI

The executable is Japanese 1.06a, SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
IDA preflight rejects the GUI's different executable. No IDA analysis read/write,
Ghidra process or decompiler is used. All 500 main instructions were read from
the hash-attested PE and every direct/switch CFG edge was reconciled.

Main `[617000,617801)` has SHA256
`7cf270d861915eb09dddb400a934ae9e1e8f4ce25333770f5eb2b6e6c654d4b4`.
Raw CFG reaches every main byte and closes 26 RET0s. There are 14 direct
zero-motion45AF40 calls, five45AF40 tails, two45C030 wave calls, one435110
scratch reset, one4351C0 frame call, one indirect virtual call and the477830
default tail. The prologue PUSH ECX allocates four used bytes for408's actual
float rounding; EBX/ESI are saved and ECX is retained in ESI. No EH/GS frame is
present. Pointer-only receiver/scratch views must never be instantiated or
embedded as recovered full owners.

Existing RTTI-backed roster evidence and raw cell6C6310 bind primary slot+3C
of Aya vtable6C62D4 to617000. Authored ownership is unchanged. Action13C is read
with MOVSX word. Access widths and call cleanup remain target observations.
The high switch indexes through ECX, so its ordinary member paths restore the
receiver while low402 enters after that restoration prefix.

Complete `[617000,617A13)` owns the following metadata:

| Destination table | DWORDs | Input range | Remap start / bytes |
| --- | ---: | --- | --- |
| 617804 |20|300..418|617854 /119|
| 6178CC |22|502..740|617924 /239|

All 42 destination words/168 bytes and 358 remap bytes participate. Alignment
is the three-byte LEA at617801 and one NOP at6178CB. Those four bytes receive
no additional callable credit. Thirteen INT3 bytes after the final remap separate
it from the independently accepted handle-manager destructor617A20. Actions
4/5/214,500,791 and797/798 use direct branches. No neighboring function bytes
are included in the complete comparison.

The accepted435110 provider consumes ECX=this+4 and returns RET0. The accepted
4351C0 provider returns a byte;408 consumes AL. Aya's actual primary slot+8
points to45BFE0, the independently accepted `int(short)` action/finalization
wrapper with RET4. The root pushes action0 before that virtual call. The actual
45C030 provider consumes a dword selector and has RET4 cleanup. These are real
typed declarations; no substituted helpers or new callee credit are claimed.

## Independently reviewed behavior

Source keeps numeric actions, typed offsets and opaque calls. Target instructions,
field widths, edges and physical publication epochs are observations. Original
nominal source names, complete owner layouts and original TU identity are unknown.

- 4/5 set horizontal speed+/-5.5.214 calls the scratch reset onthis+4, clears
  horizontal/vertical speed and736, sets gravity0.6,108=0,10C=95,73C=12 and
  74C=0.300/301/303/320/321 conditionally zero motion when47E is zero, then
  clear180 and set184=1.302 additionally clears47E/horizontal speed and sets
  750=1;322 has those clears without writing750.304 clears47E and publishes
  184=1/180=0 before zero-motion, then sets750=1.
- 305 sets vertical speed0, horizontal speed17.5, gravity0,47E/180=0 and184=1.
  306 clears730/180 and sets184=1.307 clears both velocities/730/180/gravity,
  sets184=1 and73C=25.308 only sets184=1/180=0 and clears both velocities;
  its table entry skips545's17C=6 prefix.309 only sets184=1/180=0 and skips
  554's17C=10 prefix.310 clears velocities/730/180 and sets184=99/gravity0.5.
- 400/401/410/412 clear180 before zero-motion, then clear730/732/736 and set
  750=1.402 clears180 before zero-motion, then clears732/736/730/738 without
  writing750.404/406 scale both velocities by double0.25, clear180, set gravity
  0.5 and enter400's actual post-call short/750 suffix.414/416 publish gravity
  0.5 before those products.415 instead enters411's suffix, which clears750.
- 408's first-use gate requires144 dword,142 word,140 word and13E word all
  zero. Only then it sets horizontal speed17.5, clears47E/730/vertical speed/
  180 and sets184=1. Every entry then subtracts double0.5 from horizontal speed,
  rounds to an actual float local, publishes the result and clamps it to0 only
  when ordered below zero. FSTP/FLD atESP+8 are real rounding operations; the
  local value is used in the comparison. The FNSTSW/TEST AH,5/JP path preserves
  unordered inputs instead of treating them as negative.
- 408 next calls4351C0 and invokes primary slot+8 with short action0 if AL is
  nonzero. It then rereads142/140; only142=0 and140=6 dispatch wave27. Reads
  remain after the possibly mutating frame/virtual calls. The first complete
  source already reproduces this entire path, including the four-byte frame,
  input gate, rounded decrement, virtual call and final wave guard.
- 409 clears47E/730/180, sets gravity0.35 and184=1.411 clears180 before
  zero-motion, then clears730/732/736/750.418 clears vertical speed/gravity,
  sets73C=25 and enters305's real47E/180/184 suffix without writing horizontal
  speed. Its scalar publication phase must preserve that physical sharing.
- 500 and502 independently set17C=0 and enter402's180/zero/short suffix.
  505/506 use17C=4;510 uses17C=8.507/508 use17C=4,180=0 and double0.25
  velocity products without a zero-motion call, then enter402's short suffix.
- 520/521/522/523 use17C=1, zero motion, clear180/47E/730 and set184=1.
  612/662 enter after the17C store and therefore preserve17C.525/526/527/528
  use17C=255 and additionally clear738.529 uses17C=255, zero-motion and the
  180/47E/184 publications while preserving730/738.530/531/532/533 instead
  use17C=9, zero-motion,180=1 and47E=0, preserving184/short fields.
- 540 sets17C=2 and603 skips that store. Their shared body clears180 before
  zero-motion, clears gravity/730/732/736/738 and scales both velocities by
  double0.25.545 sets17C=6 then shares308's velocity/184/180 body.546 clears
  both velocities/184/180 and sets17C=6 without calling zero-motion.
- 550/551/552/553 set17C=10, clear730/180, set184=1 and tail-call zero-motion.
  554 sets17C=10/184=1/180=0 without a zero call.791 directly enters550's
  helper tail after all scalar stores, so it only zeroes motion.560/561 and
  565/567 use17C=3/7, clear730/732 before zero-motion, then clear180 afterward.
- 600/601/602/604/605/611/661 clear730/732, set180=1 and tail-call zero-motion.
  606 clears730/73C/732/734/736/738/180, sets184=1 and tail-calls zero-motion.
  710/720/721/730 clear730/732/734 before the same helper tail.740 additionally
  clears73C/740/744/748/74C and736/738, retaining its own floating epoch.
- Independent797/798 source arms both call zero-motion, set horizontal speed6,
  vertical speed-30 and730=0, then dispatch wave14. The compiler naturally
  shares their complete body while retaining both direct branch comparisons.
  Other actions delegate to the common initializer.

Different source ordering of non-overlapping scalar stores can affect VC8's
shared tails. The final machine publications are independently checked against
the target; source spelling does not establish the original source layout.
No runtime matrix, compiler-profile search or LTCG impossibility is claimed.

## Whole-function experiments and negative controls

Private inputs are retained in `.analysis/exact-first-aya-action-entry-20261025/`;
reports/objects are under `build/exact-first-aya-action-entry-20261025/`.
Every row compares the entire emitted symbol with complete relocation replay.

| Complete source/control | Full bytes | SHA256 prefix | Whole result |
| --- | ---: | --- | --- |
| First complete source |2507|5ee7f15a|23/26 RETs;500 shares502;520-family tails folded into305|
| Independent500/502 source arms |2523|60a71db1|restores direct500 prefix and high502 receiver restoration|
| Early184 publication in305 |2599|9ce63073|retains520/525/529 bodies;extra418 scalar copy;27 RETs|
| Same scalar phase for418 |2579|66057eaf|native305 suffix restored;26 RETs;full exact|

The first full comparison immediately reproduces408 and every helper/tail count,
both table dimensions and all remap bytes. Only three target-backed controls are
needed. No assembly, target-byte arrays, inert locals, fake returns, ABI lies or
padding is used. There are no neutral controls to repeat.

The public full auditor rejects the retained first complete source at+19 with
1224 differing byte positions and SHA256
`5ee7f15aec03d48205b24e1aa7746e71e9e7c08e1837c0a5d8e5233fb8832064`.
A separate negative changes only the last generated-object remap byte617A12
from valid index20 to valid index0. Parsing still succeeds, but full comparison
rejects exactly+2578 with one differing byte, SHA256
`c3903a372875f6faa4002420c881583e0fc4d20fea82b4182d1cb0408f0c0937`.
Neither the canonical PE nor the accepted object is modified. Five public
synthetic fixtures cover both EAX/ECX tables, invalid final indices, metadata
destinations, truncated remaps and an unreviewed external CFG tail.

## Reproduction and next scope

Use locked repository Python and serial CPU0/nice10 jobs:

```sh
taskset -c 0 nice -n 10 scripts/repo-python scripts/build.py --unit exact-first-aya-action-initialization --compare --json
taskset -c 0 nice -n 10 scripts/repo-python scripts/audit-aya-action-initialization.py
TH105_ENABLE_GS=0 TH105_FP_MODE=default TH105_INLINE_MODE=default \
  taskset -c 0 nice -n 10 scripts/compile-unit.sh src/characters/AyaActionInitialization.cpp build/aya-entry-cold.obj
taskset -c 0 nice -n 10 scripts/repo-python scripts/audit-aya-action-initialization.py --object build/aya-entry-cold.obj
```

Only new local source/interface/unit and13 exclusive literal aliases are added.
Prior accepted sources, shared headers, compiler settings and bindings remain
unchanged. Formal and independent cold callable/full results agree. Complete
serial cold replay passes all522 accepted units/1410 functions. Receipt:
`build/exact-first-aya-action-entry-20261025/cold-all.log`. The full2579-byte
audit also passes on the object rebuilt during that replay. The exact ledger
records377464 callable authored bytes; metadata/alignment receive no extra
callable credit. Source-present1554, mapped1573 and593 configured units are
independently ledger-validated.

Next independently review Komachi primary slot+3C5F6700, candidate1971 bytes and
cell6C60A0, currently authored and source-missing. Re-attest its boundary/ABI
and every changed action before reuse. Parked roots remain separate; do not
reopen neutral controls without new independent evidence.
