# Suika action initialization: 2026-10-25

`Suika_initialize_action_entry @ 0x005AD4A0` now has complete selected ordinary
C++ source. Formal and independent cold builds reproduce3139 emitted bytes,
SHA256 `ce5845dc668156c8b22569f82f35f4dcd35fee100afc04030b5cab248a2d3342`,
against3171 target bytes. First whole mismatch is+0x15; there is no exact credit.
Two subsequent target-backed publication controls reproduce this entire payload
byte-for-byte, so preserve the receipts and select another representative.

## Observed target, boundary and ABI

Target is Japanese1.06a SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
IDA preflight still rejects the GUI database's different executable. No IDA
analysis read/write or Ghidra/decompiler is used. All629 linear main instructions
were read from the hash-attested PE, then all switch edges were resolved.

Main `[5AD4A0,5ADEB1)` is2577 bytes, SHA256
`7f8f830fa4b0f6e87494b8f34899215aba9bf38a77a0c2de30a451a7673c7f7d`.
All629 instructions/2577 bytes are reachable, including the executed four-byte
loop-alignment LEA at5ADDDC. There are40 RET0s, seven zero-motion45AF40 tails
and the477830 default. No EH/GS frame is present. A real20-byte temporary frame
coexists with EBX/ESI saves and ECX receiver; it holds the consumed float loop
counter, three-float packet and conversion temporary. No dummy storage is added.

Full `[5AD4A0,5AE103)` is3171 bytes, SHA256
`497737f1cea8be3b66368574f3f72eb2833717a47121fbdc875f75edbfb034d0`.
It includes56 destination DWORDs/224 bytes,366 remap bytes and four adjacent
alignment bytes: three at5ADEB1..5ADEB3 and one after the first remap.

| Destination table | DWORDs | Input range | Remap start/bytes |
| --- | ---: | --- | --- |
| 5ADEB4 | 24 | 300..418 | 5ADF14 /119 |
| 5ADF8C | 32 | 505..751 | 5AE00C /247 |

The high remap indexes through ECX. Low4/5/214,500/501,795 and the797/798 range
have direct dispatch branches outside these tables. Next candidate5AE110 is
outside the complete payload. Metadata does not enlarge callable/authored credit.

Existing RTTI-backed roster evidence pins primary cell6C5BC8, offset3C of Suika
vtable6C5B8C, to5AD4A0. Its authored classification is unchanged. The new receiver
view is pointer-only, never instantiated/embedded as a recovered full Fighter.
Declarations preserve normal thiscall/RET0 and cdecl RNG transport; original
nominal source spelling, full layout and TU partition remain unknown.

The target has23 direct45AF40 calls, two45C030 wave calls, two4067D0 RNG sites,
one465190 spawn site, seven45AF40 tails and one477830 tail. Selected source
has22 zero calls and39 RETs, with all other physical helper/tail counts equal.
All125 source-section relocations are replayed. No declaration-only callee or
interior window gets implementation/matching credit.

## Complete semantic review and meaningful differences

The complete source retains numeric actions and typed field offsets. Reuse of
the prior Fighter family was checked against every target instruction:

- 4/5 use +/-5.5.214 sets736=0, horizontal/vertical speed0, gravity0.6,108=0,
  10C=72,73C=9 and74C=0; it does not call the scratch reset used by Patchouli.
- 300/301 set750 before conditional zero-motion.303 sets it after the call;
  321/322 skip that write.302 zeros unconditionally;304 publishes47E/184/180
  before zero-motion.418 writes17.5 then enters the321/322 path without a750
  write, retaining the observed overwrite when47E is zero.
- 309 keeps separate ordered clamps to+8 and-8, leaving NaN unmodified.330
  scales horizontal speed by double0.5 and sets vertical speed6.401/402 retain
  a distinct184 prefix;404..406 clear734 while414..416 do not.
- 505..508 use17C=4;520..523 use1;525/526 use5;530/531 use9.545/546 clear750,
  while560/561 set it.567 has no zero-motion call and preserves184.599 clears
  four shorts after actual zero-motion, without adding a750 write.
- 601/604 set184/180 before the zero tail;704/707/710/711/720 enter the same
  tail after those writes and therefore must skip them.607 leaves180 unchanged.
  605/730 use73C=2 while602 uses1.740 and751 preserve their distinct clear order.
- 795 sets73C=200, clears734 and dispatches wave19.797/798 set vertical speed3,
  clear734, set gravity0.1 and dispatch wave19, then run the complete eight-spawn
  loop with a case-local float[3]. Their range dispatch differs from Patchouli's
  independently retained797/798 equality entries.

The loop uses a real float counter0..7. Each iteration consumes RNG40 and RNG12
as unsigned-to-float conversions, writes packet `(rng40+(index*45-20),rng12+16,0)`,
and requests object999 at current X/Y+100, byte direction, variant1, packet count3.
It retains the target arithmetic association, conversion widths, two real RNG
calls, pointer lifetime, float increment and ordered upper-bound back edge.
The known producer remains declared as cdecl int-return and explicitly cast to
unsigned; no substitute RNG/provider result is supplied.

## Whole-source controls and bounded loop evidence

Private inputs are retained under `.analysis/exact-first-suika-action-entry-20261025/`;
reports and objects are under `build/exact-first-suika-action-entry-20261025/`.

| Complete source/control | Full bytes | Canonical SHA256 | Result |
| --- | ---: | --- | --- |
| First complete source | 3139 | a37d186f0e991df76908f96a0db0aaa401f73069a21baf61e77b154c1b50e562 | nonexact+15 |
| Correct unsigned RNG conversion to float, selected | 3139 | ce5845dc668156c8b22569f82f35f4dcd35fee100afc04030b5cab248a2d3342 | nonexact+15 |
| Group740 floating clears | 3139 | ce5845dc668156c8b22569f82f35f4dcd35fee100afc04030b5cab248a2d3342 | whole-payload neutral |
| Separate520 publication ordering from525 | 3139 | ce5845dc668156c8b22569f82f35f4dcd35fee100afc04030b5cab248a2d3342 | whole-payload neutral |

The first complete comparison immediately retains both table dimensions and all
366 remap bytes. It shows the old double conversion uses qword2^32 at6D6ED0,
whereas the target's unsigned correction reads dword2^32 at6D6EF8. A truthful
unsigned-to-float conversion recovers those exact instructions without an extra
rounding slot. This is a source-type/code-generation correction; no wider runtime
equivalence claim is inferred merely from the constants' equal numerical value.

The optional window selects `[5ADDE0,5ADEA5)`, from the first actual PUSH40/RNG
call through the actual RET0. The source body is independently found from its
PUSH40/CALL4067D0 pair and next RET. It begins5ADDC0. Replaying the entire COFF
symbol at diagnostic root5AD4C0 places that window at its target address, with
every external displacement and literal validated normally. The complete197
window bytes then agree, SHA256
`2f0e8b5cda698c0ccea19489a986a6a80d0923025302bff6e4c5d6154547886b`.
Both RNG calls, packet writes, actual spawn CALL and loop back edge are included.
The old double source fails at window+0x13/5ADDF3. No relocation field is masked;
no code is executed, and no generated window replaces the root comparison.
This is diagnostic only, with `whole_root_exact=false` and no helper credit.

Whole comparison still differs at1930 unmasked positions including32 missing
bytes. Code/alignment to the first table is2548 versus2580. The remaining
physical differences include401/402 prefix placement, the pooled525 zero call
and740's shared ending. Two consecutive controls preserve identical full output;
stop those questions and switch representative absent new independent evidence.
No original TU/LTCG impossibility is established. No behavior matrix, compiler
flag search, assembly, fake return, inert local or padding is used.

## Reproduction and handoff

Run serially with locked repository Python, CPU0/nice10:

```sh
taskset -c 0 nice -n 10 scripts/repo-python scripts/build.py --unit exact-first-suika-action-initialization --compare --json
taskset -c 0 nice -n 10 scripts/repo-python scripts/audit-suika-action-initialization.py --loop-window
TH105_ENABLE_GS=0 TH105_FP_MODE=default TH105_INLINE_MODE=default \
  taskset -c 0 nice -n 10 scripts/compile-unit.sh src/characters/SuikaActionInitialization.cpp build/suika-entry-cold.obj
taskset -c 0 nice -n 10 scripts/repo-python scripts/audit-suika-action-initialization.py --object build/suika-entry-cold.obj --loop-window
```

The full comparison commands deliberately return1 while nonexact. Five public
synthetic fixtures reject corrupt last indices, metadata destinations, truncated
remaps and unreviewed tails, while retaining both EAX/ECX-indexed table ranges.
Only new local source/interface/unit and25 exclusive literal aliases are added;
prior accepted source/headers/compiler settings and bindings are unchanged.
Source-present1549/mapped1568, units588. The exact ledger is unchanged; the last
aggregate cold replay remains the Patchouli checkpoint, with no new aggregate
replay claimed here. Next fresh same-slot peer is Tenshi64A0A0, candidate2453:
re-attest its slot and reconcile its own complete CFG/ABI before implementation.
