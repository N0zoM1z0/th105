# Tenshi action initialization: 2026-10-25

`Tenshi_initialize_action_entry @ 0x0064A0A0` is canonical exact: 2453 callable
bytes and the entire 3023-byte emitted payload. Formal and independent cold
ordinary VC8 builds reproduce SHA256
`4ab4401633d0b2eb19e2a6abe306fccd1ae348342899e85f280a3b4bcd81cb52`.
All 108 section relocations are replayed; neither code nor metadata is masked.

## Observed target and boundary

The executable is Japanese 1.06a, SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
IDA preflight rejects the GUI's different executable. No IDA analysis read/write,
Ghidra process or decompiler is used. The complete raw instruction listing was
read independently before adapting the earlier Fighter initializer family.

The main span `[64A0A0,64AA35)` is 2453 bytes, SHA256
`7a989492486b9f7242beaa58cf6fae9e80672263aa30299a0b05246909323ae5`.
Raw CFG reaches all 585 instructions/all 2453 bytes and closes 40 RET0s, with
no external tail. Calls are 24 zero-motion `45AF40`, three object-spawn `465190`,
one face/velocity-flip `478E60` and one common initializer `477830`. The default
is an actual CALL followed by the shared ordinary epilogue.

The prologue reserves 28 real temporary bytes and saves EBX/ESI. ECX is the
receiver, moved into ESI. There is no EH/GS frame. The pointer-only receiver
has the observed primary virtual order, ending in slot+3C; it is never
instantiated or embedded as a complete recovered Fighter. Existing RTTI-backed
roster evidence and the raw PE cell `6C67D0` independently bind that slot of
Tenshi vtable `6C6794` to `64A0A0`. Authored ownership is already established.

Complete `[64A0A0,64AC6F)` includes the following three remapped tables:

| Destination table | DWORDs | Input range | Remap start / bytes |
| --- | ---: | --- | --- |
| 64AA38 | 24 | 300..418 | 64AA98 / 119 |
| 64AB10 | 20 | 505..750 | 64AB60 / 246 |
| 64AC58 | 3 | 788..798 | 64AC64 / 11 |

All 47 destination words/188 bytes and 376 remap bytes participate in full
comparison. Adjacent alignment is three bytes `8D4900` after the main, one
`90` after the first remap and two `8BFF` after the second. Those six bytes
are payload, not additional callable credit. The final remap ends at 64AC6F;
an INT3 separates the next function at 64AC70. Low 4/5/214, 500/501 and 780
are direct branches outside the remaps.

## Independently reviewed behavior

Complete ordinary source keeps numeric states, typed offset accesses and real
opaque helper calls. Same-family reuse does not normalize these differences:

- 4/5 set horizontal speed to +/-4.5. 214 clears short736 and both velocities,
  sets gravity0.6,108=0,10C=95,73C=12,74C=0, with no scratch-reset helper.
- 300/301/303/322 conditionally zero motion and preserve byte750. 302 adds its
  750 write; 308 zeros unconditionally, while 309 skips that call. 310 preserves
  both velocities, setting short730=0, gravity0.5,180=0 and184=4.
- 400 clears float73C/744 and shorts730/732 after zero-motion. 401/402 clear
  shorts730/732/736. 560/561 publish17C=3 and184=1 before entering the actual
  shared 401 suffix. This sharing must not be moved to a later physical owner.
- 404 and 406 consume horizontal and vertical products at different publication
  epochs around the short clears. Both spawn848 with `(0,0,2)`, as do 414/415.
  414 skips the short clears; 415 publishes180/gravity/750 before the products.
  416 neither spawns nor writes750. 418 sets speed11 before the 300-family path.
- 500/501 use17C=0, gravity0.55 and180=1, without adding a750 write. Only505
  belongs to the17C=4 entry; 520/521 publish184=99. 525/526/527 use17C=5 and
  enter the actual505 zero-motion suffix. 540 uses180=1 and clears750;
  542 skips zero-motion and preserves those distinct publications.
- 545..548 publish17C=6/180=1, call zero-motion, then re-read the actual action
  short. Only a *post-call* value547/548 spawns848; the entry action must not be
  cached across the opaque call. All four entries set750=1. 565/566 instead
  clear180/184 before zero-motion and do not add a750 write.
- 599 sets180=1 before zero-motion and clears four shorts; 731 enters after the
  180 write. 600/603/606/607/657, 601/604, 602 and605 retain their distinct
  publication/short-clear paths. 700 is a no-op; 780 only calls zero-motion.
- 720 publishes184=1/180=0, calls zero-motion, writes784=25 and clears four
  shorts. It loads the actual peer at170, computes `(self.x-peer.x)/45.0`,
  narrows to float, applies absolute value with the observed float round trips,
  stores780 and writes788 to the pinned float `0x3F0E38E4`.
- 730 calls the real face/velocity helper before zero-motion and clears730/73C.
  740/741 set180=1 before zero-motion, then clear73C/730/740.
- 750 clears74C and five shorts and passes a real `(0,0,0)` float packet to
  spawn940. The transported direction is an unsigned byte; horizontal position
  uses the same byte sign-extended and multiplied by integer30. Vertical
  position adds double120 and narrows to float. Both actual coordinate round
  trips survive compilation. 788 clears730 only; 795/797/798 additionally set
  horizontal speed0, vertical speed-15 and gravity0.5.

All packet storage is populated and consumed through its real pointer/count.
The target distinguishes 404's array home from the case-local packet home used
by the other spawn branches. Moving the used 404 array to function scope
naturally reproduces both homes, the 28-byte frame and ordinary CALL/RETs.
No inert storage, forced return, padding, assembly or invented ABI is used.

## Full-function experiments

Private source controls are retained in
`.analysis/exact-first-tenshi-action-entry-20261025/`; reports/objects are under
`build/exact-first-tenshi-action-entry-20261025/`.

| Complete source/control | Full bytes | SHA256 prefix | Whole result |
| --- | ---: | --- | --- |
| First complete source, all packets case-local | 2887 | b92254e6 | nonexact+2; frame16 versus28 |
| Actual 404 packet moved to outer scope | 2979 | ff6a6800 | frame28 and ordinary calls restored |
| 560 fallthrough into shared401 source | 2979 | d1144c54 | changes layout, does not recover owner |
| Distinct602 post-call scalar publications | 3015 | 1dee978b | restores24 zero calls/all40 RETs/three remaps |
| Explicit560 goto shared401 | 3015 | 1dee978b | whole-payload neutral; retain ordinary source |
| 560 writes180 before184, then opaque zero call | 3023 | ab03db58 | target physical shared owner;17 differing bytes |
| 601/604 publish184 before180/47E in source | 3023 | 7e1cffee |11 remaining bytes, all in605 |
| 605 uses the same independent publication epoch | 3023 | 4ab44016 | exact, zero unmasked differences |

Each comparison covers the entire COFF payload. The last two source edits let
ordinary scheduling recover the target's actual post-call store order. Their
purpose is supported by the complete instruction difference, not an isolated
similarity score. No compiler flag search or runtime behavior matrix is needed.
Original nominal field names, full owner layout and original TU remain unknown;
there is no general compiler/LTCG impossibility claim.

A negative generated-object control changes only the last remap byte at
64AC6E, from valid index1 to valid index0. Inventory parsing still succeeds,
but full comparison rejects exactly that byte at+3022, SHA256
`cdb24dcb3055be9bfa14a245effa45bc14e8687b208e97f34ab9c566a16d6eeb`.
The canonical executable and accepted object are untouched. Six public synthetic
fixtures cover all three ranges, both supported EAX/ECX forms, corrupt high/third
last indices, metadata destinations, remap truncation and unreviewed CFG tails.

## Reproduction and next scope

Use the locked repository Python and serial CPU0/nice10 commands:

```sh
taskset -c 0 nice -n 10 scripts/repo-python scripts/build.py --unit exact-first-tenshi-action-initialization --compare --json
taskset -c 0 nice -n 10 scripts/repo-python scripts/audit-tenshi-action-initialization.py
TH105_ENABLE_GS=0 TH105_FP_MODE=default TH105_INLINE_MODE=default \
  taskset -c 0 nice -n 10 scripts/compile-unit.sh src/characters/TenshiActionInitialization.cpp build/tenshi-entry-cold.obj
taskset -c 0 nice -n 10 scripts/repo-python scripts/audit-tenshi-action-initialization.py --object build/tenshi-entry-cold.obj
```

Only the new local source/interface/unit and17 exclusive literal aliases are
added. Prior accepted sources, headers, compiler settings and bindings are
unchanged. Formal and independent cold results agree on both callable and full
payload bytes. Complete serial cold replay passes all518 accepted units/1406
functions. Receipt: `build/exact-first-tenshi-action-entry-20261025/cold-all.log`.
The current exact ledger records368780 callable authored bytes; full table and
alignment payload bytes receive no extra callable credit. Source-present1550,
mapped1569 and589 configured units are independently ledger-validated.

Next review the independently authored, still source-missing Marisa primary
slot+3C root4B89C0, candidate2446 bytes. Re-attest its own boundary/ABI and every
changed action before family reuse. Parked nonexact Suika/common/Reimu roots
remain separate; do not reopen their neutral controls without new evidence.
