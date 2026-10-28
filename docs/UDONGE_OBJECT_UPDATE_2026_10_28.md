# UdongeObject complete update, 2026-10-28

`UdongeObject_update_action_state @ 005D46C0` has a complete manual source
hypothesis for31 primary actions and the default. It is **not exact**. The
first complete body compiled before source controls; no partial branch or
normalized instruction comparison receives exactness credit.

## Observed target and ownership

Canonical Japanese TH10.5 v1.06a SHA256:
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Primary vtable6C5DA4, COL6DB294 and TD6E8B04 identify UdongeObject; slot28
cell6C5DCC points to5D46C0. The following independent action initializer is
5DF0E0 and its existing source/unit remain unchanged.

Callable `[5D46C0,5DED80)` is42688 bytes, SHA256
`11e719f4310c3c30abb1ac1c71b0010c89af29180171d5b1dee319233a90a589`.
All10269 instructions decode; CFG traversal reaches10265 instructions and
42671 bytes, with64 RET0s and25 virtual calls. Four internal alignment ranges
account for17 unreachable bytes:5D482A..5D4830,5D4C3E..5D4C40,
5D647A..5D6480 and5D71CD..5D71D0. No tail escapes the callable.
The native prologue aligns ESP to8 and allocates0x2F0 bytes.

Complete payload `[5D46C0,5DF0D1)` is43537 bytes, SHA256
`08cad8c18fa386a4775237e631d62dcabb7d989e55472c3b652a7cfd34365b71`.
Seventeen destination tables contain, in order:
32,5,8,12,8,5,11,7,6,9,13,4,11,9,4,5,9 DWORDs.
Primary800..998 uses199 remap bytes at5DEE00; phase920 uses17 remap bytes
at5DF0C0. One NOP at5DEEC7 aligns the second table. Fifteen INT3 bytes after
the complete payload separate the following initializer and are not claimed.
The audit covers every table edge, both remaps, complete metadata extent,
canonical hashes and all callable/padding bytes without masking.

## Source evidence

The direct repository IDA preflight lacked its local MCP runtime; that
session was not used. Factory-native th105-ida was independently re-attested
at19:14 UTC with canonical metadata, entry68B9D2, mapped entry bytes,
function inventory and46 exposed operations. Its decompilation was only a
navigation hypothesis. Canonical raw instructions determine the source;
no IDA metadata or target bytes were modified.

The new receiver is a pointer-only view, not an allocation/layout claim.
Motion helper435160 uses this+4; wave45C030 uses owner348. Deferred-counter
45D510 calls use target170, including the two separately reloaded calls in857.
Bounds helper4FC710 is the already proved four-int/three-short interface.
Owner-relative5B0400 takes integer offsets and returns Fighter*. Owner
virtual08 uses the existing short-action contract;920 action700 then reloads
the owner before setting768 to60. No shared source header changed.

Raw review corrects omitted sine/cosine/atan2/square return values, signed
owner skill tiers and sequence counters, float RNG conversions, integer
addition before unsigned conversion, qword X/Y and pre-height snapshots,
and callback-sensitive sequential phase tests.848 intentionally ignores the
advance result and can decrement without returning.920 preserves two height
calls and its post-movement next-Y snapshot.800/910/920 half-scale fade tests
use ordered `<0.5`, not `!(>=0.5)`; the latter incorrectly changes the native
unordered path and was corrected after the first whole comparison.

Several native phases store11C after adding0.05f and then overwrite11C from
120. The ordinary source retains these observed expressions; no volatile,
fake alias or instruction insertion forces redundant stores.825's retained
entry guard and inter-action shared continuations are still source-shape
questions, not a license to manufacture dead instructions or fake liveness.

## Reproduction and result

```sh
taskset -c 0 nice -n 10 scripts/repo-python scripts/build.py \
  --unit exact-first-udonge-object-update --compare --json
scripts/repo-python scripts/audit-udonge-object-update.py --target-only
scripts/repo-python scripts/audit-udonge-object-update.py
```

Receipts: `build/frontier-5d46c0-20261028/formal-build.json` and
`full-audit.json`. Full selected candidate43873 bytes, SHA256
`86d85bf7ca358e9a9f2b1a8bb021c234c56c2269a2daf8b1063a84ce465fc97c`.
Unmasked comparison reports38087 differing bytes, first+37/5D46E5 in the
initial default-branch displacement. The actual812 floating count lifetime
recovers the native0x2F0 frame; this is still a whole-layout/precision/
physical-sharing residual, not merely a displacement correction.
All17 table dimensions and all216 remap bytes agree. Candidate has74 RETs
versus64 and25 virtual calls versus25. All22 direct-callee counts now agree,
including19 sine calls and15 advance calls. These are diagnostics only.

Source and mapping inventory now include this root; exact matches do not.
Original class layout, translation-unit visibility, expression lifetimes,
control sharing and full execution equivalence remain unproved. Continue
from whole-byte evidence; never pad the frame or force register allocation.

## Native lifetime and continuation refinement

The first44125-byte whole body exposed a real width omission in812: the
float-rounded owner60C+8 count is widened into a qword at5D781C and stays
live through the radial loop. A real double count initialized from that float
recovers frame2F0 naturally; no filler local or forced stack size is used.
801's randomized X and Y centers are also both qwords at5D5D92/5D5D9C,
not the decompiler's apparent float X. Spawn argument expressions preserve
right-to-left evaluation and keep computed Y on the outgoing argument stack
while X's trig/RNG call runs.

The selected source shares the actual816/912 owner-angle-wave continuation
and the generic817 advance exit, while849 retains its independent advance
call. This restores all direct/virtual call counts and all17 table dimensions
without merging semantically different entry-retirement paths. The early
800/910/920 empty-alpha guard uses the native nonpositive spelling. Local
frame offsets, remaining physical tail sharing and instruction scheduling
still differ; matching counts and size reductions are not exactness claims.
