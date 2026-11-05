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

## Actions 821, 857 and 910 motion gates, 2026-11-04

Seven native paths compare the surface with the QWORD next Y and branch to
continued motion on `AH & 1`, followed by the frame-count gate. Their status
tests are at `0x005B491B`, `0x005B5313`, `0x005B70A1`, `0x005B7968`,
`0x005B7C33`, `0x005B93F5` and `0x005B9D56`. Unordered comparisons also
take that motion branch. The earlier ordered `surface < nextY` instead fell
through to the impact path on NaN. The seven conditions now use the negated
ordered `surface >= nextY`, preserving the native unordered path. Fresh VC8
emits the same local status mask, branch and frame-count check at all seven
sites. This does not assert whole-function or unmasked-exception equivalence.

The 52,190-byte callable remains nonexact from +17; the candidate section
tail is 53,204 bytes. No exact credit is added.

## Actions 815 and 940 continuation gates, 2026-11-04

The three action 815 paths test the surface/current-Y comparison at
`0x005B210D`, `0x005B238D` and `0x005B2616` and continue on `AH & 1`,
including unordered values. Their source conditions now preserve that case.
Action 940's three paths at `0x005BAD55`, `0x005BB175` and `0x005BB54A`
likewise continue to the horizontal-bound checks when the surface comparison
is unordered. Those checks also let unordered X pass. The first two source
phases now use the same negated impact condition already used by phase 2.
Fresh VC8 emits the corresponding local tests and branches for these paths.
These observations do not establish unmasked-exception or whole-root equivalence.

The 52,190-byte callable remains nonexact from +17 with a 53,204-byte candidate
section tail. No exact credit is added.

## Actions 858, 900 and 901 scale gates, 2026-11-05

Native action 858 tests at `0x005B8109..0x005B8114` and
`0x005B8169..0x005B8174` enter the fading paths only for ordered values
below 0.5 and above 2.0 respectively. Actions 900/901 retire only for an
ordered nonpositive scale at `0x005B89DA..0x005B89E5` and
`0x005B9017..0x005B9022`. The earlier negated comparisons admitted NaN;
the source now expresses the ordered relations. Fresh VC8 emits the
corresponding masks and branches at `0x7CAB`, `0x7D0B`, `0x8577` and
`0x8BD1`. This does not establish whole-root or unmasked-exception equivalence.

The 52,190-byte callable remains nonexact from +17; the candidate section
tail is 53,204 bytes. No exact credit is added.

## Action 855 spawn X grouping, 2026-11-05

Native `0x005B691C..0x005B692C` subtracts 150 from current X before
adding the random offset. The previous source associated the random offset
with X first. It now uses `random + (X - 150.0)`, preserving the native x87
order and its possible rounding difference. Fresh VC8 emits the corresponding
`fld X`, `fsub 150`, `faddp` sequence at `0x64FD..0x650D`. Random call order
is unchanged. This does not establish whole-root or unmasked-exception
equivalence.

The 52,190-byte callable remains nonexact from +17; the candidate section
tail is 53,204 bytes. No exact credit is added.

## Action 800 upper X bound, 2026-11-05

At `0x5B09CD..0x5B09DE`, the target compares 1380 against X and retires only for an ordered X greater than 1380 (`test ah, 0x05; jnp`). The prior negated `<=` also retired an unordered X. The source now uses ordered `>`, and the focused candidate has the same branch at `0x55D..0x56E`. The 52190-byte root is still non-exact (candidate section tail 53204, first mismatch +17); no exact credit is claimed.

## Actions 815 and 940 fade speed, 2026-11-05

The target phase 6 checks at `0x5B293C..0x5B294A` and `0x5BB957..0x5BB965` enter fade only when parameter speed is ordered and at or below 6. The previous negated greater-than conditions also entered fade for unordered speed. Both now use ordered `<=`; focused compilation reproduces the target-style `test ah, 1; jne` continuation. The 52190-byte root remains non-exact (candidate section tail 53204, first mismatch +17); no exact credit is claimed.

## Action 811 signed collision counter, 2026-11-05

Three native paths, `0x5B1236..0x5B1253`, `0x5B13E1..0x5B13FE` and `0x5B14B1..0x5B14CE`, compare the 16-bit field at `0x364` against 5 with signed `jge`. For a negative value and collision state 4 the target increments the counter, clears the collision and increments the hit byte; the earlier unsigned source skipped that work. The three source paths now use the signed short. Focused VC8 compilation confirms signed threshold gates. Negative-counter reachability in ordinary play is unproved; the complete root remains nonexact with no exact credit.

## Action 930 signed age thresholds, 2026-11-05

At `0x5BAAC1..0x5BAB23`, the native incremented 16-bit field at `0x366` is compared against 120, 180, 240 or 300 using signed `jl`, with a shared expiration branch. The former unsigned local caused a negative incremented value to expire immediately. The local and field access are now signed; focused VC8 emits signed threshold jumps for all four selectors. Normal-play reachability of a negative age is not established, and the full root remains nonexact without exact credit.

## Action 815 signed owner-level timing, 2026-11-05

For sequences 7 and 8, the native owner byte `0x608` is compared with 4 using signed `setge` at `0x5B2B47..0x5B2B56` and `0x5B2EDA..0x5B2EE9`. The earlier unsigned source treated byte values `0x80..0xFF` as upgraded, shortening the respective thresholds from 45 to 30 and 60 to 40 frames. Both reads now use signed char. Focused VC8 emits `setge` at the two corresponding sites. Negative level reachability in ordinary play is unproved; the entire root remains nonexact with no exact credit.

## Action 818 signed owner-level rate, 2026-11-05

At `0x5B4155..0x5B415D` and `0x5B42A5..0x5B42AD`, the owner byte `0x60B` uses signed `jg` comparisons with 2 and 3 to select the projectile interval. The former unsigned local routed values `0x80..0xFF` to the three-frame branch rather than the native five-frame branch. The local now reads a signed byte, retaining the separate post-random signed reload used for projectile speed. Focused VC8 emits signed branches; ordinary-play reachability of negative levels is unproved. The full root remains nonexact and receives no exact credit.
