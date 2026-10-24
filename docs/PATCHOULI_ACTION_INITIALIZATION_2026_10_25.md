# Patchouli action initialization: 2026-10-25

`Patchouli_initialize_action_entry @ 0x0051D650` accepts3132 callable bytes and
all3868 emitted bytes in formal and independent cold VC8 builds. Full payload
SHA256 is
`ec90d466db8f4cb187863f1125ed614967ba4547a6e557406c23328debfecd4c`.
All136 section relocations are replayed without masking code or metadata.
This continues the independently checked Fighter slot3C family after Yukari.

## Observed target, boundary and ownership

All observations use Japanese1.06a SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
IDA preflight still rejects the GUI database's different executable. No IDA
analysis read/write or Ghidra/decompiler is used for this scope. All732 main
instructions were read from the hash-attested PE.

Main `[51D650,51E28C)` is3132 bytes, SHA256
`e5b3f190f41d05e3f8fb86e2624d19334f67c26b967be6a17501d4a977aa7dc0`.
The resolved CFG reaches every main instruction/byte and closes41 RET0s,
seven external zero-motion45AF40 tails and one common477830 default tail.
No unreachable main alignment, GS or EH is present. The eight-byte temporary
frame and EBX/ESI saves preserve the observed ECX receiver and unused return.
The entry follows INT3 padding. Next candidate51E570 starts after the reviewed
payload and four further alignment bytes.

The existing RTTI-backed roster anchor pins primary cell6C4EE8, offset3C of
Patchouli vtable6C4EAC, to51D650. Authored ownership was established before this
work; source/exactness were not. Exact promotion removes only this3132-byte
root from the roster rule's `skip_matching` selection. Candidate size and total
authored denominator do not change.

Full `[51D650,51E56C)` includes all3132 main bytes,71 destination DWORDs/284
bytes,447 remap bytes and five adjacent alignment bytes:

| Destination table | DWORDs | Input range | Remap start/bytes |
| --- | ---: | --- | --- |
| 51E28C | 23 | 198..418 | 51E2E8 /221 |
| 51E3C8 | 33 | 505..730 | 51E44C /226 |
| 51E530 | 15 | 100..114 | direct; no remap |

The second switch uses ECX as its remapped index. The nested card switch keeps
the signed card value in ECX while LEA forms EAX=ECX-100. Three alignment bytes
follow the first remap and two follow the second. None of this metadata extends
the callable/authored code credit, but all bytes participate in full comparison.

Physical CALL counts are435110 scratch1,45AF40 zero-motion23,435240 effect2,
4399C0 deque1,45DEB0 sequence-window1,435D60 surface-height2,45D110 finalizer1,
45F560 texture-state1,45B250 word-copy1 and4359F0 event1. The seven45AF40 tails
and477830 default are additional. No virtual call is emitted inside this root.
Every external relocation has an explicit target binding. Declaration-only
callees receive no extra implementation or matching credit.

## Complete source and independently reviewed differences

The receiver, scratch and returned-card prefixes are pointer-only declarations;
no complete owner or native deque is instantiated. The surface-height function
retains its independently accepted float-return/fastcall ECX ABI. Short action
and byte-facing effect transport follows the actual435200 word setter and
437C00 byte read, with the prior exact52-byte forwarding witness documented in
`COMMON_ACTION_INITIALIZATION_2026_10_25.md`.

Source reuse was limited to independently checked patterns. Important target
differences from Yukari and the common initializer are retained:

- 4/5 use +/-4;197/198 use +/-11.214 resets actual this+4 scratch, sets736=0,
  gravity0.6,73C=9 and74C=0. It has no extra108/10C publication afterward.
- 300/301 use conditional zero-motion plus180=0/184=1/750=1.418 first writes
  horizontal speed8.5 and then joins303/321/322's conditional zero path; keep
  the observed overwrite when47E is zero.
- 414 reads/scales horizontal speed before clearing730/732/736/738 and750,
  then consumes vertical speed. The target keeps this suffix separately from
  404/406/409/415.580's730/744/732 reset relationship differs from an already
  completed744 reset followed by a shared two-short suffix.
- 540/541 clear750;542 sets184=1 without zero-motion.505/506 set750 before the
  real zero helper, whereas520/521 leave that byte unchanged. Several high
  entries start inside shared tails:704/707 only zero motion, without600/604's
  preceding180=0;709 only clears730, without708's preceding horizontal zero.
- 690 unconditionally reads deque index0 at this+55C. There is no common
  initializer55A guard. After zero-motion it captures738 for both the switch
  and subsequent effect-code lookup. Fifteen signed byte levels624..632 form
  three five-column groups. Each increment keeps zero-to-one correction and
  signed upper clamp4, then clears the other two same-column bytes to-1.
  Case104's632-before62D order joins the observed114 tail. The following effect
  consumes signed byte `[this+5C0+card]+130` as a short, then window `(0,1,60)`.
- 720 and721 each capture current Y as double before the actual height call.
  Ordered `height >= captured_y` tails into zero-motion; unordered comparison
  returns. Both real provider calls and the pre-call read epoch survive.
- 730 uses texture index2 and resets76C/76A/766/768/764 before event23.797 and
  798 independently dispatch to zero-motion/gravity0.4/730=0, without a spawn
  packet.700 explicitly returns; unhandled actions tail into477830.

Original source names, full class layout and TU partition remain unknown.
Canonical equality does not prove a parked peer has the same compiler context.

## First full comparison and bounded controls

Private sources/inspection drivers remain in
`.analysis/exact-first-patchouli-action-entry-20261025/`; receipts are below
`build/exact-first-patchouli-action-entry-20261025/`.

| Complete source/control | Full bytes | Canonical SHA256 | Result |
| --- | ---: | --- | --- |
| First complete source | 3792 | bfb8aa73a5588b0227bcfef3b25b9808279917b47b1d4efd24cec3db9c3536f1 | nonexact+15 |
| Move both414 products ahead of short clears | 3764 | 6ddeafb9835dcbeec3b896127d6cddeb8139d6436b0a6ae04f4cd18bc15103f4 | rejected |
| Split414 products around actual clears | 3872 | 330aaed6330c324965b0fa1438f71a6ab3897679e6032b247ec535686ea7d37b | restores414 body |
| Independent797 and798 entries | 3872 | 451c05d461275c6082820f533778cbb9b66c9cb773c016ea5ceb93b8ed382e4e | restores dispatch/return placement |
| Keep580 short reset before float publication | 3868 | ec90d466db8f4cb187863f1125ed614967ba4547a6e557406c23328debfecd4c | exact |

The first complete comparison already retains all three table dimensions and
index ranges. It exposes414's pooled suffix: the first source reaches416 at
target-77 and has40 versus41 RETs. Moving both products earlier pools more
copies and is rejected. Splitting their real consumption around the resets
reproduces414 instruction-for-instruction and restores the target RET count.
Independent797/798 entries recover the direct equality dispatch and final
return placement.580's target-backed publication relationship prevents the
wrong shared two-short suffix; this also restores585's real shared zero-motion
site. The entire payload then matches. Every control changes full output;
there is no repeated neutral control or compiler-flag search.

These are ordinary C++ statements/lifetimes with real data consumers. No
assembly, copied code arrays, inert locals, fake return or padding is added.
Complete equality resolves the current source-shape questions, so no native
behavior matrix is run. Five target-free fixtures cover both remaps, ECX index,
LEA-based direct range, corrupt final index, metadata destinations, truncated
last direct word and unreviewed CFG edges. The range fixture caught stale SUB
ownership from a preceding cluster; the parser now uses the latest normalization
before the current bound and safely ignores zero-operand instructions.

## Reproduction and handoff

Run serially with the locked interpreter, CPU0/nice10:

```sh
taskset -c 0 nice -n 10 scripts/repo-python scripts/build.py --unit exact-first-patchouli-action-initialization --compare --json
taskset -c 0 nice -n 10 scripts/repo-python scripts/audit-patchouli-action-initialization.py
TH105_ENABLE_GS=0 TH105_FP_MODE=default TH105_INLINE_MODE=default \
  taskset -c 0 nice -n 10 scripts/compile-unit.sh src/characters/PatchouliActionInitialization.cpp build/patchouli-entry-cold.obj
taskset -c 0 nice -n 10 scripts/repo-python scripts/audit-patchouli-action-initialization.py --object build/patchouli-entry-cold.obj
```

Only new local source/interfaces/unit and14 exclusive literal aliases are added;
prior accepted source/header/compiler settings and bindings are unchanged.
Provenance check and complete serial cold replay pass517 units/all1405 accepted
functions; receipt `build/exact-first-patchouli-action-entry-20261025/cold-all.log`.
The exact ledger records366327 authored bytes; source-present1548/mapped1567,
units587. Next source-missing same-slot peer is Suika5AD4A0, candidate2577
bytes; independently re-attest its slot and complete CFG/ABI before implementation.
