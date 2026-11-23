# Youmu Fighter action initialization: 2026-10-25

`YoumuFighter_initialize_action_entry @ 0x0053A1D0` now has complete source.
It is **not exact**. Formal and independent cold VC8 builds emit 1874 bytes,
SHA256 `4a86c07d7cabefc28c50d2aba1978f690d0e08ef59ae00c27c84501de627e57f`,
with 44 unmasked differing bytes. Preserve this bounded result and switch scope
instead of repeating the two byte-neutral controls below. No `matches.csv` row
or new accepted-byte credit is added.

The later fixed-field rewrite uses checked C++ members and compiles to the
same 1,874-byte canonical payload as the offset baseline. The comparison
includes both dispatch tables and all 60 relocations. Cases 601 and 604 still
share the wrong physical order. Their order also moves the entry shared by
602, 605–607 and 710 by four bytes. The source now falls through into that
shared reset after the two flag writes. An explicit reset label and chained
publication of the already shared phase were byte-neutral. A phase helper
stayed out of line under ordinary inlining and duplicated the case body when
forced inline. The unit now records the dispatch tables for future strict
comparison.

## Observed target and boundary

The executable is original Japanese 1.06a, SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
IDA preflight rejects the GUI's different executable; no IDA analysis read/write,
Ghidra process or decompiler is used. All 353 main instructions were read from
the hash-attested PE. Raw CFG reaches every instruction/all1424 bytes, closes 23
RET 0s and reconciles both indirect switches. The callable span is
`[53A1D0,53A760)`, SHA256
`cc0458b925ef32d9195d351e0fa67642028edb5c7776d9cddead0ad44e2415b8`.

Existing RTTI-backed roster evidence and raw cell 6C5180 identify primary slot 3C
of Youmu Fighter vtable 6C5144. This is a distinct owner/function from the parked
YoumuObject initializer 543670. Authored ownership remains unchanged.

The main saves EBX/ESI, retains ECX in ESI and allocates 16 local bytes. Those
bytes hold a real three-float spawn payload and call-argument arithmetic; no
GS/EH frame is present. There are 14 direct 45AF40 zero-motion calls, one 45AF40
tail, one 465190 spawn, one 4359F0 event, one indirect slot 0C call and the 477830
default tail. Action 13C uses MOVSX word. The high switch uses ECX as index;
its paths restore the receiver. No scratch-reset or wave helper is present.

The complete `[53A1D0,53A922)` payload is 1874 bytes, target SHA256
`9ae1d2bcebc090193d038f6998f47199d9aac2ebeb60e6b9cdc540f0fefe2609`:

| Destination table | DWORDs | Input range | Remap start / bytes |
| --- | ---: | --- | --- |
| 53A760 |14|300..418|53A798 /119|
| 53A810 |12|505..730|53A840 /226|

All 26 destination words/104 bytes and 345 remap bytes participate. One NOP at
53A80F aligns the high table; there is no alignment gap after the main. These
450 metadata/alignment bytes receive no callable credit. Fourteen INT3 bytes
separate the final remap from the accepted handle-manager destructor 53A930.
Direct 4/5/214,500/501 and 797/798 branches also participate in the complete CFG.

## Observed behavior and ABI

Instructions, widths and skipped writes below are observed. The source uses
numeric actions, typed offsets and declaration-only callees. Names, original
translation unit and full nominal owner layout remain unknown. Never construct
or embed the pointer-only receiver as a complete Fighter allocation.

- Before reading the action, if byte 7E4 is zero, create a real local float
  payload `{0,0,0}` and call 465190 with object 899, horizontal position
  `x - signed(direction)*600`, float-rounded `y + double100`, byte direction,
  variant-1, payload pointer and count 3. Set 7E4=1 after the call. Both the
  payload and the argument arithmetic are consumed. This entire instruction
  prefix agrees in the first complete build, including the 16-byte frame,
  MOVZX/MOVSX direction views and x87 stores/reloads.
- 4/5 set horizontal speed+4/-4.214 clears horizontal speed/736/vertical
  speed, sets gravity 0.6,108=0,10C=95,73C=14.5 and 74C=0. No scratch call.
  300/301/303/311/321/322/323 conditionally zero motion when 47E is zero,
  clear 180 and set 184=1/7CD=1.302 also clears 738 and sets 750=1, preserving
  47E.304 clears 47E/180 and publishes 750=1/184=1/7CD=1 before its actual
  zero-motion tail.529 enters after 304's x87 discard and shares that body.
- 305/308 only clear 180 and set 184=1/7CD=1;306/309 additionally clear 730.
  307 zeroes motion, then clears 180/73C/730 and sets 184=1/7CD=1.310 clears
  both velocities/180/730, sets 184=99/gravity0.5 and preserves 7CD.320 clears
  47E/180 and sets 184=1/7CD=1 without zero-motion.
- 400/401/402/410/411/412 set 180=1 before zero-motion, then clear 738/736/
  734/732/730 and set 750=1.404 sets 180=1 and enters that actual post-call
  suffix without zero-motion.408 sets horizontal speed 14/vertical speed 0,
  clears 47E/180/730/gravity and sets 184=1/7CD=1.418 has the corresponding
  scalar path but preserves gravity.414/415/416 clear gravity, set 180=1,
  scale both velocities by float 0.2 and enter the same five-short/750 suffix.
- 500/501 clear 180 before zero-motion and set 750=1; no 17C or short writes.
  505/506/510/511/560/561/565/566/570/571 also clear 730 after zero-motion.
  520/521/540/541/545 publish 180=0/184=1/7CD=1 before zero-motion and set
  750=1 afterward.525/526 have that prefix, then capture signed byte 609,
  set 750=1, and call virtual slot 0C with the sign-extended low word only if
  the captured value is at least 2.730 is preserved on these paths.
- 530/531 clear 180/184 before zero-motion and set 750=1, preserving 7CD.
  546 publishes 180=0/184=3/7CD=3 before zero-motion, then clears 730 and
  sets 750=1.600/603 publish 180=0/184=1/7CD=1 before zero-motion, then clear
  730 while preserving 750.601 sets 184=5/7CD=5, clears 180, zeroes motion and
  clears 730.604 uses 6 and jumps into 601's actual flag-publication body.
  602/605/606/607/710 skip those flag writes and share the zero/730 suffix.
- 720/730 clear 180 before zero-motion, then clear 732/734/730.797/798
  independently zero motion, dispatch indexed event 31 through 4359F0, set
  horizontal speed 17.5/vertical speed 0/gravity1.2 and clear 730. No wave call.
  Other actions delegate to the common initializer.

Fresh target reads reproduce the accepted 66-byte465190 wrapper and 14-byte
4359F0 member forwarder. The spawn wrapper returns RET 28 and forwards the
arguments to the object's manager; the event wrapper returns RET4. Youmu's
slot 0C cell 6C5150 points to 45C390. Its complete 202-byte provider loads a
four-byte stack argument but consumes AX in word tests/stores and a decrement
loop, ending RET4. The partial virtual view therefore uses a low-word `short`
argument in a four-byte slot. This does not recover its original nominal
parameter type or change the separately accepted provider's conservative `int`
declaration.525/526 match the actual AL load/comparison, MOVSX AX,AL and PUSH
EAX sequence; no fabricated upper-word contract is assumed.

## Whole-function experiments and stopping point

| Complete source/control | Full bytes | SHA256 prefix | Whole result |
| --- | ---: | --- | --- |
| First complete source |1910|7d0af66a|extra 604 copy;24 RETs/15 zero calls instead of 23/14|
| Shared consumed 601/604 phase |1874|4a86c07d|target counts restored;44 byte differences remain|
| Reverse phase case order |1874|4c5641cf|46 differences; swaps 5/6 positions, retaining wrong join orientation|
| Phase publication after switch |1874|4a86c07d|byte-identical to selected shared-phase source|
| Chained flag assignments |1910|7d0af66a|byte-identical to the first source, retaining extra copy|

Each control answers the observed 601/604 sharing/entry-placement question.
The selected source uses a consumed phase byte and a real common flag/zero
suffix. Its remainder agrees, including the entire spawn, virtual selector,
other actions, both remaps and all external call/tail counts. No compiler flag
grid, runtime matrix, assembly, copied target arrays, inert locals, fake returns,
ABI lies or padding is used.

The remaining 44 differences are 42 code bytes within 53A6BC..53A6E5 and two
destination-pointer bytes at 53A830/53A834. Target 601 falls through from MOV AL,5
into its common flag stores at 53A6BC;604 loads 6 at 53A6E2 and jumps backward.
The selected build instead jumps over its 6 load into the common body. It also
places the shared 602 suffix four bytes later. This is a documented physical
layout residual, not a whole-function exact or LTCG impossibility claim. The
two byte-neutral controls are closed absent new independent evidence.

All 60 section relocations are replayed. Formal and independent cold builds give
the same complete 1874-byte canonical hash and 44 differences. A generated-COFF-
only negative changes the final remap byte 53A921 from valid index 10 to valid
index 0. Parsing still succeeds and the difference count rises to 45; SHA256
`9e6f2cd29fb03923817aad15ef44663a230aa8b8a3d745cb39ee00291b19ad86`.
The target PE and selected object are unchanged. Five synthetic fixtures cover
both EAX/ECX tables, invalid final indices, metadata destinations, truncated
remaps and an unreviewed external CFG tail.

## VC8 block ordering, 2026-11-23

A headless trace of the pinned VC8 SP1 back end reproduces the complete
1,874-byte candidate and all 60 relocations. At `c2.dll:0x10B26CA8`, the
phase-5 assignment is followed by the common publication statements in
the instruction list. The same nodes survive `0x10B281E0`. At its return
at `0x10B26CAE`, an extra branch record follows phase 5, and the shared
publication now follows phase 6. The final object encodes that branch as
`EB 02` at root offset `+0x4EC`. The native byte store starts there.
This is the same list-splicing pass observed in
[the common Fighter trace](COMMON_FIGHTER_VC8_LAYOUT_2026_11_23.md).

The order is already decided when the list-splicing pass starts. In the
pinned `c2.dll`, `0x10B5CD30` walks the outgoing edges at block `+0x0C` in
depth-first order. Each edge has its next pointer at `+0` and destination
block at `+0x0C`. The routine appends each block to the list at graph
`+8`, through block `+0x10`, when it finishes visiting that block's
successors. Reconstructing that traversal from the live graph gives the
same 56 entries in the same order. The high switch reaches the phase-6
stub before the phase-5 stub, so phase 6 discovers the common publication
block. Reversing that postorder puts the publication after phase 6 in the
physical instruction list. The traced build still reproduces the complete
existing candidate, including both dispatch tables.

Moving the 604 stub next to 601, putting the 602 group before both, spelling
the shared motion reset as a direct fallthrough, and compiling independent
copies of the 600/603 or 602 reset statements each reproduce the same
44 differences. Placing the 604 stub before the 601 body reverses
the two phase constants and their table entries, leaving 46 differences
as in the earlier reversed-order control.

The compact switch edges are created before the depth-first walk. At
`c2.dll:0x10B26B65`, all 56 physical blocks already exist and the two compact
switches have empty outgoing lists. In `0x10B28910`, the compiler walks the
destination blocks in physical order. The instructions at `0x10B289BC`
through `0x10B289C5` prepend each incoming reference to its source block's
outgoing list. Reversing the 20 and 22 insertions captured for the two
switches reproduces their entire edge lists, including repeated destinations.
The high switch therefore visits its later phase-6 block before phase 5.
This trace reproduces the complete 1,874-byte baseline with 60 relocations.

Two source controls separate the case label from its phase assignment with
a forward or backward `goto`. Moving 604's label before 601 and moving 601's
label after 604 both generate the same four-byte change as swapping the full
cases. They exchange the two phase constants and table entries. A source
shape that selects the native tail direction is still open.

## Late publication merge with a shared switch exit

Publishing both bytes inside 601 and 604, then using a shared reset after
the switch, postpones the join to the same late `c2.dll:0x10B2C950` pass
that resolves Reimu's motion tail. Both copies survive the early layout
pass and lowering. At `0x10C077B6`, 601's two stores are gone, and 604's
stores have been exchanged. The resulting 1,874-byte candidate differs at
four byte offsets from the retained candidate and still has 44 differences
against the target. Reversing the stores in both source arms reproduces
the retained candidate, including its forward jump out of 601.

The target's action 602 enters at `0x0053A6C8`, immediately after 601's two
flag stores. Including 602 in the post-switch reset, or spelling its reset
as a fallthrough from 601 and a named branch from 604, gives the same late
merge and complete candidate. Leaving either phase arm with its own return
brings back the 1,910-byte duplicate. A successful late source shape still
needs to keep 601's stores and route 604 backward to them.

A hardware watchpoint on the link to 601's first store stops just after
`c2.dll:0x10B2E587` rewrites it to the second store inside the late splice
routine at `0x10B2E1B0`. The traced build reproduces the same relocated
1,874-byte candidate. Moving the group of reset-only cases before or after
both publishing cases leaves those bytes identical. Giving the reset its
own label inside the switch also reproduces the original baseline across all
three positions. Changing the lexical placement of the reset group alone
does not change the splice direction.

## The receiver load moves after tail merging

Giving 601, 602 and 604 independent returns reproduces the native bytes
from the 601 entry at `0x0053A6BA` through the 604 phase load at
`0x0053A6E2`, including 602's entry at `0x0053A6C8`. The compiler keeps
604's body in this 1,910-byte build, adding a call to the motion reset.
The shared-tail control emits 1,874 bytes by keeping the copies of the
two flag writes in 604. Swapping the store order in just one arm,
following the pattern used in the exact Komachi initializer, changes at
most four bytes in that control and leaves 44 differences.

Before the late merge at `c2.dll:0x10B2C950`, both independent phase
arms still set up ECX after clearing `+0x180`. The merge introduces the
602 entry between the flag stores and this clear in 601. It leaves the
604 receiver load in place. A hardware watchpoint on the predecessor
link of the first 604 store stops at `0x10C721DA`, immediately after
`0x10C721D7` links the store after the ECX load in `0x10C71DC0`. This
late instruction scheduler runs after the merge decision. Removing only
the reset-only case group in a scratch build also moves 601's receiver
load above the stores. Omitting 600/603, 720/730 or 797/798 leaves it
below them. The 602 entry accounts for an instruction-order difference
in a different action, and the next merge investigation belongs before
the scheduler.

The selected fallthrough source replays the same 1,874 bytes as the
prior selection, with identical relocation sites and kinds. The complete
replay has 42 DIR32 and 18 REL32 fields, including 26 local jump words,
345 remap bytes and the alignment byte. The strict switch verifier
rejects the candidate at `0x0053A6BC`. A separate complete comparison
finds 42 changed callable bytes through `0x0053A6E5` and two changed
destination bytes at `0x0053A830` and `0x0053A834`.

## The visible motion-reset definition changes later calls

A separate translation-unit control used the real four-store motion
reset from [FighterMotionReset.cpp](../src/characters/FighterMotionReset.cpp).
Both variants used `/Gy` to keep the two COFF bodies separate. The
declaration-only build reproduces the original caller. Putting the
definition before the initializer and marking it `noinline` retains all
the calls and reproduces the 27-byte callee at `0x0045AF40`. The 601/604
join direction stays the same. The caller loses two `mov ecx, esi`
instructions that the target has, one before the 525/526 virtual selector
at `0x0053A638` and one before the 797/798 event dispatch at
`0x0053A71E`. The caller shrinks by four bytes in both the independent
and shared-tail builds.

The receiver copies are present after register allocation in both
contexts. With the body visible they disappear in `c2.dll:0x10C07690`,
before tail merging. At that point the instruction list still has
separate receiver copies for 797 and 798, which subsequently share their
event dispatch. With ordinary inlining the visible definition also
removes two motion-reset call sites. Keep the declaration-only context for
the selected initializer. The resulting call count and switch size agree
with the target. This is a bounded compiler witness for the
[TH09 translation-unit control](GIANT_ROOT_REVIEW_2026_11_23.md#the-difference-can-originate-in-another-case).

## Reproduction and next scope

Use locked repository Python and serial CPU 0/nice10 jobs. Build/comparison and
full-audit commands intentionally return 1 for this retained nonexact root:

```sh
taskset -c 0 nice -n 10 scripts/repo-python scripts/build.py --unit exact-first-youmu-fighter-action-initialization --compare --json
TH105_ENABLE_GS=0 TH105_FP_MODE=default TH105_INLINE_MODE=default \
  taskset -c 0 nice -n 10 scripts/compile-unit.sh src/characters/YoumuFighterActionInitialization.cpp build/youmu-fighter-entry-cold.obj
```

Only this local source/interface/unit and 11 exclusively named literal aliases
are added. No accepted function references these aliases; prior headers,
profiles, sources and bindings remain unchanged. The accepted graph remains
524 units/1412 functions/381108 callable bytes. Its latest full cold receipt is
the preceding Remilia checkpoint; no new aggregate cold replay is claimed.
Mapped 1577/source-present1558 and 597 configured units/1565 functions are
ledger-validated. All 1405 floating target references agree.

Next independently review SakuyaObject slot 28 at 4E0D30, candidate 28985 bytes,
whose authored source remains missing. Re-attest slot 6C48B4, its complete CFG,
ABI and metadata ownership before implementing the first whole body. Keep
the parked initializer/common/Object residuals closed absent new target facts.
