# SuikaObject complete update, 2026-10-28

`SuikaObject_update_action_state @ 005B0460` has a complete manual source
hypothesis for31 primary actions and the default. Whole canonical replay is
**nonexact**. Source presence, matched counts and metadata do not earn byte credit.

## Raw target and owner

Canonical Japanese1.06a SHA256:
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
The raw RTTI chain is primary vtable6C5B04, slot28 cell6C5B2C, COL6DB060,
TD6E89C0 `.?AVSuikaObject@@`. The audit verifies this independently. The existing
initializer5BD380 and its accepted dependencies remain unchanged.

Callable `[5B0460,5BD03E)` is52190 bytes, SHA256
`7d949921e4b7bd78fee89e6c400dd0d5f627e7207a4b9f51d075693f1e5b5b46`.
All12269 instructions decode; the CFG reaches12266 instructions/52177 bytes.
Thirteen unreachable alignment bytes are5B242D..5B2430,5B7C5D..5B7C60 and
5B9A19..5B9A20. There are59 RET0s,17 virtual calls and23 distinct direct callees.
There is no outgoing callable tail. Native ESP alignment is8 and frame is4B0.

Full payload `[5B0460,5BD374)` is53012 bytes, SHA256
`81051d3a275426cada3750802f29fd476452a718e4db0e6e1700438bdc2a677f`.
Two-byte8BFF alignment precedes the tables. Eighteen table dimensions are
32,14,6,9,7,9,4,11,5,4,4,4,4,10,4,5,4,19 DWORDs. One200-byte primary remap at
5BD0C0 maps800..999. Twelve following INT3 bytes separate the initializer and
are not claimed. The audit traverses every edge and covers the entire payload.

## Evidence and source

The repository IDA preflight lacked its pinned local MCP runtime; that session
was not used. Factory-native th105-ida was independently re-attested at20:23 UTC
against canonical metadata, entry68B9D2, mapped entry bytes, function inventory
and46 exposed operations. Decompilation is navigation only; raw instructions
and the canonical target decide comparison. No target or IDA metadata changed.

The receiver is a pointer-only view. Motion435160 uses this+4. Wave45C030 uses
owner348. Quantity45C060 is called on this, with the independently established
int/int/short/signed-char contract. Seven4359D0 scalar calls use owner348; the
910 difficulty-wave call uses this. Both view declarations have the same
already-proved unused-this callee contract, without changing that implementation.
The root snapshots owner348 and its4B8 field address before dispatch;853 consumes
the field after callbacks. Candidate owner-address calculation/register scheduling
still differs. A genuine pointer-to-reference source control was byte-neutral.

Source corrects decompiler omissions of sine/cosine/atan2/square return values,
retains signed versus unsigned counters, real3/4-float packet arrays, sequential
phase reloads, owner/related/target distinction and pre-height qword snapshots.
801's2.5 limit uses a float source carrier after the first whole compile, removing
a non-native qword literal. The first whole candidate already recovered4B0 and
all direct-call counts. No partial case was compiled or credited.

900/901 retain the observed entry guard within phase2, including its phase-zero
check. The ordinary source is compiled as written; no volatile/fake alias is
introduced to force this apparently redundant path.940 phase16 retains the
observed unusual alpha comparison, and its fading phases0..2 subtract6 from
alpha but5 from the two color channels. Original source spelling and all
floating-point/exception paths remain hypotheses until whole exactness.

## Selected replay

`scripts/repo-python scripts/build.py --unit exact-first-suika-object-update --compare --json`

The candidate complete payload is53204 bytes, SHA256
`46a881082898988338e7431c8f6ef3771c7ef4fb61e36517940d70585a7123a2`.
First mismatch+17 /5B0471 is the initial owner/switch scheduling;50218 unmasked
positions differ including length. Frame4B0, all23 direct-callee counts, all18
table dimensions and all200 remap bytes agree. Candidate70 RETs/15 virtual calls
versus native59/17 show different control-tail sharing. In particular,812's
sequence4 paths and818's sequence-advance return merge differently. Packet stack
homes, scalar lifetimes, owner-address scheduling and shared continuations remain
unresolved. No exactness percentage follows from these diagnostic agreements.

Audit: `scripts/audit-suika-object-update.py`.
Receipts: `build/frontier-5b0460-20261028/{formal-build,full-audit,target-audit}.json`.
Private preparation: `.analysis/frontier-5b0460-20261028/`.
Only source/mapping ledgers advance. `matches.csv` is unchanged, and unchanged
accepted units retain their incremental receipts. No shared ABI/profile/binding
was modified and no full corpus rebuild was needed.
