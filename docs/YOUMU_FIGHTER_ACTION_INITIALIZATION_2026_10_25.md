# Youmu Fighter action initialization: 2026-10-25

`YoumuFighter_initialize_action_entry @ 0x0053A1D0` now has complete source.
It is **not exact**. Formal and independent cold VC8 builds emit1874 bytes,
SHA256 `4a86c07d7cabefc28c50d2aba1978f690d0e08ef59ae00c27c84501de627e57f`,
with44 unmasked differing bytes. Preserve this bounded result and switch scope
instead of repeating the two byte-neutral controls below. No `matches.csv` row
or new accepted-byte credit is added.

## Observed target and boundary

The executable is original Japanese1.06a, SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
IDA preflight rejects the GUI's different executable; no IDA analysis read/write,
Ghidra process or decompiler is used. All353 main instructions were read from
the hash-attested PE. Raw CFG reaches every instruction/all1424 bytes, closes23
RET0s and reconciles both indirect switches. The callable span is
`[53A1D0,53A760)`, SHA256
`cc0458b925ef32d9195d351e0fa67642028edb5c7776d9cddead0ad44e2415b8`.

Existing RTTI-backed roster evidence and raw cell6C5180 identify primary slot3C
of Youmu Fighter vtable6C5144. This is a distinct owner/function from the parked
YoumuObject initializer543670. Authored ownership remains unchanged.

The main saves EBX/ESI, retains ECX in ESI and allocates16 local bytes. Those
bytes hold a real three-float spawn payload and call-argument arithmetic; no
GS/EH frame is present. There are14 direct45AF40 zero-motion calls, one45AF40
tail, one465190 spawn, one4359F0 event, one indirect slot0C call and the477830
default tail. Action13C uses MOVSX word. The high switch uses ECX as index;
its paths restore the receiver. No scratch-reset or wave helper is present.

The complete `[53A1D0,53A922)` payload is1874 bytes, target SHA256
`9ae1d2bcebc090193d038f6998f47199d9aac2ebeb60e6b9cdc540f0fefe2609`:

| Destination table | DWORDs | Input range | Remap start / bytes |
| --- | ---: | --- | --- |
| 53A760 |14|300..418|53A798 /119|
| 53A810 |12|505..730|53A840 /226|

All26 destination words/104 bytes and345 remap bytes participate. One NOP at
53A80F aligns the high table; there is no alignment gap after the main. These
450 metadata/alignment bytes receive no callable credit. Fourteen INT3 bytes
separate the final remap from the accepted handle-manager destructor53A930.
Direct4/5/214,500/501 and797/798 branches also participate in the complete CFG.

## Observed behavior and ABI

Instructions, widths and skipped writes below are observed. The source uses
numeric actions, typed offsets and declaration-only callees. Names, original
translation unit and full nominal owner layout remain unknown. Never construct
or embed the pointer-only receiver as a complete Fighter allocation.

- Before reading the action, if byte7E4 is zero, create a real local float
  payload `{0,0,0}` and call465190 with object899, horizontal position
  `x - signed(direction)*600`, float-rounded `y + double100`, byte direction,
  variant-1, payload pointer and count3. Set7E4=1 after the call. Both the
  payload and the argument arithmetic are consumed. This entire instruction
  prefix agrees in the first complete build, including the16-byte frame,
  MOVZX/MOVSX direction views and x87 stores/reloads.
- 4/5 set horizontal speed+4/-4.214 clears horizontal speed/736/vertical
  speed, sets gravity0.6,108=0,10C=95,73C=14.5 and74C=0. No scratch call.
  300/301/303/311/321/322/323 conditionally zero motion when47E is zero,
  clear180 and set184=1/7CD=1.302 also clears738 and sets750=1, preserving
  47E.304 clears47E/180 and publishes750=1/184=1/7CD=1 before its actual
  zero-motion tail.529 enters after304's x87 discard and shares that body.
- 305/308 only clear180 and set184=1/7CD=1;306/309 additionally clear730.
  307 zeroes motion, then clears180/73C/730 and sets184=1/7CD=1.310 clears
  both velocities/180/730, sets184=99/gravity0.5 and preserves7CD.320 clears
  47E/180 and sets184=1/7CD=1 without zero-motion.
- 400/401/402/410/411/412 set180=1 before zero-motion, then clear738/736/
  734/732/730 and set750=1.404 sets180=1 and enters that actual post-call
  suffix without zero-motion.408 sets horizontal speed14/vertical speed0,
  clears47E/180/730/gravity and sets184=1/7CD=1.418 has the corresponding
  scalar path but preserves gravity.414/415/416 clear gravity, set180=1,
  scale both velocities by float0.2 and enter the same five-short/750 suffix.
- 500/501 clear180 before zero-motion and set750=1; no17C or short writes.
  505/506/510/511/560/561/565/566/570/571 also clear730 after zero-motion.
  520/521/540/541/545 publish180=0/184=1/7CD=1 before zero-motion and set
  750=1 afterward.525/526 have that prefix, then capture signed byte609,
  set750=1, and call virtual slot0C with the sign-extended low word only if
  the captured value is at least2.730 is preserved on these paths.
- 530/531 clear180/184 before zero-motion and set750=1, preserving7CD.
  546 publishes180=0/184=3/7CD=3 before zero-motion, then clears730 and
  sets750=1.600/603 publish180=0/184=1/7CD=1 before zero-motion, then clear
  730 while preserving750.601 sets184=5/7CD=5, clears180, zeroes motion and
  clears730.604 uses6 and jumps into601's actual flag-publication body.
  602/605/606/607/710 skip those flag writes and share the zero/730 suffix.
- 720/730 clear180 before zero-motion, then clear732/734/730.797/798
  independently zero motion, dispatch indexed event31 through4359F0, set
  horizontal speed17.5/vertical speed0/gravity1.2 and clear730. No wave call.
  Other actions delegate to the common initializer.

Fresh target reads reproduce the accepted66-byte465190 wrapper and14-byte
4359F0 member forwarder. The spawn wrapper returns RET28 and forwards the
arguments to the object's manager; the event wrapper returns RET4. Youmu's
slot0C cell6C5150 points to45C390. Its complete202-byte provider loads a
four-byte stack argument but consumes AX in word tests/stores and a decrement
loop, ending RET4. The partial virtual view therefore uses a low-word `short`
argument in a four-byte slot. This does not recover its original nominal
parameter type or change the separately accepted provider's conservative `int`
declaration.525/526 match the actual AL load/comparison, MOVSX AX,AL and PUSH
EAX sequence; no fabricated upper-word contract is assumed.

## Whole-function experiments and stopping point

Private source controls are under
`.analysis/exact-first-youmu-fighter-action-entry-20261025/`; objects/reports
are under `build/exact-first-youmu-fighter-action-entry-20261025/`.

| Complete source/control | Full bytes | SHA256 prefix | Whole result |
| --- | ---: | --- | --- |
| First complete source |1910|7d0af66a|extra604 copy;24 RETs/15 zero calls instead of23/14|
| Shared consumed601/604 phase |1874|4a86c07d|target counts restored;44 byte differences remain|
| Reverse phase case order |1874|4c5641cf|46 differences; swaps5/6 positions, retaining wrong join orientation|
| Phase publication after switch |1874|4a86c07d|byte-identical to selected shared-phase source|
| Chained flag assignments |1910|7d0af66a|byte-identical to the first source, retaining extra copy|

Each control answers the observed601/604 sharing/entry-placement question.
The selected source uses a consumed phase byte and a real common flag/zero
suffix. Its remainder agrees, including the entire spawn, virtual selector,
other actions, both remaps and all external call/tail counts. No compiler flag
grid, runtime matrix, assembly, copied target arrays, inert locals, fake returns,
ABI lies or padding is used.

The remaining44 differences are42 code bytes within53A6BC..53A6E5 and two
destination-pointer bytes at53A830/53A834. Target601 falls through from MOV AL,5
into its common flag stores at53A6BC;604 loads6 at53A6E2 and jumps backward.
The selected build instead jumps over its6 load into the common body. It also
places the shared602 suffix four bytes later. This is a documented physical
layout residual, not a whole-function exact or LTCG impossibility claim. The
two byte-neutral controls are closed absent new independent evidence.

All60 section relocations are replayed. Formal and independent cold builds give
the same complete1874-byte canonical hash and44 differences. A generated-COFF-
only negative changes the final remap byte53A921 from valid index10 to valid
index0. Parsing still succeeds and the difference count rises to45; SHA256
`9e6f2cd29fb03923817aad15ef44663a230aa8b8a3d745cb39ee00291b19ad86`.
The target PE and selected object are unchanged. Five synthetic fixtures cover
both EAX/ECX tables, invalid final indices, metadata destinations, truncated
remaps and an unreviewed external CFG tail.

## Reproduction and next scope

Use locked repository Python and serial CPU0/nice10 jobs. Build/comparison and
full-audit commands intentionally return1 for this retained nonexact root:

```sh
taskset -c 0 nice -n 10 scripts/repo-python scripts/build.py --unit exact-first-youmu-fighter-action-initialization --compare --json
taskset -c 0 nice -n 10 scripts/repo-python scripts/audit-youmu-fighter-action-initialization.py
TH105_ENABLE_GS=0 TH105_FP_MODE=default TH105_INLINE_MODE=default \
  taskset -c 0 nice -n 10 scripts/compile-unit.sh src/characters/YoumuFighterActionInitialization.cpp build/youmu-fighter-entry-cold.obj
taskset -c 0 nice -n 10 scripts/repo-python scripts/audit-youmu-fighter-action-initialization.py --object build/youmu-fighter-entry-cold.obj
```

Only this local source/interface/unit and11 exclusively named literal aliases
are added. No accepted function references these aliases; prior headers,
profiles, sources and bindings remain unchanged. The accepted graph remains
524 units/1412 functions/381108 callable bytes. Its latest full cold receipt is
the preceding Remilia checkpoint; no new aggregate cold replay is claimed.
Mapped1577/source-present1558 and597 configured units/1565 functions are
ledger-validated. All1405 floating target references agree.

Next independently review SakuyaObject slot28 at4E0D30, candidate28985 bytes,
whose authored source remains missing. Re-attest slot6C48B4, its complete CFG,
ABI and metadata ownership before implementing the first whole body. Keep
the parked initializer/common/Object residuals closed absent new target facts.
