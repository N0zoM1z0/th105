# Suika control mode: complete source and parked callback-layout residual

## Result and reproduction

Suika Fighter primary slot `+0x5C @0x005AC680` has complete reviewed source in
`src/characters/SuikaControlMode.cpp/.hpp`. The target owns **3292 callable
bytes /3568 complete emitted bytes**. Selected source emits 3564 complete bytes
and remains **nonexact** at `+2 /0x005AC682`, where register save/zero scheduling
first differs. Source-present credit is added; no match or exact credit is added.

```sh
taskset -c 0 nice -n 10 python3 scripts/build.py \
  --unit exact-first-suika-control-mode --compare --json
```

Both commands correctly return 1. The full audit replays all 143 relocations
(58 REL32 /85 DIR32), including switch destinations beyond the callable body.
It checks every emitted byte and section-tail length. Formal comparison and
full audit reproduce selected private probe01. The VC8 SP1 `/O2` profile is
unchanged. The formal object/provenance is retained privately.

Target callable SHA256:
`00bbc2d3905fb8b53d8e8a6021c5666a82a9fadf99dd26938def8183d20e7a60`.
Target full SHA256:
`8373a0300127bccbc3f2dd49057dacd9264ff6f991e55cb844db3c915c72b279`.
Selected canonical full SHA256:
`5c4dd2b795f337de69cb509126b23997b5cacf985049af5b2d4fe039a0d76aab`.

These are pointer-only call views; never construct or embed them. Existing
slot 08/0C callees 45BFE0/45C390 support int returns and short/int arguments.
Motion reset 45AF40 is the existing 27-byte void thiscall/no-argument helper.
No callee gains implementation or exact credit from a declaration. Full owner
layout, original field declarations, unused virtual signatures and source/TU
identity remain unknown. No assembly, copied bytes, inert locals, padding,
fake returns, ABI/register forcing or compiler-profile search is used.

## Observed target boundary and ABI

Only the original Japanese 1.06a executable SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`
is inspected. Existing RTTI evidence classifies the root as authored. Raw
vtable base 6C5B8C has slot 08=45BFE0, slot 0C=45C390, slot 58=5F1F80 and
slot 5C cell 6C5BE8=5AC680. These are target observations, not source identity.

Raw traversal closes all **869 instructions**, **13 RET 0s**, **75 CALLs**,
internal direct edges and six switch destination entries. Direct calls are
4399C0 once,478E60 eleven times and 4067D0 forty-five times. Eighteen further
calls use action/sequence virtual slots. There are two independently reviewed
external tails:5AD068 jumps to motion reset 45AF40 with ECX restored to the
receiver and no arguments;5AD129 jumps through the actual slot 58 load at
5AD11E after vptr/receiver restoration. No other unresolved exit or remote
chunk remains in this bounded CFG. The helper tail is not an internal edge.

The function reserves four bytes and saves EBX/EBP/ESI. EDI is saved only for
records 0..11 at 5AC775. EBX has a zero lifetime; EBP initially holds 1 and becomes 2
inside the sequence family; EDI supplies 3 in the first motion/sequence paths.
The last instruction is **5AD35A JMP 5AD2E7**, ending exclusively 5AD35C. It
returns backward to the vertical store/callback tail and must not be omitted
by choosing the last textual RET as the boundary.

There is no alignment gap before the three-entry table at 5AD35C. Its 12 index
bytes start 5AD368. The second three-entry table starts 5AD374 and its 240-byte
index map starts 5AD380. Together they add 276 metadata bytes. Full payload ends
exclusively 5AD470 at the next function's FLD instruction; that neighbor is not
included. Only callable bytes could receive future exact credit.

All used literal widths and bits are read from the target. Position limits
are float 320.0 at 6C13B8 and double 960.0 at 6C0E98; scale is float.5 at 6CD140.
Unsigned RNG conversion uses float 2^32 at 6D6EF8. Motion bases use double
5/-5,10/-10,3/-3,6 and vertical 8/10/12. Sequence checks use double 200 and 350.
Two new named mappings pin double-10 at 6C4AA0 and double-3 at 6C4C90. Explicit
DIR32 overrides confine them to this unit; previous default bindings and
accepted sources/headers stay unchanged. Ordinary literal audits check COFF
encoding and hash-attested target bytes.

## Independently reviewed behavior

| Surface | Native behavior retained |
| --- | --- |
| Prefix |Decrement WORD768; clear DWORD724/728 and 6B4..6D0. Signed action 50..149 clears five word lanes; action<=199 separately clears 76C/764. Action 50..149 also compares byte 113 againstFF and writesFF only when different. Signed byte 55A<1 returns before checked deque selection. |
| Records 0..3 |Ready state 0 selects 770 then 1. State 1/positive peer 170/174 faces, selects 710 then 2. Ready positive-peer state 2 faces and sets motion 701 then 3. Edge-position paths continue into the state 3 check; the central path returns immediately. Ready positive-peer state 3 faces/selects711 then 4. Ready positive-peer state 4 faces, selects motion 701 then 1. No nonpositive-peer fallback store is copied from Alice. |
| First motion cycle |For ordered x<320, facing+1 uses RNG 5+5, other facing uses-5-RNG5. For ordered x>960 those directions swap. Edge vertical motion is RNG 4+8. Central/default motion is 5-RNG10 and RNG 4+8. All scale stores are.5. |
| Second motion cycle |Same horizontal branches and bases; every vertical route uses RNG 4+12. All paths select 701 then 1 and return. |
| Records 4..7 |Initial 770/1. Positive-peer ready state 1 faces/selects720 then 2. Positive-peer ready state 2 faces and uses the edge 10/-10 bases with RNG 5 and vertical RNG 4+10; center/default uses 10-RNG20 and RNG 4+12. Scale.5/action701 then 1. |
| Records 8..11 entry |Initial 770/1. Ready state 1 faces/selects730 then 2. State 2 requires positive peer, action 730, sequence 1 and expired timer; face, RNG 100<50 selects sequence 2/state3 and timer=RNG 60+60. Otherwise sequence 3 clears DWORD180, writes byte 184=1 and state 4. |
| Sequence state 3 |Expired timer and sequence 2 face/select1, clear floatF4 and write state 5. RNG 100<=20 selects sequence 3, clears 180, writes 184=1 and state 4. Both outcomes return. The condition does not require action 730. |
| Sequence state 4 |Action 730/sequence1 writes state 5 before RNG 100. Strict RNG 100<20 selects sequence 2/state3 and a new delay; otherwise continue to state 5 in the same tick. The inclusive state 3 threshold is not substituted here. |
| Sequence state 5 |Face; ordered peerY>=200 and `abs(int(selfX-peerX<=350.0))` gate RNG 100<=80. Success writes state 2 before sequence 9; failure writes state 2 before sequence 7. Both really tail-call zero_velocity_acceleration. The abs wraps the comparison's integer result, not the distance. No symmetric-distance rewrite is made. |
| Records 12..15 |Initial 770/1. Ready state 1 republishes 1 before 740. There is no peer gate or transition to 2. |
| Records 248..255 |Conditional action0, then the actual slot 58 virtual tail. |
| Records 16..19 |Initial 770/1. Ready state 1 publishes 2 before 750. Positive-peer ready state 2 faces; edge motion uses 3/-3 with RNG 5 and vertical RNG 4+10, center/default uses 6-RNG12 and RNG 4+12. Scale.5/action701 then 1. The final central vertical conversion jumps backward to the shared store. |

Readiness means action700 or 0. State and peer values are re-read at actual
post-callback points; callbacks are not assumed to leave fields unchanged.
RNG motion values consume unsigned 32 before conversion; timers/state/peer
checks keep their observed word widths and signs. Local byte 255 access records
the target representation without claiming the original source signedness.
No large runtime matrix was required for a concrete unresolved ambiguity.

## Early complete comparison and finite experiments

| Probe | Evidence-backed question and result |
| --- | --- |
|00|First complete source emits 3564 bytes, with 45 selectors and 11 facing calls. It represents byte 113 as signed-1; VC8 shares that constant with timer decrement and changes its immediate instruction. Shared tails and constant promotion also differ. |
|01 selected|Use unsigned byte 255 for the same observed byte compare/write. Timer decrement returns to the native immediate form and the byte flag uses AL=FF. Complete 3564 still differs from 3568; register/save allocation first differs+2. Keep this structured source. |
|02 neutral|Express the consumed byte 184 as bool true to test its possible contribution to the retained 1 constant. Its entire payload equals 01; no original bool type is inferred and the control is unselected. |
|03 unselected|Express the two actual shared sequence 3/delay endpoints explicitly. It changes the complete payload to 3552; constant promotion and physical callback sharing remain wrong. This is not an identical-output control or an exact result. |
|04 rejected|Convert motion RNG unsigned values directly to double to test conversion ownership. Full 3564 and physical calls stay unchanged, but 31 correction operands become qword 2^32 instead of the target's dword 2^32, changing 62 bytes. The float conversions in 01 remain necessary. |

Selected source has all 57 direct CALL sites and both real tails. It merges
virtual callbacks into 14 physical CALL sites versus 18 native. Native EDI 3
lifetime, EBP 1-to2 reuse, conditional save placement and the resulting shared
motion/action epilogues remain unexplained. The similar payload length is
not a match score. Stop this bounded investigation and select another complete
family peer; reopen only with new lifetime/partition/TU evidence. No LTCG
requirement is established. The previous Yukari/Patchouli neutral controls
remain parked.

## Validation and retained evidence

IDA preflight rejects the different executable open in its GUI; no semantics
or writes from that session are used. The one-process Ghidra guard first
refuses launch while foreign analysis is live. After it exits, a read-only run
independently attests file SHA, image base, entry 68B9D2, Windows x86 language/
compiler and all raw-backed sections. A temporary 3292-byte entry closes 869
instructions; callee views and metadata are read back, then rolled back. All
nine primary DB pins are unchanged. Decompiled output only corroborates raw
facts and is not pasted into source. Own Ghidra uses 384MiB/one CPU; builds
remain serial CPU 0/nice10 with memory/swap monitored.

Source-present total becomes 1525 and configured graph 566 units/1534 functions. Exact
ledger totals stay 1397 functions/327058 callable bytes, with no aggregate cold
replay claim. Origin dispositions/denominator/selector stay unchanged.
