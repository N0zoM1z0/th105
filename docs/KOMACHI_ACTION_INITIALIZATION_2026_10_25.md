# Komachi action initialization: 2026-10-25

`Komachi_initialize_action_entry @ 0x005F6700` now has complete target-reviewed
source, but remains **nonexact**. Formal and independent cold ordinary VC8
builds emit2496 bytes, SHA256
`c6dac7e036e8d53995998560299b03e014b1f0727ddbddbbeed985b975ac915a`.
All94 relocations are replayed. The complete target also has2496 bytes, but49
unmasked byte positions differ:47 in550/551's code layout and two in551's
destination pointer. This source-present checkpoint adds no exact credit.

## Observed target, boundary and ABI

The executable is Japanese1.06a, SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
IDA preflight rejects the GUI's different executable. No IDA analysis read/write,
Ghidra process or decompiler is used. All456 main instructions were read from
the hash-attested PE; all direct/switch CFG edges were reconciled.

Main `[5F6700,5F6EB3)` has1971 bytes and SHA256
`b914a20a2cfa84638b160892ff82bc4094be80628d5644ba537844d80fd1a222`.
Raw CFG reaches every main instruction/byte and closes34 RET0s. It has23 direct
zero-motion45AF40 calls, four45AF40 tails, one435110 scratch reset, one4359F0
indexed event call and the477830 default tail. EBX/ESI are saved and ECX is
retained in ESI. No local, GS or EH frame is present. The pointer-only receiver
and scratch views must never be instantiated or embedded as complete owners.

Existing RTTI-backed roster evidence and raw cell6C60A0 bind primary slot+3C
of Komachi vtable6C6064 to5F6700. Authored ownership is unchanged. Action13C is
read with MOVSX word. The high switch indexes through ECX and restores the
receiver before its actual helper paths.

Complete `[5F6700,5F70C0)` owns:

| Destination table | DWORDs | Input range | Remap start / bytes |
| --- | ---: | --- | --- |
| 5F6EB4 |19|300..418|5F6F00 /119|
| 5F6F78 |25|505..732|5F6FDC /228|

All44 destination words/176 bytes and347 remap bytes participate. One alignment
NOP follows the main and another follows the low remap. The final remap ends
exactly at the independently accepted handle-manager destructor5F70C0. No
neighboring function or invented padding is included.4/5/214,500/501 and797/798
use direct branches.

The accepted435110 scratch helper consumes ECX=this+4. The accepted4359F0
unused-this member forwards a dword event selector with RET4 cleanup;797/798
pass31. It is distinct from the character wave-handle provider45C030, which
this root never calls. Existing callee acceptance earns no new credit here.

## Independently reviewed behavior

Widths, instructions and edges are target observations. Source retains numeric
actions, typed offsets and opaque calls. Original nominal source names, full
class layouts and original TU/layout context remain unknown.

- 4/5 set horizontal speed+6/-5.214 calls the scratch reset onthis+4, clears
  horizontal/vertical speed and736, sets gravity0.6,108=0,10C=95,73C=12 and
  74C=0.300/301/303/321/322 conditionally zero motion when47E is zero, clear
  180 and set184=1.302 additionally clears47E and sets750=1.304 publishes
  47E=0/184=1/180=0 before zero-motion, then sets750=1.
- 305 clears vertical speed/47E/180/gravity, sets horizontal speed17.5 and
  184=1.306 clears730/180 and sets184=1.307/308/309 set184=1/180=0/750=1;
  613 enters after their184 store and therefore preserves184.310 sets gravity
  0.5/184=1/180=0 without clearing velocities.320 only clears47E/180 and sets
  184=1, without zero-motion.418 sets horizontal speed17.5 before entering
  the300 conditional-zero path.
- 400/401/402 set180=1 before zero-motion, clear73C/740/744 and730/732/734,
  then set750=1.404/405/406 perform these clears without zero-motion, clear
  gravity and scale both velocities by float0.2.408 sets horizontal speed17.5,
  clears47E/730/180/vertical speed and sets184=1.409 uses gravity0.35.
- 410 sets180=1 before zero-motion, clears730/732/736/738 and sets750=1.
  411 preserves738;412 clears732/736/730/738 and preserves750.414 clears
  gravity/730/732/736/738, sets180=1/750=1 and scales both velocities by
  float0.2 without zero-motion.415/416 preserve738 and retain an independent
  floating body. Actual publication/product epochs distinguish those bodies.
- 500/501 use17C=0, zero motion,184=0/47E=0/180=1, preserving750.505/506
  use17C=4 and add750=1.507/508 instead scale both velocities by float0.1,
  clear184/47E/gravity and use17C=4/180=1/750=1 without a zero call.510/511
  use17C=8 and the500 suffix, preserving750.
- 520/521 use17C=1, zero motion,180=1/47E=0 and clear730/732/734, without
  writing184/750.525/526 use17C=5, zero motion,184=8/12,180=0/47E=0 and
  clear730.540/541/542/543 publish17C=2/738=0/180=1 before zero-motion, then
  clear750 while preserving other shorts.545/546 use17C=6/180=1 before
  zero-motion and set750=1.
- 550/551 set73C=0/1 respectively, set184=1/17C=10/180=0 before zero-motion,
  then set750=1. Native target550 falls through from FLDZ into shared5F6CEE;
  native551 loads FLD1 at5F6D1D and jumps backward to that shared receiver/
  FSTP/publication/call suffix. Selected source preserves values and stores,
  but VC8 places both constant-loading entries before their common suffix.
- 560/561 and565/566 use17C=3/7, set180=1 before zero-motion, clear730/732/
  734/736 and set750=1.599 enters412's body through an actual receiver prefix.
  600 clears730/180, sets184=1 and tail-calls zero-motion.601 publishes180=0
  before184=1;611 retains a separate184-before180 tail.603 clears730/184,
  sets180=1 and tail-calls zero-motion.
- 602/605/606 zero motion, then enter520's short suffix after its180/47E
  stores: those fields and17C/184 must be preserved.604 publishes180=0/184=1
  before zero-motion and clears730/732 afterward.612/615 use410's complete
  body through its receiver prefix.710/720/730 zero motion and clear730;711
  also clears732;732 instead clears738.
- Independent797/798 source arms both call zero-motion and actual event31,
  set horizontal speed12,730=0, vertical speed0 and gravity0.5. The compiler
  naturally shares their body while preserving both direct comparisons. Other
  actions delegate to the common initializer.

The float0.2 and float0.1 products use their compiler-emitted qword extensions,
not decimal double0.2/0.1. Every literal has a target-observed width/bit binding.

## Finite whole-function experiments

Private inputs are retained in `.analysis/exact-first-komachi-action-entry-20261025/`;
reports/objects are under `build/exact-first-komachi-action-entry-20261025/`.
All comparisons replay the complete emitted section without masking.

| Complete source/control | Full bytes | SHA256 prefix | Whole result |
| --- | ---: | --- | --- |
| First complete source |2460|f77e910e|414/415 folded;550/551 duplicate helper;24/23 zero calls|
| Early750 publication in415 |2540|5152c543|independent414/415 bodies restored;551 still copied|
| Consumed shared float initial value |2556|181d5dfa|23 calls restored;adds a four-byte frame;rejected|
| Explicit common publication label |2496|b6eeba1d|all counts/dimensions agree;62 byte differences|
| Backward source551 join |2496|b6eeba1d|whole-payload neutral|
|415 counter publication before750 |2496|c6dac7e0|49 differences;all confined to550/551 and its table pointer|
|551 source arm before550 |2496|c7a40995|swaps constant-loading order;51 differences;rejected|
| Join after actual184 publication |2496|c6dac7e0|whole-payload neutral relative to selected source|

The selected source uses the small backward551 label form and no local frame.
The label expresses a genuine shared publication/call body. The rejected float
local was actually consumed, but its emitted frame contradicts the target; it
is not selected. No assembly, copied target arrays, inert locals, fake returns,
ABI lies or padding are used. Alternative joins reproduce the same complete
payload and source-order reversal does not recover the native placement. Close
these finite controls and choose another complete representative unless new
independent target/TU evidence changes the question. No standalone-object/LTCG
impossibility has been proved.

The49 differences split into47 main-code positions from5F6CEE through the end
of551's owner, plus the two551 destination bytes at5F6F9C/5F6F9D. Both remaps
and all other metadata agree. Formal and independent cold builds reproduce the
same complete payload and the same residual; byte length alone is not acceptance.

## Scoped native check and negatives

`--shared-initial-witness` executes only actual actions550 and551 to RET0,
using the real canonical45AF40 provider, no substituted helpers, FPCW0x27F,
and a0x900-byte owner initialized toA5. It checks all owner bytes, return stack
and nonvolatile registers. Both target/candidate execute the actual helper once;
550 publishes73C=0,551 publishes73C=1, and no owner bytes differ. This is a
two-input diagnostic for the differing join, not a full-root runtime claim.

A generated-COFF-only negative replaces the candidate's FLD1 with FLDZ. It still
has49 byte differences overall, but the witness rejects551 at owner73E/73F:
target73C=1 versus candidate0. This illustrates why a byte-distance score alone
does not establish even local semantics. Negative full SHA256:
`2b31e9ab346608a6fefd4632826df6116d0dbbcb06c90c51a20f9fc19dbfdb92`.
Another generated-object negative changes the final remap byte5F70BF from valid
index23 to valid index0. The original49 differences remain and the last byte
adds one more, for50 total; full SHA256
`410389b40f7ff3177a0d7e998c3026d5541bb4718516872cf58e264650ec65b0`.
Neither the canonical PE nor the selected object is modified. Five synthetic
fixtures check table ranges/ECX indexing, invalid final indices, metadata
destinations, truncated remaps and an unreviewed external tail.

## Reproduction and next scope

The comparisons below intentionally return1 for the recorded nonexact result,
including when the optional two-case witness passes:

```sh
taskset -c 0 nice -n 10 scripts/repo-python scripts/build.py --unit exact-first-komachi-action-initialization --compare --json
taskset -c 0 nice -n 10 scripts/repo-python scripts/audit-komachi-action-initialization.py --shared-initial-witness
TH105_ENABLE_GS=0 TH105_FP_MODE=default TH105_INLINE_MODE=default \
  taskset -c 0 nice -n 10 scripts/compile-unit.sh src/characters/KomachiActionInitialization.cpp build/komachi-entry-cold.obj
taskset -c 0 nice -n 10 scripts/repo-python scripts/audit-komachi-action-initialization.py --object build/komachi-entry-cold.obj --shared-initial-witness
```

Only new local source/interface/unit and10 exclusive literal aliases are added.
Accepted sources, shared headers, compiler settings and bindings are unchanged.
No matches.csv row is added. The accepted graph remains522 units/1410 functions;
there is no new aggregate cold-replay claim. The last aggregate receipt remains
the Aya checkpoint. Source-present1555, mapped1574 and594 configured units are
ledger-validated.

Next independently review Iku primary slot+3C62FFF0, candidate1842 bytes and
cell6C6568, currently authored and source-missing. Re-attest its boundary/ABI
and every changed action before reuse. Keep this residual parked absent new
independent evidence; do not repeat closed join/source-order trials.
