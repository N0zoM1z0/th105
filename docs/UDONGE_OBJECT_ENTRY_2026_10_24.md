# UdongeObject initializer: complete canonical acceptance

Work begun2026-10-24 and finalized2026-10-25; recipe/report paths retain the
bounded work unit's start date.

`0x005DF0E0`, UdongeObject primary slot+3C, accepts all10723 callable bytes and
the complete11112-byte emitted payload. Formal and independent cold compilations
reproduce the target SHA256, including all three destination tables,199 remap
bytes and every one of500 relocations. No masking, assembly, manual padding, inert
locals or fabricated helper bodies are used.

Complete11112-byte canonical SHA256:
`bf3801d220492a28d82be486b7c1a8706c83e8e4edfd2b6ef403618148218654`.
Callable SHA256:
`5ce63575231f335fa762e8b294ef98c92c52fbec120d025629c99e5499a67f8b`.
Selected source is `src/characters/UdongeObjectActionEntry.cpp/.hpp`;
unit `exact-first-udonge-object-entry` uses the unchanged VC8 SP1/O2 probe
profile with GS disabled.

```sh
taskset -c 0 nice -n 10 scripts/repo-python scripts/build.py \
  --unit exact-first-udonge-object-entry --compare --json
scripts/repo-python scripts/audit-udonge-object-entry.py
taskset -c 0 nice -n 10 bash scripts/compile-unit.sh \
  src/characters/UdongeObjectActionEntry.cpp \
  build/exact-first-udonge-object-entry-20261024/cold.obj
scripts/repo-python scripts/compare-unit-object.py exact-first-udonge-object-entry \
  build/exact-first-udonge-object-entry-20261024/cold.obj --json
scripts/repo-python scripts/audit-udonge-object-entry.py \
  --object build/exact-first-udonge-object-entry-20261024/cold.obj
```

Every command returns0. The public audit replays the entire COFF section tail;
the callable comparator independently uses the reviewed10723-byte boundary.
Formal reports pin source/compiler/inputs. Existing-object comparison reports
unverified build provenance, supplied separately by the independent cold build.
Receipts are under `build/exact-first-udonge-object-entry-20261024/`.

## Observed target, origin and complete boundary

The only analyzed target is original Japanese1.06a SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Existing RTTI/allocator/vtable evidence classifies this root authored. Primary
vtable6C5DA4, slot cell6C5DE0, points to5DF0E0. There was no previous durable
name or selected source. Authored classification and denominator are unchanged;
the generated origin witness is promoted to `canonical-exact-authored`.
The Object rule skips matching roots, so its remaining census changes from
29/659829 to28/649106; exactly10723 bytes move to the canonical baseline.

| Region | Reviewed extent |
| --- | --- |
| Callable | 5DF0E0..5E1AC2 inclusive /10723 bytes |
| First alignment | 5E1AC3 /one NOP |
| Primary destination table | 5E1AC4..5E1B43 /32 DWORDs |
| Action800..998 remap | 5E1B44..5E1C0A /199 BYTEs |
| Second alignment | 5E1C0B /one NOP |
| 858 sequence table | 5E1C0C..5E1C1B /4 DWORDs |
| 859 sequence table | 5E1C1C..5E1C47 /11 DWORDs |
| Following separation | 5E1C48..5E1C4F /eight INT3 bytes |
| Next independent callable | 5E1C50, outside this payload |

Raw traversal reaches2712 of2716 decoded instructions. The remaining four are
26 independently reviewed alignment bytes at5E07E9/5E0EDA/5E155A/5E19B9,
skipped by unconditional jumps. They remain in the canonical callable extent.
All three indirect jumps follow the reviewed tables. The only external jump
is real980 tail5E1AB6 ->596370. There are37 RET0 exits. The frame reserves28
local bytes and saves ESI/EDI, then EBX for in-range actions;815 additionally
saves EBP around its selector. No root EH region is observed.

| Direct callee | Physical calls | Observed contract |
| --- | ---: | --- |
| 68A1A0 | 28 | FTOL:27 sequence selections plus one frame selection |
| 4067D0 | 114 | Bounded RNG, with unsigned float conversions |
| 4FCA60 | 8 | Parented request, seven four-byte arguments, RET28 |
| 64CCB0 | 13 | Unparented request, seven four-byte arguments, RET28 |
| 435160 | 7 | ECX=this+4, two float arguments, RET8 |
| 45C030 | 3 | Parent receiver, unsigned wave-handle index2, RET4 |
| 406540 | 1 | Two float arguments y/x, float result in ST0 |

All174 direct calls and28 virtual calls survive. Virtual calls comprise27
physical slot0C selectors (820/821 share one) and one slot1C frame selection.
All175 REL32 relocations, including the tail, and325 DIR32 relocations replay
without overrides to instruction bytes. Declaration-only helpers receive no
implementation/exact credit from this caller.

45C3E8 loads the selector argument from a four-byte stack slot;45C3EC/45C40E
test AX and45C3EF writes the low WORD. Its loop decrements EAX but controls only
AX. A local signed-WORD call view preserves that physical contract and recovers
the caller's argument scheduling. Existing accepted int-view declarations are
unchanged. The frame-selection view likewise consumes a low WORD in its
four-byte slot. Original nominal class and parameter spelling remain unknown.

## Inferred complete source and reviewed family differences

The implementation retains offsets, numeric states and pointer-only partial
receiver views. Never instantiate/embed these as recovered complete owners.
Peer initializers are hypotheses; Udonge's own instructions establish every
selected case, access width, call and continuation.

- This prefix clears float37C before WORD384 and float380 before WORD386.
 802 sets1841 without selecting.998 has an explicit no-op table entry.980
 preserves the real shared tail.849 only selects;855 sets1841 before selecting.
- 800/910 call the parent wave dispatcher at sequence1, draw heading/scale,
 then issue five **action800** unparented requests.920 sequence15 instead
 issues two action920 requests with packet word16. Packet speeds convert
 unsigned **integer RNG15+10**, preserving addition before float conversion.
 810/811/812/852/900 similarly convert integer RNG30+45 for128.
- 800 sequence4 emits {storedHeading,0,3}, clears184 and finally assigns113128.
 910 sequence4 emits its parented910 packet, changes word2 to1 for a second
 unparented910 request, then assigns113128.920 sequence14 independently
 rebuilds {storedHeading,0,15} and {freshStoredHeading,0,17} for its two requests.
- 801/810/900 retain distinct physical jitter bodies:124/128 use30-RNG60,
 370 usesRNG8+4, and374 consumes a float product before adding double(float0.04)
 or double(float0.1). Other scale formulas deliberately keep their product
 extended. Do not impose one rounding macro on the entire family.
- 815 sequence0 assigns11C4/1203 and sends {0,0,3} at layer+1.816/912 assign
 only11C35 in sequences0/4.817 writes17C9 twice around its signed-facing
 calculation; sequence2 independently reads H[3] for each scale. Sequence3
 sets1841 and shares853 sequence2's real two-read scale-copy tail.
- 820/821 share a selector and heading-derived scale tail after distinct17C2/6
 stores.911 sequence3 joins that same result path after its random heading.
 **H[0] is loaded before clearing BYTE113.** The consumed scale is
 H[0]-double(float0.3), then copied to11C/120. The first source's byte-clear
 before-load ordering fails two native alias fixtures.
- 822 uses separate random scale components at sequence3 and an unsigned>=50
 branch at sequence1.825 copies signed parentBYTE607 into WORD36C, preserves
 its F100 gravity stores, and sequence8 requests action800.826's signed<=4
 guard includes negative sequences; it independently writes heading -H[0]
 times signed BYTE facing.848 uses signed<=2 before its extra virtual frame
 selection from H[1]; later velocities come from either constants or H[0]/H[1].
- 850 uses a real float loop index0..3 with step double1 and packets
 {n*double90,0,1}.853's packet stores occur in the observed order1,2,0. Its
 shared H[3] copy tail remains separate from850's independent physical copy.
- 856/857 keep their distinct alpha/scale cases and physical motion calls.
 857 sequence0 first sends {0,0,2}, then six {RNG360,0,12} requests. Sequence8
 uses an unsigned<=49 branch;12 independently rounds two products for scales.
 858 retains its explicit sequence1 no-op, which preserves its four-slot table.
- 859 keeps a genuine11-slot switch. Sequence6 sends three {0,0,7} requests,
 then four outer by eight inner float iterations. The outer angle is
 RNG40-n*double60-double20; packets are
 {RNG30+double(angle)-double15,RNG6+m*double7+double12,10}.
 Both loops increment by float1. Other sequence1/7 bodies retain their own
 physical copies and use RNG60-30, rather than the reversed jitter subtraction.
 Sequence4 converts parentfloat7B4 to signed BYTE before integer multiplication
 by60; sequence5 changes only11C;10 draws its own scale/heading/370 values.
- 911 sequence0 stores -atan2_degrees(otherY+double100-selfY,
 (otherX-selfX)*signedFacing), with independently rounded float call arguments.
 The pointer is from170, not348/34C.920 sequence1 sets113192 after motion;
 the later wave/motion/request sequences are distinct and remain ordered.

## Comparison-directed lifetime recovery

The first complete build already retains all174 direct/28 virtual calls and
the real tail. Whole comparison directs source recovery toward the actual
820/821 and817/853 shared paths, explicit858 no-op, selector argument width,
853 packet store order and857's real branch stores. Independent local consumed
scale copies do not recover the target's common tail. Sharing an input value
adds an unsupported intermediate round trip; sharing the **computed result**
removes it and leaves only two stack-displacement bytes different.

Raw instructions place859's inner float index and the final shared scale
result at the same frame location, +0C before the two epilogue pops. A real
scalar reused for those disjoint lifetimes recovers that storage without an
extra local or padding. This final change accepts the entire11112-byte payload.
It is an inferred source explanation, not proof of the original variable names
or whether the original compiler coalesced separate locals. Complete owner
layout, original TU/project settings and nominal gameplay meanings remain
unknown. Exact acceptance does not require inventing those identities.

## Specific native alias control

```sh
taskset -c 0 nice -n 10 scripts/repo-python scripts/audit-udonge-object-entry-paths.py
```

All4 inputs pass on formal and independent cold objects:820/821 sequence3 each
with ordinary H[0] and with H pointing to owner113. The alias fixtures store
H[0] bits3F800034 and H[2] at11B; they verify load-before-clear followed by the
consumed scale publication. The native selector, checked tree, FTOL and frame
instructions execute against read-only resource fixtures. Each path completes
a real RET0 with an empty x87 stack and preserved control word. No helper
return/result or control-flow transfer is injected. Source and target run in
separate canonical memory overlays; the target executable on disk is unchanged.
The first complete source fails exactly the two alias inputs. These four vectors
resolve that read epoch; whole canonical equality supplies the broader byte
claim. They are not whole-game behavioral equivalence evidence.

IDA preflight still rejects GUI SHA10350095..., so it supplies no semantics or
writes. One direct serial read-only/noanalysis Ghidra run uses CPU0/nice10 and
384MiB heap. Disk/import/entry/mapped bytes and the bounded root SHA are
independently checked; temporary root/helper views and the real-tail metadata
are read back, rolled back, and all nine primary database pins remain unchanged.
Decompiler text is a hypothesis; the raw CFG and strict comparisons are the
acceptance evidence.

Two new generic keys bind float0.71 at6C5F00 (`__real@3f35c28f`,8fc2353f) and
float17 at6C4A94 (`__real@41880000`,00008841). All older bindings, accepted
headers and compiler settings are unchanged.

## Fresh aggregate replay and cohort checkpoint

```sh
taskset -c 0 nice -n 10 scripts/repo-python scripts/verify-exact-units.py --all
```

This fresh serial replay deletes each accepted object/provenance before building
and passes515 cold units/all1403 accepted functions (`cold-all.log`). The final
Udonge full-payload audit also passes11112/11112 after that rebuild. The current
aggregate is359740 exact code bytes; this root adds10723. Its389 adjacent
metadata/alignment bytes compare as part of the full payload without code credit.

All15 roster Object slot3C roots now have selected source:3 exact ledger records
(Alice/Iku/Udonge) and12 implemented/nonexact roots. The census is recorded in
`cohort.json`; source selection is not a new behavior/exact claim for those12.
Keep their recorded residuals parked and choose a new complete medium/large
authored representative unless new independent evidence opens a specific peer.
