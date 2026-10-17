# Reimu action root: boundary and checked entry phase

Only Japanese TH1051.06a SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`
is used. `Reimu_dispatch_action_state_vslot28 @478FA0` is the largest
currently unimplemented authored candidate. Its reconciled callable is
`[478FA0,48CE2E)`, **81550 bytes**, SHA256
`dbf6f375a809fea91cbbccf0f8cff2196f40cba11458c98e475a290b623053e6`.
It remains **unclassified/declaration-only**. Staged entry source does not
provide the complete action body, and no source-present or exact credit is added.

## Whole target CFG

Raw RTTI identifies primary vtable6C412C as Reimu, with slot+28 at6C4154
pointing to this root. The existing name, authored origin and void thiscall
model are retained. Entry saves the frame, aligns ESP to8, reserves570 bytes,
then saves EBX, a second EBP, ESI and EDI. That second save permits temporary
EBP use before restoring the real frame for RET.

The whole extent decodes to20256 instructions. All eleven validated switches
reach **20243 instructions /81488 bytes**, including153 RETs. No internal
direct CALL, unresolved indirect jump or external tail JMP remains. The other
62 bytes are nine loop-alignment gaps: each follows a JMP to the next16-byte
boundary and consists only of LEA of a register onto itself and optional NOP.
They remain significant in strict comparison; no byte exclusion was introduced.

The primary tables have126 distinct destinations in their union. Direct
special actions300/560 have separate dispatcher edges. All metadata ends at
48D38C, outside the callable.

| Action range | Destinations | Destination table | Index table |
| --- | ---: | --- | --- |
|0..226|45|48CE30|48CEE4|
|301..551|50|48CFC8|48D090|
|561..798|33|48D19C|48D220|

| Nested owner | Dispatch | Table | Entries |
| --- | --- | --- | ---: |
|550/551 sequence|4874E6|48D18C|4|
|616 sequence1..7|489C5E|48D310|7|
|710 match identifier|48B19F|48D32C|4|
|711 match identifier|48B794|48D33C|4|
|720 match identifier|48BE9D|48D34C|4|
|730 match identifier|48C3DD|48D35C|4|
|740 first identifier|48C738|48D36C|4|
|740 second identifier|48C8A8|48D37C|4|

At action720's CMP48BE95, backward reaching-write analysis finds only
`MOV EBP,3 @48BC57` across117 predecessor instructions, proving the four-entry
bound under ordinary callee-saved EBP. The algorithm retains unknown,
conflicting and partial-register paths; four regression tests cover them.

There are **1188 decoded E8 calls to32 targets**. The legacy mapper's raw-E8
sanity guard sees1191 byte occurrences pointing to35 plausible addresses;
three are inside other instructions. Those raw counts are explicitly not
decoded-call evidence. The most frequent real callees are spawn465190 (243),
advance4351C0 (121), landing473DD0 (96), wave45C030 (77) and crossed-surface
5F9310 (75). The audit annotates all32 with current ledger state. The two
orientation lookups and common action root remain nonexact; conversion68A1A0
retains its separate runtime-classification work.

## Staged C++ behavior

`src/characters/ReimuActionStatePrelude.cpp` has a typed receiver/peer prefix
and offset assertions. `run_checked_prelude()` returns true when entry handling
completes this update; false requires the remaining action switch. It is
**a staging helper, not an original function boundary or the vslot28 root**.
No match unit maps it to a target address. The root's source selection remains
the declaration header until complete semantics are recovered.

Observed entry behavior through4791D4, including shared return489D6A..489D72:

- Set WORD+7A0 to0 and WORD+7A2 to85 each update.
- For signed action150..158 with BYTE+751 zero, set that byte to1. Later
  independent action reads select object998 at Y+94 for150..153, Y+60 for
  154..157, or Y+100 for158. X adds57 times signed facing; the direction
  stack argument zero-extends the original byte to int. Final args are1/0/0.
  Preserve three conditions because a spawn can change owner state before
  the next action read; callback-returning behavior is not yet modeled.
- When signed WORD+7C8 is positive, clear it if self WORD+174 or peer WORD+174
  is nonpositive, then continue. If WORD+7CC is zero and DWORD+180 is1 or7,
  increment WORD+7CA with WORD wrap and set+7CC to1. If signed +7CA is at
  least7 and signed action at most10, call virtual `set_action(short669)` and
  return. Otherwise decrement +7C8, including a newly cleared0 becoming-1.
- Nonzero self WORD+186 or peer WORD+48C completes the update; otherwise
  proceed to dispatch. The normal valid-peer invariant is retained, with
  no invented null guard.

Field meanings remain numerically named. Widths, predicates and side effects
are observed; roles such as health, mode or cooldown are not inferred here.

## Focused native proof

```bash
scripts/compile-unit.sh src/characters/ReimuActionStatePrelude.cpp build/reimu-action-root/ReimuActionStatePrelude.obj
python3 scripts/audit-reimu-action-root.py --json
python3 scripts/audit-reimu-action-prelude.py build/reimu-action-root/ReimuActionStatePrelude.obj
```

Fresh VC8 SP1 `/O2 /GS- /GR /EHsc /MT`, default FP, produces object SHA256
`f3fae67b92f992240e76498a66948b07112bf46c937618bc024fa787b3a95b0b`.
At the entry-only checkpoint, CRLF source SHA256 was
`6443e0bc15d41b5d49432ac4665bc78096ef8813c1ba9c457a0534017b17d088`.
No shared header/profile/relocation ledger or accepted unit changed.

**0/10584 differences** cover the entire supplied7D0-byte actor prefix,
exit category, first callback receiver/argument bytes, native handled RET,
stack delta, preserved registers, x87 TOP and control word. Counter cases
use masked PC53; effect cases use PC53/PC64. Inputs include WORD endpoints
and wrap, count6/7, both tracked states, self/peer clear conditions, gates,
effect bytes0/1/128/255, all effect ranges, facing-128/-1/0/1/127, signed zero,
subnormals, infinities and quiet/signaling NaNs.

| Target exit | Controls |
| --- | ---: |
| ready for action dispatch |8286|
| first set_action669 entry |720|
| native handled RET |768|
| first object spawn entry |810|

Both programs execute native x86 instructions in separate emulators. No helper
result is replaced. Execution stops before callbacks or action dispatch;
actual creation, action669 animation and subsequent handlers remain outside
the proof. Target execution is restricted to the entry/shared-return spans;
unreviewed execution and writes outside actor/stack fail. Exception and full
gameplay equivalence are unproved. Reports pin target, object, audit, input,
Python, Unicorn and loaded-library identities, but do not themselves attest
compiler provenance. Input SHA256 is
`4785bfe52adb50f7f75e7be610e69e8930eaabda7c466019856487d493a64995`.

Two separately compiled wrong-source controls each fail1/9 smoke cases.
Returning immediately after clearing +7C8 misses the count/latch update and
decrement: action200/count6/state1 should reach count7/latch1/timer-1 and
dispatch. Passing signed facing gives FFFFFFFF instead of000000FF for-1;
the first150 spawn otherwise agrees at object998, X43/Y144 and args1/0/0.
Coordinates alone therefore do not prove correct call arguments.

## Direct Ghidra and remaining work

IDA preflight still rejects its attached executable; it is unused. One direct
Ghidra process at768MiB/twoCPUs reattested file/import identity, image base,
entry68B9D2, Windows x86 language and every mapped `.text` byte. The snapshot
initially had no Reimu function, so its first readback stopped. In a disposable
clone, the second pass decoded the exact20256 instruction starts and created
the bounded void-thiscall/no-stack-argument view. Readback confirmed body,
prototype, entry stores, all eleven dispatches, spawn call, common fallback
and final RET. This metadata is not compiler provenance. All nine primary
database files stayed hash-identical; the clone was removed, with no target
byte patching.

Facts are retained in the manifest, ledger note, typed staged source and
auditors. Private recipes/reports are in `.analysis/reimu-action-root-20261017/`
and `build/reimu-action-root/`. The [low0..10 follow-up](REIMU_LOW_ACTIONS_2026_10_17.md)
now carries the shared staging header and current source/native proof.
Complete81KB source and a strict whole-root comparison are still required
before any root implementation/exact claim.
