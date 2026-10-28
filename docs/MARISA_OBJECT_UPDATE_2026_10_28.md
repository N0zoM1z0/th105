# MarisaObject complete update, 2026-10-28

`MarisaObject_update_action_state @ 004BBE00` now has a complete manual source
hypothesis for all 41 primary actions and the default. It is **not exact**.
The first complete compilation preceded source-property controls. No case,
normalized instruction sequence, mapped byte, or partial body receives credit.

## Observed target

Canonical Japanese TH10.5 v1.06a SHA256:
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
RTTI primary slot28 cell6C4524 points to4BBE00. Table6C44FC, COL6D9EC0 and
TD6E7F6C identify MarisaObject. The next independent initializer starts4C8050.

Callable `[4BBE00,4C7C83)` is48771 bytes, SHA256
`ee841171c5399bb81bbfd2514da95cfc572a90bf85d8a3f077e6064006b18b36`.
The raw CFG reaches11310 instructions/48722 bytes, with71 RET0s,355 direct
calls to22 targets and36 virtual calls. No tail exits the callable. Six
internal alignment ranges account for49 unreachable bytes:
4BDEE5..4BDEF0,4BDF28..4BDF30,4BE528..4BE530,4C003D..4C0040,
4C0075..4C0080,4C1938..4C1940. The target prologue aligns ESP to8 and
allocates0x340 bytes. These bytes remain included in all comparisons.

Complete payload `[4BBE00,4C8050)` is49744 bytes, SHA256
`ed64218fba02fe174150885db55f58797fbcb3ff7e47f79a54c4c26b9cb64e4d`.
After the callable are one NOP,18 destination tables and four byte remaps.
Table destination counts, in physical order:
42,9,8,5,6,7,11,14,8,7,5,4,7,12,7,8,12,4.
The remaps at4C7D2C/4C7F60/4C7FC4/4C7FF8 contain200/22/19/22 bytes.
Inter-remap alignment at4C7F76/4C7FD7/4C800E is8BFF/90/8BFF.
The audit validates all table edges, remap ranges, metadata coverage, target
hashes and callable reachability. It compares the entire unmasked payload,
including every relocation after the provisional callable boundary.

## Evidence and source decisions

The repository direct IDA preflight could not load its local MCP runtime.
That direct session was not used. The separate Factory-native th105-ida
stdio provider was independently attested against canonical metadata, entry
68B9D2, entry bytes, function inventory and available operations. Its
4BBE00 decompilation was used only as a navigation hypothesis. Raw canonical
instructions govern all decisions; no target bytes or IDA metadata were edited.

The pointer-only receiver header does not claim an allocation size. Slot0C,
14,1C,20 and28 signatures follow the existing engine calls. Member435160 uses
this+4. Owned spawns465190 and wave dispatch45C030 use owner348. Effect435240
uses this except the explicit owner call4C32EB. Owner-relative5B0400 takes
integer offsets38/54 and returns Fighter*. Shared header consumers are unchanged.

Manual review corrected decompiler omissions of actual sine/cosine/atan2 and
square-helper ST0 results, signed owner state bytes, qword pre-height-call Y
captures, late callback-sensitive owner reloads, orbital Y addition grouping,
and unordered floating guards. Phases800/848/863 deliberately retain the
observed repeated movement steps. Action822's inner phase chain is a sequence
of scalar tests, not an extra jump table. Its color conversion is directly to
an unsigned byte, retaining native x87 truncation rather than a helper call.
RNG conversions preserve float conversion before double arithmetic. Early
800/801/802 arm ordering follows raw control flow. No inert locals, manual
register assignments, copied instructions, assembly or padding were introduced.

## Reproduction and current result

```sh
taskset -c 0 nice -n 10 scripts/repo-python scripts/build.py \
  --unit exact-first-marisa-object-update --compare --json
scripts/repo-python scripts/audit-marisa-object-update.py --target-only
scripts/repo-python scripts/audit-marisa-object-update.py
```

Receipts: `build/frontier-4bbe00-20261028/formal-build.json` and
`full-audit.json`. The selected canonical full candidate is50156 bytes,
SHA256`7378dbdae931e6b638b8b04269c50711cf02447b6cd2c75fc35d65a746d53c14`.
Full comparison has41591 unmasked differing bytes, first+37/4BBE25 in the
initial default-branch displacement. This is not merely a displacement fix:
code order, precision, call/return sharing and later control flow remain
nonexact. Candidate frame0x340, all18 table dimensions and four remap lengths
agree;37 virtual calls versus36 and92 RETs versus71 remain. All22 direct
callee counts agree except advance_frame11 versus10. These structural facts
are diagnostics, not execution-equivalence or byte-exact acceptance.

The unit is isolated; aliases only bind this function's literal operands and
match identifier. The callable/source/mapping inventory changes, but
`matches.csv` and confirmed exact totals remain unchanged. Original class
names, full class layout, original expression lifetimes, control-sharing and
translation-unit context remain hypotheses until independently established.

## Target-backed continuation refinement

The selected source now shares the observed825/826 parented expansion fade,
812/849 owner-hitstop exit and865/901 RGB fade continuations. These are ordinary
source labels for identical authored behavior, not copied instruction blocks.
The812 orbital offset expressions preserve native integer-multiply conversion
and compute the sine radius before loading the owner Y. The825/826 subtractive
integer offsets retain the native FISUB operation. Direct aim-call arguments
restore X-then-Y evaluation without keeping both rounded arguments live across
the call;900 RNG-plus-offset grouping follows its raw x87 additions.

A separate whole-root shared-finish control compiled50124 bytes but moved
previously aligned early control flow and changed advance_frame sharing to9
versus native10. It is not selected. Smaller size is not the acceptance rule.
The selected50156 bytes remain wholly nonexact, with all18 destination-table
counts and all263 remap bytes equal, native0x340 frame, and the remaining
call/return/control-sharing differences stated above.
